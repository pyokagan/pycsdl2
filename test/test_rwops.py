"""test bindings in src/rwops.h"""
import distutils.util
import os.path
import sys
import tempfile
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa
import _csdl2test  # noqa


class TestRwopsConstants(unittest.TestCase):
    """Tests for value of constants in SDL_rwops.h"""

    def test_SDL_RWOPS_UNKNOWN(self):
        self.assertEqual(SDL_RWOPS_UNKNOWN, 0)

    def test_SDL_RWOPS_WINFILE(self):
        self.assertEqual(SDL_RWOPS_WINFILE, 1)

    def test_SDL_RWOPS_STDFILE(self):
        self.assertEqual(SDL_RWOPS_STDFILE, 2)

    def test_SDL_RWOPS_JNIFILE(self):
        self.assertEqual(SDL_RWOPS_JNIFILE, 3)

    def test_SDL_RWOPS_MEMORY(self):
        self.assertEqual(SDL_RWOPS_MEMORY, 4)

    def test_SDL_RWOPS_MEMORY_RO(self):
        self.assertEqual(SDL_RWOPS_MEMORY_RO, 5)

    def test_RW_SEEK_SET(self):
        self.assertEqual(RW_SEEK_SET, 0)

    def test_RW_SEEK_CUR(self):
        self.assertEqual(RW_SEEK_CUR, 1)

    def test_RW_SEEKEND(self):
        self.assertEqual(RW_SEEK_END, 2)


class Test_SDL_RWops(unittest.TestCase):
    """Tests for SDL_RWops"""

    def setUp(self):
        self.rw = SDL_AllocRW()

    def test_cannot_create(self):
        "Cannot create SDL_RWops instances"
        self.assertRaises(TypeError, SDL_RWops)
        self.assertRaises(TypeError, SDL_RWops.__new__, SDL_RWops)

    def test_cannot_subclass(self):
        "Cannot be used as a base class"
        self.assertRaises(TypeError, type, "testtype", (SDL_RWops,), {})

    def test_type_is_int(self):
        "SDL_RWops.type is an integer"
        self.assertIs(type(self.rw.type), int)

    def test_type_set_int(self):
        "SDL_RWops.type can be set to an integer"
        self.rw.type = 42
        self.assertEqual(self.rw.type, 42)

    def test_type_set_invalid_type(self):
        "SDL_RWops.type raises a TypeError if not set to an integer"
        self.assertRaises(TypeError, setattr, self.rw, 'type', None)

    def test_freed_type(self):
        "SDL_RWops.type raises an ValueError if the object has been freed"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'type')

    def test_size(self):
        "size is initialized to None"
        self.assertIs(self.rw.size, None)

    def test_size_freed(self):
        "When freed, size raises a ValueError"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'size')

    def test_size_set(self):
        "size can be set to any object"
        x = {}
        self.rw.size = x
        self.assertIs(self.rw.size, x)

    def test_RWsize(self):
        "SDL_RWsize() with custom size callback"
        def size_callback(ctx):
            self.assertIs(ctx, self.rw)
            return 42

        self.rw.size = size_callback
        self.assertEqual(SDL_RWsize(self.rw), 42)

    def test_RWsize_exception(self):
        "SDL_RWsize() with custom exception"
        class SizeException(Exception):
            pass

        def size_callback(ctx):
            raise SizeException()

        self.rw.size = size_callback
        self.assertRaises(SizeException, SDL_RWsize, self.rw)

    def test_seek(self):
        "seek is initialized to None"
        self.assertIs(self.rw.seek, None)

    def test_seek_freed(self):
        "When freed, seek raises a ValueError"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'seek')

    def test_seek_set(self):
        "seek can be set to any object"
        x = {}
        self.rw.seek = x
        self.assertIs(self.rw.seek, x)

    def test_RWseek(self):
        "SDL_RWseek() with custom seek callback"
        def seek_callback(ctx, offset, whence):
            self.assertIs(ctx, self.rw)
            self.assertEqual(offset, 41)
            self.assertEqual(whence, 0)
            return 42

        self.rw.seek = seek_callback
        self.assertEqual(SDL_RWseek(self.rw, 41, 0), 42)

    def test_RWseek_exception(self):
        "SDL_RWseek() with custom exception"
        class SeekException(Exception):
            pass

        def seek_callback(ctx, offset, whence):
            raise SeekException()

        self.rw.seek = seek_callback
        self.assertRaises(SeekException, SDL_RWseek, self.rw, 41, 0)

    def test_read(self):
        "read is initialized to None"
        self.assertIs(self.rw.read, None)

    def test_read_freed(self):
        "When freed, read raises a ValueError"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'read')

    def test_read_set(self):
        "read can be set to any object"
        x = {}
        self.rw.read = x
        self.assertIs(self.rw.read, x)

    def test_RWread(self):
        "SDL_RWread() with custom read callback"
        def read_callback(context, ptr, size, maxnum):
            self.assertIs(context, self.rw)
            self.assertEqual(size, 1)
            self.assertEqual(maxnum, 2)
            with memoryview(ptr) as x:
                self.assertEqual(x.nbytes, 2)
                self.assertFalse(x.readonly)
                x[0] = 1
                x[1] = 2
            return 2

        x = bytearray(2)
        self.rw.read = read_callback
        self.assertEqual(SDL_RWread(self.rw, x, 1, 2), 2)
        self.assertEqual(x, b'\x01\x02')

    def test_RWread_exception(self):
        "SDL_RWread() with custom exception"
        class ReadException(Exception):
            pass

        def read_callback(context, ptr, size, maxnum):
            raise ReadException()

        x = bytearray(2)
        self.rw.read = read_callback
        self.assertRaises(ReadException, SDL_RWread, self.rw, x, 1, 2)

    def test_write(self):
        "write is initialized to None"
        self.assertIs(self.rw.write, None)

    def test_write_freed(self):
        "When freed, write raises ValueError"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'write')

    def test_write_set(self):
        "write can be set to any object"
        x = {}
        self.rw.write = x
        self.assertIs(self.rw.write, x)

    def test_RWwrite(self):
        "SDL_RWwrite() with custom write callback"
        def write_callback(context, ptr, size, num):
            self.assertIs(context, self.rw)
            self.assertEqual(size, 1)
            self.assertEqual(num, 2)
            with memoryview(ptr) as x:
                self.assertEqual(x.nbytes, 2)
                self.assertTrue(x.readonly)
                self.assertEqual(x[0], 1)
                self.assertEqual(x[1], 2)
            return 2

        x = b'\x01\x02'
        self.rw.write = write_callback
        self.assertEqual(SDL_RWwrite(self.rw, x, 1, 2), 2)

    def test_RWwrite_exception(self):
        "SDL_RWwrite() with custom exception"
        class WriteException(Exception):
            pass

        def write_callback(context, ptr, size, num):
            raise WriteException()

        x = b'\x01\x02'
        self.rw.write = write_callback
        self.assertRaises(WriteException, SDL_RWwrite, self.rw, x, 1, 2)

    def test_close(self):
        "close is initialized to None"
        self.assertIs(self.rw.close, None)

    def test_close_freed(self):
        "When freed, close raises ValueError"
        SDL_FreeRW(self.rw)
        self.assertRaises(ValueError, getattr, self.rw, 'close')

    def test_RWclose(self):
        "SDL_RWclose() with custom close callback"
        def close_callback(ctx):
            self.assertIs(ctx, self.rw)
            SDL_FreeRW(ctx)

        self.rw.close = close_callback
        self.assertIs(SDL_RWclose(self.rw), None)

    def test_RWclose_exception(self):
        "SDL_RWclose() with custom exception"
        class CloseException(Exception):
            pass

        def close_callback(ctx):
            raise CloseException()

        self.rw.close = close_callback
        self.assertRaises(CloseException, SDL_RWclose, self.rw)

    def test_RWclose_not_freed(self):
        "SDL_RWclose() with callback that does not call SDL_FreeRW()"
        def close_callback(ctx):
            pass

        self.rw.close = close_callback
        self.assertRaises(AssertionError, SDL_RWclose, self.rw)


class TestRWFromFile_Read(unittest.TestCase):
    "Tests for SDL_RWFromFile(file, 'r')"

    @classmethod
    def setUpClass(cls):
        cls.content = b'TEST'
        cls.dir = tempfile.TemporaryDirectory()

    @classmethod
    def tearDownClass(cls):
        # Handle "directory not empty" errors on Windows by attempting 3 times
        for i in range(3):
            try:
                cls.dir.cleanup()
            except OSError:
                continue
            break

    def setUp(self):
        self.path = os.path.join(self.dir.name, self.id())
        with open(self.path, 'wb') as f:
            f.write(self.content)
        self.rw = SDL_RWFromFile(self.path, 'r')

    def test_return(self):
        "returns SDL_RWops"
        self.assertIs(type(self.rw), SDL_RWops)

    def test_size(self):
        "size() works"
        self.assertEqual(self.rw.size(self.rw), len(self.content))

    def test_size_set(self):
        "size is readonly"
        self.assertRaises(AttributeError, setattr, self.rw, 'size', 42)

    def test_RWsize(self):
        "SDL_RWsize() works"
        self.assertEqual(SDL_RWsize(self.rw), len(self.content))

    def test_seek(self):
        "seek() works"
        self.assertEqual(self.rw.seek(self.rw, 2, RW_SEEK_SET), 2)

    def test_seek_set(self):
        "seek is readonly"
        self.assertRaises(AttributeError, setattr, self.rw, 'seek', 42)

    def test_RWseek(self):
        "SDL_RWseek() works"
        self.assertEqual(SDL_RWseek(self.rw, 2, RW_SEEK_SET), 2)

    def test_read(self):
        "read() works"
        dst = bytearray(len(self.content))
        self.assertEqual(self.rw.read(self.rw, dst, 1, len(self.content)),
                         len(self.content))
        self.assertEqual(dst, self.content)

    def test_read_invalid_size(self):
        "read() raises BufferError if buffer has invalid size"
        dst = bytearray(2)
        self.assertRaises(BufferError, self.rw.read, self.rw, dst, 1,
                          len(self.content))

    def test_read_set(self):
        "read is readonly"
        self.assertRaises(AttributeError, setattr, self.rw, 'read', 42)

    def test_RWread(self):
        "SDL_RWread() works"
        dst = bytearray(len(self.content))
        self.assertEqual(SDL_RWread(self.rw, dst, 1, len(self.content)),
                         len(self.content))
        self.assertEqual(dst, self.content)

    def test_RWread_eof(self):
        "SDL_RWread() returns 0 on EOF without raising an exception"
        dst = bytearray(1)
        contents = b''
        while SDL_RWread(self.rw, dst, 1, 1):
            contents += dst
        self.assertEqual(contents, self.content)

    def test_close(self):
        "close() works"
        self.assertIs(self.rw.close(self.rw), None)
        self.assertRaises(ValueError, getattr, self.rw, 'type')

    def test_close_set(self):
        "close is readonly"
        self.assertRaises(AttributeError, setattr, self.rw, 'close', 42)

    def test_RWclose(self):
        "SDL_RWclose() works"
        self.assertIs(SDL_RWclose(self.rw), None)
        self.assertRaises(ValueError, getattr, self.rw, 'type')


class TestRWFromFile_Write(unittest.TestCase):
    "Tests for SDL_RWFromFile(file, 'w')"

    @classmethod
    def setUpClass(cls):
        cls.dir = tempfile.TemporaryDirectory()

    @classmethod
    def tearDownClass(cls):
        # Handle "directory not empty" errors on Windows by attempting 3 times
        for i in range(3):
            try:
                cls.dir.cleanup()
            except OSError:
                continue
            break

    def setUp(self):
        self.path = os.path.join(self.dir.name, self.id())
        self.rw = SDL_RWFromFile(self.path, 'w')

    def test_return(self):
        "returns SDL_RWops"
        self.assertIs(type(self.rw), SDL_RWops)

    def test_write(self):
        "write() works"
        self.assertEqual(self.rw.write(self.rw, b'TEST', 1, 4), 4)
        del self.rw
        with open(self.path, 'rb') as f:
            self.assertEqual(f.read(), b'TEST')

    def test_write_invalid_size(self):
        "write() raises BufferError when buffer is of invalid size"
        self.assertRaises(BufferError, self.rw.write, self.rw, b'TE', 1, 4)

    def test_write_set(self):
        "write is readonly"
        self.assertRaises(AttributeError, setattr, self.rw, 'write', 42)

    def test_RWwrite(self):
        "SDL_RWwrite() works"
        self.assertEqual(self.rw.write(self.rw, b'TEST', 1, 4), 4)
        del self.rw
        with open(self.path, 'rb') as f:
            self.assertEqual(f.read(), b'TEST')


class TestRWopsCreate(unittest.TestCase):
    "Tests PyCSDL2_RWopsCreate"

    def test_returns_RWops(self):
        "Returns a new SDL_RWops"
        rw = _csdl2test.rwops()
        self.assertIs(type(rw), SDL_RWops)
        self.assertEqual(rw.type, 42)


class TestRWopsPtr(unittest.TestCase):
    "Tests PyCSDL2_RWopsPtr"

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        rw = SDL_AllocRW()
        self.assertEqual(rw.type, 0)
        _csdl2test.rwops_set_type(rw)
        self.assertEqual(rw.type, 42)

    def test_freed(self):
        "Raises ValueError if rwops has been freed"
        rw = SDL_AllocRW()
        SDL_FreeRW(rw)
        self.assertRaises(ValueError, _csdl2test.rwops_set_type, rw)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.rwops_set_type, 42)


if __name__ == '__main__':
    unittest.main()
