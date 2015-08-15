"""test bindings in src/init.h"""
import distutils.util
import os.path
import sys
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa


class TestInitConstants(unittest.TestCase):
    """Tests for the availability of constants and their values in SDL.h"""

    def test_SDL_INIT_TIMER(self):
        self.assertEqual(SDL_INIT_TIMER, 0x00000001)

    def test_SDL_INIT_AUDIO(self):
        self.assertEqual(SDL_INIT_AUDIO, 0x00000010)

    def test_SDL_INIT_VIDEO(self):
        self.assertEqual(SDL_INIT_VIDEO, 0x00000020)

    def test_SDL_INIT_JOYSTICK(self):
        self.assertEqual(SDL_INIT_JOYSTICK, 0x00000200)

    def test_SDL_INIT_HAPTIC(self):
        self.assertEqual(SDL_INIT_HAPTIC, 0x00001000)

    def test_SDL_INIT_GAMECONTROLLER(self):
        self.assertEqual(SDL_INIT_GAMECONTROLLER, 0x00002000)

    def test_SDL_INIT_EVENTS(self):
        self.assertEqual(SDL_INIT_EVENTS, 0x00004000)

    def test_SDL_INIT_NOPARACHUTE(self):
        self.assertEqual(SDL_INIT_NOPARACHUTE, 0x00100000)

    def test_SDL_INIT_EVERYTHING(self):
        self.assertEqual(SDL_INIT_EVERYTHING, 29233)


class TestSDL_Init(unittest.TestCase):
    """Tests SDL_Init()"""

    def test_SDL_INIT_TIMER(self):
        self.assertIs(SDL_Init(SDL_INIT_TIMER), None)

    def test_SDL_INIT_AUDIO(self):
        self.assertIs(SDL_Init(SDL_INIT_AUDIO), None)

    def test_SDL_INIT_VIDEO(self):
        self.assertIs(SDL_Init(SDL_INIT_VIDEO), None)

    def test_SDL_INIT_JOYSTICK(self):
        self.assertIs(SDL_Init(SDL_INIT_JOYSTICK), None)

    def test_SDL_INIT_HAPTIC(self):
        self.assertIs(SDL_Init(SDL_INIT_HAPTIC), None)

    def test_SDL_INIT_GAMECONTROLLER(self):
        self.assertIs(SDL_Init(SDL_INIT_GAMECONTROLLER), None)

    def test_SDL_INIT_EVENTS(self):
        self.assertIs(SDL_Init(SDL_INIT_EVENTS), None)

    def test_SDL_INIT_NOPARACHUTE(self):
        self.assertIs(SDL_Init(SDL_INIT_NOPARACHUTE), None)

    def test_SDL_INIT_EVERYTHING(self):
        self.assertIs(SDL_Init(SDL_INIT_EVERYTHING), None)


if __name__ == '__main__':
    unittest.main()
