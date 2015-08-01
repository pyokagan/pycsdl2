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
 * \file methods.h
 * \brief _csdl2test list of module methods.
 */
#ifndef _PYCSDL2TEST_METHODS_H_
#define _PYCSDL2TEST_METHODS_H_
#include <Python.h>
#include "../include/pycsdl2.h"
#include "audio.h"
#include "events.h"
#include "pixels.h"

/**
 * \brief _csdl2test methods definitions.
 *
 * \sa PyCSDL2Test_Module
 */
static PyMethodDef PyCSDL2Test_Methods[] = {

    /* audio.h */

    {"audio_spec",
     PyCSDL2Test_AudioSpec,
     METH_VARARGS,
     "audio_spec() -> SDL_AudioSpec"
    },

    {"audio_spec_set_freq",
     PyCSDL2Test_AudioSpecSetFreq,
     METH_VARARGS,
     "audio_spec_set_freq(spec: SDL_AudioSpec) -> None"
    },

    {"audio_device",
     PyCSDL2Test_AudioDevice,
     METH_VARARGS,
     "audio_device() -> SDL_AudioDevice"
    },

    {"audio_device_unpause",
     PyCSDL2Test_AudioDeviceUnpause,
     METH_VARARGS,
     "audio_device_unpause(dev: SDL_AudioDevice) -> None"
    },

    /* events.h */

    {"mouse_motion_event",
     PyCSDL2Test_MouseMotionEvent,
     METH_VARARGS,
     "mouse_motion_event() -> SDL_MouseMotionEvent"
    },

    {"mouse_motion_event_set_type",
     PyCSDL2Test_MouseMotionEventSetType,
     METH_VARARGS,
     "mouse_motion_event_set_type(ev: SDL_MouseMotionEvent) -> None"
    },

    {"event",
     PyCSDL2Test_Event,
     METH_VARARGS,
     "event() -> SDL_Event"
    },

    {"event_set_type",
     PyCSDL2Test_EventSetType,
     METH_VARARGS,
     "event_set_type(ev: SDL_Event) -> None"
    },

    /* pixels.h */

    {"palette",
     PyCSDL2Test_Palette,
     METH_VARARGS,
     "palette() -> SDL_Palette"
    },

    {"palette_set_ncolors",
     PyCSDL2Test_PaletteSetNColors,
     METH_VARARGS,
     "palette_set_ncolors(plt: SDL_Palette) -> None"
    },

    {"pixel_format",
     PyCSDL2Test_PixelFormat,
     METH_VARARGS,
     "pixel_format() -> SDL_PixelFormat"
    },

    {"pixel_format_set_bpp",
     PyCSDL2Test_PixelFormatSetBPP,
     METH_VARARGS,
     "pixel_format_set_bpp(pfmt: SDL_PixelFormat) -> None"
    },

    /* End */
    {0}
};

#endif /* _PYCSDL2TEST_METHODS_H_ */
