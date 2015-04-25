"""test bindings in src/surface.h"""
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


class Test_Surface(unittest.TestCase):
    """Tests for SDL_Surface"""

    def setUp(self):
        self.surface = SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)

    def test_cannot_create(self):
        "Cannot create SDL_Surface instances"
        self.assertRaises(TypeError, SDL_Surface)
        self.assertRaises(TypeError, SDL_Surface.__new__, SDL_Surface)

    def test_cannot_subclass(self):
        "Cannot be used as a base class"
        self.assertRaises(TypeError, type, "testtype", (SDL_Surface,), {})

    def test_flags(self):
        "flags is an int"
        self.assertIs(type(self.surface.flags), int)

    def test_flags_readonly(self):
        "flags is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'flags', 42)

    def test_freed_flags(self):
        "Once freed, flags raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'flags')

    def test_format(self):
        "format is a SDL_PixelFormat"
        self.assertIs(type(self.surface.format), SDL_PixelFormat)

    def test_format_holdsref(self):
        "the format SDL_PixelFormat still works after surface is freed"
        x = self.surface.format
        SDL_FreeSurface(self.surface)
        self.assertEqual(x.BytesPerPixel, 4)

    def test_format_readonly(self):
        "format is readonly"
        x = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)
        self.assertRaises(AttributeError, setattr, self.surface, 'format', x)

    def test_freed_format(self):
        "Once freed, format raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'format')

    def test_w(self):
        "w is correct"
        self.assertIs(type(self.surface.w), int)
        self.assertEqual(self.surface.w, 32)

    def test_w_readonly(self):
        "w is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'w', 42)

    def test_freed_w(self):
        "Once freed, w raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'w')

    def test_h(self):
        "h is correct"
        self.assertIs(type(self.surface.h), int)
        self.assertEqual(self.surface.h, 16)

    def test_h_readonly(self):
        "h is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'h', 42)

    def test_freed_h(self):
        "Once freed, h raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'h')

    def test_pitch(self):
        "pitch is correct"
        # 4 bytes per pixel * 32 pixels
        self.assertIs(type(self.surface.pitch), int)
        self.assertEqual(self.surface.pitch, 4 * 32)

    def test_pitch_readonly(self):
        "pitch is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'pitch', 42)

    def test_freed_pitch(self):
        "Once freed, pitch raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'pitch')

    def test_pixels(self):
        "pixels is a buffer of bytes"
        mem = memoryview(self.surface.pixels)
        self.assertEqual(mem.itemsize, 1)
        self.assertEqual(mem.nbytes, 4 * 32 * 16)

    def test_pixels_hold_ref(self):
        "pixels holds a reference to underlying buffer"
        pixels = self.surface.pixels
        SDL_FreeSurface(self.surface)
        memview = memoryview(pixels)
        self.assertEqual(memview[0], 0)

    def test_pixels_readonly(self):
        "pixels is readonly"
        x = bytearray(1)
        self.assertRaises(AttributeError, setattr, self.surface, 'pixels', x)

    def test_freed_pixels(self):
        "Once freed, pixels raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'pixels')

    def test_userdata(self):
        "userdata is correct"
        self.assertIs(self.surface.userdata, None)

    def test_userdata_set(self):
        "userdata can be set"
        self.surface.userdata = True
        self.assertIs(self.surface.userdata, True)

    def test_freed_userdata(self):
        "Once freed, userdata raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'userdata')

    def test_locked(self):
        "locked is correct"
        self.assertIs(self.surface.locked, False)

    def test_locked_readonly(self):
        "locked is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'locked',
                          True)

    def test_freed_locked(self):
        "Once freed, locked raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'locked')

    def test_clip_rect(self):
        "clip_rect is correct"
        rect = self.surface.clip_rect
        self.assertIs(type(rect.x), int)
        self.assertEqual(rect.x, 0)
        self.assertIs(type(rect.y), int)
        self.assertEqual(rect.y, 0)
        self.assertIs(type(rect.w), int)
        self.assertEqual(rect.w, 32)
        self.assertIs(type(rect.h), int)
        self.assertEqual(rect.h, 16)

    def test_clip_rect_buffer(self):
        "clip_rect supports buffer protocol"
        rect = self.surface.clip_rect
        mem = memoryview(rect)
        self.assertTrue(mem.readonly)
        self.assertEqual(mem.format, 'iiii')
        self.assertEqual(mem.ndim, 0)
        x = struct.unpack('iiii', mem.tobytes())
        self.assertEqual(x, (0, 0, 32, 16))

    def test_clip_rect_readonly(self):
        "clip_rect is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'clip_rect',
                          SDL_Rect())
        rect = self.surface.clip_rect
        self.assertRaises(AttributeError, setattr, rect, 'x', 42)
        self.assertRaises(AttributeError, setattr, rect, 'y', 42)
        self.assertRaises(AttributeError, setattr, rect, 'w', 42)
        self.assertRaises(AttributeError, setattr, rect, 'h', 42)

    def test_freed_clip_rect(self):
        "Once freed, clip_rect raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'clip_rect')

    def test_freed_clip_rect_ref(self):
        "Once freed, any remaining references to clip_rect still works"
        rect = self.surface.clip_rect
        SDL_FreeSurface(self.surface)
        self.assertEqual(rect.x, 0)
        self.assertEqual(rect.y, 0)
        self.assertEqual(rect.w, 32)
        self.assertEqual(rect.h, 16)

    def test_refcount(self):
        "refcount is an int"
        self.assertIs(type(self.surface.refcount), int)

    def test_refcount_readonly(self):
        "refcount is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'refcount',
                          42)

    def test_freed_refcount(self):
        "Once freed, refcount raises AssertionError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(AssertionError, getattr, self.surface, 'refcount')


class Test_MUSTLOCK(unittest.TestCase):
    "Tests SDL_MUSTLOCK()"

    def setUp(self):
        self.surface = SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)

    def test_returns_bool(self):
        "Returns a bool"
        self.assertIs(type(SDL_MUSTLOCK(self.surface)), bool)


class Test_CreateRGBSurface(unittest.TestCase):
    "Tests SDL_CreateRGBSurface()"

    def test_returns_surface(self):
        "Returns a SDL_Surface"
        self.assertIs(type(SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)),
                      SDL_Surface)


if __name__ == '__main__':
    unittest.main()
