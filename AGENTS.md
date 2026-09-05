# AGENTS.md — YARMI

This repository must be recoverable without chat history. Before changing YARMI code, architecture, semantics, interaction design or implementation priorities, read in this order:

1. `docs/DECISIONS.md` — controlling design decisions.
2. `docs/FIRST-STATION.md` — current canonical station to implement.
3. `docs/PLAYABILITY.md` — constitutive playability and audience-legibility constraints.
4. `docs/MANIPULATORS.md` — manipulator concept and fiducial-less object strategy.
5. `docs/ARCHITECTURE.md` — current decomposition and deferred design envelope.
6. `docs/DEVELOPMENT.md` — current implementation sequence.
7. `docs/PROTOTYPE-V0-AUDIT.md` — what may and may not be reused from the Codex prototype branch.
8. `docs/PROTOCOL.md` and `docs/SEMANTICS.md` — deliberately minimal coordination/network semantics.
9. `WORK-ADMIN.md` — cross-repository ownership/status.

Also follow the hard public-facing-file rule in `krahd/tom-work-admin/PUBLIC-FACING-FILE-SAFETY.md` whenever creating any text intended for publication, submission, portfolio use, a public project page, CV, proposal or other external delivery.

## Decision precedence

If repository documents disagree, use this order:

1. direct current instruction from Tomas Laurenzo;
2. `docs/DECISIONS.md`;
3. `docs/FIRST-STATION.md`, `docs/PLAYABILITY.md`, `docs/MANIPULATORS.md`;
4. `docs/ARCHITECTURE.md`;
5. `docs/DEVELOPMENT.md`;
6. `docs/PROTOCOL.md` / `docs/SEMANTICS.md`;
7. `WORK-ADMIN.md`;
8. `README.md` as public orientation only.

Do not leave contradictions behind. A material decision change must update every affected controlling/handoff document in the same work session.

## Current non-negotiable direction

- YARMI is an **ensemble of augmented musical stations**. Station is a first-class YARMI concept.
- A station is not defined by one device, one process, one sensing technology, one audio engine, one performer or one internal musical design.
- **Audience intelligibility is constitutive.** A station must make consequential performer action, computational transformation and musical consequence publicly observable. Performer and audience views may differ.
- The first canonical station is a **revised original-YARMI station**, not an archival recreation.
- The first station uses freely arranged tracks, explicit musical periods independent of geometry, visible current-time cursors, track components/effects, immediate components/effects, global/station controls and manipulators.
- A **Manipulator** is a performer-controlled source bound to a manipulable musical element/parameter. Rotation is only one possible channel.
- Runtime-selected arbitrary physical objects can become manipulators without semantic object recognition, subject to observable-feature/confidence constraints.
- The existing `codex/playable-prototype-v0` branch is a technology spike. **Do not merge it wholesale.** Reuse infrastructure selectively; the 4×16 grid may later become a station component.
- JUCE is a useful portable process/audio/MIDI host, not the ontology of a station. Native ARKit/ARCore, openFrameworks or other manifestation-specific runtimes may coexist.
- libpd is the first local DSP candidate behind a replaceable output boundary.
- YARMI must be able to control VST/other sound endpoints **without caring where they are hosted**.
- Ableton Link is the first shared timing substrate; consume shared/absolute musical time and derive station-specific periods locally. Link is not authority or the YARMI protocol.
- No authority subsystem, broad replication framework or universal control protocol is implemented until musical use requires it; future architecture must not preclude leaderless, fixed/dynamic/multiple/hierarchical/domain-specific leadership.
- If semantic networking becomes necessary, define YARMI semantics independently of transport; OSC is an adapter candidate, not YARMI itself.
- Required native platform horizon: iPhone/iPad, Android, macOS, Windows, Linux.
- Historical YARMI code and student implementation decisions are evidence only. Nothing is inherited automatically.

## Governing method

```text
implement -> play -> observe -> revise -> play again
```

Do not aim for a universal distributed-music framework. Keep the architecture intelligible, open and coherent; add abstraction only when a concrete musical, portability, reliability or integration requirement earns it.
