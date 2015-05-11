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
    if (!renderer->renderer) {
        PyErr_SetString(PyExc_ValueError, "Invalid SDL_Renderer");
        return 0;
    }
    PyCSDL2_Assert(renderer->deftarget, 0);
    if (Py_TYPE(renderer->deftarget) == &PyCSDL2_WindowType) {
        if (!((PyCSDL2_Window*)renderer->deftarget)->window) {
            PyErr_SetString(PyExc_ValueError, "Invalid SDL_Window");
            return 0;
        }
    } else if (Py_TYPE(renderer->deftarget) == &PyCSDL2_SurfaceType) {
        if (!((PyCSDL2_Surface*)renderer->deftarget)->surface) {
            PyErr_SetString(PyExc_ValueError, "Invalid SDL_Surface");
            return 0;
        }
    } else {
        PyErr_SetString(PyExc_AssertionError, "renderer->deftarget must be "
                        "SDL_Window or SDL_Surface");
        return 0;
    }
    return 1;
}

/**
 * \brief Creates an instance of PyCSDL2_RendererType
 *
 * \param renderer SDL_Renderer to manage. The new instance will take over
 *                 ownership of this renderer.
 * \param deftarget The PyCSDL2_Window or PyCSDL2_Surface which is the default
 *                  target for the renderer.
 */
static PyCSDL2_Renderer *
PyCSDL2_RendererCreate(SDL_Renderer *renderer, PyObject *deftarget)
{
    PyCSDL2_Renderer *self;
    PyTypeObject *type = &PyCSDL2_RendererType;

    PyCSDL2_Assert(renderer, NULL);
    PyCSDL2_Assert(deftarget, NULL);
    PyCSDL2_Assert(Py_TYPE(deftarget) == &PyCSDL2_WindowType
                   || Py_TYPE(deftarget) == &PyCSDL2_SurfaceType, NULL);

    if (!(self = (PyCSDL2_Renderer*) type->tp_alloc(type, 0)))
        return NULL;
    self->renderer = renderer;
    PyCSDL2_Set(self->deftarget, deftarget);
    return self;
}

/**
 * \brief Implements csdl2.SDL_CreateRenderer()
 *
 * \code{.py}
 * SDL_CreateRenderer(window: SDL_Window, index: int, flags: int)
 *                   -> SDL_Renderer
 * \endcode
 */
static PyCSDL2_Renderer *
PyCSDL2_CreateRenderer(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_Renderer *renderer;
    PyCSDL2_Window *window;
    int index;
    Uint32 flags;
    PyCSDL2_Renderer *out;
    static char *kwlist[] = {"window", "index", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!i" Uint32_UNIT, kwlist,
                                     &PyCSDL2_WindowType, &window, &index,
                                     &flags))
        return NULL;
    PyCSDL2_Assert(window->window, NULL);
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
static PyCSDL2_Renderer *
PyCSDL2_CreateSoftwareRenderer(PyObject *module, PyObject *args,
                               PyObject *kwds)
{
    PyCSDL2_Surface *surface;
    SDL_Renderer *renderer;
    PyCSDL2_Renderer *out;
    static char *kwlist[] = {"surface", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_SurfaceType, &surface))
        return NULL;
    PyCSDL2_Assert(surface->surface, NULL);
    if (!(renderer = SDL_CreateSoftwareRenderer(surface->surface)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_RendererCreate(renderer, (PyObject*) surface))) {
        SDL_DestroyRenderer(renderer);
        return NULL;
    }
    return out;
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
    PyCSDL2_Renderer *renderer;
    unsigned char r, g, b, a;
    static char *kwlist[] = {"renderer", "r", "g", "b", "a", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!bbbb", kwlist,
                                     &PyCSDL2_RendererType, &renderer,
                                     &r, &g, &b, &a))
        return NULL;
    PyCSDL2_Assert(renderer->renderer, NULL);
    if (SDL_SetRenderDrawColor(renderer->renderer, r, g, b, a))
        return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
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
    PyCSDL2_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RendererType, &renderer))
        return NULL;
    PyCSDL2_Assert(renderer->renderer, NULL);
    if (SDL_RenderClear(renderer->renderer))
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
    PyCSDL2_Renderer *renderer;
    Py_buffer rect;
    int ret;
    static char *kwlist[] = {"renderer", "rect", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O&", kwlist,
                                     &PyCSDL2_RendererType, &renderer,
                                     PyCSDL2_ConvertRectRead, &rect))
        return NULL;
    PyCSDL2_Assert(renderer->renderer, (PyBuffer_Release(&rect), NULL));
    ret = SDL_RenderFillRect(renderer->renderer, rect.buf);
    PyBuffer_Release(&rect);
    if (ret) return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
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
    PyCSDL2_Renderer *renderer;
    static char *kwlist[] = {"renderer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RendererType, &renderer))
        return NULL;
    PyCSDL2_Assert(renderer->renderer, NULL);
    SDL_RenderPresent(renderer->renderer);
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
    PyCSDL2_Assert(renderer->renderer, NULL);
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
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_RendererType)) { return 0; }
    Py_INCREF(&PyCSDL2_RendererType);
    if (PyModule_AddObject(module, "SDL_Renderer",
                           (PyObject*) &PyCSDL2_RendererType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RENDER_H_ */
