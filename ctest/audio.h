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
 * \brief Tests for csdl2's SDL_audio bindings.
 */
#ifndef _PYCSDL2TEST_AUDIO_H_
#define _PYCSDL2TEST_AUDIO_H_
#include <Python.h>
#include <SDL_audio.h>
#include "../include/pycsdl2.h"

/**
 * \brief SDL Audio callback for PyCSDL2Test_AudioSpec()
 */
static void SDLCALL
PyCSDL2Test_AudioSpecCallback(void *userdata, Uint8 *stream, int len)
{
    /* do nothing */
}

/**
 * \brief Creates and returns a PyCSDL2_AudioSpec object.
 *
 * \code{.py}
 * audio_spec() -> SDL_AudioSpec
 * \endcode
 */
static PyObject *
PyCSDL2Test_AudioSpec(PyObject *module, PyObject *args)
{
    SDL_AudioSpec spec;

    spec.freq = 1;
    spec.format = 2;
    spec.channels = 3;
    spec.silence = 4;
    spec.samples = 5;
    spec.size = 6;
    spec.callback = PyCSDL2Test_AudioSpecCallback;
    return PyCSDL2_AudioSpecCreate(&spec);
}

/**
 * \brief Sets the "freq" field of a SDL_AudioSpec to 42.
 *
 * \code{.py}
 * audio_spec_set_freq(spec: SDL_AudioSpec) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_AudioSpecSetFreq(PyObject *module, PyObject *args)
{
    SDL_AudioSpec *spec;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_AudioSpecPtr, &spec))
        return NULL;

    spec->freq = 42;

    Py_RETURN_NONE;
}

/**
 * \brief Creates and returns a PyCSDL2_AudioDevice object.
 *
 * \code{.py}
 * audio_device() -> SDL_AudioDevice
 * \endcode
 */
static PyObject *
PyCSDL2Test_AudioDevice(PyObject *module, PyObject *args)
{
    SDL_AudioSpec spec;
    SDL_AudioDeviceID dev;

    spec.freq = 44100;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = 4096;
    spec.callback = PyCSDL2Test_AudioSpecCallback;

    dev = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if (dev <= 0) {
        PyErr_SetString(PyExc_RuntimeError, "SDL_OpenAudioDevice failed");
        return NULL;
    }

    return PyCSDL2_AudioDeviceCreate(dev);
}

/**
 * \brief Unpauses a SDL_AudioDeviceID
 *
 * \code{.py}
 * audio_device_unpause(dev: SDL_AudioDevice) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_AudioDeviceUnpause(PyObject *module, PyObject *args)
{
    SDL_AudioDeviceID id;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_AudioDeviceID, &id))
        return NULL;

    SDL_PauseAudioDevice(id, 0);

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_AUDIO_H_ */
