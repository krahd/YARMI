# Minimal YARMI semantics — provisional v0

This is an intentionally small working vocabulary for the first portable/playable YARMI iteration. It is **not a frozen ontology**. Musical use may change it.

The purpose of the semantic core is to keep physical manifestation, DSP implementation and timing infrastructure separable without prematurely designing a universal distributed-music model.

## Current state model

For the first implementation, it is sufficient to reason about an ensemble as:

```text
E = (S, X, τ)
```

where:

- `S` is the set of stations known/required by the current manifestation;
- `X` is musical/entity state used by that manifestation;
- `τ` is shared musical time, supplied in v0 by Ableton Link.

`S` and `X` should remain deliberately weakly specified until playing the instrument reveals which distinctions need to be durable.

There is **no authority-policy component in v0**.

## Station

At the semantic level, a station has stable identity and whatever local musical state the current manifestation requires.

```text
Station = StationId
```

Station identity must not intrinsically encode:

- device type;
- performer;
- location;
- screen/table/object;
- leader/follower role;
- audio backend;
- physicality;
- spatial coordinates;
- interaction modality.

For the first Link-based iteration, stations are peers. YARMI does not add a separate authority model unless musical use demonstrates a need.

## Entity vocabulary

An entity is something a manifestation needs to refer to durably:

```text
Entity = (EntityId, kind, state)
```

`kind` and `state` are extensible and provisional. The core does not prescribe tracks, notes, samples, effects, spatial nodes, physical objects, clips, voices or graphics.

A manifestation may use such concepts, but they must earn promotion into reusable YARMI semantics through repeated musical need rather than historical precedent.

## Actions

Semantic changes may be represented as actions:

```text
Action = (
    ActionId,
    actor: StationId,
    operation,
    target?,
    payload?,
    musicalTime?
)
```

A useful initial operation vocabulary is simply:

```text
create
update
delete
```

Do not add domain-specific operations until they clarify a real musical interaction.

The important architectural property is that a manifestation can map physical interaction into actions/state without the core knowing whether the source was touch, AR, object tracking, MIDI, VR, haptics or another modality.

## Musical time

In v0, shared musical time comes from **Ableton Link**.

The semantic layer should consume musical timing in a form appropriate for scheduling without treating network packet arrival as musical time. Each station renders against its own local audio clock and maps Link timing to local scheduling.

The exact representation is an implementation detail until a real use case requires a richer semantic time object. Beat/phase/tempo information should not be generalised into a custom clock architecture prematurely.

## Physical manifestations

A manifestation conceptually maps:

```text
input / sensing -> provisional musical action/state
YARMI state/time -> sound / image / spatial augmentation / haptics / external control
```

Markers, arbitrary objects, hands, touch, projectors, AR goggles, VR, tactile interfaces and conventional screens can therefore produce different YARMI manifestations without entering the core ontology.

Spatial metadata is optional. Non-spatial interfaces remain first-class.

## Audio boundary

The semantic layer does not know whether audio is produced by Pd, native C++ DSP, a hosted VST3 instrument, external MIDI hardware or something else.

For v0:

- JUCE owns the process and audio-device callback;
- libpd is the first `AudioBackend`;
- Pd patches receive musical information and render/process sound;
- Pd does not own ensemble semantics.

## Control/state networking

The first playable iteration does not require a general YARMI network protocol merely to justify the architecture. Multiple stations may initially share only Link timing while remaining musically independent.

When a concrete musical interaction requires station-to-station semantic exchange, define only the state/actions and network behaviour needed by that interaction.

## Authority — deferred extension, not v0 semantics

The architecture should not make future authority impossible, but v0 does not model it.

If playing reveals a need for restricted or structured control, a later extension may introduce authority policies over specific domains. Candidate configurations include no leader, fixed leader, dynamic leader, multiple leaders, hierarchical/subleaders and subensemble-specific authority.

Those possibilities are preserved in `ARCHITECTURE.md` and `DECISIONS.md` as a large-schema design envelope. They are not part of current minimal semantics.

## Existing iOS/iPadOS AR proof

`apps/ios-proof/` is a disposable existence proof, not the semantic specification. It currently uses manifestation-level concepts:

```text
track(start, end)
sample(position-on-track, frequency)
cursor(phase)
```

The first two taps place track boundaries, later taps place sample entities, and a moving cursor triggers them. This is intentionally a tiny historical echo used to prove that a contemporary manifestation can exist; it does not establish tracks, samples or this interaction grammar as YARMI 2.0 semantics.

## v0 non-goals

Until playability demands otherwise, do not implement:

- authority/leader management;
- custom distributed clocks;
- consensus;
- replicated-state machinery;
- general persistence;
- universal capability negotiation;
- elaborate discovery;
- a general spatial ontology;
- historical YARMI zones/mappings/track rules.

Cross-platform support, Link timing, JUCE hosting and libpd audio are current implementation work; the items above are not.
