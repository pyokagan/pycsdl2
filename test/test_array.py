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

    def test_release(self):
        "release releases the underlying buffer"
        self.assertIsNone(self.view.release())
        self.assertRaises(ValueError, memoryview, self.view)

    def test_len(self):
        "len() returns the array length"
        self.assertEqual(len(self.view), 4)

    def test_getitem(self):
        "getitem returns the element type that points to the array's memory"
        item = self.view[1]
        self.assertIs(type(item), self.item_cls)

        # We can't directly check if the item points to the same memory as the
        # array's memory, so we indirectly check by modifying the array's
        # memory, and then seeing if the modification is reflected in the
        # item's memory as well.
        item_view = memoryview(item)
        arr_view = memoryview(self.array[1:2])
        self.assertEqual(item_view.tobytes(), arr_view.tobytes())
        self.assertNotEqual(arr_view.tobytes(),
                            memoryview(self.array[2:3]).tobytes())
        self.array[1] = self.array[2]
        self.assertEqual(item_view.tobytes(), arr_view.tobytes())

    def test_getitem_neg(self):
        "getitem supports negative indices"
        item = self.view[-2]
        self.assertIs(type(item), self.item_cls)

        # We can't directly check if the item points to the same memory as the
        # array's memory, so we indirectly check by modifying the array's
        # memory, and then seeing if the modification is reflected in the
        # item's memory as well.
        item_view = memoryview(item)
        arr_view = memoryview(self.array[2:3])
        self.assertEqual(item_view.tobytes(), arr_view.tobytes())
        self.assertNotEqual(arr_view.tobytes(),
                            memoryview(self.array[0:1]).tobytes())
        self.array[-2] = self.array[0]
        self.assertEqual(item_view.tobytes(), arr_view.tobytes())

    def test_getitem_oob(self):
        "Raises IndexError if the index is out of bounds"
        self.assertRaises(IndexError, operator.getitem, self.view, 4)
        self.assertRaises(IndexError, operator.getitem, self.view, -5)

    def test_getitem_readonly(self):
        "the element type respects the readonly flag"
        try:
            import numpy as np
        except ImportError:
            raise unittest.SkipTest('could not import numpy')
        x = np.asarray(self.array)
        self.assertTrue(x.flags.writeable)
        x.flags.writeable = False
        view = self.cls(x)
        y = memoryview(view[0])
        self.assertTrue(y.readonly)

    def test_slice(self):
        "slicing works"
        view = self.view[::2]
        self.assertIs(type(view), self.cls)
        self.assertEqual(len(view), 2)

        # Using getitem on the slice should yield the correct elements
        # (their memory contents are the same)
        self.assertEqual(memoryview(view[0]).tobytes(),
                         memoryview(self.array[0:1]).tobytes())
        self.assertEqual(memoryview(view[1]).tobytes(),
                         memoryview(self.array[2:3]).tobytes())

        # Check to see that the buffer info tallies up
        mem = memoryview(view)
        x = memoryview(self.array)
        self.assertEqual(mem.itemsize, x.itemsize)
        self.assertEqual(mem.nbytes, x.itemsize * 2)
        self.assertEqual(mem.ndim, 1)
        self.assertIs(mem.obj, view)
        self.assertEqual(mem.shape, (2,))
        self.assertEqual(mem.strides, (x.itemsize * 2,))

    def test_slice_stride(self):
        "slicing strides should be multiplicative"
        # should be equivalent to doing self.view[::4]
        view = self.view[::2][::2]
        self.assertIs(type(view), self.cls)
        self.assertEqual(len(view), 1)

        # Check to see that the buffer info tallies up
        mem = memoryview(view)
        x = memoryview(self.array)
        self.assertEqual(mem.itemsize, x.itemsize)
        self.assertEqual(mem.nbytes, x.itemsize * 1)
        self.assertEqual(mem.ndim, 1)
        self.assertIs(mem.obj, view)
        self.assertEqual(mem.shape, (1,))
        self.assertEqual(mem.strides, (x.itemsize * 4,))

    def test_slice_neg_stride(self):
        "slicing with negative strides"
        view = self.view[::-2]
        self.assertIs(type(view), self.cls)
        self.assertEqual(len(view), 2)

        # Using getitem on the slice should yield the correct elements
        # (their memory contents are the same)
        self.assertEqual(memoryview(view[0]).tobytes(),
                         memoryview(self.array[3:4]).tobytes())
        self.assertEqual(memoryview(view[1]).tobytes(),
                         memoryview(self.array[1:2]).tobytes())

        # Check to see that the buffer info tallies up
        mem = memoryview(view)
        x = memoryview(self.array)
        self.assertEqual(mem.itemsize, x.itemsize)
        self.assertEqual(mem.nbytes, x.itemsize * 2)
        self.assertEqual(mem.ndim, 1)
        self.assertIs(mem.obj, view)
        self.assertEqual(mem.shape, (2,))
        self.assertEqual(mem.strides, (x.itemsize * -2,))


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
