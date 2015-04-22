File I/O Abstraction
====================
.. module:: csdl2

SDL provides the RWops interface for reading from and writing to various types
of data streams.

.. class:: SDL_RWops

   Provides an abstract interface to stream I/O.

   This structure cannot be initiated directly. Instead, use :func:`SDL_AllocRW`,
   :func:`SDL_RWFromFile`, :func:`SDL_RWFromFP`, :func:`SDL_RWFromMem` or :func:`SDL_RWFromConstMem` to create
   an instance of this structure.

   Applications shouldn't have to care about the specifics of this structure.
   They should treat this as an opaque object and use the :func:`SDL_RWsize`,
   :func:`SDL_RWseek`, :func:`SDL_RWtell`, :func:`SDL_RWread`,
   :func:`SDL_RWwrite` and :func:`SDL_RWclose` functions on them.

   .. attribute:: type

      The type of stream. It is currently one of these values, though
      applications can usually ignore this information:

      ============================= ===========================================
      Identifier                    Description
      ============================= ===========================================
      :const:`SDL_RWOPS_UNKNOWN`    Unknown stream type or application defined.
      :const:`SDL_RWOPS_WINFILE`    Win32 file handle.
      :const:`SDL_RWOPS_STDFILE`    stdio ``FILE*``
      :const:`SDL_RWOPS_JNIFILE`    Android asset
      :const:`SDL_RWOPS_MEMORY`     Memory stream (read/write)
      :const:`SDL_RWOPS_MEMORY_RO`  Memory stream (read-only)
      ============================= ===========================================

      Applications and libraries rolling their own implementations should use
      :const:`SDL_RWOPS_UNKNOWN`. All other values are currently reserved for
      SDL's internal use.

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
