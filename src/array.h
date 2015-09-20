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
 * \file array.h
 * \brief Shared utility functionality.
 */
#ifndef _PYCSDL2_ARRAY_H_
#define _PYCSDL2_ARRAY_H_
#include <Python.h>
#include "../include/pycsdl2.h"
#include "util.h"

/**
 * \defgroup csdl2_arrayview Array view implementation macros
 *
 * \brief C macros for implementing array view types.
 *
 * These C macros can be used for defining and implementing an array view
 * Python class. Array views, like memoryviews, provide list-like access to an
 * existing memory buffer.
 *
 * Array view macros allow us to specialize the array view for a single array
 * type, thus allowing the C compiler to better optimize the implementation,
 * leading to faster array access operations.
 *
 * @{
 */

/** \brief Flag that is set if the buffer is readonly */
#define PyCSDL2_ARRAYVIEW_READONLY (1 << 0)

/**
 * \brief Instance data for an array view type.
 */
#define PyCSDL2_ARRAYVIEW_HEAD \
    PyObject_HEAD \
    unsigned int flags; \
    char *buf; \
    Py_ssize_t len; \
    Py_ssize_t stride; \
    Py_buffer *view;

/**
 * \brief Implements the destructor for the array view.
 *
 * \param[in] p_self The array view instance PyObject*.
 */
#define PyCSDL2_ARRAYVIEW_DEALLOC(p_self) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avd_self = (void*)(p_self); \
        \
        if (_avd_self->view) { \
            PyBuffer_Release(_avd_self->view); \
            PyMem_Free(_avd_self->view); \
        } \
    } while (0)

/**
 * \brief Initializes an array view from a Py_buffer view.
 *
 * \param[out] p_ret Return code.
 * \param[in] p_self Array view PyObject* to initialize.
 * \param[in] p_flags Flags that should be set on the array view.
 * \param[in] p_view Pointer to a Py_buffer memory that must be allocated with
 *                   the CPython memory allocator. The new array view instance
 *                   will take ownership of this memory, and will call
 *                   PyBuffer_Release() and PyMem_Free() on it in its
 *                   destructor.
 * \param[in] p_type C type of the array view element.
 * \returns 0 on success, -1 if an exception occurred.
 */
#define PyCSDL2_ARRAYVIEW_INIT_VIEW(p_ret, p_self, p_flags, p_view, p_type) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_aviv_self = (void*)(p_self); \
        \
        if (PyCSDL2_ValidateArrayBuffer((p_view), sizeof(p_type), -1, 0) < 0) { \
            p_ret = -1; \
            break; \
        } \
        \
        _aviv_self->flags = (p_flags); \
        if ((p_view)->readonly) \
            _aviv_self->flags |= PyCSDL2_ARRAYVIEW_READONLY; \
        _aviv_self->buf = (p_view)->buf; \
        _aviv_self->len = (p_view)->shape[0]; \
        _aviv_self->stride = (p_view)->strides ? (p_view)->strides[0] : sizeof(p_type); \
        _aviv_self->view = (p_view); \
        p_ret = 0; \
    } while (0)

/**
 * \brief Fills up a Py_buffer with buffer info.
 *
 * \param[out] p_out int that will be set to the return code. Set to 0 on
 *                   success, -1 if an exception occurred.
 * \param[in] p_self The array view PyObject*.
 * \param[in] p_view The Py_buffer* to be filled with buffer info.
 * \param[in] p_type C type of the array view element.
 * \param[in] p_format Format string that corresponds to the C type of the
 *                     array view element.
 */
#define PyCSDL2_ARRAYVIEW_GETBUFFER(p_out, p_self, p_view, p_type, p_format) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avgb_self = (void*)(p_self); \
        \
        Py_INCREF(self); \
        (p_view)->obj = (PyObject*)_avgb_self; \
        (p_view)->buf = _avgb_self->buf; \
        (p_view)->len = sizeof(p_type) * _avgb_self->len; \
        (p_view)->readonly = (_avgb_self->flags & PyCSDL2_ARRAYVIEW_READONLY); \
        (p_view)->itemsize = sizeof(p_type); \
        (p_view)->format = NULL; \
        if ((flags & PyBUF_FORMAT) == PyBUF_FORMAT) \
            (p_view)->format = (char *)(p_format); \
        (p_view)->ndim = 1; \
        (p_view)->shape = NULL; \
        if ((flags & PyBUF_ND) == PyBUF_ND) \
            (p_view)->shape = &_avgb_self->len; \
        (p_view)->strides = NULL; \
        if ((flags & PyBUF_STRIDES) == PyBUF_STRIDES) \
            (p_view)->strides = &_avgb_self->stride; \
        (p_view)->suboffsets = NULL; \
        (p_view)->internal = NULL; \
        p_out = 0; \
    } while (0)

/**
 * \brief Implements an array view Python type, and all of its functions and
 *        variables.
 *
 * The following will be defined:
 *
 * \li \c p_prefix - Instance data struct.
 * \li <tt>p_prefix ## Type</tt> PyTypeObject for the array view type.
 * \li <tt>p_prefix ## Dealloc</tt> Implements \c tp_dealloc
 * \li <tt>p_prefix ## New</tt> Implements \c tp_new
 * \li <tt>p_prefix ## GetBuffer</tt> Implements \c bf_getbuffer
 * \li <tt>p_prefix ## AsBuffer</tt> Defines \c tp_asbuffer
 *
 * \param[in] p_prefix Prefix for naming all the functions and variables.
 * \param[in] p_type C type of the array view element.
 * \param[in] p_format Format string that corresponds to the C type of the
 *                     array view element.
 * \param[in] p_name \c tp_name of the type.
 */
#define PyCSDL2_ARRAYVIEW_IMPL(p_prefix, p_type, p_format, p_name) \
    typedef struct p_prefix { \
        PyCSDL2_ARRAYVIEW_HEAD \
    } p_prefix; \
    \
    static PyTypeObject p_prefix ## Type; \
    \
    static void \
    p_prefix ## Dealloc(PyObject *self) \
    { \
        PyCSDL2_ARRAYVIEW_DEALLOC(self); \
        Py_TYPE(self)->tp_free(self); \
    } \
    \
    static PyObject * \
    p_prefix ## New(PyTypeObject *type, PyObject *args, PyObject *kwds) \
    { \
        Py_buffer *view; \
        PyObject *buffer, *out; \
        int ret, readonly = 0; \
        unsigned int flags = 0; \
        static char *kwlist[] = {"buffer", "readonly", NULL}; \
        \
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|p", kwlist, &buffer, \
                                         &readonly)) \
            return NULL; \
        \
        view = PyMem_New(Py_buffer, 1); \
        if (!view) \
            return PyErr_NoMemory(); \
        \
        if (PyObject_GetBuffer(buffer, view, PyBUF_STRIDED_RO) < 0) { \
            PyMem_Free(view);\
            return NULL; \
        } \
        \
        out = type->tp_alloc(type, 0); \
        if (!out) { \
            PyBuffer_Release(view); \
            PyMem_Free(view); \
            return NULL; \
        } \
        \
        if (readonly) \
            flags |= PyCSDL2_ARRAYVIEW_READONLY; \
        \
        PyCSDL2_ARRAYVIEW_INIT_VIEW(ret, out, flags, view, p_type); \
        if (ret < 0) { \
            Py_DECREF(out); \
            PyBuffer_Release(view); \
            PyMem_Free(view); \
            return NULL; \
        } \
        \
        return out; \
    } \
    \
    static int \
    p_prefix ## GetBuffer(PyObject *self, Py_buffer *view, int flags) \
    { \
        int ret; \
        PyCSDL2_ARRAYVIEW_GETBUFFER(ret, self, view, p_type, p_format); \
        return ret; \
    } \
    \
    static PyBufferProcs p_prefix ## AsBuffer = { \
        /* bf_getbuffer     */ p_prefix ## GetBuffer, \
        /* bf_releasebuffer */ 0 \
    }; \
    \
    static PyTypeObject p_prefix ## Type = { \
        PyVarObject_HEAD_INIT(NULL, 0) \
        /* tp_name           */ ("csdl2." p_name), \
        /* tp_basicsize      */ sizeof(p_prefix), \
        /* tp_itemsize       */ 0, \
        /* tp_dealloc        */ (p_prefix ## Dealloc), \
        /* tp_print          */ 0, \
        /* tp_getattr        */ 0, \
        /* tp_setattr        */ 0, \
        /* tp_reserved       */ 0, \
        /* tp_repr           */ 0, \
        /* tp_as_number      */ 0, \
        /* tp_as_sequence    */ 0, \
        /* tp_as_mapping     */ 0, \
        /* tp_hash           */ 0, \
        /* tp_call           */ 0, \
        /* tp_str            */ 0, \
        /* tp_getattro       */ 0, \
        /* tp_setattro       */ 0, \
        /* tp_as_buffer      */ &(p_prefix ## AsBuffer), \
        /* tp_flags          */ Py_TPFLAGS_DEFAULT, \
        /* tp_doc            */ \
        p_name "(buffer)\n" \
        "\n" \
        "Create a new " #p_type " array view object which references the\n" \
        "buffer of the given object.", \
        /* tp_traverse       */ 0, \
        /* tp_clear          */ 0, \
        /* tp_richcompare    */ 0, \
        /* tp_weaklistoffset */ 0, \
        /* tp_iter           */ 0, \
        /* tp_iternext       */ 0, \
        /* tp_methods        */ 0, \
        /* tp_members        */ 0, \
        /* tp_getset         */ 0, \
        /* tp_base           */ 0, \
        /* tp_dict           */ 0, \
        /* tp_descr_get      */ 0, \
        /* tp_descr_set      */ 0, \
        /* tp_dictoffset     */ 0, \
        /* tp_init           */ 0, \
        /* tp_alloc          */ 0, \
        /* tp_new            */ (p_prefix ## New) \
    };

/** @} */

/**
 * \brief Initializes array types.
 *
 * \param module csdl2 module object.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initarray(PyObject *module)
{
    return 1;
}

#endif /* _PYCSDL2_ARRAY_H_ */
