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
 * \file capi.h
 * \brief csdl2's C API
 *
 * This file implements functionality to expose csdl2's C API to other
 * extensions so that these extensions can use csdl2's functionality.
 */
#ifndef _PYCSDL2_CAPI_H_
#define _PYCSDL2_CAPI_H_
#include <Python.h>
#include "../include/pycsdl2.h"

/**
 * \brief Initializes csdl2's PyCSDL2_CAPI PyCapsule
 *
 * Initialize csdl2's PyCSDL2_CAPI PyCapsule object and adds it to the module m
 * with the name "_C_API". The PyCSDL2_CAPI can thus be retrieved with:
 * \code
 * (PyCSDL2_CAPI*) PyCapsule_Import("csdl2._C_API", 0);
 * \endcode
 *
 * \param m the csdl2 module object
 * \returns 1 on success, 0 on failure
 */
static int
PyCSDL2_initcapi(PyObject *m)
{
    static const PyCSDL2_CAPI api = {
        0
    };
    PyObject *capsule = PyCapsule_New((void*) &api, "csdl2._C_API", NULL);
    if (!capsule) { return 0; }
    if (PyModule_AddObject(m, "_C_API", capsule)) { return 0; }
    return 1;
}

#endif /* _PYCSDL2_CAPI_H_ */
