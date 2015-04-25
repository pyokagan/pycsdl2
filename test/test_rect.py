"""test bindings in src/rect.h"""
import distutils.util
import os.path
import struct
import sys
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *


class Test_Rect(unittest.TestCase):
    """Tests SDL_Rect"""

    def setUp(self):
        self.r = SDL_Rect(1, 2, 3, 4)

    def test_create(self):
        "Can create instances directly"
        self.assertIs(type(SDL_Rect()), SDL_Rect)
        self.assertIs(type(SDL_Rect.__new__(SDL_Rect)), SDL_Rect)

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_Rect,), {})

    def test_x(self):
        "x has the correct int value"
        self.assertIs(type(self.r.x), int)
        self.assertEqual(self.r.x, 1)

    def test_x_set(self):
        "x can be set to an int"
        self.r.x = 42
        self.assertEqual(self.r.x, 42)

    def test_y(self):
        "y has the correct int value"
        self.assertIs(type(self.r.y), int)
        self.assertEqual(self.r.y, 2)

    def test_y_set(self):
        "y can be set to an int"
        self.r.y = 42
        self.assertEqual(self.r.y, 42)

    def test_w(self):
        "w has the correct int value"
        self.assertIs(type(self.r.w), int)
        self.assertEqual(self.r.w, 3)

    def test_w_set(self):
        "w can be set to an int"
        self.r.w = 42
        self.assertEqual(self.r.w, 42)

    def test_h(self):
        "h has the correct int value"
        self.assertIs(type(self.r.h), int)
        self.assertEqual(self.r.h, 4)

    def test_h_set(self):
        "h can be set to an int"
        self.r.h = 42
        self.assertEqual(self.r.h, 42)

    def test_buffer(self):
        "supports the buffer protocol"
        mem = memoryview(self.r)
        self.assertFalse(mem.readonly)
        self.assertEqual(mem.format, 'iiii')
        self.assertEqual(mem.ndim, 0)
        self.assertEqual(struct.unpack('iiii', mem.tobytes()), (1, 2, 3, 4))


if __name__ == '__main__':
    unittest.main()
