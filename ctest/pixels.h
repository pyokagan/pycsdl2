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

#endif /* _PYCSDL2TEST_PIXELS_H_ */
