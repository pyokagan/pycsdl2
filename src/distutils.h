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
 * \file distutils.h
 * \brief distutils support.
 *
 * This file implements functionality to help building with distutils
 * extensions which use pycsdl2's functionality.
 */
#ifndef _PYCSDL2_DISTUTILS_H_
#define _PYCSDL2_DISTUTILS_H_
#include <Python.h>
#include "../include/pycsdl2.h"

#ifndef PYCSDL2_INCLUDE_DIRS
/**
 * \brief \c include_dirs used to find the system SDL2 header files when
 *        compiling pycsdl2.
 *
 * A comma-separated list of C string literals that must end with a
 * comma. Each C string literal is a include directory that can be used to find
 * the system SDL2 header files and their dependencies. This corresponds to the
 * \c distutils.extension.Extension.include_dirs attribute. If the list has no
 * elements, either leave the macro empty or do not define this macro.
 */
#define PYCSDL2_INCLUDE_DIRS
#endif /* PYCSDL2_INCLUDE_DIRS */

/**
 * \brief Return PyListObject of PYCSDL2_INCLUDE_DIRS.
 *
 * \return PyListObject of PYCSDL2_INCLUDE_DIRS if defined, else an empty
 *         PyListObject. Returns NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_GetSystemSDLIncludeDirs(void)
{
    static const char *include_dirs[] = {PYCSDL2_INCLUDE_DIRS NULL};
    PyObject *list;
    Py_ssize_t i, len;

    /* Calculate len of include_dirs */
    for (len = 0; include_dirs[len] != NULL; ++len) {}
    /* Create output list */
    if (!(list = PyList_New(len)))
        return NULL;
    /* Set items on list */
    for (i = 0; include_dirs[i] != NULL; ++i) {
        PyObject *str = PyUnicode_FromString(include_dirs[i]);
        if (str == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i, str);
    }
    return list;
}

#endif /* _PYCSDL2_DISTUTILS_H_ */
