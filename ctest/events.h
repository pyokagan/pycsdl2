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
 * \brief Tests for csdl2's SDL_events bindings.
 */
#ifndef _PYCSDL2TEST_EVENTS_H_
#define _PYCSDL2TEST_EVENTS_H_
#include <Python.h>
#include <SDL_events.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_MouseMotionEvent object.
 *
 * \code{.py}
 * mouse_motion_event() -> SDL_MouseMotionEvent
 * \endcode
 */
static PyObject *
PyCSDL2Test_MouseMotionEvent(PyObject *module, PyObject *args)
{
    SDL_MouseMotionEvent motion;

    motion.type = 1;
    motion.timestamp = 2;
    motion.windowID = 3;
    motion.which = 4;
    motion.state = 5;
    motion.x = 6;
    motion.y = 7;
    motion.xrel = 8;
    motion.yrel = 9;

    return PyCSDL2_MouseMotionEventCreate(&motion);
}

/**
 * \brief Sets the "type" of a SDL_MouseMotionEvent to 42.
 *
 * \code{.py}
 * mouse_motion_event_set_type(ev: SDL_MouseMotionEvent) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_MouseMotionEventSetType(PyObject *module, PyObject *args)
{
    SDL_MouseMotionEvent *ev;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_MouseMotionEventPtr, &ev))
        return NULL;

    ev->type = 42;

    Py_RETURN_NONE;
}

/**
 * \brief Creates a PyCSDL2_Event object.
 *
 * \code{.py}
 * event() -> SDL_Event
 * \endcode
 */
static PyObject *
PyCSDL2Test_Event(PyObject *module, PyObject *args)
{
    SDL_Event ev;

    ev.type = 1;

    return PyCSDL2_EventCreate(&ev);
}

/**
 * \brief Sets the "type" field of a SDL_Event to 42.
 *
 * \code{.py}
 * event_set_type(ev: SDL_Event) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_EventSetType(PyObject *module, PyObject *args)
{
    SDL_Event *ev;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_EventPtr, &ev))
        return NULL;

    ev->type = 42;

    Py_RETURN_NONE;
}

#endif /* _PYCSDL2TEST_EVENTS_H_ */
