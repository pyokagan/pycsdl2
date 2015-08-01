"""test bindings in src/render.h"""
import distutils.util
import os.path
import sys
import unittest
import weakref


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
