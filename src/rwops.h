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
 * \file rwops.h
 * \brief Bindings for SDL_rwops.h
 *
 * Implements bindings for SDL's File IO API (SDL_rwops.h)
 */
#ifndef _PYCSDL2_RWOPS_H_
#define _PYCSDL2_RWOPS_H_
#include <Python.h>
#include <SDL_rwops.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief Instance data for PyCSDL2_RWopsPtrType */
typedef struct PyCSDL2_RWopsPtr {
    PyObject_HEAD
    /** \brief Pointer to SDL_RWops */
    SDL_RWops *rwops;
} PyCSDL2_RWopsPtr;

/** \brief Traversal function for PyCSDL2_RWopsPtrType */
static int
PyCSDL2_RWopsPtrTraverse(PyCSDL2_RWopsPtr *self, visitproc visit, void *arg)
{
    return 0;
}

/** \brief Clear function for PyCSDL2_RWopsPtrType */
static int
PyCSDL2_RWopsPtrClear(PyCSDL2_RWopsPtr *self)
{
    return 0;
}

/** \brief Destructor for PyCSDL2_RWopsPtrType */
static void
PyCSDL2_RWopsPtrDealloc(PyCSDL2_RWopsPtr *self)
{
    PyCSDL2_RWopsPtrClear(self);
    if (self->rwops) {
        if (self->rwops->close)
            self->rwops->close(self->rwops);
        else
            SDL_FreeRW(self->rwops);
    }
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Type definition for csdl2.SDL_RWopsPtr
 *
 * csdl2.SDL_RWopsPtr is an internal type that "owns" the SDL_RWops pointer.
 */
static PyTypeObject PyCSDL2_RWopsPtrType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_RWopsPtr",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWopsPtr),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RWopsPtrDealloc,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ 0,
    /* tp_str            */ 0,
    /* tp_getattro       */ 0,
    /* tp_setattro       */ 0,
    /* tp_as_buffer      */ 0,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    /* tp_doc            */ "Owner of SDL_RWops pointer",
    /* tp_traverse       */ (traverseproc) PyCSDL2_RWopsPtrTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_RWopsPtrClear
};

/**
 * \brief Creates a new PyCSDL2_RWopsPtr instance
 */
static PyCSDL2_RWopsPtr *
PyCSDL2_RWopsPtrCreate(SDL_RWops *rwops)
{
    PyCSDL2_RWopsPtr *self;
    PyTypeObject *type = &PyCSDL2_RWopsPtrType;
    if (!(self = (PyCSDL2_RWopsPtr*) type->tp_alloc(type, 0)))
        return NULL;
    self->rwops = rwops;
    return self;
}

/**
 * \brief Asserts that the PyCSDL2_RWopsPtr instance is valid
 *
 * \returns 0 on success, -1 on assertion failure.
 */
static int
PyCSDL2_RWopsPtrAssert(PyCSDL2_RWopsPtr *self)
{
    if (!self) {
        PyErr_SetString(PyExc_AssertionError,
                        "Invalid reference to PyCSDL2_RWopsPtr");
        return -1;
    }
    if (!self->rwops) {
        PyErr_SetString(PyExc_AssertionError,
                        "SDL_RWops already freed.");
        return -1;
    }
    return 0;
}

/** \brief Instance data for PyCSDL2_RWopsType */
typedef struct PyCSDL2_RWops {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief Pointer to the underlying PyCSDL2_RWopsPtr */
    PyCSDL2_RWopsPtr *ptr;
} PyCSDL2_RWops;

/** \brief Traversal function for PyCSDL2_RWopsType */
static int
PyCSDL2_RWopsTraverse(PyCSDL2_RWops *self, visitproc visit, void *arg)
{
    Py_VISIT(self->ptr);
    return 0;
}

/** \brief Clear function for PyCSDL2_RWopsType */
static int
PyCSDL2_RWopsClear(PyCSDL2_RWops *self)
{
    Py_CLEAR(self->ptr);
    return 0;
}

/** \brief Destructor for PYCSDL2_RWopsType */
static void
PyCSDL2_RWopsDealloc(PyCSDL2_RWops *self)
{
    PyCSDL2_RWopsClear(self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Implements getter for SDL_RWops.type */
static PyObject *
PyCSDL2_RWopsGetType(PyCSDL2_RWops *self, void *closure)
{
    if (PyCSDL2_RWopsPtrAssert(self->ptr))
        return NULL;
    return PyLong_FromUnsignedLong(self->ptr->rwops->type);
}

/** \brief Implements setter for SDL_RWops.type */
static int
PyCSDL2_RWopsSetType(PyCSDL2_RWops *self, PyObject *value, void *closure)
{
    unsigned long val;
    if (PyCSDL2_RWopsPtrAssert(self->ptr))
        return -1;
    val = PyLong_AsUnsignedLong(value);
    if (PyErr_Occurred())
        return -1;
    self->ptr->rwops->type = val;
    return 0;
}

/** \brief List of properties for PyCSDL2_RWopsType */
static PyGetSetDef PyCSDL2_RWopsGetSetters[] = {
    {"type",
     (getter) PyCSDL2_RWopsGetType,
     (setter) PyCSDL2_RWopsSetType,
     "Type of stream.",
     NULL},
    {NULL}
};

/**
 * \brief Type definition for csdl2.SDL_RWops
 */
static PyTypeObject PyCSDL2_RWopsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_RWops",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWops),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RWopsDealloc,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ 0,
    /* tp_str            */ 0,
    /* tp_getattro       */ 0,
    /* tp_setattro       */ 0,
    /* tp_as_buffer      */ 0,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    /* tp_doc            */
    "SDL_RWops",
    /* tp_traverse       */ (traverseproc) PyCSDL2_RWopsTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_RWopsClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_RWops, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_RWopsGetSetters,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ 0,
    /* tp_alloc          */ 0,
    /* tp_new            */ 0
};

/**
 * \brief Creates a new instance of PyCSDL2_RWopsType
 */
static PyCSDL2_RWops *
PyCSDL2_RWopsCreate(SDL_RWops *rwops)
{
    PyCSDL2_RWops *self;
    PyTypeObject *type = &PyCSDL2_RWopsType;
    PyCSDL2_RWopsPtr *ptr;
    if (!(ptr = PyCSDL2_RWopsPtrCreate(rwops)))
        return NULL;
    if (!(self = (PyCSDL2_RWops*)type->tp_alloc(type, 0))) {
        Py_DECREF(ptr);
        return NULL;
    }
    self->ptr = ptr;
    return self;
}

/**
 * \brief Implements csdl2.SDL_RWFromFile()
 *
 * \code
 * SDL_RWFromFile(file: str, mode: str) -> SDL_RWops
 * \endcode
 */
static PyCSDL2_RWops *
PyCSDL2_RWFromFile(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *file, *mode;
    SDL_RWops *ret;
    static char *kwlist[] = {"file", "mode", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist,
                                     &file, &mode))
        return NULL;
    if (!(ret = SDL_RWFromFile(file, mode)))
        return PyCSDL2_RaiseSDLError();
    return PyCSDL2_RWopsCreate(ret);
}

/**
 * \brief Implements csdl2.SDL_AllocRW()
 *
 * \code
 * SDL_AllocRW() -> SDL_RWops
 * \endcode
 */
static PyCSDL2_RWops *
PyCSDL2_AllocRW(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_RWops *ret;
    static char *kwlist[] = {NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;
    if (!(ret = SDL_AllocRW()))
        return PyCSDL2_RaiseSDLError();
    /*
     * PyCSDL2_RWopsPtr calls SDL_RWops.close if it is not NULL on destruction.
     * However, SDL_AllocRW() does not zero SDL_RWops on allocation, and thus
     * PyCSDL2_RWopsPtr will call an invalid pointer on destructor and cause a
     * segfault. Fix this by zeroing SDL_RWops.
     */
    memset(ret, 0, sizeof(SDL_RWops));
    return PyCSDL2_RWopsCreate(ret);
}

/**
 * \brief Initializes bindings to SDL_rwops.h
 *
 * Adds constants defined in SDL_rwops.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initrwops(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_RWOPS_UNKNOWN", SDL_RWOPS_UNKNOWN},
        {"SDL_RWOPS_WINFILE", SDL_RWOPS_WINFILE},
        {"SDL_RWOPS_STDFILE", SDL_RWOPS_STDFILE},
        {"SDL_RWOPS_JNIFILE", SDL_RWOPS_JNIFILE},
        {"SDL_RWOPS_MEMORY", SDL_RWOPS_MEMORY},
        {"SDL_RWOPS_MEMORY_RO", SDL_RWOPS_MEMORY_RO},

        {"RW_SEEK_SET", RW_SEEK_SET},
        {"RW_SEEK_CUR", RW_SEEK_CUR},
        {"RW_SEEK_END", RW_SEEK_END},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_RWopsPtrType)) { return 0; }

    if (PyType_Ready(&PyCSDL2_RWopsType)) { return 0; }
    Py_INCREF(&PyCSDL2_RWopsType);
    if (PyModule_AddObject(module, "SDL_RWops", (PyObject*)&PyCSDL2_RWopsType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RWOPS_H_ */
