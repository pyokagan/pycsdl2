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
 * \file pixels.h
 * \brief Tests for csdl2's SDL_pixels bindings.
 */
#ifndef _PYCSDL2TEST_PIXELS_H_
#define _PYCSDL2TEST_PIXELS_H_
#include <Python.h>
#include <SDL_pixels.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_Palette object.
 *
 * \code{.py}
 * palette() -> SDL_Palette
 * \endcode
 */
static PyObject *
PyCSDL2Test_Palette(PyObject *module, PyObject *args)
{
    SDL_Palette *plt;

    plt = SDL_AllocPalette(2);
    if (!plt)
        return PyErr_NoMemory();

    return PyCSDL2_PaletteCreate(plt);
}

/**
 * \brief Sets the "ncolors" field of the SDL_Palette to 42.
 *
 * \code{.py}
 * palette_set_ncolors(plt: SDL_Palette) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_PaletteSetNColors(PyObject *module, PyObject *args)
{
    SDL_Palette *plt;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_PalettePtr, &plt))
        return NULL;

    plt->ncolors = 42;

    Py_RETURN_NONE;
}

/**
 * \brief Creates a PyCSDL2_PixelFormat object.
 *
 * \code{.py}
 * pixel_format() -> SDL_PixelFormat
 * \endcode
 */
static PyObject *
PyCSDL2Test_PixelFormat(PyObject *module, PyObject *args)
{
    SDL_PixelFormat *pfmt;

    /*
     * We use an indexed format to ensure that it is not shared with other
     * callers. (SDL shares pixel formats that are not indexed)
     */
    pfmt = SDL_AllocFormat(SDL_PIXELFORMAT_INDEX8);
    if (!pfmt)
        return PyErr_NoMemory();

    return PyCSDL2_PixelFormatCreate(pfmt);
}

/**
 * \brief Sets the "BitsPerPixel" field of a SDL_PixelFormat to 42.
 *
 * \code{.py}
 * pixel_format_set_bpp(pfmt: SDL_PixelFormat) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_PixelFormatSetBPP(PyObject *module, PyObject *args)
{
    SDL_PixelFormat *pfmt;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_PixelFormatPtr, &pfmt))
        return NULL;

    pfmt->BitsPerPixel = 42;

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_PIXELS_H_ */
