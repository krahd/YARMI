# YARMI protocol — deferred, transport-independent design basis

Status: no general YARMI control/state wire protocol is required for the first playable station.

## Current rule

Do not design a broad distributed protocol before a musical behaviour requires semantic station-to-station exchange.

When that need appears:

1. identify the exact musical interaction;
2. identify the smallest shared identities/state/actions needed;
3. define musical-time, ordering and failure behaviour;
4. define a transport-independent semantic contract;
5. choose an encoding/transport appropriate to the measured requirement;
6. play it and revise.

## Ableton Link

Link supplies shared tempo/beat timing for the first ensemble. It is **not** the YARMI semantic/control protocol and it is not an authority mechanism.

Stations derive their own track/phrase periods from shared/absolute musical time; a fixed Link quantum does not define YARMI metre or track length.

Several independent stations sharing only Link timing are a valid first ensemble.

## OSC

OSC is a strong interoperability candidate because it is widespread in computer music.

YARMI itself must not be defined as an OSC address tree. If OSC is used, it encodes YARMI semantics required by the current interaction. Another transport must be able to carry the same semantic contract without redefining the musical concept.

## Local/in-process paths

The same station/component semantics may be exercised locally without networking. Local calls/IPC are useful for tests, components and multi-process stations.

## Authority

Do not implement grants, leases, election, consensus or hierarchy in the first protocol. If authority becomes musically necessary, introduce it as a semantic extension while preserving possible leaderless, fixed, dynamic, multiple, hierarchical and domain-specific arrangements.

## DAW/plugin boundary

VST3, AU/AUv3, CLAP/LV2 and DAW APIs are integration surfaces, not YARMI network transports.

A station may control a VST synthesiser/effect without knowing which host instantiated it. YARMI may host a plugin itself, or the endpoint may live in Ableton, Reaper, Bitwig, another host/process or hardware. Host identity is outside YARMI musical semantics.

## Future questions — answer only when required

- discovery/ad-hoc membership;
- reliable versus unreliable delivery;
- scheduled future events;
- snapshots/deltas;
- ordering/idempotence/replay;
- persistence/session recovery;
- remote/NAT behaviour;
- capability negotiation;
- conflict semantics.

The compatibility goal is that changing transport, DSP endpoint or sensing/rendering implementation does not require redefining the station's musical behaviour.
