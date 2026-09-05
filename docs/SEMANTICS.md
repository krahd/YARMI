# Minimal YARMI semantics — current first-iteration boundary

This document deliberately avoids defining a universal musical ontology. The first station has its own musical model; only distinctions that must survive across station/timing/integration boundaries belong here.

## Ensemble

For the first implementation it is sufficient to reason about an ensemble as:

```text
E = (S, X, τ)
```

where:

- `S` is the set of logical YARMI station identities participating in the current ensemble;
- `X` is the collection of station-local states needed by the current implementation, without requiring one universal entity schema;
- `τ` is shared musical time supplied initially by Ableton Link.

There is no authority-policy component in the first implementation.

## Station

Station is a first-class YARMI concept.

```text
Station = StationId + station-local musical/interaction state
```

A station is an independently playable **augmented** musical locus. Its logical identity must not encode:

- one device/process;
- one performer;
- one sensing technology;
- one rendering technology;
- one audio backend or ownership of sound generation;
- leader/follower role;
- tracks, grids or a specific component vocabulary.

A logical station may span several devices/processes.

Audience-visible rendering is constitutive of a complete YARMI station, although the rendering representation itself remains station-specific.

## Station-local musical state

Do not introduce a universal `Entity`/`Action` framework merely for architectural neatness.

The first revised-original station may define station-local concepts such as:

- Track;
- track period;
- sound/event component;
- local effect;
- immediate component/effect;
- station/global control;
- Manipulator;
- Binding.

Promote a concept into shared YARMI semantics only when several station types or a real network/integration boundary demonstrate the need.

## Manipulator

A Manipulator is a performer-controlled source bound to one or more manipulable station elements/parameters.

The semantic relation is independent of sensing modality:

```text
source -> observed channel -> binding -> parameter
```

Rotation is only one channel. Runtime-selected arbitrary physical objects can become manipulators without semantic category recognition. The sensing implementation must expose only channels that are sufficiently observable/reliable.

See `MANIPULATORS.md`.

## Musical time

The first shared time source is Ableton Link.

YARMI consumes shared/absolute beat/tempo information and each station derives its own periods/phases locally. A track may therefore have a period unrelated to a fixed four-beat Link quantum.

Network packet arrival and UI display-frame time are not musical time. Musical events must be scheduled against the audio/shared musical timeline.

## Augmentation and views

Sensing/rendering technology is not part of the musical semantics, but augmentation is part of what makes a station YARMI.

A station may have:

```text
station state
   +--> performer rendering
   +--> audience rendering
```

The two renderings may be the same. The audience rendering must expose the consequential action/state/music relationship sufficiently for performance legibility.

## Audio/output boundary

Station musical state does not know whether sound is produced by:

- embedded libpd;
- native C++/JUCE DSP;
- a VST/AU/other plugin hosted anywhere;
- MIDI hardware;
- another external process/system.

Adapters translate the station/component's musical/control output into the endpoint's interface. Plugin-host identity is not musical semantics.

## Networking

No general YARMI state protocol is required while stations only share Link time.

When a concrete musical interaction requires semantic exchange, promote only the necessary shared identities/state/actions and specify their timing/failure behaviour. Keep that semantic contract independent of wire transport; OSC may encode it.

## Authority

Authority is deliberately absent from first-iteration semantics. If musical use later requires it, model it as a relation/policy over coordination domains rather than an intrinsic station type. The architecture must remain compatible with leaderless, fixed/dynamic/multiple/hierarchical/domain-specific/subensemble arrangements.

## First station

The canonical first station is specified by `FIRST-STATION.md`. Its tracks, effects and immediate components are station-local semantics, not claims that every future YARMI station must use those concepts.
