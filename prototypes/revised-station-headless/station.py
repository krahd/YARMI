"""Headless revised-original station slice; clock and audio are external."""
from dataclasses import dataclass, replace
from fractions import Fraction as F


@dataclass(frozen=True)
class Event:
    phase: F
    pitch: int

    def __post_init__(self):
        if not 0 <= self.phase < 1 or not 0 <= self.pitch <= 127:
            raise ValueError("invalid event phase or MIDI pitch")


@dataclass(frozen=True)
class Track:
    name: str
    start: tuple
    end: tuple
    period: F
    events: tuple

    def __post_init__(self):
        if self.period <= 0:
            raise ValueError("period must be positive")

    def cursor(self, beat):
        phase = (F(beat) % self.period) / self.period
        return tuple(a + (b - a) * phase for a, b in zip(self.start, self.end))

    def window(self, begin, end):
        """Half-open absolute beat window, independent of display frames."""
        for event in self.events:
            offset = event.phase * self.period
            cycle = (begin - offset) // self.period
            beat = cycle * self.period + offset
            if beat < begin:
                beat += self.period
            while beat < end:
                yield beat, self.name, event.pitch
                beat += self.period


@dataclass(frozen=True)
class Station:
    tracks: tuple

    def __post_init__(self):
        if len({t.name for t in self.tracks}) != len(self.tracks):
            raise ValueError("duplicate track names")

    def schedule(self, begin, end):
        begin, end = F(begin), F(end)
        if end < begin:
            raise ValueError("reversed window")
        return tuple(sorted(e for t in self.tracks for e in t.window(begin, end)))

    def set_period(self, track, beats):
        """Adapter-facing binding target; sensing and tracking stay outside."""
        if not any(t.name == track for t in self.tracks):
            raise KeyError(track)
        return Station(tuple(replace(t, period=F(beats)) if t.name == track else t
                             for t in self.tracks))

    def audience(self, beat):
        return tuple((t.name, t.start, t.end, t.period, t.cursor(beat))
                     for t in self.tracks)


def demo():
    import math
    import struct
    import wave
    from pathlib import Path
    from sys import argv
    out = Path(argv[1]) if len(argv) == 2 else Path("station-out")
    out.mkdir(parents=True, exist_ok=True)
    station = Station((
        Track("a", (10, 10), (100, 70), F(3), (Event(F(0), 52), Event(F(1, 3), 59))),
        Track("b", (100, 10), (10, 40), F(5, 2), (Event(F(1, 2), 67),)),
    ))
    events = station.schedule(0, 12)
    rate = 16000
    pcm = [0.0] * (rate * 6)
    for beat, _, pitch in events:
        onset = round(beat * rate / 2)
        for i in range(min(1800, len(pcm) - onset)):
            pcm[onset + i] += 0.17 * math.sin(2 * math.pi * 440 * 2 ** ((pitch - 69) / 12) * i / rate) * (1 - i / 1800)
    with wave.open(str(out / "station.wav"), "wb") as file:
        file.setparams((1, 2, rate, 0, "NONE", "not compressed"))
        file.writeframes(b"".join(struct.pack("<h", round(max(-1, min(1, v)) * 32767)) for v in pcm))
    (out / "events.tsv").write_text("beat\ttrack\tpitch\n" + "".join(
        f"{beat}\t{track}\t{pitch}\n" for beat, track, pitch in events))
    shapes = []
    for name, a, b, period, cursor in station.audience(F(7, 4)):
        x, y = map(float, cursor)
        shapes.extend((f'<line x1="{a[0]}" y1="{a[1]}" x2="{b[0]}" y2="{b[1]}" stroke="black"/>',
                       f'<circle cx="{x}" cy="{y}" r="2" fill="red"/>',
                       f'<text x="{a[0]}" y="{a[1]+8}" font-size="5">{name}: {period} beats</text>'))
    (out / "audience.svg").write_text('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 120 85">' +
                                     "".join(shapes) + '</svg>\n')


if __name__ == "__main__":
    demo()
