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
 * \file surface.h
 * \brief Tests for csdl2's SDL_surface bindings.
 */
#ifndef _PYCSDL2TEST_SURFACE_H_
#define _PYCSDL2TEST_SURFACE_H_
#include <Python.h>
#include <SDL_surface.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_Surface object.
 *
 * \code{.py}
 * surface() -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2Test_Surface(PyObject *module, PyObject *args)
{
    SDL_Surface *sf;

    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    sf = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    if (!sf) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    return PyCSDL2_SurfaceCreate(sf, NULL);
}

/**
 * \brief Creates a PyCSDL2_Surface object from a pixels buffer.
 *
 * \code{.py}
 * surface_from(pixels: buffer) -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2Test_SurfaceFrom(PyObject *module, PyObject *args)
{
    Py_buffer pixels;
    SDL_Surface *sf;
    PyObject *out;

    if (!PyArg_ParseTuple(args, "y*", &pixels))
        return NULL;

    sf = SDL_CreateRGBSurfaceFrom(pixels.buf, 32, 32, 32, 32 * 4, 0, 0, 0, 0);
    if (!sf) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    out = PyCSDL2_SurfaceCreate(sf, pixels.obj);
    PyBuffer_Release(&pixels);
    return out;
}

/**
 * \brief Fills the SDL_Surface pixels with white
 *
 * \code{.py}
 * surface_fill(sf: SDL_Surface) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_SurfaceFill(PyObject *module, PyObject *args)
{
    SDL_Surface *sf;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_SurfacePtr, &sf))
        return NULL;

    memset(sf->pixels, 255, sf->pitch * sf->h);

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_SURFACE_H_ */
