"""test bindings in src/events.h"""
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


from csdl2 import *


class TestEventsConstants(unittest.TestCase):
    """Tests for the availability of constants and their values"""

    def test_SDL_RELEASED(self):
        self.assertEqual(SDL_RELEASED, 0)

    def test_SDL_PRESSED(self):
        self.assertEqual(SDL_PRESSED, 1)

    def test_SDL_FIRSTEVENT(self):
        self.assertEqual(SDL_FIRSTEVENT, 0)

    def test_SDL_QUIT(self):
        self.assertEqual(SDL_QUIT, 0x100)

    def test_SDL_APP_TERMINATING(self):
        self.assertEqual(SDL_APP_TERMINATING, 0x101)

    def test_SDL_APP_LOWMEMORY(self):
        self.assertEqual(SDL_APP_LOWMEMORY, 0x102)

    def test_SDL_APP_WILLENTERBACKGROUND(self):
        self.assertEqual(SDL_APP_WILLENTERBACKGROUND, 0x103)

    def test_SDL_APP_DIDENTERBACKGROUND(self):
        self.assertEqual(SDL_APP_DIDENTERBACKGROUND, 0x104)

    def test_SDL_APP_WILLENTERFOREGROUND(self):
        self.assertEqual(SDL_APP_WILLENTERFOREGROUND, 0x105)

    def test_SDL_APP_DIDENTERFOREGROUND(self):
        self.assertEqual(SDL_APP_DIDENTERFOREGROUND, 0x106)

    def test_SDL_WINDOWEVENT(self):
        self.assertEqual(SDL_WINDOWEVENT, 0x200)

    def test_SDL_SYSWMEVENT(self):
        self.assertEqual(SDL_SYSWMEVENT, 0x201)

    def test_SDL_KEYDOWN(self):
        self.assertEqual(SDL_KEYDOWN, 0x300)

    def test_SDL_KEYUP(self):
        self.assertEqual(SDL_KEYUP, 0x301)

    def test_SDL_TEXTEDITING(self):
        self.assertEqual(SDL_TEXTEDITING, 0x302)

    def test_SDL_TEXTINPUT(self):
        self.assertEqual(SDL_TEXTINPUT, 0x303)

    def test_SDL_MOUSEMOTION(self):
        self.assertEqual(SDL_MOUSEMOTION, 0x400)

    def test_SDL_MOUSEBUTTONDOWN(self):
        self.assertEqual(SDL_MOUSEBUTTONDOWN, 0x401)

    def test_SDL_MOUSEBUTTONUP(self):
        self.assertEqual(SDL_MOUSEBUTTONUP, 0x402)

    def test_SDL_MOUSEWHEEL(self):
        self.assertEqual(SDL_MOUSEWHEEL, 0x403)

    def test_SDL_JOYAXISMOTION(self):
        self.assertEqual(SDL_JOYAXISMOTION, 0x600)

    def test_SDL_JOYBALLMOTION(self):
        self.assertEqual(SDL_JOYBALLMOTION, 0x601)

    def test_SDL_JOYHATMOTION(self):
        self.assertEqual(SDL_JOYHATMOTION, 0x602)

    def test_SDL_JOYBUTTONDOWN(self):
        self.assertEqual(SDL_JOYBUTTONDOWN, 0x603)

    def test_SDL_JOYBUTTONUP(self):
        self.assertEqual(SDL_JOYBUTTONUP, 0x604)

    def test_SDL_JOYDEVICEADDED(self):
        self.assertEqual(SDL_JOYDEVICEADDED, 0x605)

    def test_SDL_JOYDEVICEREMOVED(self):
        self.assertEqual(SDL_JOYDEVICEREMOVED, 0x606)

    def test_SDL_CONTROLLERAXISMOTION(self):
        self.assertEqual(SDL_CONTROLLERAXISMOTION, 0x650)

    def test_SDL_CONTROLLERBUTTONDOWN(self):
        self.assertEqual(SDL_CONTROLLERBUTTONDOWN, 0x651)

    def test_SDL_CONTROLLERBUTTONUP(self):
        self.assertEqual(SDL_CONTROLLERBUTTONUP, 0x652)

    def test_SDL_CONTROLLERDEVICEADDED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEADDED, 0x653)

    def test_SDL_CONTROLLERDEVICEREMOVED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEREMOVED, 0x654)

    def test_SDL_CONTROLLERDEVICEREMAPPED(self):
        self.assertEqual(SDL_CONTROLLERDEVICEREMAPPED, 0x655)

    def test_SDL_FINGERDOWN(self):
        self.assertEqual(SDL_FINGERDOWN, 0x700)

    def test_SDL_FINGERUP(self):
        self.assertEqual(SDL_FINGERUP, 0x701)

    def test_SDL_FINGERMOTION(self):
        self.assertEqual(SDL_FINGERMOTION, 0x702)

    def test_SDL_DOLLARGESTURE(self):
        self.assertEqual(SDL_DOLLARGESTURE, 0x800)

    def test_SDL_DOLLARRECORD(self):
        self.assertEqual(SDL_DOLLARRECORD, 0x801)

    def test_SDL_MULTIGESTURE(self):
        self.assertEqual(SDL_MULTIGESTURE, 0x802)

    def test_SDL_CLIPBOARDUPDATE(self):
        self.assertEqual(SDL_CLIPBOARDUPDATE, 0x900)

    def test_SDL_DROPFILE(self):
        self.assertEqual(SDL_DROPFILE, 0x1000)

    def test_SDL_USEREVENT(self):
        self.assertEqual(SDL_USEREVENT, 0x8000)

    def test_SDL_LASTEVENT(self):
        self.assertEqual(SDL_LASTEVENT, 0xFFFF)


class Test_SDL_Event(unittest.TestCase):
    """Tests csdl2.SDL_Event"""

    def setUp(self):
        self.ev = SDL_Event()

    def test_cannot_subclass(self):
        "Cannot be subclassed"
        self.assertRaises(TypeError, type, 'TestSubclass', (SDL_Event,), {})

    def test_weakref(self):
        "Can create weak reference"
        ref = weakref.ref(self.ev)

    def test_memview(self):
        "Can create memoryview"
        mem = memoryview(self.ev)

    def test_memview_obj(self):
        "memoryview.obj is the SDL_Event"
        mem = memoryview(self.ev)
        self.assertIs(mem.obj, self.ev)

    def test_memview_bytes(self):
        "memoryview is made up of C contiguous bytes"
        mem = memoryview(self.ev)
        self.assertTrue(mem.c_contiguous)
        self.assertTrue(mem.contiguous)
        self.assertEqual(mem.format, 'B')
        self.assertEqual(mem.itemsize, 1)
        self.assertEqual(mem.ndim, 1)
        self.assertEqual(mem.strides, (1,))

    def test_memview_writable(self):
        "memoryview contains valid memory that can be written to"
        mem = memoryview(self.ev)
        self.assertFalse(mem.readonly)
        for i in range(mem.nbytes):
            mem[i] = 42

    def test_memview_zeroes(self):
        "memory of SDL_Event is initialized with 0s"
        mem = memoryview(self.ev)
        zeroes = bytes(mem.nbytes)
        self.assertEqual(mem.tobytes(), zeroes)

    def test_type_attr_get(self):
        "SDL_Event.type gets an int that defaults to 0"
        self.assertIs(type(self.ev.type), int)
        self.assertEqual(self.ev.type, 0)

    def test_type_attr_set(self):
        "SDL_Event.type allows setting an int"
        setattr(self.ev, 'type', 42)

    def test_type_attr_set_no_neg(self):
        "SDL_Event.type raises OverflowError on negative ints"
        self.assertRaises(OverflowError, setattr, self.ev, 'type', -42)

    def test_type_attr_set_no_overflow(self):
        "SDL_Event.type raises OverflowError on ints overflowing Uint32"
        self.assertRaises(OverflowError, setattr, self.ev, 'type', 0xfffffffff)

    def test_type_attr_set_reject_non_int(self):
        "SDL_Event.type rejects non-integers"
        self.assertRaises(TypeError, setattr, self.ev, 'type', 42.0)


class Test_SDL_PumpEvents(unittest.TestCase):
    """Tests SDL_PumpEvents"""

    @classmethod
    def setUpClass(cls):
        SDL_Init(SDL_INIT_EVENTS)

    def test_pump_events(self):
        "SDL_PumpEvents() works"
        self.assertIs(SDL_PumpEvents(), None)


class Test_SDL_PeepEvents(unittest.TestCase):
    """Tests SDL_PeepEvents"""

    def test_ADDEVENT_SDL_Event(self):
        "SDL_ADDEVENT with a SDL_Event works"
        ev = SDL_Event()
        self.assertEqual(SDL_PeepEvents(ev, 1, SDL_ADDEVENT, 0, 0), 1)

    def test_ADDEVENT_writable_buf(self):
        "SDL_ADDEVENT with a writable buffer works"
        mem = memoryview(SDL_Event())
        self.assertEqual(SDL_PeepEvents(mem, 1, SDL_ADDEVENT, 0, 0), 1)

    def test_ADDEVENT_readonly_buf(self):
        "SDL_ADDEVENT with a readonly buffer works"
        mem = memoryview(SDL_Event())
        bites = mem.tobytes()
        self.assertEqual(SDL_PeepEvents(bites, 1, SDL_ADDEVENT, 0, 0), 1)

    def test_ADDEVENT_buf_wrongsize(self):
        "SDL_ADDEVENT with a buffer with wrong size fails with BufferError"
        mem = bytearray(1)
        self.assertRaises(BufferError, SDL_PeepEvents, mem, 1, SDL_ADDEVENT, 0,
                          0)

    def test_PEEKEVENT_SDL_Event(self):
        "SDL_PEEKEVENT with a SDL_Event works"
        ev_type = SDL_USEREVENT + 0
        ev_src, ev_dst = SDL_Event(), SDL_Event()
        ev_src.type = ev_type
        self.assertEqual(ev_dst.type, 0)
        self.assertEqual(SDL_PeepEvents(ev_src, 1, SDL_ADDEVENT, 0, 0), 1)
        self.assertEqual(SDL_PeepEvents(ev_dst, 1, SDL_PEEKEVENT,
                                        ev_type, ev_type), 1)
        self.assertEqual(ev_dst.type, ev_type)

    def test_PEEKEVENT_writable_buf(self):
        "SDL_PEEKEVENT with a writable buffer works"
        ev_type = SDL_USEREVENT + 1
        ev_src, ev_dst = SDL_Event(), memoryview(SDL_Event())
        ev_src.type = ev_type
        self.assertEqual(SDL_PeepEvents(ev_src, 1, SDL_ADDEVENT, 0, 0), 1)
        self.assertEqual(SDL_PeepEvents(ev_dst, 1, SDL_PEEKEVENT,
                                        ev_type, ev_type), 1)
        self.assertEqual(ev_dst.obj.type, ev_type)

    def test_PEEKEVENT_buf_wrongsize(self):
        "SDL_PEEKEVENT with a buffer of wrong size fails with BufferError"
        ev_dst = bytearray(1)
        self.assertRaises(BufferError, SDL_PeepEvents, ev_dst, 1,
                          SDL_PEEKEVENT, 0, 0)

    def test_PEEKEVENT_readonly_buf(self):
        "SDL_PEEKEVENT with a readonly buffer fails with BufferError"
        ev_dst = memoryview(SDL_Event()).tobytes()
        self.assertRaises(BufferError, SDL_PeepEvents, ev_dst, 1,
                          SDL_PEEKEVENT, 0, 0)

    def test_GETEVENT_SDL_Event(self):
        "SDL_GETEVENT with a SDL_Event works"
        ev_type = SDL_USEREVENT + 2
        ev_src, ev_dst = SDL_Event(), SDL_Event()
        ev_src.type = ev_type
        self.assertEqual(SDL_PeepEvents(ev_src, 1, SDL_ADDEVENT, 0, 0), 1)
        self.assertEqual(SDL_PeepEvents(ev_dst, 1, SDL_GETEVENT,
                                        ev_type, ev_type), 1)
        self.assertEqual(ev_dst.type, ev_type)

    def test_GETEVENT_writable_buf(self):
        "SDL_GETEVENT with a writable buffer works"
        ev_type = SDL_USEREVENT + 3
        ev_src, ev_dst = SDL_Event(), memoryview(SDL_Event())
        ev_src.type = ev_type
        self.assertEqual(SDL_PeepEvents(ev_src, 1, SDL_ADDEVENT, 0, 0), 1)
        self.assertEqual(SDL_PeepEvents(ev_dst, 1, SDL_GETEVENT, ev_type,
                                        ev_type), 1)
        self.assertEqual(ev_dst.obj.type, ev_type)

    def test_GETEVENT_buf_wrongsize(self):
        "SDL_GETEVENT with a buffer of wrong size fails with BufferError"
        ev_dst = bytearray(1)
        self.assertRaises(BufferError, SDL_PeepEvents, ev_dst, 1, SDL_GETEVENT,
                          0, 0)

    def test_GETEVENT_readonly_buf(self):
        "SDL_GETEVENT with a readonly buffer fails with BufferError"
        ev_dst = memoryview(SDL_Event()).tobytes()
        self.assertRaises(BufferError, SDL_PeepEvents, ev_dst, 1,
                          SDL_GETEVENT, 0, 0)


class Test_SDL_PushEvent(unittest.TestCase):
    """Tests SDL_PushEvent()"""

    @classmethod
    def setUpClass(cls):
        SDL_Init(SDL_INIT_EVENTS)

    def test_push_SDL_Event(self):
        "Pushing a SDL_Event works"
        ev = SDL_Event()
        self.assertTrue(SDL_PushEvent(ev))

    def test_push_writable_buf(self):
        "Pushing a writable buffer with the same size as SDL_Event works"
        mem = memoryview(SDL_Event())
        self.assertFalse(mem.readonly)
        self.assertTrue(SDL_PushEvent(mem))

    def test_push_readonly_buf(self):
        "Pushing a readonly buffer with the same size as SDL_Event works"
        mem = memoryview(SDL_Event())
        bites = mem.tobytes()
        self.assertTrue(SDL_PushEvent(bites))

    def test_push_None(self):
        "Pushing None fails"
        self.assertRaises(TypeError, SDL_PushEvent, None)

    def test_buffer_wrong_size(self):
        "Pushing a buffer with wrong size fails"
        mem = bytearray(1)
        self.assertRaises(BufferError, SDL_PushEvent, mem)


class Test_SDL_FlushEvents(unittest.TestCase):
    """Tests SDL_FlushEvents()"""

    @classmethod
    def setUpClass(cls):
        SDL_Init(SDL_INIT_EVENTS)

    def test_flush_all(self):
        "SDL_FlushEvents() flushes all events"
        ev = SDL_Event()
        ev.type = SDL_USEREVENT
        SDL_PeepEvents(ev, 1, SDL_ADDEVENT, 0, 0)
        self.assertIs(SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT), None)
        self.assertEqual(SDL_PeepEvents(ev, 1, SDL_GETEVENT,
                                        SDL_USEREVENT, SDL_LASTEVENT), 0)


class Test_SDL_PollEvent(unittest.TestCase):
    """Tests SDL_PollEvent()"""

    @classmethod
    def setUpClass(cls):
        SDL_Init(SDL_INIT_EVENTS)

    def test_SDL_Event(self):
        "Works with SDL_Event"
        ev = SDL_Event()
        ev.type = SDL_USEREVENT
        SDL_PushEvent(ev)
        self.assertTrue(SDL_PollEvent(ev))

    def test_writable_buffer(self):
        "Works with writable buffer"
        ev_src, ev_dst = SDL_Event(), memoryview(SDL_Event())
        ev_src.type = SDL_USEREVENT
        SDL_PushEvent(ev_src)
        self.assertTrue(SDL_PollEvent(ev_dst))

    def test_readonly_buffer(self):
        "Raises BufferError with readonly buffer"
        ev_src, ev_dst = SDL_Event(), memoryview(SDL_Event()).tobytes()
        ev_src.type = SDL_USEREVENT
        SDL_PushEvent(ev_src)
        self.assertRaises(BufferError, SDL_PollEvent, ev_dst)

    def test_buffer_wrong_size(self):
        "Raises BufferError with writable buffer of wrong size"
        ev_src, ev_dst = SDL_Event(), bytearray(1)
        ev_src.type = SDL_USEREVENT
        SDL_PushEvent(ev_src)
        self.assertRaises(BufferError, SDL_PollEvent, ev_dst)


if __name__ == '__main__':
    unittest.main()