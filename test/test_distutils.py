"""test methods in src/distutils.h"""
import distutils.util
import os.path
import subprocess
import sys
import tempfile
import textwrap
import unittest


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    tests_dir = os.path.dirname(os.path.abspath(__file__))
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


class TestLinkSystemSDL(unittest.TestCase):
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

    setup_src = textwrap.dedent('''
    from distutils.core import setup
    from distutils.extension import Extension

    ext = Extension('_csdl2test', [{src_path!r}],
                    include_dirs={include_dirs!r},
                    define_macros={define_macros!r},
                    undef_macros={undef_macros!r},
                    extra_compile_args={extra_compile_args!r},
                    library_dirs={library_dirs!r},
                    libraries={libraries!r},
                    runtime_library_dirs={runtime_library_dirs!r},
                    extra_link_args={extra_link_args!r})
    setup(name='_csdl2test', ext_modules=[ext])
    ''')

    test_src = textwrap.dedent('''
    import sys
    sys.path.insert(0, {tempdir!r})
    import _csdl2test
    ''')

    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()

    def tearDown(self):
        self.dir.cleanup()

    def test_extension(self):
        """Info returned by PyCSDL2_GetSystemSDL() is valid.

        It should be possible to use the information to compile and import an
        extension that links against the system's SDL library.
        """
        src_path = os.path.join(self.dir.name, '_csdl2test.c')
        cfg = PyCSDL2_GetSystemSDL()
        if not cfg:
            raise unittest.SkipTest('csdl2 not dynamically linked')
        setup_src = self.setup_src.format(src_path=src_path, **cfg)
        setup_path = os.path.join(self.dir.name, 'setup.py')
        with open(src_path, 'w') as f:
            f.write(self.src)
        with open(setup_path, 'w') as f:
            f.write(setup_src)
        # Build the extension
        subprocess.check_call([sys.executable, setup_path, 'build_ext',
                               '--inplace'], cwd=self.dir.name,
                               stdout=subprocess.DEVNULL)
        test_src = self.test_src.format(tempdir=self.dir.name)
        test_src_path = os.path.join(self.dir.name, 'test.py')
        with open(test_src_path, 'w') as f:
            f.write(test_src)
        out = subprocess.check_output([sys.executable, test_src_path],
                                      universal_newlines=True)
        self.assertEqual(out, 'OK')


if __name__ == '__main__':
    unittest.main()
