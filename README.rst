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

On Windows, the `Windows 7 SDK`_ must be installed.

.. _`Windows 7 SDK`:
   http://www.microsoft.com/en-sg/download/details.aspx?id=8279

On Mac OS X, `XCode`_ must be installed.

.. _`XCode`: https://guide.macports.org/chunked/installing.xcode.html

On other platforms such as Linux, the system must have a C compiler installed.

Once your system satisfies the above requirements, run the following in the
root of the source directory::

    python3 setup.py build

If the build is successful, pycsdl2 can be installed with::

    python3 setup.py install

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
