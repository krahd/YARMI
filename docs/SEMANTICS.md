# Minimal YARMI semantics — v0.0.1

This is intentionally the smallest formal model that can support a real YARMI manifestation without committing the project to a physical interface, network transport, audio engine, DAW, sequencer model, or leadership topology.

## State

At any instant an ensemble is:

```text
E = (S, X, P, τ)
```

where:

- `S` is a finite set of **stations**;
- `X` is a finite map from stable entity identifiers to **entity state**;
- `P` is a finite map from authority domains to **authority policies**;
- `τ` is optional **musical time**.

Nothing else is required by the core.

## Station

A station has only stable identity at the semantic level:

```text
Station = StationId
```

Capabilities, device type, performer, location, screen, audio hardware, DAW host, physical object, and leadership role are optional metadata/adapters and are not part of station identity.

## Entity

An entity is a durable thing the ensemble can refer to and change:

```text
Entity = (EntityId, kind, state)
```

`kind` and `state` are extensible. The core does not prescribe tracks, notes, samples, effects, spatial nodes, physical objects, or graphics.

A manifestation may introduce entity kinds such as `track`, `event`, `sample`, `effect`, `spatial-node`, or `daw-parameter`, but those are application vocabulary rather than YARMI primitives.

## Action

All semantic change is represented as an action:

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

The minimum operations are:

```text
create
update
delete
```

Domain-specific operations may later be added only where they have semantics that cannot be expressed coherently as state mutation.

Applying an action is a state transition:

```text
δ(E, a) → E' | rejected
```

The same reducer semantics must apply whether the action came from touch, OSC, AR, a DAW, a hand tracker, another station, replayed history, or a test.

## Authority

Authority is not a station property. For each named domain `d`, an authority policy is a predicate over proposed actions:

```text
P[d](E, a) → allow | reject
```

An absent policy means the domain is unrestricted by YARMI authority semantics.

This representation can express, without changing `Station`:

- no leader;
- one fixed leader;
- dynamically selected leader;
- several leaders;
- domain-specific leaders;
- hierarchical/subleader configurations;
- consensus or other policies.

Only the policies actually needed by a manifestation need to be implemented.

## Musical time

`τ` is optional. A YARMI ensemble does not require shared musical time.

When present, musical time is represented independently of transport and authority. The minimum useful representation is:

```text
MusicalTime = (cycle, phase)
phase ∈ [0, 1)
```

A timing adapter may derive this from Ableton Link, a DAW, an internal clock, MIDI clock, or another source.

## Manifestations

A manifestation has two conceptual mappings:

```text
input / sensing → Action
E → presentation / sound / haptics / external control
```

Therefore markers, arbitrary objects, hands, touch, projectors, AR goggles, VR, tactile interfaces and DAWs can all manifest the same semantic ensemble without entering the core ontology.

## Transport

The semantic protocol transports actions and state; it is not defined by a wire format.

```text
encode_transport(Action | State) ↔ semantic object
```

OSC is one candidate encoding. An in-process call is another. Neither changes `δ`.

## First proof manifestation

The initial iOS/iPadOS AR proof deliberately defines three manifestation-level entity kinds:

```text
track(start, end)
sample(position-on-track, frequency)
cursor(phase)
```

The first two taps place the track boundaries. Subsequent taps create sample entities projected onto the track. A local musical clock advances a cursor from `phase = 0` to `phase → 1`; crossing a sample position triggers its sound.

This reproduces the smallest recognisable historical YARMI behaviour while importing none of the old token ontology, zones, fixed leader semantics, client/server architecture, Pd organisation, or track-length rules.

## Non-goals of v0.0.1

- distributed networking;
- OSC;
- Ableton Link;
- libpd;
- VST/AU hosting or bridging;
- multi-station authority;
- persistence;
- conflict-free replicated state;
- general capability negotiation;
- arbitrary-object recognition;
- Android client;
- production-quality synthesis.

Those remain compatible with the model but are deliberately outside the first existence proof.
