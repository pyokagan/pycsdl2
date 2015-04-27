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

.. data:: SDL_TEXTUREACCESS_STATIC

   Texture changes rarely, not lockable.

.. data:: SDL_TEXTUREACCESS_STREAMING

   Texture changes frequently, lockable.

.. data:: SDL_TEXTUREACCESS_TARGET

   Texture can be used as a render target.

.. data:: SDL_FLIP_NONE

   Do not flip.

.. data:: SDL_FLIP_HORIZONTAL

   Flip horizontally.

.. data:: SDL_FLIP_VERTICAL

   Flip vertically.
