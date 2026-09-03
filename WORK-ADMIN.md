# YARMI — work administration

- **Canonical project repository:** `krahd/YARMI`
- **Canonical project identity:** `krahd/tom-work-admin/registry/projects.yaml`
- **Human cross-domain record:** `krahd/tom-work-admin/projects/yarmi.md`
- **Current status:** active; architecture/protocol design and from-scratch implementation start
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
- DAWs, VST3/AU/CLAP plug-ins, external plugin hosts, MIDI and other musical systems are potential adapters/components rather than architectural dependencies;
- no historical YARMI semantic or implementation decision is inherited automatically.

## Current opportunity relationship

CTM 2027 — *Resynthesising the Traditional: At the Extreme* is an active opportunity in which a materially new 2026 YARMI manifestation may become relevant if sufficient current work exists before the deadline. The project remains independent of that call.

## Next actions

1. Define the minimal semantic model for ensemble, station, state, action, timing, authority and musical entities.
2. Define the versioned YARMI protocol independently of wire transport.
3. Prototype one transport adapter, likely OSC first for interoperability, without making OSC semantics canonical.
4. Evaluate JUCE+libpd and native JUCE/C++ DSP with identical backend interfaces.
5. Define optional Ableton Link integration for beat/tempo/phase.
6. Define DAW/plugin adapters separately from standalone station operation.
7. Recover the historical codebase if available and archive observations without importing code or semantics by default.

`krahd/tom-work-admin` is the canonical cross-domain administration/ledger repository; there is no separate canonical `tom-main-work` repository.
