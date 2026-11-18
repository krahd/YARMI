from fractions import Fraction as F
import unittest
from live import PCM
from station import Station, Track, Event


class PCMTest(unittest.TestCase):
    def setUp(self):
        self.station = Station((Track("a", (0, 0), (2, 1), F(3, 7), (Event(F(1, 3), 60),)),))

    def test_partition_invariance(self):
        a = PCM(self.station, block=128)
        b = PCM(self.station, block=256)
        self.assertEqual(b"".join(a.render() for _ in range(40)),
                         b"".join(b.render() for _ in range(20)))

    def test_immediate_and_tail(self):
        audio = PCM(Station(()), block=32)
        self.assertEqual(audio.render(), bytes(64))
        pitch = audio.command("hit 64")
        self.assertNotEqual(audio.render((pitch,)), bytes(64))
        self.assertNotEqual(audio.render(), bytes(64))
        for _ in range(60):
            audio.render()
        self.assertEqual(audio.render(), bytes(64))

    def test_edit_at_render_boundary(self):
        audio = PCM(self.station)
        audio.render()
        phase = audio.beat
        audio.command("period a 5/2")
        self.assertEqual(audio.beat, phase)
        self.assertEqual(audio.station.tracks[0].period, F(5, 2))
        self.assertEqual(audio.station.tracks[0].end, (2, 1))
        with self.assertRaises(ValueError):
            audio.command("period a 0")
        self.assertEqual(audio.station.tracks[0].period, F(5, 2))


if __name__ == "__main__":
    unittest.main()
