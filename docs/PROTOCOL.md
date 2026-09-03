# YARMI protocol — design basis

Status: architecture design, not yet a frozen wire specification.

## Principle

The **YARMI protocol is not OSC**. It is a versioned semantic contract describing YARMI entities, events, commands, state transitions, timing information and authority relations.

OSC is expected to be a first-class interoperability mapping because of its broad use in computer music. The core protocol must remain serialisable over other transports without changing YARMI semantics.

## Why not define YARMI directly as OSC?

OSC is an excellent message representation/interoperability mechanism, but YARMI needs additional guarantees and semantics that should be stated independently:

- stable entity identity;
- schema/version negotiation;
- message/event identity;
- causal or revision relationships where needed;
- ordering requirements per message class;
- idempotence/replay behaviour;
- station/ensemble membership semantics;
- authority grants, scopes, leases and revocation;
- state snapshots and incremental changes;
- capability discovery;
- conflict behaviour for multiple authorities;
- timing intent distinct from packet arrival time;
- transport-specific reliability policy.

An OSC adapter can encode these concepts through address patterns and arguments, but the OSC representation must be derived from the canonical semantic schema.

## Initial conceptual entities

These names are provisional and will be tested before implementation:

- `EnsembleId`
- `StationId`
- `EntityId`
- `ActionId`
- `AuthorityDomain`
- `AuthorityGrant`
- `Capability`
- `MusicalTime`
- `StateRevision`

The core should not assume that a musical entity is spatial, audible, visual, tangible or controlled by one person.

## Message families

Candidate families:

### Discovery / membership

- station announces/join request;
- capabilities advertised;
- membership accepted/observed;
- station leaves/expires;
- subensemble created/changed.

### State / action

- create/delete entity;
- mutate entity property;
- perform semantic action;
- request/supply state snapshot;
- acknowledge/reject action where policy requires it.

### Authority

- propose/grant authority;
- revoke authority;
- authority lease renewal/expiry;
- change authority policy;
- resolve or report conflicting writes.

### Timing

The protocol may carry musical-time annotations and timing intentions, but network synchronisation should remain replaceable. Ableton Link, DAW clocks or internal clocks may establish a shared timeline independently.

## Transport adapters

### OSC

Likely first interoperability adapter. OSC address spaces should be generated/documented from YARMI semantic messages rather than becoming the domain model.

### Local in-process / IPC

A station should be able to run the same semantic model without networking. Local transports are required for tests and for single-device multi-component applications.

### Future network transports

Reliable and unreliable channels may eventually be separated. Candidate transports are deliberately not fixed before latency, discovery, NAT, mobile networking and failure requirements are measured.

## DAW/plugin boundary

VST3, AU/AUv3, CLAP and DAW APIs are not YARMI protocol transports. They are integration adapters that translate host/plugin parameters, notes, transport information, automation and audio/MIDI streams to/from YARMI concepts.

Ableton Link is similarly a timing adapter, not the YARMI control protocol.

## Compatibility rule

A manifestation that replaces OSC with another transport, libpd with another audio engine, or AR interaction with touch/haptics must remain recognisably the same YARMI system at the semantic level.
