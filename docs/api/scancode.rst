.. _scancode-constants:

Scancode Constants
==================
.. currentmodule:: csdl2

These constants are used to represent the physical location of a keyboard key
on the keybord. They are used in many places, such as the
:attr:`SDL_KeyboardEvent.keysym` attribute.

.. data:: SDL_SCANCODE_UNKNOWN

.. data:: SDL_SCANCODE_A

.. data:: SDL_SCANCODE_B

.. data:: SDL_SCANCODE_C

.. data:: SDL_SCANCODE_D

.. data:: SDL_SCANCODE_E

.. data:: SDL_SCANCODE_F

.. data:: SDL_SCANCODE_G

.. data:: SDL_SCANCODE_H

.. data:: SDL_SCANCODE_I

.. data:: SDL_SCANCODE_J

.. data:: SDL_SCANCODE_K

.. data:: SDL_SCANCODE_L

.. data:: SDL_SCANCODE_M

.. data:: SDL_SCANCODE_N

.. data:: SDL_SCANCODE_O

.. data:: SDL_SCANCODE_P

.. data:: SDL_SCANCODE_Q

.. data:: SDL_SCANCODE_R

.. data:: SDL_SCANCODE_S

.. data:: SDL_SCANCODE_T

.. data:: SDL_SCANCODE_U

.. data:: SDL_SCANCODE_V

.. data:: SDL_SCANCODE_W

.. data:: SDL_SCANCODE_X

.. data:: SDL_SCANCODE_Y

.. data:: SDL_SCANCODE_Z

.. data:: SDL_SCANCODE_1

.. data:: SDL_SCANCODE_2

.. data:: SDL_SCANCODE_3

.. data:: SDL_SCANCODE_4

.. data:: SDL_SCANCODE_5

.. data:: SDL_SCANCODE_6

.. data:: SDL_SCANCODE_7

.. data:: SDL_SCANCODE_8

.. data:: SDL_SCANCODE_9

.. data:: SDL_SCANCODE_0

.. data:: SDL_SCANCODE_RETURN

.. data:: SDL_SCANCODE_ESCAPE

.. data:: SDL_SCANCODE_BACKSPACE

.. data:: SDL_SCANCODE_TAB

.. data:: SDL_SCANCODE_SPACE

.. data:: SDL_SCANCODE_MINUS

.. data:: SDL_SCANCODE_EQUALS

.. data:: SDL_SCANCODE_LEFTBRACKET

.. data:: SDL_SCANCODE_RIGHTBRACKET

.. data:: SDL_SCANCODE_BACKSLASH

   Located at the lower left of the return key on ISO keyboards and at the
   right end of the QWERTY row on ANSI keyboards.  Produces REVERSE SOLIDUS
   (backslash) and VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL
   LINE in a UK Mac layout, NUMBER SIGN and TILDE in a UK Windows layout,
   DOLLAR SIGN and POUND SIGN in a Swiss German layout, NUMBER SIGN and
   APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a French Mac
   layout, and ASTERISK and MICRO SIGN in a French Windows layout.

.. data:: SDL_SCANCODE_NONUSHASH

   ISO USB keyboards actually use this code instead of 49 for the same key, but
   all OSes I've seen treat the two codes identically. So, as an implementor,
   unless your keyboard generates both of those codes and your OS treats them
   differently, you should generate SDL_SCANCODE_BACKSLASH instead of this
   code. As a user, you should not rely on this code because SDL will never
   generate it with most (all?) keyboards.

.. data:: SDL_SCANCODE_SEMICOLON

.. data:: SDL_SCANCODE_APOSTROPHE

.. data:: SDL_SCANCODE_GRAVE

   Located in the top left corner (on both ANSI and ISO keyboards). Produces
   GRAVE ACCENT and TILDE in a US Windows layout and in US and UK Mac layouts
   on ANSI keyboards, GRAVE ACCENT and NOT SIGN in a UK Windows layout, SECTION
   SIGN and PLUS-MINUS SIGN in US and UK Mac layouts on ISO keyboards, SECTION
   SIGN and DEGREE SIGN in a Swiss German layout (Mac: only on ISO keyboards),
   CIRCUMFLEX ACCENT and DEGREE SIGN in a German layout (Mac: only on ISO
   keyboards), SUPERSCRIPT TWO and TILDE in a French Windows layout, COMMERCIAL
   AT and NUMBER SIGN in a French Mac layout on ISO keyboards, and LESS-THAN
   SIGN and GREATER-THAN SIGN in a Swiss German, German, or French Mac layout
   on ANSI keyboards.

.. data:: SDL_SCANCODE_COMMA

.. data:: SDL_SCANCODE_PERIOD

.. data:: SDL_SCANCODE_SLASH

.. data:: SDL_SCANCODE_CAPSLOCK

.. data:: SDL_SCANCODE_F1

.. data:: SDL_SCANCODE_F2

.. data:: SDL_SCANCODE_F3

.. data:: SDL_SCANCODE_F4

.. data:: SDL_SCANCODE_F5

.. data:: SDL_SCANCODE_F6

.. data:: SDL_SCANCODE_F7

.. data:: SDL_SCANCODE_F8

.. data:: SDL_SCANCODE_F9

.. data:: SDL_SCANCODE_F10

.. data:: SDL_SCANCODE_F11

.. data:: SDL_SCANCODE_F12

.. data:: SDL_SCANCODE_PRINTSCREEN

.. data:: SDL_SCANCODE_SCROLLLOCK

.. data:: SDL_SCANCODE_PAUSE

.. data:: SDL_SCANCODE_INSERT

   Insert on PC, help on some Mac keyboards (but does send code 73, not 117)

.. data:: SDL_SCANCODE_HOME

.. data:: SDL_SCANCODE_PAGEUP

.. data:: SDL_SCANCODE_DELETE

.. data:: SDL_SCANCODE_END

.. data:: SDL_SCANCODE_PAGEDOWN

.. data:: SDL_SCANCODE_RIGHT

.. data:: SDL_SCANCODE_LEFT

.. data:: SDL_SCANCODE_DOWN

.. data:: SDL_SCANCODE_UP

.. data:: SDL_SCANCODE_NUMLOCKCLEAR

   Num lock on PC, clear on Mac keyboards

.. data:: SDL_SCANCODE_KP_DIVIDE

.. data:: SDL_SCANCODE_KP_MULTIPLY

.. data:: SDL_SCANCODE_KP_MINUS

.. data:: SDL_SCANCODE_KP_PLUS

.. data:: SDL_SCANCODE_KP_ENTER

.. data:: SDL_SCANCODE_KP_1

.. data:: SDL_SCANCODE_KP_2

.. data:: SDL_SCANCODE_KP_3

.. data:: SDL_SCANCODE_KP_4

.. data:: SDL_SCANCODE_KP_5

.. data:: SDL_SCANCODE_KP_6

.. data:: SDL_SCANCODE_KP_7

.. data:: SDL_SCANCODE_KP_8

.. data:: SDL_SCANCODE_KP_9

.. data:: SDL_SCANCODE_KP_0

.. data:: SDL_SCANCODE_KP_PERIOD

.. data:: SDL_SCANCODE_NONUSBACKSLASH

   This is the additional key that ISO keyboards have over ANSI ones, located
   between left shift and Y.  Produces GRAVE ACCENT and TILDE in a US or UK Mac
   layout, REVERSE SOLIDUS (backslash) and VERTICAL LINE in a US or UK Windows
   layout, and LESS-THAN SIGN and GREATER-THAN SIGN in a Swiss German, German,
   or French layout.

.. data:: SDL_SCANCODE_APPLICATION

   Windows contextual menu, compose.

.. data:: SDL_SCANCODE_POWER

   The USB document says this is a status flag, not a physical key - but some
   Mac keyboards do have a power key.

.. data:: SDL_SCANCODE_KP_EQUALS

.. data:: SDL_SCANCODE_F13

.. data:: SDL_SCANCODE_F14

.. data:: SDL_SCANCODE_F15

.. data:: SDL_SCANCODE_F16

.. data:: SDL_SCANCODE_F17

.. data:: SDL_SCANCODE_F18

.. data:: SDL_SCANCODE_F19

.. data:: SDL_SCANCODE_F20

.. data:: SDL_SCANCODE_F21

.. data:: SDL_SCANCODE_F22

.. data:: SDL_SCANCODE_F23

.. data:: SDL_SCANCODE_F24

.. data:: SDL_SCANCODE_EXECUTE

.. data:: SDL_SCANCODE_HELP

.. data:: SDL_SCANCODE_MENU

.. data:: SDL_SCANCODE_SELECT

.. data:: SDL_SCANCODE_STOP

.. data:: SDL_SCANCODE_AGAIN

   Redo.

.. data:: SDL_SCANCODE_UNDO

.. data:: SDL_SCANCODE_CUT

.. data:: SDL_SCANCODE_COPY

.. data:: SDL_SCANCODE_PASTE

.. data:: SDL_SCANCODE_FIND

.. data:: SDL_SCANCODE_MUTE

.. data:: SDL_SCANCODE_VOLUMEUP

.. data:: SDL_SCANCODE_VOLUMEDOWN

.. data:: SDL_SCANCODE_KP_COMMA

.. data:: SDL_SCANCODE_KP_EQUALSAS400

.. data:: SDL_SCANCODE_INTERNATIONAL1

   Used on Asian keyboards, see footnotes in USB doc.

.. data:: SDL_SCANCODE_INTERNATIONAL2

.. data:: SDL_SCANCODE_INTERNATIONAL3

   Yen.

.. data:: SDL_SCANCODE_INTERNATIONAL4

.. data:: SDL_SCANCODE_INTERNATIONAL5

.. data:: SDL_SCANCODE_INTERNATIONAL6

.. data:: SDL_SCANCODE_INTERNATIONAL7

.. data:: SDL_SCANCODE_INTERNATIONAL8

.. data:: SDL_SCANCODE_INTERNATIONAL9

.. data:: SDL_SCANCODE_LANG1

   Hangul/English toggle.

.. data:: SDL_SCANCODE_LANG2

   Hanja conversion.

.. data:: SDL_SCANCODE_LANG3

   Katakana.

.. data:: SDL_SCANCODE_LANG4

   Hiragana.

.. data:: SDL_SCANCODE_LANG5

   Zenkaku/Hankaku

.. data:: SDL_SCANCODE_LANG6

.. data:: SDL_SCANCODE_LANG7

.. data:: SDL_SCANCODE_LANG8

.. data:: SDL_SCANCODE_LANG9

.. data:: SDL_SCANCODE_ALTERASE

   Erase-Eaze

.. data:: SDL_SCANCODE_SYSREQ

.. data:: SDL_SCANCODE_CANCEL

.. data:: SDL_SCANCODE_CLEAR

.. data:: SDL_SCANCODE_PRIOR

.. data:: SDL_SCANCODE_RETURN2

.. data:: SDL_SCANCODE_SEPARATOR

.. data:: SDL_SCANCODE_OUT

.. data:: SDL_SCANCODE_OPER

.. data:: SDL_SCANCODE_CLEARAGAIN

.. data:: SDL_SCANCODE_CRSEL

.. data:: SDL_SCANCODE_EXSEL

.. data:: SDL_SCANCODE_KP_00

.. data:: SDL_SCANCODE_KP_000

.. data:: SDL_SCANCODE_THOUSANDSSEPARATOR

.. data:: SDL_SCANCODE_DECIMALSEPARATOR

.. data:: SDL_SCANCODE_CURRENCYUNIT

.. data:: SDL_SCANCODE_CURRENCYSUBUNIT

.. data:: SDL_SCANCODE_KP_LEFTPAREN

.. data:: SDL_SCANCODE_KP_RIGHTPAREN

.. data:: SDL_SCANCODE_KP_LEFTBRACE

.. data:: SDL_SCANCODE_KP_RIGHTBRACE

.. data:: SDL_SCANCODE_KP_TAB

.. data:: SDL_SCANCODE_KP_BACKSPACE

.. data:: SDL_SCANCODE_KP_A

.. data:: SDL_SCANCODE_KP_B

.. data:: SDL_SCANCODE_KP_C

.. data:: SDL_SCANCODE_KP_D

.. data:: SDL_SCANCODE_KP_E

.. data:: SDL_SCANCODE_KP_F

.. data:: SDL_SCANCODE_KP_XOR

.. data:: SDL_SCANCODE_KP_POWER

.. data:: SDL_SCANCODE_KP_PERCENT

.. data:: SDL_SCANCODE_KP_LESS

.. data:: SDL_SCANCODE_KP_GREATER

.. data:: SDL_SCANCODE_KP_AMPERSAND

.. data:: SDL_SCANCODE_KP_DBLAMPERSAND

.. data:: SDL_SCANCODE_KP_VERTICALBAR

.. data:: SDL_SCANCODE_KP_DBLVERTICALBAR

.. data:: SDL_SCANCODE_KP_COLON

.. data:: SDL_SCANCODE_KP_HASH

.. data:: SDL_SCANCODE_KP_SPACE

.. data:: SDL_SCANCODE_KP_AT

.. data:: SDL_SCANCODE_KP_EXCLAM

.. data:: SDL_SCANCODE_KP_MEMSTORE

.. data:: SDL_SCANCODE_KP_MEMRECALL

.. data:: SDL_SCANCODE_KP_MEMCLEAR

.. data:: SDL_SCANCODE_KP_MEMADD

.. data:: SDL_SCANCODE_KP_MEMSUBTRACT

.. data:: SDL_SCANCODE_KP_MEMMULTIPLY

.. data:: SDL_SCANCODE_KP_MEMDIVIDE

.. data:: SDL_SCANCODE_KP_PLUSMINUS

.. data:: SDL_SCANCODE_KP_CLEAR

.. data:: SDL_SCANCODE_KP_CLEARENTRY

.. data:: SDL_SCANCODE_KP_BINARY

.. data:: SDL_SCANCODE_KP_OCTAL

.. data:: SDL_SCANCODE_KP_DECIMAL

.. data:: SDL_SCANCODE_KP_HEXADECIMAL

.. data:: SDL_SCANCODE_LCTRL

.. data:: SDL_SCANCODE_LSHIFT

.. data:: SDL_SCANCODE_LALT

   Alt, option.

.. data:: SDL_SCANCODE_LGUI

   Windows, command (apple), meta

.. data:: SDL_SCANCODE_RCTRL

.. data:: SDL_SCANCODE_RSHIFT

.. data:: SDL_SCANCODE_RALT

   Alt gr, option.

.. data:: SDL_SCANCODE_RGUI

   Windows, command (apple), meta.

.. data:: SDL_SCANCODE_MODE

.. data:: SDL_SCANCODE_AUDIONEXT

.. data:: SDL_SCANCODE_AUDIOPREV

.. data:: SDL_SCANCODE_AUDIOSTOP

.. data:: SDL_SCANCODE_AUDIOPLAY

.. data:: SDL_SCANCODE_AUDIOMUTE

.. data:: SDL_SCANCODE_MEDIASELECT

.. data:: SDL_SCANCODE_WWW

.. data:: SDL_SCANCODE_MAIL

.. data:: SDL_SCANCODE_CALCULATOR

.. data:: SDL_SCANCODE_COMPUTER

.. data:: SDL_SCANCODE_AC_SEARCH

.. data:: SDL_SCANCODE_AC_HOME

.. data:: SDL_SCANCODE_AC_BACK

.. data:: SDL_SCANCODE_AC_FORWARD

.. data:: SDL_SCANCODE_AC_STOP

.. data:: SDL_SCANCODE_AC_REFRESH

.. data:: SDL_SCANCODE_AC_BOOKMARKS

.. data:: SDL_SCANCODE_BRIGHTNESSDOWN

.. data:: SDL_SCANCODE_BRIGHTNESSUP

.. data:: SDL_SCANCODE_DISPLAYSWITCH

   Display mirroring/dual display switch, video mode switch.

.. data:: SDL_SCANCODE_KBDILLUMTOGGLE

.. data:: SDL_SCANCODE_KBDILLUMDOWN

.. data:: SDL_SCANCODE_KBDILLUMUP

.. data:: SDL_SCANCODE_EJECT

.. data:: SDL_SCANCODE_SLEEP

.. data:: SDL_SCANCODE_APP1

.. data:: SDL_SCANCODE_APP2

.. data:: SDL_NUM_SCANCODES

   Not a key, just marks the number of scancodes for array bounds.
