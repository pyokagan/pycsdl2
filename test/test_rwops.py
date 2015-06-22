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


from csdl2 import *


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


if __name__ == '__main__':
    unittest.main()
