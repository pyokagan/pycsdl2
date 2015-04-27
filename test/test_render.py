"""test bindings in src/render.h"""
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
        "Raises AssertionError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(AssertionError, SDL_SetRenderDrawColor, self.rdr,
                          0, 0, 0, 0)


class TestRenderClear(unittest.TestCase):
    """Tests SDL_RenderClear()"""

    def setUp(self):
        self.sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(self.sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_RenderClear(self.rdr), None)

    def test_destroyed_renderer(self):
        "Raises AssertionError if the renderer has been destroyed"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(AssertionError, SDL_RenderClear, self.rdr)

    @unittest.skip('FIXME: Causes a segfault')
    def test_freed_surface(self):
        "Raises AssertionError if the surface has been freed"
        SDL_FreeSurface(self.sf)
        self.assertRaises(AssertionError, SDL_RenderClear, self.rdr)


class TestDestroyRenderer(unittest.TestCase):
    """Tests SDL_DestroyRenderer()"""

    def setUp(self):
        sf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0)
        self.rdr = SDL_CreateSoftwareRenderer(sf)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_DestroyRenderer(self.rdr), None)

    def test_double_free(self):
        "Raises AssertionError on double free"
        SDL_DestroyRenderer(self.rdr)
        self.assertRaises(AssertionError, SDL_DestroyRenderer, self.rdr)


if __name__ == '__main__':
    unittest.main()
