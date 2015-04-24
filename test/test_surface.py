"""test bindings in src/surface.h"""
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


class TestSurfaceConstants(unittest.TestCase):
    """Tests value of constants in SDL_surface.h"""

    def test_SDL_SWSURFACE(self):
        self.assertEqual(SDL_SWSURFACE, 0)

    def test_SDL_PREALLOC(self):
        self.assertEqual(SDL_PREALLOC, 0x01)

    def test_SDL_RLEACCEL(self):
        self.assertEqual(SDL_RLEACCEL, 0x02)

    def test_SDL_DONTFREE(self):
        self.assertEqual(SDL_DONTFREE, 0x04)


if __name__ == '__main__':
    unittest.main()
