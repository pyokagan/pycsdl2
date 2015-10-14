/*
 * pycsdl2
 * Copyright (c) 2015 Paul Tan <pyokagan@pyokagan.name>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must
 *        not claim that you wrote the original software. If you use this
 *        software in a product, an acknowledgment in the product
 *        documentation would be appreciated but is not required.
 *     2. Altered source versions must be plainly marked as such, and must
 *        not be misrepresented as being the original software.
 *     3. This notice may not be removed or altered from any source
 *        distribution.
 */
/**
 * \file keycode.h
 * \brief Bindings for SDL_keycode.h
 *
 * Exposes the sdl keycode constants.
 */
#ifndef _PYCSDL2_KEYCODE_H_
#define _PYCSDL2_KEYCODE_H_
#include <Python.h>
#include <SDL_scancode.h>
#include "../include/pycsdl2.h"
#include "util.h"

/**
 * \brief Implements csdl2.SDL_SCANCODE_TO_KEYCODE()
 *
 * \code{.py}
 * SDL_SCANCODE_TO_KEYCODE(scancode: int) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_SCANCODE_TO_KEYCODE(PyObject *module, PyObject *args, PyObject *kwds)
{
    unsigned int scancode;
    static char *kwlist[] = {"scancode", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &scancode))
        return NULL;

    return PyLong_FromUnsignedLong(SDL_SCANCODE_TO_KEYCODE(scancode));
}

/**
 * \brief Initializes bindings to SDL_keycode.h
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initkeycode(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDLK_SCANCODE_MASK", SDLK_SCANCODE_MASK},
        {"SDLK_UNKNOWN", SDLK_UNKNOWN},
        {"SDLK_RETURN", SDLK_RETURN},
        {"SDLK_ESCAPE", SDLK_ESCAPE},
        {"SDLK_BACKSPACE", SDLK_BACKSPACE},
        {"SDLK_TAB", SDLK_TAB},
        {"SDLK_SPACE", SDLK_SPACE},
        {"SDLK_EXCLAIM", SDLK_EXCLAIM},
        {"SDLK_QUOTEDBL", SDLK_QUOTEDBL},
        {"SDLK_HASH", SDLK_HASH},
        {"SDLK_PERCENT", SDLK_PERCENT},
        {"SDLK_DOLLAR", SDLK_DOLLAR},
        {"SDLK_AMPERSAND", SDLK_AMPERSAND},
        {"SDLK_QUOTE", SDLK_QUOTE},
        {"SDLK_LEFTPAREN", SDLK_LEFTPAREN},
        {"SDLK_RIGHTPAREN", SDLK_RIGHTPAREN},
        {"SDLK_ASTERISK", SDLK_ASTERISK},
        {"SDLK_PLUS", SDLK_PLUS},
        {"SDLK_COMMA", SDLK_COMMA},
        {"SDLK_MINUS", SDLK_MINUS},
        {"SDLK_PERIOD", SDLK_PERIOD},
        {"SDLK_SLASH", SDLK_SLASH},
        {"SDLK_0", SDLK_0},
        {"SDLK_1", SDLK_1},
        {"SDLK_2", SDLK_2},
        {"SDLK_3", SDLK_3},
        {"SDLK_4", SDLK_4},
        {"SDLK_5", SDLK_5},
        {"SDLK_6", SDLK_6},
        {"SDLK_7", SDLK_7},
        {"SDLK_8", SDLK_8},
        {"SDLK_9", SDLK_9},
        {"SDLK_COLON", SDLK_COLON},
        {"SDLK_SEMICOLON", SDLK_SEMICOLON},
        {"SDLK_LESS", SDLK_LESS},
        {"SDLK_EQUALS", SDLK_EQUALS},
        {"SDLK_GREATER", SDLK_GREATER},
        {"SDLK_QUESTION", SDLK_QUESTION},
        {"SDLK_AT", SDLK_AT},
        {"SDLK_LEFTBRACKET", SDLK_LEFTBRACKET},
        {"SDLK_BACKSLASH", SDLK_BACKSLASH},
        {"SDLK_RIGHTBRACKET", SDLK_RIGHTBRACKET},
        {"SDLK_CARET", SDLK_CARET},
        {"SDLK_UNDERSCORE", SDLK_UNDERSCORE},
        {"SDLK_BACKQUOTE", SDLK_BACKQUOTE},
        {"SDLK_a", SDLK_a},
        {"SDLK_b", SDLK_b},
        {"SDLK_c", SDLK_c},
        {"SDLK_d", SDLK_d},
        {"SDLK_e", SDLK_e},
        {"SDLK_f", SDLK_f},
        {"SDLK_g", SDLK_g},
        {"SDLK_h", SDLK_h},
        {"SDLK_i", SDLK_i},
        {"SDLK_j", SDLK_j},
        {"SDLK_k", SDLK_k},
        {"SDLK_l", SDLK_l},
        {"SDLK_m", SDLK_m},
        {"SDLK_n", SDLK_n},
        {"SDLK_o", SDLK_o},
        {"SDLK_p", SDLK_p},
        {"SDLK_q", SDLK_q},
        {"SDLK_r", SDLK_r},
        {"SDLK_s", SDLK_s},
        {"SDLK_t", SDLK_t},
        {"SDLK_u", SDLK_u},
        {"SDLK_v", SDLK_v},
        {"SDLK_w", SDLK_w},
        {"SDLK_x", SDLK_x},
        {"SDLK_y", SDLK_y},
        {"SDLK_z", SDLK_z},
        {"SDLK_CAPSLOCK", SDLK_CAPSLOCK},
        {"SDLK_F1", SDLK_F1},
        {"SDLK_F2", SDLK_F2},
        {"SDLK_F3", SDLK_F3},
        {"SDLK_F4", SDLK_F4},
        {"SDLK_F5", SDLK_F5},
        {"SDLK_F6", SDLK_F6},
        {"SDLK_F7", SDLK_F7},
        {"SDLK_F8", SDLK_F8},
        {"SDLK_F9", SDLK_F9},
        {"SDLK_F10", SDLK_F10},
        {"SDLK_F11", SDLK_F11},
        {"SDLK_F12", SDLK_F12},
        {"SDLK_PRINTSCREEN", SDLK_PRINTSCREEN},
        {"SDLK_SCROLLLOCK", SDLK_SCROLLLOCK},
        {"SDLK_PAUSE", SDLK_PAUSE},
        {"SDLK_INSERT", SDLK_INSERT},
        {"SDLK_HOME", SDLK_HOME},
        {"SDLK_PAGEUP", SDLK_PAGEUP},
        {"SDLK_DELETE", SDLK_DELETE},
        {"SDLK_END", SDLK_END},
        {"SDLK_PAGEDOWN", SDLK_PAGEDOWN},
        {"SDLK_RIGHT", SDLK_RIGHT},
        {"SDLK_LEFT", SDLK_LEFT},
        {"SDLK_DOWN", SDLK_DOWN},
        {"SDLK_UP", SDLK_UP},
        {"SDLK_NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR},
        {"SDLK_KP_DIVIDE", SDLK_KP_DIVIDE},
        {"SDLK_KP_MULTIPLY", SDLK_KP_MULTIPLY},
        {"SDLK_KP_MINUS", SDLK_KP_MINUS},
        {"SDLK_KP_PLUS", SDLK_KP_PLUS},
        {"SDLK_KP_ENTER", SDLK_KP_ENTER},
        {"SDLK_KP_1", SDLK_KP_1},
        {"SDLK_KP_2", SDLK_KP_2},
        {"SDLK_KP_3", SDLK_KP_3},
        {"SDLK_KP_4", SDLK_KP_4},
        {"SDLK_KP_5", SDLK_KP_5},
        {"SDLK_KP_6", SDLK_KP_6},
        {"SDLK_KP_7", SDLK_KP_7},
        {"SDLK_KP_8", SDLK_KP_8},
        {"SDLK_KP_9", SDLK_KP_9},
        {"SDLK_KP_0", SDLK_KP_0},
        {"SDLK_KP_PERIOD", SDLK_KP_PERIOD},
        {"SDLK_APPLICATION", SDLK_APPLICATION},
        {"SDLK_POWER", SDLK_POWER},
        {"SDLK_KP_EQUALS", SDLK_KP_EQUALS},
        {"SDLK_F13", SDLK_F13},
        {"SDLK_F14", SDLK_F14},
        {"SDLK_F15", SDLK_F15},
        {"SDLK_F16", SDLK_F16},
        {"SDLK_F17", SDLK_F17},
        {"SDLK_F18", SDLK_F18},
        {"SDLK_F19", SDLK_F19},
        {"SDLK_F20", SDLK_F20},
        {"SDLK_F21", SDLK_F21},
        {"SDLK_F22", SDLK_F22},
        {"SDLK_F23", SDLK_F23},
        {"SDLK_F24", SDLK_F24},
        {"SDLK_EXECUTE", SDLK_EXECUTE},
        {"SDLK_HELP", SDLK_HELP},
        {"SDLK_MENU", SDLK_MENU},
        {"SDLK_SELECT", SDLK_SELECT},
        {"SDLK_STOP", SDLK_STOP},
        {"SDLK_AGAIN", SDLK_AGAIN},
        {"SDLK_UNDO", SDLK_UNDO},
        {"SDLK_CUT", SDLK_CUT},
        {"SDLK_COPY", SDLK_COPY},
        {"SDLK_PASTE", SDLK_PASTE},
        {"SDLK_FIND", SDLK_FIND},
        {"SDLK_MUTE", SDLK_MUTE},
        {"SDLK_VOLUMEUP", SDLK_VOLUMEUP},
        {"SDLK_VOLUMEDOWN", SDLK_VOLUMEDOWN},
        {"SDLK_KP_COMMA", SDLK_KP_COMMA},
        {"SDLK_KP_EQUALSAS400", SDLK_KP_EQUALSAS400},
        {"SDLK_ALTERASE", SDLK_ALTERASE},
        {"SDLK_SYSREQ", SDLK_SYSREQ},
        {"SDLK_CANCEL", SDLK_CANCEL},
        {"SDLK_CLEAR", SDLK_CLEAR},
        {"SDLK_PRIOR", SDLK_PRIOR},
        {"SDLK_RETURN2", SDLK_RETURN2},
        {"SDLK_SEPARATOR", SDLK_SEPARATOR},
        {"SDLK_OUT", SDLK_OUT},
        {"SDLK_OPER", SDLK_OPER},
        {"SDLK_CLEARAGAIN", SDLK_CLEARAGAIN},
        {"SDLK_CRSEL", SDLK_CRSEL},
        {"SDLK_EXSEL", SDLK_EXSEL},
        {"SDLK_KP_00", SDLK_KP_00},
        {"SDLK_KP_000", SDLK_KP_000},
        {"SDLK_THOUSANDSSEPARATOR", SDLK_THOUSANDSSEPARATOR},
        {"SDLK_DECIMALSEPARATOR", SDLK_DECIMALSEPARATOR},
        {"SDLK_CURRENCYUNIT", SDLK_CURRENCYUNIT},
        {"SDLK_CURRENCYSUBUNIT", SDLK_CURRENCYSUBUNIT},
        {"SDLK_KP_LEFTPAREN", SDLK_KP_LEFTPAREN},
        {"SDLK_KP_RIGHTPAREN", SDLK_KP_RIGHTPAREN},
        {"SDLK_KP_LEFTBRACE", SDLK_KP_LEFTBRACE},
        {"SDLK_KP_RIGHTBRACE", SDLK_KP_RIGHTBRACE},
        {"SDLK_KP_TAB", SDLK_KP_TAB},
        {"SDLK_KP_BACKSPACE", SDLK_KP_BACKSPACE},
        {"SDLK_KP_A", SDLK_KP_A},
        {"SDLK_KP_B", SDLK_KP_B},
        {"SDLK_KP_C", SDLK_KP_C},
        {"SDLK_KP_D", SDLK_KP_D},
        {"SDLK_KP_E", SDLK_KP_E},
        {"SDLK_KP_F", SDLK_KP_F},
        {"SDLK_KP_XOR", SDLK_KP_XOR},
        {"SDLK_KP_POWER", SDLK_KP_POWER},
        {"SDLK_KP_PERCENT", SDLK_KP_PERCENT},
        {"SDLK_KP_LESS", SDLK_KP_LESS},
        {"SDLK_KP_GREATER", SDLK_KP_GREATER},
        {"SDLK_KP_AMPERSAND", SDLK_KP_AMPERSAND},
        {"SDLK_KP_DBLAMPERSAND", SDLK_KP_DBLAMPERSAND},
        {"SDLK_KP_VERTICALBAR", SDLK_KP_VERTICALBAR},
        {"SDLK_KP_DBLVERTICALBAR", SDLK_KP_DBLVERTICALBAR},
        {"SDLK_KP_COLON", SDLK_KP_COLON},
        {"SDLK_KP_HASH", SDLK_KP_HASH},
        {"SDLK_KP_SPACE", SDLK_KP_SPACE},
        {"SDLK_KP_AT", SDLK_KP_AT},
        {"SDLK_KP_EXCLAM", SDLK_KP_EXCLAM},
        {"SDLK_KP_MEMSTORE", SDLK_KP_MEMSTORE},
        {"SDLK_KP_MEMRECALL", SDLK_KP_MEMRECALL},
        {"SDLK_KP_MEMCLEAR", SDLK_KP_MEMCLEAR},
        {"SDLK_KP_MEMADD", SDLK_KP_MEMADD},
        {"SDLK_KP_MEMSUBTRACT", SDLK_KP_MEMSUBTRACT},
        {"SDLK_KP_MEMMULTIPLY", SDLK_KP_MEMMULTIPLY},
        {"SDLK_KP_MEMDIVIDE", SDLK_KP_MEMDIVIDE},
        {"SDLK_KP_PLUSMINUS", SDLK_KP_PLUSMINUS},
        {"SDLK_KP_CLEAR", SDLK_KP_CLEAR},
        {"SDLK_KP_CLEARENTRY", SDLK_KP_CLEARENTRY},
        {"SDLK_KP_BINARY", SDLK_KP_BINARY},
        {"SDLK_KP_OCTAL", SDLK_KP_OCTAL},
        {"SDLK_KP_DECIMAL", SDLK_KP_DECIMAL},
        {"SDLK_KP_HEXADECIMAL", SDLK_KP_HEXADECIMAL},
        {"SDLK_LCTRL", SDLK_LCTRL},
        {"SDLK_LSHIFT", SDLK_LSHIFT},
        {"SDLK_LALT", SDLK_LALT},
        {"SDLK_LGUI", SDLK_LGUI},
        {"SDLK_RCTRL", SDLK_RCTRL},
        {"SDLK_RSHIFT", SDLK_RSHIFT},
        {"SDLK_RALT", SDLK_RALT},
        {"SDLK_RGUI", SDLK_RGUI},
        {"SDLK_MODE", SDLK_MODE},
        {"SDLK_AUDIONEXT", SDLK_AUDIONEXT},
        {"SDLK_AUDIOPREV", SDLK_AUDIOPREV},
        {"SDLK_AUDIOSTOP", SDLK_AUDIOSTOP},
        {"SDLK_AUDIOPLAY", SDLK_AUDIOPLAY},
        {"SDLK_AUDIOMUTE", SDLK_AUDIOMUTE},
        {"SDLK_MEDIASELECT", SDLK_MEDIASELECT},
        {"SDLK_WWW", SDLK_WWW},
        {"SDLK_MAIL", SDLK_MAIL},
        {"SDLK_CALCULATOR", SDLK_CALCULATOR},
        {"SDLK_COMPUTER", SDLK_COMPUTER},
        {"SDLK_AC_SEARCH", SDLK_AC_SEARCH},
        {"SDLK_AC_HOME", SDLK_AC_HOME},
        {"SDLK_AC_BACK", SDLK_AC_BACK},
        {"SDLK_AC_FORWARD", SDLK_AC_FORWARD},
        {"SDLK_AC_STOP", SDLK_AC_STOP},
        {"SDLK_AC_REFRESH", SDLK_AC_REFRESH},
        {"SDLK_AC_BOOKMARKS", SDLK_AC_BOOKMARKS},
        {"SDLK_BRIGHTNESSDOWN", SDLK_BRIGHTNESSDOWN},
        {"SDLK_BRIGHTNESSUP", SDLK_BRIGHTNESSUP},
        {"SDLK_DISPLAYSWITCH", SDLK_DISPLAYSWITCH},
        {"SDLK_KBDILLUMTOGGLE", SDLK_KBDILLUMTOGGLE},
        {"SDLK_KBDILLUMDOWN", SDLK_KBDILLUMDOWN},
        {"SDLK_KBDILLUMUP", SDLK_KBDILLUMUP},
        {"SDLK_EJECT", SDLK_EJECT},
        {"SDLK_SLEEP", SDLK_SLEEP},
        {"KMOD_NONE", KMOD_NONE},
        {"KMOD_LSHIFT", KMOD_LSHIFT},
        {"KMOD_RSHIFT", KMOD_RSHIFT},
        {"KMOD_LCTRL", KMOD_LCTRL},
        {"KMOD_RCTRL", KMOD_RCTRL},
        {"KMOD_LALT", KMOD_LALT},
        {"KMOD_RALT", KMOD_RALT},
        {"KMOD_LGUI", KMOD_LGUI},
        {"KMOD_RGUI", KMOD_RGUI},
        {"KMOD_NUM", KMOD_NUM},
        {"KMOD_CAPS", KMOD_CAPS},
        {"KMOD_MODE", KMOD_MODE},
        {"KMOD_RESERVED", KMOD_RESERVED},
        {"KMOD_CTRL", KMOD_CTRL},
        {"KMOD_SHIFT", KMOD_SHIFT},
        {"KMOD_ALT", KMOD_ALT},
        {"KMOD_GUI", KMOD_GUI},

        {NULL, 0}
    };

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_SCANCODE_H_ */
