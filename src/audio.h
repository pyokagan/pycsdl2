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
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initaudio(PyObject *module)
{
    return 1;
}

#endif /* _PYCSDL2_AUDIO_H_ */
