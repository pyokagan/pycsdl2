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
 * \file rwops.h
 * \brief Bindings for SDL_rwops.h
 *
 * Implements bindings for SDL's File IO API (SDL_rwops.h)
 */
#ifndef _PYCSDL2_RWOPS_H_
#define _PYCSDL2_RWOPS_H_
#include <Python.h>
#include <SDL_rwops.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief SDL_RWops size callback pointer */
typedef Sint64 (SDLCALL *rwsizefunc)(SDL_RWops*);

/** \brief SDL_RWops seek callback pointer */
typedef Sint64 (SDLCALL *rwseekfunc)(SDL_RWops*, Sint64, int);

/** \brief SDL_RWops read callback pointer */
typedef size_t (SDLCALL *rwreadfunc)(SDL_RWops*, void*, size_t, size_t);

/** \brief SDL_RWops write callback pointer */
typedef size_t (SDLCALL *rwwritefunc)(SDL_RWops*, const void*, size_t, size_t);

/** \brief SDL_RWops close callback pointer */
typedef int (SDLCALL *rwclosefunc)(SDL_RWops*);

/** \brief Instance data for PyCSDL2_RWopsType */
typedef struct PyCSDL2_RWops {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief SDL_RWops pointer that this instance owns */
    SDL_RWops *rwops;
} PyCSDL2_RWops;

static PyTypeObject PyCSDL2_RWopsType;

/**
 * \brief Validates the PyCSDL2_RWops object
 *
 * A PyCSDL2_RWops object is valid if self->rwops is not NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_RWopsValid(PyCSDL2_RWops *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!self->rwops) {
        PyErr_SetString(PyExc_ValueError, "SDL_RWops has been freed");
        return 0;
    }

    return 1;
}

/** \brief Instance data for PyCSDL2_RWSizeFuncType */
typedef struct PyCSDL2_RWSizeFunc {
    PyObject_HEAD
    /** \brief SDL_RWops size callback */
    rwsizefunc func;
} PyCSDL2_RWSizeFunc;

static PyTypeObject PyCSDL2_RWSizeFuncType;

/**
 * \brief Implements SDL_RWsize() and __call__() for PyCSDL2_RWSizeFuncType
 *
 * \code{.py}
 * SDL_RWsize(context: SDL_RWops) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_RWsize(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    Sint64 ret;
    SDL_RWops *rwops;
    rwsizefunc callback;
    static char *kwlist[] = {"context", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj))
        return NULL;

    if (!PyCSDL2_RWopsValid(rwops_obj))
        return NULL;

    rwops = rwops_obj->rwops;

    if (Py_TYPE(self) == &PyCSDL2_RWSizeFuncType)
        callback = ((PyCSDL2_RWSizeFunc*)self)->func;
    else
        callback = rwops->size;

    if (!callback) {
        PyErr_SetString(PyExc_ValueError,
                        "SDL_RWops object has no size callback");
        return NULL;
    }

    /*
     * To prevent segfaults due to invalid SDL_RWops internal data, do not
     * allow mixing of SDL_RWops and callbacks by checking to see if the
     * SDL_RWops has the same callback as the one we have.
     */
    if (callback != rwops->size) {
        PyErr_SetString(PyExc_ValueError, "Do not mix different "
                        "SDL_RWops and callbacks.");
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    ret = callback(rwops);
    Py_END_ALLOW_THREADS

    if (ret < 0)
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromLongLong(ret);
}

/**
 * \brief Type definition for csdl2.RWSizeFunc
 */
static PyTypeObject PyCSDL2_RWSizeFuncType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.RWSizeFunc",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWSizeFunc),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ PyCSDL2_RWsize
};

/** \brief Creates instance of PyCSDL2_RWSizeFuncType */
static PyCSDL2_RWSizeFunc *
PyCSDL2_RWSizeFuncCreate(rwsizefunc sizefunc)
{
    PyCSDL2_RWSizeFunc *self;
    PyTypeObject *type = &PyCSDL2_RWSizeFuncType;

    if (!PyCSDL2_Assert(sizefunc))
        return NULL;

    if (!(self = (PyCSDL2_RWSizeFunc*)type->tp_alloc(type, 0)))
        return NULL;
    self->func = sizefunc;
    return self;
}

/** \brief Instance data for PyCSDL2_RWSeekFuncType */
typedef struct PyCSDL2_RWSeekFunc {
    PyObject_HEAD
    /** \brief SDL_RWops seek callback */
    rwseekfunc func;
} PyCSDL2_RWSeekFunc;

static PyTypeObject PyCSDL2_RWSeekFuncType;

/**
 * \brief Implements SDL_RWseek() and __call__() for PyCSDL2_RWSeekFuncType
 *
 * \code{.py}
 * SDL_RWseek(context: SDL_RWops, offset: int, whence: int) -> int
 * \endcode
 */
static PyObject *
PyCSDL2_RWseek(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    Sint64 offset, ret;
    int whence;
    SDL_RWops *rwops;
    rwseekfunc callback;
    static char *kwlist[] = {"context", "offset", "whence", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!" Sint64_UNIT "i", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj, &offset,
                                     &whence))
        return NULL;

    if (!PyCSDL2_RWopsValid(rwops_obj))
        return NULL;

    rwops = rwops_obj->rwops;

    if (Py_TYPE(self) == &PyCSDL2_RWSeekFuncType)
        callback = ((PyCSDL2_RWSeekFunc*)self)->func;
    else
        callback = rwops->seek;

    if (!callback) {
        PyErr_SetString(PyExc_ValueError,
                        "SDL_RWops object has no seek callback");
        return NULL;
    }

    /*
     * To prevent segfaults due to invalid SDL_RWops internal data, do not
     * allow mixing of SDL_RWops and callbacks by checking to see if the
     * SDL_RWops has the same callback as the one we have.
     */
    if (callback != rwops->seek) {
        PyErr_SetString(PyExc_ValueError, "Do not mix different "
                        "SDL_RWops and callbacks.");
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    ret = callback(rwops, offset, whence);
    Py_END_ALLOW_THREADS

    if (ret < 0)
        return PyCSDL2_RaiseSDLError();

    return PyLong_FromLongLong(ret);
}

/** \brief Type definition of csdl2.RWSeekFunc */
static PyTypeObject PyCSDL2_RWSeekFuncType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.RWSeekFunc",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWSeekFunc),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ PyCSDL2_RWseek
};

/** \brief Creates an instance of PyCSDL2_RWSeekFuncType */
static PyCSDL2_RWSeekFunc *
PyCSDL2_RWSeekFuncCreate(rwseekfunc seekfunc)
{
    PyCSDL2_RWSeekFunc *self;
    PyTypeObject *type = &PyCSDL2_RWSeekFuncType;

    if (!PyCSDL2_Assert(seekfunc))
        return NULL;

    if (!(self = (PyCSDL2_RWSeekFunc*)type->tp_alloc(type, 0)))
        return NULL;
    self->func = seekfunc;
    return self;
}

/** \brief Instance data for PyCSDL2_RWReadFuncType */
typedef struct PyCSDL2_RWReadFunc {
    PyObject_HEAD
    /** \brief SDL_RWops read callback */
    rwreadfunc func;
} PyCSDL2_RWReadFunc;

/** \brief Implements __call__() for PyCSDL2_RWReadFuncType */
static PyObject *
PyCSDL2_RWReadFuncCall(PyCSDL2_RWReadFunc *self, PyObject *args,
                       PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    size_t ret;
    Py_buffer buf;
    Py_ssize_t size, maxnum;
    static char *kwlist[] = {"context", "ptr", "size", "maxnum", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!w*nn", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj,
                                     &buf, &size, &maxnum))
        return NULL;
    if (buf.len != size * maxnum) {
        PyBuffer_Release(&buf);
        return PyErr_Format(PyExc_BufferError, "Invalid buffer size");
    }

    if (!PyCSDL2_RWopsValid(rwops_obj)) {
        PyBuffer_Release(&buf);
        return NULL;
    }

    /*
     * To prevent segfaults due to invalid SDL_RWops internal data, do not
     * allow mixing of SDL_RWops and callbacks by checking to see if the
     * SDL_RWops has the same callback as the one we have.
     */
    if (self->func != rwops_obj->rwops->read) {
        PyBuffer_Release(&buf);
        PyErr_SetString(PyExc_ValueError, "Do not mix different "
                        "SDL_RWops and callbacks.");
        return NULL;
    }

    ret = self->func(rwops_obj->rwops, buf.buf, size, maxnum);
    PyBuffer_Release(&buf);
    if (PyErr_Occurred())
        return NULL;
    return PyLong_FromUnsignedLong(ret);
}

/** \brief Type definition for csdl2.RWReadFunc */
static PyTypeObject PyCSDL2_RWReadFuncType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.RWReadFunc",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWReadFunc),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ (ternaryfunc) PyCSDL2_RWReadFuncCall
};

/** \brief Creates a new instance of PyCSDL2_RWReadFuncType */
static PyCSDL2_RWReadFunc *
PyCSDL2_RWReadFuncCreate(rwreadfunc readfunc)
{
    PyCSDL2_RWReadFunc *self;
    PyTypeObject *type = &PyCSDL2_RWReadFuncType;

    if (!PyCSDL2_Assert(readfunc))
        return NULL;

    if (!(self = (PyCSDL2_RWReadFunc*)type->tp_alloc(type, 0)))
        return NULL;
    self->func = readfunc;
    return self;
}

/** \brief Instance data for PyCSDL2_RWWriteFuncType */
typedef struct PyCSDL2_RWWriteFunc {
    PyObject_HEAD
    /** \brief SDL_RWops write callback */
    rwwritefunc func;
} PyCSDL2_RWWriteFunc;

/** \brief Implements __call__() for PyCSDL2_RWWriteFuncType */
static PyObject *
PyCSDL2_RWWriteFuncCall(PyCSDL2_RWWriteFunc *self, PyObject *args,
                        PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    Py_buffer buf;
    size_t ret;
    Py_ssize_t size, num;
    static char *kwlist[] = {"context", "ptr", "size", "num", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!y*nn", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj,
                                     &buf, &size, &num))
        return NULL;
    if (buf.len != size * num) {
        PyBuffer_Release(&buf);
        return PyErr_Format(PyExc_BufferError, "Invalid buffer size");
    }

    if (!PyCSDL2_RWopsValid(rwops_obj)) {
        PyBuffer_Release(&buf);
        return NULL;
    }

    /*
     * To prevent segfaults due to invalid SDL_RWops internal data, do not
     * allow mixing of SDL_RWops and callbacks by checking to see if the
     * SDL_RWops has the same callback as the one we have.
     */
    if (self->func != rwops_obj->rwops->write) {
        PyBuffer_Release(&buf);
        PyErr_SetString(PyExc_ValueError, "Do not mix different "
                        "SDL_RWops and callbacks.");
        return NULL;
    }

    ret = self->func(rwops_obj->rwops, buf.buf, size, num);
    PyBuffer_Release(&buf);
    if (PyErr_Occurred())
        return NULL;
    return PyLong_FromUnsignedLong(ret);
}

/** \brief Type definition for csdl2.RWWriteFunc */
static PyTypeObject PyCSDL2_RWWriteFuncType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.RWWriteFunc",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWWriteFunc),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ (ternaryfunc) PyCSDL2_RWWriteFuncCall
};

/** \brief Creates a new instance of PyCSDL2_RWWriteFuncType */
static PyCSDL2_RWWriteFunc *
PyCSDL2_RWWriteFuncCreate(rwwritefunc writefunc)
{
    PyCSDL2_RWWriteFunc *self;
    PyTypeObject *type = &PyCSDL2_RWWriteFuncType;

    if (!PyCSDL2_Assert(writefunc))
        return NULL;

    if (!(self = (PyCSDL2_RWWriteFunc*)type->tp_alloc(type, 0)))
        return NULL;
    self->func = writefunc;
    return self;
}

/** \brief Instance data for PyCSDL2_RWCloseFuncType */
typedef struct PyCSDL2_RWCloseFunc {
    PyObject_HEAD
    /** \brief SDL_RWops close callback */
    rwclosefunc func;
} PyCSDL2_RWCloseFunc;

/** \brief Implements __call__() for PyCSDL2_RWCloseFuncType */
static PyObject *
PyCSDL2_RWCloseFuncCall(PyCSDL2_RWCloseFunc *self, PyObject *args,
                        PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    int ret;
    static char *kwlist[] = {"context", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj))
        return NULL;

    if (!PyCSDL2_RWopsValid(rwops_obj))
        return NULL;

    /*
     * To prevent segfaults due to invalid SDL_RWops internal data, do not
     * allow mixing of SDL_RWops and callbacks by checking to see if the
     * SDL_RWops has the same callback as the one we have.
     */
    if (self->func != rwops_obj->rwops->close) {
        PyErr_SetString(PyExc_ValueError, "Do not mix different "
                        "SDL_RWops and callbacks.");
        return NULL;
    }

    ret = self->func(rwops_obj->rwops);
    /* We expect out SDL_RWops to be freed, so invalidate the rwops pointer */
    rwops_obj->rwops = NULL;
    if (ret < 0)
        return PyCSDL2_RaiseSDLError();
    Py_RETURN_NONE;
}

/** \brief Type definition for csdl2.RWCloseFunc */
static PyTypeObject PyCSDL2_RWCloseFuncType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.RWCloseFunc",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWCloseFunc),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
    /* tp_print          */ 0,
    /* tp_getattr        */ 0,
    /* tp_setattr        */ 0,
    /* tp_reserved       */ 0,
    /* tp_repr           */ 0,
    /* tp_as_number      */ 0,
    /* tp_as_sequence    */ 0,
    /* tp_as_mapping     */ 0,
    /* tp_hash           */ 0,
    /* tp_call           */ (ternaryfunc) PyCSDL2_RWCloseFuncCall
};

/** \brief Creates instance of PyCSDL2_RWCloseFuncType */
static PyCSDL2_RWCloseFunc *
PyCSDL2_RWCloseFuncCreate(rwclosefunc closefunc)
{
    PyCSDL2_RWCloseFunc *self;
    PyTypeObject *type = &PyCSDL2_RWCloseFuncType;

    if (!PyCSDL2_Assert(closefunc))
        return NULL;

    if (!(self = (PyCSDL2_RWCloseFunc*) type->tp_alloc(type, 0)))
        return NULL;
    self->func = closefunc;
    return self;
}

/** \brief tp_finalize for PyCSDL2_RWopsType */
static void
PyCSDL2_RWopsFinalize(PyCSDL2_RWops *self)
{
    PyObject *error_type, *error_value, *error_traceback;

    if (!self->rwops)
        return;

    PyErr_Fetch(&error_type, &error_value, &error_traceback);

    if (self->rwops->close)
        self->rwops->close(self->rwops);
    else
        SDL_FreeRW(self->rwops);

    self->rwops = NULL;

    PyErr_Restore(error_type, error_value, error_traceback);
}

/** \brief Destructor for PYCSDL2_RWopsType */
static void
PyCSDL2_RWopsDealloc(PyCSDL2_RWops *self)
{
    if (PyObject_CallFinalizerFromDealloc((PyObject*) self) < 0)
        return;
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Implements getter for SDL_RWops.type */
static PyObject *
PyCSDL2_RWopsGetType(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->rwops->type);
}

/** \brief Implements setter for SDL_RWops.type */
static int
PyCSDL2_RWopsSetType(PyCSDL2_RWops *self, PyObject *value, void *closure)
{
    unsigned long val;

    if (!PyCSDL2_RWopsValid(self))
        return -1;

    val = PyLong_AsUnsignedLong(value);
    if (PyErr_Occurred())
        return -1;

    self->rwops->type = val;

    return 0;
}

/** \brief Implements getter for SDL_RWops.size */
static PyObject *
PyCSDL2_RWopsGetSize(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;

    if (!self->rwops->size)
        Py_RETURN_NONE;

    return (PyObject*) PyCSDL2_RWSizeFuncCreate(self->rwops->size);
}

/** \brief Implements getter for SDL_RWops.seek */
static PyObject *
PyCSDL2_RWopsGetSeek(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;

    if (!self->rwops->seek)
        Py_RETURN_NONE;

    return (PyObject*) PyCSDL2_RWSeekFuncCreate(self->rwops->seek);
}

/** \brief Implements getter for SDL_RWops.read */
static PyObject *
PyCSDL2_RWopsGetRead(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;

    if (!self->rwops->read)
        Py_RETURN_NONE;

    return (PyObject*) PyCSDL2_RWReadFuncCreate(self->rwops->read);
}

/** \brief Implements getter for SDL_RWops.write */
static PyObject *
PyCSDL2_RWopsGetWrite(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;

    if (!self->rwops->write)
        Py_RETURN_NONE;

    return (PyObject*) PyCSDL2_RWWriteFuncCreate(self->rwops->write);
}

/** \brief Implements getter for SDL_RWops.close*/
static PyObject *
PyCSDL2_RWopsGetClose(PyCSDL2_RWops *self, void *closure)
{
    if (!PyCSDL2_RWopsValid(self))
        return NULL;

    if (!self->rwops->close)
        Py_RETURN_NONE;

    return (PyObject*) PyCSDL2_RWCloseFuncCreate(self->rwops->close);
}

/** \brief List of properties for PyCSDL2_RWopsType */
static PyGetSetDef PyCSDL2_RWopsGetSetters[] = {
    {"type",
     (getter) PyCSDL2_RWopsGetType,
     (setter) PyCSDL2_RWopsSetType,
     "Type of stream.",
     NULL},
    {"size",
     (getter) PyCSDL2_RWopsGetSize,
     (setter) NULL,
     "Callback that reports stream size. It has the signature:\n"
     "\n"
     "size(context: SDL_RWops) -> int\n",
     NULL},
    {"seek",
     (getter) PyCSDL2_RWopsGetSeek,
     (setter) NULL,
     "Callback that seeks in stream. It has the signature:\n"
     "\n"
     "seek(context: SDL_RWops, offset: int, whence: int) -> int\n",
     NULL},
    {"read",
     (getter) PyCSDL2_RWopsGetRead,
     (setter) NULL,
     "Callback that reads from the stream. It has the signature:\n"
     "\n"
     "read(context: SDL_RWops, ptr: buffer, size: int, maxnum: int) -> int\n",
     NULL},
    {"write",
     (getter) PyCSDL2_RWopsGetWrite,
     (setter) NULL,
     "Callback that writes to the stream. It has the signature:\n"
     "\n"
     "write(context: SDL_RWops, ptr: buffer, size: int, maxnum: int) -> int\n",
     NULL},
    {"close",
     (getter) PyCSDL2_RWopsGetClose,
     (setter) NULL,
     "Callback that closes the stream and deallocates the SDL_RWops. It has\n"
     "signature:\n"
     "\n"
     "close(context: SDL_RWops) -> None\n",
     NULL},
    {NULL}
};

/**
 * \brief Type definition for csdl2.SDL_RWops
 */
static PyTypeObject PyCSDL2_RWopsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_RWops",
    /* tp_basicsize      */ sizeof(PyCSDL2_RWops),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_RWopsDealloc,
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
    /* tp_flags          */ Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    /* tp_doc            */
    "SDL_RWops",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_RWops, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_RWopsGetSetters,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ 0,
    /* tp_alloc          */ 0,
    /* tp_new            */ 0,
    /* tp_free           */ 0,
    /* tp_is_gc          */ 0,
    /* tp_bases          */ 0,
    /* tp_mro            */ 0,
    /* tp_cache          */ 0,
    /* tp_subclasses     */ 0,
    /* tp_weaklist       */ 0,
    /* tp_del            */ 0,
    /* tp_version_tag    */ 0,
    /* tp_finalize       */ (destructor) PyCSDL2_RWopsFinalize
};

/**
 * \brief Creates a new instance of PyCSDL2_RWopsType
 */
static PyCSDL2_RWops *
PyCSDL2_RWopsCreate(SDL_RWops *rwops)
{
    PyCSDL2_RWops *self;
    PyTypeObject *type = &PyCSDL2_RWopsType;

    self = (PyCSDL2_RWops*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->rwops = rwops;

    return self;
}

/**
 * \brief Implements csdl2.SDL_RWFromFile()
 *
 * \code
 * SDL_RWFromFile(file: str, mode: str) -> SDL_RWops
 * \endcode
 */
static PyCSDL2_RWops *
PyCSDL2_RWFromFile(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *file, *mode;
    SDL_RWops *ret;
    static char *kwlist[] = {"file", "mode", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist,
                                     &file, &mode))
        return NULL;
    if (!(ret = SDL_RWFromFile(file, mode)))
        return PyCSDL2_RaiseSDLError();
    return PyCSDL2_RWopsCreate(ret);
}

/**
 * \brief Implements csdl2.SDL_AllocRW()
 *
 * \code
 * SDL_AllocRW() -> SDL_RWops
 * \endcode
 */
static PyCSDL2_RWops *
PyCSDL2_AllocRW(PyObject *module, PyObject *args, PyObject *kwds)
{
    SDL_RWops *ret;
    static char *kwlist[] = {NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;
    if (!(ret = SDL_AllocRW()))
        return PyCSDL2_RaiseSDLError();
    /*
     * PyCSDL2_RWopsPtr calls SDL_RWops.close if it is not NULL on destruction.
     * However, SDL_AllocRW() does not zero SDL_RWops on allocation, and thus
     * PyCSDL2_RWopsPtr will call an invalid pointer on destructor and cause a
     * segfault. Fix this by zeroing SDL_RWops.
     */
    memset(ret, 0, sizeof(SDL_RWops));
    return PyCSDL2_RWopsCreate(ret);
}

/**
 * \brief Implements csdl2.SDL_FreeRW()
 *
 * \code
 * SDL_FreeRW(area: SDL_RWops) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_FreeRW(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_RWops *rwops_obj;
    static char *kwlist[] = {"area", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_RWopsType, &rwops_obj))
        return NULL;

    if (!PyCSDL2_RWopsValid(rwops_obj))
        return NULL;

    SDL_FreeRW(rwops_obj->rwops);
    rwops_obj->rwops = NULL;

    Py_RETURN_NONE;
}

/**
 * \brief Initializes bindings to SDL_rwops.h
 *
 * Adds constants defined in SDL_rwops.h to module.
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initrwops(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_RWOPS_UNKNOWN", SDL_RWOPS_UNKNOWN},
        {"SDL_RWOPS_WINFILE", SDL_RWOPS_WINFILE},
        {"SDL_RWOPS_STDFILE", SDL_RWOPS_STDFILE},
        {"SDL_RWOPS_JNIFILE", SDL_RWOPS_JNIFILE},
        {"SDL_RWOPS_MEMORY", SDL_RWOPS_MEMORY},
        {"SDL_RWOPS_MEMORY_RO", SDL_RWOPS_MEMORY_RO},

        {"RW_SEEK_SET", RW_SEEK_SET},
        {"RW_SEEK_CUR", RW_SEEK_CUR},
        {"RW_SEEK_END", RW_SEEK_END},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_RWSizeFuncType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_RWSeekFuncType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_RWReadFuncType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_RWWriteFuncType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_RWCloseFuncType)) { return 0; }

    if (PyType_Ready(&PyCSDL2_RWopsType)) { return 0; }
    Py_INCREF(&PyCSDL2_RWopsType);
    if (PyModule_AddObject(module, "SDL_RWops", (PyObject*)&PyCSDL2_RWopsType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_RWOPS_H_ */
