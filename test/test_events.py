"""test bindings in src/events.h"""
import distutils.util
import os.path
import sys
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *


class TestEventsConstants(unittest.TestCase):
    """Tests for the availability of constants and their values"""

    def test_SDL_RELEASED(self):
        self.assertEqual(SDL_RELEASED, 0)

    def test_SDL_PRESSED(self):
        self.assertEqual(SDL_PRESSED, 1)

    def test_SDL_FIRSTEVENT(self):
        self.assertEqual(SDL_FIRSTEVENT, 0)

    def test_SDL_QUIT(self):
        self.assertEqual(SDL_QUIT, 0x100)

    def test_SDL_APP_TERMINATING(self):
        self.assertEqual(SDL_APP_TERMINATING, 0x101)

    def test_SDL_APP_LOWMEMORY(self):
        self.assertEqual(SDL_APP_LOWMEMORY, 0x102)

    def test_SDL_APP_WILLENTERBACKGROUND(self):
        self.assertEqual(SDL_APP_WILLENTERBACKGROUND, 0x103)

    def test_SDL_APP_DIDENTERBACKGROUND(self):
        self.assertEqual(SDL_APP_DIDENTERBACKGROUND, 0x104)

    def test_SDL_APP_WILLENTERFOREGROUND(self):
        self.assertEqual(SDL_APP_WILLENTERFOREGROUND, 0x105)

    def test_SDL_APP_DIDENTERFOREGROUND(self):
        self.assertEqual(SDL_APP_DIDENTERFOREGROUND, 0x106)

    def test_SDL_WINDOWEVENT(self):
        self.assertEqual(SDL_WINDOWEVENT, 0x200)

    def test_SDL_SYSWMEVENT(self):
        self.assertEqual(SDL_SYSWMEVENT, 0x201)

    def test_SDL_KEYDOWN(self):
        self.assertEqual(SDL_KEYDOWN, 0x300)

    def test_SDL_KEYUP(self):
        self.assertEqual(SDL_KEYUP, 0x301)

    def test_SDL_TEXTEDITING(self):
        self.assertEqual(SDL_TEXTEDITING, 0x302)

    def test_SDL_TEXTINPUT(self):
        self.assertEqual(SDL_TEXTINPUT, 0x303)

    def test_SDL_MOUSEMOTION(self):
        self.assertEqual(SDL_MOUSEMOTION, 0x400)

    def test_SDL_MOUSEBUTTONDOWN(self):
        self.assertEqual(SDL_MOUSEBUTTONDOWN, 0x401)

    def test_SDL_MOUSEBUTTONUP(self):
        self.assertEqual(SDL_MOUSEBUTTONUP, 0x402)

    def test_SDL_MOUSEWHEEL(self):
        self.assertEqual(SDL_MOUSEWHEEL, 0x403)

    def test_SDL_JOYAXISMOTION(self):
        self.assertEqual(SDL_JOYAXISMOTION, 0x600)

    def test_SDL_JOYBALLMOTION(self):
        self.assertEqual(SDL_JOYBALLMOTION, 0x601)

    def test_SDL_JOYHATMOTION(self):
        self.assertEqual(SDL_JOYHATMOTION, 0x602)

    def test_SDL_JOYBUTTONDOWN(self):
        self.assertEqual(SDL_JOYBUTTONDOWN, 0x603)

    def test_SDL_JOYBUTTONUP(self):
        self.assertEqual(SDL_JOYBUTTONUP, 0x604)

    def test_SDL_JOYDEVICEADDED(self):
        self.assertEqual(SDL_JOYDEVICEADDED, 0x605)

    def test_SDL_JOYDEVICEREMOVED(self):
        self.assertEqual(SDL_JOYDEVICEREMOVED, 0x606)

    def test_SDL_CONTROLLERAXISMOTION(self):
        self.assertEqual(SDL_CONTROLLERAXISMOTION, 0x650)

    def test_SDL_CONTROLLERBUTTONDOWN(self):
        self.assertEqual(SDL_CONTROLLERBUTTONDOWN, 0x651)

    def test_SDL_CONTROLLERBUTTONUP(self):
        self.assertEqual(SDL_CONTROLLERBUTTONUP, 0x652)

    def test_SDL_CONTROLLERDEVICEADDED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEADDED, 0x653)

    def test_SDL_CONTROLLERDEVICEREMOVED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEREMOVED, 0x654)

    def test_SDL_CONTROLLERDEVICEREMAPPED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEREMAPPED, 0x655)

    def test_SDL_FINGERDOWN(self):
        self.assertEqual(SDL_FINGERDOWN, 0x700)

    def test_SDL_FINGERUP(self):
        self.assertEqual(SDL_FINGERUP, 0x701)

    def test_SDL_FINGERMOTION(self):
        self.assertEqual(SDL_FINGERMOTION, 0x702)

    def test_SDL_DOLLARGESTURE(self):
        self.assertEqual(SDL_DOLLARGESTURE, 0x800)

    def test_SDL_DOLLARRECORD(self):
        self.assertEqual(SDL_DOLLARRECORD, 0x801)

    def test_SDL_MULTIGESTURE(self):
        self.assertEqual(SDL_MULTIGESTURE, 0x802)

    def test_SDL_CLIPBOARDUPDATE(self):
        self.assertEqual(SDL_CLIPBOARDUPDATE, 0x900)

    def test_SDL_DROPFILE(self):
        self.assertEqual(SDL_DROPFILE, 0x1000)

    def test_SDL_USEREVENT(self):
        self.assertEqual(SDL_USEREVENT, 0x8000)

    def test_SDL_LASTEVENT(self):
        self.assertEqual(SDL_LASTEVENT, 0xFFFF)


if __name__ == '__main__':
    unittest.main()
