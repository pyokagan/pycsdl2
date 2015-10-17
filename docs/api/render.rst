2D Accelerated Rendering
========================
.. currentmodule:: csdl2

Render drivers
--------------
A render driver is a set of code that handles rendering and texture management
on a particular display.

.. class:: SDL_RendererInfo(name=None, flags=0, num_texture_formats=0, texture_formats=0, max_texture_width=0, max_texture_height=0)

   Information on the capabilities of a render driver or context.

   .. attribute:: name

      Name of the renderer.

   .. attribute:: flags

      A mask of supported `Renderer creation flags`_.

   .. attribute:: num_texture_formats

      The number of available texture formats.

   .. attribute:: texture_formats

      The available texture formats as an array of
      :ref:`pixel-format-constants` ints.

      Note that the size of the array is always 16. However, only the first
      ``num_texture_formats`` values are valid.

   .. attribute:: max_texture_width

      Maximum texture width.

   .. attribute:: max_texture_height

      Maximum texture height

.. function:: SDL_GetNumRenderDrivers() -> int

   Get the number of 2D rendering drivers available for the current display.

.. function:: SDL_GetRenderDriverInfo(index) -> SDL_RendererInfo

   Gets information about a specific 2D rendering driver for the current
   display.

   :param int index: The index of the driver to query information about. It
                     must be in the range 0 to
                     ``SDL_GetNumRenderDrivers() - 1``.
   :returns: A new :class:`SDL_RendererInfo` filled with information about the
             render driver.

Renderers
---------
.. class:: SDL_Renderer

   A 2d rendering context.

   This is an opaque handle that cannot be directly constructed. Instead, use
   :func:`SDL_CreateRenderer` or :func:`SDL_CreateSoftwareRenderer`.

.. function:: SDL_CreateWindowAndRenderer(width, height, window_flags) -> tuple

   Creates a window and a default renderer.

   :param int width: The width of the window.
   :param int height: The height of the window.
   :param int window_flags: 0, or one or more of the :ref:`window-flags` OR'd
                            together.
   :returns: A 2-tuple ``(window, renderer)``, where `window` is the created
             :class:`SDL_Window` and `renderer` is the created
             :class:`SDL_Renderer`.

.. function:: SDL_CreateRenderer(window: SDL_Window, index: int, flags: int) -> SDL_Renderer

   Creates a :class:`SDL_Renderer` for `window`.

   :param SDL_Window window: :class:`SDL_Window` to render to.
   :param int index: The index of the rendering driver to initialize, or -1 to
                     initialize the first driver supporting `flags`.
   :param int flags: 0, or one or more `Renderer creation flags`_ OR'ed
                     together.
   :returns: A new :class:`SDL_Renderer` that renders to `window`.

.. function:: SDL_CreateSoftwareRenderer(surface: SDL_Surface) -> SDL_Renderer

   Creates a :class:`SDL_Renderer` for `surface`.

   :param SDL_Surface surface: :class:`SDL_Surface` to render to.
   :returns: A new :class:`SDL_Renderer` that renders to `surface`.

.. function:: SDL_GetRenderer(window) -> SDL_Renderer

   Returns the renderer associated with a window.

   :param window: The window to query.
   :type window: :class:`SDL_Renderer`
   :returns: The :class:`SDL_Renderer` associated with the window, or None if
             there is no renderer associated with the window.

.. function:: SDL_GetRendererInfo(renderer) -> SDL_RendererInfo

   Get information about a rendering context.

   :param renderer: The rendering context to query.
   :type renderer: :class:`SDL_Renderer`
   :returns: A new :class:`SDL_RendererInfo` filled with information about the
             renderer.

.. function:: SDL_GetRendererOutputSize(renderer) -> tuple

   Get the output size of a rendering context.

   :param renderer: The rendering context to query.
   :type renderer: :class:`SDL_Renderer`
   :returns: A 2-tuple ``(width, height)`` with the output width and height of
             the rendering context respectively.

.. function:: SDL_DestroyRenderer(renderer: SDL_Renderer) -> None

   Destroys `renderer`, freeing up its associated textures and resources.

   There is no need to manually call this function. :class:`SDL_Renderer` will
   automatically call this function as part of its destructor.

   :param SDL_Renderer renderer: :class:`SDL_Renderer` to destroy

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

Render targets
--------------
.. function:: SDL_RenderTargetSupported(renderer) -> bool

   Queries whether a renderer supports the use of render targets.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: True if render targets are supported, False if not.

.. function:: SDL_SetRenderTarget(renderer, texture)

   Sets a texture as the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param texture: The targeted texture, which must be created with the
                   :const:`SDL_TEXTURTEACCESS_TARGET` flag, or None for the
                   default render target.
   :type texture: :class:`SDL_Texture` or None

.. function:: SDL_GetRenderTarget(renderer) -> SDL_Texture

   Queries the renderer's current render target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: The current render target, or None for the default render target.

Device independent resolution
-----------------------------
.. function:: SDL_RenderSetLogicalSize(renderer, w, h)

   Sets a device independent resolution for rendering.

   :param renderer: The renderer for which resolution should be set.
   :type renderer: :class:`SDL_Renderer`
   :param int w: The width of the logical resolution.
   :param int h: The height of the logical resolution.

.. function:: SDL_RenderGetLogicalSize(renderer) -> tuple

   Queries the device independent resolution for rendering.

   If the renderer did not have its logical size set by
   :func:`SDL_RenderSetLogicalSize`, the function returns ``(0, 0)``.

   :param renderer: A rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: An ``(int, int)`` tuple with the width and height of the logical
             resolution respectively.

Viewport
--------
.. function:: SDL_RenderSetViewport(renderer, rect)

   Sets the drawing area for rendering on the current target.

   When the window is resized, the current viewport is automatically centered
   within the new window size.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The drawing area, or None to set the viewport to the entire
                target.
   :type rect: :class:`SDL_Rect` or None

.. function:: SDL_RenderGetViewport(renderer) -> SDL_Rect

   Queries the drawing area for the current target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: A :class:`SDL_Rect` with the drawing area for the current target.

Clip Rectangle
--------------
.. function:: SDL_RenderSetClipRect(renderer, rect)

   Sets the clip rectangle for the current target.

   :param renderer: The renderer for which clip rectangle should be set.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The rectangle to set as the clip rectangle, or None to disable
                clipping.
   :type rect: :class:`SDL_Rect` or None

.. function:: SDL_RenderGetClipRect(renderer) -> SDL_Rect

   Gets the clip rectangle for the current target.

   :param renderer: The renderer from which clip rectangle should be queried.
   :type renderer: :class:`SDL_Renderer`
   :returns: A :class:`SDL_Rect` with the current clip rectangle, or an empty
             rectangle if clipping is disabled.

Scaling
-------
.. function:: SDL_RenderSetScale(renderer, scaleX, scaleY)

   Sets the drawing scale for rendering on the current target.

   The drawing coordinates are scaled by the ``x/y`` scaling factors before
   they are used by the renderer. This allows resolution independent drawing
   with a single coordinate system.

   :param renderer: The renderer for which the drawing scale should be set.
   :type renderer: :class:`SDL_Renderer`
   :param float scaleX: The horizontal scaling factor.
   :param float scaleY: The vertical scaling factor.

   .. note::

      If this results in scaling or subpixel drawing by the rendering backend,
      it will be hendled using the appropriate quality hints. For best results
      use integer scaling factors.

.. function:: SDL_RenderGetScale(renderer) -> tuple

   Gets the drawing scale for the current target.

   :param renderer: The renderer from which drawing scale should be queried.
   :type renderer: :class:`SDL_Renderer`
   :returns: A 2-tuple ``(scaleX, scaleY)`` with the float horizontal and
             vertical scaling factors respectively.

Drawing
-------
.. function:: SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: int, g: int, b: int, a: int) -> None

   Sets the color used for drawing primitives, and for :func:`SDL_RenderClear`.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param int r: The red value used to draw on the rendering target, within the
                 range 0-255.
   :param int g: The green value used to draw on the rendering target, within
                 the range 0-255.
   :param int b: The blue value used to draw on the rendering target, within
                 the range 0-255.
   :param int a: The alpha value used to draw on the rendering target, within
                 the range 0-255. Use :func:`SDL_SetRenderDrawBlendMode` to
                 specify how the alpha channel is used.

.. function:: SDL_GetRenderDrawColor(renderer: SDL_Renderer) -> tuple

   Returns the color used for drawing operations.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :returns: The (r, g, b, a) components of the drawing color.
   :rtype: (int, int, int, int) tuple

.. function:: SDL_SetRenderDrawBlendMode(renderer, blendMode)

   Sets the blend mode used for drawing operations (Fill and Line).

   :param renderer: The renderer for which blend mode should be set.
   :type renderer: :class:`SDL_Renderer`
   :param int blendMode: The blend mode to use for blending. One of the
                         :ref:`blend-modes`.

   .. note::

      If the blend mode is not supported, the closest supported mode is chosen.

.. function:: SDL_GetRenderDrawBlendMode(renderer) -> int

   Gets the blend mode used for drawing operations.

   :param renderer: The renderer from which blend mode should be queried.
   :type renderer: :class:`SDL_Renderer`
   :returns: The current blend mode. One of the :ref:`blend-modes`.

.. function:: SDL_RenderClear(renderer: SDL_Renderer) -> None

   Clears the current rendering target with the current drawing color.

   The entire rendering target will be cleared, ignoring the viewport.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`

.. function:: SDL_RenderDrawPoint(renderer, x, y)

   Draws a point on the current rendering target.

   :param renderer: The renderer which should draw a point.
   :type renderer: :class:`SDL_Renderer`
   :param int x: The x coordinate of the point.
   :param int y: The y coordinate of the point.

.. function:: SDL_RenderDrawPoints(renderer, points, count)

   Draw multiple points on the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param points: The points to draw.
   :type points: :class:`SDL_Point` array
   :param int count: The number of points to draw.

.. function:: SDL_RenderDrawLine(renderer, x1, y1, x2, y2)

   Draw a line on the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param int x1: The x coordinate of the start point.
   :param int y1: The y coordinate of the start point.
   :param int x2: The x coordinate of the end point.
   :param int y2: The y coordinate of the end point.

.. function:: SDL_RenderDrawLines(renderer, points, count)

   Draw a series of connected lines on the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param points: The points along the lines.
   :type points: :class:`SDL_Point` array
   :param int count: The number of points, drawing ``count - 1`` lines.

.. function:: SDL_RenderDrawRect(renderer, rect)

   Draw a rectangle on the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The rectangle to draw, or None to outline the entire rendering
                target.
   :type rect: :class:`SDL_Rect` or None

.. function:: SDL_RenderDrawRects(renderer, rects, count)

   Draw some number of rectangles on the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rects: The rectangles to be drawn.
   :type rects: :class:`SDL_Rect` array.
   :param int count: The number of rectangles.

.. function:: SDL_RenderFillRect(renderer: SDL_Renderer, rect: SDL_Rect) -> None

   Fills a rectangle on the current rendering target with the current drawing
   color.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The :class:`SDL_Rect` representing the rectangle to fill. If
                None, the entire rendering target will be filled.
   :type rect: :class:`SDL_Rect` or None

.. function:: SDL_RenderFillRects(renderer, rects, count)

   Fill some number of rectangles on the current rendering target with the
   current drawing color.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rects: The rectangles to be filled.
   :type rects: :class:`SDL_Rect` array
   :param int count: The number of rectangles.

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

Reading pixels
--------------
.. function:: SDL_RenderReadPixels(renderer, rect, format, pixels, pitch)

   Read pixels from the current rendering target.

   :param renderer: The rendering context.
   :type renderer: :class:`SDL_Renderer`
   :param rect: The area to read, or None for the entire render target.
   :type rect: :class:`SDL_Rect` or None
   :param int format: The desired format of the pixel data (one of the
                      :ref:`pixel-format-constants`), or 0 to use the format of
                      the rendering target.
   :param pixels: The buffer to be filled in with the pixel data.
   :type pixels: buffer
   :param int pitch: The pitch of the `pixels` buffer.

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

OpenGL Support
--------------
.. function:: SDL_GL_BindTexture(texture) -> tuple

   Bind an OpenGL/ES/ES2 texture to the current context for use with when
   rendering OpenGL primitives directly.

   :param texture: The texture to bind to the current OpenGL/ES/ES2 context.
   :type texture: :class:`SDL_Texture`
   :returns: A ``(float, float)`` tuple with the texture width and texture
             height respectively.

   .. note:: In most cases, the texture height and width will be 1.0.
             However, on systems that support the GL_ARB_texture_rectangle
             extension, these values will actually be the pixel width and
             height used to create the texture, and so this factor needs to be
             taken into account when providing texture coordinates to OpenGL.

   .. note:: SDL may upload RGB textures as BGR (or vice-versa), and re-order
             the color channels in the shader phase, so the uploaded texture
             may have swapped color channels.

.. function:: SDL_GL_UnbindTexture(texture)

   Unbind an OpenGL/ES/ES2 texture from the current context.

   :param texture: The texture to unbind from the current OpenGL/ES/ES2
                   context.
   :type texture: :class:`SDL_Texture`
