"""test bindings in src/audio.h"""
import distutils.util
import os.path
import sys
import unittest
import threading
import struct
import io
import tempfile


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa
import _csdl2test  # noqa


try:
    SDL_Init(SDL_INIT_AUDIO)
    has_audio = True
except RuntimeError:
    has_audio = False


class TestAudioConstants(unittest.TestCase):
    """Tests value of SDL_audio.h constants"""

    def test_SDL_AUDIO_MASK_BITSIZE(self):
        self.assertEqual(SDL_AUDIO_MASK_BITSIZE, 0xFF)

    def test_SDL_AUDIO_MASK_DATATYPE(self):
        self.assertEqual(SDL_AUDIO_MASK_DATATYPE, 1 << 8)

    def test_SDL_AUDIO_MASK_ENDIAN(self):
        self.assertEqual(SDL_AUDIO_MASK_ENDIAN, 1 << 12)

    def test_SDL_AUDIO_MASK_SIGNED(self):
        self.assertEqual(SDL_AUDIO_MASK_SIGNED, 1 << 15)

    def test_AUDIO_U8(self):
        self.assertEqual(AUDIO_U8, 0x0008)

    def test_AUDIO_S8(self):
        self.assertEqual(AUDIO_S8, 0x8008)

    def test_AUDIO_U16LSB(self):
        self.assertEqual(AUDIO_U16LSB, 0x0010)

    def test_AUDIO_S16LSB(self):
        self.assertEqual(AUDIO_S16LSB, 0x8010)

    def test_AUDIO_U16MSB(self):
        self.assertEqual(AUDIO_U16MSB, 0x1010)

    def test_AUDIO_S16MSB(self):
        self.assertEqual(AUDIO_S16MSB, 0x9010)

    def test_AUDIO_U16(self):
        self.assertEqual(AUDIO_U16, AUDIO_U16LSB)

    def test_AUDIO_S16(self):
        self.assertEqual(AUDIO_S16, AUDIO_S16LSB)

    def test_AUDIO_S32LSB(self):
        self.assertEqual(AUDIO_S32LSB, 0x8020)

    def test_AUDIO_S32MSB(self):
        self.assertEqual(AUDIO_S32MSB, 0x9020)

    def test_AUDIO_S32(self):
        self.assertEqual(AUDIO_S32, AUDIO_S32LSB)

    def test_AUDIO_F32LSB(self):
        self.assertEqual(AUDIO_F32LSB, 0x8120)

    def test_AUDIO_F32MSB(self):
        self.assertEqual(AUDIO_F32MSB, 0x9120)

    def test_AUDIO_F32(self):
        self.assertEqual(AUDIO_F32, AUDIO_F32LSB)

    def test_AUDIO_U16SYS(self):
        if sys.byteorder == 'little':
            self.assertEqual(AUDIO_U16SYS, AUDIO_U16LSB)
        else:
            self.assertEqual(AUDIO_U16SYS, AUDIO_U16MSB)

    def test_AUDIO_S16SYS(self):
        if sys.byteorder == 'little':
            self.assertEqual(AUDIO_S16SYS, AUDIO_S16LSB)
        else:
            self.assertEqual(AUDIO_S16SYS, AUDIO_S16MSB)

    def test_AUDIO_S32SYS(self):
        if sys.byteorder == 'little':
            self.assertEqual(AUDIO_S32SYS, AUDIO_S32LSB)
        else:
            self.assertEqual(AUDIO_S32SYS, AUDIO_S32MSB)

    def test_AUDIO_F32SYS(self):
        if sys.byteorder == 'little':
            self.assertEqual(AUDIO_F32SYS, AUDIO_F32LSB)
        else:
            self.assertEqual(AUDIO_F32SYS, AUDIO_F32MSB)

    def test_SDL_AUDIO_ALLOW_FREQUENCY_CHANGE(self):
        self.assertEqual(SDL_AUDIO_ALLOW_FREQUENCY_CHANGE, 0x01)

    def test_SDL_AUDIO_ALLOW_FORMAT_CHANGE(self):
        self.assertEqual(SDL_AUDIO_ALLOW_FORMAT_CHANGE, 0x02)

    def test_SDL_AUDIO_ALLOW_CHANNELS_CHANGE(self):
        self.assertEqual(SDL_AUDIO_ALLOW_CHANNELS_CHANGE, 0x04)

    def test_SDL_AUDIO_ALLOW_ANY_CHANGE(self):
        self.assertEqual(SDL_AUDIO_ALLOW_ANY_CHANGE, 7)

    def test_SDL_AUDIO_STOPPED(self):
        self.assertEqual(SDL_AUDIO_STOPPED, 0)

    def test_SDL_AUDIO_PLAYING(self):
        self.assertEqual(SDL_AUDIO_PLAYING, 1)

    def test_SDL_AUDIO_PAUSED(self):
        self.assertEqual(SDL_AUDIO_PAUSED, 2)

    def test_SDL_MIX_MAXVOLUME(self):
        self.assertEqual(SDL_MIX_MAXVOLUME, 128)


class TestAudioSpec(unittest.TestCase):
    """Tests SDL_AudioSpec"""

    def setUp(self):
        self.spec = SDL_AudioSpec()

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_AudioSpec,), {})

    def test_init(self):
        "__init__() with positional arguments"
        def callback(): return None
        userdata = {}
        self.spec.__init__(1, 2, 3, 4, 5, 6, callback, userdata)
        self.assertEqual(self.spec.freq, 1)
        self.assertEqual(self.spec.format, 2)
        self.assertEqual(self.spec.channels, 3)
        self.assertEqual(self.spec.silence, 4)
        self.assertEqual(self.spec.samples, 5)
        self.assertEqual(self.spec.size, 6)
        self.assertIs(self.spec.callback, callback)
        self.assertIs(self.spec.userdata, userdata)

    def test_init_kwds(self):
        "__init__() with keyword arguments"
        def callback(): return None
        userdata = {}
        self.spec.__init__(freq=1, format=2, channels=3, silence=4, samples=5,
                           size=6, callback=callback, userdata=userdata)
        self.assertEqual(self.spec.freq, 1)
        self.assertEqual(self.spec.format, 2)
        self.assertEqual(self.spec.channels, 3)
        self.assertEqual(self.spec.silence, 4)
        self.assertEqual(self.spec.samples, 5)
        self.assertEqual(self.spec.size, 6)
        self.assertIs(self.spec.callback, callback)
        self.assertIs(self.spec.userdata, userdata)

    def test_init_default(self):
        "default arguments of __init__() are 0"
        def callback(): return None
        userdata = {}
        self.spec.__init__(1, 2, 3, 4, 5, 6, callback, userdata)
        self.spec.__init__()
        self.assertEqual(self.spec.freq, 0)
        self.assertEqual(self.spec.format, 0)
        self.assertEqual(self.spec.channels, 0)
        self.assertEqual(self.spec.silence, 0)
        self.assertEqual(self.spec.samples, 0)
        self.assertEqual(self.spec.size, 0)
        self.assertIs(self.spec.callback, None)
        self.assertIs(self.spec.userdata, None)

    def test_freq(self):
        "freq is an int"
        self.assertIs(type(self.spec.freq), int)
        self.assertEqual(self.spec.freq, 0)

    def test_freq_set(self):
        "freq can be set to an int"
        self.spec.freq = 42
        self.assertEqual(self.spec.freq, 42)

    def test_format(self):
        "format is an int"
        self.assertIs(type(self.spec.format), int)
        self.assertEqual(self.spec.format, 0)

    def test_format_set(self):
        "format can be set to an int"
        self.spec.format = 42
        self.assertEqual(self.spec.format, 42)

    def test_channels(self):
        "channels is an int"
        self.assertIs(type(self.spec.channels), int)
        self.assertEqual(self.spec.channels, 0)

    def test_channels_set(self):
        "channels can be set to an int"
        self.spec.channels = 42
        self.assertEqual(self.spec.channels, 42)

    def test_silence(self):
        "silence is an int"
        self.assertIs(type(self.spec.silence), int)
        self.assertEqual(self.spec.silence, 0)

    def test_silence_set(self):
        "silence can be set to an int"
        self.spec.silence = 42
        self.assertEqual(self.spec.silence, 42)

    def test_samples(self):
        "samples is an int"
        self.assertIs(type(self.spec.samples), int)
        self.assertEqual(self.spec.samples, 0)

    def test_samples_set(self):
        "samples can be set to an int"
        self.spec.samples = 42
        self.assertEqual(self.spec.samples, 42)

    def test_size(self):
        "size is an int"
        self.assertIs(type(self.spec.size), int)
        self.assertEqual(self.spec.size, 0)

    def test_size_set(self):
        "size can be set to an int"
        self.spec.size = 42
        self.assertEqual(self.spec.size, 42)

    def test_callback(self):
        "callback is an object"
        self.assertIs(self.spec.callback, None)

    def test_callback_set(self):
        "callback can be set to a callable"
        def f(x, y, z): return None
        self.spec.callback = f
        self.assertIs(self.spec.callback, f)

    def test_userdata(self):
        "userdata is an object"
        self.assertIs(self.spec.userdata, None)

    def test_userdata_set(self):
        "userdata can be set to an object"
        x = {}
        self.spec.userdata = x
        self.assertIs(self.spec.userdata, x)


class TestAudioCVT(unittest.TestCase):
    "Tests SDL_AudioCVT class"

    def setUp(self):
        self.cvt = SDL_AudioCVT()

    def test_cannot_subclass(self):
        "Cannot be used as base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_AudioCVT,), {})

    def test_needed(self):
        "needed is a bool"
        self.assertIs(type(self.cvt.needed), bool)

    def test_needed_readonly(self):
        "needed is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'needed', True)

    def test_src_format_int(self):
        "src_format is an int"
        self.assertIs(type(self.cvt.src_format), int)

    def test_src_format_readonly(self):
        "src_format is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'src_format', 42)

    def test_dst_format_int(self):
        "dst_format is an int"
        self.assertIs(type(self.cvt.dst_format), int)

    def test_dst_format_readonly(self):
        "dst_format is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'dst_format', 42)

    def test_rate_incr(self):
        "rate_incr is a float"
        self.assertIs(type(self.cvt.rate_incr), float)

    def test_rate_incr_readonly(self):
        "rate_incr is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'rate_incr', 42)

    def test_buf_none(self):
        "buf is initialized to None"
        self.assertIs(self.cvt.buf, None)

    def test_buf_buffer(self):
        "buf can be set to a buffer"
        x = bytearray(1)
        self.cvt.buf = x
        self.assertIs(self.cvt.buf, x)

    def test_buf_not_buffer(self):
        "buf raises TypeError when object is not a buffer"
        self.assertRaises(TypeError, setattr, self.cvt, 'buf', {})

    def test_len_int(self):
        "len is an int"
        self.assertIs(type(self.cvt.len), int)

    def test_len_set_int(self):
        "len can be set to an int"
        self.cvt.len = 42
        self.assertEqual(self.cvt.len, 42)

    def test_len_cvt_int(self):
        "len_cvt is an int"
        self.assertIs(type(self.cvt.len_cvt), int)

    def test_len_cvt_readonly(self):
        "len_cvt is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'len_cvt', 42)

    def test_len_mult_int(self):
        "len_mult is an int"
        self.assertIs(type(self.cvt.len_mult), int)

    def test_len_mult_readonly(self):
        "len_mult is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'len_mult', 42)

    def test_len_ratio_float(self):
        "len_ratio is a float"
        self.assertIs(type(self.cvt.len_ratio), float)

    def test_len_ratio_readonly(self):
        "len_ratio is readonly"
        self.assertRaises(AttributeError, setattr, self.cvt, 'len_ratio', 42)


class TestAudioDevice(unittest.TestCase):
    """Tests SDL_AudioDevice class"""

    def test_cannot_create(self):
        "Cannot create SDL_AudioDevice instances"
        self.assertRaises(TypeError, SDL_AudioDevice)
        self.assertRaises(TypeError, SDL_AudioDevice.__new__, SDL_AudioDevice)

    def test_cannot_inherit(self):
        "Cannot be used as a base class"
        self.assertRaises(TypeError, type, 'testtype', (SDL_AudioDevice,), {})


class TestAUDIO_BITSIZE(unittest.TestCase):
    "Tests SDL_AUDIO_BITSIZE()"

    def test_returns_int(self):
        "Returns int"
        self.assertIs(type(SDL_AUDIO_BITSIZE(42)), int)


class TestAUDIO_ISFLOAT(unittest.TestCase):
    "Tests SDL_AUDIO_ISFLOAT()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISFLOAT(42)), bool)


class TestAUDIO_ISBIGENDIAN(unittest.TestCase):
    "Tests SDL_AUDIO_ISBIGENDIAN()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISBIGENDIAN(42)), bool)


class TestAUDIO_ISSIGNED(unittest.TestCase):
    "Tests SDL_AUDIO_ISSIGNED()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISSIGNED(42)), bool)


class TestAUDIO_ISINT(unittest.TestCase):
    "Tests SDL_AUDIO_ISINT()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISINT(42)), bool)


class TestAUDIO_ISLITTLEENDIAN(unittest.TestCase):
    "Tests SDL_AUDIO_ISLITTLEENDIAN()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISLITTLEENDIAN(42)), bool)


class TestAUDIO_ISUNSIGNED(unittest.TestCase):
    "Tests SDL_AUDIO_ISUNSIGNED()"

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_AUDIO_ISUNSIGNED(42)), bool)


class TestGetNumAudioDrivers(unittest.TestCase):
    "Tests SDL_GetNumAudioDrivers()"

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_GetNumAudioDrivers()), int)


class TestGetAudioDriver(unittest.TestCase):
    "Tests SDL_GetAudioDriver()"

    def test_returns_str(self):
        "Returns a str"
        if not SDL_GetNumAudioDrivers():
            raise unittest.SkipTest('No audio drivers')
        self.assertIs(type(SDL_GetAudioDriver(0)), str)

    def test_out_of_range(self):
        "Raises ValueError when index is out of range"
        self.assertRaises(ValueError, SDL_GetAudioDriver,
                          SDL_GetNumAudioDrivers() + 1)


class TestAudioInit(unittest.TestCase):
    "Tests SDL_AudioInit()"

    def setUp(self):
        self.driver_name = SDL_GetCurrentAudioDriver()
        if not self.driver_name:
            raise unittest.SkipTest('No audio support')

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_AudioInit(self.driver_name), None)

    def test_none_driver_name(self):
        "Driver name can be None"
        self.assertIs(SDL_AudioInit(None), None)


class TestAudioQuit(unittest.TestCase):
    "Tests SDL_AudioQuit()"

    def setUp(self):
        self.driver_name = SDL_GetCurrentAudioDriver()
        if not self.driver_name:
            raise unittest.SkipTest('No audio support')

    def tearDown(self):
        SDL_AudioInit(self.driver_name)

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_AudioQuit(), None)


class TestGetCurrentAudioDriver(unittest.TestCase):
    "Tests SDL_GetCurrentAudioDriver()"

    def test_returns_str_or_none(self):
        "Returns str or None"
        x = SDL_GetCurrentAudioDriver()
        self.assertTrue(x is None or type(x) is str)


class TestOpenAudio(unittest.TestCase):
    "Tests SDL_OpenAudio()"

    def setUp(self):
        if not has_audio:
            raise unittest.SkipTest('no audio support')

        def callback(userdata, data, length):
            self.assertIs(type(length), int)
            x = memoryview(data)
            self.assertEqual(x.nbytes, length)
            self.assertEqual(x.itemsize, 1)
            self.assertEqual(x.format, 'B')
            for i in range(x.nbytes):
                x[i] = self.obtained.silence
            # we can store a ref to the data object (though not it's buffer)
            self.data = data
            with self.cv:
                self.called = userdata
                self.cv.notify()

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback, userdata=True)
        self.obtained = SDL_AudioSpec()
        self.called = None
        self.cv = threading.Condition()

    def tearDown(self):
        SDL_CloseAudio()

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_OpenAudio(self.desired, self.obtained), None)

    def test_fails_no_callback(self):
        "Fails if callback is None"
        self.desired.callback = None
        self.assertRaises(ValueError, SDL_OpenAudio, self.desired,
                          self.obtained)

    def test_obtained_none(self):
        "obtained can be None"
        self.assertIs(SDL_OpenAudio(self.desired, None), None)

    def test_callback(self):
        "callback is saved in the audio device and called"
        def wrong_callback(userdata, data, length):
            with self.cv:
                self.called = {}
                self.cv.notify()

        SDL_OpenAudio(self.desired, self.obtained)
        self.desired.callback = wrong_callback
        self.desired.userdata = False
        SDL_PauseAudio(False)
        with self.cv:
            self.cv.wait_for(lambda: self.called)
        self.assertTrue(self.called)
        # If we save the data buffer provided to the callback, it is still
        # invalidated.
        self.assertRaises(ValueError, len, self.data)


class TestGetNumAudioDevices(unittest.TestCase):
    "Tests SDL_GetNumAudioDevices()"

    def setUp(self):
        if not has_audio:
            raise unittest.SkipTest('No audio support')

    def test_returns_int(self):
        "Returns an int"
        self.assertIs(type(SDL_GetNumAudioDevices(False)), int)


class TestGetAudioDeviceName(unittest.TestCase):
    "Tests SDL_GetAudioDeviceName()"

    def setUp(self):
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        if SDL_GetNumAudioDevices(False) <= 0:
            raise unittest.SkipTest('No audio devices')

    def test_returns_str(self):
        "Returns a str"
        self.assertIs(type(SDL_GetAudioDeviceName(0, False)), str)


class TestOpenAudioDevice(unittest.TestCase):
    """Tests SDL_OpenAudioDevice()"""

    @classmethod
    def setUpClass(cls):
        if not has_audio:
            raise unittest.SkipTest('No audio support')

    def setUp(self):
        def callback(userdata, data, length):
            self.assertIs(type(length), int)
            x = memoryview(data)
            self.assertEqual(x.nbytes, length)
            self.assertEqual(x.itemsize, 1)
            self.assertEqual(x.format, 'B')
            for i in range(x.nbytes):
                x[i] = self.obtained.silence
            # we can store a ref to the data object (though not it's buffer)
            self.data = data
            with self.cv:
                self.called = userdata
                self.cv.notify()

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback, userdata=True)
        self.obtained = SDL_AudioSpec()
        self.called = None
        self.cv = threading.Condition()

    def test_returns_AudioDevice(self):
        "Returns an SDL_AudioDevice object"
        x = SDL_OpenAudioDevice(None, False, self.desired, self.obtained,
                                0)
        self.assertIs(type(x), SDL_AudioDevice)

    def test_fails_no_callback(self):
        "Fails if callback is None"
        self.desired.callback = None
        self.assertRaises(ValueError, SDL_OpenAudioDevice, None, False,
                          self.desired, self.obtained, 0)

    def test_obtained_none(self):
        "obtained can be None"
        x = SDL_OpenAudioDevice(None, False, self.desired, None, 0)

    def test_callback(self):
        "callback is saved in the audio device and called"
        def wrong_callback(userdata, data, length):
            with self.cv:
                self.called = {}
                self.cv.notify()

        dev = SDL_OpenAudioDevice(None, False, self.desired, self.obtained, 0)
        self.desired.callback = wrong_callback
        self.desired.userdata = False
        SDL_PauseAudioDevice(dev, False)
        with self.cv:
            self.cv.wait_for(lambda: self.called)
        self.assertTrue(self.called)
        # If we save the data buffer provided to the callback, it is still
        # invalidated.
        self.assertRaises(ValueError, len, self.data)


class TestGetAudioStatus(unittest.TestCase):
    "Tests SDL_GetAudioStatus()"

    def setUp(self):
        def callback(a, b, c):
            return None
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_CloseAudio()

    def test_returns_int(self):
        "Returns int"
        self.assertIs(type(SDL_GetAudioStatus()), int)

    def test_closed(self):
        "No-op when the audio device is not open"
        SDL_CloseAudio()
        self.assertIs(type(SDL_GetAudioStatus()), int)


class TestGetAudioDeviceStatus(unittest.TestCase):
    "Tests SDL_GetAudioDeviceStatus()"

    def setUp(self):
        def callback(userdata, data, length):
            x = memoryview(data)
            for i in range(x.nbytes):
                x[i] = self.obtained.silence

        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        self.dev = SDL_OpenAudioDevice(None, False, self.desired,
                                       self.obtained, 0)

    def tearDown(self):
        del self.dev

    def test_returns_int(self):
        "Returns int"
        self.assertIs(type(SDL_GetAudioDeviceStatus(self.dev)), int)

    def test_closed(self):
        "Raises ValueError if the device has been closed"
        SDL_CloseAudioDevice(self.dev)
        self.assertRaises(ValueError, SDL_GetAudioDeviceStatus, self.dev)


class TestPauseAudio(unittest.TestCase):
    "Tests SDL_PauseAudio()"

    def setUp(self):
        if not has_audio:
            raise unittest.SkipTest('no audio support')

        def callback(userdata, data, length):
            x = memoryview(data)
            for i in range(x.nbytes):
                x[i] = self.obtained.silence

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_CloseAudio()

    def test_true(self):
        "SDL_PauseAudio(True) works"
        self.assertIs(SDL_PauseAudio(True), None)

    def test_false(self):
        "SDL_PauseAudio(False) works"
        self.assertIs(SDL_PauseAudio(False), None)

    def test_closed(self):
        "No-op when the audio device is not open"
        SDL_CloseAudio()
        self.assertIs(SDL_PauseAudio(False), None)


class TestPauseAudioDevice(unittest.TestCase):
    """Tests SDL_PauseAudioDevice()"""

    @classmethod
    def setUpClass(cls):
        if not has_audio:
            raise unittest.SkipTest('No audio support')

    def setUp(self):
        def callback(userdata, data, length):
            x = memoryview(data)
            for i in range(x.nbytes):
                x[i] = self.obtained.silence

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        self.dev = SDL_OpenAudioDevice(None, False, self.desired,
                                       self.obtained, 0)

    def tearDown(self):
        del self.dev

    def test_true(self):
        "SDL_PauseAudioDevice(dev, True) works"
        self.assertIs(SDL_PauseAudioDevice(self.dev, True), None)

    def test_false(self):
        "SDL_PauseAudioDevice(dev, False) works"
        self.assertIs(SDL_PauseAudioDevice(self.dev, False), None)

    def test_closed(self):
        "Raises ValueError when the SDL_AudioDevice has been closed"
        SDL_CloseAudioDevice(self.dev)
        self.assertRaises(ValueError, SDL_PauseAudioDevice, self.dev, False)


def sample_wave(num_channels, sample_rate, bits_per_sample):
    "Generates and returns a sample WAVE file."
    byte_rate = sample_rate * num_channels * bits_per_sample // 8
    block_align = num_channels * bits_per_sample // 8
    fmt_chunk = struct.pack('<4sIHHIIHH', b'fmt ', 16, 1, num_channels,
                            sample_rate, byte_rate, block_align,
                            bits_per_sample)
    data = bytes(1 * num_channels * bits_per_sample // 8)
    data_chunk = struct.pack('<4sI', b'data', len(data)) + data
    wave_chunk = b'WAVE' + fmt_chunk + data_chunk
    riff_chunk = struct.pack('<4sI', b'RIFF', len(wave_chunk)) + wave_chunk
    return riff_chunk


class TestLoadWAVRW(unittest.TestCase):
    """Tests for SDL_LoadWAV_RW()"""

    @classmethod
    def setUpClass(cls):
        cls.num_channels = 1
        cls.sample_rate = 8000
        cls.bits_per_sample = 8

    def setUp(self):
        f = io.BytesIO(sample_wave(self.num_channels, self.sample_rate,
                                   self.bits_per_sample))
        self.rwops = SDL_AllocRW()
        self.rwops.size = lambda a: len(f.getbuffer())
        self.rwops.read = lambda a, b, c, d: f.readinto(b) // c
        self.rwops.seek = lambda a, b, c: f.seek(b, c)
        self.rwops.close = lambda a: SDL_FreeRW(a)

    def test_return(self):
        "Returns a (SDL_AudioSpec, buffer, int) tuple"
        audiospec, buf, size = SDL_LoadWAV_RW(self.rwops, True)
        self.assertIs(type(audiospec), SDL_AudioSpec)
        self.assertEqual(audiospec.freq, self.sample_rate)
        self.assertEqual(audiospec.format, AUDIO_U8)
        self.assertEqual(audiospec.channels, self.num_channels)
        self.assertIs(audiospec.callback, None)
        self.assertIs(audiospec.userdata, None)
        self.assertIs(type(size), int)


class TestLoadWAV(unittest.TestCase):
    """Tests for SDL_LoadWAV()"""

    @classmethod
    def setUpClass(cls):
        cls.num_channels = 1
        cls.sample_rate = 8000
        cls.bits_per_sample = 8
        cls.dir = tempfile.TemporaryDirectory()
        cls.path = os.path.join(cls.dir.name, 'test.wav')
        with open(cls.path, 'wb') as f:
            f.write(sample_wave(cls.num_channels, cls.sample_rate,
                                cls.bits_per_sample))

    @classmethod
    def tearDownClass(cls):
        # Handle "directory not empty" errors on Windows by attempting 3 times
        for i in range(3):
            try:
                cls.dir.cleanup()
            except OSError:
                continue
            break

    def test_return(self):
        "Returns a (SDL_AudioSpec, buffer, int) tuple"
        audiospec, buf, size = SDL_LoadWAV(self.path)
        self.assertIs(type(audiospec), SDL_AudioSpec)
        self.assertEqual(audiospec.freq, self.sample_rate)
        self.assertEqual(audiospec.format, AUDIO_U8)
        self.assertEqual(audiospec.channels, self.num_channels)
        self.assertIs(audiospec.callback, None)
        self.assertIs(audiospec.userdata, None)
        self.assertIs(type(size), int)


class TestFreeWAV(unittest.TestCase):
    """Tests for SDL_FreeWAV()"""

    def setUp(self):
        f = io.BytesIO(sample_wave(1, 8000, 8))
        rwops = SDL_AllocRW()
        rwops.size = lambda a: len(f.getbuffer())
        rwops.read = lambda a, b, c, d: f.readinto(b) // c
        rwops.seek = lambda a, b, c: f.seek(b, c)
        rwops.close = lambda a: SDL_FreeRW(a)
        self.audiospec, self.buf, self.size = SDL_LoadWAV_RW(rwops, True)

    def test_return(self):
        "Returns None"
        self.assertIs(SDL_FreeWAV(self.buf), None)

    def test_freed(self):
        "When freed, raises ValueError"
        SDL_FreeWAV(self.buf)
        self.assertRaises(ValueError, SDL_FreeWAV, self.buf)


class TestBuildAudioCVT(unittest.TestCase):
    "Tests for SDL_BuildAudioCVT()"

    def setUp(self):
        self.cvt = SDL_AudioCVT()

    def test_returns_bool(self):
        "Returns bool"
        self.assertIs(type(SDL_BuildAudioCVT(self.cvt, AUDIO_F32, 2, 48000,
                                             AUDIO_S16, 2, 48000)), bool)

    def test_clears_buf(self):
        "Clears the buf field"
        x = bytearray(1)
        self.cvt.buf = x
        self.assertIs(self.cvt.buf, x)
        SDL_BuildAudioCVT(self.cvt, AUDIO_F32, 2, 48000, AUDIO_S16, 2, 48000)
        self.assertIs(self.cvt.buf, None)


class TestConvertAudio(unittest.TestCase):
    "Tests for SDL_ConvertAudio()"

    def setUp(self):
        self.cvt = SDL_AudioCVT()
        SDL_BuildAudioCVT(self.cvt, AUDIO_S16SYS, 1, 1, AUDIO_S32SYS, 1, 1)

    def test_returns_none(self):
        "Returns None"
        self.cvt.len = 2
        self.cvt.buf = bytearray(self.cvt.len * self.cvt.len_mult)
        self.assertIs(SDL_ConvertAudio(self.cvt), None)

    def test_no_buf(self):
        "Raises ValueError if the SDL_AudioCVT has no buf"
        self.assertIs(self.cvt.buf, None)
        self.assertRaises(ValueError, SDL_ConvertAudio, self.cvt)

    def test_buf_invalid_size(self):
        "Raises BufferError if the SDL_AudioCVT buf has wrong size"
        self.cvt.len = 2
        self.cvt.buf = bytearray(1)
        self.assertRaises(BufferError, SDL_ConvertAudio, self.cvt)


class TestMixAudio(unittest.TestCase):
    "Tests for SDL_MixAudio()"

    def setUp(self):
        def callback(a, b, c):
            return None
        if not has_audio:
            raise unittest.SkipTest('no audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_CloseAudio()

    def test_returns_none(self):
        "Returns None"
        src = bytes(64)
        dst = bytearray(64)
        self.assertIsNone(SDL_MixAudio(dst, src, 64, 64))

    def test_src_invalid_size(self):
        "Raises BufferError if src has invalid size"
        src = bytes(63)
        dst = bytearray(64)
        self.assertRaises(BufferError, SDL_MixAudio, dst, src, 64, 64)

    def test_dst_invalid_size(self):
        "Raises BufferError if dst has invalid size"
        src = bytes(64)
        dst = bytearray(63)
        self.assertRaises(BufferError, SDL_MixAudio, dst, src, 64, 64)

    def test_dst_readonly(self):
        "Raises TypeError if dst is a readonly buffer"
        src = bytes(64)
        dst = bytes(64)
        self.assertRaises(TypeError, SDL_MixAudio, dst, src, 64, 64)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        src = bytes(64)
        dst = bytearray(64)
        self.assertRaises(TypeError, SDL_MixAudio, 42, src, 64, 64)
        self.assertRaises(TypeError, SDL_MixAudio, dst, 42, 64, 64)
        self.assertRaises(TypeError, SDL_MixAudio, dst, src, {}, 64)
        self.assertRaises(TypeError, SDL_MixAudio, dst, src, 64, {})


class TestMixAudioFormat(unittest.TestCase):
    "Tests for SDL_MixAudioFormat()"

    def test_returns_none(self):
        "Returns None"
        src = bytes(64)
        dst = bytearray(64)
        self.assertIsNone(SDL_MixAudioFormat(dst, src, AUDIO_S16SYS, 64, 64))

    def test_src_invalid_size(self):
        "Raises BufferError if src has invalid size"
        src = bytes(63)
        dst = bytearray(64)
        self.assertRaises(BufferError, SDL_MixAudioFormat, dst, src,
                          AUDIO_S16SYS, 64, 64)

    def test_dst_invalid_size(self):
        "Raises BufferError if dst has invalid size"
        src = bytes(64)
        dst = bytearray(63)
        self.assertRaises(BufferError, SDL_MixAudioFormat, dst, src,
                          AUDIO_S16SYS, 64, 64)

    def test_dst_readonly(self):
        "Raises TypeError if dst is a readonly buffer"
        src = bytes(64)
        dst = bytes(64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, dst, src,
                          AUDIO_S16SYS, 64, 64)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        src = bytes(64)
        dst = bytearray(64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, 42, src, AUDIO_S16SYS,
                          64, 64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, dst, 42, AUDIO_S16SYS,
                          64, 64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, dst, src, {}, 64, 64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, dst, src,
                          AUDIO_S16SYS, {}, 64)
        self.assertRaises(TypeError, SDL_MixAudioFormat, dst, src,
                          AUDIO_S16SYS, 64, {})


class TestLockAudio(unittest.TestCase):
    "Tests for SDL_LockAudio()"

    def setUp(self):
        def callback(x, y, z):
            return None
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_UnlockAudio()
        SDL_CloseAudio()

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_LockAudio())


class TestLockAudioDevice(unittest.TestCase):
    "Tests for SDL_LockAudioDevice()"

    def setUp(self):
        def callback(x, y, z):
            return None
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        self.dev = SDL_OpenAudioDevice(None, False, self.desired,
                                       self.obtained, 0)

    def tearDown(self):
        SDL_UnlockAudioDevice(self.dev)
        del self.dev

    def test_returns_none(self):
        "Returns None"
        self.assertIsNone(SDL_LockAudioDevice(self.dev))

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_LockAudioDevice, 42)


class TestUnlockAudio(unittest.TestCase):
    "Tests for SDL_UnlockAudio()"

    def setUp(self):
        def callback(x, y, z):
            return None
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_CloseAudio()

    def test_returns_none(self):
        "Returns None"
        SDL_LockAudio()
        self.assertIsNone(SDL_UnlockAudio())


class TestUnlockAudioDevice(unittest.TestCase):
    "Tests for SDL_UnlockAudioDevice()"

    def setUp(self):
        def callback(x, y, z):
            return None
        if not has_audio:
            raise unittest.SkipTest('No audio support')
        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        self.dev = SDL_OpenAudioDevice(None, False, self.desired,
                                       self.obtained, 0)

    def tearDown(self):
        del self.dev

    def test_returns_none(self):
        "Returns None"
        SDL_LockAudioDevice(self.dev)
        self.assertIsNone(SDL_UnlockAudioDevice(self.dev))

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, SDL_UnlockAudioDevice, 42)


class TestCloseAudio(unittest.TestCase):
    "Tests for SDL_CloseAudio()"

    def setUp(self):
        if not has_audio:
            raise unittest.SkipTest('No audio support')

        def callback(userdata, data, length):
            x = memoryview(data)
            for i in range(x.nbytes):
                x[i] = self.obtained.silence

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        SDL_OpenAudio(self.desired, self.obtained)

    def tearDown(self):
        SDL_CloseAudio()

    def test_returns_none(self):
        "Returns None"
        self.assertIs(SDL_CloseAudio(), None)

    def test_closed(self):
        "No-op when audio device has been closed"
        SDL_CloseAudio()
        SDL_CloseAudio()


class TestCloseAudioDevice(unittest.TestCase):
    """Tests for SDL_CloseAudioDevice()"""

    @classmethod
    def setUpClass(cls):
        if not has_audio:
            raise unittest.SkipTest('No audio support')

    def setUp(self):
        def callback(userdata, data, length):
            x = memoryview(data)
            for i in range(x.nbytes):
                x[i] = self.obtained.silence

        self.desired = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS,
                                     channels=1, samples=4096,
                                     callback=callback)
        self.obtained = SDL_AudioSpec()
        self.dev = SDL_OpenAudioDevice(None, False, self.desired,
                                       self.obtained, 0)

    def tearDown(self):
        del self.dev

    def test_closed(self):
        "Raises ValueError when the SDL_AudioDevice has been closed"
        SDL_CloseAudioDevice(self.dev)
        self.assertRaises(ValueError, SDL_CloseAudioDevice, self.dev)


class TestAudioSpecCreate(unittest.TestCase):
    "Tests PyCSDL2_AudioSpecCreate()"

    def test_returns_AudioSpec(self):
        x = _csdl2test.audio_spec()
        self.assertIs(type(x), SDL_AudioSpec)
        self.assertEqual(x.freq, 1)
        self.assertEqual(x.format, 2)
        self.assertEqual(x.channels, 3)
        self.assertEqual(x.silence, 4)
        self.assertEqual(x.samples, 5)
        self.assertEqual(x.size, 6)
        self.assertIsNotNone(x.callback)
        self.assertIsNotNone(x.userdata)


class TestAudioSpecPtr(unittest.TestCase):
    "Tests PyCSDL2_AudioSpecPtr()"

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        spec = SDL_AudioSpec()
        self.assertEqual(spec.freq, 0)
        _csdl2test.audio_spec_set_freq(spec)
        self.assertEqual(spec.freq, 42)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.audio_spec_set_freq, None)


class TestAudioDeviceCreate(unittest.TestCase):
    "Tests PyCSDL2_AudioDeviceCreate()"

    @classmethod
    def setUpClass(cls):
        if not has_audio:
            raise unittest.SkipTest('no audio support')

    def test_returns_AudioDevice(self):
        "Returns SDL_AudioDevice"
        x = _csdl2test.audio_device()
        self.assertIs(type(x), SDL_AudioDevice)


class TestAudioDeviceID(unittest.TestCase):
    "Tests PyCSDL2_AudioDeviceID()"

    @classmethod
    def setUpClass(cls):
        if not has_audio:
            raise unittest.SkipTest('no audio support')

    def setUp(self):
        self.cv = threading.Condition()
        self.called = False

        def callback(a, b, c):
            with self.cv:
                self.called = True
                self.cv.notify()

        spec = SDL_AudioSpec(freq=44100, format=AUDIO_S16SYS, channels=1,
                             samples=4096, callback=callback)
        self.dev = SDL_OpenAudioDevice(None, False, spec, None, 0)

    def tearDown(self):
        del self.dev

    def test_converter(self):
        "Works as a converter with PyArg_ParseTuple()"
        _csdl2test.audio_device_unpause(self.dev)
        with self.cv:
            self.cv.wait_for(lambda: self.called, 3)
        self.assertTrue(self.called)

    def test_closed(self):
        "Raises ValueError when the SDL_AudioDevice has been closed"
        SDL_CloseAudioDevice(self.dev)
        self.assertRaises(ValueError, _csdl2test.audio_device_unpause,
                          self.dev)

    def test_invalid_type(self):
        "Raises TypeError on invalid type"
        self.assertRaises(TypeError, _csdl2test.audio_device_unpause, 42)


if __name__ == '__main__':
    unittest.main()
