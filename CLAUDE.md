# CLAUDE.md — YARMI

Before implementation or architectural changes, read:

1. `docs/DEVELOPMENT.md`
2. `docs/DECISIONS.md`
3. `docs/ARCHITECTURE.md`
4. `docs/SEMANTICS.md`
5. `docs/PROTOCOL.md`
6. `WORK-ADMIN.md`

## Current project direction

YARMI 2.0 / YARMI 2026 is being implemented from scratch. Historical YARMI is conceptual/historical evidence, not a specification or base architecture.

The first portable/playable iteration uses:

- JUCE as the native cross-platform app/audio/MIDI host;
- libpd as the first embedded DSP backend behind a replaceable interface;
- Ableton Link for all v0 tempo/beat/phase synchronisation;
- JUCE VST3 hosting as the first desktop plugin-host integration;
- no dependency on Ableton Live or standalone Pd;
- no custom synchronisation layer in v0;
- no authority/leader-management subsystem in v0;
- no general YARMI semantic network protocol until a musical interaction actually needs one;
- no fixed physical/UI modality in the core.

## Development method

YARMI is playability-driven:

```text
implement -> play -> observe -> revise -> play again
```

The architecture itself may change. Do not pre-build abstractions merely because the larger design space can imagine them.

Tomas Laurenzo is the principal initial performer/designer; repeated musical use is valid evidence for changing semantics or architecture.

## Deferred design horizon

The repository deliberately records possible future authority topologies, alternate timing systems, shared state, discovery, capabilities, persistence, transports, heterogeneous station roles and physical manifestations.

Treat these as constraints against unnecessarily closing future paths, **not** as features to implement now.

## Physicality

The core must remain agnostic to markers, arbitrary objects, hands/body tracking, touch, projectors, AR, VR/XR, haptics, screens, MIDI/OSC controllers and other modalities. Spatial coordinates are optional manifestation data.

## Historical code

If old YARMI source is recovered, inspect and document it but inherit nothing automatically. In particular, do not assume the historical station roles, leader model, tracks/zones, token semantics, networking, Pd organisation or student implementation choices remain desirable.

## Existing prototype

`apps/ios-proof/` is a disposable Apple-native AR existence proof. Validate the narrow proof on hardware; do not expand it into the portable runtime.

## Handoff

`docs/DEVELOPMENT.md` is the controlling implementation roadmap, including immediate steps, real-time diagnostics, multi-station success criteria, VST-host sequencing and decision gates.
