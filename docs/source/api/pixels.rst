Pixel Formats and Conversion Routines
=====================================
.. module:: csdl2

Pixel Types
-----------
The pixel type is one of the following values:

.. data:: SDL_PIXELTYPE_UNKNOWN

   Unknown pixel type.

Indexed Pixel Types
~~~~~~~~~~~~~~~~~~~
.. data:: SDL_PIXELTYPE_INDEX1

.. data:: SDL_PIXELTYPE_INDEX4

.. data:: SDL_PIXELTYPE_INDEX8

Packed Pixel Types
~~~~~~~~~~~~~~~~~~
.. data:: SDL_PIXELTYPE_PACKED8

.. data:: SDL_PIXELTYPE_PACKED16

.. data:: SDL_PIXELTYPE_PACKED32

Bitmap Pixel Types
~~~~~~~~~~~~~~~~~~
.. data:: SDL_PIXELTYPE_ARRAYU8

.. data:: SDL_PIXELTYPE_ARRAYU16

.. data:: SDL_PIXELTYPE_ARRAYU32

.. data:: SDL_PIXELTYPE_ARRAYF16

.. data:: SDL_PIXELTYPE_ARRAYF32

Pixel Ordering
--------------
Depending on the pixel type there are three different types of orderings --
bitmapped, packed or array.

Bitmap pixel order (high bit -> low bit)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. data:: SDL_BITMAPORDER_NONE

.. data:: SDL_BITMAPORDER_4321

.. data:: SDL_BITMAPORDER_1234

Packed component order (high bit -> low bit)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. data:: SDL_PACKEDORDER_NONE

.. data:: SDL_PACKEDORDER_XRGB

.. data:: SDL_PACKEDORDER_RGBX

.. data:: SDL_PACKEDORDER_ARGB

.. data:: SDL_PACKEDORDER_RGBA

.. data:: SDL_PACKEDORDER_XBGR

.. data:: SDL_PACKEDORDER_BGRX

.. data:: SDL_PACKEDORDER_ABGR

.. data:: SDL_PACKEDORDER_BGRA

Array component order (low byte -> high byte)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. data:: SDL_ARRAYORDER_NONE

.. data:: SDL_ARRAYORDER_RGB

.. data:: SDL_ARRAYORDER_RGBA

.. data:: SDL_ARRAYORDER_ARGB

.. data:: SDL_ARRAYORDER_BGR

.. data:: SDL_ARRAYORDER_BGRA

.. data:: SDL_ARRAYORDER_ABGR

Pixel Formats
-------------
.. class:: SDL_PixelFormat

   Pixel format information.

   This structure cannot be directly constructed. Use :func:`SDL_AllocFormat`
   instead.

   .. attribute:: format

      (readonly) A constant specifying the pixel format. See `Pixel format
      constants`_ for possible values.

   .. attribute:: palette

      (readonly) The :class:`SDL_Palette` associated with this pixel format, or
      None if this format does not have a palette.

   .. attribute:: BitsPerPixel

      (readonly) The number of significant bits in a pixel value. E.g. 8, 15,
      16, 24, 32.

   .. attribute:: BytesPerPixel

      (readonly) The number of bytes required to hold a pixel value. E.g. 1,
      2, 3, 4.

   .. attribute:: Rmask

      (readonly) A mask representing the location of the red component of a
      pixel.

   .. attribute:: Gmask

      (readonly) A mask representing the location of the green component of a
      pixel.

   .. attribute:: Bmask

      (readonly) A mask representing the location of the blue component of a
      pixel.

   .. attribute:: Rloss

      (readonly) The red value of a pixel has this number of bits less compared
      to 8-bit values.

   .. attribute:: Gloss

      (readonly) The green value of a pixel has this number of bits less
      compared to 8-bit values.

   .. attribute:: Bloss

      (readonly) The blue value of a pixel has this number of bits less
      compared to 8-bit values.

   .. attribute:: Aloss

      (readonly) The alpha value of a pixel has this number of bits less
      compared to 8-bit values.

   .. attribute:: Rshift

      (readonly) The bit index of the red field of a pixel.

   .. attribute:: Gshift

      (readonly) The bit index of the green value of a pixel.

   .. attribute:: Bshift

      (readonly) The bit index of the blue value of a pixel.

   .. attribute:: Ashift

      (readonly) The bit index of the alpha value of a pixel.

.. function:: SDL_AllocFormat(pixel_format: int) -> SDL_PixelFormat

   Creates a :class:`SDL_PixelFormat` structure corresponding to the pixel
   format constant `pixel_format`.

   :param int pixel_format: One of the `Pixel format constants`_.
   :returns: A :class:`SDL_PixelFormat`.
   :raises ValueError: Invalid `pixel_format`.
   :raises MemoryError: Not enough memory to allocate the
                        :class:`SDL_PixelFormat`.

.. function:: SDL_FreeFormat(format: SDL_PixelFormat) -> None

   Frees the :class:`SDL_PixelFormat` structure allocated by
   :func:`SDL_AllocFormat`.

   There is no need to manually call this function. csdl2 will automatically
   call this function upon garbage collection.

   :param SDL_PixelFormat format: :class:`SDL_PixelFormat` structure to free.
   :raises AssertionError: The pixel format has already been freed.

   .. warning:: Do not access the pixel format structure once is has been
                freed. Doing so will at best raise AssertionErrors and at worse
                crash the interpreter.

Pixel format constants
~~~~~~~~~~~~~~~~~~~~~~
.. data:: SDL_PIXELFORMAT_UNKNOWN

.. data:: SDL_PIXELFORMAT_INDEX1LSB

.. data:: SDL_PIXELFORMAT_INDEX1MSB

.. data:: SDL_PIXELFORMAT_INDEX4LSB

.. data:: SDL_PIXELFORMAT_INDEX4MSB

.. data:: SDL_PIXELFORMAT_INDEX8

.. data:: SDL_PIXELFORMAT_RGB332

.. data:: SDL_PIXELFORMAT_RGB444

.. data:: SDL_PIXELFORMAT_RGB555

.. data:: SDL_PIXELFORMAT_BGR555

.. data:: SDL_PIXELFORMAT_ARGB4444

.. data:: SDL_PIXELFORMAT_RGBA4444

.. data:: SDL_PIXELFORMAT_ABGR4444

.. data:: SDL_PIXELFORMAT_BGRA4444

.. data:: SDL_PIXELFORMAT_ARGB1555

.. data:: SDL_PIXELFORMAT_RGBA5551

.. data:: SDL_PIXELFORMAT_ABGR1555

.. data:: SDL_PIXELFORMAT_BGRA5551

.. data:: SDL_PIXELFORMAT_RGB565

.. data:: SDL_PIXELFORMAT_BGR565

.. data:: SDL_PIXELFORMAT_RGB24

.. data:: SDL_PIXELFORMAT_BGR24

.. data:: SDL_PIXELFORMAT_RGB888

.. data:: SDL_PIXELFORMAT_RGBX8888

.. data:: SDL_PIXELFORMAT_BGR888

.. data:: SDL_PIXELFORMAT_BGRX8888

.. data:: SDL_PIXELFORMAT_ARGB8888

.. data:: SDL_PIXELFORMAT_RGBA8888

.. data:: SDL_PIXELFORMAT_ABGR8888

.. data:: SDL_PIXELFORMAT_BGRA8888

.. data:: SDL_PIXELFORMAT_ARGB2101010

.. data:: SDL_PIXELFORMAT_YV12

.. data:: SDL_PIXELFORMAT_IYUV

.. data:: SDL_PIXELFORMAT_YUY2

.. data:: SDL_PIXELFORMAT_UYVY

.. data:: SDL_PIXELFORMAT_YVYU

Color Palette
-------------
.. class:: SDL_Palette

   A color palette.

   Every pixel in an 8-bit surface is an index into the `colors` field of the
   :class:`SDL_Palette` referenced by the :class:`SDL_PixelFormat`.

   This structure cannot be directly constructed. One will be automatically
   created as needed when SDL allocates a :class:`SDL_PixelFormat`. It can also
   be created through :func:`SDL_AllocPalette`.

   .. attribute:: ncolors

      (readonly) Number of colors in the palette.

   .. attribute:: colors

      (readonly) An array of :class:`SDL_Color` structures representing the
      palette. This array cannot be directly modified. Use
      :func:`SDL_SetPaletteColors` instead.

.. function:: SDL_AllocPalette(ncolors: int) -> SDL_AllocPalette

   Create a new :class:`SDL_Palette` with `ncolors` number of color entries.
   The color entries are initialized to white.

   :param int ncolors: Number of colors in the palette.
   :returns: A new :class:`SDL_Palette`.
   :raises ValueError: Invalid number of colors.
   :raises MemoryError: Not enough memory to allocate the palette.

.. function:: SDL_FreePalette(palette: SDL_Palette) -> None

   Frees the specified palette.

   There is no need to call this function as csdl2 will automatically call this
   function on garbage collection.

   :param SDL_Palette palette: The :class:`SDL_Palette` to be freed.
   :raises AssertionError: The palette has already been freed.

   .. warning:: Do not access the palette once it has been freed. Doing so will
                at best raise AssertionErrors and at worse crash the
                interpreter.
