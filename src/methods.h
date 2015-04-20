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
 * \file methods.h
 * \brief csdl2 list of module methods.
 */
#ifndef _PYCSDL2_METHODS_H_
#define _PYCSDL2_METHODS_H_
#include <Python.h>
#include "../include/pycsdl2.h"
#include "distutils.h"
#include "error.h"
#include "events.h"
#include "init.h"
#include "video.h"

/**
 * \brief csdl2 methods definitions.
 *
 * \sa PyCSDL2_Module
 */
static PyMethodDef PyCSDL2_Methods[] = {

    /* distutils.h */

    {"PyCSDL2_GetSystemSDL",
     (PyCFunction) PyCSDL2_GetSystemSDL,
     METH_VARARGS | METH_KEYWORDS,
     "PyCSDL2_GetSystemSDL() -> dict or None\n"
     "\n"
     "Returns a dict with the keys 'include_dirs', 'define_macros',\n"
     "'undef_macros', 'extra_compile_args', 'library_dirs', 'libraries',\n"
     "'runtime_library_dirs' and 'extra_link_args' corresponding to\n"
     "attributes of the same name in distutils.extension.Extension which\n"
     "were used to link csdl2 against the system's SDL2 library. Returns\n"
     "None if csdl2 was statically linked to SDL2."},

    /* events.h */

    /* init.h */

    {"SDL_Init",
     (PyCFunction) PyCSDL2_Init,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_Init(flags: int) -> None\n"
     "\n"
     "Initializes the subsystems specified by `flags`, which is one or more\n"
     "of the following constants OR'ed together:\n"
     "\n"
     "* SDL_INIT_TIMER\n"
     "* SDL_INIT_AUDIO\n"
     "* SDL_INIT_VIDEO (implies SDL_INIT_EVENTS)\n"
     "* SDL_INIT_JOYSTICK (implies SDL_INIT_EVENTS)\n"
     "* SDL_INIT_HAPTIC\n"
     "* SDL_INIT_GAMECONTROLLER (implies SDL_INIT_JOYSTICK)\n"
     "* SDL_INIT_EVENTS\n"
     "\n"
     "Alternatively, pass SDL_INIT_EVERYTHING to initialize all subsystems.\n"
     "\n"
     "Unless the SDL_INIT_NOPARACHUTE flag is set, it will install cleanup\n"
     "signal handlers for some commonly ignored fatal signals like SIGSEGV.\n"
    },

    /* video.h */

    {"SDL_CreateWindow",
     (PyCFunction) PyCSDL2_CreateWindow,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateWindow(title: str, x: int, y: int, w: int, h: int,\n"
     "                 flags: int) -> SDL_Window\n"
     "\n"
     "Create a window with the specified `title`, position (`x`, `y`),\n"
     "dimensions `w` x `h`, and flags `flags`.\n"
     "\n"
     "`flags` can be one or more of following OR'ed together:\n"
     "`SDL_WINDOW_FULLSCREEN`, `SDL_WINDOW_OPENGL`, `SDL_WINDOW_SHOWN`,\n"
     "`SDL_WINDOW_HIDDEN`, `SDL_WINDOW_BORDERLESS`, `SDL_WINDOW_RESIZABLE`,\n"
     "`SDL_WINDOW_RESIZABLE`, `SDL_WINDOW_MINIMIZED`,\n"
     "`SDL_WINDOW_MAXIMIZED`, `SDL_WINDOW_INPUT_GRABBED`,\n"
     "`SDL_WINDOW_INPUT_FOCUS`, `SDL_WINDOW_MOUSE_FOCUS`,\n"
     "`SDL_WINDOW_FULLSCREEN_DESKTOP`.\n"},

    /* End */
    {0}
};

#endif /* _PYCSDL2_METHODS_H_ */
