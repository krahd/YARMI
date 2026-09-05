# YARMI design decisions

This file is the controlling repository record for current design decisions. Architecture remains revisable through sustained musical use, but a change is not complete until this file and every affected handoff/specification are reconciled.

## D0 — Playability precedes architectural generality

```text
implement -> play -> observe -> revise -> play again
```

Do not build speculative distributed-system generality merely because it is conceivable. Features and abstractions must earn their place through musical use, portability, reliability, integration or a concrete station requirement.

Keep the architecture intelligible, understandable, open and coherent: do not aim for the moon and hit our foot.

## D1 — From-scratch implementation

YARMI 2 is a new implementation/contemporary continuation. Historical code, mappings, networking, Pd organisation, station roles and student implementation decisions are evidence only and are inherited only after a new independent decision.

## D2 — Station is a first-class YARMI concept

YARMI is not generic distributed-music middleware. It is an ensemble of **augmented musical stations**.

A station is an independently playable augmented musical locus that may participate in an ad-hoc ensemble. It is not intrinsically one device/process, one performer, one sensing system, one sound generator, one geometry or one musical component design.

One logical station may span several devices/processes.

## D3 — Augmentation is constitutive; implementation is open

Every YARMI station is augmented. Augmentation may use projection, camera-mediated AR, spatial displays, AR glasses, tracked physical objects, touch, hands, haptics or other arrangements.

The sensing/rendering implementation is replaceable; the requirement that the station's physical/performance situation and computational representation be meaningfully coupled is not optional.

## D4 — Audience intelligibility is the reason for the instrument

Audience intelligibility is constitutive, not decorative. Consequential performer action, computational transformation and musical result must have a publicly observable relationship.

Performer/audience renderings may be the same or different. A private headset/phone experience is incomplete as a YARMI station until the relevant performance state/action relationship also has a public manifestation.

## D5 — First canonical station is a revised original-YARMI design

The first station deliberately revisits the original interaction proposition because it is a useful design, not because it deserves historical preservation.

Required first-station ideas are specified in `FIRST-STATION.md`: freely arranged tracks, explicit periods, visible cursors, track sound/event components, track-local effects, immediate interaction, station/global controls, manipulators, and audience rendering.

This is not an archival recreation; every historical mapping remains revisable.

## D6 — Track geometry and musical period are distinct

Tracks must not collapse into a fixed rectangular 16-step grid.

The first implementation uses freely positioned/oriented line segments. Geometry and musical duration/period are independent. A historical-style binding may let the track-start manipulator change the number of bars, but that is a manipulable parameter mapping, not a centimetre-to-time law.

Curves/non-linear geometry may come later if musically useful.

## D7 — Manipulator is the performer-control concept

A **Manipulator** is a performer-controlled source bound to a manipulable musical element/parameter.

Rotation is only one channel. Translation, scale, distance, orientation, velocity, pressure, contact, hand gesture or another reliable observable may be used.

Additional manipulators may be assigned to expose additional parameters of an existing musical component.

## D8 — Runtime arbitrary objects may become manipulators

The target fiducial-less interaction is instance acquisition, not semantic object recognition: the performer designates *this physical thing* and YARMI tracks it.

Any suitable object may be used for any compatible manipulable element/parameter. The object only exposes channels that the sensing system can recover reliably.

Observable asymmetry matters more than geometric asymmetry. A labelled cylinder may expose rotation; a perfectly uniform rotationally symmetric object does not. The interface must report suitability/confidence and never silently convert ambiguous tracking into musical control.

The first target is runtime selection + region/mask acquisition + lightweight feature tracking + translation/scale/in-plane rotation where observable, plus depth/world position where available. Universal arbitrary-object 6-DoF is not a first requirement.

See `MANIPULATORS.md`.

## D9 — Native platform horizon

Required native targets remain iPhone/iPad, Android, macOS, Windows and Linux.

## D10 — JUCE is a portable host, not station ontology

JUCE is the first portable process/audio/MIDI host and may supply application lifecycle on several targets. It is not required to own every station's sensing/rendering UI.

Native ARKit/ARCore, openFrameworks, headset runtimes or other frameworks may coexist inside one logical station.

## D11 — libpd is the first local DSP backend

Embedded libpd is the first local sound engine behind a replaceable output boundary. Pd does not own station/ensemble semantics, physical interaction, networking or authority.

Native C++/JUCE DSP and external sound generators remain alternatives.

## D12 — Sound endpoints and DAWs are host-agnostic integrations

A station must be able to control sound-producing/processing endpoints without caring where they are hosted.

A VST synthesiser/effect may live inside YARMI, Ableton, Reaper, Bitwig, another plugin host/process or elsewhere. Host identity is not musical semantics. JUCE VST3 hosting is an optional integration route, not the definition of plugin support.

A DAW may also participate as an optional integration environment/component: it may share time through Link, exchange MIDI/audio/control, host plug-ins, expose automatable parameters, or mediate external instruments. DAW-specific concepts do not enter YARMI station semantics merely because a station uses them.

Ableton Live, any other commercial DAW, and standalone Pd are not dependencies. YARMI must remain usable without them.

## D13 — Ableton Link is the first shared timing substrate

Link supplies shared beat/tempo timing. Link is not the YARMI protocol and not authority.

Stations/tracks derive their own periods/phases from shared/absolute musical time. Do not bake a fixed four-beat Link quantum into YARMI semantics.

## D14 — No authority subsystem in the first iteration

First stations are peer-oriented. Do not implement leader election, grants, leases, consensus or hierarchy yet.

The architecture must not preclude later leaderless, fixed-leader, dynamic, multiple, domain-specific, hierarchical/subleader or subensemble authority. If introduced, authority belongs to relations/policies over coordination domains, not a fixed station type.

## D15 — Semantic networking is deferred; OSC is an adapter candidate

No general YARMI state/control protocol is required while stations only share Link timing.

When a musical interaction needs semantic exchange, define the smallest **versioned, transport-independent semantic contract** first. OSC may encode it; OSC is not YARMI itself.

## D16 — `codex/playable-prototype-v0` is a technology spike, not a merge target

Do **not** merge `codex/playable-prototype-v0` wholesale.

Selectively reuse CMake/JUCE/libpd/Link/diagnostic/CI work after removing station-specific leakage. The 4×16 sequencer may later become a `GridSequencer` component inside a station; its lanes, pitches, cutoff and `EVOLVE` behaviour are not core semantics.

See `PROTOTYPE-V0-AUDIT.md`.

## D17 — Architecture remains revisable

Separation at volatile boundaries is required; speculative abstraction is not. The first revised-original station should remain small enough to understand and play.

## Current first-iteration decomposition

```text
YARMI station
  |
  +-- station-local musical model/components
  +-- Manipulators / performer interaction
  +-- performer rendering
  +-- audience rendering
  |
  +--------------------+--------------------+--------------------+
  |                    |                    |                    |
  v                    v                    v                    v
shared time         output endpoints      sensing             rendering
Ableton Link       libpd / VST / ...     AR/CV/touch/...     AR/projection/...
```

## Explicitly open

- exact synthesis/sample palette;
- exact first effect types and multi-effect routing/order;
- quantisation behaviour/UI;
- curves/non-linear tracks after the first line segments;
- exact performer/audience-view composition;
- precise markerless tracking implementation after v0 experiments;
- whether deeper arbitrary-object 6-DoF is musically needed;
- station discovery and shared state beyond Link;
- persistence/replication/conflict semantics;
- whether authority becomes musically necessary;
- alternate timing backends;
- AU/AUv3/CLAP/LV2 priorities;
- whether YARMI itself becomes a plugin;
- final public version naming.

## Historical sources

The 2009 YARMI paper is a primary design source for the original goals of direct manipulation, sequenced organisation, immediate interaction and audience legibility.

The 2011 paper *A New Iteration of YARMI* has been recovered into `krahd/research/academic-writing/my_papers/2011 - A New Iteration of YARMI/` with PDF and original Spanish Word source. Its existence/completeness must not be confused with current design authority.

If the historical codebase is recovered, classify observations only as `historical-observation`, `candidate`, or `rejected`; nothing becomes current by inertia.
