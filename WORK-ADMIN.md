# YARMI — work administration

- **Canonical project repository:** `krahd/YARMI`
- **Canonical project identity:** `krahd/tom-work-admin/registry/projects.yaml`
- **Human cross-domain record:** `krahd/tom-work-admin/projects/yarmi.md`
- **Status:** active; current architecture/playability/manipulator decisions reconciled in repository; tiny iOS AR proof compile-verified but not device-validated; first canonical revised-original station not yet implemented
- **Working name:** YARMI / YARMI 2
- **Type:** artwork / software / computer-music / interaction-research project

## Current project identity

YARMI is an ensemble of **augmented musical stations** built around direct manipulation and audience-intelligible musical causality. Station is a first-class concept; a logical station may span multiple devices/processes and its internal musical design remains open.

Audience intelligibility is constitutive. A station needs a public/audience manifestation of consequential performer action and musical/computational state.

Historical YARMI is lineage/evidence, not an implementation specification.

## Canonical design/handoff documents

Read `AGENTS.md` first. The controlling/current documents are:

- `docs/DECISIONS.md`
- `docs/FIRST-STATION.md`
- `docs/PLAYABILITY.md`
- `docs/MANIPULATORS.md`
- `docs/ARCHITECTURE.md`
- `docs/DEVELOPMENT.md`
- `docs/PROTOTYPE-V0-AUDIT.md`
- `docs/PROTOCOL.md`
- `docs/SEMANTICS.md`

`README.md` is public project orientation and must not be used as the sole implementation handoff.

## Current first station

The first canonical station is a **revised original YARMI design**, not an archival recreation. It starts with freely arranged line-segment tracks, explicit periods independent of geometry, visible cursors, track sound/event components, track-local effects, immediate interaction, station/global controls, Manipulator bindings, and performer/audience rendering.

The markerless direction lets a performer select a suitable arbitrary visible object at runtime and use it as a Manipulator without semantic category recognition. First reliable channels are translation, scale and in-plane rotation where observable, with depth/world position where available.

## Existing prototypes

### Tiny iOS AR proof on `main`

`apps/ios-proof/` remains disposable existence-proof code. GitHub Actions run `33808267591` compiled it for iOS Simulator. Physical-device AR behaviour is still unverified. Its `CADisplayLink`/display-frame scheduling must not become the musical scheduler.

### Codex portable prototype branch

`codex/playable-prototype-v0` (audited commit `0daf7a19c6c088cc425f7cc1bd2b198d2ca4e5c5`) is a preserved technology spike.

**Do not merge it wholesale.** Selectively port useful CMake/JUCE/libpd/Link/diagnostic/CI work. The grid may become a station component; grid semantics do not become YARMI core.

## Current implementation sequence

`docs/DEVELOPMENT.md` is authoritative. In brief:

1. device-validate the tiny AR proof;
2. preserve/freeze the Codex prototype and selectively port infrastructure only;
3. implement the revised-original station-local model;
4. create generic output/end-point boundaries and local libpd path;
5. build the augmented performer/audience rendering;
6. implement markerless Manipulator v0 (runtime object acquisition + reliable channels/confidence);
7. complete track/immediate/effect/direct-manipulation behaviour;
8. integrate Link using shared/absolute musical time and station-specific periods;
9. play/revise repeatedly;
10. prove host-agnostic control of an external VST endpoint;
11. run two or more Link-synchronised stations;
12. add YARMI semantic networking only when a musical interaction needs it;
13. revisit the grid only as an optional station component;
14. expand cross-platform validation across iOS/iPadOS, Android, macOS, Windows, Linux.

## Historical sources

- 2009: *YARMI: An Augmented Reality Musical Instrument* — primary original-design source.
- 2011: *A New Iteration of YARMI* — recovered under `krahd/research/academic-writing/my_papers/2011 - A New Iteration of YARMI/` (PDF + Spanish Word source).

## Current opportunity relationship

CTM 2027 — *Resynthesising the Traditional: At the Extreme* remains an active opportunity. YARMI is independent of that application; the call must not distort the project architecture.

## Cross-repository note

`krahd/tom-work-admin` is the cross-domain administration system of record. Any stale YARMI action/notes there must be reconciled when project state changes; the YARMI repository controls substantive implementation/design state.
