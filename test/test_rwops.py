"""test bindings in src/rwops.h"""
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


class TestRwopsConstants(unittest.TestCase):
    """Tests for value of constants in SDL_rwops.h"""

    def test_SDL_RWOPS_UNKNOWN(self):
        self.assertEqual(SDL_RWOPS_UNKNOWN, 0)

    def test_SDL_RWOPS_WINFILE(self):
        self.assertEqual(SDL_RWOPS_WINFILE, 1)

    def test_SDL_RWOPS_STDFILE(self):
        self.assertEqual(SDL_RWOPS_STDFILE, 2)

    def test_SDL_RWOPS_JNIFILE(self):
        self.assertEqual(SDL_RWOPS_JNIFILE, 3)

    def test_SDL_RWOPS_MEMORY(self):
        self.assertEqual(SDL_RWOPS_MEMORY, 4)

    def test_SDL_RWOPS_MEMORY_RO(self):
        self.assertEqual(SDL_RWOPS_MEMORY_RO, 5)

    def test_RW_SEEK_SET(self):
        self.assertEqual(RW_SEEK_SET, 0)

    def test_RW_SEEK_CUR(self):
        self.assertEqual(RW_SEEK_CUR, 1)

    def test_RW_SEEKEND(self):
        self.assertEqual(RW_SEEK_END, 2)


if __name__ == '__main__':
    unittest.main()
