# Terminal PCM audition adapter

Requires Python 3.10+; optional FFmpeg `ffplay` for listening. From this directory:

    python -m unittest -v
    python live.py | ffplay -nodisp -loglevel error -f s16le -ar 16000 -ac 1 -

Type commands in the terminal running the pipeline:

- `hit 64`: introduce an immediate MIDI-pitch event.
- `period a 5/2`: retime track a in beats without changing its geometry. A corresponding audience-state snapshot is printed to standard error.
- `quit`: exit.

The bridge generates raw PCM on stdout and uses emitted sample count as its clock; command edits are applied at the next rendered block. A downstream player buffers audio, so the live listening path can lag the edit and is not a production audio callback. Redirecting the stream to a file produces audio faster than real time. The event renderer and terminal/PCM command path were tested separately from the hardware sink. No physical audio device, AR, tracking, latency or audience comprehension verified. Local DSP/Link integration remains future work. AI assistance: OpenAI authored and tested this experimental adapter and its tests, 2026-11-18.
