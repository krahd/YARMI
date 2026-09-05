# YARMI

YARMI is a contemporary continuation of the augmented-reality musical instrument first developed at Universidad de la República in Uruguay. YARMI 2 is conceived as an ensemble of **augmented musical stations**: independently playable musical loci that can join ad-hoc ensembles while making the relationship between performer action, computational transformation and musical consequence visible to an audience.

A station is deliberately not tied to one device or interface. It may combine phones or tablets, projection, tracked physical objects, hands, spatial displays, AR glasses, computers, external synthesisers or other systems. One logical station may span several devices or processes.

## Audience intelligibility

Audience intelligibility is central to YARMI. A performance should not collapse into an opaque relation in which a performer operates a hidden interface and unexplained sound follows. Each station therefore provides a public manifestation of the consequential performer actions and musical/computational state. Performer and audience renderings may be identical or different.

## Manipulators

YARMI uses the term **Manipulator** for a performer-controlled source bound to a musical element or parameter. A manipulator may be a runtime-selected physical object, a traditional fiducial, a hand, touch, a virtual object, a MIDI controller or another source. Rotation is only one possible channel; translation, scale, distance, velocity, orientation, pressure and other observable values may be used when reliable.

The current markerless direction allows a performer to select an arbitrary visible rigid object and turn that physical instance into a manipulator without requiring the system to know its semantic category.

## First station

The first canonical YARMI 2 station is a revised version of the original interaction proposition rather than an archival reconstruction. It combines freely arranged temporal tracks, visible time cursors, track-local musical components and effects, immediate musical interaction, station/global controls, and assignable manipulators. Track geometry and musical duration are intentionally separable.

A conventional grid sequencer may also appear as one component inside a station; it does not define YARMI.

## Technical architecture

The implementation is intentionally replaceable at volatile boundaries:

- native targets: iPhone/iPad, Android, macOS, Windows and Linux;
- JUCE is the first portable process/audio/MIDI host;
- libpd is the first local DSP backend candidate;
- Ableton Link is the first shared beat/tempo timing substrate;
- ARKit, ARCore, openFrameworks and other sensing/rendering systems may be used where appropriate;
- VST/DAW integrations are host-agnostic from YARMI's musical semantics;
- OSC may be used as an interoperability transport when semantic station-to-station exchange becomes necessary.

The project is developed through repeated musical use: implementation, playing, observation and revision.
