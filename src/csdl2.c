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
 * \file csdl2.c
 * \brief csdl2 extension source code.
 */
#include <Python.h>
#define PYCSDL2_MODULE
#include "../include/pycsdl2.h"
#include "util.h"
#include "audio.h"
#include "blendmode.h"
#include "capi.h"
#include "events.h"
#include "init.h"
#include "pixels.h"
#include "rect.h"
#include "render.h"
#include "rwops.h"
#include "surface.h"
#include "video.h"
#include "methods.h"

/**
 * \brief csdl2 module definition.
 *
 * \sa PyInit_csdl2()
 */
static PyModuleDef PyCSDL2_Module = {
    PyModuleDef_HEAD_INIT,
    /* m_name */ "csdl2",
    /* m_doc */ "Simple DirectMedia Layer",
    /* m_size */ -1,
    /* m_methods */ PyCSDL2_Methods,
    /* m_reload */ NULL,
    /* m_traverse */ NULL,
    /* m_clear */ NULL,
    /* m_free */ NULL
};

/**
 * \brief csdl2 module init entry point.
 */
PyMODINIT_FUNC
PyInit_csdl2(void)
{
    PyObject *m = PyModule_Create(&PyCSDL2_Module);

    if (!m) { return NULL; }
    if (!PyCSDL2_initutil(m)) { goto fail; }
    if (!PyCSDL2_initaudio(m)) { goto fail; }
    if (!PyCSDL2_initblendmode(m)) { goto fail; }
    if (!PyCSDL2_initcapi(m)) { goto fail; }
    if (!PyCSDL2_initinit(m)) { goto fail; }
    if (!PyCSDL2_initpixels(m)) { goto fail; }
    if (!PyCSDL2_initrect(m)) { goto fail; }
    if (!PyCSDL2_initrender(m)) { goto fail; }
    if (!PyCSDL2_initrwops(m)) { goto fail; }
    if (!PyCSDL2_initsurface(m)) { goto fail; }
    if (!PyCSDL2_initvideo(m)) { goto fail; }
    if (!PyCSDL2_initevents(m)) { goto fail; }
    return m;

fail:
    Py_DECREF(m);
    return NULL;
}
