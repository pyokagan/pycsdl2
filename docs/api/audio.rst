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

Audio Driver Discovery
----------------------
.. function:: SDL_GetNumAudioDrivers() -> int

   Returns the number of audio drivers that SDL supports.

   :returns: The number of builtin audio drivers.
   :rtype: int

Opening and Closing an Audio Device
-----------------------------------
SDL provides 2 methods for accessing audio devices. The recommended way is to
open the audio device with :func:`SDL_OpenAudioDevice` and then control it with
:func:`SDL_PauseAudioDevice`, :func:`SDL_LockAudioDevice` etc. The legacy way
is to open the audio device with :func:`SDL_OpenAudio`, and then control it
with :func:`SDL_PauseAudio`, :func:`SDL_LockAudio` etc.

Audio data is passed to the audio device through an audio callback, which is
specified through the :attr:`SDL_AudioSpec.callback` attribute. Once the audio
device has been opened, and the audio device unpaused, SDL will call the audio
callback to fill the audio buffer with audio data as needed.

.. class:: SDL_AudioDevice

   An opaque handle returned by :func:`SDL_OpenAudioDevice` representing an
   opened audio device. It's destructor will call :func:`SDL_CloseAudioDevice`.

.. function:: SDL_OpenAudioDevice(device, iscapture, desired, obtained, allowed_changes) -> SDL_AudioDevice

   Opens a specific audio device.

   An opened audio device starts out paused, and should be enabled for playing
   by calling :func:`SDL_PauseAudioDevice` when the audio callback function is
   ready to be called.

   The audio callback runs in a separate thread in most cases. You can prevent
   race conditions between your callback and other threads without fully
   pausing playback with :func:`SDL_LockAudioDevice`.

   :param device: The name of the device to open as reported by
                  :func:`SDL_GetAudioDeviceName`. If None, the default device
                  is opened.
   :type device: str or None
   :param iscapture: True to specify the device should be obtained for
                     recording, not playback.
   :type iscapture: bool
   :param desired: A :class:`SDL_AudioSpec` specifying the audio callback and
                   desired output format.
   :type desired: :class:`SDL_AudioSpec`
   :param obtained: If a :class:`SDL_AudioSpec` is provided, it will be filled
                    with the actual output format. Depending on the value of
                    `allowed_changes`, this can differ from the `desired`
                    :class:`SDL_AudioSpec`.
   :type obtained: :class:`SDL_AudioSpec` or None
   :param allowed_changes: If set to 0, SDL will transparently handle all
                           differences between the `desired` audio output
                           format and the actual hardware. This handling can be
                           selectively disabled by specifying zero or more of
                           the following flags OR'd together:

                           * :const:`SDL_AUDIO_ALLOW_FREQUENCY_CHANGE`
                           * :const:`SDL_AUDIO_ALLOW_FORMAT_CHANGE`
                           * :const:`SDL_AUDIO_ALLOW_CHANNELS_CHANGE`
                           * :const:`SDL_AUDIO_ALLOW_ANY_CHANGE`

                           If these flags are set, the corresponding fields in
                           the `obtained` :class:`SDL_AudioSpec` will be set to
                           the values of the actual hardware audio output
                           format.
   :returns: An :class:`SDL_AudioDevice` object representing the opened audio
             device.

.. data:: SDL_AUDIO_ALLOW_FREQUENCY_CHANGE

   Allow the actual audio output frequency to differ from the desired
   frequency.

.. data:: SDL_AUDIO_ALLOW_FORMAT_CHANGE

   Allow the actual audio output format to differ from the desired format.

.. data:: SDL_AUDIO_ALLOW_CHANNELS_CHANGE

   Allow the actual number of channels to differ from the desired number of
   channels.

.. data:: SDL_AUDIO_ALLOW_ANY_CHANGE

   Allow all of the above changes.

.. function:: SDL_CloseAudioDevice(dev) -> None

   Shuts down audio processing and closes the specified device.

   There is no need to explictly call this function. :class:`SDL_AudioDevice`
   will automatically call this function as part of its destructor.

   :param dev: Audio device to close
   :type dev: :class:`SDL_AudioDevice`

Controlling Playback
--------------------
.. function:: SDL_PauseAudioDevice(dev, pause_on) -> None

   Pause or unpause audio playback on the specified device. When the device is
   paused, silence will be written to the audio device and the audio callback
   is guaranteed to not be called.

   Pausing state does not stack. Even if the device is paused several times, a
   single unpause will start the device playing again, and vice versa.

   If you need to protect a few variables from race conditions with the audio
   callback, you should not pause the audio device as it will lead to dropouts
   in audio playback. Instead, use :func:`SDL_LockAudioDevice`.

   :param dev: Audio device to pause or unpause
   :type dev: :class:`SDL_AudioDevice`
   :param bool pause_on: If True, the audio device will be paused, otherwise
                         the audio device will be unpaused.

WAVE file format support
------------------------
SDL supports loading a Waveform Audio File Format (WAVE) file from a data
stream.

.. function:: SDL_LoadWAV_RW(src: SDL_RWops, freesrc: bool)

   Loads a WAVE from the data source.

   :param src: Data source for the wave file.
   :type src: :class:`SDL_RWops`
   :param bool freesrc: If True, the data source will be freed with
                        :func:`SDL_RWclose`.
   :returns: A 3-tuple (:class:`SDL_AudioSpec`, buffer, int):

             * A :class:`SDL_AudioSpec` specifying the audio format of the
               wave file.
             * A byte buffer containing the audio data.
             * An int specifying the size of the audio data buffer in bytes.

.. function:: SDL_LoadWAV(file: str)

   Loads a WAVE from a file.

   :param str file: Name of the file to load
   :returns: A 3-tuple (:class:`SDL_AudioSpec`, buffer, int):

             * A :class:`SDL_AudioSpec` specifying the audio format of the
               wave file.
             * A byte buffer containing the audio data.
             * An int specifying the size of the audio data buffer in bytes.

.. function:: SDL_FreeWAV(audio_buf) -> None

   Frees the buffer previously allocated with :func:`SDL_LoadWAV` or
   :func:`SDL_LoadWAV_RW`.

   There is no need to explictly call this function. The buffer returned by
   :func:`SDL_LoadWAV` or :func:`SDL_LoadWAV_RW` will automatically call this
   function as part of its destructor.

   :param buffer audio_buf: Buffer created by :func:`SDL_LoadWAV` or
                            :func:`SDL_LoadWAV_RW`.

   .. warning:: Once freed, do not access the buffer. Doing so may crash the
                interpreter.
