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


from csdl2 import *  # noqa
import _csdl2test  # noqa


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
        "ncolors raises ValueError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(ValueError, getattr, self.plt, 'ncolors')

    def test_colors_buffer(self):
        "colors support buffer protocol"
        colors = self.plt.colors
        mem = memoryview(colors)
        self.assertEqual(mem.shape, (8,))

    def test_colors_readonly(self):
        "colors is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'colors', 42)

    def test_freed_colors(self):
        "colors raises ValueError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(ValueError, getattr, self.plt, 'colors')

    def test_version(self):
        "version is an integer"
        self.assertIs(type(self.plt.version), int)

    def test_version_readonly(self):
        "version is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'version', 42)

    def test_freed_version(self):
        "version raises ValueError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(ValueError, getattr, self.plt, 'version')

    def test_refcount(self):
        "refcount is an integer"
        self.assertIs(type(self.plt.refcount), int)

    def test_refcount_readonly(self):
        "refcount is readonly"
        self.assertRaises(AttributeError, setattr, self.plt, 'refcount', 42)

    def test_freed_refcount(self):
        "refcount raises ValueError when freed"
        SDL_FreePalette(self.plt)
        self.assertRaises(ValueError, getattr, self.plt, 'refcount')


class Test_PixelFormat(unittest.TestCase):
    """Tests SDL_PixelFormat"""

    def setUp(self):
        self.pfmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)

    def test_cannot_create(self):
        "Cannot create instances directly"
        self.assertRaises(TypeError, SDL_PixelFormat)
        self.assertRaises(TypeError, SDL_PixelFormat.__new__, SDL_PixelFormat)

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_PixelFormat,), {})

    def test_format(self):
        "format has the correct int value"
        self.assertIs(type(self.pfmt.format), int)
        self.assertEqual(self.pfmt.format, SDL_PIXELFORMAT_RGBA8888)

    def test_format_readonly(self):
        "format is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'format', 42)

    def test_freed_format(self):
        "when freed, format raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'format')

    def test_palette(self):
        "palette has the correct value"
        self.assertIs(self.pfmt.palette, None)

    def test_palette_readonly(self):
        "palette is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'palette', 42)

    def test_freed_palette(self):
        "when freed, palette raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'palette')

    def test_BitsPerPixel(self):
        "BitsPerPixel has the correct int value"
        self.assertIs(type(self.pfmt.BitsPerPixel), int)
        self.assertEqual(self.pfmt.BitsPerPixel, 32)

    def test_BitsPerPixel_readonly(self):
        "BitsPerPixel is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'BitsPerPixel',
                          42)

    def test_freed_BitsPerPixel(self):
        "when freed, BitsPerPixel raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'BitsPerPixel')

    def test_BytesPerPixel(self):
        "BytesPerPixel has the correct int value"
        self.assertIs(type(self.pfmt.BytesPerPixel), int)
        self.assertEqual(self.pfmt.BytesPerPixel, 4)

    def test_BytesPerPixel_readonly(self):
        "BytesPerPixel is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'BytesPerPixel',
                          42)

    def test_freed_BytesPerPixel(self):
        "when freed, BytesPerPixel raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'BytesPerPixel')

    def test_Rmask(self):
        "Rmask has the correct int value"
        self.assertIs(type(self.pfmt.Rmask), int)
        self.assertEqual(self.pfmt.Rmask, 0xFF000000)

    def test_Rmask_readonly(self):
        "Rmask is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Rmask', 42)

    def test_freed_Rmask(self):
        "when freed, Rmask raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Rmask')

    def test_Gmask(self):
        "Gmask has the correct int value"
        self.assertIs(type(self.pfmt.Gmask), int)
        self.assertEqual(self.pfmt.Gmask, 0x00FF0000)

    def test_Gmask_readonly(self):
        "Gmask is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Gmask', 42)

    def test_freed_Gmask(self):
        "when freed, Gmask raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Gmask')

    def test_Bmask(self):
        "Bmask has the correct int value"
        self.assertIs(type(self.pfmt.Bmask), int)
        self.assertEqual(self.pfmt.Bmask, 0x0000FF00)

    def test_Bmask_readonly(self):
        "Bmask is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Bmask', 42)

    def test_freed_Bmask(self):
        "when freed, Bmask raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Bmask')

    def test_Amask(self):
        "Amask has the correct int value"
        self.assertIs(type(self.pfmt.Amask), int)
        self.assertEqual(self.pfmt.Amask, 0x000000FF)

    def test_Amask_readonly(self):
        "Amask is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Amask', 42)

    def test_freed_Amask(self):
        "when freed, Amask raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Amask')

    def test_Rloss(self):
        "Rloss has the correct int value"
        self.assertIs(type(self.pfmt.Rloss), int)
        self.assertEqual(self.pfmt.Rloss, 0)

    def test_Rloss_readonly(self):
        "Rloss is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Rloss', 42)

    def test_freed_Rloss(self):
        "when freed, Rloss raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Rloss')

    def test_Gloss(self):
        "Gloss has the correct int value"
        self.assertIs(type(self.pfmt.Gloss), int)
        self.assertEqual(self.pfmt.Gloss, 0)

    def test_Gloss_readonly(self):
        "Gloss is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Gloss', 42)

    def test_freed_Gloss(self):
        "when freed, Gloss raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Gloss')

    def test_Bloss(self):
        "Bloss has the correct int value"
        self.assertIs(type(self.pfmt.Bloss), int)
        self.assertEqual(self.pfmt.Bloss, 0)

    def test_Bloss_readonly(self):
        "Bloss is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Bloss', 42)

    def test_freed_Bloss(self):
        "when freed, Bloss raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Bloss')

    def test_Aloss(self):
        "Aloss has the correct int value"
        self.assertIs(type(self.pfmt.Aloss), int)
        self.assertEqual(self.pfmt.Aloss, 0)

    def test_Aloss_readonly(self):
        "Aloss is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Aloss', 42)

    def test_freed_Aloss(self):
        "when freed, Aloss raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Aloss')

    def test_Rshift(self):
        "Rshift has the correct int value"
        self.assertIs(type(self.pfmt.Rshift), int)
        self.assertEqual(self.pfmt.Rshift, 24)

    def test_Rshift_readonly(self):
        "Rshift is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Rshift', 42)

    def test_freed_Rshift(self):
        "when freed, Rshift raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Rshift')

    def test_Gshift(self):
        "Gshift has the correct int value"
        self.assertIs(type(self.pfmt.Gshift), int)
        self.assertEqual(self.pfmt.Gshift, 16)

    def test_Gshift_readonly(self):
        "Gshift is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Gshift', 42)

    def test_freed_Gshift(self):
        "when freed, Gshift raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Gshift')

    def test_Bshift(self):
        "Bshift has the correct int value"
        self.assertIs(type(self.pfmt.Bshift), int)
        self.assertEqual(self.pfmt.Bshift, 8)

    def test_Bshift_readonly(self):
        "Bshift is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Bshift', 42)

    def test_freed_Bshift(self):
        "when freed, Bshift raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Bshift')

    def test_Ashift(self):
        "Ashift has the correct int value"
        self.assertIs(type(self.pfmt.Ashift), int)
        self.assertEqual(self.pfmt.Ashift, 0)

    def test_Ashift_readonly(self):
        "Ashift is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'Ashift', 42)

    def test_freed_Ashift(self):
        "when freed, Ashift raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'Ashift')

    def test_refcount(self):
        "refcount has an int value"
        self.assertIs(type(self.pfmt.refcount), int)

    def test_refcount_readonly(self):
        "refcount is readonly"
        self.assertRaises(AttributeError, setattr, self.pfmt, 'refcount', 42)

    def test_freed_refcount(self):
        "when freed, refcount raises ValueError"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, getattr, self.pfmt, 'refcount')


class Test_AllocFormat(unittest.TestCase):
    "Tests SDL_AllocFormat()"

    def test_returns_PixelFormat(self):
        "Returns a SDL_PixelFormat"
        self.assertIs(type(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)),
                      SDL_PixelFormat)

    def test_invalid_format(self):
        "Raises ValueError on invalid format"
        self.assertRaises(ValueError, SDL_AllocFormat, 42)


class Test_FreeFormat(unittest.TestCase):
    "Tests SDL_FreeFormat()"

    def setUp(self):
        self.pfmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_FreeFormat(self.pfmt), None)

    def test_double_free(self):
        "Raises ValueError on double free"
        SDL_FreeFormat(self.pfmt)
        self.assertRaises(ValueError, SDL_FreeFormat, self.pfmt)


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
        "Raises ValueError on double free"
        SDL_FreePalette(self.plt)
        self.assertRaises(ValueError, SDL_FreePalette, self.plt)


class TestPaletteCreate(unittest.TestCase):
    "Tests PyCSDL2_PaletteCreate()"

    def test_returns_Palette(self):
        "Returns a new SDL_Palette"
        plt = _csdl2test.palette()
        self.assertIs(type(plt), SDL_Palette)
        self.assertEqual(plt.ncolors, 2)
        x = memoryview(plt.colors)
        self.assertEqual(x.shape, (2,))


class TestPalettePtr(unittest.TestCase):
    "Tests PyCSDL2_PalettePtr()"

    def test_converter(self):
        "Can be used as a converter"
        plt = SDL_AllocPalette(2)
        self.assertEqual(plt.ncolors, 2)
        _csdl2test.palette_set_ncolors(plt)
        self.assertEqual(plt.ncolors, 42)

    def test_freed(self):
        "Raises ValueError if palette has been freed"
        plt = SDL_AllocPalette(2)
        SDL_FreePalette(plt)
        self.assertRaises(ValueError, _csdl2test.palette_set_ncolors, plt)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.palette_set_ncolors, 42)


class TestPixelFormatCreate(unittest.TestCase):
    "Tests PyCSDL2_PixelFormatCreate()"

    def test_returns_PixelFormat(self):
        "Returns a new SDL_PixelFormat"
        pfmt = _csdl2test.pixel_format()
        self.assertIs(type(pfmt), SDL_PixelFormat)
        self.assertEqual(pfmt.format, SDL_PIXELFORMAT_INDEX8)
        self.assertIsNone(pfmt.palette)
        self.assertEqual(pfmt.BitsPerPixel, 8)
        self.assertEqual(pfmt.BytesPerPixel, 1)


class TestPixelFormatPtr(unittest.TestCase):
    "Tests PyCSDL2_PixelFormatPtr()"

    def test_converter(self):
        "Can be used as a converter"
        # We use an indexed format to ensure that it is not shared with other
        # callers.
        pfmt = SDL_AllocFormat(SDL_PIXELFORMAT_INDEX8)
        self.assertEqual(pfmt.BitsPerPixel, 8)
        _csdl2test.pixel_format_set_bpp(pfmt)
        self.assertEqual(pfmt.BitsPerPixel, 42)

    def test_freed(self):
        "Raises ValueError if pixel format has been freed"
        pfmt = SDL_AllocFormat(SDL_PIXELFORMAT_INDEX8)
        SDL_FreeFormat(pfmt)
        self.assertRaises(ValueError, _csdl2test.pixel_format_set_bpp, pfmt)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.pixel_format_set_bpp, 42)


if __name__ == '__main__':
    unittest.main()
