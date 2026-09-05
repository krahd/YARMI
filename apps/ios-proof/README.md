# YARMI 2 iOS AR proof

This is intentionally a **tiny, disposable AR technology/interaction proof**, not the canonical YARMI 2 station and not the portable runtime.

Its current purpose is narrower than the first-station milestone: confirm on real Apple hardware that a musical structure can be placed in physical space, rendered with explicit temporal behaviour, and made audible.

## Behaviour

1. Move the iPhone/iPad until ARKit detects surrounding surfaces.
2. Tap once to place the beginning of a track.
3. Tap again to place its end.
4. A line and moving time cursor appear.
5. Subsequent taps are projected onto the track and create note entities.
6. The cursor loops every four seconds and triggers each note as it crosses it.
7. The note position controls a temporary proof-of-concept pitch mapping.

This recreates only one small historical echo: track boundaries, events on a track, an explicit time cursor and audible triggering.

It does **not** implement the current YARMI 2 playability contract. In particular it does not yet provide:

- the revised-original first station;
- immediate interaction/effects;
- track/global effects and controls;
- Manipulator assignment;
- markerless arbitrary-object tracking;
- the constitutive audience-view requirement beyond ordinary screen mirroring;
- audio/shared-time scheduling suitable for musical performance;
- multi-station timing/network behaviour.

## Implementation

- SwiftUI application shell;
- RealityKit / ARKit rendering;
- `AVAudioEngine` temporary sine-tone backend;
- local proof-only state;
- no networking, OSC, Link, libpd or JUCE dependency.

The cursor/note crossing logic currently uses display-frame timing. That is acceptable for this disposable proof but must **not** become the scheduler for the canonical station.

## Build

Open:

```text
apps/ios-proof/YARMI2Proof.xcodeproj
```

Select an iPhone or iPad and run `YARMI2Proof`. A real device is required for meaningful AR validation.

For a compile-only simulator build:

```bash
xcodebuild \
  -project apps/ios-proof/YARMI2Proof.xcodeproj \
  -scheme YARMI2Proof \
  -sdk iphonesimulator \
  -configuration Debug \
  CODE_SIGNING_ALLOWED=NO \
  build
```

The repository workflow `.github/workflows/ios-proof.yml` runs this compile-only check.

## Exit criterion

This proof is complete once the seven-step behaviour above has been validated on a physical iPhone/iPad and any proof-blocking defects have been recorded/fixed.

Passing this gate does **not** by itself establish the canonical YARMI 2 station. The first station milestone is defined in `../../docs/FIRST-STATION.md`.
