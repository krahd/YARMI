# YARMI design decisions

This file records current decisions and explicitly open choices. Historical YARMI decisions are not presumed valid.

## Fixed architectural decisions

### D1 — From-scratch implementation

YARMI 2.0 / YARMI 2026 is implemented from scratch. Historical code may be recovered and studied, but no code, semantics, mapping or architecture is inherited automatically.

### D2 — Physicality-agnostic core

The core does not assume markers, tables, cameras, touchscreens, objects, hands, projections, AR, VR/XR, haptics, coordinates or any other manifestation.

### D3 — Authority is orthogonal to stations

Leadership/authority is a policy over named coordination domains, not a station property. The model must represent leaderless, fixed-leader, dynamically assigned, multi-leader, hierarchical/subleader and mixed/domain-specific configurations without changing the station abstraction.

### D4 — Semantic protocol independent of wire protocol

YARMI defines its own versioned typed semantic protocol. OSC is an interoperability adapter, not the canonical schema. Transport choice remains replaceable.

### D5 — Timing independent of authority and control protocol

Shared musical timing is a service. Ableton Link is a strong candidate for beat/tempo/phase synchronisation, but using Link must not define authority or ensemble control semantics.

### D6 — DAWs and plug-ins are optional participants

Commercial DAWs such as Ableton Live may participate through timing, MIDI/audio/control, plugin-host or dedicated adapters. They are never required for YARMI operation and do not define the core.

### D7 — Audio backends replaceable

The audio interface must permit embedded libpd, native JUCE/C++ DSP, external DAW/plugin processing, and future engines. Audio backends do not own ensemble state or networking.

### D8 — Native cross-platform target

The architecture must support native applications on iPhone/iPad, Android, macOS, Windows and Linux.

## Current leading implementation hypotheses — not fixed

- JUCE as the default cross-platform application/audio/MIDI host.
- libpd as an initial rapid-composition audio backend behind a stable interface.
- native JUCE/C++ DSP as a parallel or later backend.
- openFrameworks as an optional graphics/CV/creative-coding manifestation layer.
- OSC as the first external control interoperability adapter.
- Ableton Link as an optional shared musical-time adapter.
- VST3 as the first desktop plugin/DAW format because of broad host support and its current MIT-licensed SDK.
- AU/AUv3 adapters for Apple platforms where useful.
- CLAP evaluated as an additional modern desktop plugin interface; it is not required for the first prototype.

## Explicitly open

- canonical musical entity model;
- whether tracks/sequencers exist at all in the new semantic core;
- synthesis and processing model;
- audio backend chosen for the first playable manifestation;
- rendering framework per manifestation;
- first network transport after local/in-process testing;
- precise conflict semantics for simultaneous authorities;
- initial discovery mechanism;
- whether YARMI hosts third-party plugins in the first release;
- whether YARMI itself ships as plugin formats in the first release;
- first physical manifestation: spatial AR, arbitrary-object augmentation, touch, conventional desktop/mobile, or another form;
- final public title/version naming.

## Historical-material rule

When the old codebase is recovered, review decisions under three labels only:

- `historical-observation` — what the system actually did;
- `candidate` — a behaviour worth reconsidering;
- `rejected` — a behaviour we deliberately do not carry forward.

No historical behaviour becomes `current` merely because it existed.
