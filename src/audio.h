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
#include "rwops.h"

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
    {NULL}
};

/** \brief Getter for SDL_AudioSpec.callback */
static PyObject *
PyCSDL2_AudioSpecGetCallback(PyCSDL2_AudioSpec *self, void *closure)
{
    PyObject *callback;

    if (!self->spec.callback)
        return PyCSDL2_Get(self->callback);

    if (PyCSDL2_VoidPtrCheckPtr(self->callback, self->spec.callback))
        return PyCSDL2_Get(self->callback);

    callback = PyCSDL2_VoidPtrCreate(self->spec.callback);
    if (!callback)
        return NULL;

    PyCSDL2_Set(self->callback, callback);
    return callback;
}

/** \brief Setter for SDL_AudioSpec.callback */
static int
PyCSDL2_AudioSpecSetCallback(PyCSDL2_AudioSpec *self, PyObject *value,
                             void *closure)
{
    PyCSDL2_Set(self->callback, value);
    self->spec.callback = NULL;
    return 0;
}

/** \brief Getter for SDL_AudioSpec.userdata */
static PyObject *
PyCSDL2_AudioSpecGetUserdata(PyCSDL2_AudioSpec *self, void *closure)
{
    PyObject *userdata;

    if (!self->spec.userdata)
        return PyCSDL2_Get(self->userdata);

    if (PyCSDL2_VoidPtrCheckPtr(self->userdata, self->spec.userdata))
        return PyCSDL2_Get(self->userdata);

    userdata = PyCSDL2_VoidPtrCreate(self->spec.userdata);
    if (!userdata)
        return NULL;

    PyCSDL2_Set(self->userdata, userdata);
    return userdata;
}

/** \brief Setter for SDL_AudioSpec.userdata */
static int
PyCSDL2_AudioSpecSetUserdata(PyCSDL2_AudioSpec *self, PyObject *value,
                             void *closure)
{
    PyCSDL2_Set(self->userdata, value);
    self->spec.userdata = NULL;
    return 0;
}

/** \brief List of get-setters for PyCSDL2_AudioSpecType */
static PyGetSetDef PyCSDL2_AudioSpecGetSetters[] = {
    {"callback",
     (getter) PyCSDL2_AudioSpecGetCallback,
     (setter) PyCSDL2_AudioSpecSetCallback,
     "The function to call when the audio device needs more data.",
     NULL},
    {"userdata",
     (getter) PyCSDL2_AudioSpecGetUserdata,
     (setter) PyCSDL2_AudioSpecSetUserdata,
     "The object that is passed to callback.",
     NULL},
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
    /* tp_getset         */ PyCSDL2_AudioSpecGetSetters,
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
static PyObject *
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

    return (PyObject*)self;
}

/**
 * \brief Borrows the SDL_AudioSpec managed by the PyCSDL2_AudioSpec
 *
 * \param obj The PyCSDL2_AudioSpec object
 * \param[out] out Output field
 * \returns 1 on success, 0 with an exception set on failure.
 */
static int
PyCSDL2_AudioSpecPtr(PyObject *obj, SDL_AudioSpec **out)
{
    PyCSDL2_AudioSpec *self = (PyCSDL2_AudioSpec*)obj;

    if (!PyCSDL2_Assert(obj) || !PyCSDL2_Assert(out))
        return 0;

    if (Py_TYPE(obj) != &PyCSDL2_AudioSpecType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_AudioSpec", obj);
        return 0;
    }

    *out = &self->spec;

    return 1;
}

/** @} */

/**
 * \defgroup csdl2_SDL_AudioDevice csdl2.SDL_AudioDevice
 *
 * @{
 */

/** \brief Instance data for PyCSDL2_AudioDeviceType */
typedef struct PyCSDL2_AudioDevice {
    PyObject_HEAD
    /** \brief Head of weakref list */
    PyObject *in_weakreflist;
    /** \brief SDL_AudioDeviceID that this instance owns */
    SDL_AudioDeviceID id;
    /** \brief Audio device's callback Python object */
    PyObject *callback;
    /** \brief Audio device's userdata Python object */
    PyObject *userdata;
    /** \brief buffer object used for passing stream data in callbacks */
    PyCSDL2_Buffer *callback_buf;
} PyCSDL2_AudioDevice;

static PyTypeObject PyCSDL2_AudioDeviceType;

/** \brief Traversal function for PyCSDL2_AudioDeviceType */
static int
PyCSDL2_AudioDeviceTraverse(PyCSDL2_AudioDevice *self, visitproc visit,
                            void *arg)
{
    Py_VISIT(self->callback);
    Py_VISIT(self->userdata);
    Py_VISIT(self->callback_buf);
    return 0;
}

/** \brief Clear function for PyCSDL2_AudioDeviceType */
static int
PyCSDL2_AudioDeviceClear(PyCSDL2_AudioDevice *self)
{
    Py_CLEAR(self->callback);
    Py_CLEAR(self->userdata);
    Py_CLEAR(self->callback_buf);
    return 0;
}

/**
 * \brief Check if the PyCSDL2_AudioDevice is valid.
 *
 * \returns 1 if dev is valid, 0 otherwise.
 */
static int
PyCSDL2_AudioDeviceValid(PyCSDL2_AudioDevice *dev)
{
    if (!PyCSDL2_Assert(dev))
        return 0;

    if (Py_TYPE(dev) != &PyCSDL2_AudioDeviceType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_AudioDevice", (PyObject*)dev);
        return 0;
    }

    if (!dev->id) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_AudioDevice");
        return 0;
    }

    return 1;
}

/**
 * \brief Detaches the SDL_AudioDeviceID from the PyCSDL2_AudioDevice
 */
static SDL_AudioDeviceID
PyCSDL2_AudioDeviceDetach(PyCSDL2_AudioDevice *self)
{
    SDL_AudioDeviceID id;

    if (!PyCSDL2_AudioDeviceValid(self))
        return 0;

    id = self->id;
    PyCSDL2_AudioDeviceClear(self);
    self->id = 0;

    return id;
}

/**
 * \brief Attaches the SDL_AudioDeviceID to the PyCSDL2_AudioDevice
 *
 */
static void
PyCSDL2_AudioDeviceAttach(PyCSDL2_AudioDevice *self, SDL_AudioDeviceID id,
                          PyObject *callback, PyObject *userdata)
{
    assert(!self->id);
    assert(!self->callback);
    assert(!self->userdata);

    self->id = id;
    PyCSDL2_Set(self->callback, callback);
    PyCSDL2_Set(self->userdata, userdata);
}

/** \brief Destructor for PyCSDL2_AudioDevice */
static void
PyCSDL2_AudioDeviceDealloc(PyCSDL2_AudioDevice *self)
{
    PyCSDL2_AudioDeviceClear(self);
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->id) {
        SDL_AudioDeviceID id = self->id;
        self->id = 0;
        Py_BEGIN_ALLOW_THREADS
        SDL_CloseAudioDevice(id);
        Py_END_ALLOW_THREADS
    }
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief SDL-facing callback handler for PyCSDL2_AudioDeviceType */
static void
PyCSDL2_AudioDeviceCallback(void *userdata, Uint8 *stream, int len)
{
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyCSDL2_AudioDevice *self = userdata;
    PyCSDL2_Buffer *buf = self->callback_buf;
    PyObject *ret;

    /*
     * We may be called in-between when the PyCSDL2_AudioDevice was invalidated
     * and SDL_CloseAudioDevice() is actually called. As such, don't treat this
     * as an error.
     */
    if (!PyCSDL2_AudioDeviceValid(self)) {
        PyErr_Clear();
        goto finish;
    }

    PyCSDL2_BufferInit(buf, CTYPE_UCHAR, stream, len, 0);

    ret = PyObject_CallFunction(self->callback, "OOi",
                                self->userdata ? self->userdata : Py_None,
                                buf, len);
    if (!ret)
        PyErr_Print();

    Py_XDECREF(ret);

    if (buf->num_exports)
        Py_FatalError("audio data buffer is still exported");

    buf->buf = NULL;

finish:
    PyGILState_Release(gstate);
}

/** \brief Type definition of csdl2.SDL_AudioSpec */
static PyTypeObject PyCSDL2_AudioDeviceType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_AudioDevice",
    /* tp_basicsize      */ sizeof(PyCSDL2_AudioDevice),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_AudioDeviceDealloc,
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
    "An opened audio device.\n"
    "\n"
    "This is an opaque handle that cannot be directly constructed. Use \n"
    "SDL_OpenAudioDevice() to create one.\n",
    /* tp_traverse       */ (traverseproc) PyCSDL2_AudioDeviceTraverse,
    /* tp_clear          */ (inquiry) PyCSDL2_AudioDeviceClear,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_AudioDevice, in_weakreflist)
};

/**
 * \brief Creates an instance of PyCSDL2_AudioDeviceType
 */
static PyObject *
PyCSDL2_AudioDeviceCreate(SDL_AudioDeviceID id)
{
    PyCSDL2_AudioDevice *self;
    PyTypeObject *type = &PyCSDL2_AudioDeviceType;

    self = (PyCSDL2_AudioDevice*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->callback_buf = PyCSDL2_BufferCreate(CTYPE_UCHAR, NULL, 0, 0, NULL);
    if (!self->callback_buf) {
        Py_DECREF(self);
        return NULL;
    }

    PyCSDL2_AudioDeviceAttach(self, id, NULL, NULL);
    return (PyObject*)self;
}

/**
 * \brief Borrow the SDL_AudioDeviceID managed by the PyCSDL2_AudioDevice
 *
 * \param obj The PyCSDL2_AudioDevice object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_AudioDeviceID(PyObject *obj, SDL_AudioDeviceID *out)
{
    PyCSDL2_AudioDevice *self = (PyCSDL2_AudioDevice*)obj;

    if (!PyCSDL2_AudioDeviceValid(self))
        return 0;

    if (out)
        *out = self->id;

    return 1;
}

/** @} */

/**
 * \defgroup csdl2_SDL_WAVBuf csdl2.SDL_WAVBuf
 *
 * \brief Manages the buffer returned by SDL_LoadWAV() and SDL_LoadWAV_RW()
 *
 * @{
 */

/** \brief Instance data for PyCSDL2_WAVBufType */
typedef struct PyCSDL2_WAVBuf {
    PyCSDL2_BufferHEAD
    /** \brief Head of weakref list */
    PyObject *in_weakreflist;
} PyCSDL2_WAVBuf;

/**
 * \brief Checks if the PyCSDL2_WAVBuf is valid
 */
static int
PyCSDL2_WAVBufValid(PyCSDL2_WAVBuf *buf)
{
    if (!PyCSDL2_Assert(buf))
        return 0;

    if (!buf->buf) {
        PyErr_SetString(PyExc_ValueError, "Invalid SDL_WAVBuf");
        return 0;
    }

    return 1;
}

/**
 * \brief Detaches the buffer from the PyCSDL2_WAVBuf.
 *
 * Transfers ownership of the buffer from the PyCSDL2_WAVBuf object to the
 * caller. The caller will thus now be responsible for freeing the buffer.
 *
 * \param self PyCSDL2_WAVBuf object to detach the buffer from
 * \param[out] len Will be filled with the size of the buffer in bytes
 * \returns The buffer managed by the PyCSDL2_WAVBuf object, or NULL with an
 *          exception set on error.
 */
static Uint8*
PyCSDL2_WAVBufDetach(PyCSDL2_WAVBuf *self, Uint32 *len)
{
    Uint8 *buf;

    if (!PyCSDL2_WAVBufValid(self))
        return NULL;

    if (self->num_exports) {
        PyErr_SetString(PyExc_ValueError, "SDL_WAVBuf is exporting a buffer");
        return NULL;
    }

    buf = self->buf;
    if (len)
        *len = (Uint32) self->len;
    self->buf = NULL;
    return buf;
}

/** \brief Destructor for PyCSDL2_WAVBufType */
static void
PyCSDL2_WAVBufDealloc(PyCSDL2_WAVBuf *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->buf)
        SDL_FreeWAV(self->buf);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Type definition for csdl2.SDL_WAVBuf */
static PyTypeObject PyCSDL2_WAVBufType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_WAVBuf",
    /* tp_basicsize      */ sizeof(PyCSDL2_WAVBuf),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_WAVBufDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_BufferAsBuffer,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */ "Buffer containing WAVE data.",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_WAVBuf, in_weakreflist)
};

/**
 * \brief Creates an instance of PyCSDL2_WAVBufType
 *
 * \param buf Audio buffer to take ownership of.
 * \param len Length of the buffer.
 */
static PyCSDL2_WAVBuf *
PyCSDL2_WAVBufCreate(Uint8 *buf, Uint32 len)
{
    PyCSDL2_WAVBuf *self;
    PyTypeObject *type = &PyCSDL2_WAVBufType;

    self = (PyCSDL2_WAVBuf*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    PyCSDL2_BufferInit((PyCSDL2_Buffer*) self, CTYPE_UCHAR, buf, len, 0);

    return self;
}

/**
 * \brief Internal PyCSDL2_AudioDevice for legacy API.
 *
 * The legacy SDL audio API operates on a global audio device (with ID 1).
 * Since we need a PyCSDL2_AudioDevice object to store the related Python
 * objects, we internally keep a global PyCSDL2_AudioDevice object that
 * represents the global audio device.
 */
static PyCSDL2_AudioDevice *PyCSDL2_GlobalAudioDevice;

/** @} */

/**
 * \brief Implements csdl2.SDL_GetNumAudioDrivers()
 *
 * \code{.py}
 * SDL_GetNumAudioDrivers() -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetNumAudioDrivers(PyObject *module, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    return PyLong_FromLong(SDL_GetNumAudioDrivers());
}

/**
 * \brief Implements csdl2.SDL_GetAudioDriver()
 *
 * \code{.py}
 * SDL_GetAudioDriver(index: int) -> str
 * \endcode
 */
static PyObject *
PyCSDL2_GetAudioDriver(PyObject *module, PyObject *args, PyObject *kwds)
{
    int index;
    const char *name;
    static char *kwlist[] = {"index", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &index))
        return NULL;

    name = SDL_GetAudioDriver(index);
    if (!name) {
        PyErr_SetString(PyExc_ValueError, "Index out of range");
        return NULL;
    }

    return PyUnicode_FromString(name);
}

/**
 * \brief Implements csdl2.SDL_AudioInit()
 *
 * \code{.py}
 * SDL_AudioInit(driver_name: str or None) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_AudioInit(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *driver_name;
    int ret;
    static char *kwlist[] = {"driver_name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "z", kwlist, &driver_name))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    ret = SDL_AudioInit(driver_name);
    Py_END_ALLOW_THREADS

    if (ret)
        return PyCSDL2_RaiseSDLError();

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_AudioQuit()
 *
 * \code{.py}
 * SDL_AudioQuit() -> None
 * \endcode
 */
static PyObject *
PyCSDL2_AudioQuit(PyObject *module, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    SDL_AudioQuit();
    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetCurrentAudioDriver()
 *
 * \code{.py}
 * SDL_GetCurrentAudioDriver() -> str or None
 * \endcode
 */
static PyObject *
PyCSDL2_GetCurrentAudioDriver(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *driver_name;
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    driver_name = SDL_GetCurrentAudioDriver();
    if (driver_name)
        return PyUnicode_FromString(driver_name);
    else
        Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_OpenAudio()
 *
 * \code{.py}
 * SDL_OpenAudio(desired: SDL_AudioSpec, obtained: SDL_AudioSpec or None)
 *     -> None
 * \endcode
 */
static PyObject *
PyCSDL2_OpenAudio(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_AudioSpec *desired, *obtained;
    int ret;
    static char *kwlist[] = {"desired", "obtained", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O", kwlist,
                                     &PyCSDL2_AudioSpecType, &desired,
                                     &obtained))
        return NULL;

    if ((PyObject*) obtained != Py_None &&
        Py_TYPE(obtained) != &PyCSDL2_AudioSpecType) {
        PyErr_SetString(PyExc_TypeError, "\"obtained\" must be either a "
                        "SDL_AudioSpec or None");
        return NULL;
    }

    if (!desired->callback || desired->callback == Py_None) {
        PyErr_SetString(PyExc_ValueError, "\"callback\" is None");
        return NULL;
    }

    if (PyCSDL2_GlobalAudioDevice) {
        PyErr_SetString(PyExc_RuntimeError, "Audio device is already opened");
        return NULL;
    }

    PyCSDL2_GlobalAudioDevice = (PyCSDL2_AudioDevice *)PyCSDL2_AudioDeviceCreate(0);
    if (!PyCSDL2_GlobalAudioDevice)
        return NULL;

    desired->spec.callback = PyCSDL2_AudioDeviceCallback;
    desired->spec.userdata = PyCSDL2_GlobalAudioDevice;

    PyEval_InitThreads();

    Py_INCREF(desired);
    Py_INCREF(obtained);
    Py_BEGIN_ALLOW_THREADS
    ret = SDL_OpenAudio(&desired->spec,
                        (PyObject*) obtained == Py_None ? NULL : &obtained->spec);
    Py_END_ALLOW_THREADS
    Py_DECREF(obtained);
    Py_DECREF(desired);

    if (ret) {
        Py_CLEAR(PyCSDL2_GlobalAudioDevice);
        return PyCSDL2_RaiseSDLError();
    }

    PyCSDL2_AudioDeviceAttach(PyCSDL2_GlobalAudioDevice, 1,
                              desired->callback, desired->userdata);

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_GetNumAudioDevices()
 *
 * \code{.py}
 * SDL_GetNumAudioDevices(iscapture: bool) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_GetNumAudioDevices(PyObject *module, PyObject *args, PyObject *kwds)
{
    int iscapture, ret;
    static char *kwlist[] = {"iscapture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &iscapture))
        return NULL;

    SDL_ClearError();

    Py_BEGIN_ALLOW_THREADS
    ret = SDL_GetNumAudioDevices(iscapture);
    Py_END_ALLOW_THREADS

    if (ret == -1 && *(SDL_GetError()))
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromLong(ret);
}

/**
 * \brief Implements csdl2.SDL_GetAudioDeviceName()
 *
 * \code{.py}
 * SDL_GetAudioDeviceName(index: int, iscapture: bool) -> str
 * \endcode
 */
static PyObject *
PyCSDL2_GetAudioDeviceName(PyObject *module, PyObject *args, PyObject *kwds)
{
    int index, iscapture;
    const char *device_name;
    static char *kwlist[] = {"index", "iscapture", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ip", kwlist, &index,
                                     &iscapture))
        return NULL;

    device_name = SDL_GetAudioDeviceName(index, iscapture);

    if (!device_name)
        return PyCSDL2_RaiseSDLError();

    return PyUnicode_FromString(device_name);
}

/**
 * \brief Implements csdl2.SDL_OpenAudioDevice()
 *
 * \code{.py}
 * SDL_OpenAudioDevice(device: str, iscapture: bool, desired: SDL_AudioSpec,
 *                     obtained: SDL_AudioSpec, allowed_changes: int)
 *      -> SDL_AudioDevice
 * \endcode
 */
static PyObject *
PyCSDL2_OpenAudioDevice(PyObject *module, PyObject *args, PyObject *kwds)
{
    Py_buffer device;
    int iscapture;
    SDL_AudioSpec desired;
    PyCSDL2_AudioSpec *desired_obj, *obtained;
    int allowed_changes;
    SDL_AudioDeviceID id;
    PyObject *out = NULL, *callback = NULL, *userdata = NULL;
    static char *kwlist[] = {"device", "iscapture", "desired", "obtained",
                             "allowed_changes", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "z*pO!Oi", kwlist,
                                     &device, &iscapture,
                                     &PyCSDL2_AudioSpecType, &desired_obj,
                                     &obtained, &allowed_changes))
        return NULL;

    if ((PyObject*) obtained != Py_None &&
            Py_TYPE(obtained) != &PyCSDL2_AudioSpecType) {
        PyErr_SetString(PyExc_TypeError, "\"obtained\" must be either a "
                        "SDL_AudioSpec or None");
        goto fail;
    }

    out = PyCSDL2_AudioDeviceCreate(0);
    if (!out)
        goto fail;

    desired = desired_obj->spec;

    /* If callback is NULL, install our Python bridge callback. */
    if (!desired.callback) {
        desired.callback = PyCSDL2_AudioDeviceCallback;
        desired.userdata = out;
        callback = desired_obj->callback;
        userdata = desired_obj->userdata;

        if (!callback || callback == Py_None) {
            PyErr_SetString(PyExc_ValueError, "\"callback\" is None");
            goto fail;
        }
    }

    PyEval_InitThreads();

    id = SDL_OpenAudioDevice(device.buf, iscapture, &desired,
                             (PyObject*) obtained == Py_None ? NULL : &obtained->spec,
                             allowed_changes);
    if (!id) {
        PyCSDL2_RaiseSDLError();
        goto fail;
    }

    PyCSDL2_AudioDeviceAttach((PyCSDL2_AudioDevice*)out, id, callback,
                              userdata);
    PyBuffer_Release(&device);
    return out;

fail:
    PyBuffer_Release(&device);
    Py_XDECREF(out);
    return NULL;
}

/**
 * \brief Implements csdl2.SDL_PauseAudio()
 *
 * \code{.py}
 * SDL_PauseAudio(pause_on: bool) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_PauseAudio(PyObject *module, PyObject *args, PyObject *kwds)
{
    int pause_on;
    static char *kwlist[] = {"pause_on", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &pause_on))
        return NULL;

    if (!PyCSDL2_GlobalAudioDevice) {
        PyErr_SetString(PyExc_ValueError, "Audio device not opened");
        return NULL;
    }

    if (!PyCSDL2_AudioDeviceValid(PyCSDL2_GlobalAudioDevice))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    SDL_PauseAudio(pause_on);
    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_PauseAudioDevice()
 *
 * \code{.py}
 * SDL_PauseAudioDevice(dev: SDL_AudioDevice, pause_on: bool) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_PauseAudioDevice(PyObject *module, PyObject *args, PyObject *kwds)
{
    int pause_on;
    SDL_AudioDeviceID id;
    static char *kwlist[] = {"dev", "pause_on", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&p", kwlist,
                                     PyCSDL2_AudioDeviceID, &id,
                                     &pause_on))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    SDL_PauseAudioDevice(id, pause_on);
    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_LoadWAV_RW()
 *
 * \code{.py}
 * SDL_LoadWAV_RW(src: SDL_RWops, freesrc: bool)
 *     -> (SDL_AudioSpec, SDL_WAVBuf, int)
 * \endcode
 */
static PyObject *
PyCSDL2_LoadWAV_RW(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RWops *rwops;
    int freesrc;
    SDL_AudioSpec spec;
    SDL_AudioSpec *ret;
    Uint8 *audio_buf;
    Uint32 audio_len;
    PyObject *outspec = NULL;
    PyCSDL2_WAVBuf *outbuf = NULL;
    PyObject *out = NULL;
    static char *kwlist[] = {"src", "freesrc", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!p", kwlist,
                                     &PyCSDL2_RWopsType, &rwops, &freesrc))
        return NULL;

    Py_INCREF(rwops);
    Py_BEGIN_ALLOW_THREADS
    ret = SDL_LoadWAV_RW(rwops->rwops, freesrc, &spec, &audio_buf, &audio_len);
    Py_END_ALLOW_THREADS
    Py_DECREF(rwops);

    if (!ret)
        return PyCSDL2_RaiseSDLError();

    outbuf = PyCSDL2_WAVBufCreate(audio_buf, audio_len);
    if (!outbuf)
        SDL_FreeWAV(audio_buf);

    outspec = PyCSDL2_AudioSpecCreate(&spec);

    out = Py_BuildValue("OO" Uint32_UNIT, outspec, outbuf, audio_len);

    Py_XDECREF(outspec);
    Py_XDECREF(outbuf);
    return out;
}

/**
 * \brief Implements csdl2.SDL_LoadWAV()
 *
 * \code{.py}
 * SDL_LoadWAV(file: str) -> (SDL_AudioSpec, SDL_WAVBuf, int)
 * \endcode
 */
static PyObject *
PyCSDL2_LoadWAV(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *file;
    SDL_AudioSpec spec;
    SDL_AudioSpec *ret;
    Uint8 *audio_buf;
    Uint32 audio_len;
    PyObject *outspec = NULL;
    PyCSDL2_WAVBuf *outbuf = NULL;
    PyObject *out = NULL;
    static char *kwlist[] = {"file", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &file))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    ret = SDL_LoadWAV(file, &spec, &audio_buf, &audio_len);
    Py_END_ALLOW_THREADS

    if (!ret)
        return PyCSDL2_RaiseSDLError();

    outbuf = PyCSDL2_WAVBufCreate(audio_buf, audio_len);
    if (!outbuf)
        SDL_FreeWAV(audio_buf);

    outspec = PyCSDL2_AudioSpecCreate(&spec);

    out = Py_BuildValue("OO" Uint32_UNIT, outspec, outbuf, audio_len);

    Py_XDECREF(outspec);
    Py_XDECREF(outbuf);
    return out;
}

/**
 * \brief Implements csdl2.SDL_FreeWAV()
 *
 * \code{.py}
 * SDL_FreeWAV(audio_buf: SDL_WAVBuf) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_FreeWAV(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint8 *buf;
    PyCSDL2_WAVBuf *buf_obj;
    static char *kwlist[] = {"audio_buf", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_WAVBufType, &buf_obj))
        return NULL;

    buf = PyCSDL2_WAVBufDetach(buf_obj, NULL);
    if (!buf)
        return NULL;

    SDL_FreeWAV(buf);

    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_CloseAudio()
 *
 * \code{.py}
 * SDL_CloseAudio() -> None
 * \endcode
 */
static PyObject *
PyCSDL2_CloseAudio(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_AudioDeviceID id;
    static char *kwlist[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;

    if (!PyCSDL2_GlobalAudioDevice) {
        PyErr_SetString(PyExc_ValueError, "Audio device not opened");
        return NULL;
    }

    id = PyCSDL2_AudioDeviceDetach(PyCSDL2_GlobalAudioDevice);
    if (!id)
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    SDL_CloseAudio();
    Py_END_ALLOW_THREADS

    Py_CLEAR(PyCSDL2_GlobalAudioDevice);
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_CloseAudioDevice()
 *
 * \code{.py}
 * SDL_CloseAudioDevice(dev: SDL_AudioDevice) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_CloseAudioDevice(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_AudioDevice *dev;
    SDL_AudioDeviceID id;
    static char *kwlist[] = {"dev", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_AudioDeviceType, &dev))
        return NULL;

    id = PyCSDL2_AudioDeviceDetach(dev);
    if (!id)
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    SDL_CloseAudioDevice(id);
    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

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

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_AudioSpecType) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_AudioDeviceType) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_WAVBufType)) { return 0; }

    return 1;
}

#endif /* _PYCSDL2_AUDIO_H_ */
