# YARMI recoverability audit — 4 September 2026

Status: **YARMI repository design/handoff state reconciled.**

This is an audit snapshot, not a new authority layer. `DECISIONS.md` remains the controlling design record and `AGENTS.md` defines precedence/read order.

## Purpose

A new session/model should be able to continue YARMI without access to the conversation that produced the current design. This audit checks each material decision against an explicit repository location.

## Decision persistence matrix

| Decision | Persisted in |
|---|---|
| YARMI remains YARMI, not generic distributed-music middleware | `DECISIONS.md` D2; `ARCHITECTURE.md`; `README.md`; `AGENTS.md` |
| Station is a first-class YARMI concept | `DECISIONS.md` D2; `ARCHITECTURE.md`; `SEMANTICS.md`; `FIRST-STATION.md` |
| Every station is augmented; AR technique itself is replaceable | `DECISIONS.md` D3; `ARCHITECTURE.md`; `PLAYABILITY.md`; `README.md` |
| Audience intelligibility is constitutive / reason for YARMI | `DECISIONS.md` D4; `PLAYABILITY.md` §1–2; `ARCHITECTURE.md`; `FIRST-STATION.md`; `AGENTS.md` |
| Performer and audience views may differ but public rendering is required | `DECISIONS.md` D4; `ARCHITECTURE.md`; `SEMANTICS.md`; `FIRST-STATION.md` |
| Architecture remains intelligible/open/coherent; avoid speculative generality | `DECISIONS.md` D0/D17; `AGENTS.md`; `DEVELOPMENT.md` |
| Development loop is implement → play → observe → revise | `DECISIONS.md` D0; `PLAYABILITY.md`; `DEVELOPMENT.md`; `AGENTS.md` |
| Historical YARMI has no automatic design authority | `DECISIONS.md` D1/Historical sources; `AGENTS.md`; `WORK-ADMIN.md` |
| First canonical station = revised original YARMI, not archival recreation | `DECISIONS.md` D5; `FIRST-STATION.md`; `ARCHITECTURE.md`; `README.md` |
| Tracks may be freely/geometrically arranged rather than fixed grid rows | `DECISIONS.md` D6; `FIRST-STATION.md` Tracks |
| First track representation = arbitrary-position/orientation line segment; curves later | `DECISIONS.md` D6; `FIRST-STATION.md`; `DEVELOPMENT.md` |
| Track geometry and musical period are independent | `DECISIONS.md` D6; `FIRST-STATION.md`; `SEMANTICS.md` |
| Historical-style track-start manipulation may control bars/period through a binding | `FIRST-STATION.md` Track period; `DEVELOPMENT.md` step 7 |
| Visible current-time cursor is required in first station | `FIRST-STATION.md`; `DECISIONS.md` D5; `DEVELOPMENT.md` |
| Sequenced organisation and immediate/direct musical action must coexist | `PLAYABILITY.md` §3–4; `FIRST-STATION.md`; `DECISIONS.md` D5 |
| Track-local effects and station/global controls are part of first station | `FIRST-STATION.md`; `DECISIONS.md` D5; `DEVELOPMENT.md` |
| Direct manipulation of musical things is preferred | `PLAYABILITY.md` §5; `FIRST-STATION.md` |
| Additional controls may expose additional parameters | `PLAYABILITY.md` §6; `DECISIONS.md` D7; `FIRST-STATION.md`; `MANIPULATORS.md` |
| Manipulator is the chosen control-source term | `DECISIONS.md` D7; `MANIPULATORS.md`; `SEMANTICS.md`; `README.md` |
| Rotation is only one possible Manipulator channel | `DECISIONS.md` D7; `MANIPULATORS.md`; `PLAYABILITY.md` §7 |
| Any suitable physical object can be assigned to any compatible manipulable element/parameter | `DECISIONS.md` D8; `MANIPULATORS.md`; `FIRST-STATION.md` |
| Markerless identity is runtime instance acquisition, not semantic object recognition | `DECISIONS.md` D8; `MANIPULATORS.md`; `DEVELOPMENT.md` step 6 |
| Observable asymmetry, not geometric asymmetry, governs usable rotation tracking | `DECISIONS.md` D8; `MANIPULATORS.md` Runtime assignment / suitability |
| Symmetric/unobservable objects are an acceptable constraint rather than something to fake | `DECISIONS.md` D8; `MANIPULATORS.md`; `PLAYABILITY.md` tracking-failure rule |
| Manipulator v0 = select object, region/mask, feature tracking, translation/scale/in-plane rotation if reliable; depth when available | `DECISIONS.md` D8; `MANIPULATORS.md`; `DEVELOPMENT.md` step 6 |
| Tracking confidence/channel suitability must be visible | `MANIPULATORS.md`; `PLAYABILITY.md` §12; `FIRST-STATION.md` milestone |
| Universal arbitrary-object 6-DoF is explicitly not a first requirement | `DECISIONS.md` D8; `MANIPULATORS.md`; `DEVELOPMENT.md` decision gates; `ARCHITECTURE.md` deferred envelope |
| Native target horizon = iPhone/iPad, Android, macOS, Windows, Linux | `DECISIONS.md` D9; `README.md`; `AGENTS.md`; `DEVELOPMENT.md` |
| JUCE = first portable process/audio/MIDI host, not station ontology or mandatory AR UI | `DECISIONS.md` D10; `ARCHITECTURE.md`; `AGENTS.md`; `DEVELOPMENT.md` |
| openFrameworks/native ARKit/ARCore/headset runtimes remain possible manifestation runtimes | `DECISIONS.md` D10; `ARCHITECTURE.md`; `README.md` |
| libpd = first local DSP backend behind replaceable output boundary | `DECISIONS.md` D11; `ARCHITECTURE.md`; `DEVELOPMENT.md` |
| VST/audio endpoint host location is irrelevant to YARMI semantics | `DECISIONS.md` D12; `ARCHITECTURE.md`; `PROTOCOL.md`; `DEVELOPMENT.md` step 10 |
| DAWs are optional integration environments/components, never YARMI dependencies | `DECISIONS.md` D12; `ARCHITECTURE.md`; `PROTOCOL.md`; `README.md` |
| Ableton Live and standalone Pd are not dependencies | `DECISIONS.md` D12; `ARCHITECTURE.md` |
| Ableton Link = first shared timing substrate, not protocol or authority | `DECISIONS.md` D13; `ARCHITECTURE.md`; `PROTOCOL.md`; `SEMANTICS.md` |
| Track phases/periods derive from shared/absolute musical time, not a fixed four-beat Link quantum | `DECISIONS.md` D13; `ARCHITECTURE.md`; `SEMANTICS.md`; `FIRST-STATION.md`; `DEVELOPMENT.md` |
| No authority subsystem in first iteration | `DECISIONS.md` D14; `PROTOCOL.md`; `SEMANTICS.md`; `DEVELOPMENT.md` |
| Future authority must permit leaderless/fixed/dynamic/multiple/hierarchical/domain/subensemble forms | `DECISIONS.md` D14; `ARCHITECTURE.md`; `AGENTS.md`; `DEVELOPMENT.md` |
| No general semantic networking until musical use needs it | `DECISIONS.md` D15; `PROTOCOL.md`; `DEVELOPMENT.md` |
| Future YARMI semantic protocol = minimal, versioned and transport-independent | `DECISIONS.md` D15; `ARCHITECTURE.md`; `PROTOCOL.md` |
| OSC is an interoperability adapter candidate, not YARMI itself | `DECISIONS.md` D15; `PROTOCOL.md`; `AGENTS.md` |
| `codex/playable-prototype-v0` must not be merged wholesale | `DECISIONS.md` D16; `PROTOTYPE-V0-AUDIT.md`; `AGENTS.md`; `WORK-ADMIN.md`; `DEVELOPMENT.md` |
| Useful prototype infrastructure can be selectively ported | `PROTOTYPE-V0-AUDIT.md`; `DECISIONS.md` D16; `DEVELOPMENT.md` |
| Existing 4×16 grid may become a `GridSequencer` component, not YARMI core | `DECISIONS.md` D16; `FIRST-STATION.md`; `ARCHITECTURE.md`; `PROTOTYPE-V0-AUDIT.md` |
| Tiny iOS proof is disposable and not sufficient as canonical YARMI2 station | `apps/ios-proof/README.md`; `WORK-ADMIN.md`; `DEVELOPMENT.md` |
| Display-frame timing in tiny iOS proof must not become musical scheduling | `apps/ios-proof/README.md`; `WORK-ADMIN.md`; `PROTOTYPE-V0-AUDIT.md`; `SEMANTICS.md` |
| 2009 YARMI paper remains historical design evidence | `DECISIONS.md` Historical sources; `WORK-ADMIN.md` |
| 2011 *A New Iteration of YARMI* recovered in academic-writing archive | `DECISIONS.md` Historical sources; `WORK-ADMIN.md`; verified in `krahd/research/academic-writing/my_papers/2011 - A New Iteration of YARMI/` |
| Unknown legacy `yarmi - isea2011.docx` is not silently reclassified | preserved by leaving it in historical inventory; relationship remains unresolved rather than invented |

## Current implementation handoff

Follow `DEVELOPMENT.md`. The immediate progression is:

1. device-validate the tiny iOS AR proof;
2. selectively port infrastructure from `codex/playable-prototype-v0` without merging it;
3. implement the revised-original station-local model;
4. establish generic output endpoint boundaries and libpd first;
5. implement augmented performer/audience rendering;
6. implement markerless Manipulator v0;
7. complete sequenced + immediate + effects + direct-manipulation behaviour;
8. integrate Link from shared/absolute musical time;
9. play/revise repeatedly;
10. prove host-agnostic external VST control;
11. run multiple Link-synchronised stations;
12. add semantic networking only when a musical requirement demands it;
13. revisit the grid only as an optional component;
14. expand target-platform validation.

## Known external/cross-repository reconciliation issue

The **YARMI repository itself is reconciled**. The cross-domain human record `krahd/tom-work-admin/projects/yarmi.md` has also been updated.

However, `krahd/tom-work-admin/registry/projects.yaml` still contains an older `project-yarmi.action`/`notes` block. `krahd/tom-work-admin/registry/ADMIN-REPAIRS-2026-09-03-YARMI.md` explicitly marks that entry stale, records the current replacement action and instructs agents not to let it override `krahd/YARMI` or `projects/yarmi.md`.

This remaining admin-registry edit is a known reconciliation task; it does not represent an unresolved YARMI design decision.
