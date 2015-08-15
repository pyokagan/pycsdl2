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


from csdl2 import *  # noqa
import _csdl2test  # noqa


class TestPoint(unittest.TestCase):
    "Tests SDL_Point"

    def setUp(self):
        self.p = SDL_Point(1, 2)

    def test_create(self):
        "Can create instances directly"
        self.assertIs(type(SDL_Point()), SDL_Point)
        self.assertIs(type(SDL_Point.__new__(SDL_Point)), SDL_Point)

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_Point,), {})

    def test_x(self):
        "x has the correct int value"
        self.assertIs(type(self.p.x), int)
        self.assertEqual(self.p.x, 1)

    def test_x_set(self):
        "x can be set to an int"
        self.p.x = 42
        self.assertEqual(self.p.x, 42)

    def test_y(self):
        "y has the correct int value"
        self.assertIs(type(self.p.y), int)
        self.assertIs(self.p.y, 2)

    def test_y_set(self):
        "y can be set to an int"
        self.p.y = 42
        self.assertEqual(self.p.y, 42)

    def test_buffer(self):
        "supports the buffer protocol"
        mem = memoryview(self.p)
        self.assertFalse(mem.readonly)
        self.assertEqual(mem.format, 'ii')
        self.assertEqual(mem.ndim, 1)
        self.assertEqual(struct.unpack('ii', mem.tobytes()), (1, 2))


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


class TestHasIntersection(unittest.TestCase):
    """Tests SDL_HasIntersection"""

    def setUp(self):
        # set up 2 intersecting rectangles
        self.a = SDL_Rect(0, 0, 10, 10)
        self.b = SDL_Rect(0, 0, 5, 5)

    def test_returns_bool(self):
        "Returns a bool"
        self.assertIs(SDL_HasIntersection(self.a, self.b), True)

    def test_A_none(self):
        "A can be None"
        self.assertIs(SDL_HasIntersection(None, self.b), False)

    def test_A_buffer(self):
        "A can be a buffer of suitable size"
        a = memoryview(self.a).tobytes()
        self.assertIs(SDL_HasIntersection(a, self.b), True)

    def test_A_buffer_invalid_size(self):
        "Raise BufferError if A has an invalid buffer size"
        a = bytes(1)
        self.assertRaises(BufferError, SDL_HasIntersection, a, self.b)

    def test_B_none(self):
        "B can be None"
        self.assertIs(SDL_HasIntersection(self.a, None), False)

    def test_B_buffer(self):
        "B can be a buffer of suitable size"
        b = memoryview(self.b).tobytes()
        self.assertIs(SDL_HasIntersection(self.a, b), True)

    def test_B_buffer_invalid_size(self):
        "Raise BufferError if B has an invalid buffer size"
        b = bytes(1)
        self.assertRaises(BufferError, SDL_HasIntersection, self.a, b)


class TestPointCreate(unittest.TestCase):
    "Tests PyCSDL2_PointCreate()"

    def test_returns_Point(self):
        "Returns a new SDL_Point"
        p = _csdl2test.point()
        self.assertIs(type(p), SDL_Point)
        self.assertEqual(p.x, 3)
        self.assertEqual(p.y, 4)


class TestPointPtr(unittest.TestCase):
    "Tests PyCSDL2_PointPtr()"

    def test_converter(self):
        "Can be used as a converter for PyArg_ParseTuple()"
        p = SDL_Point()
        self.assertEqual(p.x, 0)
        _csdl2test.point_set_x(p)
        self.assertEqual(p.x, 42)

    def test_invalid_type(self):
        "Raises TypeError in invalid type"
        self.assertRaises(TypeError, _csdl2test.point_set_x, 42)


class TestRectCreate(unittest.TestCase):
    "Tests PyCSDL2_RectCreate()"

    def test_returns_Rect(self):
        "Returns a new SDL_Rect"
        r = _csdl2test.rect()
        self.assertIs(type(r), SDL_Rect)
        self.assertEqual(r.x, 1)
        self.assertEqual(r.y, 2)
        self.assertEqual(r.w, 3)
        self.assertEqual(r.h, 4)


class TestRectPtr(unittest.TestCase):
    "Tests PyCSDL2_RectPtr()"

    def test_converter(self):
        "Can be used as a converter for PyArg_ParseTuple()"
        r = SDL_Rect()
        self.assertEqual(r.x, 0)
        _csdl2test.rect_set_x(r)
        self.assertEqual(r.x, 42)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.rect_set_x, 42)


if __name__ == '__main__':
    unittest.main()
