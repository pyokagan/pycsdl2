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
 * \file rect.h
 * \brief Bindings for SDL_rect.h
 *
 * Implements bindings for SDL's Rectangle functions (SDL_rect.h).
 */
#ifndef _PYCSDL2_RECT_H_
#define _PYCSDL2_RECT_H_
#include <Python.h>
#include <structmember.h>
#include <SDL_rect.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief Instance data for PyCSDL2_RectType */
typedef struct PyCSDL2_Rect {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief SDL_Rect this instance wraps */
    SDL_Rect rect;
} PyCSDL2_Rect;

/** \brief newfunc for PyCSDL2_RectType */
static PyCSDL2_Rect *
PyCSDL2_RectNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Rect *self;

    if (!(self = (PyCSDL2_Rect*)type->tp_alloc(type, 0)))
        return NULL;
    return self;
}

/** \brief Destructor for PyCSDL2_RectType */
static void
PyCSDL2_RectDealloc(PyCSDL2_Rect *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief initfunc for PyCSDL2_RectType */
static int
PyCSDL2_RectInit(PyCSDL2_Rect *self, PyObject *args, PyObject *kwds)
{
    int x = 0, y = 0, w = 0, h = 0;
    static char *kwlist[] = {"x", "y", "w", "h", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist,
                                     &x, &y, &w, &h))
        return -1;
    self->rect.x = x;
    self->rect.y = y;
    self->rect.w = w;
    self->rect.h = h;
    return 0;
}

/** \brief getbufferproc for PyCSDL2_RectType */
static int
PyCSDL2_RectGetBuffer(PyCSDL2_Rect *self, Py_buffer *view, int flags)
{
    view->buf = &self->rect;
    Py_INCREF((PyObject*) self);
    view->obj = (PyObject*) self;
    view->len = sizeof(SDL_Rect);
    view->readonly = 0;
    view->itemsize = sizeof(SDL_Rect);
    view->format = "iiii";
    view->ndim = 0;
    view->shape = NULL;
    view->strides = NULL;
    view->suboffsets = NULL;
    view->internal = NULL;
    return 0;
}

/** \brief Buffer protocol definition for PyCSDL2_RectType */
static PyBufferProcs PyCSDL2_RectBufferProcs = {
    (getbufferproc) PyCSDL2_RectGetBuffer,
    (releasebufferproc) NULL
};

/** \brief List of members in PyCSDL2_RectType */
static PyMemberDef PyCSDL2_RectMembers[] = {
    {"x", T_INT, offsetof(PyCSDL2_Rect, rect.x), 0,
     "The x location of the rectangle's upper left corner."},
    {"y", T_INT, offsetof(PyCSDL2_Rect, rect.y), 0,
     "The y location of the rectangle's upper left corner."},
    {"w", T_INT, offsetof(PyCSDL2_Rect, rect.w), 0,
     "The width of the rectangle."},
    {"h", T_INT, offsetof(PyCSDL2_Rect, rect.h), 0,
     "The height of the rectangle."},
    {NULL}
};

/** \brief Type definition for csdl2.SDL_Rect */
static PyTypeObject PyCSDL2_RectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Rect",
    /* tp_basicsize      */ sizeof(PyCSDL2_Rect),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RectDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_RectBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "A 2d rectangle with its origin at the upper left.",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Rect, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ PyCSDL2_RectMembers,
    /* tp_getset         */ 0,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ (initproc) PyCSDL2_RectInit,
    /* tp_alloc          */ 0,
    /* tp_new            */ (newfunc) PyCSDL2_RectNew
};

/**
 * \brief Creates a new PyCSDL2_Rect instance
 *
 * \param rect SDL_Rect to initialize the PyCSDL_Rect with
 * \returns The new PyCSDL_Rect object, or NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_RectCreate(const SDL_Rect *rect)
{
    PyCSDL2_Rect *self;

    self = PyCSDL2_RectNew(&PyCSDL2_RectType, NULL, NULL);
    if (!self)
        return NULL;

    if (rect)
        self->rect = *rect;

    return (PyObject*)self;
}

/**
 * \brief Borrows a pointer to the SDL_Rect managed by the PyCSDL2_Rect.
 *
 * \param obj The PyCSDL2_Rect object
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 with an exception set on failure.
 */
static int
PyCSDL2_RectPtr(PyObject *obj, SDL_Rect **out)
{
    PyCSDL2_Rect *self = (PyCSDL2_Rect*)obj;

    if (!PyCSDL2_Assert(obj))
        return 0;

    if (Py_TYPE(obj) != &PyCSDL2_RectType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_Rect", obj);
        return 0;
    }

    if (out)
        *out = &self->rect;

    return 1;
}

/** \brief converter for a readonly SDL_Rect exporting object */
static int
PyCSDL2_ConvertRectRead(PyObject *object, Py_buffer *view)
{
    if (!object) {
        PyBuffer_Release(view);
        return 1;
    }
    if (object == Py_None) {
        view->obj = NULL;
        view->buf = NULL;
        view->len = 0;
        return 1;
    }
    if (PyObject_GetBuffer(object, view, PyBUF_SIMPLE))
        return 0;
    if (!PyBuffer_IsContiguous(view, 'C')) {
        PyErr_SetString(PyExc_BufferError,
                        "SDL_Rect buffer must be C-contiguous");
        PyBuffer_Release(view);
        return 0;
    }
    if (view->len != sizeof(SDL_Rect)) {
        size_t expected = sizeof(SDL_Rect);
        PyErr_Format(PyExc_BufferError, "Invalid SDL_Rect buffer size. "
                     "Expected: %zu. Got: %zd", expected, view->len);
        PyBuffer_Release(view);
        return 0;
    }
    return Py_CLEANUP_SUPPORTED;
}

/**
 * \brief Implements csdl2.SDL_HasIntersection()
 *
 * \code{.py}
 * SDL_HasIntersection(A: SDL_Rect, B: SDL_Rect) -> bool
 * \endcode
 */
static PyObject *
PyCSDL2_HasIntersection(PyObject *module, PyObject *args, PyObject *kwds)
{
    Py_buffer a, b;
    static char *kwlist[] = {"A", "B", NULL};
    int ret;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
                                     PyCSDL2_ConvertRectRead, &a,
                                     PyCSDL2_ConvertRectRead, &b))
        return NULL;
    ret = SDL_HasIntersection(a.buf, b.buf);
    PyBuffer_Release(&a);
    PyBuffer_Release(&b);
    return PyBool_FromLong(ret);
}

/**
 * \brief Initializes bindings to SDL_rect.h
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initrect(PyObject *module)
{
    if (PyType_Ready(&PyCSDL2_RectType) < 0) return 0;
    Py_INCREF(&PyCSDL2_RectType);
    if (PyModule_AddObject(module, "SDL_Rect", (PyObject*) &PyCSDL2_RectType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RECT_H_ */
