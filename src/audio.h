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
 * \file audio.h
 * \brief Bindings for SDL_audio.h
 *
 * Implements bindings for SDL's Audio Device Management, Playing and Recording
 * (SDL_audio.h)
 */
#ifndef _PYCSDL2_AUDIO_H_
#define _PYCSDL2_AUDIO_H_
#include <Python.h>
#include <SDL_audio.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \brief Initializes bindings to SDL_audio.h
 *
 * Adds constants defined in SDL_audio.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initaudio(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_AUDIO_MASK_BITSIZE", SDL_AUDIO_MASK_BITSIZE},
        {"SDL_AUDIO_MASK_DATATYPE", SDL_AUDIO_MASK_DATATYPE},
        {"SDL_AUDIO_MASK_ENDIAN", SDL_AUDIO_MASK_ENDIAN},
        {"SDL_AUDIO_MASK_SIGNED", SDL_AUDIO_MASK_SIGNED},

        /* Audio format flags */
        {"AUDIO_U8", AUDIO_U8},
        {"AUDIO_S8", AUDIO_S8},
        {"AUDIO_U16LSB", AUDIO_U16LSB},
        {"AUDIO_S16LSB", AUDIO_S16LSB},
        {"AUDIO_U16MSB", AUDIO_U16MSB},
        {"AUDIO_S16MSB", AUDIO_S16MSB},
        {"AUDIO_U16", AUDIO_U16},
        {"AUDIO_S16", AUDIO_S16},

        /* int32 support */
        {"AUDIO_S32LSB", AUDIO_S32LSB},
        {"AUDIO_S32MSB", AUDIO_S32MSB},
        {"AUDIO_S32", AUDIO_S32},

        /* float32 support */
        {"AUDIO_F32LSB", AUDIO_F32LSB},
        {"AUDIO_F32MSB", AUDIO_F32MSB},
        {"AUDIO_F32", AUDIO_F32},

        /* Native audio byte ordering */
        {"AUDIO_U16SYS", AUDIO_U16SYS},
        {"AUDIO_S16SYS", AUDIO_S16SYS},
        {"AUDIO_S32SYS", AUDIO_S32SYS},
        {"AUDIO_F32SYS", AUDIO_F32SYS},

        /* Allow change flags */
        {"SDL_AUDIO_ALLOW_FREQUENCY_CHANGE", SDL_AUDIO_ALLOW_FREQUENCY_CHANGE},
        {"SDL_AUDIO_ALLOW_FORMAT_CHANGE", SDL_AUDIO_ALLOW_FORMAT_CHANGE},
        {"SDL_AUDIO_ALLOW_CHANNELS_CHANGE", SDL_AUDIO_ALLOW_CHANNELS_CHANGE},
        {"SDL_AUDIO_ALLOW_ANY_CHANGE", SDL_AUDIO_ALLOW_ANY_CHANGE},

        /* Audio state */
        {"SDL_AUDIO_STOPPED", SDL_AUDIO_STOPPED},
        {"SDL_AUDIO_PLAYING", SDL_AUDIO_PLAYING},
        {"SDL_AUDIO_PAUSED", SDL_AUDIO_PAUSED},

        {"SDL_MIX_MAXVOLUME", SDL_MIX_MAXVOLUME},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    return 1;
}

#endif /* _PYCSDL2_AUDIO_H_ */
