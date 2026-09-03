# YARMI — work administration

- **Canonical project repository:** `krahd/YARMI`
- **Canonical project identity:** `krahd/tom-work-admin/registry/projects.yaml`
- **Human cross-domain record:** `krahd/tom-work-admin/projects/yarmi.md`
- **Current status:** active; minimal semantics defined; first iOS/iPadOS AR existence proof compile-verified; real-device AR validation pending
- **Working names:** YARMI 2.0 / YARMI 2026; final public title not fixed
- **Type:** artwork / software / computer-music / interaction-research project

## Relationship to historical YARMI

The project is a conceptual continuation and new implementation of the earlier YARMI augmented-reality musical instrument. The historical implementation is not authoritative for current semantics or architecture. If recovered, it is evidence to inspect, not a codebase to modernise by default.

Historical sources include the 2009 YARMI paper and the 2011 iteration. They document a collaborative networked tangible musical instrument with synchronised stations, but current YARMI reopens every design decision.

## Current architectural commitments

- cross-platform native targets: iOS/iPadOS, Android, macOS, Windows, Linux;
- framework-independent semantic core;
- station semantics independent of physical manifestation;
- authority/leadership represented as configurable policy over coordination domains rather than a station property;
- transport-independent typed YARMI protocol, with OSC as an adapter candidate;
- timing/synchronisation separated from authority, with Ableton Link as a candidate timing substrate;
- audio backend replaceable; libpd and native JUCE/C++ DSP remain open candidates;
- JUCE is the current leading candidate for the default cross-platform application/audio host; openFrameworks remains a candidate for graphics/interaction manifestations rather than the semantic core;
- DAWs, VST3/AU/AUv3/CLAP plug-ins, external plugin hosts, MIDI and other musical systems are potential adapters/components rather than architectural dependencies;
- YARMI may control a VST instrument without caring which compliant host actually owns/instantiates that plug-in; DAW/plugin host identity is outside the semantic core;
- no historical YARMI semantic or implementation decision is inherited automatically.

## Minimal semantics v0.0.1

`docs/SEMANTICS.md` defines the first compact formal model:

```text
E = (S, X, P, τ)
```

with stations `S`, entity state `X`, authority policies `P`, and optional musical time `τ`. Semantic change is expressed as actions reduced by a transport-independent state transition. Physical interaction, rendering, sound, network transport and DAW integration are adapters around this state model.

## First existence proof

`apps/ios-proof/` is a deliberately small Apple-native AR manifestation. It is disposable prototype code rather than the future portable runtime.

The proof recreates only the smallest recognisable documented historical YARMI interaction:

1. tap to place the beginning of a track in physical space;
2. tap again to place its end;
3. see the track and explicit moving time cursor;
4. tap to place note/sample entities projected onto the track;
5. hear notes triggered as the cursor crosses them.

It uses SwiftUI + RealityKit/ARKit and a temporary `AVAudioEngine` sine-tone backend. It deliberately excludes networking, OSC, Link, libpd, JUCE, VST/DAW integration and old YARMI semantics.

**Verification:** GitHub Actions `iOS proof build`, run 33808267591, compiled `YARMI2Proof` successfully for the iOS Simulator on macOS. Physical-device AR behaviour remains unverified until run on an iPhone/iPad.

## Current opportunity relationship

CTM 2027 — *Resynthesising the Traditional: At the Extreme* is an active opportunity in which this materially new 2026 YARMI work may become relevant. The project remains independent of that call.

## Next actions

1. **Run the compile-verified existence proof on a physical iPhone/iPad.** Confirm plane detection, track placement, cursor motion, note creation and sound triggering.
2. Fix only defects that prevent the existence proof from satisfying that narrow behaviour; do not grow the Swift prototype into the architecture.
3. Return to the portable runtime: implement the minimal semantic reducer independently of UI/AR framework.
4. Prototype local multi-station behaviour before networking.
5. Add an OSC interoperability adapter and optional Ableton Link timing adapter only after local semantics are stable.
6. Evaluate JUCE+libpd and native JUCE/C++ DSP with identical backend interfaces.
7. Define DAW/plugin control adapters, including the ability for YARMI to drive an externally hosted VST instrument without requiring YARMI to know which host owns it.
8. Recover the historical codebase if available and archive observations without importing code or semantics by default.

`krahd/tom-work-admin` is the canonical cross-domain administration/ledger repository; there is no separate canonical `tom-main-work` repository.
