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

#ifndef PYCSDL2_DEFINE_MACROS
/**
 * \brief \c define_macros used to compile pycsdl2 to link with the system SDL2
 *        library.
 *
 * A comma-separated list of C string literals that must end with a comma.
 * Each 2 elements of the list are implicitly paired to form a python
 * 2-tuple. The first element is the macro name as a C string literal, and the
 * second element is an optional macro value as a C string literal. If the
 * macro has no value, use the \c NULL pointer constant instead of a C string
 * literal. This corresponds to the
 * \c distutils.extension.Extension.define_macros attribute. If the list has no
 * elements, leave this macro empty or do not define this macro.
 */
#define PYCSDL2_DEFINE_MACROS
#endif /* PYCSDL2_DEFINE_MACROS */

/**
 * \brief Return PyListObject of PYCSDL2_DEFINE_MACROS.
 *
 * \return PyListObject of PYCSDL2_DEFINE_MACROS if defined, else an empty
 *         PyListObject. Returns NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_GetSystemSDLDefineMacros(void)
{
    static const char *define_macros[] = {PYCSDL2_DEFINE_MACROS NULL, NULL,
                                          NULL};
    PyObject *list;
    Py_ssize_t i, len;

    /* Calculate len of define_macros */
    for (len = 0; define_macros[len] != NULL; len += 2) {}
    /* Create output list */
    if (!(list = PyList_New(len / 2)))
        return NULL;
    /* Set items on list */
    for (i = 0; define_macros[i] != NULL; i += 2) {
        PyObject *tuple, *key, *value;

        tuple = PyTuple_New(2);
        if (tuple == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i / 2, tuple);
        key = PyUnicode_FromString(define_macros[i]);
        if (key == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyTuple_SET_ITEM(tuple, 0, key);
        if (define_macros[i+1] == NULL) {
            Py_INCREF(Py_None);
            value = Py_None;
        } else {
            value = PyUnicode_FromString(define_macros[i+1]);
            if (value == NULL) {
                Py_DECREF(list);
                return NULL;
            }
        }
        PyTuple_SET_ITEM(tuple, 1, value);
    }
    return list;
}

#ifndef PYCSDL2_UNDEF_MACROS
/**
 * \brief \c undef_macros used to compile pycsdl2 to link with the system SDL2
 *        library.
 *
 * A comma-separated list of C string literals that must end with a comma. Each
 * C string literal is a macro name to undefine. This corresponds to the
 * \c distutils.extension.Extension.undef_macros attribute. If the list has no
 * elements, leave this macro empty or do not define this macro.
 */
#define PYCSDL2_UNDEF_MACROS
#endif /* PYCSDL2_UNDEF_MACROS */

/**
 * \brief Returns PyListObject of PYCSDL2_UNDEF_MACROS.
 *
 * \return PyListObject of PYCSDL2_UNDEF_MACROS if defined, else returns an
 *         empty PyListObject. Returns NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_GetSystemSDLUndefMacros(void)
{
    static const char *undef_macros[] = {PYCSDL2_UNDEF_MACROS NULL};
    PyObject *list;
    Py_ssize_t len, i;

    /* Calculate len of undef_macros */
    for (len = 0; undef_macros[len] != NULL; ++len) {}
    /* Create output list */
    if (!(list = PyList_New(len)))
        return NULL;
    /* Set items on list */
    for (i = 0; undef_macros[i] != NULL; ++i) {
        PyObject *str = PyUnicode_FromString(undef_macros[i]);
        if (str == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i, str);
    }
    return list;
}

#ifndef PYCSDL2_EXTRA_COMPILE_ARGS
/**
 * \def PYCSDL2_EXTRA_COMPILE_ARGS
 * \brief \c extra_compile_args used to compile pycsdl2 to link with the system
 *        SDL2 library.
 *
 * A comma-separated list of C string literals that must end with a comma. Each
 * C string literal is an extra argument to provide when compiling source files
 * that will link with the system SDL2 library. This corresponds to the
 * \c distutils.extension.Extension.extra_compile_args attribute. If the list
 * has no elements, do not define this macro.
 */
#define PYCSDL2_EXTRA_COMPILE_ARGS
#endif /* PYCSDL2_EXTRA_COMPILE_ARGS */

/**
 * \brief Returns PyListObject of PYCSDL2_EXTRA_COMPILE_ARGS.
 *
 * \return PyListObject of PYCSDL2_EXTRA_COMPILE_ARGS if defined, else returns
 *         an empty PyListObject. Returns NULL if an exception occured.
 */
static PyObject *
PyCSDL2_GetSystemSDLExtraCompileArgs(void)
{
    static const char *extra_compile_args[] = {PYCSDL2_EXTRA_COMPILE_ARGS
                                               NULL};
    PyObject *list;
    Py_ssize_t len, i;

    /* Calculate len of extra_compile_args */
    for (len = 0; extra_compile_args[len] != NULL; ++len) {}
    /* Create output list */
    if (!(list = PyList_New(len)))
        return NULL;
    /* Set items on list */
    for (i = 0; extra_compile_args[i] != NULL; ++i) {
        PyObject *str = PyUnicode_FromString(extra_compile_args[i]);
        if (str == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i, str);
    }
    return list;
}

#ifndef PYCSDL2_LIBRARY_DIRS
/**
 * \def PYCSDL2_LIBRARY_DIRS
 * \brief \c library_dirs that pycsdl2 used to find the system SDL2 library
 *        (and dependencies)
 *
 * A comma-separated list of C string literals that must end with a comma. Each
 * C string literal is a directory used to find the system SDL2 library and its
 * dependencies when linking. This corresponds to the
 * \c distutils.extension.Extension.library_dirs attribute. If the list has no
 * elements, do not define this macro.
 */
#define PYCSDL2_LIBRARY_DIRS
#endif /* PYCSDL2_LIBRARY_DIRS */

/**
 * \brief Returns PyListObject of PYCSDL2_LIBRARY_DIRS.
 *
 * \return PyListObject of PYCSDL2_LIBRARY_DIRS if defined, else an empty
 *         PyListObject. Returns NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_GetSystemSDLLibraryDirs(void)
{
    static const char *lib_dirs[] = {PYCSDL2_LIBRARY_DIRS NULL};
    PyObject *list;
    Py_ssize_t len, i;

    /* Calculate len of lib_dirs */
    for (len = 0; lib_dirs[len] != NULL; ++len) {}
    /* Create output list */
    if (!(list = PyList_New(len)))
        return NULL;
    /* Set items on list */
    for (i = 0; lib_dirs[i] != NULL; ++i) {
        PyObject *str = PyUnicode_FromString(lib_dirs[i]);
        if (str == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i, str);
    }
    return list;
}

#endif /* _PYCSDL2_DISTUTILS_H_ */
