"""test bindings in src/render.h"""
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


class TestRenderConstants(unittest.TestCase):
    """Test value of constants defined in SDL_render.h"""

    def test_SDL_RENDERER_SOFTWARE(self):
        self.assertEqual(SDL_RENDERER_SOFTWARE, 0x01)

    def test_SDL_RENDERER_ACCELERATED(self):
        self.assertEqual(SDL_RENDERER_ACCELERATED, 0x02)

    def test_SDL_RENDERER_PRESENTVSYNC(self):
        self.assertEqual(SDL_RENDERER_PRESENTVSYNC, 0x04)

    def test_SDL_RENDERER_TARGETTEXTURE(self):
        self.assertEqual(SDL_RENDERER_TARGETTEXTURE, 0x08)

    def test_SDL_TEXTUREACCESS_STATIC(self):
        self.assertEqual(SDL_TEXTUREACCESS_STATIC, 0)

    def test_SDL_TEXTUREACCESS_STREAMING(self):
        self.assertEqual(SDL_TEXTUREACCESS_STREAMING, 1)

    def test_SDL_TEXTUREACCESS_TARGET(self):
        self.assertEqual(SDL_TEXTUREACCESS_TARGET, 2)

    def test_SDL_TEXTUREMODULATE_NONE(self):
        self.assertEqual(SDL_TEXTUREMODULATE_NONE, 0)

    def test_SDL_TEXTUREMODULATE_COLOR(self):
        self.assertEqual(SDL_TEXTUREMODULATE_COLOR, 1)

    def test_SDL_TEXTUREMODULATE_ALPHA(self):
        self.assertEqual(SDL_TEXTUREMODULATE_ALPHA, 2)

    def test_SDL_FLIP_NONE(self):
        self.assertEqual(SDL_FLIP_NONE, 0)

    def test_SDL_FLIP_HORIZONTAL(self):
        self.assertEqual(SDL_FLIP_HORIZONTAL, 0x01)

    def test_SDL_FLIP_VERTICAL(self):
        self.assertEqual(SDL_FLIP_VERTICAL, 0x02)


if __name__ == '__main__':
    unittest.main()