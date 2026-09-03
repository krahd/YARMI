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

### D2 — Physicality-agnostic core

The core does not assume markers, tables, cameras, touchscreens, objects, hands, projections, AR, VR/XR, haptics, coordinates or any other manifestation.

Physical/spatial information is optional manifestation data. A valid YARMI station or action must not require a spatial coordinate merely because some manifestations use space.

### D3 — Native cross-platform target

The portable implementation must support native applications on:

- iPhone/iPad;
- Android;
- macOS;
- Windows;
- Linux.

### D4 — JUCE is the v0 portable application host

JUCE is the first portable host for application lifecycle, audio device access, MIDI and desktop/mobile deployment. This is a v0 implementation decision, not a claim that JUCE belongs in YARMI semantics.

openFrameworks remains available as a manifestation-specific graphics/CV/creative-coding layer if useful. Native AR/VR/platform frameworks may also be used behind manifestation adapters.

### D5 — libpd is the first v0 DSP backend

The first portable playable implementation uses embedded libpd behind an `AudioBackend` boundary. Pd is chosen for rapid and proven real-time musical DSP, not as the owner of YARMI semantics.

Pd must not own ensemble membership, networking, interaction semantics, physicality, authority or application lifecycle. Native JUCE/C++ DSP remains a later interchangeable backend if playability, latency, maintainability or deployment justifies it.

### D6 — Ableton Link is the complete v0 ensemble timing substrate

The first iteration uses Ableton Link for shared tempo/beat/phase timing. Do not implement a custom clock, leader clock, election scheme or YARMI authority layer before musical use demonstrates a need.

Link is a timing substrate only. It is not the YARMI semantic/control protocol and does not make Ableton Live a dependency.

### D7 — No authority subsystem in v0

The first iteration is peer-oriented and uses Link's shared timing behaviour. Do not implement leader election, authority grants, leases, consensus, subleaders, hierarchical control or conflict policies in v0.

The architecture should avoid assumptions that would make future authority arrangements impossible. If playability later demands authority, the larger design envelope includes:

- no leader;
- one fixed leader;
- dynamic leader assignment;
- several leaders;
- domain-specific leaders;
- hierarchical leaders/subleaders;
- subensemble/local authority;
- other policies discovered through use.

This is a deferred capability space, not a v0 implementation backlog.

### D8 — Ableton Live and standalone Pd are not dependencies

Both may participate in a musical setup, but a YARMI ensemble must run without either application.

### D9 — JUCE plugin hosting is a first-class desktop integration path

Desktop YARMI should be able to host third-party VST3 instruments/effects through JUCE. Plugin hosting is an integration surface, not a core semantic assumption.

YARMI may later also expose itself as a plugin where useful, but that is not required for the first playable iteration.

### D10 — DAWs and plug-ins remain optional participants

A DAW may join timing through Link, receive/send MIDI/audio/control, or host/route plugins. YARMI semantics must not depend on Ableton Live, Logic, Bitwig, Reaper or any other DAW.

### D11 — Architecture is intentionally revisable

Separation at volatile boundaries is required; speculative abstraction is not. We keep enough decomposition to replace DSP, synchronisation, manifestation and integration layers, but we do not build a general-purpose distributed-music framework in advance of an instrument.

## Current v0 decomposition

```text
manifestation/input adapters
        |
        v
minimal YARMI station/musical semantics
        |
        +-------------------+
        |                   |
        v                   v
Ableton Link           AudioBackend
(shared time)              |
                           v
                         libpd

portable process/application host: JUCE
optional desktop integration: JUCE VST3 hosting
```

Control/state networking beyond Link is introduced only when a musical behaviour actually needs station-to-station semantic exchange.

## Explicitly open

- canonical musical entity model;
- whether tracks/sequencers exist at all in the contemporary instrument;
- synthesis/processing model beyond the first libpd backend;
- rendering framework per manifestation;
- first persistent physical manifestation after the existing iOS AR proof;
- control/state network protocol and transport, if/when needed;
- OSC's eventual role;
- station discovery beyond what the first playable ensemble requires;
- persistence/replication/conflict semantics;
- whether authority is needed at all;
- if authority is needed, its domains and policies;
- whether native JUCE/C++ DSP replaces or complements libpd;
- AU/AUv3/LV2/CLAP integration priorities;
- whether YARMI itself ships as a plugin;
- final public title/version naming.

## Large-schema design envelope — preserve, do not implement by default

The longer-term architecture may eventually need to represent independently:

- station/device capabilities;
- ensemble/subensemble membership;
- timing backends other than Link;
- multiple authority domains and topologies;
- shared semantic state and replication;
- discovery and capability negotiation;
- ordering/idempotence/replay guarantees;
- persistence and session recovery;
- several simultaneous transports;
- local, spatial and remote manifestations;
- object-, hand-, marker-, touch-, projection-, AR-, VR-, haptic- and controller-based interaction;
- several DSP engines;
- DAWs, plugin hosts and hardware instruments;
- heterogeneous stations that render the same ensemble differently.

This list records design possibility. It is not a commitment to implement the corresponding abstractions before they are justified.

## Historical-material rule

When the old codebase is recovered, review observations under three labels only:

- `historical-observation` — what the system actually did;
- `candidate` — something worth independently reconsidering;
- `rejected` — something deliberately not carried forward.

No historical behaviour becomes `current` merely because it existed or because it was documented in a paper/codebase.
