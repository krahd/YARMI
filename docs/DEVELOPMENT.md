# YARMI development plan

Status: current handoff after the September 2026 architecture/playability audit.

## Governing method

```text
implement -> play -> observe -> revise -> play again
```

The architecture and instrument co-evolve. Do not implement an abstraction merely because a generic distributed musical framework might need it.

## Immediate implementation sequence

### 0 — Read the controlling design documents

Before code changes, follow `AGENTS.md`. In particular, `DECISIONS.md`, `FIRST-STATION.md`, `PLAYABILITY.md` and `MANIPULATORS.md` control the implementation direction.

### 1 — Preserve, do not merge, the existing Codex prototype

`codex/playable-prototype-v0` is a technology spike. Do not merge it wholesale.

Use `PROTOTYPE-V0-AUDIT.md` to port only infrastructure that survives the architecture audit: CMake/JUCE setup, Link adapters, libpd lifecycle/quantum handling, diagnostics, CI/tests.

### 2 — Device-validate the existing tiny AR proof

Run `apps/ios-proof/` on a real iPhone/iPad. Confirm AR placement, cursor motion and audible triggering. Fix only proof-blocking defects.

This validates the narrow AR path; it is not the canonical station implementation and its display-frame musical scheduling must not be retained.

### 3 — Establish the revised-original station model

Implement the smallest station-local model required by `FIRST-STATION.md` rather than a universal musical ontology.

Initial concerns include:

- track geometry;
- track period;
- temporal position of sound/event components;
- local effects;
- immediate components/effects;
- station/global controls;
- Manipulator bindings;
- performer/audience render state.

Keep the station model independent of one rendering/sensing framework and one audio endpoint.

### 4 — Establish generic output boundaries

Port/refactor the useful libpd work from the prototype without preserving lane/cutoff-specific interfaces.

The station/component must be able to drive:

- embedded libpd first;
- later native DSP;
- an external VST/plugin host;
- MIDI/hardware/other endpoints.

YARMI semantics must not care where a VST is hosted.

Instrument sample rate, buffer size, latency/xrun/callback load and scheduling behaviour from the beginning.

### 5 — Build the first augmented station rendering

Use the shortest credible path on iPhone/iPad first, likely native ARKit/RealityKit where useful. JUCE may provide portable audio/MIDI/process services without becoming the required AR UI framework.

Implement:

- arbitrary-position/orientation line-segment tracks;
- visible current-time cursor;
- sound/event placement;
- station state renderable to performer view and public/audience view.

The first audience view may be a mirrored/external display if that is the quickest legible implementation; preserve the ability to render it independently later.

### 6 — Implement Manipulator v0

First target:

1. performer taps/selects one suitable arbitrary rigid visible object;
2. acquire a region/mask;
3. track visual features frame-to-frame;
4. expose translation/scale/in-plane rotation when reliable;
5. use depth for world position where available;
6. report channel suitability/tracking confidence;
7. bind a supported channel to any manipulable first-station parameter;
8. visibly degrade/lose the binding rather than silently output incorrect control.

Semantic category recognition is not required. Prefer lightweight tracking after acquisition; promptable segmentation may be used to initialise/correct the object mask.

### 7 — Complete the first station's sequence/direct-manipulation grammar

Add enough behaviour to test the playability contract:

- explicit track periods independent of geometric length;
- default track-start manipulation of period/bars;
- direct manipulation of sound/event primary parameters;
- one track-local effect;
- one immediate musical interaction;
- one station/global control;
- an additional Manipulator assigned to another parameter.

Do not reproduce historical mappings if they are not musically useful.

### 8 — Integrate Ableton Link correctly

Link supplies shared tempo/beat time. Each track derives its own phase/period locally from shared/absolute musical time.

Do not bake a fixed four-beat quantum into station semantics. Do not implement leader clock, election, consensus or authority.

### 9 — Play the station repeatedly

Create `docs/playability/` when real playing begins. Record concise observations about musical usefulness, friction, unexpected possibilities, tracking, audience legibility, DSP and timing. Change architecture only when an observation or concrete portability/reliability need warrants it.

### 10 — Prove host-agnostic external sound control

Once the local station is playable, route one station/component to an external VST synthesiser or effect through a suitable adapter. The test passes if musical behaviour remains the same regardless of whether that VST is hosted by YARMI, Ableton, Reaper, Bitwig or another host.

Do not build a general plugin host merely to satisfy this test.

### 11 — Run two or more stations

Run at least two independent stations/devices sharing Link time.

Success criteria:

- each station remains independently playable;
- join/leave is musically tolerable;
- timing is stable enough to perform;
- no YARMI authority subsystem is required;
- audience-visible state remains intelligible.

This does not require YARMI semantic replication yet.

### 12 — Introduce semantic networking only when needed

When a concrete piece/interaction needs station-to-station semantic control/state beyond Link, define the smallest transport-independent semantics for that behaviour and then choose a transport. OSC remains a likely adapter, not the protocol definition.

### 13 — Revisit the grid as a component only if useful

The Codex 4×16 sequencer may become a `GridSequencer` station component. If revived, give it YARMI-style augmentation/manipulation rather than reinstating it as core.

### 14 — Expand platform coverage continuously

The target remains iPhone/iPad, Android, macOS, Windows and Linux. Establish compile/smoke-test coverage early enough to expose platform assumptions, but do not block the first playable AR station on simultaneous full-platform feature parity.

## Decision gates

### Link

Keep Link unless playing demonstrates a concrete problem it cannot solve.

### Authority

Do not implement authority because historical YARMI had a leader or because distributed-systems theory suggests it. Preserve the future possibility of leaderless, fixed, dynamic, multiple, hierarchical, domain-specific and subensemble authority.

### libpd

Keep libpd while latency, stability, dynamic structure, portability and maintainability are acceptable. Move DSP only for a concrete gain.

### Manipulator tracking

Do not promise universal arbitrary-object 6-DoF. Start with runtime acquisition plus reliable observable channels. Add depth, reacquisition or object-centric 6-DoF only when a musical use requires them.

### First station scope

Do not add curves, universal component schemas, complex routing, persistent sessions, shared-state replication or a component marketplace before the first revised-original station is genuinely playable.

## Definition of progress

Progress means:

- the station becomes more playable;
- performer action and musical consequence become more legible to the audience;
- arbitrary objects can become useful manipulators without fiducials;
- the architecture remains understandable and replaceable at genuinely volatile boundaries;
- timing/latency/reliability are good enough for performance;
- external sound generation can be swapped without changing station musical semantics;
- multiple stations can join an ensemble without forcing premature distributed-system machinery.
