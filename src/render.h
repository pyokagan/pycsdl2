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
 * \file render.h
 * \brief Bindings for SDL_render.h
 *
 * Implements bindings for SDL's 2D Accelerated Rendering API (SDL_render.h)
 */
#ifndef _PYCSDL2_RENDER_H_
#define _PYCSDL2_RENDER_H_
#include <Python.h>
#include <SDL_render.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"
#include "video.h"
#include "surface.h"
#include "rect.h"

/**
 * \defgroup csdl2_PyCSDL2_RendererInfoMem csdl2.PyCSDL2_RendererInfoMem
 *
 * \brief Manages the SDL_RendererInfo buffer
 *
 * @{
 */

/** \brief Instance data of PyCSDL2_RendererInfoMemType */
typedef struct PyCSDL2_RendererInfoMem {
    PyObject_HEAD
    /** \brief The wrapped SDL_RendererInfo struct */
    SDL_RendererInfo info;
    /** \brief Associated "name" str object */
    PyObject *name;
} PyCSDL2_RendererInfoMem;

static PyTypeObject PyCSDL2_RendererInfoMemType;

/** \brief tp_dealloc for PyCSDL2_RendererInfoMemType */
static void
PyCSDL2_RendererInfoMemDealloc(PyCSDL2_RendererInfoMem *self)
{
    Py_CLEAR(self->name);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/** \brief Validates the PyCSDL2_RendererInfoMem */
static int
PyCSDL2_RendererInfoMemValid(PyCSDL2_RendererInfoMem *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!PyCSDL2_Assert(Py_TYPE(self) == &PyCSDL2_RendererInfoMemType))
        return 0;

    if (self->name && !PyCSDL2_Assert(PyUnicode_CheckExact(self->name)))
        return 0;

    return 1;
}

/** \brief Type definition for csdl2.PyCSDL2_RendererInfoMem */
static PyTypeObject PyCSDL2_RendererInfoMemType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.PyCSDL2_RendererInfoMem",
    /* tp_basicsize      */ sizeof(PyCSDL2_RendererInfoMem),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RendererInfoMemDealloc,
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
    /* tp_flags          */ Py_TPFLAGS_DEFAULT
};

/**
 * \brief Creates a new PyCSDL2_RendererInfoMem.
 */
static PyCSDL2_RendererInfoMem *
PyCSDL2_RendererInfoMemCreate(const SDL_RendererInfo *info)
{
    PyCSDL2_RendererInfoMem *self;
    PyTypeObject *type = &PyCSDL2_RendererInfoMemType;

    self = (PyCSDL2_RendererInfoMem*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    if (info)
        self->info = *info;

    return self;
}

/** @} */

/**
 * \defgroup csdl2_SDL_RendererInfo csdl2.SDL_RendererInfo
 *
 * \brief Bindings for SDL_RendererInfo struct.
 *
 * @{
 */

/** \brief Instance data of PyCSDL2_RendererInfoType */
typedef struct PyCSDL2_RendererInfo {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief Underlying SDL_RendererInfo buffer */
    PyCSDL2_RendererInfoMem *info_mem;
    /** \brief Buffer to expose the "texture_formats" array */
    PyCSDL2_Buffer *texture_formats;
} PyCSDL2_RendererInfo;

static PyTypeObject PyCSDL2_RendererInfoType;

/** \brief Destructor for PyCSDL2_RendererInfoType */
static void
PyCSDL2_RendererInfoDealloc(PyCSDL2_RendererInfo *self)
{
    Py_CLEAR(self->texture_formats);
    Py_CLEAR(self->info_mem);
    PyObject_ClearWeakRefs((PyObject*)self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/** \brief tp_new for PyCSDL2_RendererInfoType */
static PyCSDL2_RendererInfo *
PyCSDL2_RendererInfoNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RendererInfo *self;
    PyCSDL2_Buffer *buf;

    self = (PyCSDL2_RendererInfo*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->info_mem = PyCSDL2_RendererInfoMemCreate(NULL);
    if (!self->info_mem) {
        Py_DECREF(self);
        return NULL;
    }

    buf = PyCSDL2_BufferCreate(CTYPE_UINT32,
                               self->info_mem->info.texture_formats,
                               SDL_arraysize(self->info_mem->info.texture_formats),
                               0, (PyObject*)self->info_mem);
    if (!buf) {
        Py_DECREF(self);
        return NULL;
    }

    self->texture_formats = buf;

    return self;
}

/** \brief Validates the PyCSDL2_RendererInfo object */
static int
PyCSDL2_RendererInfoValid(PyCSDL2_RendererInfo *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_RendererInfoType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_RendererInfo", (PyObject*)self);
        return 0;
    }

    if (!PyCSDL2_Assert(self->info_mem) ||
        !PyCSDL2_Assert(self->texture_formats))
        return 0;

    if (!PyCSDL2_RendererInfoMemValid(self->info_mem))
        return 0;

    return 1;
}

/** \brief Getter for SDL_RendererInfo.name */
static PyObject *
PyCSDL2_RendererInfoGetName(PyCSDL2_RendererInfo *self, void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    if (self->info_mem->info.name)
        return PyUnicode_FromString(self->info_mem->info.name);
    else
        Py_RETURN_NONE;
}

/** \brief Setter for SDL_RendererInfo.name */
static int
PyCSDL2_RendererInfoSetName(PyCSDL2_RendererInfo *self, PyObject *value,
                            void *closure)
{
    const char *name;

    if (!PyCSDL2_RendererInfoValid(self))
        return -1;

    if (!PyUnicode_CheckExact(value)) {
        PyCSDL2_RaiseTypeError("name", "str", value);
        return -1;
    }

    name = PyUnicode_AsUTF8(value);
    if (!name)
        return -1;

    self->info_mem->info.name = name;
    PyCSDL2_Set(self->info_mem->name, value);
    return 0;
}

/** \brief Getter for SDL_RendererInfo.flags */
static PyObject *
PyCSDL2_RendererInfoGetFlags(PyCSDL2_RendererInfo *self, void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->info_mem->info.flags);
}

/** \brief Setter for SDL_RendererInfo.flags */
static int
PyCSDL2_RendererInfoSetFlags(PyCSDL2_RendererInfo *self, PyObject *value,
                             void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->info_mem->info.flags);
}

/** \brief Getter for SDL_RendererInfo.num_texture_formats */
static PyObject *
PyCSDL2_RendererInfoGetNumTextureFormats(PyCSDL2_RendererInfo *self,
                                         void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->info_mem->info.num_texture_formats);
}

/** \brief Setter for SDL_RendererInfo.num_texture_formats */
static int
PyCSDL2_RendererInfoSetNumTextureFormats(PyCSDL2_RendererInfo *self,
                                         PyObject *value, void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value,
                                &self->info_mem->info.num_texture_formats);
}

/** \brief Getter for SDL_RendererInfo.texture_formats */
static PyObject *
PyCSDL2_RendererInfoGetTextureFormats(PyCSDL2_RendererInfo *self,
                                      void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    return PyCSDL2_Get((PyObject*)self->texture_formats);
}

/** \brief Getter for SDL_RendererInfo.max_texture_width */
static PyObject *
PyCSDL2_RendererInfoGetMaxTextureWidth(PyCSDL2_RendererInfo *self,
                                       void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    return PyLong_FromLong(self->info_mem->info.max_texture_width);
}

/** \brief Setter for SDL_RendererInfo.max_texture_width */
static int
PyCSDL2_RendererInfoSetMaxTextureWidth(PyCSDL2_RendererInfo *self,
                                       PyObject *value, void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return -1;
    return PyCSDL2_LongAsInt(value, &self->info_mem->info.max_texture_width);
}

/** \brief Getter for SDL_RendererInfo.max_texture_height */
static PyObject *
PyCSDL2_RendererInfoGetMaxTextureHeight(PyCSDL2_RendererInfo *self,
                                        void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return NULL;
    return PyLong_FromLong(self->info_mem->info.max_texture_height);
}

/** \brief Setter for SDL_RendererInfo.max_texture_height */
static int
PyCSDL2_RendererInfoSetMaxTextureHeight(PyCSDL2_RendererInfo *self,
                                        PyObject *value, void *closure)
{
    if (!PyCSDL2_RendererInfoValid(self))
        return -1;
    return PyCSDL2_LongAsInt(value, &self->info_mem->info.max_texture_height);
}

/** \brief List of attributes for PyCSDL2_RendererInfoType */
static PyGetSetDef PyCSDL2_RendererInfoGetSetters[] = {
    {"name",
     (getter)PyCSDL2_RendererInfoGetName,
     (setter)PyCSDL2_RendererInfoSetName,
     "Name of the renderer.",
     NULL},
    {"flags",
     (getter)PyCSDL2_RendererInfoGetFlags,
     (setter)PyCSDL2_RendererInfoSetFlags,
     "A mask of supported renderer flags. 0 or one or more of the following\n"
     "flags OR'd together:\n"
     "\n"
     "* SDL_RENDERER_SOFTWARE -- The renderer is a software fallback.\n"
     "* SDL_RENDERER_ACCELERATED -- The renderer uses hardware acceleration.\n"
     "* SDL_RENDERER_PRESENTVSYNC -- The renderer is synchronized with the\n"
     "                               refresh rate.\n"
     "* SDL_RENDERER_TARGETTEXTURE -- The renderer supports rendering to\n"
     "                                texture.\n",
     NULL},
    {"num_texture_formats",
     (getter)PyCSDL2_RendererInfoGetNumTextureFormats,
     (setter)PyCSDL2_RendererInfoSetNumTextureFormats,
     "The number of available texture formats.",
     NULL},
    {"texture_formats",
     (getter)PyCSDL2_RendererInfoGetTextureFormats,
     (setter)NULL,
     "The available texture formats as an array of SDL_PIXELFORMAT_* ints.",
     NULL},
    {"max_texture_width",
     (getter)PyCSDL2_RendererInfoGetMaxTextureWidth,
     (setter)PyCSDL2_RendererInfoSetMaxTextureWidth,
     "The maximum texture width.",
     NULL},
    {"max_texture_height",
     (getter)PyCSDL2_RendererInfoGetMaxTextureHeight,
     (setter)PyCSDL2_RendererInfoSetMaxTextureHeight,
     "The maximum texture height.",
     NULL},
    {NULL}
};

/** \brief tp_init for PyCSDL2_RendererInfoType */
static int
PyCSDL2_RendererInfoInit(PyObject *obj, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RendererInfo *self = (PyCSDL2_RendererInfo*)obj;
    PyObject *name = NULL;
    Py_buffer texture_formats = {0};
    Uint32 flags = 0, num_texture_formats = 0;
    int max_texture_width = 0, max_texture_height = 0;
    Py_ssize_t x = sizeof(self->info_mem->info.texture_formats);
    static char *kwlist[] = {"name", "flags", "num_texture_formats",
                             "texture_formats", "max_texture_width",
                             "max_texture_height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "|O" Uint32_UNIT Uint32_UNIT "y*ii",
                                     kwlist, &name, &flags,
                                     &num_texture_formats, &texture_formats,
                                     &max_texture_width, &max_texture_height))
        return -1;

    if (!PyCSDL2_RendererInfoValid(self))
        goto fail;

    if (texture_formats.buf && texture_formats.len < x) {
        PyCSDL2_RaiseBufferSizeError("texture_formats", x, texture_formats.len);
        goto fail;
    }

    if (name) {
        if (PyCSDL2_RendererInfoSetName(self, name, NULL) < 0)
            goto fail;
    } else {
        self->info_mem->info.name = NULL;
        Py_CLEAR(self->info_mem->name);
    }

    if (name && PyCSDL2_RendererInfoSetName(self, name, NULL) < 0)
        goto fail;

    self->info_mem->info.flags = flags;
    self->info_mem->info.num_texture_formats = num_texture_formats;

    if (texture_formats.buf)
        memcpy(self->info_mem->info.texture_formats, texture_formats.buf, x);
    else
        memset(self->info_mem->info.texture_formats, 0, x);

    self->info_mem->info.max_texture_width = max_texture_width;
    self->info_mem->info.max_texture_height = max_texture_height;

    PyBuffer_Release(&texture_formats);
    return 0;

fail:
    PyBuffer_Release(&texture_formats);
    return -1;
}

/** \brief Type definition for csdl2.SDL_RendererInfo */
static PyTypeObject PyCSDL2_RendererInfoType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_RendererInfo",
    /* tp_basicsize      */ sizeof(PyCSDL2_RendererInfo),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RendererInfoDealloc,
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
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "Information on the capabilities of a render driver or context.\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_RendererInfo, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_RendererInfoGetSetters,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ PyCSDL2_RendererInfoInit,
    /* tp_alloc          */ 0,
    /* tp_new            */ (newfunc)PyCSDL2_RendererInfoNew
};

/**
 * \brief Creates an instance of PyCSDL2_RendererInfoType.
 *
 * \param info SDL_RendererInfo data to initialize the object with, or NULL to
 *             zero it.
 */
static PyObject *
PyCSDL2_RendererInfoCreate(const SDL_RendererInfo *info)
{
    PyCSDL2_RendererInfo *self;
    PyTypeObject *type = &PyCSDL2_RendererInfoType;

    self = PyCSDL2_RendererInfoNew(type, NULL, NULL);
    if (!self)
        return NULL;

    if (info)
        self->info_mem->info = *info;

    return (PyObject*)self;
}

/**
 * \brief Borrow the SDL_RendererInfo managed by the PyCSDL2_RendererInfo.
 *
 * \param obj The PyCSDL2_RendererInfo object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_RendererInfoPtr(PyObject *obj, SDL_RendererInfo **out)
{
    PyCSDL2_RendererInfo *self = (PyCSDL2_RendererInfo*)obj;

    if (!PyCSDL2_RendererInfoValid(self))
        return 0;

    if (out)
        *out = &self->info_mem->info;

    return 1;
}

/** @} */

/** \brief Instance data of PyCSDL2_RendererType */
typedef struct PyCSDL2_Renderer {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief SDL_Renderer which this instance owns. */
    SDL_Renderer *renderer;
    /** \brief PyObject representing the default render target */
    PyObject *deftarget;
} PyCSDL2_Renderer;

/** \brief Traversal function for PyCSDL2_RendererType */
static int
PyCSDL2_RendererTraverse(PyCSDL2_Renderer *self, visitproc visit, void *arg)
{
    Py_VISIT(self->deftarget);
    return 0;
}

/** \brief Clear function for PyCSDL2_RendererType */
static int
PyCSDL2_RendererClear(PyCSDL2_Renderer *self)
{
    Py_CLEAR(self->deftarget);
    return 0;
}

/** \brief Destructor for PyCSDL2_RendererType */
static void
PyCSDL2_RendererDealloc(PyCSDL2_Renderer *self)
{
    PyCSDL2_RendererClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->renderer)
        SDL_DestroyRenderer(self->renderer);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Type definition for csdl2.SDL_Renderer */
static PyTypeObject PyCSDL2_RendererType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Renderer",
    /* tp_basicsize      */ sizeof(PyCSDL2_Renderer),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RendererDealloc,
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
    "Renderer",
    /* tp_traverse       */ (traverseproc) PyCSDL2_RendererTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_RendererClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Renderer, in_weakreflist)
};

/**
 * \brief Validates the PyCSDL2_Renderer object
 *
 * PyCSDL2_Renderer is valid if:
 *
 * * Its contained SDL_Renderer is not NULL
 * * The contained SDL_Window or SDL_Surface of its default render target is
 *   not NULL.
 *
 * \param renderer PyCSDL2_Renderer to check
 * \returns 1 if the renderer is valid, 0 with an exception set if it is not.
 */

static int
PyCSDL2_RendererValid(PyCSDL2_Renderer *renderer)
{
    if (!PyCSDL2_Assert(renderer))
        return 0;

    if (Py_TYPE(renderer) != &PyCSDL2_RendererType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_Renderer", (PyObject*) renderer);
        return 0;
    }

    if (!renderer->renderer) {
        PyErr_SetString(PyExc_ValueError, "Invalid SDL_Renderer");
        return 0;
    }

    if (!PyCSDL2_Assert(renderer->deftarget))
        return 0;

    if (Py_TYPE(renderer->deftarget) == &PyCSDL2_WindowType)
        return PyCSDL2_WindowValid((PyCSDL2_Window*) renderer->deftarget);
    else if (Py_TYPE(renderer->deftarget) == &PyCSDL2_SurfaceType) {
        return PyCSDL2_SurfaceValid((PyCSDL2_Surface*) renderer->deftarget);
    } else {
        PyErr_SetString(PyExc_AssertionError, "renderer->deftarget must be "
                        "SDL_Window or SDL_Surface");
        return 0;
    }
    return 1;
}

/**
 * \brief Returns the window's renderer.
 *
 * \param window Window
 * \returns A borrowed reference to the PyCSDL2_Renderer of the window, or
 *          Py_None if the window has no renderer. Otherwise, NULL if an
 *          exception occurred.
 */
static PyObject *
PyCSDL2_WindowGetRenderer(PyCSDL2_Window *window)
{
    PyObject *obj;

    if (!PyCSDL2_Assert(window))
        return NULL;

    if (!window->renderer)
        return Py_None;

    if (!PyWeakref_CheckRef(window->renderer)) {
        PyErr_SetString(PyExc_AssertionError,
                        "window->renderer is not a weakref");
        return NULL;
    }

    obj = PyWeakref_GetObject(window->renderer);
    if (!obj)
        return NULL;

    if (obj == Py_None) {
        Py_CLEAR(window->renderer);
        return Py_None;
    }

    if (!PyCSDL2_Assert(Py_TYPE(obj) == &PyCSDL2_RendererType))
        return NULL;

    if (!((PyCSDL2_Renderer*)obj)->renderer) {
        Py_CLEAR(window->renderer);
        return Py_None;
    }

    return obj;
}

/**
 * \brief Sets the window's renderer.
 */
static int
PyCSDL2_WindowSetRenderer(PyCSDL2_Window *window, PyCSDL2_Renderer *renderer)
{
    PyObject *obj, *ref;

    if (!PyCSDL2_Assert(window) || !PyCSDL2_Assert(renderer))
        return -1;

    obj = PyCSDL2_WindowGetRenderer(window);
    if (!obj)
        return -1;

    if (obj != Py_None) {
        PyErr_SetString(PyExc_AssertionError, "window already has a renderer");
        return -1;
    }

    ref = PyWeakref_NewRef((PyObject*)renderer, NULL);
    if (!ref)
        return -1;

    window->renderer = ref;

    return 0;
}

/**
 * \brief Creates an instance of PyCSDL2_RendererType
 *
 * \param renderer SDL_Renderer to manage. The new instance will take over
 *                 ownership of this renderer.
 * \param deftarget The PyCSDL2_Window or PyCSDL2_Surface which is the default
 *                  target for the renderer.
 */
static PyObject *
PyCSDL2_RendererCreate(SDL_Renderer *renderer, PyObject *deftarget)
{
    PyCSDL2_Renderer *self;
    PyTypeObject *type = &PyCSDL2_RendererType;

    if (!PyCSDL2_Assert(renderer))
        return NULL;

    if (!PyCSDL2_Assert(deftarget))
        return NULL;

    if (!PyCSDL2_Assert(Py_TYPE(deftarget) == &PyCSDL2_WindowType ||
                        Py_TYPE(deftarget) == &PyCSDL2_SurfaceType))
        return NULL;

    if (!(self = (PyCSDL2_Renderer*) type->tp_alloc(type, 0)))
        return NULL;
    self->renderer = renderer;
    PyCSDL2_Set(self->deftarget, deftarget);

    if (Py_TYPE(deftarget) == &PyCSDL2_WindowType) {
        if (PyCSDL2_WindowSetRenderer((PyCSDL2_Window*)deftarget, self)) {
            Py_DECREF(self);
            return NULL;
        }
    }

    return (PyObject*)self;
}

/**
 * \brief Borrow the SDL_Renderer pointer managed by the PyCSDL2_Renderer.
 *
 * \param obj The PyCSDL2_Renderer object
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 with an exception set on failure.
 */
static int
PyCSDL2_RendererPtr(PyObject *obj, SDL_Renderer **out)
{
    PyCSDL2_Renderer *self = (PyCSDL2_Renderer*)obj;

    if (!PyCSDL2_RendererValid(self))
        return 0;

    if (out)
        *out = self->renderer;

    return 1;
}

/**
 * \defgroup csdl2_SDL_Texture csdl2.SDL_Texture
 *
 * \brief Manages a SDL_Texture handle
 *
 * @{
 */

/** \brief Instance data of PyCSDL2_TextureType */
typedef struct PyCSDL2_Texture {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief SDL_Texture which this instance owns. */
    SDL_Texture *texture;
    /** \brief Reference to PyCSDL2_Renderer of this texture */
    PyCSDL2_Renderer *renderer;
    /** \brief weakref to PyCSDL2_TexturePixels when the texture is locked */
    PyObject *pixels;
} PyCSDL2_Texture;

static PyTypeObject PyCSDL2_TextureType;

/**
 * \brief dict of SDL_Texture pointers to PyCSDL2_Texture objects.
 */
static PyObject *PyCSDL2_TextureDict;

/** \brief tp_dealloc for PyCSDL2_TextureType */
static void
PyCSDL2_TextureDealloc(PyCSDL2_Texture *self)
{
    Py_CLEAR(self->pixels);
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->texture) {
        PyObject *key = PyLong_FromVoidPtr(self->texture);
        if (key)
            PyDict_DelItem(PyCSDL2_TextureDict, key);
        if (self->renderer && self->renderer->renderer &&
            SDL_GetRenderTarget(self->renderer->renderer) == self->texture) {
            SDL_SetRenderTarget(self->renderer->renderer, NULL);
        }
        SDL_DestroyTexture(self->texture);
    }
    /*
     * NOTE: renderer should only be cleared after the texture has been
     * destroyed.
     */
    Py_CLEAR(self->renderer);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Validates the PyCSDL2_Texture
 *
 * A PyCSDL2_Texture object is valid if its "texture" field is not NULL and its
 * "renderer" field points to a valid PyCSDL2_Renderer object.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_TextureValid(PyCSDL2_Texture *self, int allow_locked)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_TextureType) {
        PyErr_SetString(PyExc_TypeError, "object is not a SDL_Texture");
        return 0;
    }

    if (!self->texture) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_Texture");
        return 0;
    }

    if (!PyCSDL2_RendererValid(self->renderer))
        return 0;

    if (!allow_locked && self->pixels) {
        PyErr_SetString(PyExc_ValueError, "texture is locked");
        return 0;
    }

    return 1;
}

/** \brief Type definition for csdl2.SDL_Texture */
static PyTypeObject PyCSDL2_TextureType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Texture",
    /* tp_basicsize      */ sizeof(PyCSDL2_Texture),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_TextureDealloc,
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
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "An efficient driver-specific representation of pixel data.\n"
    "\n"
    "This is an opaque handle that cannot be directly constructed. Instead,\n"
    "use SDL_CreateTexture() or SDL_CreateTextureFromSurface().\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Texture, in_weakreflist)
};

/**
 * \brief Creates a new PyCSDL2_Texture
 *
 * \param texture SDL_Texture to manage.
 * \param renderer The PyCSDL2_Renderer managing the texture's renderer.
 * \returns The new PyCSDL2_Texture instance on success, NULL with an exception
 *          set otherwise.
 */
static PyObject *
PyCSDL2_TextureCreate(SDL_Texture *texture, PyObject *renderer)
{
    PyCSDL2_Texture *self = NULL;
    PyCSDL2_Renderer *rdr = (PyCSDL2_Renderer*)renderer;
    PyTypeObject *type = &PyCSDL2_TextureType;
    PyObject *key = NULL, *value = NULL;
    int contains;

    if (!PyCSDL2_Assert(texture) || !PyCSDL2_Assert(renderer))
        return NULL;

    if (!PyCSDL2_RendererValid(rdr))
        return NULL;

    self = (PyCSDL2_Texture*) type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->texture = texture;
    PyCSDL2_Set(self->renderer, rdr);

    key = PyLong_FromVoidPtr(texture);
    if (!key)
        goto fail;

    contains = PyDict_Contains(PyCSDL2_TextureDict, key);
    if (contains < 0)
        goto fail;

    if (contains) {
        PyErr_SetString(PyExc_AssertionError,
                        "SDL_Texture is already managed by csdl2");
        goto fail;
    }

    value = PyWeakref_NewRef((PyObject*)self, NULL);
    if (!value)
        goto fail;

    if (PyDict_SetItem(PyCSDL2_TextureDict, key, value))
        goto fail;

    return (PyObject*)self;

fail:
    Py_XDECREF(self);
    Py_XDECREF(key);
    Py_XDECREF(value);
    return NULL;
}

/**
 * \brief Returns the SDL_Texture managed by the PyCSDL2_Texture
 *
 * \param obj PyCSDL2_Texture object
 * \param out Output pointer
 * \returns 1 on success, 0 on failure.
 */
static int
PyCSDL2_TexturePtr(PyObject *obj, SDL_Texture **out)
{
    PyCSDL2_Texture *self = (PyCSDL2_Texture*)obj;

    if (!PyCSDL2_TextureValid(self, 0))
        return 0;

    if (out)
        *out = self->texture;

    return 1;
}

/**
 * \brief Detaches the SDL_Texture and PyCSDL2_Renderer from the
 *        PyCSDL2_Texture
 *
 * \returns 1 on success, 0 with an exception set on failure.
 */
static int
PyCSDL2_TextureDetach(PyCSDL2_Texture *self, SDL_Texture **texture,
                      PyCSDL2_Renderer **renderer)
{
    PyObject *key;

    if (!PyCSDL2_TextureValid(self, 0))
        return 0;

    key = PyLong_FromVoidPtr(self->texture);
    if (!key)
        return 0;

    if (PyDict_DelItem(PyCSDL2_TextureDict, key))
        return 0;

    if (self->renderer && self->renderer->renderer &&
        SDL_GetRenderTarget(self->renderer->renderer) == self->texture)
        SDL_SetRenderTarget(self->renderer->renderer, NULL);

    if (texture)
        *texture = self->texture;

    if (renderer)
        *renderer = self->renderer;
    else
        Py_XDECREF(self->renderer);

    self->texture = NULL;
    self->renderer = NULL;

    return 1;
}

/** @} */

/**
 * \defgroup csadl2_SDL_TexturePixels csdl2.SDL_TexturePixels
 *
 * \brief Manages the pixels buffer returned by SDL_LockTexture().
 *
 * @{
 */

/** \brief Instance data of PyCSDL2_TexturePixelsType */
typedef struct PyCSDL2_TexturePixels {
    PyCSDL2_BufferHEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief Owner of the pixels buffer */
    PyCSDL2_Texture *texture;
} PyCSDL2_TexturePixels;

static PyTypeObject PyCSDL2_TexturePixelsType;

/** \brief Destructor for PyCSDL2_TexturePixelsType */
static void
PyCSDL2_TexturePixelsDealloc(PyCSDL2_TexturePixels *self)
{
    Py_CLEAR(self->texture);
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Validates the PyCSDL2_TexturePixels object */
static int
PyCSDL2_TexturePixelsValid(PyCSDL2_TexturePixels *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_TexturePixelsType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_TexturePixels", (PyObject*)self);
        return 0;
    }

    if (!PyCSDL2_BufferValid((PyCSDL2_Buffer*)self))
        return 0;

    if (!PyCSDL2_Assert(self->texture))
        return 0;

    if (!PyCSDL2_TextureValid(self->texture, 1))
        return 0;

    return 1;
}

/** \brief getbufferproc implementation for PyCSDL2_TexturePixelsType */
static int
PyCSDL2_TexturePixelsGetBuffer(PyCSDL2_TexturePixels *self, Py_buffer *view,
                               int flags)
{
    if (!PyCSDL2_TexturePixelsValid(self))
        return -1;

    return PyCSDL2_BufferGetBuffer((PyCSDL2_Buffer*) self, view, flags);
}

/** \brief tp_as_buffer for PyCSDL2_TexturePixelsType */
static PyBufferProcs PyCSDL2_TexturePixelsBufferProcs = {
    (getbufferproc) PyCSDL2_TexturePixelsGetBuffer,
    (releasebufferproc) PyCSDL2_BufferReleaseBuffer
};

/** \brief Type definition for csdl2.SDL_TexturePixels */
static PyTypeObject PyCSDL2_TexturePixelsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_TexturePixels",
    /* tp_basicsize      */ sizeof(PyCSDL2_TexturePixels),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_TexturePixelsDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_TexturePixelsBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */ "Provides access to the texture's pixels",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_TexturePixels, in_weakreflist)
};

/**
 * \brief Creates an instance of PyCSDL2_TexturePixelsType
 */
static PyCSDL2_TexturePixels *
PyCSDL2_TexturePixelsCreate(void *pixels, Py_ssize_t len,
                            PyCSDL2_Texture *texture)
{
    PyCSDL2_TexturePixels *self;
    PyTypeObject *type = &PyCSDL2_TexturePixelsType;

    if (!PyCSDL2_Assert(pixels))
        return NULL;

    if (!PyCSDL2_Assert(texture))
        return NULL;

    self = (PyCSDL2_TexturePixels*) type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    PyCSDL2_BufferInit((PyCSDL2_Buffer*) self, CTYPE_UCHAR, pixels, len, 0);
    PyCSDL2_Set(self->texture, texture);

    return self;
}

/** @} */

/**
 * \brief Implements csdl2.SDL_GetNumRenderDrivers()
 *
 * \code{.py}
 * SDL_GetNumRenderDrivers() -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetNumRenderDrivers(PyObject *module, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    return PyLong_FromLong(SDL_GetNumRenderDrivers());
}

/**
 * \brief Implements csdl2.SDL_GetRenderDriverInfo()
 *
 * \code{.py}
 * SDL_GetRenderDriverInfo(index: int) -> SDL_RendererInfo
 * \endcode
 */
static PyObject *
PyCSDL2_GetRenderDriverInfo(PyObject *module, PyObject *args, PyObject *kwds)
{
    int index;
    struct SDL_RendererInfo info;
    static char *kwlist[] = {"index", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &index))
        return NULL;

    if (SDL_GetRenderDriverInfo(index, &info))
        return PyCSDL2_RaiseSDLError();

    return PyCSDL2_RendererInfoCreate(&info);
}

/**
 * \brief Implements csdl2.SDL_CreateWindowAndRenderer()
 *
 * \code{.py}
 * SDL_CreateWindowAndRenderer(width: int, height: int, window_flags: int)
 *     -> (SDL_Window, SDL_Renderer)
 * \endcode
 */
static PyObject *
PyCSDL2_CreateWindowAndRenderer(PyObject *module, PyObject *args,
                                PyObject *kwds)
{
    int width, height;
    Uint32 window_flags;
    int ret;
    SDL_Window *ret_win;
    SDL_Renderer *ret_rdr;
    PyObject *out_win, *out_rdr;
    static char *kwlist[] = {"width", "height", "window_flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ii" Uint32_UNIT, kwlist,
                                     &width, &height, &window_flags))
        return NULL;

    ret = SDL_CreateWindowAndRenderer(width, height, window_flags, &ret_win,
                                      &ret_rdr);
    if (ret)
        return PyCSDL2_RaiseSDLError();

    out_win = PyCSDL2_WindowCreate(ret_win);
    if (!out_win) {
        SDL_DestroyRenderer(ret_rdr);
        SDL_DestroyWindow(ret_win);
        return NULL;
    }

    out_rdr = PyCSDL2_RendererCreate(ret_rdr, out_win);
    if (!out_rdr) {
        SDL_DestroyRenderer(ret_rdr);
        Py_CLEAR(out_win);
        return NULL;
    }

    return Py_BuildValue("NN", out_win, out_rdr);
}

/**
 * \brief Implements csdl2.SDL_CreateRenderer()
 *
 * \code{.py}
 * SDL_CreateRenderer(window: SDL_Window, index: int, flags: int)
 *                   -> SDL_Renderer
 * \endcode
 */
static PyObject *
PyCSDL2_CreateRenderer(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    PyCSDL2_Window *window;
    int index;
    Uint32 flags;
    PyObject *out;
    static char *kwlist[] = {"window", "index", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!i" Uint32_UNIT, kwlist,
                                     &PyCSDL2_WindowType, &window, &index,
                                     &flags))
        return NULL;

    if (!PyCSDL2_Assert(window->window))
        return NULL;

    if (!(renderer = SDL_CreateRenderer(window->window, index, flags)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_RendererCreate(renderer, (PyObject*) window))) {
        SDL_DestroyRenderer(renderer);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_CreateSoftwareRenderer()
 *
 * \code{.py}
 * SDL_CreateSoftwareRenderer(surface: SDL_Surface) -> SDL_Renderer
 * \endcode
 */
static PyObject *
PyCSDL2_CreateSoftwareRenderer(PyObject *module, PyObject *args,
                               PyObject *kwds)
{
    PyCSDL2_Surface *surface;
    SDL_Renderer *renderer;
    PyObject *out;
    static char *kwlist[] = {"surface", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_SurfaceType, &surface))
        return NULL;

    if (!PyCSDL2_Assert(surface->surface))
        return NULL;

    if (!(renderer = SDL_CreateSoftwareRenderer(surface->surface)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_RendererCreate(renderer, (PyObject*) surface))) {
        SDL_DestroyRenderer(renderer);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_GetRenderer()
 *
 * \code{.py}
 * SDL_GetRenderer(window: SDL_Window) -> SDL_Renderer or None
 * \endcode
 */
static PyObject *
PyCSDL2_GetRenderer(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Window *window;
    PyObject *renderer;
    static char *kwlist[] = {"window", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_WindowType, &window))
        return NULL;

    if (!PyCSDL2_WindowValid((PyCSDL2_Window*)window))
        return NULL;

    renderer = PyCSDL2_WindowGetRenderer(window);
    if (!renderer)
        return NULL;

    return PyCSDL2_Get(renderer);
}

/**
 * \brief Implements csdl2.SDL_GetRendererInfo()
 *
 * \code{.py}
 * SDL_GetRendererInfo(renderer: SDL_Renderer) -> SDL_RendererInfo
 * \endcode
 */
static PyObject *
PyCSDL2_GetRendererInfo(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_RendererInfo info;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    if (SDL_GetRendererInfo(renderer, &info))
        return PyCSDL2_RaiseSDLError();

    return PyCSDL2_RendererInfoCreate(&info);
}

/**
 * \brief Implements csdl2.SDL_GetRendererOutputSize()
 *
 * \code{.py}
 * SDL_GetRendererOutputSize(renderer: SDL_Renderer) -> (int, int)
 * \endcode
 */
static PyObject *
PyCSDL2_GetRendererOutputSize(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *rdr;
    int ret, w, h;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &rdr))
        return NULL;

    ret = SDL_GetRendererOutputSize(rdr, &w, &h);
    if (ret)
        return PyCSDL2_RaiseSDLError();

    return Py_BuildValue("ii", w, h);
}

/**
 * \brief Implements csdl2.SDL_CreateTexture()
 *
 * \code{.py}
 * SDL_CreateTexture(renderer: SDL_Renderer, format: int, access: int, w: int,
 *                   h: int) -> SDL_Texture
 * \endcode
 */
static PyObject *
PyCSDL2_CreateTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyObject *rdr_obj;
    SDL_Renderer *rdr;
    Uint32 format;
    int access, w, h;
    SDL_Texture *texture;
    PyObject *out;
    static char *kwlist[] = {"renderer", "format", "access", "w", "h", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O" Uint32_UNIT "iii",
                                     kwlist, &rdr_obj, &format, &access, &w,
                                     &h))
        return NULL;

    if (!PyCSDL2_RendererPtr(rdr_obj, &rdr))
        return NULL;

    texture = SDL_CreateTexture(rdr, format, access, w, h);
    if (!texture)
        return PyCSDL2_RaiseSDLError();

    out = PyCSDL2_TextureCreate(texture, rdr_obj);
    if (!out) {
        SDL_DestroyTexture(texture);
        return NULL;
    }

    return out;
}

/**
 * \brief Implements csdl2.SDL_CreateTextureFromSurface()
 *
 * \code{.py}
 * SDL_CreateTextureFromSurface(renderer: SDL_Renderer, surface: SDL_Surface)
 *      -> SDL_Texture
 * \endcode
 */
static PyObject *
PyCSDL2_CreateTextureFromSurface(PyObject *module, PyObject *args,
                                 PyObject *kwds)
{
    PyCSDL2_Renderer *rdr;
    SDL_Surface *surface;
    SDL_Texture *texture;
    PyObject *out;
    static char *kwlist[] = {"renderer", "surface", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O&", kwlist,
                                     &PyCSDL2_RendererType, &rdr,
                                     PyCSDL2_SurfacePtr, &surface))
        return NULL;

    if (!PyCSDL2_RendererValid(rdr))
        return NULL;

    texture = SDL_CreateTextureFromSurface(rdr->renderer, surface);
    if (!texture)
        return PyCSDL2_RaiseSDLError();

    out = PyCSDL2_TextureCreate(texture, (PyObject*)rdr);
    if (!out) {
        SDL_DestroyTexture(texture);
        return NULL;
    }

    return out;
}

/**
 * \brief Implements csdl2.SDL_QueryTexture()
 *
 * \code{.py}
 * SDL_QueryTexture(texture: SDL_Texture) -> (int, int, int, int)
 * \endcode
 */
static PyObject *
PyCSDL2_QueryTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    Uint32 format;
    int access, w, h;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_TexturePtr, &texture))
        return NULL;

    if (SDL_QueryTexture(texture, &format, &access, &w, &h))
        return PyCSDL2_RaiseSDLError();

    return Py_BuildValue(Uint32_UNIT "iii", format, access, w, h);
}

/**
 * \brief Implements csdl2.SDL_SetTextureColorMod()
 *
 * \code{.py}
 * SDL_SetTextureColorMod(texture: SDL_Texture, r: int, g: int, b: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetTextureColorMod(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    unsigned char r, g, b;
    static char *kwlist[] = {"texture", "r", "g", "b", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&bbb", kwlist,
                                     PyCSDL2_TexturePtr, &texture, &r, &g, &b))
        return NULL;

    if (SDL_SetTextureColorMod(texture, r, g, b))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetTextureColorMod()
 *
 * \code{.py}
 * SDL_GetTextureColorMod(texture: SDL_Texture) -> (int, int, int)
 * \endcode
 */
static PyObject *
PyCSDL2_GetTextureColorMod(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    unsigned char r, g, b;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_TexturePtr, &texture))
        return NULL;

    if (SDL_GetTextureColorMod(texture, &r, &g, &b))
        return PyCSDL2_RaiseSDLError();

    return Py_BuildValue("bbb", r, g, b);
}

/**
 * \brief Implements csdl2.SDL_SetTextureAlphaMod()
 *
 * \code{.py}
 * SDL_SetTextureAlphaMod(texture: SDL_Texture, alpha: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetTextureAlphaMod(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    unsigned char alpha;
    static char *kwlist[] = {"texture", "alpha", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&b", kwlist,
                                     PyCSDL2_TexturePtr, &texture, &alpha))
        return NULL;

    if (SDL_SetTextureAlphaMod(texture, alpha))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetTextureAlphaMod()
 *
 * \code{.py}
 * SDL_GetTextureAlphaMod(texture: SDL_Texture) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetTextureAlphaMod(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    unsigned char alpha;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_TexturePtr, &texture))
        return NULL;

    if (SDL_GetTextureAlphaMod(texture, &alpha))
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromUnsignedLong(alpha);
}

/**
 * \brief Implements csdl2.SDL_SetTextureBlendMode()
 *
 * \code{.py}
 * SDL_SetTextureBlendMode(texture: SDL_Texture, blendMode: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetTextureBlendMode(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    int blendMode;
    static char *kwlist[] = {"texture", "blendMode", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&i", kwlist,
                                     PyCSDL2_TexturePtr, &texture, &blendMode))
        return NULL;

    if (SDL_SetTextureBlendMode(texture, blendMode))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetTextureBlendMode()
 *
 * \code{.py}
 * SDL_GetTextureBlendMode(texture: SDL_Texture) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetTextureBlendMode(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    SDL_BlendMode blendMode;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_TexturePtr, &texture))
        return NULL;

    if (SDL_GetTextureBlendMode(texture, &blendMode))
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromLong(blendMode);
}

/**
 * \brief Implements csdl2.SDL_UpdateTexture()
 *
 * \code{.py}
 * SDL_UpdateTexture(texture: SDL_Texture, rect: SDL_Rect, pixels: buffer,
 *                   pitch: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_UpdateTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Texture *texture;
    Py_buffer rect, pixels;
    SDL_Rect r;
    int pitch, ret, max_w, max_h;
    Py_ssize_t min_pitch, min_size;
    Uint32 format;
    static char *kwlist[] = {"texture", "rect", "pixels", "pitch", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&y*i", kwlist,
                                     PyCSDL2_TexturePtr, &texture,
                                     PyCSDL2_ConvertRectRead, &rect,
                                     &pixels, &pitch))
        return NULL;

    /* SDL assumes that pitch is positive */
    if (pitch < 0) {
        PyBuffer_Release(&rect);
        PyBuffer_Release(&pixels);
        PyErr_SetString(PyExc_ValueError, "pitch must be positive");
        return NULL;
    }

    if (SDL_QueryTexture(texture, &format, NULL, &max_w, &max_h)) {
        PyBuffer_Release(&rect);
        PyBuffer_Release(&pixels);
        return PyCSDL2_RaiseSDLError();
    }

    if (rect.buf) {
        r = *((SDL_Rect*)rect.buf);
    } else {
        r.x = 0;
        r.y = 0;
        r.w = max_w;
        r.h = max_h;
    }

    /* SDL assumes that rect.w and rect.h are positive */
    if (r.x < 0 || r.y < 0 || r.w < 0 || r.h < 0) {
        PyBuffer_Release(&rect);
        PyBuffer_Release(&pixels);
        PyErr_SetString(PyExc_ValueError,
                        "components of rect must be positive");
        return NULL;
    }

    /* SDL does not check if the rect exceeds texture boundaries */
    if (r.x + r.w > max_w || r.y + r.h > max_h) {
        PyBuffer_Release(&rect);
        PyBuffer_Release(&pixels);
        PyErr_SetString(PyExc_ValueError, "rect exceeds texture boundaries");
        return NULL;
    }

    /* SDL does not check if the pixels buffer is of sufficient size */
    min_pitch = SDL_BYTESPERPIXEL(format) * r.w;
    min_size = pitch * (r.h ? r.h - 1 : 0) + min_pitch;
    if (pixels.len < min_size) {
        PyBuffer_Release(&rect);
        PyBuffer_Release(&pixels);
        return PyCSDL2_RaiseBufferSizeError("pixels", min_size, pixels.len);
    }

    ret = SDL_UpdateTexture(texture, rect.buf, pixels.buf, pitch);

    PyBuffer_Release(&rect);
    PyBuffer_Release(&pixels);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_LockTexture()
 *
 * \code{.py}
 * SDL_LockTexture(texture: SDL_Texture, rect: SDL_Rect)
 *     -> (SDL_TexturePixels, int)
 * \endcode
 */
static PyObject *
PyCSDL2_LockTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Texture *texture;
    Py_buffer rect;
    SDL_Rect r;
    void *pixels = NULL;
    int pitch = -1, ret, max_w, max_h;
    Py_ssize_t len;
    Uint32 format;
    PyCSDL2_TexturePixels *out_pixels;
    static char *kwlist[] = {"texture", "rect", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O&", kwlist,
                                     &PyCSDL2_TextureType, &texture,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;

    if (!PyCSDL2_TextureValid(texture, 0)) {
        PyBuffer_Release(&rect);
        return NULL;
    }

    if (SDL_QueryTexture(texture->texture, &format, NULL, &max_w, &max_h)) {
        PyBuffer_Release(&rect);
        return PyCSDL2_RaiseSDLError();
    }

    if (rect.buf) {
        r = *((SDL_Rect*)rect.buf);
    } else {
        r.x = 0;
        r.y = 0;
        r.w = max_w;
        r.h = max_h;
    }

    /* SDL assumes that rect.w and rect.h are positive */
    if (r.x < 0 || r.y < 0 || r.w < 0 || r.h < 0) {
        PyBuffer_Release(&rect);
        PyErr_SetString(PyExc_ValueError,
                        "components of rect must be positive");
        return NULL;
    }

    /* SDL does not check if the rect exceeds texture boundaries */
    if (r.x + r.w > max_w || r.y + r.h > max_h) {
        PyBuffer_Release(&rect);
        PyErr_SetString(PyExc_ValueError, "rect exceeds texture boundaries");
        return NULL;
    }

    ret = SDL_LockTexture(texture->texture, rect.buf, &pixels, &pitch);
    PyBuffer_Release(&rect);
    if (ret)
        return PyCSDL2_RaiseSDLError();

    if (!PyCSDL2_Assert(pitch >= 0) || !PyCSDL2_Assert(pixels) ||
        !PyCSDL2_Assert(!texture->pixels)) {
        SDL_UnlockTexture(texture->texture);
        return NULL;
    }

    len = (r.h ? r.h-1 : 0) * pitch + r.w * SDL_BYTESPERPIXEL(format);
    out_pixels = PyCSDL2_TexturePixelsCreate(pixels, len, texture);
    if (!out_pixels) {
        SDL_UnlockTexture(texture->texture);
        return NULL;
    }

    texture->pixels = PyWeakref_NewRef((PyObject*) out_pixels, NULL);
    if (!texture->pixels) {
        Py_CLEAR(out_pixels);
        SDL_UnlockTexture(texture->texture);
        return NULL;
    }

    return Py_BuildValue("Ni", out_pixels, pitch);
}

/**
 * \brief Implements csdl2.SDL_UnlockTexture()
 *
 * \code{.py}
 * SDL_UnlockTexture(texture: SDL_Texture) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_UnlockTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Texture *texture;
    PyCSDL2_TexturePixels *pixels;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_TextureType, &texture))
        return NULL;

    if (!PyCSDL2_TextureValid(texture, 1))
        return NULL;

    if (!texture->pixels) {
        PyErr_SetString(PyExc_ValueError, "texture is not locked");
        return NULL;
    }

    pixels = (PyCSDL2_TexturePixels*) PyWeakref_GetObject(texture->pixels);
    if (pixels && (PyObject*) pixels != Py_None) {
        if (!PyCSDL2_Assert(Py_TYPE(pixels) == &PyCSDL2_TexturePixelsType))
            return NULL;

        if (pixels->num_exports) {
            PyErr_SetString(PyExc_ValueError, "texture pixels buffer is "
                            "exported");
            return NULL;
        }

        pixels->buf = NULL;
    }

    Py_CLEAR(texture->pixels);

    SDL_UnlockTexture(texture->texture);

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderTargetSupported()
 *
 * \code{.py}
 * SDL_RenderTargetSupported(renderer: SDL_Renderer) -> bool
 * \endcode
 */
static PyObject *
PyCSDL2_RenderTargetSupported(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    return PyBool_FromLong(SDL_RenderTargetSupported(renderer));
}

/**
 * \brief Implements csdl2.SDL_SetRenderTarget()
 *
 * \code{.py}
 * SDL_SetRenderTarget(renderer: SDL_Renderer, texture: SDL_Texture) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetRenderTarget(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    PyObject *texture_obj;
    SDL_Texture *texture;
    static char *kwlist[] = {"renderer", "texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &texture_obj))
        return NULL;

    if (texture_obj == Py_None)
        texture = NULL;
    else if (!PyCSDL2_TexturePtr(texture_obj, &texture))
        return NULL;

    if (SDL_SetRenderTarget(renderer, texture))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetRenderTarget()
 *
 * \code{.py}
 * SDL_GetRenderTarget(renderer: SDL_Renderer) -> SDL_Texture
 * \endcode
 */
static PyObject *
PyCSDL2_GetRenderTarget(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    PyObject *key, *value;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    texture = SDL_GetRenderTarget(renderer);
    if (!texture)
        Py_RETURN_NONE;

    key = PyLong_FromVoidPtr(texture);
    if (!key)
        return NULL;

    value = PyDict_GetItem(PyCSDL2_TextureDict, key);
    if (!value)
        return PyCSDL2_VoidPtrCreate(texture);

    value = PyWeakref_GetObject(value);
    if (!value)
        return NULL;

    return PyCSDL2_Get(value);
}

/**
 * \brief Implements csdl2.SDL_RenderSetLogicalSize()
 *
 * \code{.py}
 * SDL_RenderSetLogicalSize(renderer: SDL_Renderer, w: int, h: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderSetLogicalSize(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    int w, h;
    static char *kwlist[] = {"renderer", "w", "h", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&ii", kwlist,
                                     PyCSDL2_RendererPtr, &renderer, &w, &h))
        return NULL;

    if (SDL_RenderSetLogicalSize(renderer, w, h))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderGetLogicalSize()
 *
 * \code{.py}
 * SDL_RenderGetLogicalSize(renderer: SDL_Renderer) -> (int, int)
 * \endcode
 */
static PyObject *
PyCSDL2_RenderGetLogicalSize(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    int w, h;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    SDL_RenderGetLogicalSize(renderer, &w, &h);

    return Py_BuildValue("ii", w, h);
}

/**
 * \brief Implements csdl2.SDL_RenderSetViewport()
 *
 * \code{.py}
 * SDL_RenderSetViewport(renderer: SDL_Renderer, rect: SDL_Rect) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderSetViewport(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rect;
    int ret;
    static char *kwlist[] = {"renderer", "rect", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;

    ret = SDL_RenderSetViewport(renderer, rect.buf);

    PyBuffer_Release(&rect);
    if (ret)
        return PyCSDL2_RaiseSDLError();
    else
        Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderGetViewport()
 *
 * \code{.py}
 * SDL_RenderGetViewport(renderer: SDL_Renderer) -> SDL_Rect
 * \endcode
 */
static PyObject *
PyCSDL2_RenderGetViewport(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_Rect rect;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    SDL_RenderGetViewport(renderer, &rect);

    return PyCSDL2_RectCreate(&rect);
}

/**
 * \brief Implements csdl2.SDL_RenderSetClipRect()
 *
 * \code{.py}
 * SDL_RenderSetClipRect(renderer: SDL_Renderer, rect: SDL_Rect) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderSetClipRect(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rect;
    int ret;
    static char *kwlist[] = {"renderer", "rect", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;

    ret = SDL_RenderSetClipRect(renderer, rect.buf);
    PyBuffer_Release(&rect);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderGetClipRect()
 *
 * \code{.py}
 * SDL_RenderGetClipRect(renderer: SDL_Renderer) -> SDL_Rect
 * \endcode
 */
static PyObject *
PyCSDL2_RenderGetClipRect(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_Rect rect;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    SDL_RenderGetClipRect(renderer, &rect);

    return PyCSDL2_RectCreate(&rect);
}

/**
 * \brief Implements csdl2.SDL_RenderSetScale()
 *
 * \code{.py}
 * SDL_RenderSetScale(renderer: SDL_Renderer, float scaleX, float scaleY)
 *     -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderSetScale(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    float scaleX, scaleY;
    static char *kwlist[] = {"renderer", "scaleX", "scaleY", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&ff", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &scaleX, &scaleY))
        return NULL;

    if (SDL_RenderSetScale(renderer, scaleX, scaleY))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderGetScale()
 *
 * \code{.py}
 * SDL_RenderGetScale(renderer: SDL_Renderer) -> (float, float)
 * \endcode
 */
static PyObject *
PyCSDL2_RenderGetScale(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    float scaleX, scaleY;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    SDL_RenderGetScale(renderer, &scaleX, &scaleY);

    return Py_BuildValue("ff", scaleX, scaleY);
}

/**
 * \brief Implements csdl2.SDL_SetRenderDrawColor()
 *
 * \code{.py}
 * SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: int, g: int, b: int,
 *                        a: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetRenderDrawColor(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    unsigned char r, g, b, a;
    static char *kwlist[] = {"renderer", "r", "g", "b", "a", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&bbbb", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &r, &g, &b, &a))
        return NULL;
    if (SDL_SetRenderDrawColor(renderer, r, g, b, a))
        return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetRenderDrawColor()
 *
 * \code{.py}
 * SDL_GetRenderDrawColor(renderer: SDL_Renderer) -> (int, int, int, int)
 * \endcode
 */
static PyObject *
PyCSDL2_GetRenderDrawColor(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Renderer *renderer;
    unsigned char r, g, b, a;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RendererType, &renderer))
        return NULL;

    if (!PyCSDL2_RendererValid(renderer))
        return NULL;

    if (SDL_GetRenderDrawColor(renderer->renderer, &r, &g, &b, &a))
        return PyCSDL2_RaiseSDLError();

    return Py_BuildValue("BBBB", r, g, b, a);
}

/**
 * \brief Implements csdl2.SDL_SetRenderDrawBlendMode()
 *
 * \code{.py}
 * SDL_SetRenderDrawBlendMode(renderer: SDL_Renderer, blendMode: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_SetRenderDrawBlendMode(PyObject *module, PyObject *args,
                               PyObject *kwds)
{
    SDL_Renderer *renderer;
    int blendMode;
    static char *kwlist[] = {"renderer", "blendMode", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &blendMode))
        return NULL;

    if (SDL_SetRenderDrawBlendMode(renderer, blendMode))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetRenderDrawBlendMode()
 *
 * \code{.py}
 * SDL_GetRenderDrawBlendMode(renderer: SDL_Renderer) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetRenderDrawBlendMode(PyObject *module, PyObject *args,
                               PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_BlendMode blendMode;
    static char *kwlist[] = {"renderer", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;

    if (SDL_GetRenderDrawBlendMode(renderer, &blendMode))
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromLong(blendMode);
}

/**
 * \brief Implements csdl2.SDL_RenderClear()
 *
 * \code{.py}
 * SDL_RenderClear(renderer: SDL_Renderer) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderClear(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;
    if (SDL_RenderClear(renderer))
        return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawPoint()
 *
 * \code{.py}
 * SDL_RenderDrawPoint(renderer: SDL_Renderer, x: int, y: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawPoint(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    int x, y;
    static char *kwlist[] = {"renderer", "x", "y", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&ii", kwlist,
                                     PyCSDL2_RendererPtr, &renderer, &x, &y))
        return NULL;

    if (SDL_RenderDrawPoint(renderer, x, y))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawPoints()
 *
 * \code{.py}
 * SDL_RenderDrawPoints(renderer: SDL_Renderer, points: buffer, count: int)
 *     -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawPoints(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer points;
    int count, ret;
    Py_ssize_t expected;
    static char *kwlist[] = {"renderer", "points", "count", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&y*i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &points, &count))
        return NULL;

    expected = sizeof(SDL_Point) * count;
    if (points.len < expected) {
        PyBuffer_Release(&points);
        return PyCSDL2_RaiseBufferSizeError("points", expected, points.len);
    }

    ret = SDL_RenderDrawPoints(renderer, points.buf, count);
    PyBuffer_Release(&points);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawLine()
 *
 * \code{.py}
 * SDL_RenderDrawLine(renderer: SDL_Renderer, x1: int, y1: int, x2: int,
 *                    y2: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawLine(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    int x1, y1, x2, y2;
    static char *kwlist[] = {"renderer", "x1", "y1", "x2", "y2", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&iiii", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &x1, &y1, &x2, &y2))
        return NULL;

    if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2))
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawLines()
 *
 * \code{.py}
 * SDL_RenderDrawLines(renderer: SDL_Renderer, points: buffer, count: int)
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawLines(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer points;
    int count, ret;
    Py_ssize_t expected;
    static char *kwlist[] = {"renderer", "points", "count", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&y*i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer, &points,
                                     &count))
        return NULL;

    expected = sizeof(SDL_Point) * count;
    if (points.len < expected) {
        PyBuffer_Release(&points);
        return PyCSDL2_RaiseBufferSizeError("points", expected, points.len);
    }

    ret = SDL_RenderDrawLines(renderer, points.buf, count);
    PyBuffer_Release(&points);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawRect()
 *
 * \code{.py}
 * SDL_RenderDrawRect(renderer: SDL_Renderer, rect: SDL_Rect or None) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawRect(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rect;
    int ret;
    static char *kwlist[] = {"renderer", "rect", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;

    ret = SDL_RenderDrawRect(renderer, rect.buf);
    PyBuffer_Release(&rect);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderDrawRects()
 *
 * \code{.py}
 * SDL_RenderDrawRects(renderer: SDL_Renderer, rects: buffer, count: int)
 *     -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderDrawRects(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rects;
    int count, ret;
    Py_ssize_t expected;
    static char *kwlist[] = {"renderer", "rects", "count", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&y*i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &rects, &count))
        return NULL;

    expected = sizeof(SDL_Rect) * count;
    if (rects.len < expected) {
        PyBuffer_Release(&rects);
        return PyCSDL2_RaiseBufferSizeError("rects", expected, rects.len);
    }

    ret = SDL_RenderDrawRects(renderer, rects.buf, count);
    PyBuffer_Release(&rects);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderFillRect()
 *
 * \code{.py}
 * SDL_RenderFillRect(renderer: SDL_Renderer, rect: SDL_Rect or None) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderFillRect(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rect;
    int ret;
    static char *kwlist[] = {"renderer", "rect", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;
    ret = SDL_RenderFillRect(renderer, rect.buf);
    PyBuffer_Release(&rect);
    if (ret) return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_FillRects()
 *
 * \code{.py}
 * SDL_RenderFillRects(renderer: SDL_Renderer, rects: buffer, count: int)
 *     -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderFillRects(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    Py_buffer rects;
    int count, ret;
    Py_ssize_t expected;
    static char *kwlist[] = {"renderer", "rects", "count", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&y*i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     &rects, &count))
        return NULL;

    expected = sizeof(SDL_Rect) * count;
    if (rects.len < expected) {
        PyBuffer_Release(&rects);
        return PyCSDL2_RaiseBufferSizeError("rects", expected, rects.len);
    }

    ret = SDL_RenderFillRects(renderer, rects.buf, count);
    PyBuffer_Release(&rects);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderCopy()
 *
 * \code{.py}
 * SDL_RenderCopy(renderer: SDL_Renderer, texture: SDL_Texture,
 *                srcrect: SDL_Rect, dstrect: SDL_Rect) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderCopy(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Py_buffer srcrect, dstrect;
    int ret;
    static char *kwlist[] = {"renderer", "texture", "srcrect", "dstrect",
                             NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&O&O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_TexturePtr, &texture,
                                     PyCSDL2_ConvertRectRead, &srcrect,
                                     PyCSDL2_ConvertRectRead, &dstrect))
        return NULL;

    ret = SDL_RenderCopy(renderer, texture, srcrect.buf, dstrect.buf);

    PyBuffer_Release(&srcrect);
    PyBuffer_Release(&dstrect);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderCopyEx()
 *
 * \code{.py}
 * SDL_RenderCopyEx(renderer: SDL_Renderer, texture: SDL_Texture,
 *                  srcrect: SDL_Rect, dstrect: SDL_Rect, angle: float,
 *                  center: SDL_Point, flip: int) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderCopyEx(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Py_buffer srcrect, dstrect, center;
    double angle;
    int flip, ret;
    static char *kwlist[] = {"renderer", "texture", "srcrect", "dstrect",
                             "angle", "center", "flip", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&O&O&dO&i", kwlist,
                                     PyCSDL2_RendererPtr, &renderer,
                                     PyCSDL2_TexturePtr, &texture,
                                     PyCSDL2_ConvertRectRead, &srcrect,
                                     PyCSDL2_ConvertRectRead, &dstrect,
                                     &angle,
                                     PyCSDL2_ConvertPointRead, &center,
                                     &flip))
        return NULL;

    ret = SDL_RenderCopyEx(renderer, texture, srcrect.buf, dstrect.buf, angle,
                           center.buf, flip);

    PyBuffer_Release(&srcrect);
    PyBuffer_Release(&dstrect);
    PyBuffer_Release(&center);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_RenderReadPixels()
 *
 * \code{.py}
 * SDL_RenderReadPixels(renderer: SDL_Renderer, rect: SDL_Rect, format: int,
 *                      pixels: buffer, pitch: int)
 * \endcode
 */
static PyObject *
PyCSDL2_RenderReadPixels(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Renderer *renderer_obj;
    SDL_Renderer *renderer;
    Py_buffer rect, pixels;
    int format, pitch, min_pitch, min_size, ret;
    SDL_Rect r;
    static char *kwlist[] = {"renderer", "rect", "format", "pixels", "pitch",
                             NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO&iw*i", kwlist,
                                     &renderer_obj,
                                     PyCSDL2_ConvertRectRead, &rect,
                                     &format, &pixels, &pitch))
        return NULL;

    if (!PyCSDL2_RendererPtr((PyObject*)renderer_obj, &renderer))
        goto fail;

    /* SDL assumes that pitch is positive */
    if (pitch <= 0) {
        PyErr_SetString(PyExc_ValueError, "pitch must be positive");
        goto fail;
    }

    /*
     * If !format, SDL will use the native pixel format of the window. As such,
     * we need to get this pixel format as well to do proper bounds checking on
     * the pixels buffer.
     */
    if (!format && Py_TYPE(renderer_obj->deftarget) == &PyCSDL2_WindowType) {
        SDL_Window *window;

        if (!PyCSDL2_WindowPtr(renderer_obj->deftarget, &window))
            goto fail;

        format = SDL_GetWindowPixelFormat(window);
    }

    if (rect.buf) {
        r = *((SDL_Rect*)rect.buf);
    } else {
        float scaleX, scaleY;

        /*
         * SDL_RenderGetViewport() scales the actual viewport rect by the
         * renderer scale, which causes precision errors. Temporarily set scale
         * to 1.0f before calling SDL_RenderGetViewport().
         */
        SDL_RenderGetScale(renderer, &scaleX, &scaleY);
        SDL_RenderSetScale(renderer, 1.0f, 1.0f);
        SDL_RenderGetViewport(renderer, &r);
        SDL_RenderSetScale(renderer, scaleX, scaleY);
    }

    min_pitch = SDL_BYTESPERPIXEL(format) * r.w;
    min_size = pitch * (r.h ? r.h - 1 : 0) + min_pitch;
    if (pixels.len < min_size) {
        PyCSDL2_RaiseBufferSizeError("pixels", min_size, pixels.len);
        goto fail;
    }

    ret = SDL_RenderReadPixels(renderer, rect.buf, format, pixels.buf, pitch);

    PyBuffer_Release(&rect);
    PyBuffer_Release(&pixels);

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;

fail:
    PyBuffer_Release(&rect);
    PyBuffer_Release(&pixels);
    return NULL;
}

/**
 * \brief Implements csdl2.SDL_RenderPresent()
 *
 * \code{.py}
 * SDL_RenderPresent(renderer: SDL_Renderer) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_RenderPresent(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
                                     PyCSDL2_RendererPtr, &renderer))
        return NULL;
    SDL_RenderPresent(renderer);
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_DestroyTexture()
 *
 * \code{.py}
 * SDL_DestroyTexture(texture: SDL_Texture) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_DestroyTexture(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Texture *texture_obj;
    SDL_Texture *texture;
    PyCSDL2_Renderer *renderer;
    static char *kwlist[] = {"texture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_TextureType, &texture_obj))
        return NULL;

    if (!PyCSDL2_TextureDetach(texture_obj, &texture, &renderer))
        return NULL;

    SDL_DestroyTexture(texture);
    Py_CLEAR(renderer);

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_DestroyRenderer()
 *
 * \code{.py}
 * SDL_DestroyRenderer(renderer: SDL_Renderer) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_DestroyRenderer(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RendererType, &renderer))
        return NULL;
    if (!PyCSDL2_RendererValid(renderer))
        return NULL;
    SDL_DestroyRenderer(renderer->renderer);
    renderer->renderer = NULL;
    PyCSDL2_RendererClear(renderer);
    Py_RETURN_NONE;
}

/**
 * \brief Initializes bindings to SDL_render.h
 *
 * Adds constants defined in SDL_render.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initrender(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE},
        {"SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED},
        {"SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC},
        {"SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE},

        {"SDL_TEXTUREACCESS_STATIC", SDL_TEXTUREACCESS_STATIC},
        {"SDL_TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING},
        {"SDL_TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET},

        {"SDL_TEXTUREMODULATE_NONE", SDL_TEXTUREMODULATE_NONE},
        {"SDL_TEXTUREMODULATE_COLOR", SDL_TEXTUREMODULATE_COLOR},
        {"SDL_TEXTUREMODULATE_ALPHA", SDL_TEXTUREMODULATE_ALPHA},

        {"SDL_FLIP_NONE", SDL_FLIP_NONE},
        {"SDL_FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL},
        {"SDL_FLIP_VERTICAL", SDL_FLIP_VERTICAL},

        {NULL, 0}
    };

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_RendererInfoMemType)) { return 0; }

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_RendererInfoType) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_RendererType) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_TextureType) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_TexturePixelsType)) { return 0; }

    PyCSDL2_TextureDict = PyDict_New();
    if (!PyCSDL2_TextureDict)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RENDER_H_ */
