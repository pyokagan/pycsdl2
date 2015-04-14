"""setup file for pycsdl2"""
import os
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


def update_ext(ext, sources=None, include_dirs=None, define_macros=None,
               undef_macros=None, library_dirs=None, libraries=None,
               runtime_library_dirs=None, extra_objects=None,
               extra_compile_args=None, extra_link_args=None,
               export_symbols=None, swig_opts=None, depends=None,
               language=None, optional=None):
    """Updates Extension `ext`"""
    if sources:
        ext.sources.extend(sources)
    if include_dirs:
        ext.include_dirs.extend(include_dirs)
    if define_macros:
        ext.define_macros.extend(define_macros)
    if undef_macros:
        ext.undef_macros.extend(undef_macros)
    if library_dirs:
        ext.library_dirs.extend(library_dirs)
    if libraries:
        ext.libraries.extend(libraries)
    if runtime_library_dirs:
        ext.runtime_library_dirs.extend(runtime_library_dirs)
    if extra_objects:
        ext.extra_objects.extend(extra_objects)
    if extra_compile_args:
        ext.extra_compile_args.extend(extra_compile_args)
    if extra_link_args:
        ext.extra_link_args.extend(extra_link_args)
    if export_symbols:
        ext.export_symbols.extend(export_symbols)
    if swig_opts:
        ext.swig_opts.extend(swig_opts)
    if depends:
        ext.depends.extend(depends)
    if language is not None:
        ext.language = language
    if optional is not None:
        ext.optional = optional


def get_csdl2_base_ext(platform):
    """Returns csdl2 Extension that is not linked to SDL2

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    ext = Extension(name='csdl2',
                    sources=[join('src', 'csdl2.c')])
    headers = glob(join('include', '*.h'))
    return ext, headers


def get_csdl2_system_ext(platform):
    """Returns csdl2 Extension dynamically-linked to system SDL2.

    Requires either pkg-config or sdl2-config to be present in $PATH.

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    PYCSDL2_LIB = os.getenv('PYCSDL2_LIB', 'system')
    ext, headers = get_csdl2_base_ext(platform)
    if PYCSDL2_LIB == 'system':
        try:
            cflags = sdl2_config(cflags=True)
            ldflags = sdl2_config(libs=True)
        except (FileNotFoundError, subprocess.CalledProcessError):
            cflags = pkg_config(['sdl2'], cflags=True)
            ldflags = pkg_config(['sdl2'], libs=True)
    elif PYCSDL2_LIB == 'sdl2-config':
        cflags = sdl2_config(cflags=True)
        ldflags = sdl2_config(libs=True)
    elif PYCSDL2_LIB == 'pkg-config':
        cflags = pkg_config(['sdl2'], cflags=True)
        ldflags = pkg_config(['sdl2'], libs=True)
    else:
        raise ValueError('Unknown PYCSDL2_LIB value {0!r}'.format(PYCSDL2_LIB))
    cflags = parse_cflags(cflags)
    ldflags = parse_libs(ldflags)
    update_ext(ext, **cflags)
    update_ext(ext, **ldflags)
    return ext, headers


def get_csdl2_bundled_ext(platform):
    """Returns csdl2 Extension static-linked to bundled SDL2 source code.

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    ext, headers = get_csdl2_base_ext(platform)
    ext.sources += glob(join('deps', 'SDL', 'src', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'core', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'atomic', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'audio', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'cpuinfo', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'dynapi', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'events', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'file', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'libm', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'stdlib', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'thread', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'timer', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'video', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'video', 'dummy', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'dummy', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'disk', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'joystick', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'haptic', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'power', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'render', '*.c'))
    ext.sources += glob(join('deps', 'SDL', 'src', 'render', '*', '*.c'))
    ext.include_dirs.append(join('deps', 'SDL', 'include'))
    headers.extend(glob(join('deps', 'SDL', 'include', '*.h')))
    if platform in ('win-amd64', 'win32'):
        if 'DXSDK_DIR' not in os.environ:
            raise RuntimeError('DXSDK_DIR environment variable not defined. '
                               'Install the standalone DirectX SDK')
        ext.include_dirs.append(join(os.environ['DXSDK_DIR'], 'Include'))
        if platform == 'win32':
            ext.library_dirs.append(join(os.environ['DXSDK_DIR'], 'Lib',
                                         'x86'))
        elif platform == 'win-amd64':
            ext.library_dirs.append(join(os.environ['DXSDK_DIR'], 'Lib',
                                         'x64'))
        else:
            raise NotImplementedError('Unsupported platform '
                                      '{0}'.format(platform))
        ext.sources += glob(join('deps', 'SDL', 'src', 'core', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'video', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'winmm',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'directsound',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'xaudio2',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'joystick', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'haptic', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'power', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'filesystem', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'timer', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'loadso', 'windows',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'thread', 'windows',
                                 '*.c'))
        ext.sources.append(join('deps', 'SDL', 'src', 'thread', 'generic',
                                'SDL_syscond.c'))
        ext.libraries += ['user32', 'gdi32', 'winmm', 'imm32', 'ole32',
                          'oleaut32', 'shell32', 'version', 'uuid', 'd3d9',
                          'd3dx9', 'kernel32']
    elif platform.startswith('macosx-'):
        ext.define_macros += [('_THREAD_SAFE', None)]
        ext.sources += glob(join('deps', 'SDL', 'src', 'file', 'cocoa', '*.m'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'audio', 'coreaudio',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'joystick', 'darwin',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'haptic', 'darwin',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'power', 'macosx',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'timer', 'unix',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'filesystem', 'cocoa',
                                 '*.m'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'video', 'cocoa',
                                 '*.m'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'thread', 'pthread',
                                 '*.c'))
        ext.sources += glob(join('deps', 'SDL', 'src', 'loadso', 'dlopen',
                                 '*.c'))
        ext.extra_link_args += ['-framework', 'Cocoa',
                                '-framework', 'ForceFeedback',
                                '-framework', 'Carbon',
                                '-framework', 'CoreAudio',
                                '-framework', 'AudioUnit',
                                '-framework', 'OpenGL']
    else:
        raise NotImplementedError('Unsupported platform {0}'.format(platform))
    return ext, headers


def get_csdl2_ext(platform):
    """Returns csdl2 Extension appropriate for `platform`.

    :param platform str: Platform string
    :return: 2-tuple ``(Extension, headers)``
    """
    try:
        return get_csdl2_bundled_ext(platform)
    except NotImplementedError:
        return get_csdl2_system_ext(platform)


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
