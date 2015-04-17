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
/*!
 * \file error.h
 * \brief Bindings for SDL_error.h
 *
 * Implements bindings for SDL's error handling API (SDL_error.h).
 */
#ifndef _PYCSDL2_ERROR_H_
#define _PYCSDL2_ERROR_H_
#include <Python.h>
#include <SDL_error.h>
#include "../include/pycsdl2.h"

/**
 * \brief Raises exception with contents of SDL_GetError()
 *
 * Raises the appropriate exception with the contents of SDL_GetError() based
 * on the contents of the error message.
 *
 * * If error string is "Out of memory", raises PyExc_MemoryError.
 *
 * * Or else, raises the generic PyExc_RuntimeError.
 *
 * \returns NULL always.
 */
static PyObject*
PyCSDL2_RaiseSDLError(void)
{
    const char *msg = SDL_GetError();

    if (!strcmp(msg, "Out of memory"))
        PyErr_NoMemory();
    else if (!strcmp(msg, "Error reading from datastream"))
        PyErr_SetString(PyExc_OSError, msg);
    else if (!strcmp(msg, "Error writing to datastream"))
        PyErr_SetString(PyExc_OSError, msg);
    else if (!strcmp(msg, "Error seeking in datastream"))
        PyErr_SetString(PyExc_OSError, msg);
    else
        PyErr_SetString(PyExc_RuntimeError, msg);
    return NULL;
}

#endif /* _PYCSDL2_ERROR_H_ */
