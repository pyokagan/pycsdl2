"""test bindings in src/surface.h"""
import array
import distutils.util
import os.path
import struct
import sys
import unittest
import array
import io
import tempfile


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa
import _csdl2test  # noqa


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
        "Once freed, flags raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'flags')

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
        "Once freed, format raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'format')

    def test_w(self):
        "w is correct"
        self.assertIs(type(self.surface.w), int)
        self.assertEqual(self.surface.w, 32)

    def test_w_readonly(self):
        "w is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'w', 42)

    def test_freed_w(self):
        "Once freed, w raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'w')

    def test_h(self):
        "h is correct"
        self.assertIs(type(self.surface.h), int)
        self.assertEqual(self.surface.h, 16)

    def test_h_readonly(self):
        "h is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'h', 42)

    def test_freed_h(self):
        "Once freed, h raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'h')

    def test_pitch(self):
        "pitch is correct"
        # 4 bytes per pixel * 32 pixels
        self.assertIs(type(self.surface.pitch), int)
        self.assertEqual(self.surface.pitch, 4 * 32)

    def test_pitch_readonly(self):
        "pitch is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'pitch', 42)

    def test_freed_pitch(self):
        "Once freed, pitch raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'pitch')

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
        "Once freed, pixels raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'pixels')

    def test_userdata(self):
        "userdata is correct"
        self.assertIs(self.surface.userdata, None)

    def test_userdata_set(self):
        "userdata can be set"
        self.surface.userdata = True
        self.assertIs(self.surface.userdata, True)

    def test_freed_userdata(self):
        "Once freed, userdata raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'userdata')

    def test_locked(self):
        "locked is correct"
        self.assertIs(self.surface.locked, False)

    def test_locked_readonly(self):
        "locked is readonly"
        self.assertRaises(AttributeError, setattr, self.surface, 'locked',
                          True)

    def test_freed_locked(self):
        "Once freed, locked raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'locked')

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
        "Once freed, clip_rect raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'clip_rect')

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
        "Once freed, refcount raises ValueError"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, getattr, self.surface, 'refcount')


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


class Test_CreateRGBSurfaceFrom(unittest.TestCase):
    "Tests SDL_CreateRGBSurfaceFrom()"

    def test_returns_surface(self):
        "Returns a SDL_Surface"
        x = bytearray(32 * 4 * 16)
        y = SDL_CreateRGBSurfaceFrom(x, 32, 16, 32, 32 * 4, 0, 0, 0, 0)
        self.assertIs(type(y), SDL_Surface)
        self.assertIs(y.pixels, x)

    def test_invalid_buffer_size(self):
        "Raises BufferError on invalid buffer size"
        x = bytearray(32 * 4 * 17)
        self.assertRaises(BufferError, SDL_CreateRGBSurfaceFrom, x, 32, 16, 32,
                          32 * 4, 0, 0, 0, 0)

    def test_invalid_pitch(self):
        "Raises ValueError on invalid pitch"
        x = bytearray(32 * 3 * 16)
        self.assertRaises(ValueError, SDL_CreateRGBSurfaceFrom, x, 32, 16, 32,
                          32 * 3, 0, 0, 0, 0)

    def test_holds_buffer(self):
        "Holds the pixel buffer, and releases it on destruction"
        x = array.array('B', [0] * 32 * 4 * 16)
        y = SDL_CreateRGBSurfaceFrom(x, 32, 16, 32, 32 * 4, 0, 0, 0, 0)
        self.assertRaises(BufferError, x.extend, [0])
        SDL_FreeSurface(y)
        x.extend([0])  # now it works


class Test_FreeSurface(unittest.TestCase):
    "Tests SDL_FreeSurface()"

    def setUp(self):
        self.surface = SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_FreeSurface(self.surface), None)

    def test_double_free(self):
        "Raises ValueError on double free"
        SDL_FreeSurface(self.surface)
        self.assertRaises(ValueError, SDL_FreeSurface, self.surface)


def sample_bmp():
    "Returns a 4x4 white bitmap"
    # Size of bitmap in bytes
    size = 14 + 12 + 2 + 16
    # Location of pixel data
    offset = 28
    # Bitmap file header (14 bytes)
    header = struct.pack('<2sIHHI', b'BM', size, 0, 0, offset)
    # BITMAPCOREHEADER (12 bytes)
    # (size, width, height, planes, bpp)
    dib = struct.pack('<IHHHH', 12, 4, 4, 1, 8)
    # padding to 4-byte boundary (2 bytes)
    padding = b'\x00\x00'
    # 4x4 8bpp pixels (16 bytes)
    pixels = b'\xFF' * 4 * 4
    return header + dib + padding + pixels


class TestLoadBMP_RW(unittest.TestCase):
    "Tests SDL_LoadBMP_RW()"

    def setUp(self):
        f = io.BytesIO(sample_bmp())
        self.rwops = SDL_AllocRW()
        self.rwops.size = lambda a: len(f.getbuffer())
        self.rwops.read = lambda a, b, c, d: f.readinto(b) // c
        self.rwops.seek = lambda a, b, c: f.seek(b, c)
        self.rwops.close = lambda a: SDL_FreeRW(a)

    def test_returns_surface(self):
        "Returns a SDL_Surface"
        surface = SDL_LoadBMP_RW(self.rwops, True)
        self.assertIs(type(surface), SDL_Surface)
        self.assertEqual(surface.pixels[0], 255)

    def test_freesrc_true(self):
        "Frees the SDL_RWops if freesrc is True"
        SDL_LoadBMP_RW(self.rwops, True)
        self.assertRaises(ValueError, getattr, self.rwops, 'type')

    def test_freesrc_false(self):
        "Does not free the SDL_RWops if freesrc is False"
        SDL_LoadBMP_RW(self.rwops, False)
        getattr(self.rwops, 'type')

    def test_freed_rwops(self):
        "Raises ValueError if the SDL_RWops has been freed"
        SDL_FreeRW(self.rwops)
        self.assertRaises(ValueError, SDL_LoadBMP_RW, self.rwops, True)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_LoadBMP_RW, 42, True)


class TestLoadBMP(unittest.TestCase):
    "Tests SDL_LoadBMP"

    @classmethod
    def setUpClass(cls):
        cls.dir = tempfile.TemporaryDirectory()
        cls.path = os.path.join(cls.dir.name, 'test.bmp')
        with open(cls.path, 'wb') as f:
            f.write(sample_bmp())

    @classmethod
    def tearDownClass(cls):
        # Handle "directory not empty" errors on Windows by attempting 3 times
        for i in range(3):
            try:
                cls.dir.cleanup()
            except OSError:
                continue
            break

    def test_returns_surface(self):
        "Returns a SDL_Surface"
        surface = SDL_LoadBMP(self.path)
        self.assertIs(type(surface), SDL_Surface)
        self.assertEqual(surface.pixels[0], 255)


class TestSurfaceCreate(unittest.TestCase):
    "Tests PyCSDL2_SurfaceCreate()"

    def test_returns_Surface(self):
        "Returns a new SDL_Surface"
        sf = _csdl2test.surface()
        self.assertIs(type(sf), SDL_Surface)
        self.assertEqual(sf.w, 32)
        self.assertEqual(sf.h, 32)

    def test_pixels_buffer(self):
        "Keeps a reference to a provided pixels buffer"
        pixels = array.array('B', [0] * 32 * 32 * 4)
        sf = _csdl2test.surface_from(pixels)
        self.assertIs(type(sf), SDL_Surface)
        self.assertIs(sf.pixels, pixels)
        # Attempting to append an element to the pixels buffer will fail as the
        # SDL_Surface object keeps a reference to the pixels buffer
        self.assertRaises(BufferError, pixels.append, 0)

    def test_pixels_buffer_readonly(self):
        "Raises BufferError if the pixels buffer is readonly"
        pixels = bytes(32 * 32 * 4)
        self.assertRaises(BufferError, _csdl2test.surface_from, pixels)


class TestSurfacePtr(unittest.TestCase):
    "Tests PyCSDL2_SurfacePtr()"

    def test_converter(self):
        "Works as a converter for PyArg_ParseTuple()"
        sf = SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)
        self.assertEqual(sf.pixels[0], 0)
        _csdl2test.surface_fill(sf)
        self.assertEqual(sf.pixels[0], 255)

    def test_freed(self):
        "Raises ValueError if surface has been freed"
        sf = SDL_CreateRGBSurface(0, 32, 16, 32, 0, 0, 0, 0)
        SDL_FreeSurface(sf)
        self.assertRaises(ValueError, _csdl2test.surface_fill, sf)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.surface_fill, 42)


if __name__ == '__main__':
    unittest.main()
