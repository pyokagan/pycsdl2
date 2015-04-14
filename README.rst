=======
pycsdl2
=======
`pycsdl2` is a low-overhead, compiled `SDL2`_ binding for CPython. It aims to
provide the familiar C API of SDL2, while offering several `Pythonic`_ features
such as automatic memory management, bounds checking and exceptions.

.. _SDL2: https://www.libsdl.org/

.. _Pythonic: https://www.python.org/dev/peps/pep-0020/

Building
========
Building the source code requires the CPython header files to be installed.
This may require the installation of a development package such as
``python3-dev`` in Debian. The headers are installed by default in the
`official Python distributions`_ for Windows and Mac OS X.

.. _`official Python distributions`: https://www.python.org/downloads/

On Windows and Mac OS X, pycsdl2 will be statically linked against the
bundled SDL2 source code. As such,

* on Windows, the `Windows 7 SDK`_ and the `Standalone DirectX SDK`_ must be
  installed.

* on Mac OS X, `XCode`_ must be installed.

.. _`Windows 7 SDK`:
   http://www.microsoft.com/en-sg/download/details.aspx?id=8279

.. _`Standalone DirectX SDK`:
   http://www.microsoft.com/en-sg/download/details.aspx?id=6812

.. _`XCode`: https://guide.macports.org/chunked/installing.xcode.html

On other platforms such as Linux, the system must have a C compiler installed
and the SDL2 library and header files installed. This may require the
installation of a development package such as ``libsdl2-dev`` on Debian.
Furthermore, a working installation of ``sdl2-config`` or ``pkg-config`` must
be present in the executable search paths. pycsdl2 will be dynamically linked
to the SDL2 library on these platforms.

Once your system satisfies the above requirements, run the following in the
root of the source directory::

    python3 setup.py build

If the build is successful, pycsdl2 can be installed with::

    python3 setup.py install

The above build behavior can be controlled with the environment variable
``PYCSDL2_LIB``:

* setting it to ``auto`` will use the default behavior. ``setup.py`` will build
  and link against the bundled SDL2 source code on Windows and Mac OS X, and
  link against the system SDL2 library on other platforms.

* setting it to ``bundled`` will force ``setup.py`` to build and link
  against the bundled SDL2 source code.

* setting it to ``system`` will force ``setup.py`` to link against the system's
  SDL2 library. ``sdl2-config`` will be used to retrieve the required compile
  and link flags, and if it fails, ``pkg-config`` will be used instead.

* setting it to ``sdl2-config`` or ``pkg-config`` will force ``setup.py`` to
  link against the system's SDL2 library, and to only use ``sdl2-config`` or
  ``pkg-config`` respectively to retrieve the required compile and link flags.

Understanding the source code
=============================
The source code is documented with `Doxygen`_. If you have a working
installation, simply run the following in the root of the source directory::

    doxygen

The HTML documentation will be written to the ``apidocs/html`` directory.

.. _`Doxygen`: http://www.stack.nl/~dimitri/doxygen/

License
=======
Unless otherwise stated, `pycsdl2` source code is licensed under the `zlib`
license.

`pycsdl2` source code contains an unmodified copy of the
`Simple DirectMedia Layer` (SDL) version 2.0.0 source code. The source code is
licensed under the `zlib` license.
