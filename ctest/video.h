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
 * \file video.h
 * \brief Tests for csdl2's SDL_video bindings.
 */
#ifndef _PYCSDL2TEST_VIDEO_H_
#define _PYCSDL2TEST_VIDEO_H_
#include <Python.h>
#include <SDL_video.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_Window object.
 *
 * \code{.py}
 * window() -> SDL_Window
 * \endcode
 */
static PyObject *
PyCSDL2Test_Window(PyObject *module, PyObject *args)
{
    SDL_Window *window;

    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    window = SDL_CreateWindow("foo", -32, -32, 32, 32, SDL_WINDOW_HIDDEN);
    if (!window) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    return PyCSDL2_WindowCreate(window);
}

/**
 * \brief Sets the title of the SDL_Window to "bar"
 *
 * \code{.py}
 * window_set_title(win: SDL_Window) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_WindowSetTitle(PyObject *module, PyObject *args)
{
    SDL_Window *window;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_WindowPtr, &window))
        return NULL;

    SDL_SetWindowTitle(window, "bar");

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_VIDEO_H_ */
