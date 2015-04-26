2D Accelerated Rendering
========================
.. currentmodule:: csdl2

.. class:: SDL_Renderer

   A 2d rendering context.

   This is an opaque handle that cannot be directly constructed. Instead, use
   :func:`SDL_CreateRenderer` or :func:`SDL_CreateSoftwareRenderer`.

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
