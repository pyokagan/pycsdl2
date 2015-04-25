Surface Creation and Simple Drawing
===================================
.. module:: csdl2

.. class:: SDL_Surface

   A structure that contains a collection of pixels used in software blitting.

   This structure cannot be initiated directly. Use
   :func:`SDL_CreateRGBSurface`, :func:`SDL_CreateRGBSurfaceFrom`,
   :func:`SDL_LoadBMP_RW` or :func:`SDL_LoadBMP` to create a new instance.

   .. attribute:: flags

      (readonly) A bitmask of the flags :const:`SDL_PREALLOC`,
      :const:`SDL_RLEACCEL` and/or :const:`SDL_DONTFREE` for internal use.

   .. attribute:: format

      (readonly) :class:`SDL_PixelFormat` of the pixels stored in the surface.

   .. attribute:: w

      (readonly) Width of the surface in pixels.

   .. attribute:: h

      (readonly) Height of the surface in pixels.

   .. attribute:: pitch

      (readonly) The length of a row of pixels in bytes.

   .. attribute:: pixels

      (readonly) Buffer providing the actual pixel data.

   .. attribute:: userdata

      An arbitrary object that an application can set for its own use.

   .. attribute:: locked

      (readonly) True if the surface is locked.

   .. attribute:: clip_rect

      (readonly) An :class:`SDL_Rect` structure used to clip bits to the
      surface which can be set by :func:`SDL_SetClipRect`.

   .. attribute:: refcount

      (readonly) SDL's reference count of the surface. For internal use.

.. data:: SDL_PREALLOC

   Surface uses preallocated memory.

.. data:: SDL_RLEACCEL

   Surface is RLE encoded.

.. data:: SDL_DONTFREE

   Surface is referenced internally.
