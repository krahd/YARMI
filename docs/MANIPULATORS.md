# Manipulators

A **Manipulator** is a performer-controlled source that can be bound to one or more manipulable musical elements or parameters inside a YARMI station.

A manipulator does not imply a fiducial marker, a physical object, rotation, or any particular sensing technology. A manipulator may be realised by an arbitrary physical object selected at runtime, a traditional fiducial, a hand, touch, a virtual object, a MIDI controller, or another source.

The central relation is:

```text
performer-controlled source
        |
        v
   Manipulator
        |
   observed channels
        |
        v
     Binding
        |
        v
musical element / parameter
```

Examples of observable channels include translation, in-plane rotation, 3D orientation, distance, relative position, speed, contact, hand gesture, pressure, or a device-specific control value. No single channel is mandatory. A tracker or sensing adapter should expose only the channels it can estimate with useful confidence.

## Runtime assignment

The intended fiducial-less interaction is:

1. the performer selects a visible physical object;
2. the station acquires and tracks that physical instance;
3. the object becomes a manipulator;
4. the performer binds a supported observable channel to a manipulable musical element or parameter;
5. the augmented performer/audience representation makes the assignment and its consequences legible.

Object recognition by semantic category is not required. The selected instance is sufficient identity while tracking remains valid.

## Current technical strategy

No single current mobile technique provides robust full 6-DoF tracking of every arbitrary object under every viewing condition. YARMI therefore uses a progressive strategy rather than making full pose a prerequisite.

### Level 1 — arbitrary visible-object tracking

A user-selected object can be tracked in image space from a point, box, or mask. This is sufficient for translation, velocity, approximate scale, proximity, and—with suitable visual structure—an estimate of in-plane rotation.

A practical implementation can combine promptable segmentation on acquisition with lightweight feature/optical-flow tracking between segmentation updates. This avoids requiring a large segmentation model on every camera frame.

### Level 2 — depth-assisted manipulation

Where ARKit/ARCore depth is available, pixels belonging to the selected object can be lifted into 3D. This supports world-space position, approximate size, relative distance, and stronger separation of object movement from camera movement.

### Level 3 — object-centric 6-DoF pose

For rigid objects and hardware with suitable RGB-D data, an object-specific point cloud/model can be created from the selected object and registered against subsequent observations. This can provide full translation and orientation, but it is a higher-cost capability and is not required for an object to be a useful manipulator.

### Level 4 — persistent/reacquired objects

If a manipulator must survive long occlusion or leave/re-enter the camera view, appearance descriptors, multi-view snapshots, or a scanned/reference-object representation can be added for reacquisition. This is optional and should not complicate the first playable implementation.

## First implementation target

The first fiducial-less manipulator should deliberately be smaller than the complete research problem:

- performer taps/selects one arbitrary visible rigid object;
- the station acquires an object mask or bounding region;
- visual features inside the selected region are tracked frame-to-frame;
- a 2D similarity/affine estimate yields translation, scale, and in-plane rotation when observable;
- depth, where available, supplies world-space position;
- tracking confidence is visible;
- loss of tracking asks for re-selection rather than silently controlling the wrong object;
- any supported channel can be bound to a manipulable parameter.

This is sufficient to recover the important interaction grammar of the historical fiducials without requiring fiducials or pretending that arbitrary-object 6-DoF pose is already solved on all target hardware.

## Failure cases are part of the interface

An arbitrary object may not expose every motion perceptually. Examples include rotationally symmetric objects, textureless surfaces, reflective or transparent objects, severe occlusion, motion blur, and several nearly identical objects in one scene.

A manipulator must therefore carry tracking confidence and a set of currently usable channels. YARMI should prefer explicit loss/degradation over an apparently continuous but incorrect control signal.

## Relationship to historical YARMI

Historical YARMI used fiducial identity and fiducial rotation as a convenient sensing mechanism. YARMI 2 retains the more general interaction proposition:

> musical things can be controlled by directly manipulating visible things, and additional manipulators can be assigned to expose further parameters.

The physical thing, tracking method, and gesture vocabulary remain replaceable.
