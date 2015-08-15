"""test bindings in src/video.h"""
import distutils.util
import os.path
import subprocess
import sys
import unittest


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


class TestVideoConstants(unittest.TestCase):
    """Tests for the availability of constants and their values"""

    def test_SDL_WINDOW_FULLSCREEN(self):
        self.assertEqual(SDL_WINDOW_FULLSCREEN, 0x00000001)

    def test_SDL_WINDOW_OPENGL(self):
        self.assertEqual(SDL_WINDOW_OPENGL, 0x00000002)

    def test_SDL_WINDOW_SHOWN(self):
        self.assertEqual(SDL_WINDOW_SHOWN, 0x00000004)

    def test_SDL_WINDOW_HIDDEN(self):
        self.assertEqual(SDL_WINDOW_HIDDEN, 0x00000008)

    def test_SDL_WINDOW_BORDERLESS(self):
        self.assertEqual(SDL_WINDOW_BORDERLESS, 0x00000010)

    def test_SDL_WINDOW_RESIZABLE(self):
        self.assertEqual(SDL_WINDOW_RESIZABLE, 0x00000020)

    def test_SDL_WINDOW_MINIMIZED(self):
        self.assertEqual(SDL_WINDOW_MINIMIZED, 0x00000040)

    def test_SDL_WINDOW_MAXIMIZED(self):
        self.assertEqual(SDL_WINDOW_MAXIMIZED, 0x00000080)

    def test_SDL_WINDOW_INPUT_GRABBED(self):
        self.assertEqual(SDL_WINDOW_INPUT_GRABBED, 0x00000100)

    def test_SDL_WINDOW_INPUT_FOCUS(self):
        self.assertEqual(SDL_WINDOW_INPUT_FOCUS, 0x00000200)

    def test_SDL_WINDOW_MOUSE_FOCUS(self):
        self.assertEqual(SDL_WINDOW_MOUSE_FOCUS, 0x00000400)

    def test_SDL_WINDOW_FULLSCREEN_DESKTOP(self):
        self.assertEqual(SDL_WINDOW_FULLSCREEN_DESKTOP, 0x00001001)

    def test_SDL_WINDOW_FOREIGN(self):
        self.assertEqual(SDL_WINDOW_FOREIGN, 0x00000800)

    def test_SDL_WINDOWPOS_UNDEFINED_MASK(self):
        self.assertEqual(SDL_WINDOWPOS_UNDEFINED_MASK, 0x1FFF0000)

    def test_SDL_WINDOWPOS_UNDEFINED(self):
        self.assertEqual(SDL_WINDOWPOS_UNDEFINED, 0x1FFF0000)

    def test_SDL_WINDOWPOS_CENTERED_MASK(self):
        self.assertEqual(SDL_WINDOWPOS_CENTERED_MASK, 0x2FFF0000)

    def test_SDL_WINDOWPOS_CENTERED(self):
        self.assertEqual(SDL_WINDOWPOS_CENTERED, 0x2FFF0000)

    def test_SDL_WINDOWEVENT_NONE(self):
        self.assertEqual(SDL_WINDOWEVENT_NONE, 0)

    def test_SDL_WINDOWEVENT_SHOWN(self):
        self.assertEqual(SDL_WINDOWEVENT_SHOWN, 1)

    def test_SDL_WINDOWEVENT_HIDDEN(self):
        self.assertEqual(SDL_WINDOWEVENT_HIDDEN, 2)

    def test_SDL_WINDOWEVENT_EXPOSED(self):
        self.assertEqual(SDL_WINDOWEVENT_EXPOSED, 3)

    def test_SDL_WINDOWEVENT_MOVED(self):
        self.assertEqual(SDL_WINDOWEVENT_MOVED, 4)

    def test_SDL_WINDOWEVENT_RESIZED(self):
        self.assertEqual(SDL_WINDOWEVENT_RESIZED, 5)

    def test_SDL_WINDOWEVENT_SIZE_CHANGED(self):
        self.assertEqual(SDL_WINDOWEVENT_SIZE_CHANGED, 6)

    def test_SDL_WINDOWEVENT_MINIMIZED(self):
        self.assertEqual(SDL_WINDOWEVENT_MINIMIZED, 7)

    def test_SDL_WINDOWEVENT_MAXIMIZED(self):
        self.assertEqual(SDL_WINDOWEVENT_MAXIMIZED, 8)

    def test_SDL_WINDOWEVENT_RESTORED(self):
        self.assertEqual(SDL_WINDOWEVENT_RESTORED, 9)

    def test_SDL_WINDOWEVENT_ENTER(self):
        self.assertEqual(SDL_WINDOWEVENT_ENTER, 10)

    def test_SDL_WINDOWEVENT_LEAVE(self):
        self.assertEqual(SDL_WINDOWEVENT_LEAVE, 11)

    def test_SDL_WINDOWEVENT_FOCUS_GAINED(self):
        self.assertEqual(SDL_WINDOWEVENT_FOCUS_GAINED, 12)

    def test_SDL_WINDOWEVENT_FOCUS_LOST(self):
        self.assertEqual(SDL_WINDOWEVENT_FOCUS_LOST, 13)

    def test_SDL_WINDOWEVENT_CLOSE(self):
        self.assertEqual(SDL_WINDOWEVENT_CLOSE, 14)

    def test_SDL_GL_RED_SIZE(self):
        self.assertEqual(SDL_GL_RED_SIZE, 0)

    def test_SDL_GL_GREEN_SIZE(self):
        self.assertEqual(SDL_GL_GREEN_SIZE, 1)

    def test_SDL_GL_BLUE_SIZE(self):
        self.assertEqual(SDL_GL_BLUE_SIZE, 2)

    def test_SDL_GL_ALPHA_SIZE(self):
        self.assertEqual(SDL_GL_ALPHA_SIZE, 3)

    def test_SDL_GL_BUFFER_SIZE(self):
        self.assertEqual(SDL_GL_BUFFER_SIZE, 4)

    def test_SDL_GL_DOUBLEBUFFER(self):
        self.assertEqual(SDL_GL_DOUBLEBUFFER, 5)

    def test_SDL_GL_DEPTH_SIZE(self):
        self.assertEqual(SDL_GL_DEPTH_SIZE, 6)

    def test_SDL_GL_STENCIL_SIZE(self):
        self.assertEqual(SDL_GL_STENCIL_SIZE, 7)

    def test_SDL_GL_ACCUM_RED_SIZE(self):
        self.assertEqual(SDL_GL_ACCUM_RED_SIZE, 8)

    def test_SDL_GL_ACCUM_GREEN_SIZE(self):
        self.assertEqual(SDL_GL_ACCUM_GREEN_SIZE, 9)

    def test_SDL_GL_ACCUM_BLUE_SIZE(self):
        self.assertEqual(SDL_GL_ACCUM_BLUE_SIZE, 10)

    def test_SDL_GL_ACCUM_ALPHA_SIZE(self):
        self.assertEqual(SDL_GL_ACCUM_ALPHA_SIZE, 11)

    def test_SDL_GL_STEREO(self):
        self.assertEqual(SDL_GL_STEREO, 12)

    def test_SDL_GL_MULTISAMPLEBUFFERS(self):
        self.assertEqual(SDL_GL_MULTISAMPLEBUFFERS, 13)

    def test_SDL_GL_MULTISAMPLESAMPLES(self):
        self.assertEqual(SDL_GL_MULTISAMPLESAMPLES, 14)

    def test_SDL_GL_ACCELERATED_VISUAL(self):
        self.assertEqual(SDL_GL_ACCELERATED_VISUAL, 15)

    def test_SDL_GL_RETAINED_BACKING(self):
        self.assertEqual(SDL_GL_RETAINED_BACKING, 16)

    def test_SDL_GL_CONTEXT_MAJOR_VERSION(self):
        self.assertEqual(SDL_GL_CONTEXT_MAJOR_VERSION, 17)

    def test_SDL_GL_CONTEXT_MINOR_VERSION(self):
        self.assertEqual(SDL_GL_CONTEXT_MINOR_VERSION, 18)

    def test_SDL_GL_CONTEXT_EGL(self):
        self.assertEqual(SDL_GL_CONTEXT_EGL, 19)

    def test_SDL_GL_CONTEXT_FLAGS(self):
        self.assertEqual(SDL_GL_CONTEXT_FLAGS, 20)

    def test_SDL_GL_CONTEXT_PROFILE_MASK(self):
        self.assertEqual(SDL_GL_CONTEXT_PROFILE_MASK, 21)

    def test_SDL_GL_SHARE_WITH_CURRENT_CONTEXT(self):
        self.assertEqual(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 22)

    def test_SDL_GL_CONTEXT_PROFILE_CORE(self):
        self.assertEqual(SDL_GL_CONTEXT_PROFILE_CORE, 0x0001)

    def test_SDL_GL_CONTEXT_PROFILE_COMPATIBILITY(self):
        self.assertEqual(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY, 0x0002)

    def test_SDL_GL_CONTEXT_PROFILE_ES(self):
        self.assertEqual(SDL_GL_CONTEXT_PROFILE_ES, 0x0004)

    def test_SDL_GL_CONTEXT_DEBUG_FLAG(self):
        self.assertEqual(SDL_GL_CONTEXT_DEBUG_FLAG, 0x0001)

    def test_SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG(self):
        self.assertEqual(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, 0x0002)

    def test_SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG(self):
        self.assertEqual(SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG, 0x0004)

    def test_SDL_GL_CONTEXT_RESET_ISOLATION_FLAG(self):
        self.assertEqual(SDL_GL_CONTEXT_RESET_ISOLATION_FLAG, 0x0008)


class TestWindow(unittest.TestCase):
    """Test csdl2.SDL_Window"""

    def test_cannot_create(self):
        "Cannot create SDL_Window instances"
        self.assertRaises(TypeError, SDL_Window)
        self.assertRaises(TypeError, SDL_Window.__new__, SDL_Window)

    def test_cannot_inherit(self):
        "SDL_Window cannot be used as a base class"
        self.assertRaises(TypeError, type, "testtype", (SDL_Window,), {})


class TestCreateWindow(unittest.TestCase):
    """Test SDL_CreateWindow()"""

    def test_returns_SDL_Window(self):
        "SDL_CreateWindow() will succeed and return a SDL_Window"
        if not has_video:
            raise unittest.SkipTest('no video support')
        win = SDL_CreateWindow(self.id(), -32, -32, 32, 32, SDL_WINDOW_HIDDEN)
        self.assertIs(type(win), SDL_Window)


class TestGetWindowTitle(unittest.TestCase):
    "Tests SDL_GetWindowTitle"

    def setUp(self):
        self.win = SDL_CreateWindow('foo', -32, -32, 32, 32, SDL_WINDOW_HIDDEN)

    def test_returns_str(self):
        "Returns a string"
        x = SDL_GetWindowTitle(self.win)
        self.assertIs(type(x), str)
        self.assertEqual(x, 'foo')

    def test_destroyed(self):
        "Raises ValueError if the window has been destroyed"
        SDL_DestroyWindow(self.win)
        self.assertRaises(ValueError, SDL_GetWindowTitle, self.win)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_GetWindowTitle, 42)


class TestDestroyWindow(unittest.TestCase):
    """Tests SDL_DestroyWindow()"""

    def setUp(self):
        self.win = SDL_CreateWindow(self.id(), -32, -32, 32, 32,
                                    SDL_WINDOW_HIDDEN)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_DestroyWindow(self.win), None)

    def test_double_free(self):
        "Raises ValueError on double free"
        SDL_DestroyWindow(self.win)
        self.assertRaises(ValueError, SDL_DestroyWindow, self.win)


class TestWindowCreate(unittest.TestCase):
    "Tests PyCSDL2_WindowCreate()"

    @classmethod
    def setUpClass(cls):
        if not has_video:
            raise unittest.SkipTest('No video support')

    def test_returns_window(self):
        "Returns a new SDL_Window"
        win = _csdl2test.window()
        self.assertIs(type(win), SDL_Window)
        self.assertEqual(SDL_GetWindowTitle(win), 'foo')


class TestWindowPtr(unittest.TestCase):
    "Tests PyCSDL2_WindowPtr()"

    @classmethod
    def setUpClass(cls):
        if not has_video:
            raise unittest.SkipTest('No video support')

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        win = SDL_CreateWindow('foo', -32, -32, 32, 32, SDL_WINDOW_HIDDEN)
        self.assertEqual(SDL_GetWindowTitle(win), 'foo')
        _csdl2test.window_set_title(win)
        self.assertEqual(SDL_GetWindowTitle(win), 'bar')

    def test_destroyed(self):
        "Raises ValueError if the window is already destroyed"
        win = SDL_CreateWindow('foo', -32, -32, 32, 32, SDL_WINDOW_HIDDEN)
        SDL_DestroyWindow(win)
        self.assertRaises(ValueError, _csdl2test.window_set_title, win)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.window_set_title, 42)


if __name__ == '__main__':
    unittest.main()
