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

/** \brief Instance data for PyCSDL2_MouseMotionEventType */
typedef struct PyCSDL2_MouseMotionEvent {
    PyObject_HEAD
    /** \brief Head of weak ref list */
    PyObject *in_weakreflist;
    /** \brief Underlying PyCSDL2_EventMem */
    PyCSDL2_EventMem *ev_mem;
} PyCSDL2_MouseMotionEvent;

static PyTypeObject PyCSDL2_MouseMotionEventType;

/** \brief newfunc for PyCSDL2_MouseMotionEventType */
static PyCSDL2_MouseMotionEvent *
PyCSDL2_MouseMotionEventNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCSDL2_MouseMotionEvent *self;

    if (!(self = (PyCSDL2_MouseMotionEvent*) type->tp_alloc(type, 0)))
        return NULL;

    self->ev_mem = PyCSDL2_EventMemCreate();
    if (!self->ev_mem) {
        Py_DECREF(self);
        return NULL;
    }

    return self;
}

/** \brief Destructor for PyCSDL2_MouseMotionEventType */
static void
PyCSDL2_MouseMotionEventDealloc(PyCSDL2_MouseMotionEvent *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    Py_XDECREF(self->ev_mem);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Validates the PyCSDL2_MouseMotionEvent object.
 *
 * A PyCSDL2_MouseMotionEvent object is valid if it's underlying ev_mem object
 * is not NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_MouseMotionEventValid(PyCSDL2_MouseMotionEvent *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (Py_TYPE(self) != &PyCSDL2_MouseMotionEventType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_MouseMotionEvent", (PyObject*)self);
        return 0;
    }

    if (!self->ev_mem) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_MouseMotionEvent");
        return 0;
    }

    return 1;
}

/** \brief Getter for SDL_MouseMotionEvent.type */
static PyObject *
PyCSDL2_MouseMotionEventGetType(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.motion.type);
}

/** \brief Setter for SDL_MouseMotionEvent.type */
static int
PyCSDL2_MouseMotionEventSetType(PyCSDL2_MouseMotionEvent *self,
                                PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.motion.type);
}

/** \brief Getter for SDL_MouseMotionEvent.timestamp */
static PyObject *
PyCSDL2_MouseMotionEventGetTimestamp(PyCSDL2_MouseMotionEvent *self,
                                     void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.motion.timestamp);
}

/** \brief Setter for SDL_MouseMotionEvent.timestamp */
static int
PyCSDL2_MouseMotionEventSetTimestamp(PyCSDL2_MouseMotionEvent *self,
                                     PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.motion.timestamp);
}

/** \brief Getter for SDL_MouseMotionEvent.windowID */
static PyObject *
PyCSDL2_MouseMotionEventGetWindowID(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.motion.windowID);
}

/** \brief Setter for SDL_MouseMotionEvent.windowID */
static int
PyCSDL2_MouseMotionEventSetWindowID(PyCSDL2_MouseMotionEvent *self,
                                    PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.motion.windowID);
}

/** \brief Getter for SDL_MouseMotionEvent.which */
static PyObject *
PyCSDL2_MouseMotionEventGetWhich(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.motion.which);
}

/** \brief Setter for SDL_MouseMotionEvent.which */
static int
PyCSDL2_MouseMotionEventSetWhich(PyCSDL2_MouseMotionEvent *self,
                                 PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.motion.which);
}

/** \brief Getter for SDL_MouseMotionEvent.state */
static PyObject *
PyCSDL2_MouseMotionEventGetState(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.motion.state);
}

/** \brief Setter for SDL_MouseMotionEvent.state */
static int
PyCSDL2_MouseMotionEventSetState(PyCSDL2_MouseMotionEvent *self,
                                 PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.motion.state);
}

/** \brief Getter for SDL_MouseMotionEvent.x */
static PyObject *
PyCSDL2_MouseMotionEventGetX(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromLong(self->ev_mem->ev.motion.x);
}

/** \brief Setter for SDL_MouseMotionEvent.x */
static int
PyCSDL2_MouseMotionEventSetX(PyCSDL2_MouseMotionEvent *self,
                             PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsSint32(value, &self->ev_mem->ev.motion.x);
}

/** \brief Getter for SDL_MouseMotionEvent.y */
static PyObject *
PyCSDL2_MouseMotionEventGetY(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromLong(self->ev_mem->ev.motion.y);
}

/** \brief Setter for SDL_MouseMotionEvent.y */
static int
PyCSDL2_MouseMotionEventSetY(PyCSDL2_MouseMotionEvent *self,
                             PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsSint32(value, &self->ev_mem->ev.motion.y);
}

/** \brief Getter for SDL_MouseMotionEvent.xrel */
static PyObject *
PyCSDL2_MouseMotionEventGetXRel(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromLong(self->ev_mem->ev.motion.xrel);
}

/** \brief Setter for SDL_MouseMotionEvent.xrel */
static int
PyCSDL2_MouseMotionEventSetXRel(PyCSDL2_MouseMotionEvent *self,
                                PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsSint32(value, &self->ev_mem->ev.motion.xrel);
}

/** \brief Getter for SDL_MouseMotionEvent.yrel */
static PyObject *
PyCSDL2_MouseMotionEventGetYRel(PyCSDL2_MouseMotionEvent *self, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return NULL;
    return PyLong_FromLong(self->ev_mem->ev.motion.yrel);
}

/** \brief Setter for SDL_MouseMotionEvent.yrel */
static int
PyCSDL2_MouseMotionEventSetYRel(PyCSDL2_MouseMotionEvent *self,
                                PyObject *value, void *closure)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyCSDL2_LongAsSint32(value, &self->ev_mem->ev.motion.yrel);
}

/** \brief List of attributes for PyCSDL2_MouseMotionEventType */
static PyGetSetDef PyCSDL2_MouseMotionEventGetSetters[] = {
    {"type",
     (getter) PyCSDL2_MouseMotionEventGetType,
     (setter) PyCSDL2_MouseMotionEventSetType,
     "The event type. Should be set to SDL_MOUSEMOTION.",
     NULL},
    {"timestamp",
     (getter) PyCSDL2_MouseMotionEventGetTimestamp,
     (setter) PyCSDL2_MouseMotionEventSetTimestamp,
     "Timestamp of the event.",
     NULL},
    {"windowID",
     (getter) PyCSDL2_MouseMotionEventGetWindowID,
     (setter) PyCSDL2_MouseMotionEventSetWindowID,
     "The window with mouse focus, if any.",
     NULL},
    {"which",
     (getter) PyCSDL2_MouseMotionEventGetWhich,
     (setter) PyCSDL2_MouseMotionEventSetWhich,
     "The mouse instance ID, or SDL_TOUCH_MOUSEID.",
     NULL},
    {"state",
     (getter) PyCSDL2_MouseMotionEventGetState,
     (setter) PyCSDL2_MouseMotionEventSetState,
     "A 32-bit button bitmask of the current button state.\n"
     "\n"
     "You can test if different buttons are pressed by using the\n"
     "SDL_BUTTON_*MASK mask constants.\n",
     NULL},
    {"x",
     (getter) PyCSDL2_MouseMotionEventGetX,
     (setter) PyCSDL2_MouseMotionEventSetX,
     "Mouse X coordinate, relative to window's origin.",
     NULL},
    {"y",
     (getter) PyCSDL2_MouseMotionEventGetY,
     (setter) PyCSDL2_MouseMotionEventSetY,
     "Mouse Y coordinate, relative to window's origin.",
     NULL},
    {"xrel",
     (getter) PyCSDL2_MouseMotionEventGetXRel,
     (setter) PyCSDL2_MouseMotionEventSetXRel,
     "Relative motion in the X direction.",
     NULL},
    {"yrel",
     (getter) PyCSDL2_MouseMotionEventGetYRel,
     (setter) PyCSDL2_MouseMotionEventSetYRel,
     "Relative motion in the Y direction.",
     NULL},
    {NULL}
};

/** \brief getbufferproc implementation for PyCSDL2_MouseMotionEventType */
static int
PyCSDL2_MouseMotionEventGetBuffer(PyCSDL2_MouseMotionEvent *self,
                                  Py_buffer *view, int flags)
{
    if (!PyCSDL2_MouseMotionEventValid(self))
        return -1;
    return PyBuffer_FillInfo(view, (PyObject*) self, &self->ev_mem->ev.motion,
                             sizeof(SDL_MouseMotionEvent), 0, flags);
}

/** \brief Buffer protocol definition for PyCSDL2_MouseMotionEventType */
static PyBufferProcs PyCSDL2_MouseMotionEventBufferProcs = {
    (getbufferproc) PyCSDL2_MouseMotionEventGetBuffer,
    (releasebufferproc) NULL
};

/** \brief Type definition for csdl2.SDL_MouseMotionEvent */
static PyTypeObject PyCSDL2_MouseMotionEventType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_MouseMotionEvent",
    /* tp_basicsize      */ sizeof(PyCSDL2_MouseMotionEvent),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_MouseMotionEventDealloc,
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
    /* tp_as_buffer      */ &PyCSDL2_MouseMotionEventBufferProcs,
    /* tp_flags          */ Py_TPFLAGS_DEFAULT,
    /* tp_doc            */
    "A structure that contains mouse motion event information.\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_MouseMotionEvent, in_weakreflist),
    /* tp_iter           */ 0,
    /* tp_iternext       */ 0,
    /* tp_methods        */ 0,
    /* tp_members        */ 0,
    /* tp_getset         */ PyCSDL2_MouseMotionEventGetSetters,
    /* tp_base           */ 0,
    /* tp_dict           */ 0,
    /* tp_descr_get      */ 0,
    /* tp_descr_set      */ 0,
    /* tp_dictoffset     */ 0,
    /* tp_init           */ 0,
    /* tp_alloc          */ 0,
    /* tp_new            */ (newfunc) PyCSDL2_MouseMotionEventNew,
};

/**
 * \brief Creates an instance of PyCSDL2_MouseMotionEventType
 *
 * \returns A new PyCSDL2_MouseMotionEvent on success, NULL if an exception
 *          occurred.
 */
static PyObject *
PyCSDL2_MouseMotionEventCreate(const SDL_MouseMotionEvent *ev)
{
    PyCSDL2_MouseMotionEvent *self;
    PyTypeObject *type = &PyCSDL2_MouseMotionEventType;

    if (!PyCSDL2_Assert(ev))
        return NULL;

    self = PyCSDL2_MouseMotionEventNew(type, NULL, NULL);
    if (!self)
        return NULL;

    self->ev_mem->ev.motion = *ev;

    return (PyObject*)self;
}

/**
 * \brief Borrows the SDL_MouseMotionEvent managed by the
 *        PyCSDL2_MouseMotionEvent object.
 *
 * \param obj The PyCSDL2_MouseMotionEvent object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_MouseMotionEventPtr(PyObject *obj, SDL_MouseMotionEvent **out)
{
    PyCSDL2_MouseMotionEvent *self = (PyCSDL2_MouseMotionEvent*)obj;

    if (!PyCSDL2_MouseMotionEventValid(self))
        return 0;

    if (out)
        *out = &self->ev_mem->ev.motion;

    return 1;
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
    /** \brief Object providing view to "motion" attribute of SDL_Event */
    PyCSDL2_MouseMotionEvent *motion;
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
    PyTypeObject *t;

    if (!(self = (PyCSDL2_Event*)type->tp_alloc(type, 0)))
        return NULL;
    if (!(self->ev_mem = PyCSDL2_EventMemCreate())) {
        Py_DECREF(self);
        return NULL;
    }

    t = &PyCSDL2_MouseMotionEventType;
    self->motion = PyCSDL2_MouseMotionEventNew(t, NULL, NULL);
    if (!self->motion)
        goto fail;
    PyCSDL2_Set(self->motion->ev_mem, self->ev_mem);

    return self;

fail:
    Py_DECREF(self);
    return NULL;
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
    Py_XDECREF(self->motion);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/**
 * \brief Validates the PyCSDL2_Event object.
 *
 * A PyCSDL2_Event object is valid if it's underlying ev_mem object is not
 * NULL.
 *
 * \returns 1 if the object is valid, 0 with an exception set otherwise.
 */
static int
PyCSDL2_EventValid(PyCSDL2_Event *self)
{
    if (!PyCSDL2_Assert(self))
        return 0;

    if (!self->ev_mem) {
        PyErr_SetString(PyExc_ValueError, "invalid SDL_Event");
        return 0;
    }

    if (!PyCSDL2_Assert(self->motion))
        return 0;

    return 1;
}

/**
 * \brief Getter for csdl2.SDL_Event.type
 */
static PyObject *
PyCSDL2_EventGetType(PyCSDL2_Event *self, void *closure)
{
    if (!PyCSDL2_EventValid(self))
        return NULL;
    return PyLong_FromUnsignedLong(self->ev_mem->ev.type);
}

/** \brief Setter for csdl2.SDL_Event.type */
static int
PyCSDL2_EventSetType(PyCSDL2_Event *self, PyObject *value, void *closure)
{
    if (!PyCSDL2_EventValid(self))
        return -1;
    return PyCSDL2_LongAsUint32(value, &self->ev_mem->ev.type);
}

/** \brief Getter for SDL_Event.motion */
static PyObject *
PyCSDL2_EventGetMotion(PyCSDL2_Event *self, void *closure)
{
    return PyCSDL2_Get((PyObject*) self->motion);
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
    {"motion",
     (getter) PyCSDL2_EventGetMotion,
     (setter) NULL,
     "(readonly) Mouse motion event data.\n"
     "\n"
     "Use this attribute to access the mouse motion event data when a mouse\n"
     "motion event occurs (event type if SDL_MOUSEMOTION).",
     NULL
    },
    {NULL}
};

/** \brief getbufferproc implementation for PyCSDL2_EventType */
static int
PyCSDL2_EventGetBuffer(PyCSDL2_Event *self, Py_buffer *view, int flags)
{
    if (!PyCSDL2_EventValid(self))
        return -1;
    return PyBuffer_FillInfo(view, (PyObject*) self, &self->ev_mem->ev,
                             sizeof(SDL_Event), 0, flags);
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
 * \brief Creates an instance of PyCSDL2_Event.
 *
 * \param ev SDL_Event to initialize the object with
 * \returns A new PyCSDL2_Event PyObject on success, NULL with an exception set
 *          on failure.
 */
static PyObject *
PyCSDL2_EventCreate(const SDL_Event *ev)
{
    PyTypeObject *type = &PyCSDL2_EventType;
    PyCSDL2_Event *self;

    self = PyCSDL2_EventNew(type, NULL, NULL);
    if (!self)
        return NULL;

    self->ev_mem->ev = *ev;

    return (PyObject*)self;
}

/**
 * \brief Borrows the SDL_Event from a PyCSDL2_Event object.
 *
 * \param obj The PyCSDL2_Event object.
 * \param[out] out Output pointer.
 * \returns 1 on success, 0 with an exception set on failure.
 */
static int
PyCSDL2_EventPtr(PyObject *obj, SDL_Event **out)
{
    PyCSDL2_Event *self = (PyCSDL2_Event*)obj;

    if (!PyCSDL2_Assert(obj) || !PyCSDL2_Assert(out))
        return 0;

    if (Py_TYPE(obj) != &PyCSDL2_EventType) {
        PyCSDL2_RaiseTypeError(NULL, "SDL_Event", obj);
        return 0;
    }

    *out = &self->ev_mem->ev;

    return 1;
}

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

    if (PyCSDL2_PyModuleAddConstants(module, constants) < 0)
        return 0;

    if (PyType_Ready(&PyCSDL2_EventMemType)) { return 0; }

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_MouseMotionEventType) < 0)
        return 0;

    if (PyCSDL2_PyModuleAddType(module, &PyCSDL2_EventType) < 0)
        return 0;

    return 1;
}

#endif /* _PYCSDL2_EVENTS_H_ */
