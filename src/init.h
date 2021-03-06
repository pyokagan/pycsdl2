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
 * \file init.h
 * \brief Bindings for SDL.h
 *
 * Implements bindings for SDL's initialization and shutdown API (SDL.h).
 */
#ifndef _PYCSDL2_INIT_H_
#define _PYCSDL2_INIT_H_
#include <Python.h>
#include <SDL.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \brief Implements csdl2.SDL_Init()
 *
 * \code{.py}
 * SDL_Init(flags: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_Init(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 flags;
    static char *kwlist[] = {"flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT, kwlist, &flags))
        return NULL;

    if (SDL_Init(flags) < 0)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_InitSubSystem()
 *
 * \code{.py}
 * SDL_InitSubSystem(flags: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_InitSubSystem(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 flags;
    static char *kwlist[] = {"flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT, kwlist, &flags))
        return NULL;

    if (SDL_InitSubSystem(flags) < 0)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_QuitSubSystem()
 *
 * \code{.py}
 * SDL_QuitSubSystem(flags: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_QuitSubSystem(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 flags;
    static char *kwlist[] = {"flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT, kwlist, &flags))
        return NULL;

    SDL_QuitSubSystem(flags);

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_WasInit()
 *
 * \code{.py}
 * SDL_WasInit(flags: int) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_WasInit(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 flags;
    static char *kwlist[] = {"flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT, kwlist, &flags))
        return NULL;

    return PyLong_FromUnsignedLong(SDL_WasInit(flags));
}

/**
 * \brief Implements csdl2.SDL_Quit()
 *
 * \code{.py}
 * SDL_Quit() -> None
 * \endcode
 */
static PyObject *
PyCSDL2_Quit(PyObject *module, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    SDL_Quit();

    Py_RETURN_NONE;
}

/**
 * \brief Initializes bindings to SDL.h
 *
 * Adds constants defined in SDL.h to module m.
 *
 * \param m csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initinit(PyObject *m)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_INIT_TIMER", SDL_INIT_TIMER},
        {"SDL_INIT_AUDIO", SDL_INIT_AUDIO},
        {"SDL_INIT_VIDEO", SDL_INIT_VIDEO},
        {"SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK},
        {"SDL_INIT_HAPTIC", SDL_INIT_HAPTIC},
        {"SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER},
        {"SDL_INIT_EVENTS", SDL_INIT_EVENTS},
        {"SDL_INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE},
        {"SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING},
        {NULL, 0}
    };

    if (PyCSDL2_PyModuleAddConstants(m, constants) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_INIT_H_ */
