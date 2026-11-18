from fractions import Fraction as F
from dataclasses import replace
import unittest
from station import Event, Track, Station


class StationTest(unittest.TestCase):
    def setUp(self):
        self.track = Track("a", (0, 0), (9, 6), F(3), (Event(F(0), 60), Event(F(1, 3), 61)))
        self.station = Station((self.track,))

    def test_boundaries_and_partition(self):
        self.assertEqual(self.station.schedule(-2, 4),
                         ((F(-2), "a", 61), (F(0), "a", 60), (F(1), "a", 61), (F(3), "a", 60)))
        self.assertEqual(self.station.schedule(-2, 4),
                         self.station.schedule(-2, 1) + self.station.schedule(1, 4))
        self.assertEqual(self.station.schedule(1, 1), ())

    def test_geometry_independence(self):
        moved = Station((replace(self.track, end=(5, 2)),))
        self.assertEqual(self.station.schedule(0, 8), moved.schedule(0, 8))
        self.assertNotEqual(self.station.audience(1), moved.audience(1))

    def test_period_binding(self):
        changed = self.station.set_period("a", F(5, 2))
        self.assertEqual(changed.tracks[0].end, self.track.end)
        self.assertNotEqual(self.station.schedule(0, 5), changed.schedule(0, 5))
        self.assertEqual(changed.tracks[0].cursor(F(5, 4)), (F(9, 2), F(3)))
        self.assertEqual(self.track.period, F(3))

    def test_invalid_inputs(self):
        with self.assertRaises(ValueError):
            self.station.set_period("a", 0)
        with self.assertRaises(KeyError):
            self.station.set_period("other", 1)
        with self.assertRaises(ValueError):
            Event(F(1), 60)
        with self.assertRaises(ValueError):
            self.station.schedule(4, 3)


if __name__ == "__main__":
    unittest.main()
