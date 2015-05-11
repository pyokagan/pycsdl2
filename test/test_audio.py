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


if __name__ == '__main__':
    unittest.main()
