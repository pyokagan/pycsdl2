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

#ifndef INT16_MAX
/** \brief Maximum value a Sint16 can hold */
#define INT16_MAX (32767)
#endif

#ifndef INT16_MIN
/** \brief Minimum value a Sint16 can hold */
#define INT16_MIN (-32767 - 1)
#endif

#ifndef UINT16_MAX
/** \brief Maximum value a Uint16 can hold */
#define UINT16_MAX (65535U)
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
 * if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
 *     return 0;
 * \endcode
 */
typedef struct {
    const char *name; /*!< name of constant */
    long value;       /*!< value of constant */
} PyCSDL2_Constant;

/**
 * \brief Adds an array of constants to the module.
 *
 * \returns 0 on success, -1 if an exception occurred.
 */
static int
PyCSDL2_PyModuleAddConstants(PyObject *module,
                             const PyCSDL2_Constant *constants)
{
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value) < 0)
            return -1;

    return 0;
}

/**
 * \brief Adds a type object to a module.
 *
 * \returns 0 on success, -1 if an exception occurred.
 */
static int
PyCSDL2_PyModuleAddType(PyObject *module, PyTypeObject *type)
{
    const char *name;

    if (PyType_Ready(type) < 0)
        return -1;

    Py_INCREF(type);

    name = strchr(type->tp_name, '.');
    if (name)
        name += 1;
    else
        name = type->tp_name;

    if (PyModule_AddObject(module, name, (PyObject *)type) < 0)
        return -1;

    return 0;
}

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

/**
 * \brief Returns a int representation of obj.
 *
 * \returns 0 on success, -1 if an exception occurred.
 */
static int
PyCSDL2_LongAsInt(PyObject *obj, int *out)
{
    long x = PyLong_AsLong(obj);
    if (PyErr_Occurred())
        return -1;
    if (x < INT_MIN || x > INT_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "Python int too large to convert to C int");
        return -1;
    }
    *out = (int)x;
    return 0;
}

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
 * \defgroup ctype C Type Generic utility functions
 *
 * These functions take a PyCSDL2_CType as an argument, allowing callers to
 * perform operations using any of the supported C types.
 *
 * This is used by PyCSDL2_Buffer to support arrays of different item types.
 *
 * @{
 */

/**
 * \brief Supported C types.
 */
enum PyCSDL2_CType {
    CTYPE_UCHAR = 0,
    CTYPE_USHORT,
    CTYPE_UINT,
    CTYPE_ULONG,
    CTYPE_UINT16,
    CTYPE_UINT32,

    CTYPE_CHAR,
    CTYPE_SHORT,
    CTYPE_INT,
    CTYPE_LONG,
    CTYPE_SINT16,
    CTYPE_SINT32
};

/**
 * \brief Returns the size of a PyCSDL2_CType.
 */
static Py_ssize_t
PyCSDL2_CTypeSize(enum PyCSDL2_CType t)
{
    switch (t) {
        case CTYPE_UCHAR: return sizeof(unsigned char);
        case CTYPE_CHAR: return sizeof(signed char);
        case CTYPE_USHORT: return sizeof(unsigned short);
        case CTYPE_SHORT: return sizeof(short);
        case CTYPE_UINT: return sizeof(unsigned int);
        case CTYPE_INT: return sizeof(int);
        case CTYPE_ULONG: return sizeof(unsigned long);
        case CTYPE_LONG: return sizeof(long);
        case CTYPE_UINT16: return sizeof(Uint16);
        case CTYPE_SINT16: return sizeof(Sint16);
        case CTYPE_UINT32: return sizeof(Uint32);
        case CTYPE_SINT32: return sizeof(Sint32);
        default:
            Py_FatalError("PyCSDL2_CTypeSize(): invalid type");
            return 0;
    }
}


/**
 * \brief Returns the Python format string of a PyCSDL2_CType.
 */
static const char *
PyCSDL2_CTypeFormat(enum PyCSDL2_CType t)
{
    switch (t) {
        case CTYPE_UCHAR: return "B";
        case CTYPE_CHAR: return "b";
        case CTYPE_USHORT: return "H";
        case CTYPE_SHORT: return "h";
        case CTYPE_UINT: return "I";
        case CTYPE_INT: return "i";
        case CTYPE_ULONG: return "L";
        case CTYPE_LONG: return "l";
        case CTYPE_UINT16: return Uint16_UNIT;
        case CTYPE_SINT16: return Sint16_UNIT;
        case CTYPE_UINT32: return Uint32_UNIT;
        case CTYPE_SINT32: return Sint32_UNIT;
        default:
            Py_FatalError("PyCSDL2_CTypeFormat(): invalid type");
            return NULL;
    }
}

/**
 * \brief Returns true if the PyCSDL2_CType is an unsigned type.
 */
static int
PyCSDL2_CTypeUnsigned(enum PyCSDL2_CType t)
{
    return (t < CTYPE_CHAR);
}

/**
 * \brief Returns the minimum value that can be stored by the signed
 *        PyCSDL2_CType.
 *
 * \param t Signed PyCSDL2_CType.
 */
static long
PyCSDL2_CTypeSMin(enum PyCSDL2_CType t)
{
    switch (t) {
        case CTYPE_CHAR: return SCHAR_MIN;
        case CTYPE_SHORT: return SHRT_MIN;
        case CTYPE_INT: return INT_MIN;
        case CTYPE_LONG: return LONG_MIN;
        case CTYPE_SINT16: return INT16_MIN;
        case CTYPE_SINT32: return INT32_MIN;
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return 0;
    }
}

/**
 * \brief Returns the maximum value that can be stored by the signed
 *        PyCSDL2_CType.
 *
 * \param t Signed PyCSDL2_CType.
 *
 * \sa PyCSDL2_CTypeUMax()
 */
static long
PyCSDL2_CTypeSMax(enum PyCSDL2_CType t)
{
    switch (t) {
        case CTYPE_CHAR: return SCHAR_MAX;
        case CTYPE_SHORT: return SHRT_MAX;
        case CTYPE_INT: return INT_MAX;
        case CTYPE_LONG: return LONG_MAX;
        case CTYPE_SINT16: return INT16_MAX;
        case CTYPE_SINT32: return INT32_MAX;
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return 0;
    }
}

/**
 * \brief Returns the maximum value that can be stored by the unsigned
 *        PyCSDL2_CType.
 *
 * \param t Unsigned PyCSDL2_CType.
 */
static unsigned long
PyCSDL2_CTypeUMax(enum PyCSDL2_CType t)
{
    switch (t) {
        case CTYPE_UCHAR: return UCHAR_MAX;
        case CTYPE_USHORT: return USHRT_MAX;
        case CTYPE_UINT: return UINT_MAX;
        case CTYPE_ULONG: return ULONG_MAX;
        case CTYPE_UINT16: return UINT16_MAX;
        case CTYPE_UINT32: return UINT32_MAX;
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return 0;
    }
}

/**
 * \brief Returns an element of an array of signed PyCSDL2_CType items.
 *
 * \param t Signed PyCSDL2_CType.
 * \param arr The array.
 * \param i Element index.
 *
 * \sa PyCSDL2_CTypeArrayUValue()
 */
static long
PyCSDL2_CTypeArraySValue(enum PyCSDL2_CType t, void *arr, size_t i)
{
    switch (t) {
        case CTYPE_CHAR: return ((signed char*)arr)[i];
        case CTYPE_SHORT: return ((short*)arr)[i];
        case CTYPE_INT: return ((int*)arr)[i];
        case CTYPE_LONG: return ((long*)arr)[i];
        case CTYPE_SINT16: return ((Sint16*)arr)[i];
        case CTYPE_SINT32: return ((Sint32*)arr)[i];
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return 0;
    }
}

/**
 * \brief Sets an element of an array of signed PyCSDL2_CType items.
 *
 * \param t Signed PyCSDL2_CType.
 * \param arr The array.
 * \param i Element index.
 * \param x Value to assign to the element of the array.
 *
 * \sa PyCSDL2_CTypeArrayUSet()
 */
static void
PyCSDL2_CTypeArraySSet(enum PyCSDL2_CType t, void *arr, size_t i, long x)
{
    switch (t) {
        case CTYPE_CHAR:
            ((signed char*)arr)[i] = (signed char) x;
            return;
        case CTYPE_SHORT:
            ((short*)arr)[i] = (short) x;
            return;
        case CTYPE_INT:
            ((int*)arr)[i] = (int) x;
            return;
        case CTYPE_LONG:
            ((long*)arr)[i] = x;
            return;
        case CTYPE_SINT16:
            ((Sint16*)arr)[i] = (Sint16) x;
            return;
        case CTYPE_SINT32:
            ((Sint32*)arr)[i] = (Sint32) x;
            return;
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
    }
}

/**
 * \brief Returns an element of an array of unsigned PyCSDL2_CType items.
 *
 * \param t Unsigned PyCSDL2_CType.
 * \param arr The array.
 * \param i Element index.
 *
 * \sa PyCSDL2_CTypeArraySValue()
 */
static unsigned long
PyCSDL2_CTypeArrayUValue(enum PyCSDL2_CType t, void *arr, size_t i)
{
    switch (t) {
        case CTYPE_UCHAR: return ((unsigned char*)arr)[i];
        case CTYPE_USHORT: return ((unsigned short*)arr)[i];
        case CTYPE_UINT: return ((unsigned int*)arr)[i];
        case CTYPE_ULONG: return ((unsigned long*)arr)[i];
        case CTYPE_UINT16: return ((Uint16*)arr)[i];
        case CTYPE_UINT32: return ((Uint32*)arr)[i];
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return 0;
    }
}

/**
 * \brief Sets an element of an array of unsigned PyCSDL2_CType items.
 *
 * \param t Unsigned PyCSDL2_CType.
 * \param arr The array.
 * \param i Element index.
 * \param x Value to assign to the element.
 *
 * \sa PyCSDL2_CTypeArraySSet()
 */
static void
PyCSDL2_CTypeArrayUSet(enum PyCSDL2_CType t, void *arr, size_t i,
                       unsigned long x)
{
    switch (t) {
        case CTYPE_UCHAR:
            ((unsigned char*)arr)[i] = (unsigned char) x;
            return;
        case CTYPE_USHORT:
            ((unsigned short*)arr)[i] = (unsigned short) x;
            return;
        case CTYPE_UINT:
            ((unsigned int*)arr)[i] = (unsigned int) x;
            return;
        case CTYPE_ULONG:
            ((unsigned long*)arr)[i] = (unsigned long) x;
            return;
        case CTYPE_UINT16:
            ((Uint16*)arr)[i] = (Uint16) x;
            return;
        case CTYPE_UINT32:
            ((Uint32*)arr)[i] = (Uint32) x;
            return;
        default:
            Py_FatalError("PyCSDL2_CTypeArrayIndex(): invalid type");
            return;
    }
}

/** @} */

/**
 * \brief Set "invalid buffer size" exception.
 *
 * \param arg Argument name (if any)
 * \param expected Expected minimum size, in bytes.
 * \param actual Actual size, in bytes.
 * \returns NULL
 */
static void *
PyCSDL2_RaiseBufferSizeError(const char *arg, Py_ssize_t expected,
                             Py_ssize_t actual)
{
    return PyErr_Format(PyExc_BufferError, "%s%sInvalid buffer size. "
                        "Expected at least: %zd. Got: %zd.", arg ? arg : "",
                        arg ? ": " : "", expected, actual);
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
    enum PyCSDL2_CType itemtype; \
    void *buf; \
    Py_ssize_t len; \
    char readonly; \
    int num_exports;

/**
 * \brief Represents the data of PyCSDL2_Buffer-based types
 */
typedef struct PyCSDL2_Buffer {
    PyCSDL2_BufferHEAD
    /** \brief Optional reference to an object managing the buffer. */
    PyObject *obj;
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

    if (((flags & PyBUF_WRITABLE) == PyBUF_WRITABLE) && self->readonly) {
        PyErr_SetString(PyExc_BufferError, "Object is not writable.");
        return -1;
    }

    Py_INCREF(self);
    view->obj = (PyObject*) self;
    view->buf = self->buf;
    view->len = self->len * PyCSDL2_CTypeSize(self->itemtype);
    view->readonly = self->readonly;
    view->itemsize = PyCSDL2_CTypeSize(self->itemtype);
    view->format = NULL;
    if ((flags & PyBUF_FORMAT) == PyBUF_FORMAT)
        view->format = (char*) PyCSDL2_CTypeFormat(self->itemtype);
    view->ndim = 1;
    view->shape = NULL;
    if ((flags & PyBUF_ND) == PyBUF_ND)
        view->shape = &self->len;
    view->strides = NULL;
    if ((flags & PyBUF_STRIDES) == PyBUF_STRIDES)
        view->strides = &(view->itemsize);
    view->suboffsets = NULL;
    view->internal = NULL;
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

    if (PyCSDL2_CTypeUnsigned(self->itemtype)) {
        unsigned long x = PyCSDL2_CTypeArrayUValue(self->itemtype, self->buf,
                                                   index);
        return PyLong_FromUnsignedLong(x);
    } else {
        long x = PyCSDL2_CTypeArraySValue(self->itemtype, self->buf, index);
        return PyLong_FromLong(x);
    }
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

        if (PyCSDL2_CTypeUnsigned(self->itemtype)) {
            unsigned long x;

            x = PyLong_AsUnsignedLong(value);
            if (PyErr_Occurred())
                return -1;

            if (x > PyCSDL2_CTypeUMax(self->itemtype)) {
                PyErr_SetString(PyExc_OverflowError,
                                "value overflows itemtype");
                return -1;
            }

            PyCSDL2_CTypeArrayUSet(self->itemtype, self->buf, index, x);
        } else {
            long x;

            x = PyLong_AsLong(value);
            if (PyErr_Occurred())
                return -1;

            if (x < PyCSDL2_CTypeSMin(self->itemtype) ||
                x > PyCSDL2_CTypeSMax(self->itemtype)) {
                PyErr_SetString(PyExc_OverflowError,
                                "value overflows itemtype");
                return -1;
            }

            PyCSDL2_CTypeArraySSet(self->itemtype, self->buf, index, x);
        }

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
PyCSDL2_BufferInit(PyCSDL2_Buffer *self, enum PyCSDL2_CType itemtype,
                   void *buf, Py_ssize_t len, char readonly)
{
    self->itemtype = itemtype;
    self->buf = buf;
    self->len = len;
    self->readonly = readonly;
}

/**
 * \brief Creates an instance of PyCSDL2_BufferType
 */
static PyCSDL2_Buffer *
PyCSDL2_BufferCreate(enum PyCSDL2_CType itemtype, void *buf, Py_ssize_t len,
                     char readonly, PyObject *obj)
{
    PyCSDL2_Buffer *self;
    PyTypeObject *type = &PyCSDL2_BufferType;

    self = (PyCSDL2_Buffer*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    PyCSDL2_BufferInit(self, itemtype, buf, len, readonly);

    PyCSDL2_Set(self->obj, obj);

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
