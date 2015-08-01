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
} PyCSDL2_Texture;

static PyTypeObject PyCSDL2_TextureType;

/** \brief tp_dealloc for PyCSDL2_TextureType */
static void
PyCSDL2_TextureDealloc(PyCSDL2_Texture *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->texture)
        SDL_DestroyTexture(self->texture);
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
PyCSDL2_TextureValid(PyCSDL2_Texture *self)
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
    PyCSDL2_Texture *self;
    PyCSDL2_Renderer *rdr = (PyCSDL2_Renderer*)renderer;
    PyTypeObject *type = &PyCSDL2_TextureType;

    if (!PyCSDL2_Assert(texture) || !PyCSDL2_Assert(renderer))
        return NULL;

    if (!PyCSDL2_RendererValid(rdr))
        return NULL;

    self = (PyCSDL2_Texture*) type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->texture = texture;
    PyCSDL2_Set(self->renderer, rdr);

    return (PyObject*)self;
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

    if (!PyCSDL2_TextureValid(self))
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
    if (!PyCSDL2_TextureValid(self))
        return 0;

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
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_RendererType)) { return 0; }
    Py_INCREF(&PyCSDL2_RendererType);
    if (PyModule_AddObject(module, "SDL_Renderer",
                           (PyObject*) &PyCSDL2_RendererType))
        return 0;

    if (PyType_Ready(&PyCSDL2_TextureType)) { return 0; }
    Py_INCREF(&PyCSDL2_TextureType);
    if (PyModule_AddObject(module, "SDL_Texture",
                           (PyObject*) &PyCSDL2_TextureType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RENDER_H_ */
