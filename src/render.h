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
 * \file render.h
 * \brief Bindings for SDL_render.h
 *
 * Implements bindings for SDL's 2D Accelerated Rendering API (SDL_render.h)
 */
#ifndef _PYCSDL2_RENDER_H_
#define _PYCSDL2_RENDER_H_
#include <Python.h>
#include <SDL_render.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \brief Initializes bindings to SDL_render.h
 *
 * Adds constants defined in SDL_render.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initrender(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE},
        {"SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED},
        {"SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC},
        {"SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE},

        {"SDL_TEXTUREACCESS_STATIC", SDL_TEXTUREACCESS_STATIC},
        {"SDL_TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING},
        {"SDL_TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET},

        {"SDL_TEXTUREMODULATE_NONE", SDL_TEXTUREMODULATE_NONE},
        {"SDL_TEXTUREMODULATE_COLOR", SDL_TEXTUREMODULATE_COLOR},
        {"SDL_TEXTUREMODULATE_ALPHA", SDL_TEXTUREMODULATE_ALPHA},

        {"SDL_FLIP_NONE", SDL_FLIP_NONE},
        {"SDL_FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL},
        {"SDL_FLIP_VERTICAL", SDL_FLIP_VERTICAL},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    return 1;
}

#endif /* _PYCSDL2_RENDER_H_ */
