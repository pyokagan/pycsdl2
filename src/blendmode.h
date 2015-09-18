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
 * \file blendmode.h
 * \brief Bindings for SDL_blendmode.h
 *
 * Implements bindings for SDL's blendmode enumeration.
 */
#ifndef _PYCSDL2_BLENDMODE_H_
#define _PYCSDL2_BLENDMODE_H_
#include <Python.h>
#include <SDL_blendmode.h>
#include "../include/pycsdl2.h"
#include "util.h"

/**
 * \brief Initializes bindings to SDL_blendmode.h
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initblendmode(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_BLENDMODE_NONE", SDL_BLENDMODE_NONE},
        {"SDL_BLENDMODE_BLEND", SDL_BLENDMODE_BLEND},
        {"SDL_BLENDMODE_ADD", SDL_BLENDMODE_ADD},
        {"SDL_BLENDMODE_MOD", SDL_BLENDMODE_MOD},

        {NULL, 0}
    };

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_BLENDMODE_H_ */
