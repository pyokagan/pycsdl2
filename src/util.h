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
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint16
 */
#define Uint16_UNIT "H"
#elif SIZEOF_INT == 2
/* An int must be at least 16 bits long */
#define Sint16_UNIT "i"
#define Uint16_UNIT "I"
#else
#error Could not find C integer type with 2 bytes width
#endif

#if SIZEOF_SHORT == 4
/* A short int must be at least 16 bits long */
#define Sint32_UNIT "h"
#define Uint32_UNIT "H"
#elif SIZEOF_INT == 4
/* An int must be at least 16 bits long */
#define Sint32_UNIT "i"
#define Uint32_UNIT "I"
#elif SIZEOF_LONG == 4 || defined(DOXYGEN)
/* A long int must be at least 32 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint32
 */
#define Sint32_UNIT "l"
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint32
 */
#define Uint32_UNIT "k"
#else
#error Could not find C integer type with 4 bytes width
#endif

#if SIZEOF_SHORT == 8
/* A short int must be at least 16 bits long */
#define Sint64_UNIT "h"
#define Uint64_UNIT "H"
#elif SIZEOF_INT == 8
/* An int must be at least 16 bits long */
#define Sint64_UNIT "i"
#define Uint64_UNIT "I"
#elif SIZEOF_LONG == 8
/* A long int must be at least 32 bits long */
#define Sint64_UNIT "l"
#define Uint64_UNIT "k"
#elif SIZEOF_LONG_LONG == 8 || defined(DOXYGEN)
/* A long long int must be at least 64 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint64
 */
#define Sint64_UNIT "L"
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint64
 */
#define Uint64_UNIT "K"
#else
#error Could not find C integer type with 8 bytes width
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

/**
 * \brief Asserts that condition is true.
 *
 * This is a utility macro for asserting that a condition is true, and if it is
 * not, raises a Python AssertionError exception and causes the current
 * function to return with NULL.
 */
#define PyCSDL2_Assert(condition) \
    do { \
        if (!(condition)) { \
            PyErr_Format(PyExc_AssertionError, "%s:%d: %s", __FILE__, \
                         __LINE__, #condition); \
            return NULL; \
        } \
    } while(0)

/**
 * \brief Returns a new reference to var
 *
 * \returns var with if refcount incremented. If var is NULL, returns Py_None.
 */
static PyObject *
PyCSDL2_Get(PyObject *var)
{
    if (!var)
        Py_RETURN_NONE;
    Py_INCREF(var);
    return var;
}

/**
 * \brief Sets var to a new reference to value
 *
 * If var had a previous value, the refcount of the previous value is
 * decremented.
 */
#define PyCSDL2_Set(var, value) \
    do { \
        void *tmp = (var); \
        Py_XINCREF((PyObject*) value); \
        (var) = (value); \
        Py_XDECREF((PyObject*) tmp); \
    } while(0)

#endif /* _PYCSDL2_UTIL_H_ */
