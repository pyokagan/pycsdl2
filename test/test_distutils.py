"""test methods in src/distutils.h"""
import distutils.util
import os.path
import sys
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


if __name__ == '__main__':
    unittest.main()
