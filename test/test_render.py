"""test bindings in src/render.h"""
import distutils.util
import os.path
import sys
import unittest
import weakref
import array


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa
import _csdl2test  # noqa


try:
    # Check for video support. If SDL_Init(SDL_INIT_VIDEO) fails, most probably
    # there is no video support on the system (or there is something wrong with
    # csdl2).
    SDL_Init(SDL_INIT_VIDEO)
    has_video = True
except RuntimeError:
    has_video = False


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


class TestRendererInfo(unittest.TestCase):
    "Tests SDL_RendererInfo"

    def setUp(self):
        self.info = SDL_RendererInfo()

    def test_cannot_subclass(self):
        "Cannot be subclassed"
        self.assertRaises(TypeError, type, 'testtype', (SDL_RendererInfo,), {})

    def test_name(self):
        "name is initalized to None"
        self.assertIsNone(self.info.name)

    def test_name_set_str(self):
        "name can be set to a str"
        self.info.name = 'name'
        self.assertEqual(self.info.name, 'name')

    def test_name_set_invalid_type(self):
        "Raises TypeError if name is set to a not str value"
        self.assertRaises(TypeError, setattr, self.info, 'name', 42)

    def test_flags(self):
        "flags is an int"
        self.assertIs(type(self.info.flags), int)
        self.assertEqual(self.info.flags, 0)

    def test_flags_set(self):
        "flags can be set to an int"
        self.info.flags = 42
        self.assertEqual(self.info.flags, 42)

    def test_num_texture_formats(self):
        "num_texture_formats is an int"
        self.assertIs(type(self.info.num_texture_formats), int)
        self.assertEqual(self.info.num_texture_formats, 0)

    def test_num_texture_formats_set_int(self):
        "num_texture_formats can be set to an int"
        self.info.num_texture_formats = 42
        self.assertEqual(self.info.num_texture_formats, 42)

    def test_texture_formats(self):
        "texture_formats is a buffer with 16 32-bit ints"
        x = self.info.texture_formats
        y = memoryview(x)
        self.assertEqual(y.shape, (16,))
        self.assertEqual(y.itemsize, 4)
        self.assertTrue(y.c_contiguous)
        self.assertFalse(y.readonly)
        self.assertEqual(y.tolist(), [0] * 16)
        z = array.array(y.format, range(16))
        y[:] = z
        self.assertEqual(y.tolist(), z.tolist())

    def test_texture_formats_readonly(self):
        "texture_formats is readonly"
        self.assertRaises(AttributeError, setattr, self.info,
                          'texture_formats', {})

    def test_texture_formats_ref(self):
        "texture_formats can be independently referenced"
        x = self.info.texture_formats
        y = memoryview(x)
        z = array.array(y.format, range(16))
        y[:] = z
        del y
        del self.info
        y = memoryview(x)
        self.assertEqual(y.tolist(), z.tolist())

    def test_max_texture_width(self):
        "max_texture_width is an int"
        self.assertIs(type(self.info.max_texture_width), int)
        self.assertEqual(self.info.max_texture_width, 0)

    def test_max_texture_width_set_int(self):
        "max_texture_width can be set to an int"
        self.info.max_texture_width = 42
        self.assertEqual(self.info.max_texture_width, 42)

    def test_max_texture_height(self):
        "max_texture_height is an int"
        self.assertIs(type(self.info.max_texture_height), int)
        self.assertEqual(self.info.max_texture_height, 0)

    def test_max_texture_height_set_int(self):
        "max_texture_height can be set to an int"
        self.info.max_texture_height = 42
        self.assertEqual(self.info.max_texture_height, 42)

    def test_init(self):
        "Initialize values via init"
        x = array.array(memoryview(self.info.texture_formats).format,
                        range(16))
        self.info.__init__('name', 1, 2, x, 3, 4)
        self.assertEqual(self.info.name, 'name')
        self.assertEqual(self.info.flags, 1)
        self.assertEqual(self.info.num_texture_formats, 2)
        y = memoryview(self.info.texture_formats)
        self.assertEqual(y.tolist(), x.tolist())
        self.assertEqual(self.info.max_texture_width, 3)
        self.assertEqual(self.info.max_texture_height, 4)

    def test_init_kwds(self):
        "Initialize values via init with keyword arguments"
        x = array.array(memoryview(self.info.texture_formats).format,
                        range(16))
        self.info.__init__(name='name', flags=1, num_texture_formats=2,
                           texture_formats=x, max_texture_width=3,
                           max_texture_height=4)
        self.assertEqual(self.info.name, 'name')
        self.assertEqual(self.info.flags, 1)
        self.assertEqual(self.info.num_texture_formats, 2)
        y = memoryview(self.info.texture_formats)
        self.assertEqual(y.tolist(), x.tolist())
        self.assertEqual(self.info.max_texture_width, 3)
        self.assertEqual(self.info.max_texture_height, 4)


class TestRenderer(unittest.TestCase):
    """Tests properties of SDL_Renderer"""

    def test_cannot_create(self):
        "Cannot directly create SDL_Renderer instances"
        self.assertRaises(TypeError, SDL_Renderer)
        self.assertRaises(TypeError, SDL_Renderer.__new__, SDL_Renderer)

    def test_cannot_subclass(self):
        "Cannot be used as a base class"
        self.assertRaises(TypeError, type, "testtype", (SDL_Renderer,), {})


class TestTexture(unittest.TestCase):
    "Tests SDL_Texture"

    def test_cannot_create(self):
        "Cannot directly create SDL_Texture instances"
        self.assertRaises(TypeError, SDL_Texture)
        self.assertRaises(TypeError, SDL_Texture.__new__, SDL_Texture)

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_Texture,), {})


class TestGetNumRenderDrivers(unittest.TestCase):
    """Tests SDL_GetNumRenderDrivers()"""

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_GetNumRenderDrivers()), int)


class TestGetRenderDriverInfo(unittest.TestCase):
    "Tests SDL_GetRenderDriverInfo()"

    def setUp(self):
        if not SDL_GetNumRenderDrivers():
            raise unittest.SkipTest('No render drivers')

    def test_returns_renderer_info(self):
        "Returns a SDL_RendererInfo"
        self.assertIs(type(SDL_GetRenderDriverInfo(0)), SDL_RendererInfo)


class TestCreateWindowAndRenderer(unittest.TestCase):
    """Tests SDL_CreateWindowAndRenderer()"""

    @classmethod
    def setUpClass(cls):
        if not has_video:
            raise unittest.SkipTest('no video support')

    def test_returns_Window_Renderer(self):
        "Returns a (SDL_Window, SDL_Renderer) tuple"
        t = SDL_CreateWindowAndRenderer(32, 32, SDL_WINDOW_HIDDEN)
        self.assertIs(type(t), tuple)
        a, b = t
        self.assertIs(type(a), SDL_Window)
        self.assertIs(type(b), SDL_Renderer)


class TestCreateRenderer(unittest.TestCase):
    """Tests SDL_CreateRenderer()"""

    @classmethod
    def setUpClass(cls):
        if not has_video:
            raise unittest.SkipTest('no video support')

    def setUp(self):
        self.win = SDL_CreateWindow(self.id(), -32, -32, 32, 32,
                                    SDL_WINDOW_HIDDEN)

    def test_returns_SDL_Renderer(self):
        "Returns a SDL_Renderer instance"
        rdr = SDL_CreateRenderer(self.win, -1, 0)
        self.assertIs(type(rdr), SDL_Renderer)

    def test_already_created(self):
        "Raises RuntimeError if the window already has a renderer"
        rdr = SDL_CreateRenderer(self.win, -1, 0)
        self.assertRaises(RuntimeError, SDL_CreateRenderer, self.win, -1, 0)

    def test_destroyed_window(self):
        "Raises AssertionError if the window has already been destroyed"
        SDL_DestroyWindow(self.win)
        self.assertRaises(AssertionError, SDL_CreateRenderer, self.win, -1, 0)


class TestCreateSoftwareRenderer(unittest.TestCase):
    """Tests SDL_CreateSoftwareRenderer()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)

    def test_returns_SDL_Renderer(self):
        "Returns a SDL_Renderer instance"
        rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.assertIs(type(rdr), SDL_Renderer)

    def test_freed_surface(self):
        "Raises AssertionError if the surface has already been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(AssertionError, SDL_CreateSoftwareRenderer, self.sf)


class TestGetRenderer(unittest.TestCase):
    "Tests SDL_GetRenderer()"

    def setUp(self):
        if not has_video:
            raise unittest.SkipTest('no video support')
        self.win = SDL_CreateWindow(self.id(), -32, -32, 32, 32,
                                    SDL_WINDOW_HIDDEN)
        self.rdr = SDL_CreateRenderer(self.win, -1, 0)

    def test_returns_renderer(self):
        "Returns the correct SDL_Renderer"
        self.assertIs(SDL_GetRenderer(self.win), self.rdr)

    def test_del_renderer(self):
        "Returns None if renderer has been deleted"
        del self.rdr
        self.assertIsNone(SDL_GetRenderer(self.win))

    def test_destroyed_renderer(self):
        "Returns None if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertIsNone(SDL_GetRenderer(self.win))

    def test_destroyed_window(self):
        "Raises ValueError if the window has been destroyed"
        SDL_DestroyWindow(self.win)
        self.assertRaises(ValueError, SDL_GetRenderer, self.win)


class TestGetRendererInfo(unittest.TestCase):
    "Tests SDL_GetRendererInfo()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_renderer_info(self):
        "Returns a SDL_RendererInfo"
        self.assertIs(type(SDL_GetRendererInfo(self.rdr)), SDL_RendererInfo)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetRendererInfo, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetRendererInfo, self.rdr)


class TestGetRendererOutputSize(unittest.TestCase):
    "Tests SDL_GetRendererOutputSize()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_int_int(self):
        "Returns an (int, int) tuple"
        t = SDL_GetRendererOutputSize(self.rdr)
        self.assertIs(type(t), tuple)
        a, b = t
        self.assertIs(type(a), int)
        self.assertIs(type(b), int)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetRendererOutputSize, self.rdr)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has already been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetRendererOutputSize, self.rdr)


class TestCreateTexture(unittest.TestCase):
    "Tests SDL_CreateTexture()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_texture(self):
        "Returns a SDL_Texture instance"
        tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC, 32, 32)
        self.assertIs(type(tex), SDL_Texture)

    def test_ref_renderer(self):
        "The returned SDL_Texture references the renderer"
        x = weakref.ref(self.rdr)
        tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC, 32, 32)
        del self.rdr
        del self.sf
        self.assertIsNotNone(x())

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_CreateTexture, self.rdr,
                          SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                          32, 32)

    def test_freed_surface(self):
        "Raises ValueError if renderer surface has already been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_CreateTexture, self.rdr,
                          SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                          32, 32)


class TestCreateTextureFromSurface(unittest.TestCase):
    """Tests SDL_CreateTextureFromSurface()"""

    def setUp(self):
        self.rdr_sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.rdr_sf)
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)

    def test_returns_texture(self):
        "Returns a SDL_Texture instance"
        tex = SDL_CreateTextureFromSurface(self.rdr, self.sf)
        self.assertIs(type(tex), SDL_Texture)

    def test_ref_renderer(self):
        "The returned SDL_Texture references the renderer"
        x = weakref.ref(self.rdr)
        tex = SDL_CreateTextureFromSurface(self.rdr, self.sf)
        del self.rdr
        del self.rdr_sf
        del self.sf
        self.assertIsNotNone(x())

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_CreateTextureFromSurface, self.rdr,
                          self.sf)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_CreateTextureFromSurface, self.rdr,
                          self.sf)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.rdr_sf)
        self.assertRaises(ValueError, SDL_CreateTextureFromSurface, self.rdr,
                          self.sf)


class TestQueryTexture(unittest.TestCase):
    """Tests SDL_QueryTexture()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_tuple(self):
        "Returns tuple (int, int, int, int)"
        t = SDL_QueryTexture(self.tex)
        self.assertIs(type(t), tuple)
        a, b, c, d = t
        self.assertIs(type(a), int)
        self.assertIs(type(b), int)
        self.assertIs(type(c), int)
        self.assertIs(type(d), int)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_QueryTexture, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_QueryTexture, self.tex)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_QueryTexture, self.tex)


class TestSetTextureColorMod(unittest.TestCase):
    """Tests SDL_SetTextureColorMod()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_SetTextureColorMod(self.tex, 255, 255, 255), None)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_SetTextureColorMod, self.tex, 255,
                          255, 255)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetTextureColorMod, self.tex, 255,
                          255, 255)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_SetTextureColorMod, self.tex, 255,
                          255, 255)


class TestGetTextureColorMod(unittest.TestCase):
    """Tests SDL_GetTextureColorMod()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_tuple(self):
        "Returns tuple (int, int, int)"
        t = SDL_GetTextureColorMod(self.tex)
        self.assertIs(type(t), tuple)
        a, b, c = t
        self.assertIs(type(a), int)
        self.assertIs(type(b), int)
        self.assertIs(type(c), int)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_GetTextureColorMod, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetTextureColorMod, self.tex)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetTextureColorMod, self.tex)


class TestSetTextureAlphaMod(unittest.TestCase):
    """Tests SDL_SetTextureAlphaMod()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_SetTextureAlphaMod(self.tex, 255), None)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_SetTextureAlphaMod, self.tex, 255)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetTextureAlphaMod, self.tex, 255)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_SetTextureAlphaMod, self.tex, 255)


class TestGetTextureAlphaMod(unittest.TestCase):
    """Tests SDL_GetTextureAlphaMod()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_int(self):
        "Returns an int"
        x = SDL_GetTextureAlphaMod(self.tex)
        self.assertIs(type(x), int)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_GetTextureAlphaMod, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetTextureAlphaMod, self.tex)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetTextureAlphaMod, self.tex)


class TestSetTextureBlendMode(unittest.TestCase):
    """Tests SDL_SetTextureBlendMode()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        x = SDL_SetTextureBlendMode(self.tex, SDL_BLENDMODE_ADD)
        self.assertIs(x, None)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_SetTextureBlendMode, self.tex,
                          SDL_BLENDMODE_ADD)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetTextureBlendMode, self.tex,
                          SDL_BLENDMODE_ADD)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_SetTextureBlendMode, self.tex,
                          SDL_BLENDMODE_ADD)


class TestGetTextureBlendMode(unittest.TestCase):
    """Tests SDL_GetTextureBlendMode()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_GetTextureBlendMode(self.tex)), int)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_GetTextureBlendMode, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetTextureBlendMode, self.tex)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetTextureBlendMode, self.tex)


class TestUpdateTexture(unittest.TestCase):
    """Tests SDL_UpdateTexture()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        pixels = bytes(16 * 16 * 4)
        rect = SDL_Rect(0, 0, 16, 16)
        x = SDL_UpdateTexture(self.tex, rect, pixels, 16 * 4)
        self.assertIs(x, None)

    def test_no_rect(self):
        "rect can be None"
        pixels = bytes(32 * 32 * 4)
        SDL_UpdateTexture(self.tex, None, pixels, 32 * 4)

    def test_oversized_rect(self):
        "Raises ValueError if rect exceeds texture boundaries"
        rect = SDL_Rect(32, 32, 16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 16 * 4)

    def test_negative_rect(self):
        "Raises ValueError if rect component(s) are negative"
        rect = SDL_Rect(0, 0, -16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 16 * 4)

    def test_invalid_buffer_size(self):
        "Raises BufferError if the buffer is too small"
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(1 * 16 * 4)
        self.assertRaises(BufferError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 1)

    def test_small_pitch(self):
        "pitch can be smaller than the format's bytes per pixel * w"
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(1 * 16 + 16 * 4)
        SDL_UpdateTexture(self.tex, rect, pixels, 1)

    def test_negative_pitch(self):
        "Raises ValueError if pitch is negative"
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, -16)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has already been destroyed"
        SDL_DestroyTexture(self.tex)
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 16 * 4)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 16 * 4)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has already been freed"
        SDL_FreeSurface(self.sf)
        rect = SDL_Rect(0, 0, 16, 16)
        pixels = bytes(16 * 16 * 4)
        self.assertRaises(ValueError, SDL_UpdateTexture, self.tex, rect,
                          pixels, 16 * 4)


class TestLockTexture(unittest.TestCase):
    """Tests SDL_LockTexture()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STREAMING, 32, 32)

    def test_returns_buffer_int(self):
        "Returns (buffer, int) tuple"
        rect = SDL_Rect(0, 0, 16, 16)
        t = SDL_LockTexture(self.tex, rect)
        self.assertIs(type(t), tuple)
        buf, pitch = t
        self.assertIs(type(pitch), int)
        m = memoryview(buf)
        self.assertEqual(m.nbytes, 15 * pitch + 16 * 4)

    def test_no_rect(self):
        "rect can be None"
        buf, pitch = SDL_LockTexture(self.tex, None)
        m = memoryview(buf)
        self.assertEqual(m.nbytes, 31 * pitch + 32 * 4)

    def test_oversized_rect(self):
        "Raises ValueError if rect exceeds texture boundaries"
        rect = SDL_Rect(20, 20, 16, 16)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, rect)

    def test_negative_rect(self):
        "Raises ValueError if rect component(s) are negative"
        rect = SDL_Rect(0, 0, -16, 16)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, rect)

    def test_locked_texture(self):
        "Raises ValueError if texture is locked"
        SDL_LockTexture(self.tex, None)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, None)

    def test_destroyed_texture(self):
        "Raises ValueError if texture has already been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, None)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, None)

    def test_freed_surface(self):
        "Raises ValueError if the renderer surface has already been destroyed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_LockTexture, self.tex, None)


class TestUnlockTexture(unittest.TestCase):
    """Tests SDL_UnlockTexture()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STREAMING, 32, 32)
        self.buf, _ = SDL_LockTexture(self.tex, None)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_UnlockTexture(self.tex), None)

    def test_invalidates_buffer(self):
        "Invalidates the pixel buffer"
        SDL_UnlockTexture(self.tex)
        self.assertRaises(ValueError, memoryview, self.buf)

    def test_no_ref_buffer(self):
        "Works even if we do not have a reference to the pixel buffer"
        del self.buf
        SDL_UnlockTexture(self.tex)

    def test_exported_buffer(self):
        "Raises ValueError if the pixel buffer is exported"
        m = memoryview(self.buf)
        self.assertRaises(ValueError, SDL_UnlockTexture, self.tex)

    def test_unlocked_texture(self):
        "Raises ValueError if the texture is unlocked"
        SDL_UnlockTexture(self.tex)
        self.assertRaises(ValueError, SDL_UnlockTexture, self.tex)

    def test_destroyed_texture(self):
        "Raises ValueError if texture is destroyed"
        SDL_UnlockTexture(self.tex)
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_UnlockTexture, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer is destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_UnlockTexture, self.tex)

    def test_freed_surface(self):
        "Raises ValueError if renderer surface is destroyed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_UnlockTexture, self.tex)


class TestRenderTargetSupported(unittest.TestCase):
    "Tests SDL_RenderTargetSupported()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_bool(self):
        "Returns a bool"
        self.assertIs(type(SDL_RenderTargetSupported(self.rdr)), bool)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderTargetSupported, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderTargetSupported, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderTargetSupported, 42)


class TestSetRenderTarget(unittest.TestCase):
    "Tests SDL_SetRenderTarget()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_SetRenderTarget(self.rdr, self.tex))

    def test_texture_none(self):
        "texture can be None"
        self.assertIsNone(SDL_SetRenderTarget(self.rdr, None))

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetRenderTarget, self.rdr, self.tex)

    def test_freed_surface(self):
        "Raises ValueError if surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_SetRenderTarget, self.rdr, self.tex)

    def test_destroyed_texture(self):
        "Raises ValueError if texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_SetRenderTarget, self.rdr, self.tex)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_SetRenderTarget, self.rdr, 42)
        self.assertRaises(TypeError, SDL_SetRenderTarget, 42, self.tex)


class TestGetRenderTarget(unittest.TestCase):
    "Tests SDL_GetRenderTarget()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET, 32, 32)
        self.tex2 = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, 32, 32)
        SDL_SetRenderTarget(self.rdr, self.tex)

    def test_returns_texture(self):
        "Returns the same SDL_Texture"
        self.assertIs(SDL_GetRenderTarget(self.rdr), self.tex)

    def test_destroyed_texture(self):
        "Returns None if render target texture was destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertIsNone(SDL_GetRenderTarget(self.rdr))

    def test_deleted_texture(self):
        "Returns None if render target texture was deleted"
        del self.tex
        self.assertIsNone(SDL_GetRenderTarget(self.rdr))

    def test_returns_external_set_texture(self):
        "Returns the correct externally-set texture"
        _csdl2test.renderer_set_target(self.rdr, self.tex2)
        self.assertIs(SDL_GetRenderTarget(self.rdr), self.tex2)

    def test_returns_foreign_texture(self):
        "Returns a foreign texture as a void ptr"
        _csdl2test.renderer_set_target(self.rdr)
        x = SDL_GetRenderTarget(self.rdr)
        self.assertIsNotNone(x)
        self.assertIsNot(type(x), SDL_Texture)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetRenderTarget, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetRenderTarget, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_GetRenderTarget, 42)


class TestRenderSetLogicalSize(unittest.TestCase):
    "Tests SDL_RenderSetLogicalSize()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderSetLogicalSize(self.rdr, 32, 32))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderSetLogicalSize, self.rdr, 32,
                          32)

    def test_freed_surface(self):
        "Raises ValueError if surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderSetLogicalSize, self.rdr, 32,
                          32)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderSetLogicalSize, 42, 32, 32)
        self.assertRaises(TypeError, SDL_RenderSetLogicalSize, self.rdr, {},
                          32)
        self.assertRaises(TypeError, SDL_RenderSetLogicalSize, self.rdr, 32,
                          {})


class TestRenderGetLogicalSize(unittest.TestCase):
    "Tests SDL_RenderGetLogicalSize()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_tuple(self):
        "Returns (int, int) tuple"
        t = SDL_RenderGetLogicalSize(self.rdr)
        self.assertIs(type(t), tuple)
        a, b = t
        self.assertIs(type(a), int)
        self.assertIs(type(b), int)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderGetLogicalSize, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderGetLogicalSize, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderGetLogicalSize, 42)


class TestRenderSetViewport(unittest.TestCase):
    "Tests SDL_RenderSetViewport()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rect = SDL_Rect(0, 0, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderSetViewport(self.rdr, self.rect))

    def test_rect_none(self):
        "rect can be None"
        self.assertIsNone(SDL_RenderSetViewport(self.rdr, None))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderSetViewport, self.rdr,
                          self.rect)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderSetViewport, self.rdr,
                          self.rect)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderSetViewport, 42, self.rect)
        self.assertRaises(TypeError, SDL_RenderSetViewport, self.rdr, 42)


class TestRenderGetViewport(unittest.TestCase):
    "Tests SDL_RenderGetViewport()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_rect(self):
        "Returns a SDL_Rect"
        self.assertIs(type(SDL_RenderGetViewport(self.rdr)), SDL_Rect)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderGetViewport, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderGetViewport, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderGetViewport, 42)


class TestRenderSetClipRect(unittest.TestCase):
    "Tests SDL_RenderSetClipRect()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rect = SDL_Rect(0, 0, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderSetClipRect(self.rdr, self.rect))

    def test_rect_none(self):
        "rect can be None"
        self.assertIsNone(SDL_RenderSetClipRect(self.rdr, None))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderSetClipRect, self.rdr,
                          self.rect)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderSetClipRect, self.rdr,
                          self.rect)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderSetClipRect, 42, self.rect)
        self.assertRaises(TypeError, SDL_RenderSetClipRect, self.rdr, 42)


class TestRenderGetClipRect(unittest.TestCase):
    "Tests SDL_RenderGetClipRect()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_rect(self):
        "Returns a new SDL_Rect"
        self.assertIs(type(SDL_RenderGetClipRect(self.rdr)), SDL_Rect)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderGetClipRect, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderGetClipRect, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderGetClipRect, 42)


class TestRenderSetScale(unittest.TestCase):
    "Tests SDL_RenderSetScale()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderSetScale(self.rdr, 2.0, 2.0))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderSetScale, self.rdr, 2.0, 2.0)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderSetScale, self.rdr, 2.0, 2.0)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderSetScale, 42, 2.0, 2.0)
        self.assertRaises(TypeError, SDL_RenderSetScale, self.rdr, None, 2.0)
        self.assertRaises(TypeError, SDL_RenderSetScale, self.rdr, 2.0, None)


class TestRenderGetScale(unittest.TestCase):
    "Tests SDL_RenderGetScale()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_tuple(self):
        "Returns (float, float) tuple"
        t = SDL_RenderGetScale(self.rdr)
        self.assertIs(type(t), tuple)
        a, b = t
        self.assertIs(type(a), float)
        self.assertIs(type(b), float)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderGetScale, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderGetScale, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderGetScale, 42)


class TestSetRenderDrawColor(unittest.TestCase):
    """Tests SDL_SetRenderDrawColor()"""

    def setUp(self):
        sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_SetRenderDrawColor(self.rdr, 0, 0, 0, 0), None)

    def test_neg_color(self):
        "Raises OverflowError on negative integers"
        self.assertRaises(OverflowError, SDL_SetRenderDrawColor, self.rdr, -1,
                          -1, -1, -1)

    def test_overflow_color(self):
        "Raises OverflowError on color integers > 255"
        self.assertRaises(OverflowError, SDL_SetRenderDrawColor, self.rdr,
                          256, 256, 256, 256)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetRenderDrawColor, self.rdr,
                          0, 0, 0, 0)


class TestGetRenderDrawColor(unittest.TestCase):
    "Tests SDL_GetRenderDrawColor()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_tuple(self):
        "Returns an (int, int, int, int) tuple"
        t = SDL_GetRenderDrawColor(self.rdr)
        self.assertIs(type(t), tuple)
        a, b, c, d = t
        self.assertIs(type(a), int)
        self.assertIs(type(b), int)
        self.assertIs(type(c), int)
        self.assertIs(type(d), int)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetRenderDrawColor, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetRenderDrawColor, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_GetRenderDrawColor, 42)


class TestSetRenderDrawBlendMode(unittest.TestCase):
    "Tests SDL_SetRenderDrawBlendMode()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_SetRenderDrawBlendMode(self.rdr,
                                                     SDL_BLENDMODE_ADD))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_SetRenderDrawBlendMode, self.rdr,
                          SDL_BLENDMODE_ADD)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_SetRenderDrawBlendMode, self.rdr,
                          SDL_BLENDMODE_ADD)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_SetRenderDrawBlendMode, 42,
                          SDL_BLENDMODE_ADD)
        self.assertRaises(TypeError, SDL_SetRenderDrawBlendMode, self.rdr,
                          None)


class TestGetRenderDrawBlendMode(unittest.TestCase):
    "Tests SDL_GetRenderDrawBlendMode()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_GetRenderDrawBlendMode(self.rdr)), int)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_GetRenderDrawBlendMode, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_GetRenderDrawBlendMode, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_GetRenderDrawBlendMode, 42)


class TestRenderClear(unittest.TestCase):
    """Tests SDL_RenderClear()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_RenderClear(self.rdr), None)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderClear, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderClear, self.rdr)


class TestRenderDrawPoint(unittest.TestCase):
    "Tests SDL_RenderDrawPoint()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawPoint(self.rdr, 0, 0))

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawPoint, self.rdr, 0, 0)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawPoint, self.rdr, 0, 0)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawPoint, 42, 0, 0)
        self.assertRaises(TypeError, SDL_RenderDrawPoint, self.rdr, None, 0)
        self.assertRaises(TypeError, SDL_RenderDrawPoint, self.rdr, 0, None)


class TestRenderDrawPoints(unittest.TestCase):
    "Tests SDL_RenderDrawPoints()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.points = bytes(memoryview(SDL_Point()).nbytes * 2)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawPoints(self.rdr, self.points, 2))

    def test_buffer_too_small(self):
        "Raises BufferError if the buffer size is too small"
        self.assertRaises(BufferError, SDL_RenderDrawPoints, self.rdr,
                          self.points, 3)

    def test_destroyed_renderer(self):
        "Raises ValueError if renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawPoints, self.rdr,
                          self.points, 2)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawPoints, self.rdr,
                          self.points, 2)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawPoints, 42, self.points, 2)
        self.assertRaises(TypeError, SDL_RenderDrawPoints, self.rdr, None, 2)
        self.assertRaises(TypeError, SDL_RenderDrawPoints, self.rdr,
                          self.points, None)


class TestRenderDrawLine(unittest.TestCase):
    "Tests SDL_RenderDrawLine()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawLine(self.rdr, 0, 0, 1, 1))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawLine, self.rdr, 0, 0, 1, 1)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawLine, self.rdr, 0, 0, 1, 1)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawLine, 42, 0, 0, 1, 1)
        self.assertRaises(TypeError, SDL_RenderDrawLine, self.rdr, {}, 0, 1, 1)
        self.assertRaises(TypeError, SDL_RenderDrawLine, self.rdr, 0, {}, 1, 1)
        self.assertRaises(TypeError, SDL_RenderDrawLine, self.rdr, 0, 0, {}, 1)
        self.assertRaises(TypeError, SDL_RenderDrawLine, self.rdr, 0, 0, 1, {})


class TestRenderDrawLines(unittest.TestCase):
    "Tests SDL_RenderDrawLines()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.points = bytes(memoryview(SDL_Point()).nbytes * 2)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawLines(self.rdr, self.points, 2))

    def test_buffer_too_small(self):
        "Raises BufferError if the buffer is too small"
        self.assertRaises(BufferError, SDL_RenderDrawLines, self.rdr,
                          self.points, 3)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawLines, self.rdr,
                          self.points, 2)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawLines, self.rdr,
                          self.points, 2)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawLines, 42, self.points, 2)
        self.assertRaises(TypeError, SDL_RenderDrawLines, self.rdr, None, 2)
        self.assertRaises(TypeError, SDL_RenderDrawLines, self.rdr,
                          self.points, None)


class TestRenderDrawRect(unittest.TestCase):
    "Tests SDL_RenderDrawRect()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rect = memoryview(SDL_Rect(0, 0, 32, 32)).tobytes()

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawRect(self.rdr, self.rect))

    def test_rect_none(self):
        "rect can be None"
        self.assertIsNone(SDL_RenderDrawRect(self.rdr, None))

    def test_rect_buffer_invalid_size(self):
        "Raises BufferError if rect buffer is of invalid size"
        rect = bytes(1)
        self.assertRaises(BufferError, SDL_RenderDrawRect, self.rdr, rect)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawRect, self.rdr, self.rect)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawRect, self.rdr, self.rect)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawRect, 42, self.rect)
        self.assertRaises(TypeError, SDL_RenderDrawRect, self.rdr, 42)


class TestRenderDrawRects(unittest.TestCase):
    "Tests SDL_RenderDrawRects()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rects = bytes(memoryview(SDL_Rect()).nbytes * 2)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderDrawRects(self.rdr, self.rects, 2))

    def test_buffer_too_small(self):
        "Raises BufferError if the buffer is too small"
        self.assertRaises(BufferError, SDL_RenderDrawRects, self.rdr,
                          self.rects, 3)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderDrawRects, self.rdr,
                          self.rects, 2)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderDrawRects, self.rdr,
                          self.rects, 2)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderDrawRects, 42, self.rects, 2)
        self.assertRaises(TypeError, SDL_RenderDrawRects, self.rdr, None, 2)
        self.assertRaises(TypeError, SDL_RenderDrawRects, self.rdr, self.rects,
                          None)


class TestRenderFillRect(unittest.TestCase):
    """Tests SDL_RenderFillRect()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rect = SDL_Rect(0, 0, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_RenderFillRect(self.rdr, self.rect), None)

    def test_rect_none(self):
        "rect can be None"
        self.assertIs(SDL_RenderFillRect(self.rdr, None), None)

    def test_rect_buffer(self):
        "rect can be a buffer of valid size"
        rect = memoryview(self.rect).tobytes()
        self.assertIs(SDL_RenderFillRect(self.rdr, rect), None)

    def test_rect_buffer_invalid_size(self):
        "Raises BufferError if rect is of invalid buffer size"
        rect = bytes(1)
        self.assertRaises(BufferError, SDL_RenderFillRect, self.rdr, rect)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderFillRect, self.rdr,
                          self.rect)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderFillRect, self.rdr,
                          self.rect)


class TestRenderFillRects(unittest.TestCase):
    "Tests SDL_RenderFillRects()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rects = bytes(memoryview(SDL_Rect()).nbytes * 2)

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_RenderFillRects(self.rdr, self.rects, 2))

    def test_buffer_too_small(self):
        "Raises BufferError if the buffer is too small"
        self.assertRaises(BufferError, SDL_RenderFillRects, self.rdr,
                          self.rects, 3)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderFillRects, self.rdr,
                          self.rects, 2)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderFillRects, self.rdr,
                          self.rects, 2)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderFillRects, 42, self.rects, 2)
        self.assertRaises(TypeError, SDL_RenderFillRects, self.rdr, None, 2)
        self.assertRaises(TypeError, SDL_RenderFillRects, self.rdr, self.rects,
                          None)


class TestRenderCopy(unittest.TestCase):
    """Tests SDL_RenderCopy()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.sf2 = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rdr2 = SDL_CreateSoftwareRenderer(self.sf2)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        srcrect = dstrect = SDL_Rect(0, 0, 32, 32)
        x = SDL_RenderCopy(self.rdr, self.tex, srcrect, dstrect)
        self.assertIs(x, None)

    def test_srcrect_none(self):
        "srcrect can be None"
        dstrect = SDL_Rect(0, 0, 32, 32)
        SDL_RenderCopy(self.rdr, self.tex, None, dstrect)

    def test_dstrect_none(self):
        "dstrect can be None"
        srcrect = SDL_Rect(0, 0, 32, 32)
        SDL_RenderCopy(self.rdr, self.tex, srcrect, None)

    def test_srcrect_dstrect_none(self):
        "Both srcrect and dstrect can be None"
        SDL_RenderCopy(self.rdr, self.tex, None, None)

    def test_renderer_mismatch(self):
        "Raises RuntimeError if the texture's renderer is not `renderer`"
        self.assertRaises(RuntimeError, SDL_RenderCopy, self.rdr2, self.tex,
                          None, None)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has already been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_RenderCopy, self.rdr, self.tex, None,
                          None)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderCopy, self.rdr, self.tex, None,
                          None)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has already been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderCopy, self.rdr, self.tex, None,
                          None)


class TestRenderCopyEx(unittest.TestCase):
    """Tests SDL_RenderCopyEx()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.sf2 = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.rdr2 = SDL_CreateSoftwareRenderer(self.sf2)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        srcrect = dstrect = SDL_Rect(0, 0, 32, 32)
        center = SDL_Point(16, 16)
        x = SDL_RenderCopyEx(self.rdr, self.tex, srcrect, dstrect, 0, center,
                             SDL_FLIP_NONE)
        self.assertIs(x, None)

    def test_srcrect_none(self):
        "srcrect can be None"
        dstrect = SDL_Rect(0, 0, 32, 32)
        center = SDL_Point(16, 16)
        SDL_RenderCopyEx(self.rdr, self.tex, None, dstrect, 0, center,
                         SDL_FLIP_NONE)

    def test_dstrect_none(self):
        "dstrect can be None"
        srcrect = SDL_Rect(0, 0, 32, 32)
        center = SDL_Point(16, 16)
        SDL_RenderCopyEx(self.rdr, self.tex, srcrect, None, 0, center,
                         SDL_FLIP_NONE)

    def test_center_none(self):
        "center can be None"
        srcrect = dstrect = SDL_Rect(0, 0, 32, 32)
        SDL_RenderCopyEx(self.rdr, self.tex, srcrect, dstrect, 0, None,
                         SDL_FLIP_NONE)

    def test_all_none(self):
        "srcrect, dstrect and center can be None"
        SDL_RenderCopyEx(self.rdr, self.tex, None, None, 0, None,
                         SDL_FLIP_NONE)

    def test_renderer_mismatch(self):
        "Raises RuntimeError if the texture's renderer is not `renderer`"
        self.assertRaises(RuntimeError, SDL_RenderCopyEx, self.rdr2, self.tex,
                          None, None, 0, None, SDL_FLIP_NONE)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has already been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_RenderCopyEx, self.rdr, self.tex,
                          None, None, 0, None, SDL_FLIP_NONE)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderCopyEx, self.rdr, self.tex,
                          None, None, 0, None, SDL_FLIP_NONE)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has already been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderCopyEx, self.rdr, self.tex,
                          None, None, 0, None, SDL_FLIP_NONE)


class TestRenderReadPixels(unittest.TestCase):
    "Tests SDL_RenderReadPixels()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.fm = SDL_PIXELFORMAT_RGB332
        self.rect = SDL_Rect(0, 0, 32, 32)
        self.pixels = bytearray(32 * 32)

    def test_returns_none(self):
        "Returns None"
        x = SDL_RenderReadPixels(self.rdr, self.rect, self.fm, self.pixels, 32)
        self.assertIsNone(x)

    def test_rect_none(self):
        "rect can be None"
        x = SDL_RenderReadPixels(self.rdr, None, self.fm, self.pixels, 32)
        self.assertIsNone(x)

    def test_format_zero(self):
        "format can be zero"
        # In this case SDL_PIXELFORMAT_UNKNOWN will be used, which has a bpp of
        # 0. As such, no pixels will be read at all.
        SDL_RenderReadPixels(self.rdr, self.rect, 0, self.pixels, 32)

    def test_negative_rect(self):
        "A negative rect is equivalent to an empty rect"
        rect = SDL_Rect(-32, -32, -32, -32)
        SDL_RenderReadPixels(self.rdr, rect, self.fm, self.pixels, 32)

    def test_oversized_rect(self):
        "SDL will clip the rect to the viewport"
        rect = SDL_Rect(0, 0, 64, 64)
        pixels = bytearray(64 * 64)
        SDL_RenderReadPixels(self.rdr, rect, self.fm, pixels, 64)

    def test_buffer_too_small(self):
        "Raises BufferError if the buffer is too small"
        self.assertRaises(BufferError, SDL_RenderReadPixels, self.rdr,
                          self.rect, self.fm, self.pixels, 33)

    def test_small_pitch(self):
        "pitch can be smaller than the format's bytes per pixel * w"
        SDL_RenderReadPixels(self.rdr, self.rect, self.fm, self.pixels, 1)

    def test_negative_pitch(self):
        "Raises ValueError if pitch is negative"
        self.assertRaises(ValueError, SDL_RenderReadPixels, self.rdr,
                          self.rect, self.fm, self.pixels, -32)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has already been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderReadPixels, self.rdr,
                          self.rect, self.fm, self.pixels, 32)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderReadPixels, self.rdr,
                          self.rect, self.fm, self.pixels, 32)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_RenderReadPixels, 42, self.rect,
                          self.fm, self.pixels, 32)
        self.assertRaises(TypeError, SDL_RenderReadPixels, self.rdr, 42,
                          self.fm, self.pixels, 32)
        self.assertRaises(TypeError, SDL_RenderReadPixels, self.rdr, self.rect,
                          None, self.pixels, 32)
        self.assertRaises(TypeError, SDL_RenderReadPixels, self.rdr, self.rect,
                          self.fm, [], 32)
        self.assertRaises(TypeError, SDL_RenderReadPixels, self.rdr, self.rect,
                          self.fm, self.pixels, None)


class TestRenderPresent(unittest.TestCase):
    """Tests SDL_RenderPresent()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_RenderPresent(self.rdr), None)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_RenderPresent, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_RenderPresent, self.rdr)


class TestDestroyTexture(unittest.TestCase):
    "Tests SDL_DestroyTexture()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_DestroyTexture(self.tex), None)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, SDL_DestroyTexture, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_DestroyTexture, self.tex)

    def test_freed_renderer_surface(self):
        "Raises ValueError if the renderer surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, SDL_DestroyTexture, self.tex)


class TestDestroyRenderer(unittest.TestCase):
    """Tests SDL_DestroyRenderer()"""

    def setUp(self):
        sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_DestroyRenderer(self.rdr), None)

    def test_double_free(self):
        "Raises ValueError on double free"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, SDL_DestroyRenderer, self.rdr)


class TestRendererInfoCreate(unittest.TestCase):
    "Tests PyCSDL2_RendererInfoCreate()"

    def test_returns_rendererinfo(self):
        "Returns a new SDL_RendererInfo"
        x = _csdl2test.rendererinfo()
        self.assertIs(type(x), SDL_RendererInfo)
        self.assertEqual(x.name, 'name')
        self.assertEqual(x.flags, 1)
        self.assertEqual(x.num_texture_formats, 2)
        self.assertEqual(memoryview(x.texture_formats).tolist(),
                         list(range(16)))
        self.assertEqual(x.max_texture_width, 3)
        self.assertEqual(x.max_texture_height, 4)


class TestRendererInfoPtr(unittest.TestCase):
    "Tests PyCSDL2_RendererInfoPtr()"

    def setUp(self):
        self.info = SDL_RendererInfo()

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        self.assertEqual(self.info.name, None)
        _csdl2test.rendererinfo_set_name(self.info)
        self.assertEqual(self.info.name, 'name')

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.rendererinfo_set_name, 42)


class TestRendererCreate(unittest.TestCase):
    "Tests PyCSDL2_RendererCreate()"

    def test_deftarget_surface(self):
        "Returns SDL_Renderer with a SDL_Surface deftarget"
        sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        rdr = _csdl2test.renderer(sf)
        self.assertIs(type(rdr), SDL_Renderer)

    def test_deftarget_window(self):
        "Returns SDL_Renderer with a SDL_Window deftarget"
        if not has_video:
            raise unittest.SkipTest('no video support')
        win = SDL_CreateWindow(self.id(), -32, -32, 32, 32, SDL_WINDOW_HIDDEN)
        rdr = _csdl2test.renderer(win)
        self.assertIs(type(rdr), SDL_Renderer)

    def test_deftarget_invalid(self):
        "Raises AssertionError if the deftarget has invalid type"
        self.assertRaises(AssertionError, _csdl2test.renderer, 42)


class TestRendererPtr(unittest.TestCase):
    "Tests PyCSDL2_RendererPtr()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        SDL_SetRenderDrawColor(self.rdr, 0, 0, 0, 0)
        self.assertEqual(SDL_GetRenderDrawColor(self.rdr), (0, 0, 0, 0))
        _csdl2test.renderer_set_draw_color(self.rdr)
        self.assertEqual(SDL_GetRenderDrawColor(self.rdr),
                         (255, 255, 255, 255))

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, _csdl2test.renderer_set_draw_color,
                          self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, _csdl2test.renderer_set_draw_color,
                          self.rdr)

    def test_invalid_type(self):
        "Raises TypeError if the type is invalid"
        self.assertRaises(TypeError, _csdl2test.renderer_set_draw_color, 42)


class TestTextureCreate(unittest.TestCase):
    "Tests PyCSDL2_TextureCreate()"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_texture(self):
        "Returns a new SDL_Texture"
        tex = _csdl2test.texture(self.rdr)
        self.assertIs(type(tex), SDL_Texture)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, _csdl2test.texture, self.rdr)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, _csdl2test.texture, self.rdr)

    def test_invalid_type(self):
        "Raises TypeError if the type is invalid"
        self.assertRaises(TypeError, _csdl2test.texture, 42)


class TestTexturePtr(unittest.TestCase):
    "Tests PyCSDL2_Texture"

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)
        self.tex = SDL_CreateTexture(self.rdr, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STATIC, 32, 32)

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        x = _csdl2test.texture_get_format(self.tex)
        self.assertIs(type(x), int)
        self.assertEqual(x, SDL_PIXELFORMAT_RGBA8888)

    def test_destroyed_texture(self):
        "Raises ValueError if the texture has been destroyed"
        SDL_DestroyTexture(self.tex)
        self.assertRaises(ValueError, _csdl2test.texture_get_format, self.tex)

    def test_destroyed_renderer(self):
        "Raises ValueError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(ValueError, _csdl2test.texture_get_format, self.tex)

    def test_freed_surface(self):
        "Raises ValueError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(ValueError, _csdl2test.texture_get_format, self.tex)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.texture_get_format, 42)


if __name__ == '__main__':
    unittest.main()
