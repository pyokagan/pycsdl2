File I/O Abstraction
====================
.. currentmodule:: csdl2

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

   .. attribute:: size

      A function that reports the stream's total size in bytes. It must the
      same function signature as :func:`SDL_RWsize`.

   .. attribute:: seek

      A function that positions the next read/write operation in the stream. It
      must have the same function signature as :func:`SDL_RWseek`.

   .. attribute:: read

      A function that reads from the stream. It must have the same function
      signature as :func:`SDL_RWread`.

   .. attribute:: write

      A function that writes to the stream. It must have the same function
      signature as :func:`SDL_RWwrite`.

   .. attribute:: close

      A function that cleans up the stream. It must release any resources
      used by the stream and free the :class:`SDL_RWops` itself with
      :func:`SDL_FreeRW`. It must have the same function signature as
      :func:`SDL_RWclose`.

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

.. function:: SDL_RWFromFile(file: str, mode: str) -> SDL_RWops

   Creates and returns a :class:`SDL_RWops` structure for reading from and/or
   writing to the file with name `file`.

   `mode` is one of the following:

   ====== =====================================================================
   `mode` Behavior
   ====== =====================================================================
   ``r``  Open a file for reading. The file must exist.
   ``w``  Create an empty file for writing. If a file with the same name
          already exists, its contents are erased and the file is treated as a
          new empty file.
   ``a``  Append to a file. Writing operations append data at the end of the
          file. The file is created if it does not exist.
   ``r+`` Open a file for both reading and writing. The file must exist.
   ``w+`` Create an empty file for both reading and writing. If a file with the
          same name already exists its contents are erased and the file is
          treated as a new empty file.
   ``a+`` Open a file for reading and appending. All writing operations are
          performed at the end of the file. You can seek the internal pointer
          to anywhere in the file for reading, but writing operations will move
          it back to the end of the file. The file is created if it does not
          exist.
   ====== =====================================================================

   :param str file: File path
   :param str mode: File open mode
   :returns: A new :class:`SDL_RWops` structure
   :raises RuntimeError: SDL could not open the file.

.. function:: SDL_AllocRW() -> SDL_RWops

   Allocates a new :class:`SDL_RWops` structure and returns it.

   Applications do not need to use this function unless they are providing
   their own RWops implementation. You should use the built-in implementations
   in SDL, like :func:`SDL_RWFromFile`, :func:`SDL_RWFromMem` etc.

   :returns: A new :class:`SDL_RWops` structure
   :raises MemoryError: Insufficient memory to allocate the structure.

.. function:: SDL_FreeRW(area: SDL_RWops) -> None

   Frees the :class:`SDL_RWops` structure allocated by :func:`SDL_AllocRW`.

   Applications do not need to use this function unless they are providing
   their own :attr:`SDL_RWops.close` implementation. When using the built-in
   implementations of :class:`SDL_RWops` (e.g. through :func:`SDL_RWFromFile`,
   :func:`SDL_RWFromMem` etc.), you just need to call :func:`SDL_RWclose` with
   the :class:`SDL_RWops` object, as the built-in implementations of
   :attr:`SDL_RWops.close` will call :func:`SDL_FreeRW` internally.

   :param SDL_RWops area: The :class:`SDL_RWops` structure allocated with
                          :func:`SDL_AllocRW`.

.. function:: SDL_RWsize(context: SDL_RWops) -> int

   Returns the size of the data stream in the :class:`SDL_RWops`.

   :param SDL_RWops context: The :class:`SDL_RWops` stream to get the size of.
   :returns: Size of the data stream in bytes.

.. function:: SDL_RWseek(context: SDL_RWops, offset: int, whence: int) -> int

   Seeks to `offset` relative to `whence`.

   :param SDL_RWops context: Stream to seek in.
   :param int offset: New position in stream, measured in bytes, relative to
                      `whence`.
   :param int whence: :const:`RW_SEEK_SET`, :const:`RW_SEEK_CUR` or
                      :const:`RW_SEEK_END`.
   :returns: New offset, measured in bytes, from the start of the stream.

.. data:: RW_SEEK_SET

   Seek from the beginning of data.

.. data:: RW_SEEK_CUR

   Seek relative to current read point.

.. data:: RW_SEEK_END

   Seek relative to the end of data.

.. function:: SDL_RWread(context: SDL_RWops, ptr: buffer, size: int, maxnum: int) -> int

   Reads up to `maxnum` objects, each of size `size` bytes, from the data
   source to the buffer `ptr`.

   :param SDL_RWops context: Data stream to read from.
   :param buffer ptr: Buffer to read data into. It must be exactly
                      ``size * maxnum`` bytes.
   :param int size: The size of each object to read, in bytes.
   :param int maxnum: The maximum number of objects to be read.
   :returns: The number of objects read. This function may read less objects
             than requested.

.. function:: SDL_RWwrite(context: SDL_RWops, ptr: buffer, size: int, num: int) -> int

   Writes exactly `num` objects, each `size` bytes, from the buffer `ptr` to
   the stream.

   :param SDL_RWops context: Data stream to write to.
   :param buffer ptr: Buffer containing the data to write to the stream. It
                      must be exactly ``size * num`` bytes.
   :param int size: The size of each object to write, in bytes.
   :param int maxnum: The number of objects to write.
   :returns: The number of objects written, which can be less than `num` on
              error or when the end of file has been reached.

.. function:: SDL_RWclose(context: SDL_RWops) -> None

   Closes and cleans up the data stream. The :class:`SDL_RWops` object will be
   freed.

   :param SDL_RWops context: Data stream to close.

   .. note:: The :class:`SDL_RWops` object will still be freed even when an
             exception occurs while closing the stream.
