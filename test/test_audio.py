"""test bindings in src/audio.h"""
import distutils.util
import os.path
import sys
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *


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
        callback = lambda: None
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
        callback = lambda: None
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
        callback = lambda: None
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
        f = lambda x, y, z: None
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


if __name__ == '__main__':
    unittest.main()
