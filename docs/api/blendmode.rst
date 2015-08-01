Blend modes
===========
.. currentmodule:: csdl2

The following constants are used in :func:`SDL_SetTextureBlendMode`,
:func:`SDL_SetSurfaceBlendMode` and other drawing operations.

.. data:: SDL_BLENDMODE_NONE

   No blending.

   ``dstRGBA = srcRGBA``.

.. data:: SDL_BLENDMODE_BLEND

   Alpha blending.

   ``dstRGB = (srcRGB * srcA) + (dstRGB * (1 - srcA))``

   ``dstA = srcA + (dstA * (1 - srcA))``

.. data:: SDL_BLENDMODE_ADD

   Additive blending.

   ``dstRGB = (srcRGB * srcA) + dstRGB``

   ``dstA = dstA``

.. data:: SDL_BLENDMODE_MOD

   Color modulate.

   ``dstRGB = srcRGB * dstRGB``

   ``dstA = dstA``
