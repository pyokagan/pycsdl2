"""test bindings in src/init.h"""
import distutils.util
import os.path
import sys
import unittest
import atexit


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa


atexit.register(SDL_Quit)


class TestInitConstants(unittest.TestCase):
    "Tests for the availability of constants and their values in SDL.h"

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


class TestInit(unittest.TestCase):
    "Tests SDL_Init()"

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_Init(SDL_INIT_EVENTS))


class TestInitSubSystem(unittest.TestCase):
    "Tests SDL_InitSubSystem()"

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_InitSubSystem(SDL_INIT_EVENTS))


class TestQuitSubSystem(unittest.TestCase):
    "Tests SDL_QuitSubSystem()"

    def setUp(self):
        SDL_InitSubSystem(SDL_INIT_EVENTS)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_QuitSubSystem(SDL_INIT_EVENTS))


class TestWasInit(unittest.TestCase):
    "Tests SDL_WasInit()"

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_WasInit(0)), int)


if __name__ == '__main__':
    unittest.main()
