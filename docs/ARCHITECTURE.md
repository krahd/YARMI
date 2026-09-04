# YARMI architecture

## Design objective

YARMI is an ensemble of augmented musical stations designed around direct manipulation and audience-intelligible musical causality.

A **station** is a first-class YARMI concept. Its internal musical components, sensing technology, rendering technology, audio implementation, device topology and interaction techniques remain open and replaceable.

The architecture is provisional. We preserve replaceable boundaries where current evidence says change is likely, but we do not implement speculative generality before musical use demonstrates a need.

## Constitutive requirements

### Augmented station

A YARMI station is an independently playable augmented musical locus that may participate in an ad-hoc ensemble with other stations.

Augmentation does not mean one particular AR SDK or camera arrangement. A station may use projection, camera-mediated AR, spatial displays, phones/tablets, AR glasses, tracked physical objects, hands, touch, haptics or combinations of devices.

One logical station may span several physical devices or processes.

### Audience intelligibility

Audience intelligibility is constitutive of YARMI.

A station must make the consequential relationship between performer action, computational transformation and musical result available to observation. A performer view and an audience view may be identical or different renderings of the same station state.

An implementation visible only to the performer is incomplete as a YARMI station until the relevant action/state relationship also has a public manifestation.

## Development constraint: playability first

Architectural decisions are evaluated through playable iterations:

```text
implement -> play -> observe -> revise architecture/semantics -> play again
```

A theoretically elegant distributed-system feature is not a requirement merely because it is representable. The instrument must justify the architecture.

## Current first-iteration architecture

The first portable/playable iteration deliberately fixes a small set of implementation choices:

- **JUCE** is the first portable process/application host for audio, MIDI and cross-platform deployment;
- **libpd** is the first embedded DSP backend behind a replaceable output boundary;
- **Ableton Link** provides shared ensemble tempo/beat/phase timing;
- native ARKit/ARCore or other manifestation-specific frameworks may coexist with the portable host;
- VST/DAW integration is host-agnostic at the YARMI semantic level;
- no YARMI authority/leader subsystem is implemented until playability demonstrates a concrete requirement;
- control/state networking beyond Link is added only when a musical interaction needs semantic station-to-station exchange.

```text
YARMI Station
  |
  +-- station-specific musical model/components
  +-- Manipulators / performer interaction
  +-- performer rendering
  +-- audience rendering
  |
  +---------------------+--------------------+--------------------+
  |                     |                    |                    |
  v                     v                    v                    v
Timing                Output              Sensing              Rendering
Ableton Link       libpd / VST / ...   AR/CV/touch/...      AR/projection/...
```

This describes the first implementation boundary, not a universal ontology of musical components.

## Station

Station identity must not intrinsically imply:

- one device or process;
- one screen or physical form;
- one performer;
- leader/follower role;
- ownership of its sound generator;
- a fixed geometry;
- tracks or a sequencer;
- a fixed sensing technology.

For the first iteration, stations are peers sharing Link timing. They may initially have no YARMI-level knowledge of one another beyond what a playable manifestation requires.

## Manipulators

A **Manipulator** is a performer-controlled source that can be bound to a manipulable musical element or parameter.

A manipulator may be an arbitrary physical object selected at runtime, a fiducial, hand, touch gesture, virtual object, MIDI control, or another source.

Rotation is one possible observable channel, not the definition of a manipulator. Tracking/sensing adapters may expose translation, in-plane rotation, 3D orientation, scale, distance, velocity, contact, hand gesture, pressure or other values when those values are sufficiently reliable.

The station binds available manipulator channels to its own musical components. The station's internal component vocabulary is not promoted into global YARMI semantics merely because the first station uses it.

See `MANIPULATORS.md`.

## Timing

Ableton Link is the timing substrate for the first iteration. It provides common tempo/beat relationships among independently running stations.

Local audio rendering remains tied to each device's own audio clock. A station maps Link musical time to local scheduling; network packet arrival is not musical time.

Station-specific periods, tracks, polymeters or other temporal structures are derived from absolute/shared musical time rather than imposed by one fixed Link quantum.

If Link later proves insufficient for musical reasons, timing may admit another shared clock, DAW-derived time, custom YARMI timing or multiple timing domains. Do not build those before a concrete requirement exists.

## Authority / leadership

Authority is not implemented in the first iteration.

The architecture simply avoids baking in the assumption that Link's peer model is the only topology YARMI could ever support. If musical use later demonstrates a need, leadership/authority should be modelled as a relation or policy over a coordination domain rather than as an intrinsic station type.

Possible later arrangements include no leader, one fixed leader, dynamically assigned leaders, several leaders, domain-specific leaders, hierarchical leaders/subleaders and subensemble/local authority.

## Audio and external sound generation

Sound generation/processing is replaceable and may be local or external.

For the first iteration:

- embedded libpd is the first local DSP backend;
- real-time code must remain allocation/blocking/I/O safe on the audio thread;
- Pd does not own station/ensemble semantics or physical interaction.

A VST instrument or effect may be hosted inside YARMI, Ableton Live, Reaper, Bitwig, another plugin host, or another process. YARMI should control it through an adapter without requiring the station's musical semantics to know which host owns the plugin.

Native JUCE/C++ DSP or another engine may replace or coexist with libpd if use justifies it.

## JUCE, openFrameworks and native AR frameworks

JUCE is the first portable process host because the target set includes iPhone/iPad, Android, macOS, Windows and Linux and because audio/MIDI/plugin infrastructure is central.

It is not the required rendering/sensing host for every station. openFrameworks remains a legitimate graphics/CV layer; ARKit, ARCore, headset runtimes or other engines may be used directly where they provide the best manifestation.

## Control/state protocol

There is deliberately no requirement to finalise a general distributed YARMI protocol before the first playable Link-synchronised stations exist.

When musical interaction first requires semantic exchange between stations, define the smallest protocol that supports the observed behaviour. Preserve transport independence at that boundary, but do not pre-implement replication systems, discovery frameworks or conflict algorithms without evidence.

OSC remains a likely interoperability adapter because of its role in computer music, not a predetermined canonical protocol.

## Current first station

The first canonical station is a **revised original YARMI design**, not an archival recreation.

Its initial component vocabulary may include:

- freely arranged tracks;
- explicit musical period independent of geometric length;
- visible current-time cursors;
- sound/sample/event components;
- local track effects;
- immediate components/effects;
- station/global controls;
- manipulators assigned to component parameters;
- performer and audience renderings.

Historical ideas are retained only where they remain musically useful.

The existing 4×16 Codex grid prototype is not YARMI core. It may later become a **GridSequencer component** inside a station and acquire YARMI-style manipulators/augmentation.

## Large-schema design envelope

The architecture should remain conceptually compatible with, but does not currently implement:

- heterogeneous station/device capabilities;
- discovery and ad-hoc membership;
- shared/replicated semantic state;
- subensembles;
- multiple authority domains/topologies;
- multiple timing backends;
- persistence/session recovery;
- multiple network transports;
- several sensing/tracking systems;
- markerless arbitrary-object manipulators;
- hands/body/touch/haptic controls;
- several DSP engines;
- DAW/plugin/hardware adapters;
- heterogeneous performer/audience renderings of one station.

These are retained as a design horizon so that first-iteration choices do not unnecessarily close them off. They are not a roadmap of mandatory abstractions.

## Historical YARMI

Historical code and papers are evidence, not specifications. Every semantic and implementation decision is reopened. Recovery work should record what existed, why it might have existed, and whether it deserves independent re-adoption.
