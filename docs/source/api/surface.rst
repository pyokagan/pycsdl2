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

.. function:: SDL_MUSTLOCK(surface: SDL_Surface) -> bool

   Returns True if `surface` needs to be locked before its
   :attr:`SDL_Surface.pixels` can be accessed.

   :param SDL_Surface surface: The surface to test
   :returns: True if the surface needs to be locked before its pixels can be
             accessed, False otherwise.

.. function:: SDL_CreateRGBSurface(flags: int, width: int, height: int, depth: int, Rmask: int, Gmask: int, Bmask: int, Amask: int) -> SDL_Surface

   Creates and returns a new blank :class:`SDL_Surface` with the specified
   properties.

   :param int flags: This argument is unused and should be set to 0.
   :param int width: The width of the surface in pixels.
   :param int height: The height of the surface in pixels.
   :param int depth: The depth of the surface in bits. If `depth` is 4 or 8
                     bits, an empty :class:`SDL_Palette` is allocated for the
                     surface. If `depth` is greater than 8 bits, the pixel
                     format is set using the `Rmask`, `Gmask`, `Bmask` and
                     `Amask` arguments.
   :param int Rmask: Bitmask used to extract the red component from a pixel. If
                     0, a default mask based on the depth is used.
   :param int Gmask: Bitmask used to extract the green component from a pixel.
                     If 0, a default mask based on the depth is used.
   :param int Bmask: Bitmask used to extract the blue component from a pixel.
                     If 0, a default mask based on the depth is used.
   :param int Amask: Bitmask used to extract the alpha component from a pixel.
                     If 0, the surface has no alpha channel.
   :returns: A new blank :class:`SDL_Surface` structure.
   :raises RuntimeError: The surface could not be created.
