# First canonical station: revised original YARMI

This is the first YARMI 2 station to implement. It is **not** an archival recreation and carries no obligation to preserve a historical decision simply because it existed. The original design is a useful starting point because it already combines temporal organisation, direct manipulation, immediate interaction and audience-visible augmentation.

## Station boundary

The station is a first-class YARMI object but may span several physical devices/processes. Its sound generator may be local or external. Its performer and audience renderings may differ.

The first station must be recognisably augmented and must expose consequential musical state/action publicly.

## Initial components

### Tracks

A track is a station-local temporal component.

For the first implementation:

- a track is initially represented by a freely positioned/oriented line segment rather than a row in a grid;
- start/end establish geometry in the augmented space;
- several tracks may be arranged in arbitrary spatial/geometrical layouts;
- a visible cursor shows current position through the track's musical period;
- track geometry and musical duration are independent variables;
- later curved/spline geometries remain possible but are not required for the first playable implementation.

The first implementation should consume shared/absolute musical time and derive each track's phase from its own period. No fixed four-beat Link quantum is allowed to become the track ontology.

### Track period

Musical period is explicit (for example a number of beats/bars) rather than inferred automatically from physical length.

A good first mapping is the historical one remembered by Tomas Laurenzo: manipulating the track-start object changes the number of bars. Rotation is the default historical gesture when it is observable, but the mapping must be expressed through a Manipulator binding so another channel/source can replace rotation.

Physical/geometric length may later be deliberately bound to period if it proves musically useful; it is not an invariant.

### Sound/event components

Sound/sample/event components can be placed on a track and therefore acquire a temporal position within the track period.

The original interaction grammar remains a useful default: direct manipulation of a sound component can control its main parameter (historically pitch). The exact sound engine and mapping are open.

### Track-local effects

Effects may be placed/associated with a track and act on that track. Direct manipulation controls a principal parameter; additional manipulators can be assigned to further parameters.

The exact first effect types and signal-ordering rule remain open and should be chosen for musical clarity rather than historical fidelity.

### Immediate interaction

The station must include an immediate mode/area/component class in which a performer action has an immediate audible consequence.

Historical examples include a sample sounding/looping while present and an effect being applied immediately to station output. The precise YARMI 2 behaviour may change, but the immediate-vs-sequenced complement is part of the first station's playability contract.

### Station/global controls

Station/global musical controls exist separately from track-local elements where useful. They must not imply a historical leader model. A local station setting is local unless/until an explicit future ensemble/authority semantic says otherwise.

### Manipulators

Any manipulable station element/parameter may receive a Manipulator binding.

A manipulator may be:

- a runtime-selected arbitrary physical object;
- a fiducial;
- a hand/body gesture;
- touch/pen/mouse input;
- a virtual object;
- MIDI/other controller input;
- another future performer-controlled source.

No parameter is intrinsically tied to rotation. See `MANIPULATORS.md`.

### Audience view

Every meaningful interaction above must have an audience-legible representation. The first mobile AR implementation may mirror/project the performer view initially, but the architecture must permit a dedicated audience rendering from the same station state.

## Grid sequencer component

The 4×16 grid from `codex/playable-prototype-v0` is not the station and is not YARMI core. It is a potential `GridSequencer` component.

If reused, it should become manipulable within the augmented station—for example by binding a physical/virtual manipulator to swing, density, transposition, mutation amount or another musical parameter. Its existing fixed lanes, pitches, cutoff and `EVOLVE` behaviour are component-specific choices.

## First canonical station milestone

A convincing first station should demonstrate, on real hardware:

1. an augmented performer space;
2. a public/audience-visible representation;
3. at least one freely arranged track with a visible current-time cursor;
4. explicit track period independent of geometric length;
5. at least one sequenced sound/event component;
6. at least one immediate musical interaction;
7. at least one track/local or station effect;
8. at least one assigned Manipulator controlling a parameter continuously;
9. markerless runtime acquisition of one suitable arbitrary physical manipulator, with visible tracking confidence;
10. musically correct scheduling from audio/shared musical time rather than display-frame timing.

This milestone is intentionally small enough to build and rich enough to test whether the revived YARMI interaction proposition still works.

## Deliberately open

- first synthesis/sample palette;
- first effect types;
- exact routing/order semantics for several effects;
- quantisation UI/rules;
- whether track endpoints themselves are always musical objects;
- curves or non-linear track geometries beyond the first line-segment representation;
- multiple performers per station;
- state persistence;
- station-to-station shared musical objects.
