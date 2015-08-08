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
 * \file rwops.h
 * \brief Tests for csdl2's SDL_rwops bindings.
 */
#ifndef _PYCSDL2TEST_RWOPS_H_
#define _PYCSDL2TEST_RWOPS_H_
#include <Python.h>
#include <SDL_rwops.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_RWops object.
 *
 * \code{.py}
 * rwops() -> SDL_RWops
 * \endcode
 */
static PyObject *
PyCSDL2Test_RWops(PyObject *module, PyObject *args)
{
    SDL_RWops *rw;

    rw = SDL_AllocRW();
    if (!rw)
        return PyErr_NoMemory();

    /*
     * PyCSDL2_RWopsPtr calls SDL_RWops.close if it is not NULL on destruction.
     * Ensure that SDL_RWops.close is set to NULL.
     */
    memset(rw, 0, sizeof(SDL_RWops));

    rw->type = 42;

    return PyCSDL2_RWopsCreate(rw);
}

/**
 * \brief Sets the "type" field of the SDL_RWops to 42.
 *
 * \code{.py}
 * rwops_set_type(rw: SDL_RWops) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_RWopsSetType(PyObject *module, PyObject *args)
{
    SDL_RWops *rw;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_RWopsPtr, &rw))
        return NULL;

    rw->type = 42;

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_RWOPS_H_ */
