# YARMI protocol — deferred design basis

Status: **not a v0 wire specification**.

The first playable YARMI iteration uses Ableton Link for shared musical timing and does not require a general-purpose YARMI control/state network merely to satisfy architectural completeness.

## Current rule

Do not design or implement a broad distributed protocol before a musical behaviour needs semantic station-to-station exchange.

When that need appears:

1. identify the exact musical interaction;
2. identify the smallest shared state/actions needed;
3. define timing, ordering, identity and failure behaviour required by that interaction;
4. implement the minimum transport-independent semantic contract;
5. choose a transport/encoding appropriate to the measured requirement;
6. play it and revise.

## Link is timing, not the YARMI protocol

Ableton Link is the complete v0 ensemble tempo/beat/phase synchronisation substrate. It does not define YARMI musical entities or station control.

A first ensemble may therefore consist of several independent YARMI stations that share Link timing but exchange no YARMI semantic messages at all.

That is a valid v0 architecture.

## Future semantic protocol principle

If/when station-to-station control or shared state is needed, YARMI should define a versioned semantic contract independently of a particular wire technology.

Potential concepts include:

- station identity;
- entity/action identity;
- musical-time annotations;
- shared state snapshots or deltas;
- ordering/idempotence requirements;
- membership/discovery information;
- capability information;
- later, only if needed, authority relations.

These are candidate requirements, not mandatory message families.

## OSC

OSC remains a strong interoperability candidate because of its broad use in computer music.

Do not define YARMI itself as an OSC address tree. If OSC is adopted, it should encode the semantic messages required by the current musical interaction.

OSC is not automatically the first control transport; its use should be justified by the first real networked interaction.

## Local/in-process path

Local calls or IPC may implement the same musical actions without networking. This remains useful for tests, single-device components and simulated multi-station work.

## Future transport questions

Only answer these when measurements/use cases require them:

- reliable versus unreliable delivery;
- UDP/TCP/QUIC/WebSocket/other transport;
- discovery mechanism;
- NAT/remote performance requirements;
- retransmission;
- state replication;
- persistence/session recovery;
- conflict resolution;
- capability negotiation.

## Authority — deliberately absent from v0 protocol

Do not implement authority grants, leases, leader elections, revocation, consensus or hierarchical control in the initial protocol.

If musical use later shows that Link's egalitarian control model creates a real problem, authority can be introduced as a semantic extension. The architecture preserves the possibility of fixed, dynamic, multiple, hierarchical and domain-specific authority without pre-building it.

## DAW/plugin boundary

VST3, AU/AUv3, LV2/CLAP and DAW APIs are integration surfaces, not YARMI network transports.

For the first desktop integration, JUCE may host VST3 instruments/effects locally. Ableton Live may participate through Link without becoming a YARMI dependency.

## Compatibility principle

A YARMI manifestation should remain recognisably the same musical system if:

- libpd is replaced by another audio backend;
- one physical interface is replaced by another;
- a future control transport is replaced;
- a DAW/plugin integration is absent.

This compatibility principle is more important than preserving any particular speculative protocol schema.
