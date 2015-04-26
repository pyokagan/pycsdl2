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
