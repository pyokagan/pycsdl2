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
#include "pixels.h"
#include "rwops.h"

/** \brief Instance data for PyCSDL2_SurfacePixelsType */
typedef struct PyCSDL2_SurfacePixels {
    PyCSDL2_BufferHEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
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

/**
 * \brief Validates the PyCSDL2_SurfacePixels object.
 *
 * A PyCSDL2_SurfacePixels object is valid if self->pixels and self->surface
 * are not NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_SurfacePixelsValid(PyCSDL2_SurfacePixels *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!self->surface) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_SurfacePixels");
        return 0;
    }

    if (!PyCSDL2_BufferValid((PyCSDL2_Buffer*) self))
        return 0;

    return 1;
}

/** \brief getbufferproc implementation for PyCSDL2_SurfacePixelsType */
static int
PyCSDL2_SurfacePixelsGetBuffer(PyCSDL2_SurfacePixels *self, Py_buffer *view,
                               int flags)
{
    if (!PyCSDL2_SurfacePixelsValid(self))
        return -1;

    return PyCSDL2_BufferGetBuffer((PyCSDL2_Buffer*) self, view, flags);
}

/** \brief Buffer protocol definition for PyCSDL2_SurfacePixelsType */
static PyBufferProcs PyCSDL2_SurfacePixelsBufferProcs = {
    (getbufferproc) PyCSDL2_SurfacePixelsGetBuffer,
    (releasebufferproc) PyCSDL2_BufferReleaseBuffer
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
    /* tp_as_sequence    */ &PyCSDL2_BufferAsSequence,
    /* tp_as_mapping     */ &PyCSDL2_BufferAsMapping,
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

    if (!PyCSDL2_Assert(surface))
        return NULL;

    if (!PyCSDL2_Assert(surface->pixels))
        return NULL;

    if (!(self = (PyCSDL2_SurfacePixels*)type->tp_alloc(type, 0)))
        return NULL;

    PyCSDL2_BufferInit((PyCSDL2_Buffer*) self, CTYPE_UCHAR, surface->pixels,
                       surface->h * surface->pitch, 0);

    surface->refcount += 1;
    self->surface = surface;
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

/**
 * \brief Validates the PyCSDL2_SurfaceRect object.
 *
 * A PyCSDL2_SurfaceRect object is valid if self->rect and self->surface are
 * not NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_SurfaceRectValid(PyCSDL2_SurfaceRect *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!self->surface) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_SurfaceRect");
        return 0;
    }

    if (!PyCSDL2_Assert(self->rect))
        return 0;

    return 1;
}

/** \brief getbufferproc implementation for PyCSDL2_SurfaceRectType */
static int
PyCSDL2_SurfaceRectGetBuffer(PyCSDL2_SurfaceRect *self, Py_buffer *view,
                             int flags)
{
    if (!PyCSDL2_SurfaceRectValid(self))
        return -1;

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
    if (!PyCSDL2_SurfaceRectValid(self))
        return NULL;
    return PyLong_FromLong(self->rect->x);
}

/** \brief Getter for SDL_SurfaceRect.y */
static PyObject *
PyCSDL2_SurfaceRectGetY(PyCSDL2_SurfaceRect *self, void *closure)
{
    if (!PyCSDL2_SurfaceRectValid(self))
        return NULL;
    return PyLong_FromLong(self->rect->y);
}

/** \brief Getter for SDL_SurfaceRect.w */
static PyObject *
PyCSDL2_SurfaceRectGetW(PyCSDL2_SurfaceRect *self, void *closure)
{
    if (!PyCSDL2_SurfaceRectValid(self))
        return NULL;
    return PyLong_FromLong(self->rect->w);
}

/** \brief Getter for SDL_SurfaceRect.h */
static PyObject *
PyCSDL2_SurfaceRectGetH(PyCSDL2_SurfaceRect *self, void *closure)
{
    if (!PyCSDL2_SurfaceRectValid(self))
        return NULL;
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

    if (!PyCSDL2_Assert(surface))
        return NULL;

    if (!PyCSDL2_Assert(rect))
        return NULL;

    if (!(self = (PyCSDL2_SurfaceRect*)type->tp_alloc(type, 0)))
        return NULL;
    surface->refcount += 1;
    self->surface = surface;
    self->rect = rect;
    return self;
}

/** \brief Instance data for PyCSDL2_SurfaceType */
typedef struct PyCSDL2_Surface {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief Pointer to the SDL_Surface that this instance owns */
    SDL_Surface *surface;
    /** \brief stores "format" object for Python access */
    PyCSDL2_PixelFormat *format;
    /** \brief stores "pixels" object for Python access */
    PyObject *pixels;
    /** \brief holds the buffer to the "pixels" object */
    Py_buffer pixels_buf;
    /** \brief stores "userdata" attribute for Python access */
    PyObject *userdata;
    /** \brief stores "clip_rect" object for Python access */
    PyCSDL2_SurfaceRect *clip_rect;
} PyCSDL2_Surface;

static PyTypeObject PyCSDL2_SurfaceType;

/** \brief Traversal function for PyCSDL2_SurfaceType */
static int
PyCSDL2_SurfaceTraverse(PyCSDL2_Surface *self, visitproc visit, void *arg)
{
    Py_VISIT(self->format);
    Py_VISIT(self->pixels);
    if (self->pixels_buf.obj)
        Py_VISIT(self->pixels_buf.obj);
    Py_VISIT(self->userdata);
    Py_VISIT(self->clip_rect);
    return 0;
}

/** \brief Clear function for PyCSDL2_SurfaceType */
static int
PyCSDL2_SurfaceClear(PyCSDL2_Surface *self)
{
    if (self->pixels_buf.obj) {
        if (self->surface)
            self->surface->pixels = NULL;
        PyBuffer_Release(&self->pixels_buf);
    }
    Py_CLEAR(self->format);
    Py_CLEAR(self->pixels);
    Py_CLEAR(self->userdata);
    Py_CLEAR(self->clip_rect);
    if (self->surface)
        SDL_FreeSurface(self->surface);
    self->surface = NULL;
    return 0;
}

/** \brief Destructor for PyCSDL2_SurfaceType */
static void
PyCSDL2_SurfaceDealloc(PyCSDL2_Surface *self)
{
    PyCSDL2_SurfaceClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Validates a PyCSDL2_Surface object.
 *
 * A PyCSDL2_Surface object is valid if its internal SDL_Surface pointer is not
 * NULL. Otherwise, raise a ValueError;
 *
 * \param surface PyCSDL2_Surface object to validate.
 * \returns 1 if surface is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_SurfaceValid(PyCSDL2_Surface *surface)
{
    if (!PyCSDL2_Assert(surface))
        return 0;

    if (Py_TYPE(surface) != &PyCSDL2_SurfaceType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_Surface", (PyObject*)surface);
        return 0;
    }

    if (!surface->surface) {
        PyErr_SetString(PyExc_ValueError, "Invalid SDL_Surface");
        return 0;
    }
    return 1;
}

/**
 * \brief Borrow the SDL_Surface managed by the PyCSDL2_Surface object.
 *
 * \param obj The SDL_Surface object
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_SurfacePtr(PyObject *obj, SDL_Surface **out)
{
    PyCSDL2_Surface *self = (PyCSDL2_Surface*)obj;

    if (!PyCSDL2_SurfaceValid(self))
        return 0;

    if (out)
        *out = self->surface;

    return 1;
}

/** \brief Getter for SDL_Surface.flags */
static PyObject *
PyCSDL2_SurfaceGetFlags(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->surface->flags);
}

/** \brief Getter for SDL_Surface.format */
static PyObject *
PyCSDL2_SurfaceGetFormat(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyCSDL2_Get((PyObject*) self->format);
}

/** \brief Getter for SDL_Surface.w */
static PyObject *
PyCSDL2_SurfaceGetW(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyLong_FromLong(self->surface->w);
}

/** \brief Getter for SDL_Surface.h */
static PyObject *
PyCSDL2_SurfaceGetH(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyLong_FromLong(self->surface->h);
}

/** \brief Getter for SDL_Surface.pitch */
static PyObject *
PyCSDL2_SurfaceGetPitch(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyLong_FromLong(self->surface->pitch);
}

/** \brief Getter for SDL_Surface.pixels */
static PyObject *
PyCSDL2_SurfaceGetPixels(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyCSDL2_Get(self->pixels);
}

/** \brief Getter for SDL_Surface.userdata */
static PyObject *
PyCSDL2_SurfaceGetUserdata(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyCSDL2_Get(self->userdata);
}

/** \brief Setter for SDL_Surface.userdata */
static int
PyCSDL2_SurfaceSetUserdata(PyCSDL2_Surface *self, PyObject *value,
                           void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return -1;
    PyCSDL2_Set(self->userdata, value);
    return 0;
}

/** \brief Getter for SDL_Surface.locked */
static PyObject *
PyCSDL2_SurfaceGetLocked(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyBool_FromLong(self->surface->locked);
}

/** \brief Getter for SDL_Surface.refcount */
static PyObject *
PyCSDL2_SurfaceGetRefcount(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyLong_FromLong(self->surface->refcount);
}

/** \brief Getter for SDL_Surface.clip_rect */
static PyObject *
PyCSDL2_SurfaceGetClipRect(PyCSDL2_Surface *self, void *closure)
{
    if (!PyCSDL2_SurfaceValid(self))
        return NULL;
    return PyCSDL2_Get((PyObject*) self->clip_rect);
}

/** \brief List of properties for PyCSDL2_SurfaceType */
static PyGetSetDef PyCSDL2_SurfaceGetSetters[] = {
    {"flags",
     (getter) PyCSDL2_SurfaceGetFlags,
     (setter) NULL,
     "(readonly) Flags set on the surface. For internal use.",
     NULL},
    {"format",
     (getter) PyCSDL2_SurfaceGetFormat,
     (setter) NULL,
     "(readonly) Format of pixels stored in the surface.",
     NULL},
    {"w",
     (getter) PyCSDL2_SurfaceGetW,
     (setter) NULL,
     "(readonly) Width of surface in pixels.",
     NULL},
    {"h",
     (getter) PyCSDL2_SurfaceGetH,
     (setter) NULL,
     "(readonly) Height of surface in pixels.",
     NULL},
    {"pitch",
     (getter) PyCSDL2_SurfaceGetPitch,
     (setter) NULL,
     "(readonly) The length of a row of pixels in bytes.",
     NULL},
    {"pixels",
     (getter) PyCSDL2_SurfaceGetPixels,
     (setter) NULL,
     "The actual pixel data.",
     NULL},
    {"userdata",
     (getter) PyCSDL2_SurfaceGetUserdata,
     (setter) PyCSDL2_SurfaceSetUserdata,
     "Application-specific data associated with the surface.",
     NULL},
    {"locked",
     (getter) PyCSDL2_SurfaceGetLocked,
     (setter) NULL,
     "(readonly) True if the surface is locked.",
     NULL},
    {"clip_rect",
     (getter) PyCSDL2_SurfaceGetClipRect,
     (setter) NULL,
     "(readonly) Clipping information for the surface.",
     NULL},
    {"refcount",
     (getter) PyCSDL2_SurfaceGetRefcount,
     (setter) NULL,
     "(readonly) SDL's reference count of the surface.",
     NULL},
    {NULL}
};

/** \brief Type definition for csdl2.SDL_Surface */
static PyTypeObject PyCSDL2_SurfaceType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Surface",
    /* tp_basicsize      */ sizeof(PyCSDL2_Surface),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_SurfaceDealloc,
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
    "SDL_Surface",
    /* tp_traverse       */ (traverseproc) PyCSDL2_SurfaceTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_SurfaceClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Surface, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_SurfaceGetSetters,
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
 * \brief Creates a new instance of PyCSDL2_SurfaceType.
 *
 * This will steal the reference to the SDL_Surface.
 *
 * \param surface The SDL_Surface to wrap. The reference to the SDL_Surface
 *                 will be stolen.
 * \param pixels Python object owning the surface->pixels buffer. It must
 *               implement the buffer protocol. If NULL, it is assumed that the
 *               SDL surface owns the pixel buffer, and a memoryview will be
 *               created.
 */
static PyObject *
PyCSDL2_SurfaceCreate(SDL_Surface *surface, PyObject *pixels)
{
    PyCSDL2_Surface *self;
    PyTypeObject *type = &PyCSDL2_SurfaceType;

    if (!PyCSDL2_Assert(surface))
        return NULL;

    if (!PyCSDL2_Assert(surface->format))
        return NULL;

    if (!(self = (PyCSDL2_Surface*)type->tp_alloc(type, 0)))
        return NULL;
    surface->format->refcount += 1;
    self->format = (PyCSDL2_PixelFormat*)PyCSDL2_PixelFormatCreate(surface->format);
    if (!self->format) {
        surface->format->refcount -= 1;
        Py_DECREF(self);
        return NULL;
    }
    if (pixels) {
        if (PyObject_GetBuffer(pixels, &self->pixels_buf,
                               PyBUF_WRITABLE | PyBUF_ND)) {
            Py_DECREF(self);
            return NULL;
        }
        Py_INCREF(pixels);
        self->pixels = pixels;
        surface->pixels = self->pixels_buf.buf;
    } else if (surface->pixels) {
        PyCSDL2_SurfacePixels *pixels;

        if (!(pixels = PyCSDL2_SurfacePixelsCreate(surface))) {
            Py_DECREF(self);
            return NULL;
        }
        self->pixels = (PyObject*) pixels;
    }
    if (!(self->clip_rect = PyCSDL2_SurfaceRectCreate(surface,
                                                      &surface->clip_rect))) {
        Py_DECREF(self);
        return NULL;
    }
    self->surface = surface;
    return (PyObject*)self;
}

/**
 * \brief Implements csdl2.SDL_MUSTLOCK()
 *
 * \code{.py}
 * SDL_MUSTLOCK(surface: SDL_Surface) -> bool
 * \endcode
 */
static PyObject *
PyCSDL2_MUSTLOCK(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Surface *surface;
    static char *kwlist[] = {"surface", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_SurfaceType, &surface))
        return NULL;
    if (!PyCSDL2_SurfaceValid(surface))
        return NULL;
    return PyBool_FromLong(SDL_MUSTLOCK(surface->surface));
}

/**
 * \brief Implements csdl2.SDL_CreateRGBSurface()
 *
 * \code{.py}
 * SDL_CreateRGBSurface(flags: int, width: int, height: int, depth: int,
 *                      Rmask: int, Gmask: int, Bmask: int, Amask: int)
 *                      -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2_CreateRGBSurface(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 flags, Rmask, Gmask, Bmask, Amask;
    int width, height, depth;
    SDL_Surface *ret;
    PyObject *out;
    static char *kwlist[] = {"flags", "width", "height", "depth", "Rmask",
                             "Gmask", "Bmask", "Amask", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT "iii" Uint32_UNIT
                                     Uint32_UNIT Uint32_UNIT Uint32_UNIT,
                                     kwlist, &flags, &width, &height, &depth,
                                     &Rmask, &Gmask, &Bmask, &Amask))
        return NULL;
    if (!(ret = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask,
                                     Bmask, Amask)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_SurfaceCreate(ret, NULL))) {
        SDL_FreeSurface(ret);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_CreateRGBSurfaceFrom()
 *
 * \code{.py}
 * SDL_CreateRGBSurfaceFrom(pixels: buffer, width: int, height: int,
 *                          depth: int, pitch: int, Rmask: int, Gmask: int,
 *                          Bmask: int, Amask: int) -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2_CreateRGBSurfaceFrom(PyObject *module, PyObject *args, PyObject *kwds)
{
    int width, height, depth, pitch;
    Uint32 Rmask, Gmask, Bmask, Amask;
    PyObject *pixels;
    Py_buffer buf;
    SDL_Surface *surface;
    PyObject *out;
    static char *kwlist[] = {"pixels", "width", "height", "depth", "pitch",
                             "Rmask", "Gmask", "Bmask", "Amask", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Oiiii" Uint32_UNIT
                                     Uint32_UNIT Uint32_UNIT Uint32_UNIT,
                                     kwlist, &pixels, &width, &height, &depth,
                                     &pitch, &Rmask, &Gmask, &Bmask, &Amask))
        return NULL;
    if (pixels == Py_None) {
        buf.obj = NULL;
        buf.buf = NULL;
    } else if (PyObject_GetBuffer(pixels, &buf, PyBUF_WRITABLE | PyBUF_ND)) {
        return NULL;
    } else if (!PyBuffer_IsContiguous(&buf, 'C')) {
        PyErr_SetString(PyExc_BufferError, "Pixels buffer is not "
                        "C Contiguous");
        PyBuffer_Release(&buf);
        return NULL;
    } else if (buf.len != pitch * height) {
        Py_ssize_t expected = pitch * height;
        PyErr_Format(PyExc_BufferError, "Invalid pixels buffer size. "
                     "Expected: %zd. Got: %zd.", expected, buf.len);
        PyBuffer_Release(&buf);
        return NULL;
    }
    surface = SDL_CreateRGBSurfaceFrom(buf.buf, width, height, depth, pitch,
                                       Rmask, Gmask, Bmask, Amask);
    if (!surface) {
        PyBuffer_Release(&buf);
        return PyCSDL2_RaiseSDLError();
    }
    if (pitch < surface->format->BytesPerPixel * surface->w) {
        int expected = surface->format->BytesPerPixel * surface->w;
        SDL_FreeSurface(surface);
        PyBuffer_Release(&buf);
        PyErr_Format(PyExc_ValueError, "Invalid pitch. "
                     "Expected at least: %d. Got: %d", expected, pitch);
        return NULL;
    }
    if (!(out = PyCSDL2_SurfaceCreate(surface, pixels))) {
        SDL_FreeSurface(surface);
        PyBuffer_Release(&buf);
        return NULL;
    }
    PyBuffer_Release(&buf);
    return out;
}

/**
 * \brief Implements csdl2.SDL_FreeSurface()
 *
 * \code{.py}
 * SDL_FreeSurface(surface: SDL_Surface) -> NULL
 * \endcode
 */
static PyObject *
PyCSDL2_FreeSurface(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Surface *surface;
    static char *kwlist[] = {"surface", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_SurfaceType, &surface))
        return NULL;
    if (!PyCSDL2_SurfaceValid(surface))
        return NULL;
    PyCSDL2_SurfaceClear(surface);
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_LoadBMP_RW()
 *
 * \code{.py}
 * SDL_LoadBMP_RW(src: SDL_RWops, freesrc: bool) -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2_LoadBMP_RW(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RWops *src_obj;
    SDL_RWops *src = NULL;
    int freesrc;
    SDL_Surface *ret;
    static char *kwlist[] = {"src", "freesrc", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!p", kwlist,
                                     &PyCSDL2_RWopsType, &src_obj, &freesrc))
        return NULL;

    if (!PyCSDL2_RWopsPtr((PyObject*)src_obj, &src))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    ret = SDL_LoadBMP_RW(src, freesrc);
    Py_END_ALLOW_THREADS

    if (freesrc)
        PyCSDL2_RWopsDetach(src_obj);

    if (!ret)
        return PyCSDL2_RaiseSDLError();

    return PyCSDL2_SurfaceCreate(ret, NULL);
}

/**
 * \brief Implements csdl2.SDL_LoadBMP()
 *
 * \code{.py}
 * SDL_LoadBMP(file: str) -> SDL_Surface
 * \endcode
 */
static PyObject *
PyCSDL2_LoadBMP(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyObject *file_obj;
    const char *file;
    SDL_Surface *ret;
    static char *kwlist[] = {"file", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyUnicode_FSConverter, &file_obj))
        return NULL;

    file = PyBytes_AsString(file_obj);
    if (!file) {
        Py_DECREF(file_obj);
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    ret = SDL_LoadBMP(file);
    Py_END_ALLOW_THREADS

    Py_DECREF(file_obj);

    if (!ret)
        return PyCSDL2_RaiseSDLError();

    return PyCSDL2_SurfaceCreate(ret, NULL);
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

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_SurfacePixelsType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_SurfaceRectType)) { return 0; }

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_SurfaceType) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_SURFACE_H_ */
