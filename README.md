# YARMI

YARMI is a from-scratch reimplementation and conceptual continuation of the earlier YARMI augmented-reality musical instrument. Current working names are **YARMI 2.0** and **YARMI 2026**; neither is fixed as the final public title.

The contemporary project explores ad-hoc ensembles of autonomous musical stations while refusing to define the instrument by one physical interface, one DSP engine, one rendering system, one device class, or one coordination topology.

The project is **playability-driven**: architecture and semantics are expected to change through repeated musical use.

```text
implement -> play -> observe -> revise -> play again
```

## Required platform horizon

YARMI must ultimately run natively on:

- iPhone and iPad;
- Android phones and tablets;
- macOS;
- Windows;
- Linux.

## Current first-iteration decisions

The first portable/playable implementation deliberately chooses:

- **JUCE** as the cross-platform application/audio/MIDI host;
- **libpd** as the first embedded DSP backend behind a replaceable interface;
- **Ableton Link** for all v0 ensemble tempo/beat/phase synchronisation;
- **JUCE VST3 hosting** as the first desktop third-party-plugin integration path;
- no dependency on Ableton Live;
- no dependency on standalone Pd;
- no custom synchronisation system in v0;
- no YARMI leader/authority-management subsystem until musical use demonstrates a need;
- no general control/state network protocol until a musical interaction requires station-to-station semantic exchange.

These are implementation decisions for getting to a playable system quickly. The architecture remains revisable.

## Physicality is not YARMI

A station may eventually be manifested through touch, markers, arbitrary physical objects, hands/body tracking, cameras, projection, AR, VR/XR, haptics, MIDI/OSC controllers, conventional screens, or interfaces not yet selected.

None of these belongs in the semantic core.

Spatial information is optional. A tactile, MIDI or other non-spatial manifestation must not need fictitious coordinates merely because another manifestation uses 3D space.

## Stations and timing

A station is an autonomous participant; it is not intrinsically a client, leader, follower, screen, table, device type or physical object.

For v0, stations are peers sharing musical timing through Ableton Link. Multiple stations may initially share **only** Link timing and otherwise remain independent. That is a valid first ensemble.

The older YARMI concept of distributed, ad-hoc station configurations remains central, but the contemporary implementation will not inherit the old client/server or leader-station semantics automatically.

## Authority: design horizon, not v0 work

If playability later requires structured authority, the architecture should be able to evolve toward no leader, one fixed leader, dynamic leaders, several leaders, hierarchical leaders/subleaders, domain-specific leaders, subensemble authority, or other configurations.

Do **not** implement these merely because they are conceivable. They are preserved as a large-schema design envelope so early choices do not unnecessarily close them off.

## Audio and plugins

JUCE owns the portable application/audio-device lifecycle. libpd is the initial musical DSP backend.

Pd patches render/process sound; they do not own ensemble semantics, networking, physical interaction or application state.

Desktop YARMI will use JUCE's plugin-hosting facilities for a first VST3 integration path. DAWs and plugins remain optional integration surfaces rather than dependencies.

## Current manifestation ideas

Possible manifestations include:

- **Spatial YARMI:** musical entities/nodes instantiated and manipulated in 3D space;
- **Object YARMI:** arbitrary existing physical objects become musical entities/stations and are computationally/visually augmented;
- combined object-plus-spatial configurations;
- touch, projection, hands/body, AR glasses, VR/XR, haptic and other configurations.

These are manifestations, not definitions of YARMI.

## Historical YARMI

Historical papers and any recovered code are evidence only. No code, interaction grammar, track/zone semantics, token mapping, Pd organisation, networking, leadership model or student implementation decision is inherited automatically.

The new implementation starts from scratch.

## Repository map

- `docs/DECISIONS.md` — current decisions, explicit non-decisions and large-schema horizon;
- `docs/ARCHITECTURE.md` — current v0 decomposition versus deferred architectural possibilities;
- `docs/SEMANTICS.md` — deliberately small provisional semantic vocabulary;
- `docs/PROTOCOL.md` — why a general YARMI control protocol is deferred until playability requires it;
- `docs/DEVELOPMENT.md` — immediate implementation sequence, playability loop, measurement gates and coding-agent handoff;
- `apps/ios-proof/` — disposable SwiftUI/RealityKit/ARKit existence proof, not the portable architecture.

For implementation work, read **`docs/DEVELOPMENT.md` and `docs/DECISIONS.md` first**.

## Playable prototype

The first portable station is now implemented in `Source/`. The same JUCE application runs on
macOS and iPadOS and provides:

- a touch/mouse-editable four-lane, 16-step instrument;
- an embedded libpd synth (no standalone Pd installation);
- Ableton Link beat/phase/tempo on macOS and official LinkKit integration on iPadOS;
- tempo, transposition and timbre controls, plus clear/evolve performance actions;
- live sample-rate, buffer, output-latency, callback-load and estimated-xrun diagnostics.

The cells are the instrument: tap or click to toggle notes, then drag across the grid to reshape a
phrase while it plays. `EVOLVE` mutates the current phrase without replacing it. Each process is an
autonomous station; Link shares time only.

### Build on macOS

Prerequisites are Xcode and CMake 3.28 or newer. The first configure downloads pinned JUCE, libpd,
and Ableton Link sources.

```sh
./scripts/configure-macos.sh -DBUILD_TESTING=ON
cmake --build build-macos --config Debug --target YarmiStation YarmiCoreTests YarmiAudioTests
ctest --test-dir build-macos -C Debug --output-on-failure
open "build-macos/YarmiStation_artefacts/Debug/YARMI.app"
```

### Build on iPadOS

```sh
./scripts/configure-ios.sh
open build-ios/YARMI.xcodeproj
```

Select the `YarmiStation` scheme and a physical iPad, set your development team, then run. The
project downloads the pinned official LinkKit 4.1 XCFramework. Link peer discovery on hardware
requires the `com.apple.developer.networking.multicast` entitlement to be granted to the signing
team. Simulator compilation can be checked without signing:

```sh
./scripts/configure-ios.sh --simulator
cmake --build build-ios-simulator --config Debug --target YarmiStation -- \
  -destination 'generic/platform=iOS Simulator' CODE_SIGNING_ALLOWED=NO
```

Device and simulator builds use separate directories because CMake selects the appropriate static
library from LinkKit's XCFramework when it configures the Xcode project.

For offline or local dependency development, pass `YARMI_JUCE_SOURCE_DIR`,
`YARMI_LIBPD_SOURCE_DIR`, `YARMI_LINK_SOURCE_DIR`, and (on iOS)
`YARMI_LINKKIT_SOURCE_DIR` as CMake cache paths. See [THIRD_PARTY.md](THIRD_PARTY.md) before binary
distribution.
