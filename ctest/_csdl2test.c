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
 * \file _csdl2test.c
 * \brief _csdl2test extension source code.
 */
#include <Python.h>
#include "../include/pycsdl2.h"
#include "methods.h"

/**
 * \brief _csdl2test module definition.
 *
 * \sa PyInit__csdl2test()
 */
static PyModuleDef PyCSDL2Test_Module = {
    PyModuleDef_HEAD_INIT,
    /* m_name     */ "_csdl2test",
    /* m_doc      */ "csdl2 C API tests",
    /* m_size     */ -1,
    /* m_methods  */ PyCSDL2Test_Methods,
    /* m_reload   */ NULL,
    /* m_traverse */ NULL,
    /* m_clear    */ NULL,
    /* m_free     */ NULL
};

/**
 * \brief _csdl2test module init entry point.
 */
PyMODINIT_FUNC
PyInit__csdl2test(void)
{
    PyObject *m;

    m = PyModule_Create(&PyCSDL2Test_Module);
    if (!m)
        return NULL;

    if (!PyCSDL2_Import())
        return NULL;

    return m;
}
