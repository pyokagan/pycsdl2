Audio Device Management, Playing and Recording
==============================================
.. currentmodule:: csdl2

Audio data format
-----------------
The audio format is a 16-bit integer, with its bits used as follows:

===== ========
Bits  Value
===== ========
0-7   Sample bit size
8     Sample is float if set
12    Sample is big-endian if set
15    Sample is signed if set
===== ========

Unspecified bits are always zero, but may be used in later versions of SDL.

.. data:: SDL_AUDIO_MASK_BITSIZE

   Bitmask of the bits storing the sample bit size (bits 0-7).

.. data:: SDL_AUDIO_MASK_DATATYPE

   Bitmask of the bit storing the sample data type flag (bit 8).

.. data:: SDL_AUDIO_MASK_ENDIAN

   Bitmask of the bit storing the sample endianness flag (bit 12).

.. data:: SDL_AUDIO_MASK_SIGNED

   Bitmask of the bit storing the sample sign flag (bit 15).

Audio data format values
~~~~~~~~~~~~~~~~~~~~~~~~
The following are thus the possible audio data format values:

.. data:: AUDIO_U8

   Unsigned 8-bit samples.

.. data:: AUDIO_S8

   Signed 8-bit samples.

.. data:: AUDIO_S16LSB

   Signed 16-bit samples in little-endian byte order.

.. data:: AUDIO_S16MSB

   Signed 16-bit samples in big-endian byte order.

.. data:: AUDIO_S16SYS

   Signed 16-bit samples in native byte order.

.. data:: AUDIO_S16

   Aliased to :const:`AUDIO_S16LSB`.

.. data:: AUDIO_U16LSB

   Unsigned 16-bit samples in little-endian byte order.

.. data:: AUDIO_U16MSB

   Unsigned 16-bit samples in big-endian byte order.

.. data:: AUDIO_U16SYS

   Unsigned 16-bit samples in native byte order.

.. data:: AUDIO_U16

   Aliased to :const:`AUDIO_U16LSB`.

.. data:: AUDIO_S32LSB

   32-bit integer samples in little-endian byte order.

.. data:: AUDIO_S32MSB

   32-bit integer samples in big-endian byte order.

.. data:: AUDIO_S32SYS

   32-bit integer samples in native byte order.

.. data:: AUDIO_S32

   Aliased to :const:`AUDIO_S32LSB`.

.. data:: AUDIO_F32LSB

   32-bit floating point samples in little-endian byte order.

.. data:: AUDIO_F32MSB

   32-bit floating point samples in big-endian byte order.

.. data:: AUDIO_F32SYS

   32-bit floating point samples in native byte order.

.. data:: AUDIO_F32

   Aliased to :const:`AUDIO_F32LSB`.
