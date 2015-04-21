File I/O Abstraction
====================
.. module:: csdl2

SDL provides the RWops interface for reading from and writing to various types
of data streams.

.. data:: SDL_RWOPS_UNKNOWN

   Unknown stream type.

.. data:: SDL_RWOPS_WINFILE

   Win32 file.

.. data:: SDL_RWOPS_STDFILE

   Stdio file.

.. data:: SDL_RWOPS_JNIFILE

   Android asset.

.. data:: SDL_RWOPS_MEMORY

   Memory stream.

.. data:: SDL_RWOPS_MEMORY_RO

   Read-only memory stream.

.. data:: RW_SEEK_SET

   Seek from the beginning of data.

.. data:: RW_SEEK_CUR

   Seek relative to current read point.

.. data:: RW_SEEK_END

   Seek relative to the end of data.
