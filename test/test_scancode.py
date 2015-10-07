"""test bindings in src/scancode.h"""
import distutils.util
import os.path
import sys
import unittest


tests_dir = os.path.dirname(os.path.abspath(__file__))


if __name__ == '__main__':
    plat_specifier = 'lib.{0}-{1}'.format(distutils.util.get_platform(),
                                          sys.version[0:3])
    sys.path.insert(0, os.path.join(tests_dir, '..', 'build', plat_specifier))


from csdl2 import *  # noqa


class TestScancodeConstants(unittest.TestCase):
    "Test value of constants defined in SDL_scancode.h"

    def test_SDL_SCANCODE_UNKNOWN(self):
        self.assertEqual(SDL_SCANCODE_UNKNOWN, 0)

    def test_SDL_SCANCODE_A(self):
        self.assertEqual(SDL_SCANCODE_A, 4)

    def test_SDL_SCANCODE_B(self):
        self.assertEqual(SDL_SCANCODE_B, 5)

    def test_SDL_SCANCODE_C(self):
        self.assertEqual(SDL_SCANCODE_C, 6)

    def test_SDL_SCANCODE_D(self):
        self.assertEqual(SDL_SCANCODE_D, 7)

    def test_SDL_SCANCODE_E(self):
        self.assertEqual(SDL_SCANCODE_E, 8)

    def test_SDL_SCANCODE_F(self):
        self.assertEqual(SDL_SCANCODE_F, 9)

    def test_SDL_SCANCODE_G(self):
        self.assertEqual(SDL_SCANCODE_G, 10)

    def test_SDL_SCANCODE_H(self):
        self.assertEqual(SDL_SCANCODE_H, 11)

    def test_SDL_SCANCODE_I(self):
        self.assertEqual(SDL_SCANCODE_I, 12)

    def test_SDL_SCANCODE_J(self):
        self.assertEqual(SDL_SCANCODE_J, 13)

    def test_SDL_SCANCODE_K(self):
        self.assertEqual(SDL_SCANCODE_K, 14)

    def test_SDL_SCANCODE_L(self):
        self.assertEqual(SDL_SCANCODE_L, 15)

    def test_SDL_SCANCODE_M(self):
        self.assertEqual(SDL_SCANCODE_M, 16)

    def test_SDL_SCANCODE_N(self):
        self.assertEqual(SDL_SCANCODE_N, 17)

    def test_SDL_SCANCODE_O(self):
        self.assertEqual(SDL_SCANCODE_O, 18)

    def test_SDL_SCANCODE_P(self):
        self.assertEqual(SDL_SCANCODE_P, 19)

    def test_SDL_SCANCODE_Q(self):
        self.assertEqual(SDL_SCANCODE_Q, 20)

    def test_SDL_SCANCODE_R(self):
        self.assertEqual(SDL_SCANCODE_R, 21)

    def test_SDL_SCANCODE_S(self):
        self.assertEqual(SDL_SCANCODE_S, 22)

    def test_SDL_SCANCODE_T(self):
        self.assertEqual(SDL_SCANCODE_T, 23)

    def test_SDL_SCANCODE_U(self):
        self.assertEqual(SDL_SCANCODE_U, 24)

    def test_SDL_SCANCODE_V(self):
        self.assertEqual(SDL_SCANCODE_V, 25)

    def test_SDL_SCANCODE_W(self):
        self.assertEqual(SDL_SCANCODE_W, 26)

    def test_SDL_SCANCODE_X(self):
        self.assertEqual(SDL_SCANCODE_X, 27)

    def test_SDL_SCANCODE_Y(self):
        self.assertEqual(SDL_SCANCODE_Y, 28)

    def test_SDL_SCANCODE_Z(self):
        self.assertEqual(SDL_SCANCODE_Z, 29)

    def test_SDL_SCANCODE_1(self):
        self.assertEqual(SDL_SCANCODE_1, 30)

    def test_SDL_SCANCODE_2(self):
        self.assertEqual(SDL_SCANCODE_2, 31)

    def test_SDL_SCANCODE_3(self):
        self.assertEqual(SDL_SCANCODE_3, 32)

    def test_SDL_SCANCODE_4(self):
        self.assertEqual(SDL_SCANCODE_4, 33)

    def test_SDL_SCANCODE_5(self):
        self.assertEqual(SDL_SCANCODE_5, 34)

    def test_SDL_SCANCODE_6(self):
        self.assertEqual(SDL_SCANCODE_6, 35)

    def test_SDL_SCANCODE_7(self):
        self.assertEqual(SDL_SCANCODE_7, 36)

    def test_SDL_SCANCODE_8(self):
        self.assertEqual(SDL_SCANCODE_8, 37)

    def test_SDL_SCANCODE_9(self):
        self.assertEqual(SDL_SCANCODE_9, 38)

    def test_SDL_SCANCODE_0(self):
        self.assertEqual(SDL_SCANCODE_0, 39)

    def test_SDL_SCANCODE_RETURN(self):
        self.assertEqual(SDL_SCANCODE_RETURN, 40)

    def test_SDL_SCANCODE_ESCAPE(self):
        self.assertEqual(SDL_SCANCODE_ESCAPE, 41)

    def test_SDL_SCANCODE_BACKSPACE(self):
        self.assertEqual(SDL_SCANCODE_BACKSPACE, 42)

    def test_SDL_SCANCODE_TAB(self):
        self.assertEqual(SDL_SCANCODE_TAB, 43)

    def test_SDL_SCANCODE_SPACE(self):
        self.assertEqual(SDL_SCANCODE_SPACE, 44)

    def test_SDL_SCANCODE_MINUS(self):
        self.assertEqual(SDL_SCANCODE_MINUS, 45)

    def test_SDL_SCANCODE_EQUALS(self):
        self.assertEqual(SDL_SCANCODE_EQUALS, 46)

    def test_SDL_SCANCODE_LEFTBRACKET(self):
        self.assertEqual(SDL_SCANCODE_LEFTBRACKET, 47)

    def test_SDL_SCANCODE_RIGHTBRACKET(self):
        self.assertEqual(SDL_SCANCODE_RIGHTBRACKET, 48)

    def test_SDL_SCANCODE_BACKSLASH(self):
        self.assertEqual(SDL_SCANCODE_BACKSLASH, 49)

    def test_SDL_SCANCODE_NONUSHASH(self):
        self.assertEqual(SDL_SCANCODE_NONUSHASH, 50)

    def test_SDL_SCANCODE_SEMICOLON(self):
        self.assertEqual(SDL_SCANCODE_SEMICOLON, 51)

    def test_SDL_SCANCODE_APOSTROPHE(self):
        self.assertEqual(SDL_SCANCODE_APOSTROPHE, 52)

    def test_SDL_SCANCODE_GRAVE(self):
        self.assertEqual(SDL_SCANCODE_GRAVE, 53)

    def test_SDL_SCANCODE_COMMA(self):
        self.assertEqual(SDL_SCANCODE_COMMA, 54)

    def test_SDL_SCANCODE_PERIOD(self):
        self.assertEqual(SDL_SCANCODE_PERIOD, 55)

    def test_SDL_SCANCODE_SLASH(self):
        self.assertEqual(SDL_SCANCODE_SLASH, 56)

    def test_SDL_SCANCODE_CAPSLOCK(self):
        self.assertEqual(SDL_SCANCODE_CAPSLOCK, 57)

    def test_SDL_SCANCODE_F1(self):
        self.assertEqual(SDL_SCANCODE_F1, 58)

    def test_SDL_SCANCODE_F2(self):
        self.assertEqual(SDL_SCANCODE_F2, 59)

    def test_SDL_SCANCODE_F3(self):
        self.assertEqual(SDL_SCANCODE_F3, 60)

    def test_SDL_SCANCODE_F4(self):
        self.assertEqual(SDL_SCANCODE_F4, 61)

    def test_SDL_SCANCODE_F5(self):
        self.assertEqual(SDL_SCANCODE_F5, 62)

    def test_SDL_SCANCODE_F6(self):
        self.assertEqual(SDL_SCANCODE_F6, 63)

    def test_SDL_SCANCODE_F7(self):
        self.assertEqual(SDL_SCANCODE_F7, 64)

    def test_SDL_SCANCODE_F8(self):
        self.assertEqual(SDL_SCANCODE_F8, 65)

    def test_SDL_SCANCODE_F9(self):
        self.assertEqual(SDL_SCANCODE_F9, 66)

    def test_SDL_SCANCODE_F10(self):
        self.assertEqual(SDL_SCANCODE_F10, 67)

    def test_SDL_SCANCODE_F11(self):
        self.assertEqual(SDL_SCANCODE_F11, 68)

    def test_SDL_SCANCODE_F12(self):
        self.assertEqual(SDL_SCANCODE_F12, 69)

    def test_SDL_SCANCODE_PRINTSCREEN(self):
        self.assertEqual(SDL_SCANCODE_PRINTSCREEN, 70)

    def test_SDL_SCANCODE_SCROLLLOCK(self):
        self.assertEqual(SDL_SCANCODE_SCROLLLOCK, 71)

    def test_SDL_SCANCODE_PAUSE(self):
        self.assertEqual(SDL_SCANCODE_PAUSE, 72)

    def test_SDL_SCANCODE_INSERT(self):
        self.assertEqual(SDL_SCANCODE_INSERT, 73)

    def test_SDL_SCANCODE_HOME(self):
        self.assertEqual(SDL_SCANCODE_HOME, 74)

    def test_SDL_SCANCODE_PAGEUP(self):
        self.assertEqual(SDL_SCANCODE_PAGEUP, 75)

    def test_SDL_SCANCODE_DELETE(self):
        self.assertEqual(SDL_SCANCODE_DELETE, 76)

    def test_SDL_SCANCODE_END(self):
        self.assertEqual(SDL_SCANCODE_END, 77)

    def test_SDL_SCANCODE_PAGEDOWN(self):
        self.assertEqual(SDL_SCANCODE_PAGEDOWN, 78)

    def test_SDL_SCANCODE_RIGHT(self):
        self.assertEqual(SDL_SCANCODE_RIGHT, 79)

    def test_SDL_SCANCODE_LEFT(self):
        self.assertEqual(SDL_SCANCODE_LEFT, 80)

    def test_SDL_SCANCODE_DOWN(self):
        self.assertEqual(SDL_SCANCODE_DOWN, 81)

    def test_SDL_SCANCODE_UP(self):
        self.assertEqual(SDL_SCANCODE_UP, 82)

    def test_SDL_SCANCODE_NUMLOCKCLEAR(self):
        self.assertEqual(SDL_SCANCODE_NUMLOCKCLEAR, 83)

    def test_SDL_SCANCODE_KP_DIVIDE(self):
        self.assertEqual(SDL_SCANCODE_KP_DIVIDE, 84)

    def test_SDL_SCANCODE_KP_MULTIPLY(self):
        self.assertEqual(SDL_SCANCODE_KP_MULTIPLY, 85)

    def test_SDL_SCANCODE_KP_MINUS(self):
        self.assertEqual(SDL_SCANCODE_KP_MINUS, 86)

    def test_SDL_SCANCODE_KP_PLUS(self):
        self.assertEqual(SDL_SCANCODE_KP_PLUS, 87)

    def test_SDL_SCANCODE_KP_ENTER(self):
        self.assertEqual(SDL_SCANCODE_KP_ENTER, 88)

    def test_SDL_SCANCODE_KP_1(self):
        self.assertEqual(SDL_SCANCODE_KP_1, 89)

    def test_SDL_SCANCODE_KP_2(self):
        self.assertEqual(SDL_SCANCODE_KP_2, 90)

    def test_SDL_SCANCODE_KP_3(self):
        self.assertEqual(SDL_SCANCODE_KP_3, 91)

    def test_SDL_SCANCODE_KP_4(self):
        self.assertEqual(SDL_SCANCODE_KP_4, 92)

    def test_SDL_SCANCODE_KP_5(self):
        self.assertEqual(SDL_SCANCODE_KP_5, 93)

    def test_SDL_SCANCODE_KP_6(self):
        self.assertEqual(SDL_SCANCODE_KP_6, 94)

    def test_SDL_SCANCODE_KP_7(self):
        self.assertEqual(SDL_SCANCODE_KP_7, 95)

    def test_SDL_SCANCODE_KP_8(self):
        self.assertEqual(SDL_SCANCODE_KP_8, 96)

    def test_SDL_SCANCODE_KP_9(self):
        self.assertEqual(SDL_SCANCODE_KP_9, 97)

    def test_SDL_SCANCODE_KP_0(self):
        self.assertEqual(SDL_SCANCODE_KP_0, 98)

    def test_SDL_SCANCODE_KP_PERIOD(self):
        self.assertEqual(SDL_SCANCODE_KP_PERIOD, 99)

    def test_SDL_SCANCODE_NONUSBACKSLASH(self):
        self.assertEqual(SDL_SCANCODE_NONUSBACKSLASH, 100)

    def test_SDL_SCANCODE_APPLICATION(self):
        self.assertEqual(SDL_SCANCODE_APPLICATION, 101)

    def test_SDL_SCANCODE_POWER(self):
        self.assertEqual(SDL_SCANCODE_POWER, 102)

    def test_SDL_SCANCODE_KP_EQUALS(self):
        self.assertEqual(SDL_SCANCODE_KP_EQUALS, 103)

    def test_SDL_SCANCODE_F13(self):
        self.assertEqual(SDL_SCANCODE_F13, 104)

    def test_SDL_SCANCODE_F14(self):
        self.assertEqual(SDL_SCANCODE_F14, 105)

    def test_SDL_SCANCODE_F15(self):
        self.assertEqual(SDL_SCANCODE_F15, 106)

    def test_SDL_SCANCODE_F16(self):
        self.assertEqual(SDL_SCANCODE_F16, 107)

    def test_SDL_SCANCODE_F17(self):
        self.assertEqual(SDL_SCANCODE_F17, 108)

    def test_SDL_SCANCODE_F18(self):
        self.assertEqual(SDL_SCANCODE_F18, 109)

    def test_SDL_SCANCODE_F19(self):
        self.assertEqual(SDL_SCANCODE_F19, 110)

    def test_SDL_SCANCODE_F20(self):
        self.assertEqual(SDL_SCANCODE_F20, 111)

    def test_SDL_SCANCODE_F21(self):
        self.assertEqual(SDL_SCANCODE_F21, 112)

    def test_SDL_SCANCODE_F22(self):
        self.assertEqual(SDL_SCANCODE_F22, 113)

    def test_SDL_SCANCODE_F23(self):
        self.assertEqual(SDL_SCANCODE_F23, 114)

    def test_SDL_SCANCODE_F24(self):
        self.assertEqual(SDL_SCANCODE_F24, 115)

    def test_SDL_SCANCODE_EXECUTE(self):
        self.assertEqual(SDL_SCANCODE_EXECUTE, 116)

    def test_SDL_SCANCODE_HELP(self):
        self.assertEqual(SDL_SCANCODE_HELP, 117)

    def test_SDL_SCANCODE_MENU(self):
        self.assertEqual(SDL_SCANCODE_MENU, 118)

    def test_SDL_SCANCODE_SELECT(self):
        self.assertEqual(SDL_SCANCODE_SELECT, 119)

    def test_SDL_SCANCODE_STOP(self):
        self.assertEqual(SDL_SCANCODE_STOP, 120)

    def test_SDL_SCANCODE_AGAIN(self):
        self.assertEqual(SDL_SCANCODE_AGAIN, 121)

    def test_SDL_SCANCODE_UNDO(self):
        self.assertEqual(SDL_SCANCODE_UNDO, 122)

    def test_SDL_SCANCODE_CUT(self):
        self.assertEqual(SDL_SCANCODE_CUT, 123)

    def test_SDL_SCANCODE_COPY(self):
        self.assertEqual(SDL_SCANCODE_COPY, 124)

    def test_SDL_SCANCODE_PASTE(self):
        self.assertEqual(SDL_SCANCODE_PASTE, 125)

    def test_SDL_SCANCODE_FIND(self):
        self.assertEqual(SDL_SCANCODE_FIND, 126)

    def test_SDL_SCANCODE_MUTE(self):
        self.assertEqual(SDL_SCANCODE_MUTE, 127)

    def test_SDL_SCANCODE_VOLUMEUP(self):
        self.assertEqual(SDL_SCANCODE_VOLUMEUP, 128)

    def test_SDL_SCANCODE_VOLUMEDOWN(self):
        self.assertEqual(SDL_SCANCODE_VOLUMEDOWN, 129)

    def test_SDL_SCANCODE_KP_COMMA(self):
        self.assertEqual(SDL_SCANCODE_KP_COMMA, 133)

    def test_SDL_SCANCODE_KP_EQUALSAS400(self):
        self.assertEqual(SDL_SCANCODE_KP_EQUALSAS400, 134)

    def test_SDL_SCANCODE_INTERNATIONAL1(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL1, 135)

    def test_SDL_SCANCODE_INTERNATIONAL2(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL2, 136)

    def test_SDL_SCANCODE_INTERNATIONAL3(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL3, 137)

    def test_SDL_SCANCODE_INTERNATIONAL4(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL4, 138)

    def test_SDL_SCANCODE_INTERNATIONAL5(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL5, 139)

    def test_SDL_SCANCODE_INTERNATIONAL6(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL6, 140)

    def test_SDL_SCANCODE_INTERNATIONAL7(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL7, 141)

    def test_SDL_SCANCODE_INTERNATIONAL8(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL8, 142)

    def test_SDL_SCANCODE_INTERNATIONAL9(self):
        self.assertEqual(SDL_SCANCODE_INTERNATIONAL9, 143)

    def test_SDL_SCANCODE_LANG1(self):
        self.assertEqual(SDL_SCANCODE_LANG1, 144)

    def test_SDL_SCANCODE_LANG2(self):
        self.assertEqual(SDL_SCANCODE_LANG2, 145)

    def test_SDL_SCANCODE_LANG3(self):
        self.assertEqual(SDL_SCANCODE_LANG3, 146)

    def test_SDL_SCANCODE_LANG4(self):
        self.assertEqual(SDL_SCANCODE_LANG4, 147)

    def test_SDL_SCANCODE_LANG5(self):
        self.assertEqual(SDL_SCANCODE_LANG5, 148)

    def test_SDL_SCANCODE_LANG6(self):
        self.assertEqual(SDL_SCANCODE_LANG6, 149)

    def test_SDL_SCANCODE_LANG7(self):
        self.assertEqual(SDL_SCANCODE_LANG7, 150)

    def test_SDL_SCANCODE_LANG8(self):
        self.assertEqual(SDL_SCANCODE_LANG8, 151)

    def test_SDL_SCANCODE_LANG9(self):
        self.assertEqual(SDL_SCANCODE_LANG9, 152)

    def test_SDL_SCANCODE_ALTERASE(self):
        self.assertEqual(SDL_SCANCODE_ALTERASE, 153)

    def test_SDL_SCANCODE_SYSREQ(self):
        self.assertEqual(SDL_SCANCODE_SYSREQ, 154)

    def test_SDL_SCANCODE_CANCEL(self):
        self.assertEqual(SDL_SCANCODE_CANCEL, 155)

    def test_SDL_SCANCODE_CLEAR(self):
        self.assertEqual(SDL_SCANCODE_CLEAR, 156)

    def test_SDL_SCANCODE_PRIOR(self):
        self.assertEqual(SDL_SCANCODE_PRIOR, 157)

    def test_SDL_SCANCODE_RETURN2(self):
        self.assertEqual(SDL_SCANCODE_RETURN2, 158)

    def test_SDL_SCANCODE_SEPARATOR(self):
        self.assertEqual(SDL_SCANCODE_SEPARATOR, 159)

    def test_SDL_SCANCODE_OUT(self):
        self.assertEqual(SDL_SCANCODE_OUT, 160)

    def test_SDL_SCANCODE_OPER(self):
        self.assertEqual(SDL_SCANCODE_OPER, 161)

    def test_SDL_SCANCODE_CLEARAGAIN(self):
        self.assertEqual(SDL_SCANCODE_CLEARAGAIN, 162)

    def test_SDL_SCANCODE_CRSEL(self):
        self.assertEqual(SDL_SCANCODE_CRSEL, 163)

    def test_SDL_SCANCODE_EXSEL(self):
        self.assertEqual(SDL_SCANCODE_EXSEL, 164)

    def test_SDL_SCANCODE_KP_00(self):
        self.assertEqual(SDL_SCANCODE_KP_00, 176)

    def test_SDL_SCANCODE_KP_000(self):
        self.assertEqual(SDL_SCANCODE_KP_000, 177)

    def test_SDL_SCANCODE_THOUSANDSSEPARATOR(self):
        self.assertEqual(SDL_SCANCODE_THOUSANDSSEPARATOR, 178)

    def test_SDL_SCANCODE_DECIMALSEPARATOR(self):
        self.assertEqual(SDL_SCANCODE_DECIMALSEPARATOR, 179)

    def test_SDL_SCANCODE_CURRENCYUNIT(self):
        self.assertEqual(SDL_SCANCODE_CURRENCYUNIT, 180)

    def test_SDL_SCANCODE_CURRENCYSUBUNIT(self):
        self.assertEqual(SDL_SCANCODE_CURRENCYSUBUNIT, 181)

    def test_SDL_SCANCODE_KP_LEFTPAREN(self):
        self.assertEqual(SDL_SCANCODE_KP_LEFTPAREN, 182)

    def test_SDL_SCANCODE_KP_RIGHTPAREN(self):
        self.assertEqual(SDL_SCANCODE_KP_RIGHTPAREN, 183)

    def test_SDL_SCANCODE_KP_LEFTBRACE(self):
        self.assertEqual(SDL_SCANCODE_KP_LEFTBRACE, 184)

    def test_SDL_SCANCODE_KP_RIGHTBRACE(self):
        self.assertEqual(SDL_SCANCODE_KP_RIGHTBRACE, 185)

    def test_SDL_SCANCODE_KP_TAB(self):
        self.assertEqual(SDL_SCANCODE_KP_TAB, 186)

    def test_SDL_SCANCODE_KP_BACKSPACE(self):
        self.assertEqual(SDL_SCANCODE_KP_BACKSPACE, 187)

    def test_SDL_SCANCODE_KP_A(self):
        self.assertEqual(SDL_SCANCODE_KP_A, 188)

    def test_SDL_SCANCODE_KP_B(self):
        self.assertEqual(SDL_SCANCODE_KP_B, 189)

    def test_SDL_SCANCODE_KP_C(self):
        self.assertEqual(SDL_SCANCODE_KP_C, 190)

    def test_SDL_SCANCODE_KP_D(self):
        self.assertEqual(SDL_SCANCODE_KP_D, 191)

    def test_SDL_SCANCODE_KP_E(self):
        self.assertEqual(SDL_SCANCODE_KP_E, 192)

    def test_SDL_SCANCODE_KP_F(self):
        self.assertEqual(SDL_SCANCODE_KP_F, 193)

    def test_SDL_SCANCODE_KP_XOR(self):
        self.assertEqual(SDL_SCANCODE_KP_XOR, 194)

    def test_SDL_SCANCODE_KP_POWER(self):
        self.assertEqual(SDL_SCANCODE_KP_POWER, 195)

    def test_SDL_SCANCODE_KP_PERCENT(self):
        self.assertEqual(SDL_SCANCODE_KP_PERCENT, 196)

    def test_SDL_SCANCODE_KP_LESS(self):
        self.assertEqual(SDL_SCANCODE_KP_LESS, 197)

    def test_SDL_SCANCODE_KP_GREATER(self):
        self.assertEqual(SDL_SCANCODE_KP_GREATER, 198)

    def test_SDL_SCANCODE_KP_AMPERSAND(self):
        self.assertEqual(SDL_SCANCODE_KP_AMPERSAND, 199)

    def test_SDL_SCANCODE_KP_DBLAMPERSAND(self):
        self.assertEqual(SDL_SCANCODE_KP_DBLAMPERSAND, 200)

    def test_SDL_SCANCODE_KP_VERTICALBAR(self):
        self.assertEqual(SDL_SCANCODE_KP_VERTICALBAR, 201)

    def test_SDL_SCANCODE_KP_DBLVERTICALBAR(self):
        self.assertEqual(SDL_SCANCODE_KP_DBLVERTICALBAR, 202)

    def test_SDL_SCANCODE_KP_COLON(self):
        self.assertEqual(SDL_SCANCODE_KP_COLON, 203)

    def test_SDL_SCANCODE_KP_HASH(self):
        self.assertEqual(SDL_SCANCODE_KP_HASH, 204)

    def test_SDL_SCANCODE_KP_SPACE(self):
        self.assertEqual(SDL_SCANCODE_KP_SPACE, 205)

    def test_SDL_SCANCODE_KP_AT(self):
        self.assertEqual(SDL_SCANCODE_KP_AT, 206)

    def test_SDL_SCANCODE_KP_EXCLAM(self):
        self.assertEqual(SDL_SCANCODE_KP_EXCLAM, 207)

    def test_SDL_SCANCODE_KP_MEMSTORE(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMSTORE, 208)

    def test_SDL_SCANCODE_KP_MEMRECALL(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMRECALL, 209)

    def test_SDL_SCANCODE_KP_MEMCLEAR(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMCLEAR, 210)

    def test_SDL_SCANCODE_KP_MEMADD(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMADD, 211)

    def test_SDL_SCANCODE_KP_MEMSUBTRACT(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMSUBTRACT, 212)

    def test_SDL_SCANCODE_KP_MEMMULTIPLY(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMMULTIPLY, 213)

    def test_SDL_SCANCODE_KP_MEMDIVIDE(self):
        self.assertEqual(SDL_SCANCODE_KP_MEMDIVIDE, 214)

    def test_SDL_SCANCODE_KP_PLUSMINUS(self):
        self.assertEqual(SDL_SCANCODE_KP_PLUSMINUS, 215)

    def test_SDL_SCANCODE_KP_CLEAR(self):
        self.assertEqual(SDL_SCANCODE_KP_CLEAR, 216)

    def test_SDL_SCANCODE_KP_CLEARENTRY(self):
        self.assertEqual(SDL_SCANCODE_KP_CLEARENTRY, 217)

    def test_SDL_SCANCODE_KP_BINARY(self):
        self.assertEqual(SDL_SCANCODE_KP_BINARY, 218)

    def test_SDL_SCANCODE_KP_OCTAL(self):
        self.assertEqual(SDL_SCANCODE_KP_OCTAL, 219)

    def test_SDL_SCANCODE_KP_DECIMAL(self):
        self.assertEqual(SDL_SCANCODE_KP_DECIMAL, 220)

    def test_SDL_SCANCODE_KP_HEXADECIMAL(self):
        self.assertEqual(SDL_SCANCODE_KP_HEXADECIMAL, 221)

    def test_SDL_SCANCODE_LCTRL(self):
        self.assertEqual(SDL_SCANCODE_LCTRL, 224)

    def test_SDL_SCANCODE_LSHIFT(self):
        self.assertEqual(SDL_SCANCODE_LSHIFT, 225)

    def test_SDL_SCANCODE_LALT(self):
        self.assertEqual(SDL_SCANCODE_LALT, 226)

    def test_SDL_SCANCODE_LGUI(self):
        self.assertEqual(SDL_SCANCODE_LGUI, 227)

    def test_SDL_SCANCODE_RCTRL(self):
        self.assertEqual(SDL_SCANCODE_RCTRL, 228)

    def test_SDL_SCANCODE_RSHIFT(self):
        self.assertEqual(SDL_SCANCODE_RSHIFT, 229)

    def test_SDL_SCANCODE_RALT(self):
        self.assertEqual(SDL_SCANCODE_RALT, 230)

    def test_SDL_SCANCODE_RGUI(self):
        self.assertEqual(SDL_SCANCODE_RGUI, 231)

    def test_SDL_SCANCODE_MODE(self):
        self.assertEqual(SDL_SCANCODE_MODE, 257)

    def test_SDL_SCANCODE_AUDIONEXT(self):
        self.assertEqual(SDL_SCANCODE_AUDIONEXT, 258)

    def test_SDL_SCANCODE_AUDIOPREV(self):
        self.assertEqual(SDL_SCANCODE_AUDIOPREV, 259)

    def test_SDL_SCANCODE_AUDIOSTOP(self):
        self.assertEqual(SDL_SCANCODE_AUDIOSTOP, 260)

    def test_SDL_SCANCODE_AUDIOPLAY(self):
        self.assertEqual(SDL_SCANCODE_AUDIOPLAY, 261)

    def test_SDL_SCANCODE_AUDIOMUTE(self):
        self.assertEqual(SDL_SCANCODE_AUDIOMUTE, 262)

    def test_SDL_SCANCODE_MEDIASELECT(self):
        self.assertEqual(SDL_SCANCODE_MEDIASELECT, 263)

    def test_SDL_SCANCODE_WWW(self):
        self.assertEqual(SDL_SCANCODE_WWW, 264)

    def test_SDL_SCANCODE_MAIL(self):
        self.assertEqual(SDL_SCANCODE_MAIL, 265)

    def test_SDL_SCANCODE_CALCULATOR(self):
        self.assertEqual(SDL_SCANCODE_CALCULATOR, 266)

    def test_SDL_SCANCODE_COMPUTER(self):
        self.assertEqual(SDL_SCANCODE_COMPUTER, 267)

    def test_SDL_SCANCODE_AC_SEARCH(self):
        self.assertEqual(SDL_SCANCODE_AC_SEARCH, 268)

    def test_SDL_SCANCODE_AC_HOME(self):
        self.assertEqual(SDL_SCANCODE_AC_HOME, 269)

    def test_SDL_SCANCODE_AC_BACK(self):
        self.assertEqual(SDL_SCANCODE_AC_BACK, 270)

    def test_SDL_SCANCODE_AC_FORWARD(self):
        self.assertEqual(SDL_SCANCODE_AC_FORWARD, 271)

    def test_SDL_SCANCODE_AC_STOP(self):
        self.assertEqual(SDL_SCANCODE_AC_STOP, 272)

    def test_SDL_SCANCODE_AC_REFRESH(self):
        self.assertEqual(SDL_SCANCODE_AC_REFRESH, 273)

    def test_SDL_SCANCODE_AC_BOOKMARKS(self):
        self.assertEqual(SDL_SCANCODE_AC_BOOKMARKS, 274)

    def test_SDL_SCANCODE_BRIGHTNESSDOWN(self):
        self.assertEqual(SDL_SCANCODE_BRIGHTNESSDOWN, 275)

    def test_SDL_SCANCODE_BRIGHTNESSUP(self):
        self.assertEqual(SDL_SCANCODE_BRIGHTNESSUP, 276)

    def test_SDL_SCANCODE_DISPLAYSWITCH(self):
        self.assertEqual(SDL_SCANCODE_DISPLAYSWITCH, 277)

    def test_SDL_SCANCODE_KBDILLUMTOGGLE(self):
        self.assertEqual(SDL_SCANCODE_KBDILLUMTOGGLE, 278)

    def test_SDL_SCANCODE_KBDILLUMDOWN(self):
        self.assertEqual(SDL_SCANCODE_KBDILLUMDOWN, 279)

    def test_SDL_SCANCODE_KBDILLUMUP(self):
        self.assertEqual(SDL_SCANCODE_KBDILLUMUP, 280)

    def test_SDL_SCANCODE_EJECT(self):
        self.assertEqual(SDL_SCANCODE_EJECT, 281)

    def test_SDL_SCANCODE_SLEEP(self):
        self.assertEqual(SDL_SCANCODE_SLEEP, 282)

    def test_SDL_SCANCODE_APP1(self):
        self.assertEqual(SDL_SCANCODE_APP1, 283)

    def test_SDL_SCANCODE_APP2(self):
        self.assertEqual(SDL_SCANCODE_APP2, 284)

    def test_SDL_NUM_SCANCODES(self):
        self.assertEqual(SDL_NUM_SCANCODES, 512)


if __name__ == '__main__':
    unittest.main()
