# YARMI architecture

## Design objective

YARMI is not a particular user interface or physical instrument. It is a distributed musical-system architecture from which multiple instrument manifestations can be built.

The architecture must permit independent variation of:

- station implementation and device type;
- ensemble topology;
- leadership/authority policy;
- musical semantics;
- timing/synchronisation mechanism;
- network/wire transport;
- audio engine;
- rendering system;
- sensing/input modality;
- physical manifestation;
- DAW/plugin integration.

## Layers

```text
Input / sensing adapters
  touch | fiducials | objects | hands | MIDI | OSC | AR | VR | haptics | ...
                         |
                         v
Interaction adapters / manifestation semantics
                         |
                         v
YARMI semantic core
  ensemble | stations | entities | actions | state | authority | timing intent
                         |
          +--------------+----------------+
          |                               |
          v                               v
Protocol / replication                Local engines
transport-independent model          audio | visual | haptic | other
          |
          +--> OSC adapter
          +--> local IPC adapter
          +--> future network adapters

Timing service is orthogonal:
Ableton Link / internal clock / DAW clock / other

External music-system adapters are orthogonal:
DAW | VST3 | AU/AUv3 | CLAP | MIDI | external plugin host | hardware
```

## Station

A station is an autonomous participant in an ensemble. The core station identity must not imply:

- device class;
- screen or physical form;
- one performer;
- one location;
- leader/follower role;
- audio ownership;
- spatial coordinates;
- a fixed interaction modality.

Spatial metadata may be attached by manifestations that need it, but spatiality is optional.

## Authority

Authority is represented separately from station identity. It applies to named coordination domains. Candidate domains include:

- tempo;
- phase/metre;
- transport;
- form/scene;
- routing;
- parameter groups;
- membership;
- subensemble configuration;
- visual or spatial coordination.

The architecture must be capable of representing, without structural changes:

- no authority/fully local behaviour;
- peer consensus;
- one fixed authority;
- one dynamically elected authority;
- lease-based temporary authority;
- several simultaneous authorities;
- domain-partitioned authority;
- hierarchical leaders/subleaders;
- local-group/subensemble authority.

Supporting a policy in the data model does not imply implementing all policies initially.

## Timing versus authority

Musical synchronisation is not leadership. A station may share beat, phase and tempo through Ableton Link while authority over tempo changes is governed independently by YARMI policy. A DAW clock or another timing source may similarly be used without becoming the semantic centre of the ensemble.

## Semantic protocol and wire transports

YARMI defines a versioned typed protocol in terms of domain objects and events. It must not define itself as an OSC address tree.

OSC is a strong first adapter because it is established in computer music and explicitly message-based and transport-independent. An OSC mapping should expose YARMI entities/events to existing musical software while preserving a canonical transport-neutral representation.

Transport adapters may optimise delivery differently according to message class. The semantic protocol should state ordering, identity, idempotence, versioning and timing requirements rather than assuming that all messages have identical network semantics.

## Audio

Audio is an interchangeable backend. The initial host architecture should permit at least:

- embedded libpd;
- native C++/JUCE DSP;
- external audio via MIDI/OSC/DAW adapters;
- hosted third-party plug-ins where the platform permits it.

Pd, if used, receives musical events/state and produces or processes audio. It must not own ensemble membership, network replication, authority policy or interaction semantics.

## Application/UI framework

JUCE is currently the leading default application host because it provides one C++ framework across the required desktop and mobile targets and integrates audio/MIDI and plugin infrastructure. openFrameworks remains a candidate rendering/interaction layer for manifestations where its creative-coding, graphics or camera stack is advantageous.

Neither JUCE nor openFrameworks belongs in the semantic core API.

## DAWs and plug-ins

DAWs are participants/integration environments, not foundations of YARMI.

Potential relations include:

1. a YARMI station sends MIDI/audio/control to a DAW;
2. a DAW participates in YARMI timing through Link or another clock adapter;
3. a YARMI desktop station hosts VST3/AU/LV2 or other supported plug-ins;
4. a YARMI station is exposed as a VST3/AU/AUv3/CLAP plug-in where useful;
5. a YARMI adapter maps DAW automation/parameters into YARMI semantic actions;
6. a DAW or DAW track may itself be represented as a station/component if an adapter can provide the required semantics.

No DAW-specific concept belongs in the core model.

## Historical YARMI

Historical code and papers are not specifications. Every semantic and implementation decision is reopened. Recovery work should record what existed, why it might have existed, and whether it deserves independent re-adoption.
