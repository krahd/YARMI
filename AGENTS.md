# AGENTS.md — YARMI

Before changing YARMI code, architecture or semantics, read in this order:

1. `docs/DEVELOPMENT.md`
2. `docs/DECISIONS.md`
3. `docs/ARCHITECTURE.md`
4. `docs/SEMANTICS.md`
5. `docs/PROTOCOL.md`
6. `WORK-ADMIN.md`

## Controlling current direction

YARMI 2.0 / YARMI 2026 is a from-scratch, playability-driven contemporary continuation of historical YARMI.

The first portable/playable iteration currently fixes:

- JUCE as native cross-platform application/audio/MIDI host;
- libpd as the first DSP backend behind a replaceable interface;
- Ableton Link for all v0 ensemble tempo/beat/phase synchronisation;
- JUCE VST3 hosting as the first desktop third-party-plugin path;
- no dependency on Ableton Live or standalone Pd;
- no custom clock in v0;
- no authority/leader-management subsystem in v0;
- no general YARMI control/state network protocol until an actual musical interaction requires one;
- no fixed physical/UI modality in the semantic core.

## Development rule

```text
implement -> play -> observe -> revise -> play again
```

Architecture is provisional. Do not implement speculative distributed-system complexity merely because it might be useful later.

Preserve replaceability at genuinely volatile boundaries, but prefer the smallest implementation that makes the instrument playable.

## Large-schema warning

`docs/DEVELOPMENT.md` and `docs/DECISIONS.md` preserve a broader future design envelope: arbitrary authority topologies, alternate timing backends, discovery, shared-state replication, capabilities, persistence, multiple transports, heterogeneous stations, and many physical manifestations.

These are **not a v0 implementation backlog**. Implement them only when musical use or a concrete technical requirement justifies them.

## Historical YARMI

If historical source code is recovered, treat it as archaeological evidence only. Do not copy architecture, semantics, mappings, Pd organisation, station roles, networking or student implementation decisions into the new codebase by default.

## Existing iOS proof

`apps/ios-proof/` is disposable SwiftUI/RealityKit/ARKit existence-proof code. Validate it on hardware, but do not turn it into the portable architecture.

## Primary implementation handoff

For the exact immediate order of work, success conditions, real-time measurements and decision gates, follow `docs/DEVELOPMENT.md`.
