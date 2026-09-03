# YARMI 2 iOS existence proof

This is intentionally a **tiny, disposable first manifestation**, not the portable YARMI runtime.

Its purpose is to make one claim concrete as early as possible:

> YARMI 2 exists when a user can place a musical structure in physical space, see its temporal behaviour explicitly, and hear interaction change the result.

## Behaviour

1. Move the iPhone/iPad until ARKit detects surrounding surfaces.
2. Tap once to place the beginning of a track.
3. Tap again to place its end.
4. A line and moving time cursor appear.
5. Subsequent taps are projected onto the track and create note entities.
6. The cursor loops every four seconds and triggers each note as it crosses it.
7. The note position controls its temporary proof-of-concept pitch mapping.

This deliberately recreates only the smallest recognisable interaction documented in historical YARMI: track boundaries, samples placed along a track, an explicit time cursor, and audible triggering. It does **not** inherit the old zones, fiducial ontology, leader model, client/server architecture, fixed track lengths, mappings, Pd patch structure, or audio semantics.

## Implementation

- SwiftUI application shell
- RealityKit / ARKit manifestation
- `AVAudioEngine` temporary sine-tone backend
- local `ProofEnsemble` reducer mirroring the minimal semantics in `../../docs/SEMANTICS.md`
- no networking
- no OSC
- no Ableton Link
- no libpd/JUCE dependency yet

The proof uses Apple-native AR code because the immediate objective is the shortest route to a real mobile manifestation. It does not determine the eventual cross-platform AR layer.

## Build

Open:

```text
apps/ios-proof/YARMI2Proof.xcodeproj
```

Select an iPhone or iPad device and run the `YARMI2Proof` scheme. A real device is required for meaningful AR behaviour.

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

## Exit criterion

This prototype has done its job once it runs on a real iPhone/iPad and demonstrates the complete seven-step behaviour above. After that, further work should move back to the portable semantic/runtime architecture rather than growing this Swift proof opportunistically.
