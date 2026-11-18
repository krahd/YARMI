# Revised-original station: headless timing slice

Run from this directory with Python 3.10 or later (no packages required):

    python -m unittest -v
    python station.py station-out

The demonstration renders a six-second WAV, exact beat/event trace and an SVG snapshot of both cursors. It uses two freely arranged tracks with different musical periods; time is injected, not derived from screen frames. The WAV is rendered offline, not by an audio callback. Period edits affect future queries of the returned immutable state; a live adapter must choose their effective beat and swap snapshots there. This is a development reference, not the canonical real-hardware milestone or a claim of measured performance or audience understanding.

Not included: AR/device verification, immediate interaction, track effects, live output, markerless tracking, shared Link clock or dedicated audience display.

AI assistance record (2026-11-18): OpenAI coding assistant authored this prototype and unit tests and executed verification. Retain this provenance when describing implementation; the author should verify and disclose relevant use when required.