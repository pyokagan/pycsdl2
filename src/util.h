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
/*!
 * \file util.h
 * \brief Shared utility functionality.
 */
#ifndef _PYCSDL2_UTIL_H_
#define _PYCSDL2_UTIL_H_
#include <Python.h>
#include "../include/pycsdl2.h"

#if SIZEOF_SHORT == 2 || defined(DOXYGEN)
/* A short int must be at least 16 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint16
 */
#define Sint16_UNIT "h"
#elif SIZEOF_INT == 2
/* An int must be at least 16 bits long */
#define Sint16_UNIT "i"
#else
#error Could not find C integer type with 2 bytes width
#endif

/*!
 * \brief struct for defining constants.
 *
 * This allows constants to be listed in an array and added to the module
 * with the following code:
 *
 * \code
 * static const PyCSDL2_Constant constants[] = {
 *     {"CONSTANT1", 1},
 *     {"CONSTANT2", 2},
 *     {0}
 * };
 * const PyCSDL2_Constant *c;
 * for (c = constants; c->name != NULL; ++c) {
 *     if (PyModule_AddIntConstant(module, c->name, c->value) != 0) {
 *         return 0;
 *     }
 * }
 * \endcode
 */
typedef struct {
    const char *name; /*!< name of constant */
    long value;       /*!< value of constant */
} PyCSDL2_Constant;

#endif /* _PYCSDL2_UTIL_H_ */
