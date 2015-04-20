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
* \file events.h
* \brief Bindings for SDL_events.h
*
* Implements bindings for SDL's event handling API (SDL_events.h)
*/
#ifndef _PYCSDL2_EVENTS_H_
#define _PYCSDL2_EVENTS_H_
#include <Python.h>
#include <SDL_events.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/**
 * \brief Instance data for PyCSDL2_EventMemType
 */
typedef struct PyCSDL2_EventMem {
    PyObject_HEAD
    /** \brief SDL_Event struct */
    SDL_Event ev;
} PyCSDL2_EventMem;

/**
 * \brief Type definition for the private class csdl2.SDL_EventMem
 */
static PyTypeObject PyCSDL2_EventMemType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_EventMem",
    /* tp_basicsize      */ sizeof(PyCSDL2_EventMem)
};

/**
 * \brief Creates a new instance of PyCSDL2_EventMemType
 *
 * \returns Pointer to PyCSDL2_EventMem on success, NULL if an exception
 *          occurred.
 */
static PyCSDL2_EventMem *
PyCSDL2_EventMemCreate(void)
{
    return (PyCSDL2_EventMem*) PyType_GenericAlloc(&PyCSDL2_EventMemType, 0);
}

/**
 * \brief Instance data of PyCSDL2_EventType
 */
typedef struct PyCSDL2_Event {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief Pointer to the PyCSDL2_EventMem for the event */
    PyCSDL2_EventMem *ev_mem;
} PyCSDL2_Event;

/**
 * \brief Instance creation function for PyCSDL2_EventType
 *
 * Sets PyCSDL2_Event.ev_mem to a new instance of PyCSDL2_EventMemType.
 */
static PyCSDL2_Event *
PyCSDL2_EventNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Event *self;

    if (!(self = (PyCSDL2_Event*)type->tp_alloc(type, 0)))
        return NULL;
    if (!(self->ev_mem = PyCSDL2_EventMemCreate()))
        return NULL;
    return self;
}

/**
 * \brief Destructor for PyCSDL2_EventType
 *
 * Releases reference to PyCSDL2_EventMem.
 */
static void
PyCSDL2_EventDealloc(PyCSDL2_Event *self)
{
    if (self->in_weakreflist)
        PyObject_ClearWeakRefs((PyObject*) self);
    Py_XDECREF(self->ev_mem);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Getter for csdl2.SDL_Event.type
 */
static PyObject *
PyCSDL2_EventGetType(PyCSDL2_Event *self, void *closure)
{
    assert(self->ev_mem);
    return PyLong_FromUnsignedLong(self->ev_mem->ev.type);
}

/**
 * \brief Setter for csdl2.SDL_Event.type
 */
static int
PyCSDL2_EventSetType(PyCSDL2_Event *self, PyObject *value, void *closure)
{
    unsigned long x = PyLong_AsUnsignedLong(value);
    if (PyErr_Occurred()) { return -1; }
    if (x > ((Uint32)-1)) {
        PyErr_SetString(PyExc_OverflowError, "value overflows Uint32");
        return -1;
    }
    assert(self->ev_mem);
    self->ev_mem->ev.type = x;
    return 0;
}

/**
 * \brief get setters for PyCSDL2_EventType
 */
static PyGetSetDef PyCSDL2_EventGetSetters[] = {
    {"type",
     (getter) PyCSDL2_EventGetType,
     (setter) PyCSDL2_EventSetType,
     "Event type",
     NULL},
    {NULL}
};

/**
 * \brief getbufferproc implementation for PyCSDL2_EventType
 */
static int
PyCSDL2_EventGetBuffer(PyCSDL2_Event *self, Py_buffer *view, int flags)
{
    static Py_ssize_t shape[] = {sizeof(SDL_Event)};
    static Py_ssize_t strides[] = {1};

    assert(self->ev_mem);
    view->buf = &self->ev_mem->ev;
    Py_INCREF((PyObject*) self);
    view->obj = (PyObject*) self;
    view->len = sizeof(SDL_Event);
    view->readonly = 0;
    view->itemsize = 1;
    view->format = "B";
    view->ndim = 1;
    view->shape = shape;
    view->strides = strides;
    view->suboffsets = NULL;
    view->internal = NULL;
    return 0;
}

/**
 * \brief Buffer protocol definition for PyCSDL2_EventType
 */
static PyBufferProcs PyCSDL2_EventBufferProcs = {
    (getbufferproc) PyCSDL2_EventGetBuffer,
    (releasebufferproc) NULL
};

/**
 * \brief Type definition of csdl2.SDL_Event
 */
static PyTypeObject PyCSDL2_EventType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Event",
    /* tp_basicsize      */ sizeof(PyCSDL2_Event),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_EventDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_EventBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "A union that contains structures for the different event types.\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Event, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_EventGetSetters,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ 0,
    /* tp_alloc          */ 0,
    /* tp_new            */ (newfunc) PyCSDL2_EventNew,
};

/**
 * \brief Checks for and retrieves a SDL_Event Py_buffer from obj.
 *
 * \param[out] buf The Py_buffer struct to fill up with buffer info
 * \param[in] obj The PyObject to retrieve the buffer from
 * \param[in] len Expected number of SDL_Event struct contained in buffer
 * \param[in] flags Additional flags to pass to PyObject_GetBuffer()
 * \returns 0 on success, -1 if the object does not support the buffer
 *          protocol, -2 if a fatal exception occurred.
 */
static int
PyCSDL2_GetEventBuffer(Py_buffer *buf, PyObject *obj, size_t len, int flags)
{
    if (PyObject_GetBuffer(obj, buf, PyBUF_ND | flags))
        return -1;
    if (!buf->buf) {
        PyBuffer_Release(buf);
        PyErr_SetString(PyExc_BufferError, "SDL_Event buffer is NULL");
        return -2;
    }
    if (buf->len != sizeof(SDL_Event) * len) {
        PyBuffer_Release(buf);
        PyErr_Format(PyExc_BufferError, "Invalid SDL_Event buffer size. "
                     "Expected: %zu. Got: %zd.", sizeof(SDL_Event) * len,
                     buf->len);
        return -2;
    }
    return 0;
}

/**
 * \brief Implements csdl2.SDL_PumpEvents()
 *
 * \code
 * SDL_PumpEvents() -> None
 * \endcode
 *
 * \returns Py_None on success, NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_PumpEvents(PyObject *module, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist))
        return NULL;
    SDL_PumpEvents();
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_PeepEvents()
 *
 * \code
 * SDL_PeepEvents(events, numevents: int, action: int, minType: int,
 *                maxType: int) -> int
 * \endcode
 * where events is a buffer object with len == sizeof(SDL_Event) * numevents
 *
 * \returns PyLong of the number of events actually stored, NULL if an
 *          exception occurred.
 */
static PyObject *
PyCSDL2_PeepEvents(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyObject *ev_obj;
    Py_buffer ev_buf;
    int numevents, action, ret, flags = 0;
    Uint32 minType, maxType;
    static char *kwlist[] = {"events", "numevents", "action", "minType",
                             "maxType", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Oii" Uint32_UNIT Uint32_UNIT,
                                     kwlist, &ev_obj, &numevents, &action,
                                     &minType, &maxType))
        return NULL;
    if (numevents < 0) {
        PyErr_SetString(PyExc_ValueError, "numevents must be positive");
        return NULL;
    }
    if (action != SDL_ADDEVENT)
        flags |= PyBUF_WRITABLE;
    if (PyCSDL2_GetEventBuffer(&ev_buf, ev_obj, numevents, flags))
        return NULL;
    ret = SDL_PeepEvents(ev_buf.buf, numevents, action, minType, maxType);
    PyBuffer_Release(&ev_buf);
    if (ret < 0)
        return PyCSDL2_RaiseSDLError();
    return PyLong_FromLong(ret);
}

/**
 * \brief Implements csdl2.SDL_FlushEvents()
 *
 * \code
 * SDL_FlushEvents(minType: int, maxType: int) -> None
 * \endcode
 *
 * \returns Py_None on success, NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_FlushEvents(PyObject *module, PyObject *args, PyObject *kwds)
{
    Uint32 minType, maxType;
    static char *kwlist[] = {"minType", "maxType", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, Uint32_UNIT Uint32_UNIT,
                                     kwlist, &minType, &maxType))
        return NULL;
    SDL_FlushEvents(minType, maxType);
    Py_RETURN_NONE;
}

/**
 * \brief Implements csdl2.SDL_PollEvent()
 *
 * \code
 * SDL_PollEvent(event) -> bool
 * \endcode
 * where event is any object that provides a buffer with the same size as
 * SDL_Event.
 *
 * \returns Py_True if SDL_PollEvent() returned 1 and Py_False if
 *          SDL_PollEvent() returned 0. NULL if an exception occurred.
 */
static PyObject *
PyCSDL2_PollEvent(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyObject *ev_obj;
    Py_buffer ev_buf;
    int ret;
    static char *kwlist[] = {"event", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist,
                                     &ev_obj))
        return NULL;
    if (ev_obj == Py_None) {
        ev_buf.obj = NULL;
        ev_buf.buf = NULL;
    } else if (PyCSDL2_GetEventBuffer(&ev_buf, ev_obj, 1, PyBUF_WRITABLE))
        return NULL;
    ret = SDL_PollEvent((SDL_Event*) ev_buf.buf);
    PyBuffer_Release(&ev_buf);
    return PyBool_FromLong(ret);
}

/**
 * \brief Implements csdl2.SDL_PushEvent()
 *
 * \code
 * SDL_PushEvent(event) -> bool
 * \endcode
 * where event is any object that provides a buffer with the same size as
 * SDL_Event.
 *
 * \returns Py_True if SDL_PushEvent() returned 1 and Py_False if
 *          SDL_PushEvent() returned 0.
 */
static PyObject *
PyCSDL2_PushEvent(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyObject *ev_obj;
    Py_buffer ev_buf;
    int ret;
    static char *kwlist[] = {"event", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist,
                                     &ev_obj))
        return NULL;
    if (PyCSDL2_GetEventBuffer(&ev_buf, ev_obj, 1, 0))
        return NULL;
    ret = SDL_PushEvent((SDL_Event*) ev_buf.buf);
    PyBuffer_Release(&ev_buf);
    if (ret < 0)
        return PyCSDL2_RaiseSDLError();
    return PyBool_FromLong(ret);
}

/**
 * \brief Initializes bindings to SDL_events.h
 *
 * \param module csdl2 module PyObject
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initevents(PyObject *module)
{
    static const PyCSDL2_Constant constants[] = {
        {"SDL_RELEASED", SDL_RELEASED},
        {"SDL_PRESSED", SDL_PRESSED},
        {"SDL_FIRSTEVENT", SDL_FIRSTEVENT},
        /* Application events */
        {"SDL_QUIT", SDL_QUIT},
        {"SDL_APP_TERMINATING", SDL_APP_TERMINATING},
        {"SDL_APP_LOWMEMORY", SDL_APP_LOWMEMORY},
        {"SDL_APP_WILLENTERBACKGROUND", SDL_APP_WILLENTERBACKGROUND},
        {"SDL_APP_DIDENTERBACKGROUND", SDL_APP_DIDENTERBACKGROUND},
        {"SDL_APP_WILLENTERFOREGROUND", SDL_APP_WILLENTERFOREGROUND},
        {"SDL_APP_DIDENTERFOREGROUND", SDL_APP_DIDENTERFOREGROUND},
        /* Window events */
        {"SDL_WINDOWEVENT", SDL_WINDOWEVENT},
        {"SDL_SYSWMEVENT", SDL_SYSWMEVENT},
        /* Keyboard events */
        {"SDL_KEYDOWN", SDL_KEYDOWN},
        {"SDL_KEYUP", SDL_KEYUP},
        {"SDL_TEXTEDITING", SDL_TEXTEDITING},
        {"SDL_TEXTINPUT", SDL_TEXTINPUT},
        /* Mouse events */
        {"SDL_MOUSEMOTION", SDL_MOUSEMOTION},
        {"SDL_MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN},
        {"SDL_MOUSEBUTTONUP", SDL_MOUSEBUTTONUP},
        {"SDL_MOUSEWHEEL", SDL_MOUSEWHEEL},
        /* Joystick events */
        {"SDL_JOYAXISMOTION", SDL_JOYAXISMOTION},
        {"SDL_JOYBALLMOTION", SDL_JOYBALLMOTION},
        {"SDL_JOYHATMOTION", SDL_JOYHATMOTION},
        {"SDL_JOYBUTTONDOWN", SDL_JOYBUTTONDOWN},
        {"SDL_JOYBUTTONUP", SDL_JOYBUTTONUP},
        {"SDL_JOYDEVICEADDED", SDL_JOYDEVICEADDED},
        {"SDL_JOYDEVICEREMOVED", SDL_JOYDEVICEREMOVED},
        /* Game controller events */
        {"SDL_CONTROLLERAXISMOTION", SDL_CONTROLLERAXISMOTION},
        {"SDL_CONTROLLERBUTTONDOWN", SDL_CONTROLLERBUTTONDOWN},
        {"SDL_CONTROLLERBUTTONUP", SDL_CONTROLLERBUTTONUP},
        {"SDL_CONTROLLERDEVICEADDED", SDL_CONTROLLERDEVICEADDED},
        {"SDL_CONTROLLERDEVICEREMOVED", SDL_CONTROLLERDEVICEREMOVED},
        {"SDL_CONTROLLERDEVICEREMAPPED", SDL_CONTROLLERDEVICEREMAPPED},
        /* Touch events */
        {"SDL_FINGERDOWN", SDL_FINGERDOWN},
        {"SDL_FINGERUP", SDL_FINGERUP},
        {"SDL_FINGERMOTION", SDL_FINGERMOTION},
        /* Gesture events */
        {"SDL_DOLLARGESTURE", SDL_DOLLARGESTURE},
        {"SDL_DOLLARRECORD", SDL_DOLLARRECORD},
        {"SDL_MULTIGESTURE", SDL_MULTIGESTURE},
        /* Clipboard events */
        {"SDL_CLIPBOARDUPDATE", SDL_CLIPBOARDUPDATE},
        /* Drag and drop events */
        {"SDL_DROPFILE", SDL_DROPFILE},
        {"SDL_USEREVENT", SDL_USEREVENT},
        {"SDL_LASTEVENT", SDL_LASTEVENT},

        {"SDL_ADDEVENT", SDL_ADDEVENT},
        {"SDL_PEEKEVENT", SDL_PEEKEVENT},
        {"SDL_GETEVENT", SDL_GETEVENT},

        {"SDL_QUERY", SDL_QUERY},
        {"SDL_IGNORE", SDL_IGNORE},
        {"SDL_DISABLE", SDL_DISABLE},
        {"SDL_ENABLE", SDL_ENABLE},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;

    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(module, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_EventMemType)) { return 0; }

    if (PyType_Ready(&PyCSDL2_EventType)) { return 0; }
    Py_INCREF(&PyCSDL2_EventType);
    if (PyModule_AddObject(module, "SDL_Event", (PyObject*)&PyCSDL2_EventType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_EVENTS_H_ */
