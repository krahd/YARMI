"""Experimental terminal-to-PCM adapter; not production real-time DSP."""
import math
import queue
import struct
import sys
import threading
from fractions import Fraction as F
from station import Event, Station, Track


class PCM:
    def __init__(self, station, rate=16000, bpm=120, block=256):
        if not all(isinstance(x, int) and x > 0 for x in (rate, bpm, block)):
            raise ValueError("rate, tempo and block length must be positive integers")
        self.station = station
        self.rate, self.block = rate, block
        self.beats_per_frame = F(bpm, 60 * rate)
        self.frame = 0
        self.voices = []
        self.length = max(1, rate // 10)

    @property
    def beat(self):
        return self.frame * self.beats_per_frame

    def render(self, immediate=()):
        end = self.frame + self.block
        for beat, _, pitch in self.station.schedule(self.beat, end * self.beats_per_frame):
            # Floor within this half-open block; never assign to the following block.
            self.voices.append((int(beat / self.beats_per_frame), pitch))
        self.voices.extend((self.frame, pitch) for pitch in immediate)
        values = [0.0] * self.block
        for onset, pitch in self.voices:
            omega = 2 * math.pi * 440 * 2 ** ((pitch - 69) / 12) / self.rate
            for frame in range(max(self.frame, onset), min(end, onset + self.length)):
                i = frame - onset
                values[frame - self.frame] += .16 * math.sin(omega * i) * (1 - i / self.length)
        self.frame = end
        self.voices = [(onset, pitch) for onset, pitch in self.voices if onset + self.length > end]
        return struct.pack(f"<{self.block}h", *(round(max(-1, min(1, x)) * 32767) for x in values))

    def command(self, line):
        words = line.split()
        if len(words) == 2 and words[0] == "hit":
            pitch = int(words[1])
            if not 0 <= pitch <= 127:
                raise ValueError("pitch must be 0–127")
            return pitch
        if len(words) == 3 and words[0] == "period":
            beats = F(words[2])
            if not F(1, 8) <= beats <= 64:
                raise ValueError("period must be 1/8–64 beats")
            self.station = self.station.set_period(words[1], beats)
            return None
        raise ValueError("use hit MIDI_PITCH, period TRACK BEATS, or quit")


def main():
    pcm = PCM(Station((
        Track("a", (0, 0), (6, 4), F(3), (Event(F(0), 52), Event(F(1, 3), 59))),
        Track("b", (5, 1), (1, 4), F(5, 2), (Event(F(1, 2), 67),)),
    )))
    commands = queue.Queue(maxsize=32)

    def read_commands():
        for line in sys.stdin:
            commands.put(line.strip())
        commands.put("quit")

    threading.Thread(target=read_commands, daemon=True).start()
    print("Commands: hit 64 | period a 5/2 | quit", file=sys.stderr, flush=True)
    try:
        while True:
            immediate = []
            for _ in range(8):
                try:
                    command = commands.get_nowait()
                except queue.Empty:
                    break
                if command == "quit":
                    return
                try:
                    pitch = pcm.command(command)
                except (ValueError, KeyError, ZeroDivisionError) as exc:
                    print(str(exc), file=sys.stderr, flush=True)
                    continue
                if pitch is not None:
                    immediate.append(pitch)
                else:
                    print(f"beat {pcm.beat}: {pcm.station.audience(pcm.beat)}",
                          file=sys.stderr, flush=True)
            sys.stdout.buffer.write(pcm.render(immediate))
            sys.stdout.buffer.flush()
    except (BrokenPipeError, KeyboardInterrupt):
        return


if __name__ == "__main__":
    main()
