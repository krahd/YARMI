# YARMI design decisions

This file records current decisions and explicitly open choices. Historical YARMI decisions are not presumed valid. Architecture is itself provisional: decisions may be revised when sustained musical use demonstrates that another structure is better.

## Governing development rule

### D0 — Playability precedes architectural generality

YARMI is developed by repeated cycles of:

```text
implement -> play -> observe requirement/friction/possibility -> revise -> play again
```

Do not implement complexity merely because a distributed musical system might theoretically need it. A feature, abstraction, protocol or authority mechanism should earn its place through musical use, implementation necessity, portability, reliability, or a concrete manifestation requirement.

Tomas Laurenzo is the principal initial performer/designer and sustained first-person musical use is valid design evidence for early iterations. Formal user studies are not a prerequisite for changing the instrument.

## Fixed decisions for the first portable/playable iteration

### D1 — From-scratch implementation

YARMI 2.0 / YARMI 2026 is implemented from scratch. Historical code may be recovered and studied, but no code, semantics, mapping, interaction grammar, DSP organisation, networking model or architecture is inherited automatically.

### D2 — YARMI stations are augmented; their physical implementation remains open

A **station** remains a first-class YARMI concept. YARMI is not being reduced to generic distributed-music middleware.

A YARMI station is an independently playable augmented musical locus that presents an intelligible relationship between performer action, computational state and musical consequence, and that may participate in an ad-hoc ensemble with other stations.

The station concept does **not** prescribe how augmentation is implemented. A station may use projection, camera-mediated AR, spatial displays, phones/tablets, AR glasses, tracked objects, hands, touch, haptics, or other physical/computational arrangements. One logical station may span several devices.

The semantic centre must not require fiducials, one screen type, one camera topology, one sensing technology, one audio engine, one performer, or one physical form.

### D3 — Audience intelligibility is constitutive

Audience intelligibility is a defining requirement of YARMI rather than a decorative presentation feature.

A station must make consequential relationships between performer action, computational transformation and musical result available to observation. Performer and audience views may be the same or different, but an implementation visible only to the performer is incomplete as a YARMI station until it also provides a public manifestation of the relevant state/action relationship.

This does not require exposing every internal parameter. It requires that the performance not collapse into an opaque relation of hidden input followed by unexplained sound.

### D4 — Native cross-platform target

The portable implementation must support native applications on:

- iPhone/iPad;
- Android;
- macOS;
- Windows;
- Linux.

### D5 — JUCE is the first portable process/application host

JUCE is the first portable host for application lifecycle, audio device access, MIDI and desktop/mobile deployment. This is a first implementation choice, not a claim that every YARMI station must be a single JUCE application.

openFrameworks remains available as a manifestation-specific graphics/CV/creative-coding layer if useful. Native AR/VR/platform frameworks may also be used. A logical station may combine components hosted by different processes/devices.

### D6 — libpd is the first DSP backend

The first portable playable implementation uses embedded libpd behind a replaceable audio/output boundary. Pd is chosen for rapid and proven real-time musical DSP, not as the owner of YARMI semantics.

Pd must not own ensemble membership, networking, interaction semantics, physicality, authority or application lifecycle. Native JUCE/C++ DSP and external sound generators remain interchangeable alternatives.

### D7 — Ableton Link is the complete first ensemble timing substrate

The first iteration uses Ableton Link for shared tempo/beat/phase timing. Do not implement a custom clock, leader clock, election scheme or YARMI authority layer before musical use demonstrates a need.

Link is a timing substrate only. It is not the YARMI semantic/control protocol and does not make Ableton Live a dependency.

### D8 — No authority subsystem in the first iteration

The first iteration is peer-oriented and uses Link's shared timing behaviour. Do not implement leader election, authority grants, leases, consensus, subleaders, hierarchical control or conflict policies yet.

The architecture should avoid assumptions that would make future authority arrangements impossible. If playability later demands authority, the larger design envelope includes no leader, one fixed leader, dynamic leader assignment, several leaders, domain-specific leaders, hierarchical leaders/subleaders, subensemble/local authority, and other policies discovered through use.

### D9 — Ableton Live and standalone Pd are not dependencies

Both may participate in a musical setup, but a YARMI ensemble must run without either application.

### D10 — Sound endpoints are host-agnostic

YARMI must be able to control a sound-producing or sound-processing endpoint without requiring YARMI semantics to know where that endpoint is hosted.

A VST3 synthesiser may be hosted by YARMI, Ableton Live, Reaper, Bitwig, another plugin host, or another process. The station should interact through a suitable adapter/control boundary rather than treating host identity as musical semantics.

JUCE VST3 hosting remains a useful optional desktop integration path, not the definition of plugin integration.

### D11 — DAWs and plug-ins remain optional participants

A DAW may join timing through Link, receive/send MIDI/audio/control, or host/route plugins. YARMI semantics must not depend on Ableton Live, Logic, Bitwig, Reaper or any other DAW.

### D12 — Manipulator is the control-source concept

A **Manipulator** is a performer-controlled source that can be bound to a manipulable musical element or parameter.

A manipulator does not imply rotation. Possible observable channels include translation, in-plane rotation, 3D orientation, scale, distance, speed, contact, hand gesture, pressure, or another sensing/control value. A sensing adapter exposes only the channels it can estimate usefully.

An arbitrary physical object selected at runtime can become a manipulator without semantic object recognition. Fiducials, hands, virtual objects, touch, MIDI controllers and other sources can also be manipulators.

See `docs/MANIPULATORS.md`.

### D13 — Architecture is intentionally revisable

Separation at volatile boundaries is required; speculative abstraction is not. We keep enough decomposition to replace DSP, synchronisation, sensing/manifestation and integration layers, but we do not build a general-purpose distributed-music framework in advance of the instrument.

## Current first-iteration decomposition

```text
augmented station
  |
  +-- performer interaction / manipulators
  +-- performer view
  +-- audience-visible view
  +-- station-specific musical model
  |
  +-------------------+-------------------+
  |                   |                   |
  v                   v                   v
shared time        output adapters     sensing/rendering
(Ableton Link)     libpd / VST / ...   AR / CV / touch / ...
```

Control/state networking beyond Link is introduced only when a musical behaviour actually needs station-to-station semantic exchange.

## Explicitly open

- exact internal model of the first revised-original YARMI station;
- track geometry and track-period interaction rules;
- synthesis/processing model beyond the first libpd backend;
- rendering framework per station implementation;
- exact performer/audience-view relationship for mobile AR;
- fiducial-less arbitrary-object tracking implementation and supported manipulator channels;
- control/state network protocol and transport, if/when needed;
- OSC's eventual role;
- station discovery beyond what the first playable ensemble requires;
- persistence/replication/conflict semantics;
- whether authority is needed in actual musical use;
- if authority is needed, its domains and policies;
- whether native JUCE/C++ DSP replaces or complements libpd;
- AU/AUv3/LV2/CLAP integration priorities;
- whether YARMI itself ships as a plugin;
- final public title/version naming.

## Large-schema design envelope — preserve, do not implement by default

The longer-term architecture may eventually need to represent independently:

- heterogeneous station/device capabilities;
- ensemble/subensemble membership;
- timing backends other than Link;
- multiple authority domains and topologies;
- shared semantic state and replication;
- discovery and capability negotiation;
- ordering/idempotence/replay guarantees;
- persistence and session recovery;
- several simultaneous transports;
- different AR/augmentation techniques;
- object-, hand-, marker-, touch-, projection- and haptic interaction;
- several DSP engines;
- DAWs, plugin hosts and hardware instruments;
- heterogeneous performer/audience renderings of the same station state.

This list records design possibility. It is not a commitment to implement the corresponding abstractions before they are justified.

## Historical-material rule

When the old codebase is recovered, review observations under three labels only:

- `historical-observation` — what the system actually did;
- `candidate` — something worth independently reconsidering;
- `rejected` — something deliberately not carried forward.

No historical behaviour becomes current merely because it existed or because it was documented in a paper/codebase.
