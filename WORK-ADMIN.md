# YARMI — work administration

- **Canonical project repository:** `krahd/YARMI`
- **Canonical project identity:** `krahd/tom-work-admin/registry/projects.yaml`
- **Human cross-domain record:** `krahd/tom-work-admin/projects/yarmi.md`
- **Current status:** active; portable JUCE/libpd/Link station prototype implemented and runtime-smoke-tested on macOS and iPad Simulator; local two-process Link discovery verified; physical-iPad and cross-device playing sessions pending
- **Working names:** YARMI 2.0 / YARMI 2026; final public title not fixed
- **Type:** artwork / software / computer-music / interaction-research project

## Relationship to historical YARMI

The project is a conceptual continuation and new implementation of the earlier YARMI augmented-reality musical instrument. The historical implementation is not authoritative for current semantics or architecture.

If recovered, old code is archaeological/historical evidence only. Do not inherit code, semantics, mappings, Pd organisation, networking, station roles, zones, visual language, or student implementation decisions automatically.

## Governing development method

YARMI is developed through musical use:

```text
implement -> play -> observe -> revise -> play again
```

Architecture is also allowed to change. Do not implement speculative generality merely because a future distributed musical system could need it.

Tomas Laurenzo is the principal initial performer/designer; sustained first-person musical use is valid evidence for early design/architecture decisions.

## Fixed choices for the first portable/playable iteration

- native platform horizon: iPhone/iPad, Android, macOS, Windows, Linux;
- semantic/core logic remains independent of physical manifestation;
- **JUCE** is the first portable application/audio/MIDI host;
- **libpd** is the first embedded DSP backend behind a replaceable `AudioBackend` boundary;
- **Ableton Link** provides all shared ensemble tempo/beat/phase timing in v0;
- **JUCE VST3 hosting** is the first desktop third-party-plugin integration route;
- Ableton Live is not a dependency;
- standalone Pd is not a dependency;
- no custom timing/synchronisation layer in v0;
- no authority/leader-management subsystem in v0;
- no general YARMI control/state network protocol until a musical behaviour requires semantic station-to-station exchange;
- openFrameworks, native AR frameworks and other render/input systems remain manifestation-specific options rather than core dependencies.

## Authority / large-schema distinction

The architecture should not make future authority structures impossible, but they are deliberately **not** v0 work.

Possible future configurations include no leader, fixed leader, dynamic leader assignment, several leaders, domain-specific leaders, hierarchical leaders/subleaders and subensemble/local authority.

Implement authority only if playability produces a concrete recurring need. The large-schema capability space is documented in `docs/DECISIONS.md`, `docs/ARCHITECTURE.md`, and `docs/DEVELOPMENT.md` so it is preserved without becoming premature implementation work.

## Physicality rule

YARMI's core must remain agnostic to markers, arbitrary objects, hands/body, touch, cameras, projectors, phones/tablets, AR glasses, VR/XR, haptics, MIDI/OSC controllers and other physical/interface modalities.

Spatial metadata is optional. Physical manifestations are adapters around the musical/station semantics, not the definition of the instrument.

## Existing iOS/iPadOS existence proof

`apps/ios-proof/` is a deliberately small Apple-native AR manifestation. It is disposable prototype code rather than the future portable runtime.

It currently demonstrates the narrow historical echo:

1. tap to place the beginning of a track in physical space;
2. tap again to place its end;
3. see the track and moving time cursor;
4. tap to place note/sample entities projected onto the track;
5. hear notes triggered as the cursor crosses them.

It uses SwiftUI + RealityKit/ARKit and a temporary `AVAudioEngine` sine-tone backend.

**Verification:** GitHub Actions `iOS proof build`, run 33808267591, compiled `YARMI2Proof` successfully for the iOS Simulator. Physical-device AR behaviour remains unverified.

The proof does **not** establish tracks, samples, this interaction grammar, or Apple-native architecture as YARMI 2 semantics.

## Immediate implementation sequence

The authoritative detailed handoff is `docs/DEVELOPMENT.md`.

In brief:

1. run the existing iOS proof on a physical iPhone/iPad and fix only proof-blocking defects;
2. establish the portable JUCE/CMake station shell;
3. define the minimum `AudioBackend` boundary and implement libpd first;
4. instrument sample rate, buffer size, latency/xrun/callback behaviour from the beginning;
5. integrate Ableton Link as the complete v0 timing service;
6. make one station genuinely playable with the simplest useful manifestation;
7. run at least two independent stations/devices sharing Link timing and test ad-hoc join/leave;
8. conduct repeated real playing sessions and record concise playability observations;
9. revise semantics/architecture only in response to those observations or concrete portability/reliability requirements;
10. add JUCE VST3 hosting on desktop once the local audio/timing loop is stable enough to play;
11. introduce YARMI semantic networking only when an actual musical interaction needs more than shared Link timing;
12. establish cross-platform compile/smoke-test coverage early enough to catch platform assumptions.

## Current manifestation directions

Candidate manifestations, none canonical:

- Spatial YARMI: virtual musical nodes/entities placed/manipulated in 3D space;
- Object YARMI: arbitrary physical objects instantiated as musical entities/stations and computationally/visually augmented;
- combined object-plus-spatial structures;
- touch, projection, hands/body, AR glasses, VR/XR, tactile/haptic and other interfaces.

## Current opportunity relationship

CTM 2027 — *Resynthesising the Traditional: At the Extreme* is an active opportunity in which materially new 2026 YARMI work may become relevant. The project remains independent of that call.

## Canonical development documents

- `README.md`
- `docs/DECISIONS.md`
- `docs/ARCHITECTURE.md`
- `docs/SEMANTICS.md`
- `docs/PROTOCOL.md`
- `docs/DEVELOPMENT.md`

For Codex/Claude implementation work, read `docs/DEVELOPMENT.md` and `docs/DECISIONS.md` before changing architecture.

`krahd/tom-work-admin` is the canonical cross-domain administration/ledger repository; there is no separate canonical `tom-main-work` repository.
