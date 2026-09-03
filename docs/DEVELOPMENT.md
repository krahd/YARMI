# YARMI development plan

Status: current working plan as of 2026-09-03.

This document is written so work can continue directly from Codex, Claude Code or another development environment without reconstructing the design discussion from chat history.

## Governing method

YARMI is not developed by completing a speculative architecture and then implementing it. The architecture and instrument co-evolve.

```text
implement -> play -> observe -> revise -> play again
```

Early evaluation is primarily musical and performative. Tomas Laurenzo is the principal initial performer/designer. Repeated first-person use is sufficient evidence to change the implementation or architecture. Formal user research can come later if a research question requires it.

Do not implement an abstraction merely because a future distributed instrument could need it.

## Current first-iteration decisions

The first portable/playable implementation uses:

- **JUCE** as native cross-platform application/audio/MIDI host;
- **libpd** as the first embedded DSP backend behind a replaceable interface;
- **Ableton Link** for 100% of ensemble tempo/beat/phase synchronisation;
- **JUCE VST3 hosting** as the first desktop third-party-plugin integration path;
- no dependency on Ableton Live;
- no dependency on standalone Pd;
- no YARMI authority/leader-management subsystem;
- no custom clock/synchronisation system;
- no requirement for a general network control protocol until a musical interaction needs one;
- no fixed physical interface in the semantic core.

Required native platform horizon:

- iPhone/iPad;
- Android;
- macOS;
- Windows;
- Linux.

## Current implementation checkpoint

Steps 1–5 below are implemented in the first portable station. The shared JUCE target now has a
touch/mouse step instrument, an embedded libpd backend, Link/LinkKit timing, real-time diagnostics,
and pinned CMake builds for macOS and iPadOS. It has been runtime-smoke-tested on macOS and iPad
Simulator, including non-silent embedded-DSP output tests and two local processes discovering one
another as Link peers.

The next evidence gate is still physical and musical: run a signed build on an iPad, then complete
Steps 6–7 with at least two independent Link peers and record the first playing notes under
`docs/playability/`. VST3 hosting remains Step 8; do not add it before that playing pass.

## Existing disposable proof

`apps/ios-proof/` is an Apple-native SwiftUI + RealityKit/ARKit existence proof. It is not the portable architecture.

Before discarding or superseding it:

1. run it on a physical iPhone/iPad;
2. confirm AR placement, cursor movement and audible triggering;
3. fix only defects necessary to validate that narrow proof;
4. record findings;
5. do not grow it opportunistically into the portable runtime.

## Immediate implementation sequence

### Step 1 — Establish portable JUCE skeleton

Create the smallest JUCE/CMake application structure that can become the common host for desktop/mobile builds.

Initial success condition:

- application starts;
- audio device opens;
- audio callback runs cleanly;
- basic MIDI/device information can be inspected;
- core code is not coupled to UI manifestation code.

Do not design a complete domain model first.

### Step 2 — Define the minimum audio boundary

Create an `AudioBackend` interface with only the methods required by the first playable patch/instrument.

Implement `LibPdBackend` first.

Responsibilities:

- initialise/close libpd;
- adapt JUCE callback block sizes to Pd's processing quantum;
- move control/events into the audio backend without blocking the real-time thread;
- report basic health information;
- avoid making Pd responsible for station/ensemble state.

Native JUCE/C++ DSP is a future backend, not parallel v0 implementation work unless libpd immediately fails a requirement.

### Step 3 — Instrument real-time behaviour from the beginning

Capture enough diagnostics to detect whether the architecture is musically viable:

- sample rate;
- device buffer size;
- reported input/output latency where available;
- callback/xrun/underrun information where available;
- maximum/average callback load if practical;
- Link timing observations;
- obvious scheduling jitter or drift symptoms.

Do not optimise before measurement, but do not postpone observability until after problems appear.

### Step 4 — Add Ableton Link as the complete v0 timing service

Expose the minimum timing information needed by the first instrument.

Do not implement:

- leader clock;
- custom synchronisation;
- authority over tempo;
- election;
- consensus.

Stations use Link as peers.

### Step 5 — Make one station musically playable

Build the smallest interaction that permits sustained playing rather than only technical testing.

The physical/UI manifestation is intentionally open. A simple temporary touch/desktop interface is acceptable if it gets to musical use faster. The existing AR proof may inform a manifestation but does not define the interaction grammar.

Do not assume historical YARMI tracks, zones, tokens or mappings.

### Step 6 — Run two or more independent stations

Run YARMI on at least two independent processes/devices sharing Link time.

First multi-station success criteria:

- stations join/leave without a central YARMI leader;
- beat/phase relationship is musically stable enough to play;
- each station remains independently playable;
- temporary loss/rejoin does not require rebuilding the whole ensemble;
- no custom authority subsystem is involved.

This test does **not** require YARMI semantic state replication yet.

### Step 7 — Play, repeatedly

Use the instrument in real musical sessions rather than only automated tests.

Keep concise observations under `docs/playability/` (create when first used), recording:

- what was attempted;
- what felt musically useful;
- what obstructed playing;
- what unexpected possibilities appeared;
- whether the issue is semantic, interactional, DSP, timing, networking or physical manifestation;
- the smallest architectural change suggested by the observation.

Avoid converting the diary into a formal user-study apparatus.

### Step 8 — Add JUCE VST3 hosting on desktop

Once the local audio/timing loop is stable enough to play, add a minimal plugin-host path so a station can use third-party VST3 instruments/effects.

Requirements:

- hosted plugin identity does not become a YARMI core concept;
- plugin instantiation is local to the station;
- failures remain local where possible;
- YARMI runs without any hosted plugin;
- Ableton Live is unnecessary.

Evaluate AU/AUv3/LV2/CLAP later according to actual platform/use needs.

### Step 9 — Introduce semantic networking only when a piece needs it

If a musical idea requires station A to affect station B beyond sharing Link time, define the smallest required state/action exchange then.

Do not start by implementing a universal YARMI protocol.

The first requirement may be extremely small, for example:

- create/remove one shared musical entity;
- share a parameter;
- address another station;
- form a temporary subensemble;
- exchange an event scheduled at a future Link beat.

From that behaviour, derive the protocol requirements.

### Step 10 — Expand platform coverage continuously

The architectural target is native iOS/iPadOS, Android, macOS, Windows and Linux.

Do not postpone all non-macOS work until the end. Once the JUCE/libpd/Link skeleton is stable, establish compile/smoke-test coverage across the target families so platform assumptions are discovered early.

## Decision gates

### Does Link remain sufficient?

Stay with Link unless playing demonstrates a concrete limitation. Possible evidence for change:

- required authority over tempo/phase;
- coordination behaviour Link cannot express;
- unacceptable recovery/rejoin behaviour;
- multiple simultaneous timing domains;
- measured timing/playability problems not solvable locally.

If none appears, do not invent a custom synchronisation layer.

### Do we need authority semantics?

Do not implement authority because the original YARMI had a leader station or because distributed-systems theory suggests it.

Implement it only if a musical situation repeatedly requires some stations to control or constrain others.

If needed, preserve topology agnosticism. Candidate future configurations include no leader, one fixed leader, dynamic leader assignment, several leaders, domain-specific leaders, hierarchical leaders/subleaders and subensemble authority.

### Does libpd remain the right audio backend?

Stay with libpd while it supports the desired instrument with acceptable:

- latency;
- stability;
- real-time behaviour;
- dynamic musical structure;
- portability;
- maintainability.

Move specific DSP to native JUCE/C++ only when there is a concrete gain.

### Do we need a YARMI network protocol?

Only when Link-only independent stations are insufficient musically.

Derive protocol semantics from the first real shared interaction. OSC remains a likely interoperability option, not a predetermined canonical transport.

### Which physical manifestation becomes primary?

Open. Current ideas include:

- spatial AR YARMI: virtual musical nodes/entities placed in 3D space;
- object YARMI: arbitrary physical objects become instantiated musical entities/stations and are computationally/visually overwritten or augmented;
- a combined object-plus-spatial manifestation;
- touch/conventional mobile/desktop manifestations;
- hands/body tracking;
- projectors;
- AR glasses;
- VR/XR;
- tactile/haptic configurations;
- marker-based interaction if it proves musically useful again.

No physical modality has architectural privilege.

## Large-schema plan / design horizon

The following possibilities must remain documented so early implementation does not accidentally rule them out. They are **not current implementation requirements**.

### Ensemble topology

Potential future support:

- peers with no leader;
- one fixed leader;
- elected/dynamic leader;
- multiple simultaneous leaders;
- authority scoped to different musical/control domains;
- hierarchical leaders/subleaders;
- temporary local/subensemble leaders;
- heterogeneous station roles.

### Timing

Potential future timing backends:

- Ableton Link (v0 and current default);
- DAW clock;
- custom YARMI clock;
- multiple clock domains;
- topology-dependent or deliberately drifting time if artistically useful.

### Shared state/networking

Potential future needs:

- station discovery;
- ad-hoc membership;
- shared entities;
- snapshots/deltas;
- capability negotiation;
- ordering/idempotence/replay;
- scheduled future events;
- persistence/session recovery;
- several transports;
- local and remote ensembles;
- conflict semantics.

### Audio/integration

Potential future components:

- native JUCE/C++ DSP;
- multiple simultaneous DSP backends;
- VST3/AU/AUv3/LV2/CLAP hosting;
- YARMI as a plugin;
- MIDI/OSC hardware/software;
- DAWs as optional stations/adapters;
- external hardware instruments.

### Manifestation

Potential future manifestations may use any combination of:

- screens/touch;
- fiducials;
- arbitrary objects;
- computer vision;
- hands/body;
- projection;
- spatial AR;
- phones/tablets;
- AR glasses;
- VR/XR;
- tangible/haptic systems;
- non-spatial controllers.

The semantic core should not force one manifestation's ontology onto another.

## Historical YARMI recovery

If/when the original codebase is found:

1. archive it separately from the new implementation;
2. document build/runtime assumptions if recoverable;
3. inspect Pd patches, networking, station semantics, mappings and UI only as historical evidence;
4. classify observations as `historical-observation`, `candidate`, or `rejected`;
5. import nothing automatically;
6. never allow historical student implementation choices to become requirements by inertia.

The recovered code is archaeological material, not a base branch for YARMI 2.0.

## Definition of progress

Progress is not measured by how much of the large-schema plan exists in code.

The project is progressing when:

- the instrument becomes more playable;
- more interesting musical behaviour becomes possible;
- latency/timing/reliability remain acceptable;
- new manifestations can be attempted without rewriting unrelated layers;
- architecture becomes simpler or more precise in response to actual use;
- technical decisions remain reversible where there is genuine uncertainty.
