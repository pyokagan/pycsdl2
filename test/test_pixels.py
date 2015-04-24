"""test bindings in src/pixels.h"""
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


class TestPixelsConstants(unittest.TestCase):
    """Tests values of SDL_pixels.h constants"""

    @staticmethod
    def pixfmt(type, order, layout, bits, bytes):
        "Implements SDL_DEFINE_PIXELFORMAT"
        return ((1 << 28) | (type << 24) | (order << 20) | (layout << 16) |
                (bits << 8) | (bytes << 0))

    @staticmethod
    def fourcc(a, b, c, d):
        "Implements SDL_FOURCC"
        return ((a.encode('ascii')[0] << 0) | (b.encode('ascii')[0] << 8) |
                (c.encode('ascii')[0] << 16) | (d.encode('ascii')[0] << 24))

    def test_SDL_ALPHA_OPAQUE(self):
        self.assertEqual(SDL_ALPHA_OPAQUE, 255)

    def test_SDL_ALPHA_TRANSPARENT(self):
        self.assertEqual(SDL_ALPHA_TRANSPARENT, 0)

    def test_SDL_PIXELTYPE_UNKNOWN(self):
        self.assertEqual(SDL_PIXELTYPE_UNKNOWN, 0)

    def test_SDL_PIXELTYPE_INDEX1(self):
        self.assertEqual(SDL_PIXELTYPE_INDEX1, 1)

    def test_SDL_PIXELTYPE_INDEX4(self):
        self.assertEqual(SDL_PIXELTYPE_INDEX4, 2)

    def test_SDL_PIXELTYPE_INDEX8(self):
        self.assertEqual(SDL_PIXELTYPE_INDEX8, 3)

    def test_SDL_PIXELTYPE_PACKED8(self):
        self.assertEqual(SDL_PIXELTYPE_PACKED8, 4)

    def test_SDL_PIXELTYPE_PACKED16(self):
        self.assertEqual(SDL_PIXELTYPE_PACKED16, 5)

    def test_SDL_PIXELTYPE_PACKED32(self):
        self.assertEqual(SDL_PIXELTYPE_PACKED32, 6)

    def test_SDL_PIXELTYPE_ARRAYU8(self):
        self.assertEqual(SDL_PIXELTYPE_ARRAYU8, 7)

    def test_SDL_PIXELTYPE_ARRAYU16(self):
        self.assertEqual(SDL_PIXELTYPE_ARRAYU16, 8)

    def test_SDL_PIXELTYPE_ARRAYU32(self):
        self.assertEqual(SDL_PIXELTYPE_ARRAYU32, 9)

    def test_SDL_PIXELTYPE_ARRAYF16(self):
        self.assertEqual(SDL_PIXELTYPE_ARRAYF16, 10)

    def test_SDL_PIXELTYPE_ARRAYF32(self):
        self.assertEqual(SDL_PIXELTYPE_ARRAYF32, 11)

    def test_SDL_BITMAPORDER_NONE(self):
        self.assertEqual(SDL_BITMAPORDER_NONE, 0)

    def test_SDL_BITMAPORDER_4321(self):
        self.assertEqual(SDL_BITMAPORDER_4321, 1)

    def test_SDL_BITMAPORDER_1234(self):
        self.assertEqual(SDL_BITMAPORDER_1234, 2)

    def test_SDL_PACKEDORDER_NONE(self):
        self.assertEqual(SDL_PACKEDORDER_NONE, 0)

    def test_SDL_PACKEDORDER_XRGB(self):
        self.assertEqual(SDL_PACKEDORDER_XRGB, 1)

    def test_SDL_PACKEDORDER_RGBX(self):
        self.assertEqual(SDL_PACKEDORDER_RGBX, 2)

    def test_SDL_PACKEDORDER_ARGB(self):
        self.assertEqual(SDL_PACKEDORDER_ARGB, 3)

    def test_SDL_PACKEDORDER_RGBA(self):
        self.assertEqual(SDL_PACKEDORDER_RGBA, 4)

    def test_SDL_PACKEDORDER_XBGR(self):
        self.assertEqual(SDL_PACKEDORDER_XBGR, 5)

    def test_SDL_PACKEDORDER_BGRX(self):
        self.assertEqual(SDL_PACKEDORDER_BGRX, 6)

    def test_SDL_PACKEDORDER_ABGR(self):
        self.assertEqual(SDL_PACKEDORDER_ABGR, 7)

    def test_SDL_PACKEDORDER_BGRA(self):
        self.assertEqual(SDL_PACKEDORDER_BGRA, 8)

    def test_SDL_ARRAYORDER_NONE(self):
        self.assertEqual(SDL_ARRAYORDER_NONE, 0)

    def test_SDL_ARRAYORDER_RGB(self):
        self.assertEqual(SDL_ARRAYORDER_RGB, 1)

    def test_SDL_ARRAYORDER_RGBA(self):
        self.assertEqual(SDL_ARRAYORDER_RGBA, 2)

    def test_SDL_ARRAYORDER_ARGB(self):
        self.assertEqual(SDL_ARRAYORDER_ARGB, 3)

    def test_SDL_ARRAYORDER_BGR(self):
        self.assertEqual(SDL_ARRAYORDER_BGR, 4)

    def test_SDL_ARRAYORDER_BGRA(self):
        self.assertEqual(SDL_ARRAYORDER_BGRA, 5)

    def test_SDL_ARRAYORDER_ABGR(self):
        self.assertEqual(SDL_ARRAYORDER_ABGR, 6)

    def test_SDL_PACKEDLAYOUT_NONE(self):
        self.assertEqual(SDL_PACKEDLAYOUT_NONE, 0)

    def test_SDL_PACKEDLAYOUT_332(self):
        self.assertEqual(SDL_PACKEDLAYOUT_332, 1)

    def test_SDL_PACKEDLAYOUT_4444(self):
        self.assertEqual(SDL_PACKEDLAYOUT_4444, 2)

    def test_SDL_PACKEDLAYOUT_1555(self):
        self.assertEqual(SDL_PACKEDLAYOUT_1555, 3)

    def test_SDL_PACKEDLAYOUT_5551(self):
        self.assertEqual(SDL_PACKEDLAYOUT_5551, 4)

    def test_SDL_PACKEDLAYOUT_565(self):
        self.assertEqual(SDL_PACKEDLAYOUT_565, 5)

    def test_SDL_PACKEDLAYOUT_8888(self):
        self.assertEqual(SDL_PACKEDLAYOUT_8888, 6)

    def test_SDL_PACKEDLAYOUT_2101010(self):
        self.assertEqual(SDL_PACKEDLAYOUT_2101010, 7)

    def test_SDL_PACKEDLAYOUT_1010102(self):
        self.assertEqual(SDL_PACKEDLAYOUT_1010102, 8)

    def test_SDL_PIXELFORMAT_UNKNOWN(self):
        self.assertEqual(SDL_PIXELFORMAT_UNKNOWN, 0)

    def test_SDL_PIXELFORMAT_INDEX1LSB(self):
        x = self.pixfmt(SDL_PIXELTYPE_INDEX1, SDL_BITMAPORDER_4321, 0, 1, 0)
        self.assertEqual(SDL_PIXELFORMAT_INDEX1LSB, x)

    def test_SDL_PIXELFORMAT_INDEX1MSB(self):
        x = self.pixfmt(SDL_PIXELTYPE_INDEX1, SDL_BITMAPORDER_1234, 0, 1, 0)
        self.assertEqual(SDL_PIXELFORMAT_INDEX1MSB, x)

    def test_SDL_PIXELFORMAT_INDEX4LSB(self):
        x = self.pixfmt(SDL_PIXELTYPE_INDEX4, SDL_BITMAPORDER_4321, 0, 4, 0)
        self.assertEqual(SDL_PIXELFORMAT_INDEX4LSB, x)

    def test_SDL_PIXELFORMAT_INDEX4MSB(self):
        x = self.pixfmt(SDL_PIXELTYPE_INDEX4, SDL_BITMAPORDER_1234, 0, 4, 0)
        self.assertEqual(SDL_PIXELFORMAT_INDEX4MSB, x)

    def test_SDL_PIXELFORMAT_INDEX8(self):
        x = self.pixfmt(SDL_PIXELTYPE_INDEX8, 0, 0, 8, 1)
        self.assertEqual(SDL_PIXELFORMAT_INDEX8, x)

    def test_SDL_PIXELFORMAT_RGB332(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED8, SDL_PACKEDORDER_XRGB,
                        SDL_PACKEDLAYOUT_332, 8, 1)
        self.assertEqual(SDL_PIXELFORMAT_RGB332, x)

    def test_SDL_PIXELFORMAT_RGB444(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB,
                        SDL_PACKEDLAYOUT_4444, 12, 2)
        self.assertEqual(SDL_PIXELFORMAT_RGB444, x)

    def test_SDL_PIXELFORMAT_RGB555(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB,
                        SDL_PACKEDLAYOUT_1555, 15, 2)
        self.assertEqual(SDL_PIXELFORMAT_RGB555, x)

    def test_SDL_PIXELFORMAT_BGR555(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR,
                        SDL_PACKEDLAYOUT_1555, 15, 2)
        self.assertEqual(SDL_PIXELFORMAT_BGR555, x)

    def test_SDL_PIXELFORMAT_ARGB4444(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB,
                        SDL_PACKEDLAYOUT_4444, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_ARGB4444, x)

    def test_SDL_PIXELFORMAT_RGBA4444(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA,
                        SDL_PACKEDLAYOUT_4444, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_RGBA4444, x)

    def test_SDL_PIXELFORMAT_ABGR4444(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR,
                        SDL_PACKEDLAYOUT_4444, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_ABGR4444, x)

    def test_SDL_PIXELFORMAT_BGRA4444(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA,
                        SDL_PACKEDLAYOUT_4444, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_BGRA4444, x)

    def test_SDL_PIXELFORMAT_ARGB1555(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB,
                        SDL_PACKEDLAYOUT_1555, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_ARGB1555, x)

    def test_SDL_PIXELFORMAT_RGBA5551(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA,
                        SDL_PACKEDLAYOUT_5551, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_RGBA5551, x)

    def test_SDL_PIXELFORMAT_ABGR1555(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR,
                        SDL_PACKEDLAYOUT_1555, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_ABGR1555, x)

    def test_SDL_PIXELFORMAT_BGRA5551(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA,
                        SDL_PACKEDLAYOUT_5551, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_BGRA5551, x)

    def test_SDL_PIXELFORMAT_RGB565(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB,
                        SDL_PACKEDLAYOUT_565, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_RGB565, x)

    def test_SDL_PIXELFORMAT_BGR565(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR,
                        SDL_PACKEDLAYOUT_565, 16, 2)
        self.assertEqual(SDL_PIXELFORMAT_BGR565, x)

    def test_SDL_PIXELFORMAT_RGB24(self):
        x = self.pixfmt(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_RGB, 0, 24, 3)
        self.assertEqual(SDL_PIXELFORMAT_RGB24, x)

    def test_SDL_PIXELFORMAT_BGR24(self):
        x = self.pixfmt(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_BGR, 0, 24, 3)
        self.assertEqual(SDL_PIXELFORMAT_BGR24, x)

    def test_SDL_PIXELFORMAT_RGB888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XRGB,
                        SDL_PACKEDLAYOUT_8888, 24, 4)
        self.assertEqual(SDL_PIXELFORMAT_RGB888, x)

    def test_SDL_PIXELFORMAT_RGBX8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBX,
                        SDL_PACKEDLAYOUT_8888, 24, 4)
        self.assertEqual(SDL_PIXELFORMAT_RGBX8888, x)

    def test_SDL_PIXELFORMAT_BGR888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XBGR,
                        SDL_PACKEDLAYOUT_8888, 24, 4)
        self.assertEqual(SDL_PIXELFORMAT_BGR888, x)

    def test_SDL_PIXELFORMAT_BGRX8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRX,
                        SDL_PACKEDLAYOUT_8888, 24, 4)
        self.assertEqual(SDL_PIXELFORMAT_BGRX8888, x)

    def test_SDL_PIXELFORMAT_ARGB8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB,
                        SDL_PACKEDLAYOUT_8888, 32, 4)
        self.assertEqual(SDL_PIXELFORMAT_ARGB8888, x)

    def test_SDL_PIXELFORMAT_RGBA8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBA,
                        SDL_PACKEDLAYOUT_8888, 32, 4)
        self.assertEqual(SDL_PIXELFORMAT_RGBA8888, x)

    def test_SDL_PIXELFORMAT_ABGR8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ABGR,
                        SDL_PACKEDLAYOUT_8888, 32, 4)
        self.assertEqual(SDL_PIXELFORMAT_ABGR8888, x)

    def test_SDL_PIXELFORMAT_BGRA8888(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRA,
                        SDL_PACKEDLAYOUT_8888, 32, 4)
        self.assertEqual(SDL_PIXELFORMAT_BGRA8888, x)

    def test_SDL_PIXELFORMAT_ARGB2101010(self):
        x = self.pixfmt(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB,
                        SDL_PACKEDLAYOUT_2101010, 32, 4)
        self.assertEqual(SDL_PIXELFORMAT_ARGB2101010, x)

    def test_SDL_PIXELFORMAT_YV12(self):
        x = self.fourcc('Y', 'V', '1', '2')
        self.assertEqual(SDL_PIXELFORMAT_YV12, x)

    def test_SDL_PIXELFORMAT_IYUV(self):
        x = self.fourcc('I', 'Y', 'U', 'V')
        self.assertEqual(SDL_PIXELFORMAT_IYUV, x)

    def test_SDL_PIXELFORMAT_YUY2(self):
        x = self.fourcc('Y', 'U', 'Y', '2')
        self.assertEqual(SDL_PIXELFORMAT_YUY2, x)

    def test_SDL_PIXELFORMAT_UYVY(self):
        x = self.fourcc('U', 'Y', 'V', 'Y')
        self.assertEqual(SDL_PIXELFORMAT_UYVY, x)

    def test_SDL_PIXELFORMAT_YVYU(self):
        x = self.fourcc('Y', 'V', 'Y', 'U')
        self.assertEqual(SDL_PIXELFORMAT_YVYU, x)


class Test_SDL_Palette(unittest.TestCase):
    """Tests SDL_Palette"""

    def setUp(self):
        self.plt = SDL_AllocPalette(8)

    def test_cannot_create(self):
        "Cannot create instances directly"
        self.assertRaises(TypeError, SDL_Palette)
        self.assertRaises(TypeError, SDL_Palette.__new__, SDL_Palette)

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_Palette,), {})

    def test_ncolors(self):
        "ncolors has the correct int value"
        self.assertIs(type(self.plt.ncolors), int)
        self.assertEqual(self.plt.ncolors, 8)

    def test_ncolors_readonly(self):
        "ncolors is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'ncolors', 42)

    def test_freed_ncolors(self):
        "ncolors raises AssertionError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(AssertionError, getattr, self.plt, 'ncolors')

    def test_colors_buffer(self):
        "colors support buffer protocol"
        colors = self.plt.colors
        mem = memoryview(colors)
        self.assertEqual(mem.shape, (8,))

    def test_colors_readonly(self):
        "colors is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'colors', 42)

    def test_freed_colors(self):
        "colors raises AssertionError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(AssertionError, getattr, self.plt, 'colors')

    def test_version(self):
        "version is an integer"
        self.assertIs(type(self.plt.version), int)

    def test_version_readonly(self):
        "version is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'version', 42)

    def test_freed_version(self):
        "version raises AssertionError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(AssertionError, getattr, self.plt, 'version')

    def test_refcount(self):
        "refcount is an integer"
        self.assertIs(type(self.plt.refcount), int)

    def test_refcount_readonly(self):
        "refcount is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'refcount', 42)

    def test_freed_refcount(self):
        "refcount raises AssertionError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(AssertionError, getattr, self.plt, 'refcount')


class Test_SDL_AllocPalette(unittest.TestCase):
    "Tests SDL_AllocPalette()"

    def test_returns_SDL_Palette(self):
        "Returns a SDL_Palette"
        x = SDL_AllocPalette(8)
        self.assertIs(type(x), SDL_Palette)

    def test_negative_ncolors(self):
        "Raises ValueError on negative ncolors"
        self.assertRaises(ValueError, SDL_AllocPalette, -42)


class Test_SDL_FreePalette(unittest.TestCase):
    "Tests SDL_FreePalette()"

    def setUp(self):
        self.plt = SDL_AllocPalette(8)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_FreePalette(self.plt), None)

    def test_double_free(self):
        "Raises AssertionError on double free"
        SDL_FreePalette(self.plt)
        self.assertRaises(AssertionError, SDL_FreePalette, self.plt)


if __name__ == '__main__':
    unittest.main()
