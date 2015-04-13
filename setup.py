"""setup file for pycsdl2"""
import shlex
import subprocess
from os.path import join
from glob import glob
import distutils.util
from distutils.core import setup
from distutils.extension import Extension


def pkg_config(packages, cflags=False, libs=False):
    """Runs pkg-config and returns its output

    :param packages: list of package names
    :type packages: list of str
    :param cflags bool: Include compile flags
    :param libs bool: Include link flags
    :return: output of pkg-config
    """
    args = ['pkg-config']
    if cflags:
        args.append('--cflags')
    if libs:
        args.append('--libs')
    args.extend(packages)
    return subprocess.check_output(args, universal_newlines=True)


def sdl2_config(cflags=False, libs=False):
    """Runs sdl2-config and returns its output

    :param cflags bool: Include compile flags
    :param libs bool: Include link flags
    :return: output of sdl2-config
    """
    args = ['sdl2-config']
    if cflags:
        args.append('--cflags')
    if libs:
        args.append('--libs')
    return subprocess.check_output(args, universal_newlines=True)


def parse_flags(flags, flag_map, extra_flags_key):
    """Parses flags from str `flags`.

    :param flags str: str of flags and their arguments
    :param flag_map dict: Map flags (as str) to a 2-tuple, the first is the
                          output dict key and the second is a callable
                          that takes a single argument, which is the entire
                          argument excluding the flag, and return the value to
                          append to the list.
    :param extra_flags_key str: Output dict key to use if flag is not present
                                in `flag_map`.
    :return: dict
    """
    out = {}
    for arg in shlex.split(flags):
        for flag, (k, f) in flag_map.items():
            if arg.startswith(flag):
                out.setdefault(k, []).append(f(arg[len(flag):]))
                break
        else:
            out.setdefault(extra_flags_key, []).append(arg)
    return out


def parse_cflags(flags):
    """Parse compile flags

    :param flags str: str of flags and their arguments.
    :return: dict
    """
    flag_map = {
        '-I': ('include_dirs', lambda x: x),
        '-D': ('define_macros',
               lambda x: (x.partition('=')[0], x.partition('=')[2] or None)),
        '-U': ('undef_macros', lambda x: x)
    }
    return parse_flags(flags, flag_map, 'extra_compile_args')


def parse_libs(flags):
    """Parse link flags

    :param flags str: str of flags and their arguments.
    :return: dict
    """
    flag_map = {
        '-L': ('library_dirs', lambda x: x),
        '-l': ('libraries', lambda x: x),
        '-Wl,-rpath,': ('runtime_library_dirs', lambda x: x),
        '-R': ('runtime_library_dirs', lambda x: x)
    }
    return parse_flags(flags, flag_map, 'extra_link_args')


def get_csdl2_base_ext(platform):
    """Returns csdl2 Extension that is not linked to SDL2

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    ext = Extension(name='csdl2',
                    sources=[join('src', 'csdl2.c')])
    headers = glob(join('include', '*.h'))
    return ext, headers


def get_csdl2_ext(platform):
    """Returns csdl2 Extension appropriate for `platform`.

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    return get_csdl2_base_ext(platform)


extension, headers = get_csdl2_ext(distutils.util.get_platform())


setup(name='pycsdl2',
      version='2.0.0a1',
      description='Simple DirectMedia Layer',
      long_description=open('README.rst').read(),
      url='https://github.com/pyokagan/pycsdl2',
      author='Paul Tan',
      author_email='pyokagan@pyokagan.name',
      license='zlib',
      classifiers=[
          'Development Status :: 3 - Alpha',
          'Environment :: MacOS X :: Cocoa',
          'Environment :: Win32 (MS Windows)',
          'Environment :: X11 Applications',
          'Intended Audience :: Developers',
          'License :: OSI Approved :: zlib/libpng License',
          'Operating System :: Microsoft :: Windows',
          'Operating System :: POSIX :: BSD :: FreeBSD',
          'Operating System :: POSIX :: BSD :: NetBSD',
          'Operating System :: POSIX :: BSD :: OpenBSD',
          'Operating System :: POSIX :: Linux',
          'Programming Language :: C',
          'Programming Language :: Python :: Implementation :: CPython',
          'Programming Language :: Python :: 3 :: Only',
          'Programming Language :: Python :: 3.3',
          'Programming Language :: Python :: 3.4',
          'Topic :: Games/Entertainment',
          'Topic :: Multimedia :: Graphics',
          'Topic :: Multimedia :: Graphics :: 3D Rendering',
          'Topic :: Multimedia :: Sound/Audio',
          'Topic :: Multimedia :: Sound/Audio :: Players',
          'Topic :: Multimedia :: Sound/Audio :: Capture/Recording',
          'Topic :: Software Development :: Libraries :: Python Modules'
      ],
      keywords='sdl sdl2 opengl opengles opengles2',
      ext_modules=[extension],
      headers=headers)
