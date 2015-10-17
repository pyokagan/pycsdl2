"""test bindings in src/keycode.h"""
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


class TestKeycodeConstants(unittest.TestCase):
    "Test value of constants defined in SDL_keycode.h"

    def test_SDLK_SCANCODE_MASK(self):
        self.assertIs(type(SDLK_SCANCODE_MASK), int)
        self.assertEqual(SDLK_SCANCODE_MASK, 1 << 30)

    def test_SDLK_UNKNOWN(self):
        self.assertIs(type(SDLK_UNKNOWN), int)
        self.assertEqual(SDLK_UNKNOWN, 0)

    def test_SDLK_RETURN(self):
        self.assertIs(type(SDLK_RETURN), int)
        self.assertEqual(SDLK_RETURN, ord('\r'))

    def test_SDLK_ESCAPE(self):
        self.assertIs(type(SDLK_ESCAPE), int)
        self.assertEqual(SDLK_ESCAPE, ord('\033'))

    def test_SDLK_BACKSPACE(self):
        self.assertIs(type(SDLK_BACKSPACE), int)
        self.assertEqual(SDLK_BACKSPACE, ord('\b'))

    def test_SDLK_TAB(self):
        self.assertIs(type(SDLK_TAB), int)
        self.assertEqual(SDLK_TAB, ord('\t'))

    def test_SDLK_SPACE(self):
        self.assertIs(type(SDLK_SPACE), int)
        self.assertEqual(SDLK_SPACE, ord(' '))

    def test_SDLK_EXCLAIM(self):
        self.assertIs(type(SDLK_EXCLAIM), int)
        self.assertEqual(SDLK_EXCLAIM, ord('!'))

    def test_SDLK_QUOTEDBL(self):
        self.assertIs(type(SDLK_QUOTEDBL), int)
        self.assertEqual(SDLK_QUOTEDBL, ord('"'))

    def test_SDLK_HASH(self):
        self.assertIs(type(SDLK_HASH), int)
        self.assertEqual(SDLK_HASH, ord('#'))

    def test_SDLK_PERCENT(self):
        self.assertIs(type(SDLK_PERCENT), int)
        self.assertEqual(SDLK_PERCENT, ord('%'))

    def test_SDLK_DOLLAR(self):
        self.assertIs(type(SDLK_DOLLAR), int)
        self.assertEqual(SDLK_DOLLAR, ord('$'))

    def test_SDLK_AMPERSAND(self):
        self.assertIs(type(SDLK_AMPERSAND), int)
        self.assertEqual(SDLK_AMPERSAND, ord('&'))

    def test_SDLK_QUOTE(self):
        self.assertIs(type(SDLK_QUOTE), int)
        self.assertEqual(SDLK_QUOTE, ord("'"))

    def test_SDLK_LEFTPAREN(self):
        self.assertIs(type(SDLK_LEFTPAREN), int)
        self.assertEqual(SDLK_LEFTPAREN, ord('('))

    def test_SDLK_RIGHTPAREN(self):
        self.assertIs(type(SDLK_RIGHTPAREN), int)
        self.assertEqual(SDLK_RIGHTPAREN, ord(')'))

    def test_SDLK_ASTERISK(self):
        self.assertIs(type(SDLK_ASTERISK), int)
        self.assertEqual(SDLK_ASTERISK, ord('*'))

    def test_SDLK_PLUS(self):
        self.assertIs(type(SDLK_PLUS), int)
        self.assertEqual(SDLK_PLUS, ord('+'))

    def test_SDLK_COMMA(self):
        self.assertIs(type(SDLK_COMMA), int)
        self.assertEqual(SDLK_COMMA, ord(','))

    def test_SDLK_MINUS(self):
        self.assertIs(type(SDLK_MINUS), int)
        self.assertEqual(SDLK_MINUS, ord('-'))

    def test_SDLK_PERIOD(self):
        self.assertIs(type(SDLK_PERIOD), int)
        self.assertEqual(SDLK_PERIOD, ord('.'))

    def test_SDLK_SLASH(self):
        self.assertIs(type(SDLK_SLASH), int)
        self.assertEqual(SDLK_SLASH, ord('/'))

    def test_SDLK_0(self):
        self.assertIs(type(SDLK_0), int)
        self.assertEqual(SDLK_0, ord('0'))

    def test_SDLK_1(self):
        self.assertIs(type(SDLK_1), int)
        self.assertEqual(SDLK_1, ord('1'))

    def test_SDLK_2(self):
        self.assertIs(type(SDLK_2), int)
        self.assertEqual(SDLK_2, ord('2'))

    def test_SDLK_3(self):
        self.assertIs(type(SDLK_3), int)
        self.assertEqual(SDLK_3, ord('3'))

    def test_SDLK_4(self):
        self.assertIs(type(SDLK_4), int)
        self.assertEqual(SDLK_4, ord('4'))

    def test_SDLK_5(self):
        self.assertIs(type(SDLK_5), int)
        self.assertEqual(SDLK_5, ord('5'))

    def test_SDLK_6(self):
        self.assertIs(type(SDLK_6), int)
        self.assertEqual(SDLK_6, ord('6'))

    def test_SDLK_7(self):
        self.assertIs(type(SDLK_7), int)
        self.assertEqual(SDLK_7, ord('7'))

    def test_SDLK_8(self):
        self.assertIs(type(SDLK_8), int)
        self.assertEqual(SDLK_8, ord('8'))

    def test_SDLK_9(self):
        self.assertIs(type(SDLK_9), int)
        self.assertEqual(SDLK_9, ord('9'))

    def test_SDLK_COLON(self):
        self.assertIs(type(SDLK_COLON), int)
        self.assertEqual(SDLK_COLON, ord(':'))

    def test_SDLK_SEMICOLON(self):
        self.assertIs(type(SDLK_SEMICOLON), int)
        self.assertEqual(SDLK_SEMICOLON, ord(';'))

    def test_SDLK_LESS(self):
        self.assertIs(type(SDLK_LESS), int)
        self.assertEqual(SDLK_LESS, ord('<'))

    def test_SDLK_EQUALS(self):
        self.assertIs(type(SDLK_EQUALS), int)
        self.assertEqual(SDLK_EQUALS, ord('='))

    def test_SDLK_GREATER(self):
        self.assertIs(type(SDLK_GREATER), int)
        self.assertEqual(SDLK_GREATER, ord('>'))

    def test_SDLK_QUESTION(self):
        self.assertIs(type(SDLK_QUESTION), int)
        self.assertEqual(SDLK_QUESTION, ord('?'))

    def test_SDLK_AT(self):
        self.assertIs(type(SDLK_AT), int)
        self.assertEqual(SDLK_AT, ord('@'))

    def test_SDLK_LEFTBRACKET(self):
        self.assertIs(type(SDLK_LEFTBRACKET), int)
        self.assertEqual(SDLK_LEFTBRACKET, ord('['))

    def test_SDLK_BACKSLASH(self):
        self.assertIs(type(SDLK_BACKSLASH), int)
        self.assertEqual(SDLK_BACKSLASH, ord('\\'))

    def test_SDLK_RIGHTBRACKET(self):
        self.assertIs(type(SDLK_RIGHTBRACKET), int)
        self.assertEqual(SDLK_RIGHTBRACKET, ord(']'))

    def test_SDLK_CARET(self):
        self.assertIs(type(SDLK_CARET), int)
        self.assertEqual(SDLK_CARET, ord('^'))

    def test_SDLK_UNDERSCORE(self):
        self.assertIs(type(SDLK_UNDERSCORE), int)
        self.assertEqual(SDLK_UNDERSCORE, ord('_'))

    def test_SDLK_BACKQUOTE(self):
        self.assertIs(type(SDLK_BACKQUOTE), int)
        self.assertEqual(SDLK_BACKQUOTE, ord('`'))

    def test_SDLK_a(self):
        self.assertIs(type(SDLK_a), int)
        self.assertEqual(SDLK_a, ord('a'))

    def test_SDLK_b(self):
        self.assertIs(type(SDLK_b), int)
        self.assertEqual(SDLK_b, ord('b'))

    def test_SDLK_c(self):
        self.assertIs(type(SDLK_c), int)
        self.assertEqual(SDLK_c, ord('c'))

    def test_SDLK_d(self):
        self.assertIs(type(SDLK_d), int)
        self.assertEqual(SDLK_d, ord('d'))

    def test_SDLK_e(self):
        self.assertIs(type(SDLK_e), int)
        self.assertEqual(SDLK_e, ord('e'))

    def test_SDLK_f(self):
        self.assertIs(type(SDLK_f), int)
        self.assertEqual(SDLK_f, ord('f'))

    def test_SDLK_g(self):
        self.assertIs(type(SDLK_g), int)
        self.assertEqual(SDLK_g, ord('g'))

    def test_SDLK_h(self):
        self.assertIs(type(SDLK_h), int)
        self.assertEqual(SDLK_h, ord('h'))

    def test_SDLK_i(self):
        self.assertIs(type(SDLK_i), int)
        self.assertEqual(SDLK_i, ord('i'))

    def test_SDLK_j(self):
        self.assertIs(type(SDLK_j), int)
        self.assertEqual(SDLK_j, ord('j'))

    def test_SDLK_k(self):
        self.assertIs(type(SDLK_k), int)
        self.assertEqual(SDLK_k, ord('k'))

    def test_SDLK_l(self):
        self.assertIs(type(SDLK_l), int)
        self.assertEqual(SDLK_l, ord('l'))

    def test_SDLK_m(self):
        self.assertIs(type(SDLK_m), int)
        self.assertEqual(SDLK_m, ord('m'))

    def test_SDLK_n(self):
        self.assertIs(type(SDLK_n), int)
        self.assertEqual(SDLK_n, ord('n'))

    def test_SDLK_o(self):
        self.assertIs(type(SDLK_o), int)
        self.assertEqual(SDLK_o, ord('o'))

    def test_SDLK_p(self):
        self.assertIs(type(SDLK_p), int)
        self.assertEqual(SDLK_p, ord('p'))

    def test_SDLK_q(self):
        self.assertIs(type(SDLK_q), int)
        self.assertEqual(SDLK_q, ord('q'))

    def test_SDLK_r(self):
        self.assertIs(type(SDLK_r), int)
        self.assertEqual(SDLK_r, ord('r'))

    def test_SDLK_s(self):
        self.assertIs(type(SDLK_s), int)
        self.assertEqual(SDLK_s, ord('s'))

    def test_SDLK_t(self):
        self.assertIs(type(SDLK_t), int)
        self.assertEqual(SDLK_t, ord('t'))

    def test_SDLK_u(self):
        self.assertIs(type(SDLK_u), int)
        self.assertEqual(SDLK_u, ord('u'))

    def test_SDLK_v(self):
        self.assertIs(type(SDLK_v), int)
        self.assertEqual(SDLK_v, ord('v'))

    def test_SDLK_w(self):
        self.assertIs(type(SDLK_w), int)
        self.assertEqual(SDLK_w, ord('w'))

    def test_SDLK_x(self):
        self.assertIs(type(SDLK_x), int)
        self.assertEqual(SDLK_x, ord('x'))

    def test_SDLK_y(self):
        self.assertIs(type(SDLK_y), int)
        self.assertEqual(SDLK_y, ord('y'))

    def test_SDLK_z(self):
        self.assertIs(type(SDLK_z), int)
        self.assertEqual(SDLK_z, ord('z'))

    def test_SDLK_CAPSLOCK(self):
        self.assertIs(type(SDLK_CAPSLOCK), int)
        self.assertEqual(SDLK_CAPSLOCK,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK))

    def test_SDLK_F1(self):
        self.assertIs(type(SDLK_F1), int)
        self.assertEqual(SDLK_F1, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1))

    def test_SDLK_F2(self):
        self.assertIs(type(SDLK_F2), int)
        self.assertEqual(SDLK_F2, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2))

    def test_SDLK_F3(self):
        self.assertIs(type(SDLK_F3), int)
        self.assertEqual(SDLK_F3, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3))

    def test_SDLK_F4(self):
        self.assertIs(type(SDLK_F4), int)
        self.assertEqual(SDLK_F4, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4))

    def test_SDLK_F5(self):
        self.assertIs(type(SDLK_F5), int)
        self.assertEqual(SDLK_F5, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5))

    def test_SDLK_F6(self):
        self.assertIs(type(SDLK_F6), int)
        self.assertEqual(SDLK_F6, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6))

    def test_SDLK_F7(self):
        self.assertIs(type(SDLK_F7), int)
        self.assertEqual(SDLK_F7, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7))

    def test_SDLK_F8(self):
        self.assertIs(type(SDLK_F8), int)
        self.assertEqual(SDLK_F8, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8))

    def test_SDLK_F9(self):
        self.assertIs(type(SDLK_F9), int)
        self.assertEqual(SDLK_F9, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9))

    def test_SDLK_F10(self):
        self.assertIs(type(SDLK_F10), int)
        self.assertEqual(SDLK_F10, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10))

    def test_SDLK_F11(self):
        self.assertIs(type(SDLK_F11), int)
        self.assertEqual(SDLK_F11, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11))

    def test_SDLK_F12(self):
        self.assertIs(type(SDLK_F12), int)
        self.assertEqual(SDLK_F12, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12))

    def test_SDLK_PRINTSCREEN(self):
        self.assertIs(type(SDLK_PRINTSCREEN), int)
        self.assertEqual(SDLK_PRINTSCREEN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN))

    def test_SDLK_SCROLLLOCK(self):
        self.assertIs(type(SDLK_SCROLLLOCK), int)
        self.assertEqual(SDLK_SCROLLLOCK,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK))

    def test_SDLK_PAUSE(self):
        self.assertIs(type(SDLK_PAUSE), int)
        self.assertEqual(SDLK_PAUSE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE))

    def test_SDLK_INSERT(self):
        self.assertIs(type(SDLK_INSERT), int)
        self.assertEqual(SDLK_INSERT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT))

    def test_SDLK_HOME(self):
        self.assertIs(type(SDLK_HOME), int)
        self.assertEqual(SDLK_HOME, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME))

    def test_SDLK_PAGEUP(self):
        self.assertIs(type(SDLK_PAGEUP), int)
        self.assertEqual(SDLK_PAGEUP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP))

    def test_SDLK_DELETE(self):
        self.assertIs(type(SDLK_DELETE), int)
        self.assertEqual(SDLK_DELETE, ord('\177'))

    def test_SDLK_END(self):
        self.assertIs(type(SDLK_END), int)
        self.assertEqual(SDLK_END, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END))

    def test_SDLK_PAGEDOWN(self):
        self.assertIs(type(SDLK_PAGEDOWN), int)
        self.assertEqual(SDLK_PAGEDOWN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN))

    def test_SDLK_RIGHT(self):
        self.assertIs(type(SDLK_RIGHT), int)
        self.assertEqual(SDLK_RIGHT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT))

    def test_SDLK_LEFT(self):
        self.assertIs(type(SDLK_LEFT), int)
        self.assertEqual(SDLK_LEFT, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT))

    def test_SDLK_DOWN(self):
        self.assertIs(type(SDLK_DOWN), int)
        self.assertEqual(SDLK_DOWN, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN))

    def test_SDLK_UP(self):
        self.assertIs(type(SDLK_UP), int)
        self.assertEqual(SDLK_UP, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP))

    def test_SDLK_NUMLOCKCLEAR(self):
        self.assertIs(type(SDLK_NUMLOCKCLEAR), int)
        self.assertEqual(SDLK_NUMLOCKCLEAR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR))

    def test_SDLK_KP_DIVIDE(self):
        self.assertIs(type(SDLK_KP_DIVIDE), int)
        self.assertEqual(SDLK_KP_DIVIDE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE))

    def test_SDLK_KP_MULTIPLY(self):
        self.assertIs(type(SDLK_KP_MULTIPLY), int)
        self.assertEqual(SDLK_KP_MULTIPLY,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY))

    def test_SDLK_KP_MINUS(self):
        self.assertIs(type(SDLK_KP_MINUS), int)
        self.assertEqual(SDLK_KP_MINUS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS))

    def test_SDLK_KP_PLUS(self):
        self.assertIs(type(SDLK_KP_PLUS), int)
        self.assertEqual(SDLK_KP_PLUS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS))

    def test_SDLK_KP_ENTER(self):
        self.assertIs(type(SDLK_KP_ENTER), int)
        self.assertEqual(SDLK_KP_ENTER,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER))

    def test_SDLK_KP_1(self):
        self.assertIs(type(SDLK_KP_1), int)
        self.assertEqual(SDLK_KP_1, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1))

    def test_SDLK_KP_2(self):
        self.assertIs(type(SDLK_KP_2), int)
        self.assertEqual(SDLK_KP_2, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2))

    def test_SDLK_KP_3(self):
        self.assertIs(type(SDLK_KP_3), int)
        self.assertEqual(SDLK_KP_3, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3))

    def test_SDLK_KP_4(self):
        self.assertIs(type(SDLK_KP_4), int)
        self.assertEqual(SDLK_KP_4, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4))

    def test_SDLK_KP_5(self):
        self.assertIs(type(SDLK_KP_5), int)
        self.assertEqual(SDLK_KP_5, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5))

    def test_SDLK_KP_6(self):
        self.assertIs(type(SDLK_KP_6), int)
        self.assertEqual(SDLK_KP_6, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6))

    def test_SDLK_KP_7(self):
        self.assertIs(type(SDLK_KP_7), int)
        self.assertEqual(SDLK_KP_7, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7))

    def test_SDLK_KP_8(self):
        self.assertIs(type(SDLK_KP_8), int)
        self.assertEqual(SDLK_KP_8, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8))

    def test_SDLK_KP_9(self):
        self.assertIs(type(SDLK_KP_9), int)
        self.assertEqual(SDLK_KP_9, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9))

    def test_SDLK_KP_0(self):
        self.assertIs(type(SDLK_KP_0), int)
        self.assertEqual(SDLK_KP_0, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0))

    def test_SDLK_KP_PERIOD(self):
        self.assertIs(type(SDLK_KP_PERIOD), int)
        self.assertEqual(SDLK_KP_PERIOD,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD))

    def test_SDLK_APPLICATION(self):
        self.assertIs(type(SDLK_APPLICATION), int)
        self.assertEqual(SDLK_APPLICATION,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION))

    def test_SDLK_POWER(self):
        self.assertIs(type(SDLK_POWER), int)
        self.assertEqual(SDLK_POWER,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER))

    def test_SDLK_KP_EQUALS(self):
        self.assertIs(type(SDLK_KP_EQUALS), int)
        self.assertEqual(SDLK_KP_EQUALS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS))

    def test_SDLK_F13(self):
        self.assertIs(type(SDLK_F13), int)
        self.assertEqual(SDLK_F13, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13))

    def test_SDLK_F14(self):
        self.assertIs(type(SDLK_F14), int)
        self.assertEqual(SDLK_F14, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14))

    def test_SDLK_F15(self):
        self.assertIs(type(SDLK_F15), int)
        self.assertEqual(SDLK_F15, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15))

    def test_SDLK_F16(self):
        self.assertIs(type(SDLK_F16), int)
        self.assertEqual(SDLK_F16, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16))

    def test_SDLK_F17(self):
        self.assertIs(type(SDLK_F17), int)
        self.assertEqual(SDLK_F17, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17))

    def test_SDLK_F18(self):
        self.assertIs(type(SDLK_F18), int)
        self.assertEqual(SDLK_F18, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18))

    def test_SDLK_F19(self):
        self.assertIs(type(SDLK_F19), int)
        self.assertEqual(SDLK_F19, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19))

    def test_SDLK_F20(self):
        self.assertIs(type(SDLK_F20), int)
        self.assertEqual(SDLK_F20, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20))

    def test_SDLK_F21(self):
        self.assertIs(type(SDLK_F21), int)
        self.assertEqual(SDLK_F21, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21))

    def test_SDLK_F22(self):
        self.assertIs(type(SDLK_F22), int)
        self.assertEqual(SDLK_F22, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22))

    def test_SDLK_F23(self):
        self.assertIs(type(SDLK_F23), int)
        self.assertEqual(SDLK_F23, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23))

    def test_SDLK_F24(self):
        self.assertIs(type(SDLK_F24), int)
        self.assertEqual(SDLK_F24, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24))

    def test_SDLK_EXECUTE(self):
        self.assertIs(type(SDLK_EXECUTE), int)
        self.assertEqual(SDLK_EXECUTE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE))

    def test_SDLK_HELP(self):
        self.assertIs(type(SDLK_HELP), int)
        self.assertEqual(SDLK_HELP, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP))

    def test_SDLK_MENU(self):
        self.assertIs(type(SDLK_MENU), int)
        self.assertEqual(SDLK_MENU, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU))

    def test_SDLK_SELECT(self):
        self.assertIs(type(SDLK_SELECT), int)
        self.assertEqual(SDLK_SELECT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT))

    def test_SDLK_STOP(self):
        self.assertIs(type(SDLK_STOP), int)
        self.assertEqual(SDLK_STOP, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP))

    def test_SDLK_AGAIN(self):
        self.assertIs(type(SDLK_AGAIN), int)
        self.assertEqual(SDLK_AGAIN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN))

    def test_SDLK_UNDO(self):
        self.assertIs(type(SDLK_UNDO), int)
        self.assertEqual(SDLK_UNDO, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO))

    def test_SDLK_CUT(self):
        self.assertIs(type(SDLK_CUT), int)
        self.assertEqual(SDLK_CUT, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT))

    def test_SDLK_COPY(self):
        self.assertIs(type(SDLK_COPY), int)
        self.assertEqual(SDLK_COPY, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY))

    def test_SDLK_PASTE(self):
        self.assertIs(type(SDLK_PASTE), int)
        self.assertEqual(SDLK_PASTE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE))

    def test_SDLK_FIND(self):
        self.assertIs(type(SDLK_FIND), int)
        self.assertEqual(SDLK_FIND, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND))

    def test_SDLK_MUTE(self):
        self.assertIs(type(SDLK_MUTE), int)
        self.assertEqual(SDLK_MUTE, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE))

    def test_SDLK_VOLUMEUP(self):
        self.assertIs(type(SDLK_VOLUMEUP), int)
        self.assertEqual(SDLK_VOLUMEUP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP))

    def test_SDLK_VOLUMEDOWN(self):
        self.assertIs(type(SDLK_VOLUMEDOWN), int)
        self.assertEqual(SDLK_VOLUMEDOWN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN))

    def test_SDLK_KP_COMMA(self):
        self.assertIs(type(SDLK_KP_COMMA), int)
        self.assertEqual(SDLK_KP_COMMA,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA))

    def test_SDLK_KP_EQUALSAS400(self):
        self.assertIs(type(SDLK_KP_EQUALSAS400), int)
        self.assertEqual(SDLK_KP_EQUALSAS400,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400))

    def test_SDLK_ALTERASE(self):
        self.assertIs(type(SDLK_ALTERASE), int)
        self.assertEqual(SDLK_ALTERASE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE))

    def test_SDLK_SYSREQ(self):
        self.assertIs(type(SDLK_SYSREQ), int)
        self.assertEqual(SDLK_SYSREQ,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ))

    def test_SDLK_CANCEL(self):
        self.assertIs(type(SDLK_CANCEL), int)
        self.assertEqual(SDLK_CANCEL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL))

    def test_SDLK_CLEAR(self):
        self.assertIs(type(SDLK_CLEAR), int)
        self.assertEqual(SDLK_CLEAR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR))

    def test_SDLK_PRIOR(self):
        self.assertIs(type(SDLK_PRIOR), int)
        self.assertEqual(SDLK_PRIOR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR))

    def test_SDLK_RETURN2(self):
        self.assertIs(type(SDLK_RETURN2), int)
        self.assertEqual(SDLK_RETURN2,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2))

    def test_SDLK_SEPARATOR(self):
        self.assertIs(type(SDLK_SEPARATOR), int)
        self.assertEqual(SDLK_SEPARATOR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR))

    def test_SDLK_OUT(self):
        self.assertIs(type(SDLK_OUT), int)
        self.assertEqual(SDLK_OUT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT))

    def test_SDLK_OPER(self):
        self.assertIs(type(SDLK_OPER), int)
        self.assertEqual(SDLK_OPER, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER))

    def test_SDLK_CLEARAGAIN(self):
        self.assertIs(type(SDLK_CLEARAGAIN), int)
        self.assertEqual(SDLK_CLEARAGAIN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN))

    def test_SDLK_CRSEL(self):
        self.assertIs(type(SDLK_CRSEL), int)
        self.assertEqual(SDLK_CRSEL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL))

    def test_SDLK_EXSEL(self):
        self.assertIs(type(SDLK_EXSEL), int)
        self.assertEqual(SDLK_EXSEL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL))

    def test_SDLK_KP_00(self):
        self.assertIs(type(SDLK_KP_00), int)
        self.assertEqual(SDLK_KP_00,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00))

    def test_SDLK_KP_000(self):
        self.assertIs(type(SDLK_KP_000), int)
        self.assertEqual(SDLK_KP_000,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000))

    def test_SDLK_THOUSANDSSEPARATOR(self):
        x = SDL_SCANCODE_THOUSANDSSEPARATOR
        self.assertIs(type(SDLK_THOUSANDSSEPARATOR), int)
        self.assertEqual(SDLK_THOUSANDSSEPARATOR, SDL_SCANCODE_TO_KEYCODE(x))

    def test_SDLK_DECIMALSEPARATOR(self):
        x = SDL_SCANCODE_DECIMALSEPARATOR
        self.assertIs(type(SDLK_DECIMALSEPARATOR), int)
        self.assertEqual(SDLK_DECIMALSEPARATOR, SDL_SCANCODE_TO_KEYCODE(x))

    def test_SDLK_CURRENCYUNIT(self):
        self.assertIs(type(SDLK_CURRENCYUNIT), int)
        self.assertEqual(SDLK_CURRENCYUNIT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT))

    def test_SDLK_CURRENCYSUBUNIT(self):
        self.assertIs(type(SDLK_CURRENCYSUBUNIT), int)
        self.assertEqual(SDLK_CURRENCYSUBUNIT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT))

    def test_SDLK_KP_LEFTPAREN(self):
        self.assertIs(type(SDLK_KP_LEFTPAREN), int)
        self.assertEqual(SDLK_KP_LEFTPAREN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN))

    def test_SDLK_KP_RIGHTPAREN(self):
        self.assertIs(type(SDLK_KP_RIGHTPAREN), int)
        self.assertEqual(SDLK_KP_RIGHTPAREN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN))

    def test_SDLK_KP_LEFTBRACE(self):
        self.assertIs(type(SDLK_KP_LEFTBRACE), int)
        self.assertEqual(SDLK_KP_LEFTBRACE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE))

    def test_SDLK_KP_RIGHTBRACE(self):
        self.assertIs(type(SDLK_KP_RIGHTBRACE), int)
        self.assertEqual(SDLK_KP_RIGHTBRACE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE))

    def test_SDLK_KP_TAB(self):
        self.assertIs(type(SDLK_KP_TAB), int)
        self.assertEqual(SDLK_KP_TAB,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB))

    def test_SDLK_KP_BACKSPACE(self):
        self.assertIs(type(SDLK_KP_BACKSPACE), int)
        self.assertEqual(SDLK_KP_BACKSPACE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE))

    def test_SDLK_KP_A(self):
        self.assertIs(type(SDLK_KP_A), int)
        self.assertEqual(SDLK_KP_A, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A))

    def test_SDLK_KP_B(self):
        self.assertIs(type(SDLK_KP_B), int)
        self.assertEqual(SDLK_KP_B, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B))

    def test_SDLK_KP_C(self):
        self.assertIs(type(SDLK_KP_C), int)
        self.assertEqual(SDLK_KP_C, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C))

    def test_SDLK_KP_D(self):
        self.assertIs(type(SDLK_KP_D), int)
        self.assertEqual(SDLK_KP_D, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D))

    def test_SDLK_KP_E(self):
        self.assertIs(type(SDLK_KP_E), int)
        self.assertEqual(SDLK_KP_E, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E))

    def test_SDLK_KP_F(self):
        self.assertIs(type(SDLK_KP_F), int)
        self.assertEqual(SDLK_KP_F, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F))

    def test_SDLK_KP_XOR(self):
        self.assertIs(type(SDLK_KP_XOR), int)
        self.assertEqual(SDLK_KP_XOR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR))

    def test_SDLK_KP_POWER(self):
        self.assertIs(type(SDLK_KP_POWER), int)
        self.assertEqual(SDLK_KP_POWER,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER))

    def test_SDLK_KP_PERCENT(self):
        self.assertIs(type(SDLK_KP_PERCENT), int)
        self.assertEqual(SDLK_KP_PERCENT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT))

    def test_SDLK_KP_LESS(self):
        self.assertIs(type(SDLK_KP_LESS), int)
        self.assertEqual(SDLK_KP_LESS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS))

    def test_SDLK_KP_GREATER(self):
        self.assertIs(type(SDLK_KP_GREATER), int)
        self.assertEqual(SDLK_KP_GREATER,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER))

    def test_SDLK_KP_AMPERSAND(self):
        self.assertIs(type(SDLK_KP_AMPERSAND), int)
        self.assertEqual(SDLK_KP_AMPERSAND,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND))

    def test_SDLK_KP_DBLAMPERSAND(self):
        self.assertIs(type(SDLK_KP_DBLAMPERSAND), int)
        self.assertEqual(SDLK_KP_DBLAMPERSAND,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND))

    def test_SDLK_KP_VERTICALBAR(self):
        x = SDL_SCANCODE_KP_VERTICALBAR
        self.assertIs(type(SDLK_KP_VERTICALBAR), int)
        self.assertEqual(SDLK_KP_VERTICALBAR, SDL_SCANCODE_TO_KEYCODE(x))

    def test_SDLK_KP_DBLVERTICALBAR(self):
        x = SDL_SCANCODE_KP_DBLVERTICALBAR
        self.assertIs(type(SDLK_KP_DBLVERTICALBAR), int)
        self.assertEqual(SDLK_KP_DBLVERTICALBAR, SDL_SCANCODE_TO_KEYCODE(x))

    def test_SDLK_KP_COLON(self):
        self.assertIs(type(SDLK_KP_COLON), int)
        self.assertEqual(SDLK_KP_COLON,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON))

    def test_SDLK_KP_HASH(self):
        self.assertIs(type(SDLK_KP_HASH), int)
        self.assertEqual(SDLK_KP_HASH,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH))

    def test_SDLK_KP_SPACE(self):
        self.assertIs(type(SDLK_KP_SPACE), int)
        self.assertEqual(SDLK_KP_SPACE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE))

    def test_SDLK_KP_AT(self):
        self.assertIs(type(SDLK_KP_AT), int)
        self.assertEqual(SDLK_KP_AT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT))

    def test_SDLK_KP_EXCLAM(self):
        self.assertIs(type(SDLK_KP_EXCLAM), int)
        self.assertEqual(SDLK_KP_EXCLAM,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM))

    def test_SDLK_KP_MEMSTORE(self):
        self.assertIs(type(SDLK_KP_MEMSTORE), int)
        self.assertEqual(SDLK_KP_MEMSTORE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE))

    def test_SDLK_KP_MEMRECALL(self):
        self.assertIs(type(SDLK_KP_MEMRECALL), int)
        self.assertEqual(SDLK_KP_MEMRECALL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL))

    def test_SDLK_KP_MEMCLEAR(self):
        self.assertIs(type(SDLK_KP_MEMCLEAR), int)
        self.assertEqual(SDLK_KP_MEMCLEAR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR))

    def test_SDLK_KP_MEMADD(self):
        self.assertIs(type(SDLK_KP_MEMADD), int)
        self.assertEqual(SDLK_KP_MEMADD,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD))

    def test_SDLK_KP_MEMSUBTRACT(self):
        self.assertIs(type(SDLK_KP_MEMSUBTRACT), int)
        self.assertEqual(SDLK_KP_MEMSUBTRACT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT))

    def test_SDLK_KP_MEMMULTIPLY(self):
        self.assertIs(type(SDLK_KP_MEMMULTIPLY), int)
        self.assertEqual(SDLK_KP_MEMMULTIPLY,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY))

    def test_SDLK_KP_MEMDIVIDE(self):
        self.assertIs(type(SDLK_KP_MEMDIVIDE), int)
        self.assertEqual(SDLK_KP_MEMDIVIDE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE))

    def test_SDLK_KP_PLUSMINUS(self):
        self.assertIs(type(SDLK_KP_PLUSMINUS), int)
        self.assertEqual(SDLK_KP_PLUSMINUS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS))

    def test_SDLK_KP_CLEAR(self):
        self.assertIs(type(SDLK_KP_CLEAR), int)
        self.assertEqual(SDLK_KP_CLEAR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR))

    def test_SDLK_KP_CLEARENTRY(self):
        self.assertIs(type(SDLK_KP_CLEARENTRY), int)
        self.assertEqual(SDLK_KP_CLEARENTRY,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY))

    def test_SDLK_KP_BINARY(self):
        self.assertIs(type(SDLK_KP_BINARY), int)
        self.assertEqual(SDLK_KP_BINARY,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY))

    def test_SDLK_KP_OCTAL(self):
        self.assertIs(type(SDLK_KP_OCTAL), int)
        self.assertEqual(SDLK_KP_OCTAL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL))

    def test_SDLK_KP_DECIMAL(self):
        self.assertIs(type(SDLK_KP_DECIMAL), int)
        self.assertEqual(SDLK_KP_DECIMAL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL))

    def test_SDLK_KP_HEXADECIMAL(self):
        self.assertIs(type(SDLK_KP_HEXADECIMAL), int)
        self.assertEqual(SDLK_KP_HEXADECIMAL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL))

    def test_SDLK_LCTRL(self):
        self.assertIs(type(SDLK_LCTRL), int)
        self.assertEqual(SDLK_LCTRL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL))

    def test_SDLK_LSHIFT(self):
        self.assertIs(type(SDLK_LSHIFT), int)
        self.assertEqual(SDLK_LSHIFT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT))

    def test_SDLK_LALT(self):
        self.assertIs(type(SDLK_LALT), int)
        self.assertEqual(SDLK_LALT, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT))

    def test_SDLK_LGUI(self):
        self.assertIs(type(SDLK_LGUI), int)
        self.assertEqual(SDLK_LGUI, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI))

    def test_SDLK_RCTRL(self):
        self.assertIs(type(SDLK_RCTRL), int)
        self.assertEqual(SDLK_RCTRL,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL))

    def test_SDLK_RSHIFT(self):
        self.assertIs(type(SDLK_RSHIFT), int)
        self.assertEqual(SDLK_RSHIFT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT))

    def test_SDLK_RALT(self):
        self.assertIs(type(SDLK_RALT), int)
        self.assertEqual(SDLK_RALT, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT))

    def test_SDLK_RGUI(self):
        self.assertIs(type(SDLK_RGUI), int)
        self.assertEqual(SDLK_RGUI, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI))

    def test_SDLK_MODE(self):
        self.assertIs(type(SDLK_MODE), int)
        self.assertEqual(SDLK_MODE, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE))

    def test_SDLK_AUDIONEXT(self):
        self.assertIs(type(SDLK_AUDIONEXT), int)
        self.assertEqual(SDLK_AUDIONEXT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT))

    def test_SDLK_AUDIOPREV(self):
        self.assertIs(type(SDLK_AUDIOPREV), int)
        self.assertEqual(SDLK_AUDIOPREV,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV))

    def test_SDLK_AUDIOSTOP(self):
        self.assertIs(type(SDLK_AUDIOSTOP), int)
        self.assertEqual(SDLK_AUDIOSTOP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP))

    def test_SDLK_AUDIOPLAY(self):
        self.assertIs(type(SDLK_AUDIOPLAY), int)
        self.assertEqual(SDLK_AUDIOPLAY,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY))

    def test_SDLK_AUDIOMUTE(self):
        self.assertIs(type(SDLK_AUDIOMUTE), int)
        self.assertEqual(SDLK_AUDIOMUTE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE))

    def test_SDLK_MEDIASELECT(self):
        self.assertIs(type(SDLK_MEDIASELECT), int)
        self.assertEqual(SDLK_MEDIASELECT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT))

    def test_SDLK_WWW(self):
        self.assertIs(type(SDLK_WWW), int)
        self.assertEqual(SDLK_WWW, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW))

    def test_SDLK_MAIL(self):
        self.assertIs(type(SDLK_MAIL), int)
        self.assertEqual(SDLK_MAIL, SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL))

    def test_SDLK_CALCULATOR(self):
        self.assertIs(type(SDLK_CALCULATOR), int)
        self.assertEqual(SDLK_CALCULATOR,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR))

    def test_SDLK_COMPUTER(self):
        self.assertIs(type(SDLK_COMPUTER), int)
        self.assertEqual(SDLK_COMPUTER,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER))

    def test_SDLK_AC_SEARCH(self):
        self.assertIs(type(SDLK_AC_SEARCH), int)
        self.assertEqual(SDLK_AC_SEARCH,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH))

    def test_SDLK_AC_HOME(self):
        self.assertIs(type(SDLK_AC_HOME), int)
        self.assertEqual(SDLK_AC_HOME,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME))

    def test_SDLK_AC_BACK(self):
        self.assertIs(type(SDLK_AC_BACK), int)
        self.assertEqual(SDLK_AC_BACK,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK))

    def test_SDLK_AC_FORWARD(self):
        self.assertIs(type(SDLK_AC_FORWARD), int)
        self.assertEqual(SDLK_AC_FORWARD,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD))

    def test_SDLK_AC_STOP(self):
        self.assertIs(type(SDLK_AC_STOP), int)
        self.assertEqual(SDLK_AC_STOP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP))

    def test_SDLK_AC_REFRESH(self):
        self.assertIs(type(SDLK_AC_REFRESH), int)
        self.assertEqual(SDLK_AC_REFRESH,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH))

    def test_SDLK_AC_BOOKMARKS(self):
        self.assertIs(type(SDLK_AC_BOOKMARKS), int)
        self.assertEqual(SDLK_AC_BOOKMARKS,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS))

    def test_SDLK_BRIGHTNESSDOWN(self):
        self.assertIs(type(SDLK_BRIGHTNESSDOWN), int)
        self.assertEqual(SDLK_BRIGHTNESSDOWN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN))

    def test_SDLK_BRIGHTNESSUP(self):
        self.assertIs(type(SDLK_BRIGHTNESSUP), int)
        self.assertEqual(SDLK_BRIGHTNESSUP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP))

    def test_SDLK_DISPLAYSWITCH(self):
        self.assertIs(type(SDLK_DISPLAYSWITCH), int)
        self.assertEqual(SDLK_DISPLAYSWITCH,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH))

    def test_SDLK_KBDILLUMTOGGLE(self):
        self.assertIs(type(SDLK_KBDILLUMTOGGLE), int)
        self.assertEqual(SDLK_KBDILLUMTOGGLE,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE))

    def test_SDLK_KBDILLUMDOWN(self):
        self.assertIs(type(SDLK_KBDILLUMDOWN), int)
        self.assertEqual(SDLK_KBDILLUMDOWN,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN))

    def test_SDLK_KBDILLUMUP(self):
        self.assertIs(type(SDLK_KBDILLUMUP), int)
        self.assertEqual(SDLK_KBDILLUMUP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP))

    def test_SDLK_EJECT(self):
        self.assertIs(type(SDLK_EJECT), int)
        self.assertEqual(SDLK_EJECT,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT))

    def test_SDLK_SLEEP(self):
        self.assertIs(type(SDLK_SLEEP), int)
        self.assertEqual(SDLK_SLEEP,
                         SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP))

    def test_KMOD_NONE(self):
        self.assertIs(type(KMOD_NONE), int)
        self.assertEqual(KMOD_NONE, 0x0000)

    def test_KMOD_LSHIFT(self):
        self.assertIs(type(KMOD_LSHIFT), int)
        self.assertEqual(KMOD_LSHIFT, 0x0001)

    def test_KMOD_RSHIFT(self):
        self.assertIs(type(KMOD_RSHIFT), int)
        self.assertEqual(KMOD_RSHIFT, 0x0002)

    def test_KMOD_LCTRL(self):
        self.assertIs(type(KMOD_LCTRL), int)
        self.assertEqual(KMOD_LCTRL, 0x0040)

    def test_KMOD_RCTRL(self):
        self.assertIs(type(KMOD_RCTRL), int)
        self.assertEqual(KMOD_RCTRL, 0x0080)

    def test_KMOD_LALT(self):
        self.assertIs(type(KMOD_LALT), int)
        self.assertEqual(KMOD_LALT, 0x0100)

    def test_KMOD_RALT(self):
        self.assertIs(type(KMOD_RALT), int)
        self.assertEqual(KMOD_RALT, 0x0200)

    def test_KMOD_LGUI(self):
        self.assertIs(type(KMOD_LGUI), int)
        self.assertEqual(KMOD_LGUI, 0x0400)

    def test_KMOD_RGUI(self):
        self.assertIs(type(KMOD_RGUI), int)
        self.assertEqual(KMOD_RGUI, 0x0800)

    def test_KMOD_NUM(self):
        self.assertIs(type(KMOD_NUM), int)
        self.assertEqual(KMOD_NUM, 0x1000)

    def test_KMOD_CAPS(self):
        self.assertIs(type(KMOD_CAPS), int)
        self.assertEqual(KMOD_CAPS, 0x2000)

    def test_KMOD_MODE(self):
        self.assertIs(type(KMOD_MODE), int)
        self.assertEqual(KMOD_MODE, 0x4000)

    def test_KMOD_RESERVED(self):
        self.assertIs(type(KMOD_RESERVED), int)
        self.assertEqual(KMOD_RESERVED, 0x8000)

    def test_KMOD_CTRL(self):
        self.assertIs(type(KMOD_CTRL), int)
        self.assertEqual(KMOD_CTRL, KMOD_LCTRL | KMOD_RCTRL)

    def test_KMOD_SHIFT(self):
        self.assertIs(type(KMOD_SHIFT), int)
        self.assertEqual(KMOD_SHIFT, KMOD_LSHIFT | KMOD_RSHIFT)

    def test_KMOD_ALT(self):
        self.assertIs(type(KMOD_ALT), int)
        self.assertEqual(KMOD_ALT, KMOD_LALT | KMOD_RALT)

    def test_KMOD_GUI(self):
        self.assertIs(type(KMOD_GUI), int)
        self.assertEqual(KMOD_GUI, KMOD_LGUI | KMOD_RGUI)


class TestSCANCODE_TO_KEYCODE(unittest.TestCase):
    "Tests SDL_SCANCODE_TO_KEYCODE()"

    def test_returns_int(self):
        "Returns an int"
        x = SDL_SCANCODE_TO_KEYCODE(42)
        self.assertIs(type(x), int)
        self.assertEqual(x, 42 | SDLK_SCANCODE_MASK)


if __name__ == '__main__':
    unittest.main()
