"""entry point to run all tests"""
import distutils.util
import os.path
import sys
import unittest


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    tests_dir = os.path.dirname(os.path.abspath(__file__))
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))
    from .test_distutils import *
    from .test_init import *
    unittest.main()
