2D Accelerated Rendering
========================
.. currentmodule:: csdl2

.. class:: SDL_Renderer

   A 2d rendering context.

   This is an opaque handle that cannot be directly constructed. Instead, use
   :func:`SDL_CreateRenderer` or :func:`SDL_CreateSoftwareRenderer`.

Creating a renderer
-------------------
.. function:: SDL_CreateRenderer(window: SDL_Window, index: int, flags: int) -> SDL_Renderer

   Creates a :class:`SDL_Renderer` for `window`.

   :param SDL_Window window: :class:`SDL_Window` to render to.
   :param int index: The index of the rendering driver to initialize, or -1 to
                     initialize the first driver supporting `flags`.
   :param int flags: 0, or one or more `Renderer creation flags`_ OR'ed
                     together.
   :returns: A new :class:`SDL_Renderer` that renders to `window`.
   :raises RuntimeError: If the window already has a renderer associated with
                         it.
   :raises RuntimeError: If no render driver supports `flags`.
   :raises RuntimeError: If the render driver index is invalid.

.. function:: SDL_CreateSoftwareRenderer(surface: SDL_Surface) -> SDL_Renderer

   Creates a :class:`SDL_Renderer` for `surface`.

   :param SDL_Surface surface: :class:`SDL_Surface` to render to.
   :returns: A new :class:`SDL_Renderer` that renders to `surface`.

Renderer creation flags
-----------------------
These flags can be passed to :func:`SDL_CreateRenderer` to request that the
renderer support certain functions.

.. data:: SDL_RENDERER_SOFTWARE

   The renderer is a software fallback.

.. data:: SDL_RENDERER_ACCELERATED

   The renderer uses hardware acceleration.

.. data:: SDL_RENDERER_PRESENTVSYNC

   :func:`SDL_RenderPresent` is synchronized with the refresh rate.

.. data:: SDL_RENDERER_TARGETTEXTURE

   The renderer supports rendering to texture.

Destroying a renderer
---------------------
.. function:: SDL_DestroyRenderer(renderer: SDL_Renderer) -> None

   Destroys `renderer`, freeing up its associated :class:`SDL_Texture`s and
   resources.

   There is no need to manually call this function. :class:`SDL_Renderer` will
   automatically call this function as part of its destructor.

   :param SDL_Renderer renderer: :class:`SDL_Renderer` to destroy

   .. warning:: Once destroyed, do not access the renderer. Doing so will at
                best raise errors and at worse crash the interpreter.

Textures
--------
.. class:: SDL_Texture

   An efficient driver-specific representation of pixel data.

   This is an opaque handle that cannot be directly constructed. Instead, use
   :func:`SDL_CreateTexture` or :func:`SDL_CreateTextureFromSurface`.

.. function:: SDL_CreateTexture(renderer, format, access, w, h) -> SDL_Texture

   Creates a texture for a rendering context with the specified properties.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param int format: The texture pixel format. One of the
                      :ref:`pixel-format-constants`.
   :param int access: Specifies whether the texture data can be modified. One
                      of :const:`SDL_TEXTUREACCESS_STATIC`,
                      :const:`SDL_TEXTUREACCESS_STREAMING`
                      or :const:`SDL_TEXTUREACCESS_TARGET`.
   :param int w: Width of the texture in pixels.
   :param int h: Height of the texture in pixels.
   :returns: A new :class:`SDL_Texture` for the rendering context.

.. data:: SDL_TEXTUREACCESS_STATIC

   Texture changes rarely, not lockable.

.. data:: SDL_TEXTUREACCESS_STREAMING

   Texture changes frequently, lockable.

.. data:: SDL_TEXTUREACCESS_TARGET

   Texture can be used as a render target.

.. function:: SDL_CreateTextureFromSurface(renderer, surface) -> SDL_Texture

   Creates a texture for a rendering context with the pixel data of an existing
   surface.

   The surface is not modified or freed by this function. The texture will be
   created with :const:`SDL_TEXTUREACCESS_STATIC`.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param surface: The surface containing pixel data to fill the texture.
   :type surface: class:`SDL_Surface`
   :returns: A new :class:`SDL_Texture` for the rendering context.

.. function:: SDL_QueryTexture(texture) -> tuple

   Query the attributes of a texture. Namely:

   * The texture's raw pixel format, one of the :ref:`pixel-format-constants`.
   * The texture's access. One of :const:`SDL_TEXTUREACCESS_STATIC`,
     :const:`SDL_TEXTUREACCESS_STREAMING` or :const:`SDL_TEXTUREACCESS_TARGET`.
   * The texture's width and height, in pixels.

   :param texture: The texture to be queried.
   :type texture: :class:`SDL_Texture`
   :returns: A tuple ``(int, int, int, int)`` with the texture's raw pixel
             format, access, width and height respectively.

.. function:: SDL_SetTextureColorMod(texture, r, g, b)

   Sets an additional color value used in render copy operations.

   When the texture is rendered, during the copy operation each source color
   channel is modulated by the appropriate color value according to the
   following formula::

      srcC = srcC * (color / 255)

   :param texture: The texture to update.
   :type texture: :class:`SDL_Texture`
   :param int r: The red color value multiplied into copy operations.
   :param int g: The green color value multiplied into copy operations.
   :param int b: The blue color value multiplied into copy operations.

.. function:: SDL_GetTextureColorMod(texture) -> tuple

   Returns the additional color value multiplied into render copy operations.

   :param texture: The texture to query.
   :type texture: :class:`SDL_Texture`
   :returns: A tuple ``(int, int, int)`` with the red, green and blue
             components of the color respectively.

.. function:: SDL_SetTextureAlphaMod(texture, alpha)

   Sets an additional alpha value multiplied into render copy operations.

   When the texture is rendered, during the copy operation the source alpha
   value would be modulated by this alpha value according to the following
   formula::

      srcA = srcA * (alpha / 255)

   :param texture: The texture to update.
   :type texture: :class:`SDL_Texture`
   :param int alpha: The source alpha value multiplied into copy operations. It
                     must be within the range 0-255.

.. function:: SDL_GetTextureAlphaMod(texture) -> int

   Returns the additional alpha value multiplied into render copy operations.

   :param texture: The texture to query.
   :type texture: :class:`SDL_Texture`
   :returns: The current alpha value. It is within the range 0-255.

.. function:: SDL_SetTextureBlendMode(texture, blendMode: int)

   Sets the blend mode for a texture.

   :param texture: The texture to update.
   :type texture: :class:`SDL_Texture`
   :param int blendMode: The blend mode to use for texture blending. One of the
                         :ref:`blend-modes`.

.. function:: SDL_GetTextureBlendMode(texture) -> int

   Returns the blend mode used for texture copy operations.

   :param texture: The texture to query.
   :type texture: :class:`SDL_Texture`
   :returns: The texture's blend mode. One of the :ref:`blend-modes`.

.. function:: SDL_UpdateTexture(texture, rect, pixels, pitch)

   Updates the given texture rectangle with new pixel data.

   :param texture: The texture to update.
   :type texture: :class:`SDL_Texture`
   :param rect: The area to update, or None to update the entire texture.
   :type rect: :class:`SDL_Rect` buffer, or None
   :param buffer pixels: The raw pixel data.
   :param int pitch: The number of bytes in a row of pixel data, including
                     padding between lines.

   .. note::

      This is a fairly slow function, intended for use with static textures
      that do not change often.  If the texture is intended to be updated
      often, it is preferred to create the texture as streaming and use the
      locking functions :func:`SDL_LockTexture` and :func:`SDL_UnlockTexture`.
      While this function will work with streaming textures, for optimization
      reasons you may not get the pixels back if you lock the texture
      afterward.

.. function:: SDL_LockTexture(texture, rect) -> tuple

   Locks a portion of the texture for write-only pixel access.

   :param texture: The texture to lock for access, which was created with
                   :const:`SDL_TEXTUREACCESS_STREAMING`.
   :type texture: :class:`SDL_Texture`
   :param rect: The area to lock for access, or None to lock the entire
                texture.
   :type rect: :class:`SDL_Rect` buffer or None
   :returns: A tuple ``(pixels, pitch)``. `pixels` is a buffer containing the
             locked pixels, and `pitch` is the integer length of one row in
             bytes.

   .. note::

      After modifying the pixels, you must use :func:`SDL_UnlockTexture` to
      unlock the pixels and apply any changes.

   .. note::

      This is a write-only operation. As an optimization, the pixels made
      available for editing don't necessarily contain the old texture data.

.. function:: SDL_UnlockTexture(texture)

   Unlocks a texture, uploading any changes to video memory.

   :param texture: A texture locked by :func:`SDL_LockTexture`.
   :type texture: :class:`SDL_Texture`

   .. note::

      The pixels buffer returned by :func:`SDL_LockTexture` may contain junk
      data. For consistent results, ensure that you have overwritten the pixel
      buffer fully before calling this function.

.. function:: SDL_DestroyTexture(texture)

   Destroys the specified texture, freeing its resources.

   There is no need to explictly call this function. :class:`SDL_Texture` will
   automatically call it upon cleanup.

   :param texture: Texture to destroy.
   :type texture: :class:`SDL_Texture`

Drawing
-------
.. function:: SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: int, g: int, b: int, a: int) -> None

   Sets the color used for drawing primitives, and for :func:`SDL_RenderClear`.

   :param renderer: The rendering context.
   :type rendering: :class:`SDL_Renderer`
   :param int r: The red value used to draw on the rendering target, within the
                 range 0-255.
   :param int g: The green value used to draw on the rendering target, within
                 the range 0-255.
   :param int b: The blue value used to draw on the rendering target, within
                 the range 0-255.
   :param int a: The alpha value used to draw on the rendering target, within
                 the range 0-255. Use :func:`SDL_SetRenderDrawBlendMode` to
                 specify how the alpha channel is used.
   :raises RuntimeError: If the drawing color could not be set.

.. function:: SDL_GetRenderDrawColor(renderer: SDL_Renderer) -> tuple

   Returns the color used for drawing operations.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: The (r, g, b, a) components of the drawing color.
   :rtype: (int, int, int, int) tuple

.. function:: SDL_RenderClear(renderer: SDL_Renderer) -> None

   Clears the current rendering target with the current drawing color.

   The entire rendering target will be cleared, ignoring the viewport.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :raises RuntimeError: If the rendering target could not be cleared.

.. function:: SDL_RenderFillRect(renderer: SDL_Renderer, rect: SDL_Rect) -> None

   Fills a rectangle on the current rendering target with the current drawing
   color.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The :class:`SDL_Rect` representing the rectangle to fill. If
                None, the entire rendering target will be filled.
   :type rect: :class:`SDL_Rect` or None
   :raises RuntimeError: If the rectangle could not be filled.

.. function:: SDL_RenderCopy(renderer, texture, srcrect, dstrect)

   Copies a portion of the texture to the current rendering target.

   The texture is blended with the destination based on its blend mode set with
   :func:`SDL_SetTextureBlendMode`.

   The texture color is affected based on its color modulation set by
   :func:`SDL_SetTextureColorMod`.

   The texture alpha is affected based on its alpha modulation set by
   :func:`SDL_SetTextureAlphaMod`.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param texture: The source texture.
   :type texture: :class:`SDL_Texture`
   :param srcrect: The source rectangle, or None for the entire texture.
   :type srcrect: :class:`SDL_Rect` buffer or None
   :param dstrect: The destination rectangle, or None for the entire rendering
                   target. The texture will be stretched to fill the given
                   rectangle.
   :type dstrect: :class:`SDL_Rect` buffer or None

.. function:: SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip)

   Copies a portion of the texture to the current rendering target, optionally
   rotating it by an angle around the given center and also flipping it
   top-bottom and/or left-right.

   The texture is blended with the destination based on its blend mode set with
   :func:`SDL_SetTextureBlendMode`.

   The texture color is affected based on its color modulation set by
   :func:`SDL_SetTextureColorMod`.

   The texture alpha is affected based on its alpha modulation set by
   :func:`SDL_SetTextureAlphaMod`.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param texture: The source texture.
   :type texture: :class:`SDL_Texture`
   :param srcrect: The source rectangle, or None for the entire texture.
   :type srcrect: :class:`SDL_Rect` or None
   :param dstrect: The destination rectangle, or None for the entire rendering
                   target. The texture will be stretched to fill the given
                   rectangle.
   :type dstrect: :class:`SDL_Rect` or None
   :param float angle: An angle in degrees that indicates the rotation that
                       will be applied to `dstrect`.
   :param center: The point around which `dstrect` will be rotated. If None,
                  rotation will be done around ``(dstrect.w/2, dstrect.h/2)``.
   :type center: :class:`SDL_Point` or None
   :param int flip: Indicates which flipping actions should be performed on the
                    texture. One or more of :const:`SDL_FLIP_NONE`,
                    :const:`SDL_FLIP_HORIZONTAL` and/or
                    :const:`SDL_FLIP_VERTICAL` OR'd together.

.. data:: SDL_FLIP_NONE

   Do not flip.

.. data:: SDL_FLIP_HORIZONTAL

   Flip horizontally.

.. data:: SDL_FLIP_VERTICAL

   Flip vertically.

Updating the screen
-------------------
SDL's rendering functions operate on a backbuffer. Calling a rendering function
such as :func:`SDL_RenderDrawLine` does not directly draw a line on the screen,
but rather updates the backbuffer. As such, after composing your entire scene
with the drawing functions, you need to *present* the composed buffer to the
screen as a complete picture. This is done with :func:`SDL_RenderPresent`.

.. function:: SDL_RenderPresent(renderer: SDL_Renderer) -> None

   Updates the screen with any rendering performed since the previous call.

   If the renderer has VSync enabled, this function will block while waiting
   for the next vertical refresh, hence eliminating screen tearing.

   :param renderer: The rendering context
   :type renderer: :class:`SDL_Renderer`

   .. note:: The backbuffer should be considered invalidated after each call to
             :func:`SDL_RenderPresent`. Do not assume that previous contents
             will exist between frames. You are strongly encouraged to call
             :func:`SDL_RenderClear` to initialize the backbuffer before
             drawing each frame.

.. data:: SDL_FLIP_NONE

   Do not flip.

.. data:: SDL_FLIP_HORIZONTAL

   Flip horizontally.

.. data:: SDL_FLIP_VERTICAL

   Flip vertically.
