"""test bindings in src/blendmode.h"""
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


class TestBlendmodeConstants(unittest.TestCase):
    """Test value of constants defined in SDL_blendmode.h"""

    def test_SDL_BLENDMODE_NONE(self):
        self.assertEqual(SDL_BLENDMODE_NONE, 0x00)

    def test_SDL_BLENDMODE_BLEND(self):
        self.assertEqual(SDL_BLENDMODE_BLEND, 0x01)

    def test_SDL_BLENDMODE_ADD(self):
        self.assertEqual(SDL_BLENDMODE_ADD, 0x02)

    def test_SDL_BLENDMODE_MOD(self):
        self.assertEqual(SDL_BLENDMODE_MOD, 0x04)


if __name__ == '__main__':
    unittest.main()
