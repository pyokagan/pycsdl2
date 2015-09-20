"Array tests"
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


class ArrayViewBaseTest:
    """Common test cases for all array views.

    Subclasses must provide the following attributes:
    * cls: The array view type
    * item_cls: The array element type.
    * items: A list with the items in the test array. Each item must be of type
             `item_cls`.
    * array: The test array. It must support the buffer protocol, so that it
             can be used to construct an array view object. It must have the
             items in `items`.
    """

    def setUp(self):
        self.view = self.cls(self.array)

    def test_buffer(self):
        "implements buffer protocol"
        x = memoryview(self.array)
        y = memoryview(self.view)
        self.assertEqual(y.itemsize, x.itemsize)
        self.assertEqual(y.nbytes, x.nbytes)
        self.assertEqual(y.ndim, x.ndim)
        self.assertIs(y.obj, self.view)
        self.assertEqual(y.shape, x.shape)
        self.assertEqual(y.strides, x.strides)
        self.assertEqual(y.tobytes(), x.tobytes())

    def test_buffer_invalid_ndim(self):
        "constructor raises ValueError if the buffer's ndim != 1"
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        x = np.asarray(self.array)
        self.assertEqual(x.ndim, 1)
        x = np.reshape(x, (x.shape[0] // 2, x.shape[0] // 2))
        self.assertEqual(x.ndim, 2)
        self.assertRaises(ValueError, self.cls, x)

    def test_buffer_invalid_itemsize(self):
        "constructor raises ValueError if the buffer's itemsize is invalid"
        x = memoryview(self.array)
        if x.itemsize == 1:
            arr = array.array('h', [0])
        else:
            arr = bytearray(1)
        self.assertRaises(ValueError, self.cls, arr)

    def test_readonly(self):
        "respects readonly flag of buffer"
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        x = np.asarray(self.array)
        self.assertTrue(x.flags.writeable)
        x.flags.writeable = False
        view = self.cls(x)
        y = memoryview(view)
        self.assertTrue(y.readonly)


class TestEventArrayView(ArrayViewBaseTest, unittest.TestCase):
    "Tests SDL_EventArrayView"
    cls = SDL_EventArrayView
    item_cls = SDL_Event

    def setUp(self):
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        self.items = [SDL_Event(), SDL_Event(), SDL_Event(), SDL_Event()]

        m = self.items[0].motion
        m.type = SDL_MOUSEMOTION
        m.timestamp = 1
        m.windowID = 2
        m.which = 3
        m.state = 4
        m.x = 5
        m.y = 6
        m.xrel = 7
        m.yrel = 8

        m = self.items[1].motion
        m.type = SDL_MOUSEMOTION
        m.timestamp = 9
        m.windowID = 10
        m.which = 11
        m.state = 12
        m.x = 13
        m.y = 14
        m.xrel = 15
        m.yrel = 16

        m = self.items[2].motion
        m.type = SDL_MOUSEMOTION
        m.timestamp = 17
        m.windowID = 18
        m.which = 19
        m.state = 20
        m.x = 21
        m.y = 22
        m.xrel = 23
        m.yrel = 24

        m = self.items[3].motion
        m.type = SDL_MOUSEMOTION
        m.timestamp = 25
        m.windowID = 26
        m.which = 27
        m.state = 28
        m.x = 29
        m.y = 30
        m.xrel = 31
        m.yrel = 32

        self.array = np.array([memoryview(x).tobytes() for x in self.items],
                              '56V')
        super().setUp()


class TestPointArrayView(ArrayViewBaseTest, unittest.TestCase):
    "Tests SDL_PointArrayView"
    cls = SDL_PointArrayView
    item_cls = SDL_Point

    def setUp(self):
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        self.items = [SDL_Point(1, 2), SDL_Point(3, 4), SDL_Point(5, 6),
                      SDL_Point(7, 8)]
        self.array = np.array([(p.x, p.y) for p in self.items], 'i, i')
        super().setUp()


class TestRectArrayView(ArrayViewBaseTest, unittest.TestCase):
    "Tests SDL_RectArrayView"
    cls = SDL_RectArrayView
    item_cls = SDL_Rect

    def setUp(self):
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        self.items = [SDL_Rect(1, 2, 3, 4), SDL_Rect(5, 6, 7, 8),
                      SDL_Rect(9, 10, 11, 12), SDL_Rect(13, 14, 15, 16)]
        self.array = np.array([(r.x, r.y, r.w, r.h) for r in self.items],
                              'i, i, i, i')
        super().setUp()


if __name__ == '__main__':
    unittest.main()
