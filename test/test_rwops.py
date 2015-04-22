"""test bindings in src/rwops.h"""
import distutils.util
import os.path
import sys
import tempfile
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


class Test_SDL_RWops(unittest.TestCase):
    """Tests for SDL_RWops"""

    def test_cannot_create(self):
        "Cannot create SDL_RWops instances"
        self.assertRaises(TypeError, SDL_RWops)
        self.assertRaises(TypeError, SDL_RWops.__new__, SDL_RWops)

    def test_cannot_subclass(self):
        "Cannot be used as a base class"
        self.assertRaises(TypeError, type, "testtype", (SDL_RWops,), {})

    def test_type_is_int(self):
        "SDL_RWops.type is an integer"
        rwops = SDL_AllocRW()
        self.assertIs(type(rwops.type), int)

    def test_type_set_int(self):
        "SDL_RWops.type can be set to an integer"
        rwops = SDL_AllocRW()
        rwops.type = 42
        self.assertEqual(rwops.type, 42)

    def test_type_set_invalid_type(self):
        "SDL_RWops.type raises a TypeError if not set to an integer"
        rwops = SDL_AllocRW()
        self.assertRaises(TypeError, setattr, rwops, 'type', None)

    def test_freed_type(self):
        "SDL_RWops.type raises an AssertionError if the object has been freed"
        rwops = SDL_AllocRW()
        SDL_FreeRW(rwops)
        self.assertRaises(AssertionError, getattr, rwops, 'type')


class Test_SDL_RWFromFile(unittest.TestCase):
    """Tests for SDL_RWFromFile"""

    @classmethod
    def setUpClass(cls):
        cls.dir = tempfile.TemporaryDirectory()

    @classmethod
    def tearDownClass(cls):
        cls.dir.cleanup()

    def setUp(self):
        self.path = os.path.join(self.dir.name, self.id())

    def test_r_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'a') returns SDL_RWops"
        with open(self.path, 'wb') as f:
            f.write(b'TEST')
        self.assertIs(type(SDL_RWFromFile(self.path, 'r')), SDL_RWops)

    def test_w_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'w') returns SDL_RWops"
        self.assertIs(type(SDL_RWFromFile(self.path, 'w')), SDL_RWops)

    def test_a_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'a') returns SDL_RWops"
        self.assertIs(type(SDL_RWFromFile(self.path, 'a')), SDL_RWops)

    def test_rp_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'r+') returns SDL_RWops"
        with open(self.path, 'wb') as f:
            f.write(b'TEST')
        self.assertIs(type(SDL_RWFromFile(self.path, 'r+')), SDL_RWops)

    def test_wp_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'w+') returns SDL_RWops"
        self.assertIs(type(SDL_RWFromFile(self.path, 'w+')), SDL_RWops)

    def test_ap_returns_SDL_RWops(self):
        "SDL_RWFromFile(file, 'a+') returns SDL_RWops"
        self.assertIs(type(SDL_RWFromFile(self.path, 'a+')), SDL_RWops)


if __name__ == '__main__':
    unittest.main()
