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

/**
 * \brief Validates the PyCSDL2_PaletteColors object.
 *
 * A PyCSDL2_PaletteColors object is valid if self->palette and self->colors
 * are not NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_PaletteColorsValid(PyCSDL2_PaletteColors *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!self->palette) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_PaletteColors");
        return 0;
    }

    if (!PyCSDL2_Assert(self->colors))
        return 0;

    return 1;
}

/** \brief getbufferproc for PyCSDL2_PaletteColorsType */
static int
PyCSDL2_PaletteColorsGetBuffer(PyCSDL2_PaletteColors *self, Py_buffer *view,
                               int flags)
{
    static Py_ssize_t strides[1] = {sizeof(SDL_Color)};

    if (!PyCSDL2_PaletteColorsValid(self))
        return -1;

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

    if (!PyCSDL2_Assert(palette))
        return NULL;

    if (!PyCSDL2_Assert(palette->colors))
        return NULL;

    if (!PyCSDL2_Assert(palette->ncolors))
        return NULL;

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

static PyTypeObject PyCSDL2_PaletteType;

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

/**
 * \brief Validates the PyCSDL2_Palette object.
 *
 * A PyCSDL2_Palette object is valid if self->palette and self->colors are not
 * NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_PaletteValid(PyCSDL2_Palette *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_PaletteType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_Palette", (PyObject*)self);
        return 0;
    }

    if (!self->palette) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_Palette");
        return 0;
    }

    if (!PyCSDL2_Assert(self->colors))
        return 0;

    return 1;
}

/** \brief Getter for SDL_Palette.ncolors */
static PyObject *
PyCSDL2_PaletteGetNColors(PyCSDL2_Palette *self, void *closure)
{
    if (!PyCSDL2_PaletteValid(self))
        return NULL;
    return PyLong_FromLong(self->palette->ncolors);
}

/** \brief Getter for SDL_Palette.colors */
static PyObject *
PyCSDL2_PaletteGetColors(PyCSDL2_Palette *self, void *closure)
{
    if (!PyCSDL2_PaletteValid(self))
        return NULL;
    return PyCSDL2_Get((PyObject*) self->colors);
}

/** \brief Getter for SDL_Palette.version */
static PyObject *
PyCSDL2_PaletteGetVersion(PyCSDL2_Palette *self, void *closure)
{
    if (!PyCSDL2_PaletteValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->palette->version);
}

/** \brief Getter for SDL_Palette.refcount */
static PyObject *
PyCSDL2_PaletteGetRefcount(PyCSDL2_Palette *self, void *closure)
{
    if (!PyCSDL2_PaletteValid(self))
        return NULL;
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
static PyObject *
PyCSDL2_PaletteCreate(SDL_Palette *palette)
{
    PyCSDL2_Palette *self;
    PyTypeObject *type = &PyCSDL2_PaletteType;
    PyCSDL2_PaletteColors *colors;

    if (!PyCSDL2_Assert(palette))
        return NULL;

    if (!PyCSDL2_Assert(palette->colors))
        return NULL;

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
    return (PyObject*)self;
}

/**
 * \brief Borrow the SDL_Palette pointer managed by the PyCSDL2_Palette.
 *
 * \param obj The PyCSDL2_Palette object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_PalettePtr(PyObject *obj, SDL_Palette **out)
{
    PyCSDL2_Palette *self = (PyCSDL2_Palette*)obj;

    if (!PyCSDL2_PaletteValid(self))
        return 0;

    if (out)
        *out = self->palette;

    return 1;
}

/** \brief Instance data for SDL_PixelFormatType */
typedef struct PyCSDL2_PixelFormat {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief SDL_PixelFormat which this instance owns */
    SDL_PixelFormat *pfmt;
    /** \brief Palette attribute */
    PyCSDL2_Palette *palette;
} PyCSDL2_PixelFormat;

static PyTypeObject PyCSDL2_PixelFormatType;

/** \brief GC traverse function for PyCSDL2_PixelFormatType */
static int
PyCSDL2_PixelFormatTraverse(PyCSDL2_PixelFormat *self, visitproc visit,
                            void *arg)
{
    Py_VISIT(self->palette);
    return 0;
}

/** \brief GC clear function for PyCSDL2_PixelFormatType */
static int
PyCSDL2_PixelFormatClear(PyCSDL2_PixelFormat *self)
{
    Py_CLEAR(self->palette);
    return 0;
}

/** \brief Destructor for PyCSDL2_PixelFormatType */
static void
PyCSDL2_PixelFormatDealloc(PyCSDL2_PixelFormat *self)
{
    PyCSDL2_PixelFormatClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->pfmt)
        SDL_FreeFormat(self->pfmt);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Validates the PyCSDL2_PixelFormat object.
 *
 * A PyCSDL2_PixelFormat object is valid of self->pfmt is not NULL.
 *
 * \returns 1 if the object is valid, 0 otherwise.
 */
static int
PyCSDL2_PixelFormatValid(PyCSDL2_PixelFormat *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_PixelFormatType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_PixelFormat", (PyObject*)self);
        return 0;
    }

    if (!self->pfmt) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_PixelFormat");
        return 0;
    }

    return 1;
}

/** \brief Getter for SDL_PixelFormat.format */
static PyObject *
PyCSDL2_PixelFormatGetFormat(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->format);
}

/** \brief Getter for SDL_PixelFormat.palette */
static PyObject *
PyCSDL2_PixelFormatGetPalette(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyCSDL2_Get((PyObject*) self->palette);
}

/** \brief Getter for SDL_PixelFormat.BitsPerPixel */
static PyObject *
PyCSDL2_PixelFormatGetBitsPerPixel(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->BitsPerPixel);
}

/** \brief Getter for SDL_PixelFormat.BytesPerPixel */
static PyObject *
PyCSDL2_PixelFormatGetBytesPerPixel(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->BytesPerPixel);
}

/** \brief Getter for SDL_PixelFormat.Rmask */
static PyObject *
PyCSDL2_PixelFormatGetRmask(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Rmask);
}

/** \brief Getter for SDL_PixelFormat.Gmask */
static PyObject *
PyCSDL2_PixelFormatGetGmask(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Gmask);
}

/** \brief Getter for SDL_PixelFormat.Bmask */
static PyObject *
PyCSDL2_PixelFormatGetBmask(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Bmask);
}

/** \brief Getter for SDL_PixelFormat.Amask */
static PyObject *
PyCSDL2_PixelFormatGetAmask(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Amask);
}

/** \brief Getter for SDL_PixelFormat.Rloss */
static PyObject *
PyCSDL2_PixelFormatGetRloss(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Rloss);
}

/** \brief Getter for SDL_PixelFormat.Gloss */
static PyObject *
PyCSDL2_PixelFormatGetGloss(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Gloss);
}

/** \brief Getter for SDL_PixelFormat.Bloss */
static PyObject *
PyCSDL2_PixelFormatGetBloss(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Bloss);
}

/** \brief Getter for SDL_PixelFormat.Aloss */
static PyObject *
PyCSDL2_PixelFormatGetAloss(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Aloss);
}

/** \brief Getter for SDL_PixelFormat.Rshift */
static PyObject *
PyCSDL2_PixelFormatGetRshift(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Rshift);
}

/** \brief Getter for SDL_PixelFormat.Gshift */
static PyObject *
PyCSDL2_PixelFormatGetGshift(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Gshift);
}

/** \brief Getter for SDL_PixelFormat.Bshift */
static PyObject *
PyCSDL2_PixelFormatGetBshift(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Bshift);
}

/** \brief Getter for SDL_PixelFormat.Ashift */
static PyObject *
PyCSDL2_PixelFormatGetAshift(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->pfmt->Ashift);
}

/** \brief Getter for SDL_PixelFormat.refcount */
static PyObject *
PyCSDL2_PixelFormatGetRefcount(PyCSDL2_PixelFormat *self, void *closure)
{
    if (!PyCSDL2_PixelFormatValid(self))
        return NULL;
    return PyLong_FromLong(self->pfmt->refcount);
}

/** \brief List of getters and setters for PyCSDL2_PixelFormatType */
static PyGetSetDef PyCSDL2_PixelFormatGetSetters[] = {
    {"format",
     (getter) PyCSDL2_PixelFormatGetFormat,
     (setter) NULL,
     "(readonly) SDL_PIXELFORMAT_* constant of this pixel format.",
     NULL},
    {"palette",
     (getter) PyCSDL2_PixelFormatGetPalette,
     (setter) NULL,
     "(readonly) The SDL_Palette associated with this pixel format, or None\n"
     "if the format doesn't have a palette.\n",
     NULL},
    {"BitsPerPixel",
     (getter) PyCSDL2_PixelFormatGetBitsPerPixel,
     (setter) NULL,
     "(readonly) The number of significant bits in a pixel value\n"
     "e.g. 8, 15, 16, 24, 32.\n",
     NULL},
    {"BytesPerPixel",
     (getter) PyCSDL2_PixelFormatGetBytesPerPixel,
     (setter) NULL,
     "(readonly) The number of bytes required to hold a pixel value\n"
     "e.g. 1, 2, 3, 4.\n",
     NULL},
    {"Rmask",
     (getter) PyCSDL2_PixelFormatGetRmask,
     (setter) NULL,
     "(readonly) A mask representing the location of the red component of a\n"
     "pixel.\n",
     NULL},
    {"Gmask",
     (getter) PyCSDL2_PixelFormatGetGmask,
     (setter) NULL,
     "(readonly) A mask representing the location of the green component of\n"
     "a pixel.\n",
     NULL},
    {"Bmask",
     (getter) PyCSDL2_PixelFormatGetBmask,
     (setter) NULL,
     "(readonly) A mask representing the location of the blue component of\n"
     "a pixel.\n",
     NULL},
    {"Amask",
     (getter) PyCSDL2_PixelFormatGetAmask,
     (setter) NULL,
     "(readonly) A mask representing the location of the alpha component of\n"
     "a pixel. 0 if the pixel format doesn't have any alpha channel.\n",
     NULL},
    {"Rloss",
     (getter) PyCSDL2_PixelFormatGetRloss,
     (setter) NULL,
     "(readonly) Red value of a pixel has this number of bits less compared\n"
     "to 8-bit values.\n",
     NULL},
    {"Gloss",
     (getter) PyCSDL2_PixelFormatGetGloss,
     (setter) NULL,
     "(readonly) Green value of a pixel has this number of bits less\n"
     "compared to 8-bit values.\n",
     NULL},
    {"Bloss",
     (getter) PyCSDL2_PixelFormatGetBloss,
     (setter) NULL,
     "(readonly) Blue value of a pixel has this number of bits less\n"
     "compared to 8-bit values.\n",
     NULL},
    {"Aloss",
     (getter) PyCSDL2_PixelFormatGetAloss,
     (setter) NULL,
     "(readonly) Alpha value of a pixel has this number of bits less\n"
     "compared to 8-bit values.\n",
     NULL},
    {"Rshift",
     (getter) PyCSDL2_PixelFormatGetRshift,
     (setter) NULL,
     "(readonly) The bit index of the red field of a pixel.\n",
     NULL},
    {"Gshift",
     (getter) PyCSDL2_PixelFormatGetGshift,
     (setter) NULL,
     "(readonly) The bit index of the green field of a pixel.\n",
     NULL},
    {"Bshift",
     (getter) PyCSDL2_PixelFormatGetBshift,
     (setter) NULL,
     "(readonly) The bit index of the blue field of a pixel.\n",
     NULL},
    {"Ashift",
     (getter) PyCSDL2_PixelFormatGetAshift,
     (setter) NULL,
     "(readonly) The bit index of the alpha field of a pixel.\n",
     NULL},
    {"refcount",
     (getter) PyCSDL2_PixelFormatGetRefcount,
     (setter) NULL,
     "(readonly) SDL's internal reference count.\n",
     NULL},
    {NULL}
};

/** \brief Type definition for csdl2.SDL_PixelFormat */
static PyTypeObject PyCSDL2_PixelFormatType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_PixelFormat",
    /* tp_basicsize      */ sizeof(PyCSDL2_PixelFormat),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_PixelFormatDealloc,
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
    "Pixel format information\n"
    "\n"
    "This struct cannot be directly constructed. Use SDL_AllocFormat()\n"
    "instead.\n",
    /* tp_traverse       */ (traverseproc) PyCSDL2_PixelFormatTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_PixelFormatClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_PixelFormat, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_PixelFormatGetSetters
};

/**
 * \brief Creates an instance of PyCSDL2_PixelFormatType
 *
 * \param pfmt The SDL_PixelFormat to manage. Will steal the reference to it.
 */
static PyObject *
PyCSDL2_PixelFormatCreate(SDL_PixelFormat *pfmt)
{
    PyCSDL2_PixelFormat *self;
    PyTypeObject *type = &PyCSDL2_PixelFormatType;

    if (!PyCSDL2_Assert(pfmt))
        return NULL;

    if (!(self = (PyCSDL2_PixelFormat*) type->tp_alloc(type, 0)))
        return NULL;
    if (pfmt->palette) {
        PyCSDL2_Palette *palette;

        pfmt->palette->refcount += 1;
        palette = (PyCSDL2_Palette*)PyCSDL2_PaletteCreate(pfmt->palette);
        if (!palette) {
            pfmt->palette->refcount -= 1;
            Py_DECREF(self);
            return NULL;
        }
        self->palette = palette;
    }
    self->pfmt = pfmt;
    return (PyObject*)self;
}

/**
 * \brief Borrow the SDL_PixelFormat pointer managed by the PyCSDL2_PixelFormat
 *        object.
 *
 * \param obj The PyCSDL2_PixelFormat object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_PixelFormatPtr(PyObject *obj, SDL_PixelFormat **out)
{
    PyCSDL2_PixelFormat *self = (PyCSDL2_PixelFormat*)obj;

    if (!PyCSDL2_PixelFormatValid(self))
        return 0;

    if (out)
        *out = self->pfmt;

    return 1;
}

/**
 * \brief Implements csdl2.SDL_AllocFormat()
 *
 * \code{.py}
 * SDL_AllocFormat(pixel_format: int) -> SDL_PixelFormat
 * \endcode
 */
static PyObject *
PyCSDL2_AllocFormat(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 pixel_format;
    SDL_PixelFormat *pfmt;
    PyObject *out;
    static char *kwlist[] = {"pixel_format", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT, kwlist,
                                     &pixel_format))
        return NULL;
    if (!(pfmt = SDL_AllocFormat(pixel_format)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_PixelFormatCreate(pfmt))) {
        SDL_FreeFormat(pfmt);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_FreeFormat()
 *
 * \code{.py}
 * SDL_FreeFormat(format: SDL_PixelFormat) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_FreeFormat(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_PixelFormat *pfmt;
    static char *kwlist[] = {"format", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_PixelFormatType, &pfmt))
        return NULL;

    if (!PyCSDL2_PixelFormatValid(pfmt))
        return NULL;

    PyCSDL2_PixelFormatClear(pfmt);
    SDL_FreeFormat(pfmt->pfmt);
    pfmt->pfmt = NULL;
    Py_RETURN_NONE;
}

/**
* \brief Implements csdl2.SDL_AllocPalette()
*
* \code{.py}
* SDL_AllocPalette(ncolors: int) -> SDL_Palette
* \endcode
*/
static PyObject *
PyCSDL2_AllocPalette(PyObject *module, PyObject *args, PyObject *kwds)
{
    int ncolors;
    SDL_Palette *palette;
    PyObject *out;
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

    if (!PyCSDL2_PaletteValid(palette))
        return NULL;

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

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_PaletteColorsType)) { return 0; }

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_PaletteType) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_PixelFormatType) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_PIXELS_H_ */
