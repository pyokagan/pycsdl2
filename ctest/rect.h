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
 * \file rect.h
 * \brief Tests for csdl2's SDL_rect bindings.
 */
#ifndef _PYCSDL2TEST_RECT_H_
#define _PYCSDL2TEST_RECT_H_
#include <Python.h>
#include <SDL_rect.h>
#include "../include/pycsdl2.h"

/**
 * \brief Create a new PyCSDL2_Point object.
 *
 * \code{.py}
 * point() -> SDL_Point
 * \endcode
 */
static PyObject *
PyCSDL2Test_Point(PyObject *module, PyObject *args)
{
    SDL_Point p = {3, 4};

    return PyCSDL2_PointCreate(&p);
}

/**
 * \brief Sets the "x" field of the SDL_Point to 42.
 *
 * \code{.py}
 * point_set_x(point: SDL_Point) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_PointSetX(PyObject *module, PyObject *args)
{
    SDL_Point *p;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_PointPtr, &p))
        return NULL;

    p->x = 42;

    Py_RETURN_NONE;
}

/**
 * \brief Create a new PyCSDL2_Rect object.
 *
 * \code{.py}
 * rect() -> SDL_Rect
 * \endcode
 */
static PyObject *
PyCSDL2Test_Rect(PyObject *module, PyObject *args)
{
    SDL_Rect r = {1, 2, 3, 4};

    return PyCSDL2_RectCreate(&r);
}

/**
 * \brief Sets the "x" field of the SDL_Rect to 42.
 *
 * \code{.py}
 * rect_set_x(rect: SDL_Rect) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_RectSetX(PyObject *module, PyObject *args)
{
    SDL_Rect *r;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_RectPtr, &r))
        return NULL;

    r->x = 42;

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_EVENTS_H_ */
