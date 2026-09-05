# `codex/playable-prototype-v0` audit and reuse boundary

## Status

Branch: `codex/playable-prototype-v0`  
Prototype commit audited: `0daf7a19c6c088cc425f7cc1bd2b198d2ca4e5c5`

**Decision: do not merge this branch wholesale into `main`.** It is a useful technology spike whose infrastructure may be ported selectively.

## What it proved

The branch demonstrated useful implementation work around:

- JUCE/CMake application scaffolding;
- embedded libpd lifecycle/audio rendering;
- Ableton Link integration on desktop/iOS;
- realtime/audio diagnostics;
- macOS tests and iOS-simulator build infrastructure;
- a playable touch/mouse 4×16 sequencer prototype.

These are evidence that the chosen technologies can work together. They are not the canonical YARMI station design.

## Architectural drift found

### Grid-specific musical model under `Core`

`Pattern` hard-codes four lanes, sixteen steps, transposition, cutoff and random `evolve()` behaviour. `Sequencer` hard-codes lane pitches/velocities and sixteenth-note scheduling.

These are properties of one potential component, not YARMI core.

### Audio boundary contaminated by component semantics

`AudioBackend` imports the sequencer's `TriggerEvent`, including lane identity, and exposes `setCutoff()`. `LibPdBackend` consequently routes four specific lanes/voices and knows a YARMI-specific cutoff control.

A future audio/output endpoint must receive generic musical/control information appropriate to the station/component and remain usable whether the endpoint is libpd, native DSP, a VST hosted elsewhere, MIDI hardware or another system.

### UI owns too much

`MainComponent` combines grid editing, pattern state, sequencing, Link control, audio lifecycle, diagnostics and presentation. Useful code can be extracted, but this shape should not become the architecture of an augmented station.

### Fixed Link quantum

The prototype queries Link beat/phase with a fixed four-beat quantum. The canonical design now requires shared/absolute musical time from which each station/track derives its own period/phase; polymetric/arbitrary track periods must not be constrained by a four-beat UI assumption.

### Prototype grid is musically narrower than YARMI's playability contract

The grid mostly provides sequenced state editing. It lacks the immediate/direct-manipulation side of the original YARMI proposition and makes several important controls conventional GUI sliders/buttons.

## Selective reuse plan

Safe candidates to port/refactor:

- CMake/JUCE dependency setup;
- libpd initialisation and Pd-quantum adaptation, after replacing the semantic interface;
- Link platform adapters, after exposing suitable shared/absolute time rather than one grid quantum;
- audio diagnostics;
- CI/build scripts and tests where their assumptions remain valid.

Do not port as generic core:

- `Pattern`;
- `Sequencer`;
- four lanes/pitches/velocities;
- `setCutoff()` on the backend interface;
- `EVOLVE` as a YARMI-wide operation;
- the 4×16 grid UI.

The grid may later be reintroduced as a **GridSequencer station component** with YARMI-style Manipulator bindings.

## Additional technical caveats

- The libpd event adapter currently advances events to Pd processing quanta; its timing error must be measured/described intentionally rather than assumed sample-exact.
- The prototype CI validates macOS and iOS simulator only; it does not establish Android, Windows or Linux portability.
- Third-party licensing for JUCE/Link/libpd must be reviewed before public binary distribution.

## Preservation rule

Keep the branch intact as historical/engineering evidence. Future agents should not delete it, merge it wholesale, or describe it as the canonical first YARMI 2 station.
