# YARMI

YARMI is a from-scratch reimplementation and conceptual continuation of the earlier YARMI augmented-reality musical instrument. The current working names are **YARMI 2.0** and **YARMI 2026**; neither is yet fixed as the final public title.

The project is a distributed musical-system architecture for ad-hoc ensembles of autonomous stations. Its central design requirement is that musical semantics, coordination topology, interaction modality, physical manifestation, rendering, transport, synchronisation and audio implementation remain independently replaceable.

## Current scope

YARMI must be able to run natively on:

- iPhone and iPad;
- Android phones and tablets;
- macOS;
- Windows;
- Linux.

A station may eventually be manifested through touch, markers, arbitrary physical objects, hands, cameras, projection, AR, VR/XR, haptics, MIDI/OSC controllers, conventional screens, or interfaces not yet selected. None of these belongs in the semantic core.

## Architectural invariants

1. **Stations are autonomous.** A station is not intrinsically a client, leader, follower, screen, table, device type or physical object.
2. **Authority is a policy, not a station type.** Different coordination domains may have no leader, one fixed leader, dynamic leaders, several leaders, hierarchical leaders/subleaders, local-group leaders, or other policies. The architecture must not assume one topology.
3. **Physicality is an adapter concern.** The core must not require markers, cameras, hands, coordinates, AR, VR, touch or any particular physical representation.
4. **The protocol is semantic and transport-agnostic.** YARMI defines typed domain messages/events independently of OSC, WebSocket, UDP, QUIC or another transport. OSC is a first-class adapter candidate, not the protocol definition.
5. **Timing is separable from authority.** Shared beat/tempo/phase synchronisation may use Ableton Link or another timing service without thereby granting musical or structural authority.
6. **Audio is replaceable.** The initial host may use JUCE and an audio-backend interface supporting libpd and/or native JUCE/C++ DSP. Pd patches must not own ensemble networking, authority or interaction semantics.
7. **DAWs and plug-ins are integration surfaces, not the architecture.** A DAW, plug-in host, VST3/AU/CLAP plug-in, MIDI endpoint or external instrument may participate as a component or station through adapters.
8. **Nothing from historical YARMI is inherited automatically.** Old code, semantics, mappings, UI concepts, networking and Pd patches are historical evidence only and must earn re-adoption independently.

## Immediate research directions

Two possible manifestations are under consideration but do not define YARMI:

- **Spatial YARMI:** musical entities/nodes instantiated and manipulated in 3D space.
- **Object YARMI:** arbitrary existing physical objects can be instantiated as musical entities/stations and computationally or visually augmented.

The older YARMI idea of distributed, ad-hoc station configurations remains important, but the new architecture generalises it so that station membership, authority and synchronisation can vary independently.

## Repository state

This repository intentionally begins with architecture and protocol design before implementation. The original YARMI codebase, if recovered, will be archived and examined as historical material rather than used as the implementation base.

See `docs/ARCHITECTURE.md`, `docs/PROTOCOL.md`, and `docs/DECISIONS.md`.
