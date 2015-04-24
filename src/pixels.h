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
 * \brief Bindings for SDL_pixels.h
 *
 * Implements bindings for SDL's pixel formats and conversion routines API
 * (SDL_pixels.h)
 */
#ifndef _PYCSDL2_PIXELS_H_
#define _PYCSDL2_PIXELS_H_
#include <Python.h>
#include <SDL_surface.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \brief Initializes bindings to SDL_pixels.h
 *
 * Adds constants defined in SDL_pixels.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initpixels(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_ALPHA_OPAQUE", SDL_ALPHA_OPAQUE},
        {"SDL_ALPHA_TRANSPARENT", SDL_ALPHA_TRANSPARENT},

        {"SDL_PIXELTYPE_UNKNOWN", SDL_PIXELTYPE_UNKNOWN},
        {"SDL_PIXELTYPE_INDEX1", SDL_PIXELTYPE_INDEX1},
        {"SDL_PIXELTYPE_INDEX4", SDL_PIXELTYPE_INDEX4},
        {"SDL_PIXELTYPE_INDEX8", SDL_PIXELTYPE_INDEX8},
        {"SDL_PIXELTYPE_PACKED8", SDL_PIXELTYPE_PACKED8},
        {"SDL_PIXELTYPE_PACKED16", SDL_PIXELTYPE_PACKED16},
        {"SDL_PIXELTYPE_PACKED32", SDL_PIXELTYPE_PACKED32},
        {"SDL_PIXELTYPE_ARRAYU8", SDL_PIXELTYPE_ARRAYU8},
        {"SDL_PIXELTYPE_ARRAYU16", SDL_PIXELTYPE_ARRAYU16},
        {"SDL_PIXELTYPE_ARRAYU32", SDL_PIXELTYPE_ARRAYU32},
        {"SDL_PIXELTYPE_ARRAYF16", SDL_PIXELTYPE_ARRAYF16},
        {"SDL_PIXELTYPE_ARRAYF32", SDL_PIXELTYPE_ARRAYF32},

        {"SDL_BITMAPORDER_NONE", SDL_BITMAPORDER_NONE},
        {"SDL_BITMAPORDER_4321", SDL_BITMAPORDER_4321},
        {"SDL_BITMAPORDER_1234", SDL_BITMAPORDER_1234},

        {"SDL_PACKEDORDER_NONE", SDL_PACKEDORDER_NONE},
        {"SDL_PACKEDORDER_XRGB", SDL_PACKEDORDER_XRGB},
        {"SDL_PACKEDORDER_RGBX", SDL_PACKEDORDER_RGBX},
        {"SDL_PACKEDORDER_ARGB", SDL_PACKEDORDER_ARGB},
        {"SDL_PACKEDORDER_RGBA", SDL_PACKEDORDER_RGBA},
        {"SDL_PACKEDORDER_XBGR", SDL_PACKEDORDER_XBGR},
        {"SDL_PACKEDORDER_BGRX", SDL_PACKEDORDER_BGRX},
        {"SDL_PACKEDORDER_ABGR", SDL_PACKEDORDER_ABGR},
        {"SDL_PACKEDORDER_BGRA", SDL_PACKEDORDER_BGRA},

        {"SDL_ARRAYORDER_NONE", SDL_ARRAYORDER_NONE},
        {"SDL_ARRAYORDER_RGB", SDL_ARRAYORDER_RGB},
        {"SDL_ARRAYORDER_RGBA", SDL_ARRAYORDER_RGBA},
        {"SDL_ARRAYORDER_ARGB", SDL_ARRAYORDER_ARGB},
        {"SDL_ARRAYORDER_BGR", SDL_ARRAYORDER_BGR},
        {"SDL_ARRAYORDER_BGRA", SDL_ARRAYORDER_BGRA},
        {"SDL_ARRAYORDER_ABGR", SDL_ARRAYORDER_ABGR},

        {"SDL_PACKEDLAYOUT_NONE", SDL_PACKEDLAYOUT_NONE},
        {"SDL_PACKEDLAYOUT_332", SDL_PACKEDLAYOUT_332},
        {"SDL_PACKEDLAYOUT_4444", SDL_PACKEDLAYOUT_4444},
        {"SDL_PACKEDLAYOUT_1555", SDL_PACKEDLAYOUT_1555},
        {"SDL_PACKEDLAYOUT_5551", SDL_PACKEDLAYOUT_5551},
        {"SDL_PACKEDLAYOUT_565", SDL_PACKEDLAYOUT_565},
        {"SDL_PACKEDLAYOUT_8888", SDL_PACKEDLAYOUT_8888},
        {"SDL_PACKEDLAYOUT_2101010", SDL_PACKEDLAYOUT_2101010},
        {"SDL_PACKEDLAYOUT_1010102", SDL_PACKEDLAYOUT_1010102},

        {"SDL_PIXELFORMAT_UNKNOWN", SDL_PIXELFORMAT_UNKNOWN},
        {"SDL_PIXELFORMAT_INDEX1LSB", SDL_PIXELFORMAT_INDEX1LSB},
        {"SDL_PIXELFORMAT_INDEX1MSB", SDL_PIXELFORMAT_INDEX1MSB},
        {"SDL_PIXELFORMAT_INDEX4LSB", SDL_PIXELFORMAT_INDEX4LSB},
        {"SDL_PIXELFORMAT_INDEX4MSB", SDL_PIXELFORMAT_INDEX4MSB},
        {"SDL_PIXELFORMAT_INDEX8", SDL_PIXELFORMAT_INDEX8},
        {"SDL_PIXELFORMAT_RGB332", SDL_PIXELFORMAT_RGB332},
        {"SDL_PIXELFORMAT_RGB444", SDL_PIXELFORMAT_RGB444},
        {"SDL_PIXELFORMAT_RGB555", SDL_PIXELFORMAT_RGB555},
        {"SDL_PIXELFORMAT_BGR555", SDL_PIXELFORMAT_BGR555},
        {"SDL_PIXELFORMAT_ARGB4444", SDL_PIXELFORMAT_ARGB4444},
        {"SDL_PIXELFORMAT_RGBA4444", SDL_PIXELFORMAT_RGBA4444},
        {"SDL_PIXELFORMAT_ABGR4444", SDL_PIXELFORMAT_ABGR4444},
        {"SDL_PIXELFORMAT_BGRA4444", SDL_PIXELFORMAT_BGRA4444},
        {"SDL_PIXELFORMAT_ARGB1555", SDL_PIXELFORMAT_ARGB1555},
        {"SDL_PIXELFORMAT_RGBA5551", SDL_PIXELFORMAT_RGBA5551},
        {"SDL_PIXELFORMAT_ABGR1555", SDL_PIXELFORMAT_ABGR1555},
        {"SDL_PIXELFORMAT_BGRA5551", SDL_PIXELFORMAT_BGRA5551},
        {"SDL_PIXELFORMAT_RGB565", SDL_PIXELFORMAT_RGB565},
        {"SDL_PIXELFORMAT_BGR565", SDL_PIXELFORMAT_BGR565},
        {"SDL_PIXELFORMAT_RGB24", SDL_PIXELFORMAT_RGB24},
        {"SDL_PIXELFORMAT_BGR24", SDL_PIXELFORMAT_BGR24},
        {"SDL_PIXELFORMAT_RGB888", SDL_PIXELFORMAT_RGB888},
        {"SDL_PIXELFORMAT_RGBX8888", SDL_PIXELFORMAT_RGBX8888},
        {"SDL_PIXELFORMAT_BGR888", SDL_PIXELFORMAT_BGR888},
        {"SDL_PIXELFORMAT_BGRX8888", SDL_PIXELFORMAT_BGRX8888},
        {"SDL_PIXELFORMAT_ARGB8888", SDL_PIXELFORMAT_ARGB8888},
        {"SDL_PIXELFORMAT_RGBA8888", SDL_PIXELFORMAT_RGBA8888},
        {"SDL_PIXELFORMAT_ABGR8888", SDL_PIXELFORMAT_ABGR8888},
        {"SDL_PIXELFORMAT_BGRA8888", SDL_PIXELFORMAT_BGRA8888},
        {"SDL_PIXELFORMAT_ARGB2101010", SDL_PIXELFORMAT_ARGB2101010},
        {"SDL_PIXELFORMAT_YV12", SDL_PIXELFORMAT_YV12},
        {"SDL_PIXELFORMAT_IYUV", SDL_PIXELFORMAT_IYUV},
        {"SDL_PIXELFORMAT_YUY2", SDL_PIXELFORMAT_YUY2},
        {"SDL_PIXELFORMAT_UYVY", SDL_PIXELFORMAT_UYVY},
        {"SDL_PIXELFORMAT_YVYU", SDL_PIXELFORMAT_YVYU},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    return 1;
}

#endif /* _PYCSDL2_PIXELS_H_ */