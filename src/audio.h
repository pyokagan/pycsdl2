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
 * \file audio.h
 * \brief Bindings for SDL_audio.h
 *
 * Implements bindings for SDL's Audio Device Management, Playing and Recording
 * (SDL_audio.h)
 */
#ifndef _PYCSDL2_AUDIO_H_
#define _PYCSDL2_AUDIO_H_
#include <Python.h>
#include <SDL_audio.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \defgroup csdl2_SDL_AudioSpec csdl2.SDL_AudioSpec
 *
 * @{
 */

/** \brief Instance data for PyCSDL2_AudioSpecType */
typedef struct PyCSDL2_AudioSpec {
    PyObject_HEAD
    /** \brief Head of weakref list */
    PyObject *in_weakreflist;
    /** \brief Internal SDL_AudioSpec */
    SDL_AudioSpec spec;
    /** \brief Stores the "callback" Python object */
    PyObject *callback;
    /** \brief Stores the "userdata" Python object */
    PyObject *userdata;
} PyCSDL2_AudioSpec;

/** \brief newfunc for PyCSDL2_AudioSpecType */
static PyCSDL2_AudioSpec *
PyCSDL2_AudioSpecNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCSDL2_AudioSpec *self;

    if (!(self = (PyCSDL2_AudioSpec*) type->tp_alloc(type, 0)))
        return NULL;
    return self;
}

/** \brief Traversal function for PyCSDL2_AudioSpecType */
static int
PyCSDL2_AudioSpecTraverse(PyCSDL2_AudioSpec *self, visitproc visit, void *arg)
{
    Py_VISIT(self->callback);
    Py_VISIT(self->userdata);
    return 0;
}

/** \brief Clear function for PyCSDL2_AudioSpecType */
static int
PyCSDL2_AudioSpecClear(PyCSDL2_AudioSpec *self)
{
    Py_CLEAR(self->callback);
    Py_CLEAR(self->userdata);
    return 0;
}

/** \brief Destructor for PyCSDL2_AudioSpecType */
static void
PyCSDL2_AudioSpecDealloc(PyCSDL2_AudioSpec *self)
{
    PyCSDL2_AudioSpecClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief tp_init for PyCSDL2_AudioSpecType */
static int
PyCSDL2_AudioSpecInit(PyCSDL2_AudioSpec *self, PyObject *args, PyObject *kwds)
{
    int freq = 0;
    Uint16 format = 0, samples = 0;
    Uint8 channels = 0, silence = 0;
    Uint32 size = 0;
    PyObject *callback = NULL, *userdata = NULL;
    static char *kwlist[] = {"freq", "format", "channels", "silence",
                             "samples", "size", "callback", "userdata", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i" Uint16_UNIT "bb"
                                     Uint16_UNIT Uint32_UNIT "OO", kwlist,
                                     &freq, &format, &channels, &silence,
                                     &samples, &size, &callback, &userdata))
        return -1;

    self->spec.freq = freq;
    self->spec.format = format;
    self->spec.channels = channels;
    self->spec.silence = silence;
    self->spec.samples = samples;
    self->spec.size = size;
    PyCSDL2_Set(self->callback, callback);
    PyCSDL2_Set(self->userdata, userdata);

    return 0;
}

/** \brief List of members in PyCSDL2_AudioSpecType */
static PyMemberDef PyCSDL2_AudioSpecMembers[] = {
    {"freq", T_INT, offsetof(PyCSDL2_AudioSpec, spec.freq), 0,
     "DSP frequency"},
    {"format", Uint16_TYPE, offsetof(PyCSDL2_AudioSpec, spec.format), 0,
     "Audio data format"},
    {"channels", T_UBYTE, offsetof(PyCSDL2_AudioSpec, spec.channels), 0,
     "Number of separate sound channels"},
    {"silence", T_UBYTE, offsetof(PyCSDL2_AudioSpec, spec.silence), 0,
     "Audio buffer silence value"},
    {"samples", Uint16_TYPE, offsetof(PyCSDL2_AudioSpec, spec.samples), 0,
     "Audio buffer size in samples"},
    {"size", Uint32_TYPE, offsetof(PyCSDL2_AudioSpec, spec.size), 0,
     "Audio buffer size in bytes."},
    {"callback", T_OBJECT, offsetof(PyCSDL2_AudioSpec, callback), 0,
     "The function to call when the audio device needs more data."},
    {"userdata", T_OBJECT, offsetof(PyCSDL2_AudioSpec, userdata), 0,
     "The object that is passed to callback."},
    {NULL}
};

/** \brief Type definition of csdl2.SDL_AudioSpec */
static PyTypeObject PyCSDL2_AudioSpecType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_AudioSpec",
    /* tp_basicsize      */ sizeof(PyCSDL2_AudioSpec),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_AudioSpecDealloc,
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
    "Describes the audio output format and sets the audio callback.\n"
    "\n"
    "This structure is used by SDL_OpenAudioDevice() and SDL_LoadWAV().\n",
    /* tp_traverse       */ (traverseproc) PyCSDL2_AudioSpecTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_AudioSpecClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_AudioSpec, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ PyCSDL2_AudioSpecMembers,
    /* tp_getset         */ 0,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ (initproc) PyCSDL2_AudioSpecInit,
    /* tp_alloc          */ 0,
    /* tp_new            */ (newfunc) PyCSDL2_AudioSpecNew
};

/**
 * \brief Creates an instance of PyCSDL2_AudioSpecType
 *
 * \param spec SDL_AudioSpec data to be initialized with.
 * \returns A new PyCSDL2_AudioSpec on success, or NULL with an exception set
 *          on failure.
 */
static PyCSDL2_AudioSpec *
PyCSDL2_AudioSpecCreate(const SDL_AudioSpec *spec)
{
    PyCSDL2_AudioSpec *self;
    PyTypeObject *type = &PyCSDL2_AudioSpecType;

    if (!PyCSDL2_Assert(spec))
        return NULL;

    self = (PyCSDL2_AudioSpec*) type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->spec = *spec;
    return self;
}

/** @} */

/**
 * \brief Initializes bindings to SDL_audio.h
 *
 * Adds constants defined in SDL_audio.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initaudio(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_AUDIO_MASK_BITSIZE", SDL_AUDIO_MASK_BITSIZE},
        {"SDL_AUDIO_MASK_DATATYPE", SDL_AUDIO_MASK_DATATYPE},
        {"SDL_AUDIO_MASK_ENDIAN", SDL_AUDIO_MASK_ENDIAN},
        {"SDL_AUDIO_MASK_SIGNED", SDL_AUDIO_MASK_SIGNED},

        /* Audio format flags */
        {"AUDIO_U8", AUDIO_U8},
        {"AUDIO_S8", AUDIO_S8},
        {"AUDIO_U16LSB", AUDIO_U16LSB},
        {"AUDIO_S16LSB", AUDIO_S16LSB},
        {"AUDIO_U16MSB", AUDIO_U16MSB},
        {"AUDIO_S16MSB", AUDIO_S16MSB},
        {"AUDIO_U16", AUDIO_U16},
        {"AUDIO_S16", AUDIO_S16},

        /* int32 support */
        {"AUDIO_S32LSB", AUDIO_S32LSB},
        {"AUDIO_S32MSB", AUDIO_S32MSB},
        {"AUDIO_S32", AUDIO_S32},

        /* float32 support */
        {"AUDIO_F32LSB", AUDIO_F32LSB},
        {"AUDIO_F32MSB", AUDIO_F32MSB},
        {"AUDIO_F32", AUDIO_F32},

        /* Native audio byte ordering */
        {"AUDIO_U16SYS", AUDIO_U16SYS},
        {"AUDIO_S16SYS", AUDIO_S16SYS},
        {"AUDIO_S32SYS", AUDIO_S32SYS},
        {"AUDIO_F32SYS", AUDIO_F32SYS},

        /* Allow change flags */
        {"SDL_AUDIO_ALLOW_FREQUENCY_CHANGE", SDL_AUDIO_ALLOW_FREQUENCY_CHANGE},
        {"SDL_AUDIO_ALLOW_FORMAT_CHANGE", SDL_AUDIO_ALLOW_FORMAT_CHANGE},
        {"SDL_AUDIO_ALLOW_CHANNELS_CHANGE", SDL_AUDIO_ALLOW_CHANNELS_CHANGE},
        {"SDL_AUDIO_ALLOW_ANY_CHANGE", SDL_AUDIO_ALLOW_ANY_CHANGE},

        /* Audio state */
        {"SDL_AUDIO_STOPPED", SDL_AUDIO_STOPPED},
        {"SDL_AUDIO_PLAYING", SDL_AUDIO_PLAYING},
        {"SDL_AUDIO_PAUSED", SDL_AUDIO_PAUSED},

        {"SDL_MIX_MAXVOLUME", SDL_MIX_MAXVOLUME},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_AudioSpecType)) { return 0; }
    Py_INCREF(&PyCSDL2_AudioSpecType);
    if (PyModule_AddObject(module, "SDL_AudioSpec",
                           (PyObject*) &PyCSDL2_AudioSpecType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_AUDIO_H_ */
