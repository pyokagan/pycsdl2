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

.. function:: SDL_AUDIO_BITSIZE(x) -> int

   Query the sample bit size of the audio format.

   This is equivalent to the value of::

      x & SDL_AUDIO_MASK_BITSIZE

   :param int x: The audio format integer.
   :returns: The sample bit size of the audio format.

.. function:: SDL_AUDIO_ISFLOAT(x) -> bool

   Query whether the audio format is a floating point format.

   This is equivalent to the value of::

      bool(x & SDL_AUDIO_MASK_DATATYPE)

   :param int x: The audio format integer.
   :returns: True if the audio format is a floating point format, False
             otherwise.

.. function:: SDL_AUDIO_ISBIGENDIAN(x) -> bool

   Query whether the audio format is a big endian format.

   This is equivalent to the value of::

      bool(x & SDL_AUDIO_MASK_ENDIAN)

   :param int x: The audio format integer.
   :returns: True if the audio format is a big endian format, False otherwise.

.. function:: SDL_AUDIO_ISSIGNED(x) -> bool

   Query whether the audio format is a signed format.

   This is equivalent to the value of::

      bool(x & SDL_AUDIO_MASK_SIGNED)

   :param int x: The audio format integer.
   :returns: True if the audio format is a signed format, False otherwise.

.. function:: SDL_AUDIO_ISINT(x) -> bool

   Query whether the audio format is an integer format.

   This is equivalent to the value of::

      not SDL_AUDIO_ISFLOAT(x)

   :param int x: The audio format integer.
   :returns: True if the audio format is an integer format, False otherwise.

.. function:: SDL_AUDIO_ISLITTLEENDIAN(x) -> bool

   Query whether the audio format is a little endian fornmat.

   This is equivalent to the value of::

      not SDL_AUDIO_ISBIGENDIAN(x)

   :param int x: The audio format integer.
   :returns: True if the audio format is a little endian format, False
             otherwise.

.. function:: SDL_AUDIO_ISUNSIGNED(x) -> bool

   Query whether the audio format is an unsigned format.

   This is equivalent to the value of::

      not SDL_AUDIO_ISSIGNED(x)

   :param int x: The audio format integer.
   :returns: True if the audio format is an unsigned format, False otherwise.

.. _audio-data-format-values:

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

.. function:: SDL_GetAudioDriver(index: int) -> str

   Use this function to get the name of a builtin audio driver. The presence of
   a driver in this list does not mean that it will function, it just means SDL
   is capable of interacting with that interface.

   :param int index: Index of the audio driver. The value ranges from 0 to
                     ``SDL_GetNumAudioDrivers() - 1``.
   :returns: The name of the audio driver at the requested index.
   :rtype: str

.. function:: SDL_GetCurrentAudioDriver()

   Returns the name of the current audio driver.

   :returns: The name of the current audio driver, or None if no driver has
             been initialized.
   :rtype: str or None

Initialization and Cleanup
--------------------------
These functions are used internally, and should not be used unless you have a
specific need to specify the audio driver.

.. function:: SDL_AudioInit(driver_name)

   Initializes a particular audio driver.

   :param driver_name: The name of the desired audio driver.
   :type driver_name: str or None

.. function:: SDL_AudioQuit()

   Use this function to shut down audio if you initialized it with
   :func:`SDL_AudioInit`.

Audio Device Discovery
----------------------
.. function:: SDL_GetNumAudioDevices(iscapture) -> int

   Query the number of audio devices.

   This function may trigger a complete redetection of available hardware,
   which is an expensive operation.

   :param bool iscapture: False to request playback devices, True to request
                          recording devices.
   :returns: The number of available devices exposed by the current driver, or
             -1 if an explicit list of devices can't be determined.

   .. note:: The `iscapture` parameter is for future expansion and should
             always be False for now.

.. function:: SDL_GetAudioDeviceName(index, iscapture) -> str

   Query the name of an audio device.

   :param int index: The index of the audio device. The value ranges from 0 to
                     ``SDL_GetNumAudioDevices() - 1``
   :param bool iscapture: True to specify a device that has recording
                          capability.
   :returns: The name of the audio device at the requested index.

   .. note::

      This function is only valid after successfully initializing the audio
      subsystem. The values returned by this function reflect the latest call
      to :func:`SDL_GetNumAudioDevices`. Re-call that function to re-detect
      available hardware.

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

.. function:: SDL_OpenAudio(desired, obtained)

   Opens the audio device with the `desired` output format.

   This function is a legacy means of opening the audio device. Use
   :func:`SDL_OpenAudioDevice` instead.

   :param desired: Specifies the desired output format and audio callback
   :type desired: :class:`SDL_AudioSpec`
   :param obtained: A :class:`SDL_AudioSpec` that will be filled in with the
                    hardware parameters. If None, the the output format of the
                    audio device is guaranteed to match the desired output
                    format. SDL will convert the audio data to the actual
                    hardware audio format if necessary. The `desired`
                    :class:`SDL_AudioSpec` will have its fields modified as
                    well.
   :type obtained: :class:`SDL_AudioSpec` or None

.. function:: SDL_CloseAudio()

   Shuts down audio processing and closes the audio device.

Querying Playback Status
------------------------
An audio device can be in any one of these 3 states:

.. data:: SDL_AUDIO_STOPPED

   Audio device is stopped.

.. data:: SDL_AUDIO_PLAYING

   Audio device is playing.

.. data:: SDL_AUDIO_PAUSED

   Audio device is paused.

:func:`SDL_GetAudioStatus` and :func:`SDL_GetAudioDeviceStatus` can be used to
query the playback status of an audio device.

.. function:: SDL_GetAudioDeviceStatus(dev) -> int

   Query the playback status of the specified audio device.

   :param dev: Audio device to query.
   :type dev: :class:`SDL_AudioDevice`
   :returns: The playback status of the specified audio device, which is one of
             :const:`SDL_AUDIO_STOPPED`, :const:`SDL_AUDIO_PLAYING` or
             :const:`SDL_AUDIO_PAUSED`.

.. function:: SDL_GetAudioStatus() -> int

   Query the playback status of the audio device.

   This function is a legacy means of querying the audio device. Use
   :func:`SDL_GetAudioDeviceStatus` instead.

   :returns: The playback status of the audio device, which is one of
             :const:`SDL_AUDIO_STOPPED`, :const:`SDL_AUDIO_PLAYING` or
             :const:`SDL_AUDIO_PAUSED`.

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

.. function:: SDL_PauseAudio(pause_on)

   Pause or unpause audio playback on the audio device. When the device is
   paused, silence will be written to the audio device and the audio callback
   is guaranteed to not be called.

   Pausing state does not stack. Even if the device is paused several times, a
   single unpause will start the device playing again, and vice versa.

   If you need to protect a few variables from race conditions with the audio
   callback, you should not pause the audio device as it will lead to dropouts
   in audio playback. Instead, use :func:`SDL_LockAudio`.

   This function is a legacy means of pausing the audio device. Use
   :func:`SDL_PauseAudioDevice` instead.

   :param bool pause_on: If True, the audio device will be paused, otherwise
                         audio device will be unpaused.

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

Audio Data Conversion
---------------------
Audio data conversion is done in 3 steps:

1. An :class:`SDL_AudioCVT` structure is initialized with
   :func:`SDL_BuildAudioCVT`.

2. The application sets up an appropriately-sized buffer containing the source
   data, assigning it to :attr:`SDL_AudioCVT.buf`. The application must also
   set :attr:`SDL_AudioCVT.len` to the source data size in bytes. The actual
   size of the buffer must be at least ``len * len_mult`` bytes large, as the
   conversion will be done using this buffer.

3. The actual audio data conversion is done by calling :func:`SDL_ConvertAudio`
   with the :class:`SDL_AudioCVT` struct. The converted audio data will be
   written to the provided audio buffer.

.. class:: SDL_AudioCVT()

   A structure that contains audio data conversion information.

   It is initialized with :func:`SDL_BuildAudioCVT`, and passed to
   :func:`SDL_ConvertAudio` to do the actual conversion once the application
   has set up appropriately-sized buffers between these two function calls.

   conversion is done by :func:`SDL_ConvertAudio`

   .. attribute:: needed

      (readonly) True if conversion is needed.

   .. attribute:: src_format

      (readonly) Source audio format.

   .. attribute:: dst_format

      (readonly) Target audio format

   .. attribute:: rate_incr

      (readonly) Rate conversion increment.

   .. attribute:: buf

      This attribute should point to the audio data that will be used in the
      conversion.

      The buffer is both the source and the destination, which means the
      converted audio data overwrites the original data. It also means that
      converted data may be larger than the original data (if you were
      converting from 8-bit to 16-bit, for instance), so you must ensure
      :attr:`SDL_AudioCVT.buf` is larger enough for any stage of the
      conversion, regardless of the final converted data's size.

      The buffer must have a size of at least ``len * len_mult``.

   .. attribute:: len

      Length of original audio buffer in bytes.

   .. attribute:: len_cvt

      (readonly) Length of converted audio buffer.

   .. attribute:: len_mult

      (readonly) The length multiplier for determining the size of the
      converted data.

      The audio buffer may need to be larger than either the original data or
      the converted data. The allocated size of :attr:`SDL_AudioCVT.buf`
      must have a size of at least ``len * len_mult`` bytes.

   .. attribute:: len_ratio

      (readonly) The length ratio of the converted data to the original data.

      When you have finished converting your audio data, you need to know how
      much of your audio buffer is valid. ``len * len_ratio`` is the size of
      the converted audio data in bytes.

      This is similar to :attr:`SDL_AudioCVT.len_mult`. However, when the
      converted audio data is shorter than the original,
      :attr:`SDL_AudioCVT.len_mult` will be 1. :attr:`SDL_AudioCVT.len_ratio`
      on the other hand will be a fractional number between 0 and 1.

.. function:: SDL_BuildAudioCVT(cvt, src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate) -> bool

   Initialize a :class:`SDL_AudioCVT` structure for conversion.

   :param cvt: An :class:`SDL_AudioCVT` structure to be filled in with audio
               conversion information.
   :type cvt: :class:`SDL_AudioCVT`
   :param int src_format: The source format of the audio data. One of the
                          :ref:`audio-data-format-values`.
   :param int src_channels: The number of channels in the source.
   :param int src_rate: The frequency (sample-frames-per-second) of the source.
   :param int dst_format: The destination format of the audio data. One of the
                          :ref:`audio-data-format-values`.
   :param int dst_channels: The number of channels in the destination.
   :param int dst_rate: The frequency (sample-frames-per-second) of the
                        destination.
   :returns: True if conversion is needed, False otherwise.

   .. note::

      This function will zero out every field of the :class:`SDL_AudioCVT`, so
      it must be called before the application fills in the final buffer
      information.

.. function:: SDL_ConvertAudio(cvt)

   Convert the audio data as specified by the :class:`SDL_AudioCVT` structure.

   :param cvt: An :class:`SDL_AudioCVT` structure with the information required
               for audio conversion.

   .. note::

      The :class:`SDL_AudioCVT` structure must first be initialized with
      :func:`SDL_BuildAudioCVT`.

      The application then needs to set the :class:`SDL_AudioCVT` structure's
      :attr:`SDL_AudioCVT.buf` attribute to the audio buffer containing the
      source audio data, and :attr:`SDL_AudioCVT.len` attribute to the size, in
      bytes, of the source data.

      This same buffer is used for data conversion, and will contain the
      converted audio data after calling this function. The converted audio
      data, or any of the intermediate conversion data, may be larger than the
      source data, and thus the actual size of the buffer must be at least
      ``len * len_mult`` bytes long.

      This function will write the converted audio data to the buffer, and will
      set :attr:`SDL_AudioCVT.len_cvt` to the size in bytes of the converted
      audio data.
