"""test distutils-related functionality and methods in src/distutils.h"""
import distutils.extension
import distutils.util
import os.path
import subprocess
import sys
import tempfile
import textwrap
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *


class TestGetSystemSDL(unittest.TestCase):
    """Test the interface of PyCSDL2_GetSystemSDL()"""

    def test_return_value(self):
        "Must return either a dict or None"
        ret = PyCSDL2_GetSystemSDL()
        if ret is not None:
            self.assertIs(type(ret), dict)

    def test_return_value_system(self):
        """When a dict is returned, it must have the expected keys and values.

        It must only have the keys 'include_dirs', 'define_macros',
        'undef_macros', 'extra_compile_args', 'library_dirs', 'libraries',
        'runtime_library_dirs' and 'extra_link_args'.

        Values of 'include_dirs', 'define_macros', 'undef_macros',
        'extra_compile_args', 'library_dirs', 'libraries',
        'runtime_library_dirs' and 'extra_link_args' must be a list of strings.

        Value of 'define_macros' must be a list of 2-tuples of (str, str or
        None).
        """
        ret = PyCSDL2_GetSystemSDL()
        if ret is None:
            raise unittest.SkipTest('csdl2 not dynamically linked')
        self.assertEqual(len(ret), 8)

        self.assertIs(type(ret['include_dirs']), list)
        for x in ret['include_dirs']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['define_macros']), list)
        for x in ret['define_macros']:
            self.assertIs(type(x), tuple)
            self.assertEqual(len(x), 2)
            self.assertIs(type(x[0]), str)
            self.assertTrue(type(x[1]) is str or x[1] is None)

        self.assertIs(type(ret['undef_macros']), list)
        for x in ret['undef_macros']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['extra_compile_args']), list)
        for x in ret['extra_compile_args']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['library_dirs']), list)
        for x in ret['library_dirs']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['libraries']), list)
        for x in ret['libraries']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['runtime_library_dirs']), list)
        for x in ret['runtime_library_dirs']:
            self.assertIs(type(x), str)

        self.assertIs(type(ret['extra_link_args']), list)
        for x in ret['extra_link_args']:
            self.assertIs(type(x), str)


class DistutilsBuildMixin:
    """Mixin for writing test cases that builds extensions with distutils

    Building of extensions is done in a sandbox temporary directory.
    Facilities are also provided for running scripts in the directory so as to
    test the built extension.
    """

    def setUp(self):
        self.__dir = tempfile.TemporaryDirectory()
        super().setUp()

    def tearDown(self):
        self.__dir.cleanup()
        super().tearDown()

    def init_ext(self, *args, **kwargs):
        "Initializes distutils Extension with pycsdl2's and SDL's include dirs"
        ext = distutils.extension.Extension(*args, **kwargs)
        # Add pycsdl2.h's include directory
        ext.include_dirs.append(os.path.join(tests_dir, '..', 'include'))
        # If csdl2 is dynamically linked, add its include directories,
        # else add our bundled SDL's include directory so SDL.h can be found
        cfg = PyCSDL2_GetSystemSDL()
        if cfg:
            ext.include_dirs.extend(cfg['include_dirs'])
        else:
            ext.include_dirs.append(os.path.join(tests_dir, '..', 'deps',
                                                 'SDL', 'include'))
        return ext

    def add_ext_src(self, ext, name, contents):
        """Adds a source file `name` with `contents` to `ext`"""
        path = os.path.join(self.__dir.name, name)
        with open(path, 'w') as f:
            f.write(contents)
        ext.sources.append(path)

    def __write_setup(self, f, ext_modules):
        f.write('from distutils.core import setup\n')
        f.write('from distutils.extension import Extension\n')
        mods = []
        for i, ext in enumerate(ext_modules):
            f.write('ext{0} = Extension({1.name!r}, {1.sources!r}, '
                    '{1.include_dirs!r}, {1.define_macros!r}, '
                    '{1.undef_macros!r}, {1.library_dirs!r}, '
                    '{1.libraries!r}, {1.runtime_library_dirs!r}, '
                    '{1.extra_compile_args!r}, '
                    '{1.extra_link_args!r})\n'.format(i, ext))
            mods.append('ext{0}'.format(i))
        f.write("setup(name='csdl2test', "
                "ext_modules=[{0}])".format(', '.join(mods)))

    def build_exts(self, exts):
        """Builds the distutils.extension.Extension in `exts`."""
        setup_path = os.path.join(self.__dir.name, 'setup.py')
        with open(setup_path, 'w') as f:
            self.__write_setup(f, exts)
        subprocess.check_call([sys.executable, setup_path, 'build_ext',
                               '--inplace'], cwd=self.__dir.name,
                              stdout=subprocess.DEVNULL)

    def __write_script(self, f, contents):
        # Propagate our sys.path to the script
        f.write('import sys\n')
        for x in reversed(sys.path):
            f.write('if {0!r} not in sys.path: '
                    'sys.path.insert(0, {0!r})\n'.format(x))
        # Ensure self.__dir is first in sys.path
        f.write('sys.path.insert(0, {0!r})\n'.format(self.__dir.name))
        f.write(contents)

    def check_call_script(self, name, contents, **kwargs):
        """Check call of script `name` with `contents`"""
        script_path = os.path.join(self.__dir.name, name)
        with open(script_path, 'w') as f:
            self.__write_script(f, contents)
        subprocess.check_call([sys.executable, script_path],
                              cwd=self.__dir.name, **kwargs)

    def check_output_script(self, name, contents, **kwargs):
        script_path = os.path.join(self.__dir.name, name)
        with open(script_path, 'w') as f:
            self.__write_script(f, contents)
        return subprocess.check_output([sys.executable, script_path],
                                       cwd=self.__dir.name,
                                       universal_newlines=True, **kwargs)


class TestLinkSystemSDL(DistutilsBuildMixin, unittest.TestCase):
    """Test building and importing an extension that links against system SDL

    This ensures that the return value of PyCSDL2_GetSystemSDL() is correct.
    """

    src = textwrap.dedent('''
    #include <Python.h>
    #include <SDL.h>

    static void log_output_func(void *userdata, int category,
                                SDL_LogPriority priority, const char *message)
    {
        printf("%s", message);
    }

    static PyModuleDef PyCSDL2Test_Module = {
        PyModuleDef_HEAD_INIT,
        /* m_name */ "_csdl2test",
        /* m_doc */  "",
        /* m_size */ -1,
        /* m_methods */ NULL,
        /* m_reload */ NULL,
        /* m_traverse */ NULL,
        /* m_clear */ NULL,
        /* m_free */ NULL
    };

    PyMODINIT_FUNC
    PyInit__csdl2test(void)
    {
        PyObject *m = PyModule_Create(&PyCSDL2Test_Module);
        if (m == NULL) { return NULL; }
        SDL_LogSetOutputFunction(log_output_func, NULL);
        SDL_Log("OK");
        return m;
    }
    ''')

    def test_extension(self):
        """Info returned by PyCSDL2_GetSystemSDL() is valid.

        It should be possible to use the information to compile and import an
        extension that links against the system's SDL library.
        """
        cfg = PyCSDL2_GetSystemSDL()
        if not cfg:
            raise unittest.SkipTest('csdl2 not dynamically linked')
        ext = self.init_ext('_csdl2test', [], **cfg)
        self.add_ext_src(ext, '_csdl2test.c', self.src)
        self.build_exts([ext])
        out = self.check_output_script('test.py', 'import _csdl2test')
        self.assertEqual(out, 'OK')


class TestPyCSDL2_Import(DistutilsBuildMixin, unittest.TestCase):
    """Test building and running an extension that calls PyCSDL2_Import()
    """

    src = textwrap.dedent('''
    #include <pycsdl2.h>

    static PyModuleDef PyCSDL2Test_Module = {
        PyModuleDef_HEAD_INIT,
        /* m_name */ "_csdl2test",
        /* m_doc */  "",
        /* m_size */ -1,
        /* m_methods */ NULL,
        /* m_reload */ NULL,
        /* m_traverse */ NULL,
        /* m_clear */ NULL,
        /* m_free */ NULL
    };

    PyMODINIT_FUNC
    PyInit__csdl2test(void)
    {
        PyObject *m = PyModule_Create(&PyCSDL2Test_Module);
        const PyCSDL2_CAPI *api;
        #ifdef TEST_SAME_POINTER
        const PyCSDL2_CAPI *api2;
        #endif
        if (m == NULL) { return NULL; }
        if (!(api = PyCSDL2_Import())) { Py_DECREF(m); return NULL; }
        #ifdef TEST_SAME_POINTER
        if (!(api2 = PyCSDL2_Import())) { Py_DECREF(m); return NULL; }
        if (api != api2) {
            PyErr_SetString(PyExc_AssertionError, "api != api2");
            Py_DECREF(m);
            return NULL;
        }
        #endif
        return m;
    }
    ''')

    def test_same_pointer(self):
        "When called multiple times, it should return the same ptr"
        ext = self.init_ext('_csdl2test', [])
        ext.define_macros.append(('TEST_SAME_POINTER', None))
        self.add_ext_src(ext, '_csdl2test.c', self.src)
        self.build_exts([ext])
        self.check_call_script('test.py', 'import _csdl2test')


if __name__ == '__main__':
    unittest.main()
