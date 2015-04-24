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
 * \file pixels.h
 * \brief Bindings for SDL_pixels.h
 *
 * Implements bindings for SDL's pixel formats and conversion routines API
 * (SDL_pixels.h)
 */
#ifndef _PYCSDL2_PIXELS_H_
#define _PYCSDL2_PIXELS_H_
#include <Python.h>
#include <SDL_surface.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief Instance data for PyCSDL2_PaletteColorsType */
typedef struct PyCSDL2_PaletteColors {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief Pointer to SDL_Palette this instance owns */
    SDL_Palette *palette;
    /** \brief Pointer to SDL_Color buffer */
    SDL_Color *colors;
    /** \brief Shape of colors buffer */
    Py_ssize_t shape[1];
} PyCSDL2_PaletteColors;

/** \brief Destructor for PyCSDL2_PaletteColorsType */
static void
PyCSDL2_PaletteColorsDealloc(PyCSDL2_PaletteColors *self)
{
    if (self->in_weakreflist)
        PyObject_ClearWeakRefs((PyObject*) self);
    if (self->palette)
        SDL_FreePalette(self->palette);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief getbufferproc for PyCSDL2_PaletteColorsType */
static int
PyCSDL2_PaletteColorsGetBuffer(PyCSDL2_PaletteColors *self, Py_buffer *view,
                               int flags)
{
    static Py_ssize_t strides[1] = {sizeof(SDL_Color)};

    if ((flags & PyBUF_WRITABLE) == PyBUF_WRITABLE) {
        PyErr_SetString(PyExc_BufferError, "Object is not writable.");
        return -1;
    }
    view->buf = self->colors;
    Py_INCREF((PyObject*) self);
    view->obj = (PyObject*) self;
    view->len = self->shape[0] * sizeof(SDL_Color);
    view->readonly = 1;
    view->itemsize = sizeof(SDL_Color);
    view->format = "BBBB";
    view->ndim = 1;
    view->shape = self->shape;
    view->strides = strides;
    view->suboffsets = NULL;
    view->internal = NULL;
    return 0;
}

/** \brief Buffer protocol definition for PyCSDL2_PaletteColorsType */
static PyBufferProcs PyCSDL2_PaletteColorsBufferProcs = {
    (getbufferproc) PyCSDL2_PaletteColorsGetBuffer,
    (releasebufferproc) NULL
};

/** \brief Type definition for csdl2.SDL_PaletteColors */
static PyTypeObject PyCSDL2_PaletteColorsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_PaletteColors",
    /* tp_basicsize      */ sizeof(PyCSDL2_PaletteColors),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_PaletteColorsDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_PaletteColorsBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "Array of palette SDL_Colors\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_PaletteColors, in_weakreflist),
};

/**
 * \brief Creates an instance of PyCSDL2_PaletteColorsType
 *
 * \param palette SDL_Palette to manage the colors array for. Will steal the
 *                reference.
 */
static PyCSDL2_PaletteColors *
PyCSDL2_PaletteColorsCreate(SDL_Palette *palette)
{
    PyCSDL2_PaletteColors *self;
    PyTypeObject *type = &PyCSDL2_PaletteColorsType;

    PyCSDL2_Assert(palette);
    PyCSDL2_Assert(palette->colors);
    PyCSDL2_Assert(palette->ncolors);
    if (!(self = (PyCSDL2_PaletteColors*) type->tp_alloc(type, 0)))
        return NULL;
    self->palette = palette;
    self->colors = palette->colors;
    self->shape[0] = palette->ncolors;
    return self;
}

/** \brief Instance data for PyCSDL2_PaletteType */
typedef struct PyCSDL2_Palette {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief Pointer to SDL_Palette this instance owns */
    SDL_Palette *palette;
    /** \brief View on the "colors" attribute */
    PyCSDL2_PaletteColors *colors;
} PyCSDL2_Palette;

/** \brief GC Traverse function for PyCSDL2_PaletteType */
static int
PyCSDL2_PaletteTraverse(PyCSDL2_Palette *self, visitproc visit, void *arg)
{
    Py_VISIT(self->colors);
    return 0;
}

/** \brief GC Clear function for PyCSDL2_PaletteType */
static int
PyCSDL2_PaletteClear(PyCSDL2_Palette *self)
{
    Py_CLEAR(self->colors);
    return 0;
}

/** \brief Destructor for PyCSDL2_PaletteType */
static void
PyCSDL2_PaletteDealloc(PyCSDL2_Palette *self)
{
    PyCSDL2_PaletteClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->palette)
        SDL_FreePalette(self->palette);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Getter for SDL_Palette.ncolors */
static PyObject *
PyCSDL2_PaletteGetNColors(PyCSDL2_Palette *self, void *closure)
{
    PyCSDL2_Assert(self->palette);
    return PyLong_FromLong(self->palette->ncolors);
}

/** \brief Getter for SDL_Palette.colors */
static PyObject *
PyCSDL2_PaletteGetColors(PyCSDL2_Palette *self, void *closure)
{
    PyCSDL2_Assert(self->palette);
    return PyCSDL2_Get((PyObject*) self->colors);
}

/** \brief Getter for SDL_Palette.version */
static PyObject *
PyCSDL2_PaletteGetVersion(PyCSDL2_Palette *self, void *closure)
{
    PyCSDL2_Assert(self->palette);
    return PyLong_FromUnsignedLong(self->palette->version);
}

/** \brief Getter for SDL_Palette.refcount */
static PyObject *
PyCSDL2_PaletteGetRefcount(PyCSDL2_Palette *self, void *closure)
{
    PyCSDL2_Assert(self->palette);
    return PyLong_FromLong(self->palette->refcount);
}

/** \brief List of getters and setters of PyCSDL2_PaletteType */
static PyGetSetDef PyCSDL2_PaletteGetSetters[] = {
    {"ncolors",
     (getter) PyCSDL2_PaletteGetNColors,
     (setter) NULL,
     "(readonly) Number of colors in the palette.",
     NULL},
    {"colors",
     (getter) PyCSDL2_PaletteGetColors,
     (setter) NULL,
     "(readonly) An array of SDL_Color structures representing the palette.\n"
     "This array cannot be modified directly, use SDL_SetPaletteColors()\n"
     "instead.\n",
     NULL},
    {"version",
     (getter) PyCSDL2_PaletteGetVersion,
     (setter) NULL,
     "(readonly) Internal version number used by SDL to track changes to\n"
     "the palette.\n",
     NULL},
    {"refcount",
     (getter) PyCSDL2_PaletteGetRefcount,
     (setter) NULL,
     "(readonly) SDL's internal reference count.\n",
     NULL},
    {NULL}
};

/** \brief Type definition for csdl2.SDL_Palette */
static PyTypeObject PyCSDL2_PaletteType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Palette",
    /* tp_basicsize      */ sizeof(PyCSDL2_Palette),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_PaletteDealloc,
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
    "A color palette\n"
    "\n"
    "Every pixel in an 8-bit surface is an index into the `colors` field\n"
    "of the SDL_Palette referenced by the SDL_PixelFormat.\n"
    "\n"
    "This structure cannot be directly constructed. One will be\n"
    "automatically created when needed when SDL allocates a \n"
    "SDL_PixelFormat, or through SDL_AllocPalette().\n",
    /* tp_traverse       */ (traverseproc) PyCSDL2_PaletteTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_PaletteClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Palette, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_PaletteGetSetters
};

/**
 * \brief Creates an instance of PyCSDL2_PaletteType
 *
 * \param palette SDL_Palette to manage. Steals the reference.
 */
static PyCSDL2_Palette *
PyCSDL2_PaletteCreate(SDL_Palette *palette)
{
    PyCSDL2_Palette *self;
    PyTypeObject *type = &PyCSDL2_PaletteType;
    PyCSDL2_PaletteColors *colors;

    PyCSDL2_Assert(palette);
    PyCSDL2_Assert(palette->colors);
    if (!(self = (PyCSDL2_Palette*) type->tp_alloc(type, 0)))
        return NULL;
    palette->refcount += 1;
    if (!(colors = PyCSDL2_PaletteColorsCreate(palette))) {
        palette->refcount -= 1;
        Py_DECREF(self);
        return NULL;
    }
    self->palette = palette;
    self->colors = colors;
    return self;
}

/**
 * \brief Implements csdl2.SDL_AllocPalette()
 *
 * \code{.py}
 * SDL_AllocPalette(ncolors: int) -> SDL_Palette
 * \endcode
 */
static PyCSDL2_Palette *
PyCSDL2_AllocPalette(PyObject *module, PyObject *args, PyObject *kwds)
{
    int ncolors;
    SDL_Palette *palette;
    PyCSDL2_Palette *out;
    static char *kwlist[] = {"ncolors", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &ncolors))
        return NULL;
    if (!(palette = SDL_AllocPalette(ncolors)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_PaletteCreate(palette))) {
        SDL_FreePalette(palette);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_FreePalette()
 *
 * \code{.py}
 * SDL_FreePalette(palette: SDL_Palette) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_FreePalette(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Palette *palette;
    static char *kwlist[] = {"palette", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_PaletteType, &palette))
        return NULL;
    PyCSDL2_Assert(palette->palette);
    PyCSDL2_PaletteClear(palette);
    SDL_FreePalette(palette->palette);
    palette->palette = NULL;
    Py_RETURN_NONE;
}

/**
 * \brief Initializes bindings to SDL_pixels.h
 *
 * Adds constants defined in SDL_pixels.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initpixels(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_ALPHA_OPAQUE", SDL_ALPHA_OPAQUE},
        {"SDL_ALPHA_TRANSPARENT", SDL_ALPHA_TRANSPARENT},

        {"SDL_PIXELTYPE_UNKNOWN", SDL_PIXELTYPE_UNKNOWN},
        {"SDL_PIXELTYPE_INDEX1", SDL_PIXELTYPE_INDEX1},
        {"SDL_PIXELTYPE_INDEX4", SDL_PIXELTYPE_INDEX4},
        {"SDL_PIXELTYPE_INDEX8", SDL_PIXELTYPE_INDEX8},
        {"SDL_PIXELTYPE_PACKED8", SDL_PIXELTYPE_PACKED8},
        {"SDL_PIXELTYPE_PACKED16", SDL_PIXELTYPE_PACKED16},
        {"SDL_PIXELTYPE_PACKED32", SDL_PIXELTYPE_PACKED32},
        {"SDL_PIXELTYPE_ARRAYU8", SDL_PIXELTYPE_ARRAYU8},
        {"SDL_PIXELTYPE_ARRAYU16", SDL_PIXELTYPE_ARRAYU16},
        {"SDL_PIXELTYPE_ARRAYU32", SDL_PIXELTYPE_ARRAYU32},
        {"SDL_PIXELTYPE_ARRAYF16", SDL_PIXELTYPE_ARRAYF16},
        {"SDL_PIXELTYPE_ARRAYF32", SDL_PIXELTYPE_ARRAYF32},

        {"SDL_BITMAPORDER_NONE", SDL_BITMAPORDER_NONE},
        {"SDL_BITMAPORDER_4321", SDL_BITMAPORDER_4321},
        {"SDL_BITMAPORDER_1234", SDL_BITMAPORDER_1234},

        {"SDL_PACKEDORDER_NONE", SDL_PACKEDORDER_NONE},
        {"SDL_PACKEDORDER_XRGB", SDL_PACKEDORDER_XRGB},
        {"SDL_PACKEDORDER_RGBX", SDL_PACKEDORDER_RGBX},
        {"SDL_PACKEDORDER_ARGB", SDL_PACKEDORDER_ARGB},
        {"SDL_PACKEDORDER_RGBA", SDL_PACKEDORDER_RGBA},
        {"SDL_PACKEDORDER_XBGR", SDL_PACKEDORDER_XBGR},
        {"SDL_PACKEDORDER_BGRX", SDL_PACKEDORDER_BGRX},
        {"SDL_PACKEDORDER_ABGR", SDL_PACKEDORDER_ABGR},
        {"SDL_PACKEDORDER_BGRA", SDL_PACKEDORDER_BGRA},

        {"SDL_ARRAYORDER_NONE", SDL_ARRAYORDER_NONE},
        {"SDL_ARRAYORDER_RGB", SDL_ARRAYORDER_RGB},
        {"SDL_ARRAYORDER_RGBA", SDL_ARRAYORDER_RGBA},
        {"SDL_ARRAYORDER_ARGB", SDL_ARRAYORDER_ARGB},
        {"SDL_ARRAYORDER_BGR", SDL_ARRAYORDER_BGR},
        {"SDL_ARRAYORDER_BGRA", SDL_ARRAYORDER_BGRA},
        {"SDL_ARRAYORDER_ABGR", SDL_ARRAYORDER_ABGR},

        {"SDL_PACKEDLAYOUT_NONE", SDL_PACKEDLAYOUT_NONE},
        {"SDL_PACKEDLAYOUT_332", SDL_PACKEDLAYOUT_332},
        {"SDL_PACKEDLAYOUT_4444", SDL_PACKEDLAYOUT_4444},
        {"SDL_PACKEDLAYOUT_1555", SDL_PACKEDLAYOUT_1555},
        {"SDL_PACKEDLAYOUT_5551", SDL_PACKEDLAYOUT_5551},
        {"SDL_PACKEDLAYOUT_565", SDL_PACKEDLAYOUT_565},
        {"SDL_PACKEDLAYOUT_8888", SDL_PACKEDLAYOUT_8888},
        {"SDL_PACKEDLAYOUT_2101010", SDL_PACKEDLAYOUT_2101010},
        {"SDL_PACKEDLAYOUT_1010102", SDL_PACKEDLAYOUT_1010102},

        {"SDL_PIXELFORMAT_UNKNOWN", SDL_PIXELFORMAT_UNKNOWN},
        {"SDL_PIXELFORMAT_INDEX1LSB", SDL_PIXELFORMAT_INDEX1LSB},
        {"SDL_PIXELFORMAT_INDEX1MSB", SDL_PIXELFORMAT_INDEX1MSB},
        {"SDL_PIXELFORMAT_INDEX4LSB", SDL_PIXELFORMAT_INDEX4LSB},
        {"SDL_PIXELFORMAT_INDEX4MSB", SDL_PIXELFORMAT_INDEX4MSB},
        {"SDL_PIXELFORMAT_INDEX8", SDL_PIXELFORMAT_INDEX8},
        {"SDL_PIXELFORMAT_RGB332", SDL_PIXELFORMAT_RGB332},
        {"SDL_PIXELFORMAT_RGB444", SDL_PIXELFORMAT_RGB444},
        {"SDL_PIXELFORMAT_RGB555", SDL_PIXELFORMAT_RGB555},
        {"SDL_PIXELFORMAT_BGR555", SDL_PIXELFORMAT_BGR555},
        {"SDL_PIXELFORMAT_ARGB4444", SDL_PIXELFORMAT_ARGB4444},
        {"SDL_PIXELFORMAT_RGBA4444", SDL_PIXELFORMAT_RGBA4444},
        {"SDL_PIXELFORMAT_ABGR4444", SDL_PIXELFORMAT_ABGR4444},
        {"SDL_PIXELFORMAT_BGRA4444", SDL_PIXELFORMAT_BGRA4444},
        {"SDL_PIXELFORMAT_ARGB1555", SDL_PIXELFORMAT_ARGB1555},
        {"SDL_PIXELFORMAT_RGBA5551", SDL_PIXELFORMAT_RGBA5551},
        {"SDL_PIXELFORMAT_ABGR1555", SDL_PIXELFORMAT_ABGR1555},
        {"SDL_PIXELFORMAT_BGRA5551", SDL_PIXELFORMAT_BGRA5551},
        {"SDL_PIXELFORMAT_RGB565", SDL_PIXELFORMAT_RGB565},
        {"SDL_PIXELFORMAT_BGR565", SDL_PIXELFORMAT_BGR565},
        {"SDL_PIXELFORMAT_RGB24", SDL_PIXELFORMAT_RGB24},
        {"SDL_PIXELFORMAT_BGR24", SDL_PIXELFORMAT_BGR24},
        {"SDL_PIXELFORMAT_RGB888", SDL_PIXELFORMAT_RGB888},
        {"SDL_PIXELFORMAT_RGBX8888", SDL_PIXELFORMAT_RGBX8888},
        {"SDL_PIXELFORMAT_BGR888", SDL_PIXELFORMAT_BGR888},
        {"SDL_PIXELFORMAT_BGRX8888", SDL_PIXELFORMAT_BGRX8888},
        {"SDL_PIXELFORMAT_ARGB8888", SDL_PIXELFORMAT_ARGB8888},
        {"SDL_PIXELFORMAT_RGBA8888", SDL_PIXELFORMAT_RGBA8888},
        {"SDL_PIXELFORMAT_ABGR8888", SDL_PIXELFORMAT_ABGR8888},
        {"SDL_PIXELFORMAT_BGRA8888", SDL_PIXELFORMAT_BGRA8888},
        {"SDL_PIXELFORMAT_ARGB2101010", SDL_PIXELFORMAT_ARGB2101010},
        {"SDL_PIXELFORMAT_YV12", SDL_PIXELFORMAT_YV12},
        {"SDL_PIXELFORMAT_IYUV", SDL_PIXELFORMAT_IYUV},
        {"SDL_PIXELFORMAT_YUY2", SDL_PIXELFORMAT_YUY2},
        {"SDL_PIXELFORMAT_UYVY", SDL_PIXELFORMAT_UYVY},
        {"SDL_PIXELFORMAT_YVYU", SDL_PIXELFORMAT_YVYU},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_PaletteColorsType)) { return 0; }

    if (PyType_Ready(&PyCSDL2_PaletteType)) { return 0; }
    Py_INCREF(&PyCSDL2_PaletteType);
    if (PyModule_AddObject(module, "SDL_Palette",
                           (PyObject*) &PyCSDL2_PaletteType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_PIXELS_H_ */
