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
    PyObject *master; \
    Py_buffer *view;

/**
 * \brief Validates the array view.
 *
 * \param writeable Set to true to ensure that the underlying buffer can be
 *                  written to.
 */
#define PyCSDL2_ARRAYVIEW_VALID(p_out, p_self, p_writeable) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avv_self = (void*)(p_self); \
        \
        if (!_avv_self->buf) { \
            PyErr_SetString(PyExc_ValueError, "array has been released"); \
            p_out = 0; \
            break; \
        } \
        \
        if ((p_writeable) && _avv_self->flags & PyCSDL2_ARRAYVIEW_READONLY) { \
            PyCSDL2_RaiseReadonlyError((PyObject *)_avv_self); \
            p_out = 0; \
            break; \
        } \
        \
        p_out = 1; \
    } while (0)

/**
 * \brief Releases the array view
 */
#define PyCSDL2_ARRAYVIEW_RELEASE(p_self) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avr_self = (void*)(p_self); \
        \
        _avr_self->buf = NULL; \
        Py_CLEAR(_avr_self->master); \
        if (_avr_self->view) { \
            PyBuffer_Release(_avr_self->view); \
            PyMem_Free(_avr_self->view); \
            _avr_self->view = NULL; \
        } \
    } while (0)

/**
 * \brief Implements the destructor for the array view.
 *
 * \param[in] p_self The array view instance PyObject*.
 */
#define PyCSDL2_ARRAYVIEW_DEALLOC(p_self) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avd_self = (void*)(p_self); \
        \
        PyCSDL2_ARRAYVIEW_RELEASE(_avd_self); \
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
 * \brief Initializes an array view from a pointer.
 *
 * \param[in] p_self Array view PyObject* to initialize.
 * \param[in] p_flags Array view flags.
 * \param[in] p_buf Buffer pointer.
 * \param[in] p_len (Py_ssize_t) Number of elements in the array.
 * \param[in] p_stride (Py_ssize_t) Stride of the array
 * \param[in] p_master (PyObject*) Array view managing the buffer
 * \param[in] p_type C type of the array view element.
 */
#define PyCSDL2_ARRAYVIEW_INIT_PTR(p_self, p_flags, p_buf, p_len, p_stride, \
                                   p_master) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avip_self = (void *)(p_self); \
        \
        _avip_self->flags = (p_flags); \
        _avip_self->buf = (char *)(p_buf); \
        _avip_self->len = (p_len); \
        _avip_self->stride = (p_stride); \
        PyCSDL2_Set(_avip_self->master, (p_master)); \
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
        int _avgb_ret; \
        \
        PyCSDL2_ARRAYVIEW_VALID(_avgb_ret, _avgb_self, 0); \
        if (!_avgb_ret) { \
            p_out = -1; \
            break; \
        } \
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
 * \brief Returns the length of the array view.
 *
 * \param[out] p_out Py_ssize_t that will be set to the length of the array.
 * \param[in] p_self Array view to query.
 */
#define PyCSDL2_ARRAYVIEW_LENGTH(p_out, p_self) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *bl_self = (void*)(p_self); \
        (p_out) = bl_self->len; \
    } while (0)

/**
 * \brief Returns the element at index, using a conversion function.
 *
 * \param[out] p_out Output PyObject*.
 * \param[in] p_self The array view PyObject.
 * \param[in] p_index The index to retrieve the element of, a Py_ssize_t.
 * \param[in] p_type C type of the element.
 * \param[in] p_getitem_fn The conversion function which constructs the output
 *                         object. It must have the function signature
 *                         <tt>PyObject *getitem_fn(p_type *, PyObject *)</tt>.
 *                         The first argument is the pointer to the element,
 *                         and the second argument is the backing array object.
 *                         If the object stores the pointer, it must keep a
 *                         reference to that object to guarantee the validity
 *                         of that pointer.
 */
#define PyCSDL2_ARRAYVIEW_GETITEM(p_out, p_self, p_index, p_type, p_getitem_fn) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avgi_self = (void*)(p_self); \
        \
        if ((p_index) < 0 || (p_index) >= _avgi_self->len) { \
            PyErr_SetString(PyExc_IndexError, "index out of bounds"); \
            return NULL; \
        } \
        \
        p_out = (p_getitem_fn)((p_type*)(_avgi_self->buf + (p_index) * _avgi_self->stride), (PyObject*)_avgi_self); \
    } while (0)

/**
 * Array subscript.
 */
#define PyCSDL2_ARRAYVIEW_SUBSCRIPT(p_out, p_self, p_key, p_type, p_typeobject, p_getitem_fn) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avs_self = (void*)(p_self); \
        \
        if (PyIndex_Check(p_key)) { \
            Py_ssize_t _avs_index; \
            \
            _avs_index = PyNumber_AsSsize_t(key, PyExc_IndexError); \
            if (_avs_index == -1 && PyErr_Occurred()) { \
                p_out = NULL; \
                break; \
            } \
            \
            if (_avs_index < 0) \
                _avs_index = _avs_self->len + _avs_index; \
            \
            PyCSDL2_ARRAYVIEW_GETITEM(p_out, _avs_self, _avs_index, p_type, p_getitem_fn); \
        } else if (PySlice_Check(p_key)) { \
            PyObject *_avs_out; \
            Py_ssize_t _avs_start, _avs_stop, _avs_step, _avs_len; \
            \
            if (PySlice_GetIndicesEx((p_key), _avs_self->len, &_avs_start,\
                                     &_avs_stop, &_avs_step, &_avs_len) < 0) {\
                p_out = NULL; \
                break; \
            } \
            \
            _avs_out = (p_typeobject)->tp_alloc((p_typeobject), 0); \
            if (!_avs_out) { \
                p_out = NULL; \
                break; \
            } \
            \
            PyCSDL2_ARRAYVIEW_INIT_PTR(_avs_out, _avs_self->flags, \
                                       _avs_self->buf + _avs_start * _avs_self->stride, \
                                       _avs_len, _avs_self->stride * _avs_step,\
                                       _avs_self->master ? _avs_self->master : (PyObject *)_avs_self); \
            p_out = (PyObject *)_avs_out; \
        } else { \
            PyErr_SetString(PyExc_TypeError, "Invalid slice key"); \
            p_out = NULL; \
        } \
    } while (0)

/**
 * \brief Sets an item
 */
#define PyCSDL2_ARRAYVIEW_SETITEM(p_out, p_self, p_index, p_value, p_type, p_cvtitem_fn) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avsi_self = (void*)(p_self); \
        Py_ssize_t _avsi_index = (p_index); \
        int _avsi_ret; \
        \
        _avsi_ret = (p_cvtitem_fn)(p_value, \
                                  (p_type*)(_avsi_self->buf + _avsi_index * _avsi_self->stride)); \
        if (!_avsi_ret) { \
            p_out = -1; \
            break; \
        } \
        p_out = 0; \
    } while (0)

/**
 * \brief Copies the contents of a buffer to a slice.
 *
 * \param[out] p_out
 * \param[in] p_self
 * \param[in] p_start
 * \param[in] p_count Number of elements to copy
 * \param[in] p_step
 * \param[in] p_view
 * \param[in] p_type
 */
#define PyCSDL2_ARRAYVIEW_SETSLICE_FROMBUF(p_out, p_self, p_start, p_count, p_step, p_view, p_type) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avssfb_self = (void*)(p_self); \
        Py_ssize_t _avssfb_count, _avssfb_i, _avssfb_view_stride; \
        \
        _avssfb_view_stride = (p_view)->strides ? (p_view)->strides[0] : (p_view)->itemsize; \
        \
        for (_avssfb_i = (p_start), _avssfb_count = 0; \
             _avssfb_count < (p_count); \
             _avssfb_i += (p_step), _avssfb_count++) \
            *((p_type*)(_avssfb_self->buf + _avssfb_i * _avssfb_self->stride))\
            = *((p_type*)((char*)((p_view)->buf) + _avssfb_count * _avssfb_view_stride)); \
        \
        p_out = 0; \
    } while (0)

/**
 * \brief Implements subscript
 */
#define PyCSDL2_ARRAYVIEW_ASS_SUBSCRIPT(p_out, p_self, p_key, p_value, p_type,\
                                        p_cvtitem_fn) \
    do { \
        struct { PyCSDL2_ARRAYVIEW_HEAD } *_avsb_self = (void*)(p_self); \
        int _avsb_ret; \
        \
        PyCSDL2_ARRAYVIEW_VALID(_avsb_ret, _avsb_self, 1); \
        if (!_avsb_ret) { \
            p_out = -1; \
            break; \
        } \
        \
        if (!(p_value)) { \
            PyErr_SetString(PyExc_TypeError, "cannot delete memory"); \
            p_out = -1; \
            break; \
        } \
        \
        if (PyIndex_Check(p_key)) { \
            Py_ssize_t _avsb_index; \
            \
            _avsb_index = PyNumber_AsSsize_t((p_key), PyExc_IndexError); \
            if (_avsb_index == -1 && PyErr_Occurred()) { \
                p_out = -1; \
                break; \
            } \
            \
            if (_avsb_index < 0) \
                _avsb_index = _avsb_self->len + _avsb_index; \
            \
            if (_avsb_index < 0 || _avsb_index >= _avsb_self->len) { \
                PyErr_SetString(PyExc_IndexError, "index out of bounds"); \
                p_out = -1; \
                break; \
            } \
            \
            PyCSDL2_ARRAYVIEW_SETITEM(p_out, _avsb_self, _avsb_index, p_value, \
                                      p_type, p_cvtitem_fn); \
        } else if (PySlice_Check(p_key)) { \
            Py_ssize_t _avsb_start, _avsb_stop, _avsb_step, _avsb_count; \
            Py_buffer _avsb_view; \
            \
            if (PySlice_GetIndicesEx((p_key), _avsb_self->len, &_avsb_start,\
                                     &_avsb_stop, &_avsb_step, &_avsb_count) < 0) { \
                p_out = -1; \
                break; \
            } \
            \
            if (PyObject_GetBuffer((p_value), &_avsb_view, PyBUF_STRIDED_RO) < 0) { \
                p_out = -1; \
                break; \
            } \
            \
            if (PyCSDL2_ValidateArrayBuffer(&_avsb_view, sizeof(p_type), _avsb_count, 0) < 0) { \
                PyBuffer_Release(&_avsb_view); \
                p_out = -1; \
                break; \
            } \
            \
            PyCSDL2_ARRAYVIEW_SETSLICE_FROMBUF(p_out, _avsb_self, _avsb_start,\
                                               _avsb_count, _avsb_step, \
                                               &_avsb_view, p_type); \
            PyBuffer_Release(&_avsb_view); \
        } else { \
            PyErr_SetString(PyExc_TypeError, "Invalid slice key"); \
            p_out = -1; \
        } \
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
#define PyCSDL2_ARRAYVIEW_IMPL(p_prefix, p_type, p_format, p_name, \
                               p_getitem_fn, p_cvtitem_fn) \
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
    static Py_ssize_t \
    p_prefix ## Length(PyObject *self) \
    { \
        Py_ssize_t out; \
        PyCSDL2_ARRAYVIEW_LENGTH(out, self); \
        return out; \
    } \
    \
    static PyObject * \
    p_prefix ## GetItem(PyObject *self, Py_ssize_t index) \
    { \
        PyObject *out; \
        PyCSDL2_ARRAYVIEW_GETITEM(out, self, index, p_type, p_getitem_fn); \
        return out; \
    } \
    \
    static PyObject * \
    p_prefix ## Subscript(PyObject *self, PyObject *key) \
    { \
        PyObject *out; \
        PyCSDL2_ARRAYVIEW_SUBSCRIPT(out, self, key, p_type, &(p_prefix ## Type), p_getitem_fn); \
        return out; \
    } \
    \
    static int \
    p_prefix ## AssSubscript(PyObject *self, PyObject *key, PyObject *value) \
    { \
        int ret; \
        PyCSDL2_ARRAYVIEW_ASS_SUBSCRIPT(ret, self, key, value, p_type, \
                                        p_cvtitem_fn); \
        return ret; \
    } \
    \
    static PyObject * \
    p_prefix ## Release(PyObject *self, PyObject *args, PyObject *kwds) \
    { \
        static char *kwlist[] = {NULL}; \
        \
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist)) \
            return NULL; \
        \
        PyCSDL2_ARRAYVIEW_RELEASE(self); \
        \
        Py_RETURN_NONE; \
    } \
    \
    static PyBufferProcs p_prefix ## AsBuffer = { \
        /* bf_getbuffer     */ p_prefix ## GetBuffer, \
        /* bf_releasebuffer */ 0 \
    }; \
    \
    static PySequenceMethods p_prefix ## AsSequence = { \
        /* sq_length         */ p_prefix ## Length, \
        /* sq_concat         */ NULL, \
        /* sq_repeat         */ NULL, \
        /* sq_item           */ p_prefix ## GetItem \
    }; \
    \
    static PyMappingMethods p_prefix ## AsMapping = { \
        /* mp_length        */ p_prefix ## Length, \
        /* mp_subscript     */ p_prefix ## Subscript, \
        /* mp_ass_subscript */ p_prefix ## AssSubscript \
    }; \
    \
    static PyMethodDef p_prefix ## Methods[] = { \
        {"release", \
         (PyCFunction) p_prefix ## Release, \
         METH_VARARGS | METH_KEYWORDS, \
         "release() -> None \n" \
         "\n" \
         "Release the underlying buffer exposed by the array view.\n" \
        }, \
        {NULL}, \
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
        /* tp_as_sequence    */ &(p_prefix ## AsSequence), \
        /* tp_as_mapping     */ &(p_prefix ## AsMapping), \
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
        /* tp_methods        */ (p_prefix ## Methods), \
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
