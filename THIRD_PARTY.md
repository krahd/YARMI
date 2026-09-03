# Third-party dependencies

YARMI's CMake configuration downloads pinned upstream dependencies at configure time.

- JUCE 9.0.1 — AGPLv3 or a JUCE commercial licence, depending on distribution.
- libpd 0.16.1 / Pure Data — Standard Improved BSD licence.
- Ableton Link desktop source — GPLv2+ or Ableton's proprietary licence.
- Ableton LinkKit 4.1 on iOS/iPadOS — Ableton Link SDK Licence v2.0.

Review the upstream licence terms before distributing binaries. LinkKit also requires Apple's
multicast networking entitlement for physical-device peer discovery; the entitlement is present
in the project, but Apple must grant it to the signing team.
