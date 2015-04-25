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
 * \file surface.h
 * \brief Bindings for SDL_surface.h
 *
 * Implements bindings for SDL's surface creation and drawing API
 * (SDL_surface.h)
 */
#ifndef _PYCSDL2_SURFACE_H_
#define _PYCSDL2_SURFACE_H_
#include <Python.h>
#include <SDL_surface.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief Instance data for PyCSDL2_SurfacePixelsType */
typedef struct PyCSDL2_SurfacePixels {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief Pixels buffer */
    void *pixels;
    /** \brief Size of pixels buffer */
    Py_ssize_t len;
    /** \brief Pointer to the SDL_Surface that owns the pixels buffer */
    SDL_Surface *surface;
} PyCSDL2_SurfacePixels;

/** \brief Destructor for PyCSDL2_SurfacePixelsType */
static void
PyCSDL2_SurfacePixelsDealloc(PyCSDL2_SurfacePixels *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->surface)
        SDL_FreeSurface(self->surface);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief getbufferproc implementation for PyCSDL2_SurfacePixelsType */
static int
PyCSDL2_SurfacePixelsGetBuffer(PyCSDL2_SurfacePixels *self, Py_buffer *view,
                               int flags)
{
    return PyBuffer_FillInfo(view, (PyObject*) self, self->pixels, self->len,
                             0, flags);
}

/** \brief Buffer protocol definition for PyCSDL2_SurfacePixelsType */
static PyBufferProcs PyCSDL2_SurfacePixelsBufferProcs = {
    (getbufferproc) PyCSDL2_SurfacePixelsGetBuffer,
    (releasebufferproc) NULL
};

/** \brief Type definition for csdl2.SDL_SurfacePixels */
static PyTypeObject PyCSDL2_SurfacePixelsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_SurfacePixels",
    /* tp_basicsize      */ sizeof(PyCSDL2_SurfacePixels),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_SurfacePixelsDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_SurfacePixelsBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */ "Owner of SDL_Surface pixels buffer",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_SurfacePixels, in_weakreflist)
};

/**
 * \brief Creates an instance of PyCSDL2_SurfacePixelsType
 *
 * This will steal the reference to the SDL_Surface.
 * */
static PyCSDL2_SurfacePixels *
PyCSDL2_SurfacePixelsCreate(SDL_Surface *surface)
{
    PyCSDL2_SurfacePixels *self;
    PyTypeObject *type = &PyCSDL2_SurfacePixelsType;
    PyCSDL2_Assert(surface);
    PyCSDL2_Assert(surface->pixels);
    if (!(self = (PyCSDL2_SurfacePixels*)type->tp_alloc(type, 0)))
        return NULL;
    surface->refcount += 1;
    self->surface = surface;
    self->pixels = surface->pixels;
    self->len = surface->h * surface->pitch;
    return self;
}

/** \brief Instance data for PyCSDL2_SurfaceRectType */
typedef struct PyCSDL2_SurfaceRect {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief The SDL_Rect */
    SDL_Rect *rect;
    /** \brief Pointer to the SDL_Surface that owns the rect */
    SDL_Surface *surface;
} PyCSDL2_SurfaceRect;

/** \brief Destructor for PyCSDL2_SurfaceRectType */
static void
PyCSDL2_SurfaceRectDealloc(PyCSDL2_SurfaceRect *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->surface)
        SDL_FreeSurface(self->surface);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief getbufferproc implementation for PyCSDL2_SurfaceRectType */
static int
PyCSDL2_SurfaceRectGetBuffer(PyCSDL2_SurfaceRect *self, Py_buffer *view,
                             int flags)
{
    if ((flags & PyBUF_WRITABLE) == PyBUF_WRITABLE) {
        PyErr_SetString(PyExc_BufferError, "Object is not writable.");
        return -1;
    }
    view->buf = self->rect;
    Py_INCREF((PyObject*) self);
    view->obj = (PyObject*) self;
    view->len = sizeof(SDL_Rect);
    view->readonly = 1;
    view->itemsize = sizeof(SDL_Rect);
    view->format = "iiii";
    view->ndim = 0;
    view->shape = NULL;
    view->strides = NULL;
    view->suboffsets = NULL;
    view->internal = NULL;
    return 0;
}

/** \brief Buffer protocol definition for PyCSDL2_SurfaceRectType */
static PyBufferProcs PyCSDL2_SurfaceRectBufferProcs = {
    (getbufferproc) PyCSDL2_SurfaceRectGetBuffer,
    (releasebufferproc) NULL
};

/** \brief Getter for SDL_SurfaceRect.x */
static PyObject *
PyCSDL2_SurfaceRectGetX(PyCSDL2_SurfaceRect *self, void *closure)
{
    PyCSDL2_Assert(self->surface);
    return PyLong_FromLong(self->rect->x);
}

/** \brief Getter for SDL_SurfaceRect.y */
static PyObject *
PyCSDL2_SurfaceRectGetY(PyCSDL2_SurfaceRect *self, void *closure)
{
    PyCSDL2_Assert(self->surface);
    return PyLong_FromLong(self->rect->y);
}

/** \brief Getter for SDL_SurfaceRect.w */
static PyObject *
PyCSDL2_SurfaceRectGetW(PyCSDL2_SurfaceRect *self, void *closure)
{
    PyCSDL2_Assert(self->surface);
    return PyLong_FromLong(self->rect->w);
}

/** \brief Getter for SDL_SurfaceRect.h */
static PyObject *
PyCSDL2_SurfaceRectGetH(PyCSDL2_SurfaceRect *self, void *closure)
{
    PyCSDL2_Assert(self->surface);
    return PyLong_FromLong(self->rect->h);
}

/** \brief List of properties for PyCSDL2_SurfaceRectType */
static PyGetSetDef PyCSDL2_SurfaceRectGetSetters[] = {
    {"x",
     (getter) PyCSDL2_SurfaceRectGetX,
     (setter) NULL,
     "(readonly) The x location of the rectangle's upper left corner.",
     NULL},
    {"y",
     (getter) PyCSDL2_SurfaceRectGetY,
     (setter) NULL,
     "(readonly) The y location of the rectangle's upper left corner.",
     NULL},
    {"w",
     (getter) PyCSDL2_SurfaceRectGetW,
     (setter) NULL,
     "(readonly) The width of the rectangle.",
     NULL},
    {"h",
     (getter) PyCSDL2_SurfaceRectGetH,
     (setter) NULL,
     "(readonly) The height of the rectangle.",
     NULL},
    {NULL}
};

/** \brief Type definition for csdl2.SDL_SurfaceRect */
static PyTypeObject PyCSDL2_SurfaceRectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_SurfaceRect",
    /* tp_basicsize      */ sizeof(PyCSDL2_SurfaceRect),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_SurfaceRectDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_SurfaceRectBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "A 2d rectangle with its origin at the upper left corner.\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_SurfaceRect, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_SurfaceRectGetSetters
};

/** \brief Creates an instance of PyCSDL2_SurfaceRect */
PyCSDL2_SurfaceRect *
PyCSDL2_SurfaceRectCreate(SDL_Surface *surface, SDL_Rect *rect)
{
    PyCSDL2_SurfaceRect *self;
    PyTypeObject *type = &PyCSDL2_SurfaceRectType;

    PyCSDL2_Assert(surface);
    PyCSDL2_Assert(rect);
    if (!(self = (PyCSDL2_SurfaceRect*)type->tp_alloc(type, 0)))
        return NULL;
    surface->refcount += 1;
    self->surface = surface;
    self->rect = rect;
    return self;
}

/**
 * \brief Initializes bindings to SDL_surface.h
 *
 * Adds constants defined in SDL_surface.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initsurface(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_SWSURFACE", SDL_SWSURFACE},
        {"SDL_PREALLOC", SDL_PREALLOC},
        {"SDL_RLEACCEL", SDL_RLEACCEL},
        {"SDL_DONTFREE", SDL_DONTFREE},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_SurfacePixelsType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_SurfaceRectType)) { return 0; }

    return 1;
}

#endif /* _PYCSDL2_SURFACE_H_ */
