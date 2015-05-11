Audio Device Management, Playing and Recording
==============================================
.. currentmodule:: csdl2

Audio output format
-------------------

.. class:: SDL_AudioSpec(freq=0, format=0, channels=0, silence=0, samples=0, size=0, callback=None, userdata=None)

   Specifies an audio output format. This is used in functions like
   :func:`SDL_OpenAudioDevice`, :func:`SDL_OpenAudio` for specifying the audio
   callback, desired and obtained audio output, and by functions like
   :func:`SDL_LoadWAV` for returning the audio data format of the wave source
   data.

   .. attribute:: freq

      Specifies the number of sample frames sent to the audio device per
      second. Common values are 11025, 22050, 44100 and 48000. Larger values
      produce cleaner audio, in much the same way that larger resolutions
      produce cleaner graphics.

   .. attribute:: format

      Specifies the size and type of each sample element. One of the `Audio
      data format values`_. See `Audio data format`_ for more info.

   .. attribute:: channels

      Specifies the number of output channels. Supported values are 1 (mono), 2
      (stereo), 4 (quad) and 6 (5.1).

   .. attribute:: silence

      Calculated by :func:`SDL_OpenAudioDevice`. The audio device silence
      value.

   .. attribute:: samples

      The audio buffer size in samples. A sample is a chunk of audio data of
      the size specified in `format` multiplied by the number of channels. Must
      be a power of two.

   .. attribute:: size

      Calculated by :func:`SDL_OpenAudioDevice`. The audio buffer size in
      bytes.

   .. attribute:: callback

      When used with :func:`SDL_OpenAudioDevice`, it specifies the callable to
      call when the audio device needs more data. The callable must have the
      function signature::

         callback(userdata, stream, len) -> None

      where `stream` is a pointer to the audio data buffer which must be filled
      in by the callback. `len` is the length of that buffer in bytes.

      Stereo samples are stored in a LRLR ordering.

   .. attribute:: userdata

      Object that is passed as the `userdata` argument to the audio callback.

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
