Keycode and Key Modifier Constants
==================================
.. currentmodule:: csdl2

.. _keycode-constants:

Keycode Constants
-----------------
These constants are mapped to the current layout of the keyboard and correlate
to one of the :ref:`scancode-constants`. The scancode identifies the location
of a key press and the corresponding keycode gives that key press meaning in
the context of the current keyboard layout.

.. data:: SDLK_UNKNOWN

.. data:: SDLK_RETURN

.. data:: SDLK_ESCAPE

.. data:: SDLK_BACKSPACE

.. data:: SDLK_TAB

.. data:: SDLK_SPACE

.. data:: SDLK_EXCLAIM

.. data:: SDLK_QUOTEDBL

.. data:: SDLK_HASH

.. data:: SDLK_PERCENT

.. data:: SDLK_DOLLAR

.. data:: SDLK_AMPERSAND

.. data:: SDLK_QUOTE

.. data:: SDLK_LEFTPAREN

.. data:: SDLK_RIGHTPAREN

.. data:: SDLK_ASTERISK

.. data:: SDLK_PLUS

.. data:: SDLK_COMMA

.. data:: SDLK_MINUS

.. data:: SDLK_PERIOD

.. data:: SDLK_SLASH

.. data:: SDLK_0

.. data:: SDLK_1

.. data:: SDLK_2

.. data:: SDLK_3

.. data:: SDLK_4

.. data:: SDLK_5

.. data:: SDLK_6

.. data:: SDLK_7

.. data:: SDLK_8

.. data:: SDLK_9

.. data:: SDLK_COLON

.. data:: SDLK_SEMICOLON

.. data:: SDLK_LESS

.. data:: SDLK_EQUALS

.. data:: SDLK_GREATER

.. data:: SDLK_QUESTION

.. data:: SDLK_AT

.. data:: SDLK_LEFTBRACKET

.. data:: SDLK_BACKSLASH

.. data:: SDLK_RIGHTBRACKET

.. data:: SDLK_CARET

.. data:: SDLK_UNDERSCORE

.. data:: SDLK_BACKQUOTE

.. data:: SDLK_a

.. data:: SDLK_b

.. data:: SDLK_c

.. data:: SDLK_d

.. data:: SDLK_e

.. data:: SDLK_f

.. data:: SDLK_g

.. data:: SDLK_h

.. data:: SDLK_i

.. data:: SDLK_j

.. data:: SDLK_k

.. data:: SDLK_l

.. data:: SDLK_m

.. data:: SDLK_n

.. data:: SDLK_o

.. data:: SDLK_p

.. data:: SDLK_q

.. data:: SDLK_r

.. data:: SDLK_s

.. data:: SDLK_t

.. data:: SDLK_u

.. data:: SDLK_v

.. data:: SDLK_w

.. data:: SDLK_x

.. data:: SDLK_y

.. data:: SDLK_z

.. data:: SDLK_CAPSLOCK

.. data:: SDLK_F1

.. data:: SDLK_F2

.. data:: SDLK_F3

.. data:: SDLK_F4

.. data:: SDLK_F5

.. data:: SDLK_F6

.. data:: SDLK_F7

.. data:: SDLK_F8

.. data:: SDLK_F9

.. data:: SDLK_F10

.. data:: SDLK_F11

.. data:: SDLK_F12

.. data:: SDLK_PRINTSCREEN

.. data:: SDLK_SCROLLLOCK

.. data:: SDLK_PAUSE

.. data:: SDLK_INSERT

.. data:: SDLK_HOME

.. data:: SDLK_PAGEUP

.. data:: SDLK_DELETE

.. data:: SDLK_END

.. data:: SDLK_PAGEDOWN

.. data:: SDLK_RIGHT

.. data:: SDLK_LEFT

.. data:: SDLK_DOWN

.. data:: SDLK_UP

.. data:: SDLK_NUMLOCKCLEAR

.. data:: SDLK_KP_DIVIDE

.. data:: SDLK_KP_MULTIPLY

.. data:: SDLK_KP_MINUS

.. data:: SDLK_KP_PLUS

.. data:: SDLK_KP_ENTER

.. data:: SDLK_KP_1

.. data:: SDLK_KP_2

.. data:: SDLK_KP_3

.. data:: SDLK_KP_4

.. data:: SDLK_KP_5

.. data:: SDLK_KP_6

.. data:: SDLK_KP_7

.. data:: SDLK_KP_8

.. data:: SDLK_KP_9

.. data:: SDLK_KP_0

.. data:: SDLK_KP_PERIOD

.. data:: SDLK_APPLICATION

.. data:: SDLK_POWER

.. data:: SDLK_KP_EQUALS

.. data:: SDLK_F13

.. data:: SDLK_F14

.. data:: SDLK_F15

.. data:: SDLK_F16

.. data:: SDLK_F17

.. data:: SDLK_F18

.. data:: SDLK_F19

.. data:: SDLK_F20

.. data:: SDLK_F21

.. data:: SDLK_F22

.. data:: SDLK_F23

.. data:: SDLK_F24

.. data:: SDLK_EXECUTE

.. data:: SDLK_HELP

.. data:: SDLK_MENU

.. data:: SDLK_SELECT

.. data:: SDLK_STOP

.. data:: SDLK_AGAIN

.. data:: SDLK_UNDO

.. data:: SDLK_CUT

.. data:: SDLK_COPY

.. data:: SDLK_PASTE

.. data:: SDLK_FIND

.. data:: SDLK_MUTE

.. data:: SDLK_VOLUMEUP

.. data:: SDLK_VOLUMEDOWN

.. data:: SDLK_KP_COMMA

.. data:: SDLK_KP_EQUALSAS400

.. data:: SDLK_ALTERASE

.. data:: SDLK_SYSREQ

.. data:: SDLK_CANCEL

.. data:: SDLK_CLEAR

.. data:: SDLK_PRIOR

.. data:: SDLK_RETURN2

.. data:: SDLK_SEPARATOR

.. data:: SDLK_OUT

.. data:: SDLK_OPER

.. data:: SDLK_CLEARAGAIN

.. data:: SDLK_CRSEL

.. data:: SDLK_EXSEL

.. data:: SDLK_KP_00

.. data:: SDLK_KP_000

.. data:: SDLK_THOUSANDSSEPARATOR

.. data:: SDLK_DECIMALSEPARATOR

.. data:: SDLK_CURRENCYUNIT

.. data:: SDLK_CURRENCYSUBUNIT

.. data:: SDLK_KP_LEFTPAREN

.. data:: SDLK_KP_RIGHTPAREN

.. data:: SDLK_KP_LEFTBRACE

.. data:: SDLK_KP_RIGHTBRACE

.. data:: SDLK_KP_TAB

.. data:: SDLK_KP_BACKSPACE

.. data:: SDLK_KP_A

.. data:: SDLK_KP_B

.. data:: SDLK_KP_C

.. data:: SDLK_KP_D

.. data:: SDLK_KP_E

.. data:: SDLK_KP_F

.. data:: SDLK_KP_XOR

.. data:: SDLK_KP_POWER

.. data:: SDLK_KP_PERCENT

.. data:: SDLK_KP_LESS

.. data:: SDLK_KP_GREATER

.. data:: SDLK_KP_AMPERSAND

.. data:: SDLK_KP_DBLAMPERSAND

.. data:: SDLK_KP_VERTICALBAR

.. data:: SDLK_KP_DBLVERTICALBAR

.. data:: SDLK_KP_COLON

.. data:: SDLK_KP_HASH

.. data:: SDLK_KP_SPACE

.. data:: SDLK_KP_AT

.. data:: SDLK_KP_EXCLAM

.. data:: SDLK_KP_MEMSTORE

.. data:: SDLK_KP_MEMRECALL

.. data:: SDLK_KP_MEMCLEAR

.. data:: SDLK_KP_MEMADD

.. data:: SDLK_KP_MEMSUBTRACT

.. data:: SDLK_KP_MEMMULTIPLY

.. data:: SDLK_KP_MEMDIVIDE

.. data:: SDLK_KP_PLUSMINUS

.. data:: SDLK_KP_CLEAR

.. data:: SDLK_KP_CLEARENTRY

.. data:: SDLK_KP_BINARY

.. data:: SDLK_KP_OCTAL

.. data:: SDLK_KP_DECIMAL

.. data:: SDLK_KP_HEXADECIMAL

.. data:: SDLK_LCTRL

.. data:: SDLK_LSHIFT

.. data:: SDLK_LALT

.. data:: SDLK_LGUI

.. data:: SDLK_RCTRL

.. data:: SDLK_RSHIFT

.. data:: SDLK_RALT

.. data:: SDLK_RGUI

.. data:: SDLK_MODE

.. data:: SDLK_AUDIONEXT

.. data:: SDLK_AUDIOPREV

.. data:: SDLK_AUDIOSTOP

.. data:: SDLK_AUDIOPLAY

.. data:: SDLK_AUDIOMUTE

.. data:: SDLK_MEDIASELECT

.. data:: SDLK_WWW

.. data:: SDLK_MAIL

.. data:: SDLK_CALCULATOR

.. data:: SDLK_COMPUTER

.. data:: SDLK_AC_SEARCH

.. data:: SDLK_AC_HOME

.. data:: SDLK_AC_BACK

.. data:: SDLK_AC_FORWARD

.. data:: SDLK_AC_STOP

.. data:: SDLK_AC_REFRESH

.. data:: SDLK_AC_BOOKMARKS

.. data:: SDLK_BRIGHTNESSDOWN

.. data:: SDLK_BRIGHTNESSUP

.. data:: SDLK_DISPLAYSWITCH

.. data:: SDLK_KBDILLUMTOGGLE

.. data:: SDLK_KBDILLUMDOWN

.. data:: SDLK_KBDILLUMUP

.. data:: SDLK_EJECT

.. data:: SDLK_SLEEP

.. _key-modifier-constants:

Key Modifier Constants
----------------------
Key Modifier masks. These constants may be OR'd together.

.. data:: KMOD_NONE

   0 (no modifier is applicable)

.. data:: KMOD_LSHIFT

   The left Shift key is down.

.. data:: KMOD_RSHIFT

   The right Shift key is down.

.. data:: KMOD_LCTRL

   The left Ctrl (Control) key is down.

.. data:: KMOD_RCTRL

   The right Ctrl (Control) key is down.

.. data:: KMOD_LALT

   The left Alt key is down.

.. data:: KMOD_RALT

   The right Alt key is down.

.. data:: KMOD_LGUI

   The left GUI key (often the Windows key) is down.

.. data:: KMOD_RGUI

   The right GUI key (often the Windows key) is down.

.. data:: KMOD_NUM

   The Num lock key (may be located on an extended keypad) is down.

.. data:: KMOD_CAPS

   The Caps Lock key is down.

.. data:: KMOD_MODE

   The AltGr key is down.

.. data:: KMOD_CTRL

   ``(KMOD_LCTRL | KMOD_RCTRL)``

.. data:: KMOD_SHIFT

   ``(KMOD_LSHIFT | KMOD_RSHIFT)``

.. data:: KMOD_ALT

   ``(KMOD_LALT | KMOD_RALT)``

.. data:: KMOD_GUI

   ``(KMOD_LGUI | KMOD_RGUI)``
