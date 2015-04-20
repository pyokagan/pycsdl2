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

    return 1;
}

#endif /* _PYCSDL2_EVENTS_H_ */
