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
#ifndef _PYCSDL2_H_
#define _PYCSDL2_H_
/**
 * \file pycsdl2.h
 * \brief pycsdl2 public API header
 */
#ifdef __cplusplus
extern "C" {
#endif
#include <Python.h>

/**
 * \brief pycsdl2's C API
 *
 * This struct is used to hold pointers to functions and data that csdl2
 * exposes to other extensions. csdl2 stores an instance of this struct in a
 * PyCapsule object which can be accessed with PyCapsule_Import().
 */
typedef struct PyCSDL2_CAPI {
    int x; /**< Dummy integer */
} PyCSDL2_CAPI;

#ifndef PYCSDL2_MODULE

/**
 * \brief Imports csdl2 and returns its PyCSDL2_CAPI.
 * \returns const pointer to PyCSDL2_CAPI, or NULL when an exception occurred.
 */
static const PyCSDL2_CAPI *PyCSDL2_Import(void)
{
    static const PyCSDL2_CAPI *capi;

    if (!capi)
        capi = (const PyCSDL2_CAPI*) PyCapsule_Import("csdl2._C_API", 0);
    return capi;
}

#endif /* PYCSDL2_MODULE */

#ifdef __cplusplus
}
#endif
#endif /* _PYCSDL2_H_ */
