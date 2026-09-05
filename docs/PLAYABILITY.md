# YARMI playability contract

These are constitutive design constraints, not a checklist for reproducing historical YARMI.

## 1. Audience intelligibility comes first

YARMI exists to make musical interaction causally legible to an audience. Important performer actions, computational changes and musical consequences must have an observable relationship in the station's public rendering.

The audience does not need to see every internal parameter, but the performance must not reduce to hidden operation followed by unexplained sound.

## 2. Augmented performance space is part of the instrument

A station is an augmented musical locus. Projection, camera-mediated AR, spatial displays, AR glasses or another augmentation technique may be used, but an implementation visible only to the performer is incomplete until the relevant state/action relationships have a public manifestation.

## 3. Sequence and instrument must coexist

Repeatable temporal organisation provides musical safety and structure; immediate/continuous interaction provides performative expression. Neither replaces the other.

The historical combination of sequencer-like organisation and direct manipulation is retained because it supports both coherence and instrumental agency.

## 4. Immediate consequence

Important direct gestures should be capable of producing an immediately perceptible musical consequence. A performer should be able to learn what an object/control does by acting on it rather than waiting for a long hidden future state change.

## 5. Direct manipulation

Musical things should expose important controls through manipulation of the thing itself whenever that remains intelligible. Detached sliders/menus are allowed where useful, but they are not the default interaction ideal.

## 6. Composable control

Additional manipulators can be assigned to parameters of existing musical elements. A musical component need not expose all of its expressive dimensions through one physical object or gesture.

## 7. No privileged gesture

Rotation is historically important but is not the definition of manipulation. Translation, scale, distance, orientation, velocity, proximity, pressure, contact and other observable channels may be bound to parameters.

## 8. Low floor, higher ceiling

A new performer should be able to produce coherent musical behaviour quickly. Continued use should permit refinement, coordination and expression rather than only more presets or randomisation.

## 9. Musical safety without grid imprisonment

Quantisation, synchronisation, defaults and periodic structures may make the instrument safer to play. They must not force every station into a rectangular step-sequencer model.

## 10. Performer agency

Generative/autonomous behaviour may exist, but it should not become the default substitute for consequential performative action. Random mutation is a possible component behaviour, not YARMI's core interaction model.

## 11. Local playability

A station should be musically useful on its own. Ensemble membership and synchronisation add possibilities; they should not be prerequisites for making the station an instrument.

## 12. Tracking failure must be legible

For vision/depth-based manipulators, uncertainty is part of the interface. Tracking degradation or ambiguous channels must be shown rather than silently converted into incorrect musical control.

## Evaluation loop

The governing early evaluation method is first-person performance practice:

```text
implement -> play -> observe -> revise -> play again
```

Tomas Laurenzo is the principal initial performer/designer. Formal user research may later be appropriate for a specific research question, but it is not required before changing an interaction that fails musically.
