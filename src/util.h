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
/*!
 * \file util.h
 * \brief Shared utility functionality.
 */
#ifndef _PYCSDL2_UTIL_H_
#define _PYCSDL2_UTIL_H_
#include <Python.h>
#include <structmember.h>
#include "../include/pycsdl2.h"

#if SIZEOF_SHORT == 2 || defined(DOXYGEN)
/* A short int must be at least 16 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint16
 */
#define Sint16_UNIT "h"
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint16
 */
#define Uint16_UNIT "H"
/**
 * \brief PyMemberDef type for C signed integer type with same size as Sint16
 */
#define Sint16_TYPE T_SHORT
/**
 * \brief PyMemberDef type for C unsigned integer type with same size as Uint16
 */
#define Uint16_TYPE T_USHORT
#elif SIZEOF_INT == 2
/* An int must be at least 16 bits long */
#define Sint16_UNIT "i"
#define Uint16_UNIT "I"
#define Sint16_TYPE T_INT
#define Uint16_TYPE T_UINT
#else
#error Could not find C integer type with 2 bytes width
#endif

#if SIZEOF_SHORT == 4
/* A short int must be at least 16 bits long */
#define Sint32_UNIT "h"
#define Uint32_UNIT "H"
#define Sint32_TYPE T_SHORT
#define Uint32_TYPE T_USHORT
#elif SIZEOF_INT == 4
/* An int must be at least 16 bits long */
#define Sint32_UNIT "i"
#define Uint32_UNIT "I"
#define Sint32_TYPE T_INT
#define Uint32_TYPE T_UINT
#elif SIZEOF_LONG == 4 || defined(DOXYGEN)
/* A long int must be at least 32 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint32
 */
#define Sint32_UNIT "l"
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint32
 */
#define Uint32_UNIT "k"
/**
 * \brief PyMemberDef type for C signed integer type with same size as Sint32
 */
#define Sint32_TYPE T_LONG
/**
 * \brief PyMemberDef type for C unsigned integer type with same size as Uint32
 */
#define Uint32_TYPE T_ULONG
#else
#error Could not find C integer type with 4 bytes width
#endif

#if SIZEOF_SHORT == 8
/* A short int must be at least 16 bits long */
#define Sint64_UNIT "h"
#define Uint64_UNIT "H"
#define Sint64_TYPE T_SHORT
#define Uint64_TYPE T_USHORT
#elif SIZEOF_INT == 8
/* An int must be at least 16 bits long */
#define Sint64_UNIT "i"
#define Uint64_UNIT "I"
#define Sint64_TYPE T_INT
#define Uint64_TYPE T_UINT
#elif SIZEOF_LONG == 8
/* A long int must be at least 32 bits long */
#define Sint64_UNIT "l"
#define Uint64_UNIT "k"
#define Sint64_TYPE T_LONG
#define Uint64_TYPE T_ULONG
#elif SIZEOF_LONG_LONG == 8 || defined(DOXYGEN)
/* A long long int must be at least 64 bits long */
/**
 * \brief Python format unit for C signed integer type with same size as
 *        Sint64
 */
#define Sint64_UNIT "L"
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        Uint64
 */
#define Uint64_UNIT "K"
/**
 * \brief PyMemberDef type for C signed integer type with same size as Sint64
 */
#define Sint64_TYPE T_LONGLONG
/**
 * \brief PyMemberDef type for C unsigned integer type with same size as Uint64
 */
#define Uint64_TYPE T_ULONGLONG
#else
#error Could not find C integer type with 8 bytes width
#endif

#if SIZEOF_SHORT == SIZEOF_SIZE_T || defined(DOXYGEN)
/**
 * \brief Python format unit for C unsigned integer type with same size as
 *        size_t
 */
#define SIZE_T_UNIT "H"
#elif SIZEOF_INT == SIZEOF_SIZE_T
#define SIZE_T_UNIT "I"
#elif SIZEOF_LONG == SIZEOF_SIZE_T || defined(DOXYGEN)
#define SIZE_T_UNIT "k"
#elif SIZEOF_LONG_LONG == SIZEOF_SIZE_T
#define SIZE_T_UNIT "K"
#else
#error Could not find C integer type with size_t width
#endif

/*!
 * \brief struct for defining constants.
 *
 * This allows constants to be listed in an array and added to the module
 * with the following code:
 *
 * \code
 * static const PyCSDL2_Constant constants[] = {
 *     {"CONSTANT1", 1},
 *     {"CONSTANT2", 2},
 *     {0}
 * };
 * const PyCSDL2_Constant *c;
 * for (c = constants; c->name != NULL; ++c) {
 *     if (PyModule_AddIntConstant(module, c->name, c->value) != 0) {
 *         return 0;
 *     }
 * }
 * \endcode
 */
typedef struct {
    const char *name; /*!< name of constant */
    long value;       /*!< value of constant */
} PyCSDL2_Constant;

/**
 * \brief Asserts that condition is true.
 *
 * \returns 1 if the condition is true, 0 with an AssertionError exception set
 *          if it is false.
 */
#define PyCSDL2_Assert(condition) \
    ((condition) ? 1 : \
        (PyErr_Format(PyExc_AssertionError, "%s:%d: %s", __FILE__, __LINE__, \
                     #condition), 0))

/**
 * \brief Returns a new reference to var
 *
 * \returns var with if refcount incremented. If var is NULL, returns Py_None.
 */
static PyObject *
PyCSDL2_Get(PyObject *var)
{
    if (!var)
        Py_RETURN_NONE;
    Py_INCREF(var);
    return var;
}

/**
 * \brief Sets var to a new reference to value
 *
 * If var had a previous value, the refcount of the previous value is
 * decremented.
 */
#define PyCSDL2_Set(var, value) \
    do { \
        void *tmp = (var); \
        Py_XINCREF((PyObject*) value); \
        (var) = (value); \
        Py_XDECREF((PyObject*) tmp); \
    } while(0)

#ifndef INT32_MAX
/** \brief Maximum value a Sint32 can hold */
#define INT32_MAX 2147483647
#endif

#ifndef INT32_MIN
/** \brief Minimum value a Sint32 can hold */
#define INT32_MIN (-INT32_MAX - 1)
#endif

/**
 * \brief Returns a Sint32 representation of obj.
 *
 * \returns 0 on success, -1 with an exception set if the value of obj is out
 *          of range for a Sint32.
 */
static int
PyCSDL2_LongAsSint32(PyObject *obj, Sint32 *out)
{
#if SIZEOF_LONG >= 4
    long x = PyLong_AsLong(obj);
#elif SIZEOF_SIZE_T >= 4
    Py_ssize_t x = PyLong_AsSsize_t(obj);
#elif SIZEOF_LONG_LONG >= 4
    PY_LONG_LONG x = PyLong_AsLongLong(obj);
#endif
    if (PyErr_Occurred()) return -1;
    if (x < INT32_MIN || x > INT32_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "Python int too large to convert to Sint32");
        return -1;
    }
    *out = (Sint32) x;
    return 0;
}

#ifndef UINT32_MAX
/** \brief Maximum value a Uint32 can hold */
#define UINT32_MAX 4294967295U
#endif

/**
 * \brief Returns a Uint32 representation of obj
 *
 * \returns 0 on success, -1 with an exception set if the value of obj is out
 *          of range for a Uint32.
 */
static int
PyCSDL2_LongAsUint32(PyObject *obj, Uint32 *out)
{
#if SIZEOF_LONG >= 4
    unsigned long x = PyLong_AsUnsignedLong(obj);
#elif SIZEOF_SIZE_T >= 4
    size_t x = PyLong_AsSize_t(obj);
#elif SIZEOF_LONG_LONG >= 4
    unsigned PY_LONG_LONG x = PyLong_AsUnsignedLongLong(obj);
#endif
    if (PyErr_Occurred()) return -1;
    if (x > UINT32_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "Python int is too large to convert to Uint32");
        return -1;
    }
    *out = (Uint32) x;
    return 0;
}

#ifndef INT64_MAX
#if HAVE_LONG_LONG
#define INT64_MAX 9223372036854775807LL
#else
/** \brief Maximum value a Sint64 can hold */
#define INT64_MAX 9223372036854775807L
#endif  /* HAVE_LONG_LONG */
#endif  /* INT64_MAX */

#ifndef INT64_MIN
/** \brief Minimum value a Sint64 can hold */
#define INT64_MIN (-INT64_MAX - 1)
#endif

/**
 * \brief Returns a Sint64 representation of obj
 *
 * \returns 0 on success, -1 with an exception set on failure.
 */
static int
PyCSDL2_LongAsSint64(PyObject *obj, Sint64 *out)
{
#if SIZEOF_LONG >= 8
    long x = PyLong_AsLong(obj);
#elif SIZEOF_SIZE_T >= 8
    Py_ssize_t x = PyLong_AsSsize_t(obj);
#elif SIZEOF_LONG_LONG >= 8
    PY_LONG_LONG x = PyLong_AsLongLong(obj);
#endif

    if (PyErr_Occurred())
        return -1;

    if (x < INT64_MIN || x > INT64_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "Python int too large to convert to Sint64");
        return -1;
    }

    *out = (Sint64) x;
    return 0;
}

/**
 * \brief Set "invalid type" exception.
 *
 * \param arg Argument Name (if any)
 * \param expected Expected type name
 * \param actual Actual object
 * \returns NULL
 */
static void *
PyCSDL2_RaiseTypeError(const char *arg, const char *expected, PyObject *actual)
{
    return PyErr_Format(PyExc_TypeError, "%.50s%smust be %.50s, not %.50s",
                        arg ? arg : "", arg ? ": " : "", expected,
                        actual == Py_None ? "None" : Py_TYPE(actual)->tp_name);
}

/**
 * \brief Base instance struct members for PyCSDL2_Buffer-based types
 *
 * This macro will insert the required field members required for a type to use
 * the PyCSDL2_Buffer* utility functions and protocols.
 *
 * The PyCSDL2_Buffer* functions and protocols are useful for exposing a bytes
 * buffer that is managed by ther SDL library.
 */
#define PyCSDL2_BufferHEAD \
    PyObject_HEAD \
    unsigned char *buf; \
    Py_ssize_t len; \
    char readonly; \
    int num_exports;

/**
 * \brief Represents the data of PyCSDL2_Buffer-based types
 */
typedef struct PyCSDL2_Buffer {
    PyCSDL2_BufferHEAD
} PyCSDL2_Buffer;

/**
 * \brief Validates the PyCSDL2_Buffer object.
 *
 * A PyCSDL2_Buffer is valid if its internal buf pointer is not NULL. If it is,
 * raise a ValueError.
 *
 * \param buffer PyCSDL2_Buffer to validate.
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_BufferValid(PyCSDL2_Buffer *buffer)
{
    if (!PyCSDL2_Assert(buffer))
        return 0;

    if (!buffer->buf) {
        PyErr_SetString(PyExc_ValueError, "buffer has been released");
        return 0;
    }

    return 1;
}

/**
 * \brief bf_getbuffer for PyCSDL2_Buffer-based types
 */
static int
PyCSDL2_BufferGetBuffer(PyCSDL2_Buffer *self, Py_buffer *view, int flags)
{
    if (!PyCSDL2_BufferValid(self))
        return -1;

    if (PyBuffer_FillInfo(view, (PyObject*) self, self->buf, self->len,
                          self->readonly, flags))
        return -1;

    self->num_exports++;

    return 0;
}

/**
 * \brief bf_releasebuffer for PyCSDL2_Buffer-based types
 */
static void
PyCSDL2_BufferReleaseBuffer(PyCSDL2_Buffer *self, Py_buffer *view)
{
    self->num_exports--;
}

/**
 * \brief tp_as_buffer for PyCSDL2_Buffer-based types
 */
static PyBufferProcs PyCSDL2_BufferAsBuffer = {
    /* bf_getbuffer     */ (getbufferproc) PyCSDL2_BufferGetBuffer,
    /* bf_releasebuffer */ (releasebufferproc) PyCSDL2_BufferReleaseBuffer
};

/**
 * \brief sq_length, mp_length for PyCSDL2_Buffer-based types
 */
static Py_ssize_t
PyCSDL2_BufferLength(PyCSDL2_Buffer *self)
{
    if (!PyCSDL2_BufferValid(self))
        return -1;

    return self->len;
}

/**
 * \brief sq_item for PyCSDL2_Buffer-based types
 */
static PyObject *
PyCSDL2_BufferGetItem(PyCSDL2_Buffer *self, Py_ssize_t index)
{
    if (!PyCSDL2_BufferValid(self))
        return NULL;

    if (index < 0 || index >= self->len) {
        PyErr_SetString(PyExc_IndexError, "index out of bounds");
        return NULL;
    }

    return PyLong_FromUnsignedLong(self->buf[index]);
}

/**
 * \brief tp_as_sequence for PyCSDL2_Buffer-based types
 */
static PySequenceMethods PyCSDL2_BufferAsSequence = {
    /* sq_length         */ (lenfunc) PyCSDL2_BufferLength,
    /* sq_concat         */ (binaryfunc) NULL,
    /* sq_repeat         */ (ssizeargfunc) NULL,
    /* sq_item           */ (ssizeargfunc) PyCSDL2_BufferGetItem
};

/**
 * \brief mp_subscript for PyCSDL2_Buffer-based types
 */
static PyObject *
PyCSDL2_BufferSubscript(PyCSDL2_Buffer *self, PyObject *key)
{
    if (!PyCSDL2_BufferValid(self))
        return NULL;

    if (PyIndex_Check(key)) {
        Py_ssize_t index;

        index = PyNumber_AsSsize_t(key, PyExc_IndexError);
        if (index == -1 && PyErr_Occurred())
            return NULL;

        return PyCSDL2_BufferGetItem(self, index);
    } else if (PySlice_Check(key)) {
        PyObject *memview, *out;

        memview = PyMemoryView_FromObject((PyObject*) self);
        if (!memview)
            return NULL;

        out = PyObject_GetItem(memview, key);
        if (!out) {
            Py_DECREF(memview);
            return NULL;
        }

        Py_DECREF(memview);
        return out;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid slice key");
        return NULL;
    }
}

/**
 * \brief mp_ass_subscript for PyCSDL2_Buffer-based types
 */
static int
PyCSDL2_BufferSetItem(PyCSDL2_Buffer *self, PyObject *key, PyObject *value)
{
    if (!PyCSDL2_BufferValid(self))
        return -1;

    if (self->readonly) {
        PyErr_SetString(PyExc_TypeError, "cannot modify read-only memory");
        return -1;
    }

    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "cannot delete memory");
        return -1;
    }

    if (PyIndex_Check(key)) {
        unsigned long x;
        Py_ssize_t index;

        index = PyNumber_AsSsize_t(key, PyExc_IndexError);
        if (index == -1 && PyErr_Occurred())
            return -1;

        if (index < 0)
            index = self->len + index;

        if (index < 0 || index >= self->len) {
            PyErr_SetString(PyExc_IndexError, "index out of bounds");
            return -1;
        }

        x = PyLong_AsUnsignedLong(value);
        if (PyErr_Occurred())
            return -1;

        if (x > (unsigned char)-1) {
            PyErr_SetString(PyExc_OverflowError, "value overflows byte");
            return -1;
        }

        self->buf[index] = x;

        return 0;
    } else {
        PyObject *memview;
        int ret;

        memview = PyMemoryView_FromObject((PyObject*) self);
        if (!memview)
            return -1;

        ret = PyObject_SetItem(memview, key, value);
        Py_DECREF(memview);
        return ret;
    }
}

/**
 * \brief tp_as_mapping for PyCSDL2_Buffer-based types.
 */
static PyMappingMethods PyCSDL2_BufferAsMapping = {
    /* mp_length        */ (lenfunc) PyCSDL2_BufferLength,
    /* mp_subscript     */ (binaryfunc) PyCSDL2_BufferSubscript,
    /* mp_ass_subscript */ (objobjargproc) PyCSDL2_BufferSetItem
};

/** \brief Type definition for csdl2.SDL_SurfacePixels */
static PyTypeObject PyCSDL2_BufferType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Buffer",
    /* tp_basicsize      */ sizeof(PyCSDL2_Buffer),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ 0,
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
    /* tp_as_buffer      */ &PyCSDL2_BufferAsBuffer,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */ "Temporary buffer"
};

/**
 * \brief Initializes the PyCSDL2_BufferHEAD members.
 *
 * All PyCSDL2_Buffer-based types need to call this during initialization.
 */
static void
PyCSDL2_BufferInit(PyCSDL2_Buffer *self, void *buf, Py_ssize_t len,
                   char readonly)
{
    PyCSDL2_Buffer *bufself = self;

    bufself->buf = buf;
    bufself->len = len;
    bufself->readonly = readonly;
}

/**
 * \brief Creates an instance of PyCSDL2_BufferType
 */
static PyCSDL2_Buffer *
PyCSDL2_BufferCreate(void *buf, Py_ssize_t len, char readonly)
{
    PyCSDL2_Buffer *self;
    PyTypeObject *type = &PyCSDL2_BufferType;

    self = (PyCSDL2_Buffer*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    PyCSDL2_BufferInit(self, buf, len, readonly);

    return self;
}

/**
 * \defgroup csdl2_PyCSDL2_VoidPtr csdl2.PyCSDL2_VoidPtr
 *
 * A generic object that holds a void pointer. This is mainly used to represent
 * a foreign pointer which has an unknown type and is not managed by csdl2.
 *
 * @{
 */

/** \brief Instance data for PyCSDL2_VoidPtrType */
typedef struct PyCSDL2_VoidPtr {
    PyObject_HEAD
    /** \brief Head of weakref list */
    PyObject *in_weakreflist;
    /** \brief Internal void* pointer */
    void *ptr;
} PyCSDL2_VoidPtr;

static PyTypeObject PyCSDL2_VoidPtrType;

/** \brief Destructor for PyCSDL2_VoidPtrType */
static void
PyCSDL2_VoidPtrDealloc(PyCSDL2_VoidPtr *self)
{
    PyObject_ClearWeakRefs((PyObject*)self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/** \brief Type definition of csdl2.PyCSDL2_VoidPtr */
static PyTypeObject PyCSDL2_VoidPtrType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.PyCSDL2_VoidPtr",
    /* tp_basicsize      */ sizeof(PyCSDL2_VoidPtr),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_VoidPtrDealloc,
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
    /* tp_doc            */ "A foreign pointer of unknown type.",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_VoidPtr, in_weakreflist)
};

/**
 * \brief Creates a new PyCSDL2_VoidPtr instance.
 *
 * \param ptr The pointer to wrap.
 * \returns The new PyCSDL2_VoidPtr object on success, NULL if an exception
 *          occurred.
 */
static PyObject *
PyCSDL2_VoidPtrCreate(void *ptr)
{
    PyCSDL2_VoidPtr *self;
    PyTypeObject *type = &PyCSDL2_VoidPtrType;

    self = (PyCSDL2_VoidPtr*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->ptr = ptr;

    return (PyObject*)self;
}

/**
 * \brief Checks the pointer value of the PyCSDL2_VoidPtr.
 *
 * \param obj PyObject to check
 * \param ptr Pointer value which the PyCSDL2_VoidPtr must have.
 * \returns 1 if the PyObject is a PyCSDL2_VoidPtr and has the pointer value of
 *          ptr, 0 otherwise.
 */
static int
PyCSDL2_VoidPtrCheckPtr(PyObject *obj, void *ptr)
{
    if (!obj)
        return 0;

    if (Py_TYPE(obj) != &PyCSDL2_VoidPtrType)
        return 0;

    if (((PyCSDL2_VoidPtr*)obj)->ptr != ptr)
        return 0;

    return 1;
}

/** @} */

/**
 * \brief Initializes csdl2's utility types
 *
 * \param module csdl2 module object
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initutil(PyObject *module)
{
    if (PyType_Ready(&PyCSDL2_BufferType)) { return 0; }
    if (PyType_Ready(&PyCSDL2_VoidPtrType)) { return 0; }

    return 1;
}

#endif /* _PYCSDL2_UTIL_H_ */
