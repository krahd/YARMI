# YARMI architecture

## Design objective

YARMI is not a particular user interface or physical instrument. It is a distributed musical-system architecture from which multiple instrument manifestations can be built.

The architecture itself is provisional. We preserve replaceable boundaries where current evidence says change is likely, but we do not implement speculative generality before musical use demonstrates a need.

## Development constraint: playability first

Architectural decisions are evaluated through playable iterations. The current loop is:

```text
implement -> play -> observe -> revise architecture/semantics -> play again
```

A theoretically elegant distributed-system feature is not a requirement merely because it is representable. The instrument must justify the architecture.

## Current v0 architecture

The first portable/playable iteration deliberately fixes a small set of implementation choices:

- **JUCE** owns portable application lifecycle, audio device access, MIDI and desktop/mobile deployment;
- **libpd** is the first embedded DSP backend, behind a replaceable `AudioBackend` interface;
- **Ableton Link** provides all shared ensemble tempo/beat/phase timing in v0;
- **JUCE VST3 hosting** is the first desktop third-party-plugin integration path;
- **Ableton Live and standalone Pd are not dependencies**;
- no YARMI authority/leader subsystem is implemented until playability demonstrates a concrete requirement;
- control/state networking beyond Link is added only when a musical interaction needs semantic station-to-station exchange.

```text
Input / manifestation adapters
  touch | AR | objects | hands | MIDI | VR | haptics | projection | ...
                         |
                         v
Provisional YARMI musical/station semantics
                         |
             +-----------+-----------+
             |                       |
             v                       v
       Ableton Link              AudioBackend
    tempo / beat / phase             |
                                     v
                                   libpd

JUCE hosts the portable process/application.
JUCE also provides the first desktop VST3-host integration path.
```

This diagram describes the first implementation, not the final ontology.

## Physicality is outside the core

YARMI 2.0 must not know, at its semantic centre, whether interaction comes from:

- fiducial markers;
- arbitrary physical objects;
- hands/body tracking;
- touch;
- mouse/keyboard;
- projectors;
- phones/tablets;
- AR glasses;
- VR/XR;
- tactile/haptic devices;
- MIDI/OSC controllers;
- cameras;
- interfaces not yet selected.

Manifestations translate physical/perceptual interaction into musical actions and translate YARMI state into sound, image, spatial augmentation, haptics or external control.

Spatial coordinates are optional metadata. Non-spatial manifestations must not invent fake coordinates to satisfy the core.

## Station

A station is an autonomous participant in a musical ensemble. At the architectural level, station identity must not imply:

- device class;
- screen or physical form;
- one performer;
- one location;
- leader/follower role;
- audio ownership;
- spatial coordinates;
- a fixed interaction modality.

For v0, stations are peers sharing Link timing. They may initially have no YARMI-level knowledge of one another beyond what a playable manifestation actually requires.

## Timing

### v0

Ableton Link is the timing substrate for the first iteration. It provides the common tempo/beat/phase relationship among independently running stations.

Local audio rendering remains tied to each device's own audio clock. A station maps Link musical time to local scheduling; network packet arrival must not be treated as musical time.

### Later, only if required

If Link proves insufficient for musical reasons, a timing abstraction may later admit:

- another shared clock;
- DAW-derived timing;
- a custom YARMI clock;
- multiple timing domains;
- topology-dependent time.

Do not build these before a concrete requirement exists.

## Authority / leadership

Authority is **not implemented in v0**.

The architecture should simply avoid baking in the assumption that Link's peer model is the only topology YARMI could ever support. If musical use later demonstrates a need, future arrangements may include:

- leaderless control;
- one fixed leader;
- dynamically assigned leader;
- several leaders;
- leaders scoped to different domains;
- hierarchical leaders/subleaders;
- subensemble/local authority;
- other policies discovered through performance.

Leadership should then be modelled as a relation/policy over a coordination domain rather than as an intrinsic station type. This is a **large-schema design envelope**, not current implementation work.

## Audio

Audio is an interchangeable local backend.

### v0

- JUCE owns audio-device integration and callback lifecycle.
- Embedded **libpd** is the first DSP backend.
- Any buffering required between JUCE callback sizes and Pd's DSP quantum belongs inside the backend adapter.
- Real-time code must remain allocation/blocking/I/O safe on the audio thread.

Pd receives musical events/state and produces/processes audio. Pd must not own ensemble semantics, membership, timing policy, physical interaction or networking.

### Later

Native JUCE/C++ DSP or another engine may replace or coexist with libpd if actual use justifies it.

## JUCE versus openFrameworks

JUCE is fixed for the first portable host because the target set includes iPhone/iPad, Android, macOS, Windows and Linux and because audio/MIDI/plugin infrastructure is central.

openFrameworks remains a legitimate manifestation-specific layer for custom graphics, computer vision or creative coding. Native ARKit/ARCore/headset frameworks or other engines may also be used.

Neither JUCE nor openFrameworks belongs in the semantic core.

## DAWs and plug-ins

DAWs are participants/integration environments, not foundations of YARMI.

For v0/near-v0:

1. YARMI runs standalone without Ableton Live or any other DAW.
2. Ableton Live may share timing through Link.
3. Desktop YARMI can host VST3 instruments/effects through JUCE.
4. MIDI/audio/control may connect YARMI to external tools.

Possible later relations include AU/AUv3/LV2/CLAP support, YARMI itself as a plugin, DAW automation mappings and DAW-hosted stations. None is required to define YARMI.

## Control/state protocol

There is deliberately **no requirement to finalise a general distributed YARMI protocol before the first playable Link-synchronised station exists**.

When musical interaction first requires semantic exchange between stations, define the smallest protocol that supports the observed behaviour. Preserve transport independence at that boundary, but do not pre-implement authority grants, replication systems, discovery frameworks or conflict algorithms without evidence.

OSC remains a likely interoperability adapter because of its role in computer music, but it is not automatically the first control transport.

## Large-schema design envelope

The architecture should remain conceptually compatible with, but does not currently implement:

- heterogeneous station/device capabilities;
- discovery and ad-hoc membership;
- shared/replicated semantic state;
- subensembles;
- multiple authority domains/topologies;
- multiple timing backends;
- ordering/idempotence/replay requirements;
- persistence/session recovery;
- multiple network transports;
- spatial and non-spatial manifestations;
- object-, marker-, hand-, touch-, projection-, AR-, VR- and haptic interfaces;
- multiple DSP engines;
- DAW/plugin/hardware adapters;
- heterogeneous renderings of the same ensemble.

These are retained as a design horizon so that v0 choices do not unnecessarily close them off. They are not a roadmap of mandatory abstractions.

## Historical YARMI

Historical code and papers are not specifications. Every semantic and implementation decision is reopened. Recovery work should record what existed, why it might have existed, and whether it deserves independent re-adoption.
