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
 * \file video.h
 * \brief Bindings for SDL_video.h.
 *
 * Implements bindings for SDL's display and window management API
 * (SDL_video.h).
 */
#ifndef _PYCSDL2_VIDEO_H_
#define _PYCSDL2_VIDEO_H_
#include <Python.h>
#include <SDL_video.h>
#include "../include/pycsdl2.h"
#include "util.h"
#include "error.h"

/** \brief Instance data of PyCSDL2_WindowType */
typedef struct PyCSDL2_Window {
    PyObject_HEAD
    /** \brief Head of weak reference list */
    PyObject *in_weakreflist;
    /** \brief SDL_Window handle which this instance owns */
    SDL_Window *window;
} PyCSDL2_Window;

/** \brief Destructor for PyCSDL2_WindowType */
static void
PyCSDL2_WindowDealloc(PyCSDL2_Window *self)
{
    PyObject_ClearWeakRefs((PyObject*) self);
    if (self->window)
        SDL_DestroyWindow(self->window);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

/** \brief Type definition of csdl2.SDL_Window */
static PyTypeObject PyCSDL2_WindowType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    /* tp_name           */ "csdl2.SDL_Window",
    /* tp_basicsize      */ sizeof(PyCSDL2_Window),
    /* tp_itemsize       */ 0,
    /* tp_dealloc        */ (destructor) PyCSDL2_WindowDealloc,
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
    /* tp_doc            */
    "A Window.\n"
    "\n"
    "This is an opaque handle that cannot be directly constructed. To create\n"
    "one, use SDL_CreateWindow().\n",
    /* tp_traverse       */ 0,
    /* tp_clear          */ 0,
    /* tp_richcompare    */ 0,
    /* tp_weaklistoffset */ offsetof(PyCSDL2_Window, in_weakreflist)
};

/**
 * \brief Creates a new instance of PyCSDL2_WindowType
 *
 * \param window SDL_Window to manage. The new instance will steal the
 *               SDL_Window reference.
 * \returns Pointer to PyCSDL2_Window on success, NULL if an exception
 *          occurred.
 */
static PyCSDL2_Window *
PyCSDL2_WindowCreate(SDL_Window *window)
{
    PyCSDL2_Window *self;
    PyTypeObject *type = &PyCSDL2_WindowType;

    PyCSDL2_Assert(window);
    if (!(self = (PyCSDL2_Window*) type->tp_alloc(type, 0)))
        return NULL;
    self->window = window;
    return self;
}

/**
 * \brief Implements csdl2.SDL_CreateWindow()
 *
 * \code{.py}
 * SDL_CreateWindow(title: str, x: int, y: int, w: int, h: int, flags: int)
 *     -> SDL_Window
 * \endcode
 *
 * \returns New instance of PyCSDL2_Window* on success, or NULL if an exception
 *          occurred.
 */
static PyCSDL2_Window *
PyCSDL2_CreateWindow(PyObject *module, PyObject *args, PyObject *kwds)
{
    const char *title;
    int x, y, w, h;
    Uint32 flags;
    static char *kwlist[] = {"title", "x", "y", "w", "h", "flags", NULL};
    SDL_Window *window;
    PyCSDL2_Window *out;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "siiii" Uint32_UNIT, kwlist,
        &title, &x, &y, &w, &h, &flags))
        return NULL;
    if (!(window = SDL_CreateWindow(title, x, y, w, h, flags)))
        return PyCSDL2_RaiseSDLError();
    if (!(out = PyCSDL2_WindowCreate(window))) {
        SDL_DestroyWindow(window);
        return NULL;
    }
    return out;
}

/**
 * \brief Implements csdl2.SDL_DestroyWindow()
 *
 * \code{.py}
 * SDL_DestroyWindow(window: SDL_Window) -> None
 * \endcode
 */
static PyObject *
PyCSDL2_DestroyWindow(PyObject *module, PyObject *args, PyObject *kwds)
{
    PyCSDL2_Window *window;
    static char *kwlist[] = {"window", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist,
                                     &PyCSDL2_WindowType, &window))
        return NULL;
    PyCSDL2_Assert(window->window);
    SDL_DestroyWindow(window->window);
    window->window = NULL;
    Py_RETURN_NONE;
}

/**
 * \brief Initializes bindings to SDL_video.h
 *
 * \param m csdl2 module PyObject
 * \returns 1 on success, 0 if an exception occurred.
 */
static int
PyCSDL2_initvideo(PyObject *m)
{
    static const PyCSDL2_Constant constants[] = {
        /* SDL_WindowFlags */
        {"SDL_WINDOW_FULLSCREEN", SDL_WINDOW_FULLSCREEN},
        {"SDL_WINDOW_OPENGL", SDL_WINDOW_OPENGL},
        {"SDL_WINDOW_SHOWN", SDL_WINDOW_SHOWN},
        {"SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN},
        {"SDL_WINDOW_BORDERLESS", SDL_WINDOW_BORDERLESS},
        {"SDL_WINDOW_RESIZABLE", SDL_WINDOW_RESIZABLE},
        {"SDL_WINDOW_MINIMIZED", SDL_WINDOW_MINIMIZED},
        {"SDL_WINDOW_MAXIMIZED", SDL_WINDOW_MAXIMIZED},
        {"SDL_WINDOW_INPUT_GRABBED", SDL_WINDOW_INPUT_GRABBED},
        {"SDL_WINDOW_INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS},
        {"SDL_WINDOW_MOUSE_FOCUS", SDL_WINDOW_MOUSE_FOCUS},
        {"SDL_WINDOW_FULLSCREEN_DESKTOP", SDL_WINDOW_FULLSCREEN_DESKTOP},
        {"SDL_WINDOW_FOREIGN", SDL_WINDOW_FOREIGN},

        {"SDL_WINDOWPOS_UNDEFINED_MASK", SDL_WINDOWPOS_UNDEFINED_MASK},
        {"SDL_WINDOWPOS_UNDEFINED", SDL_WINDOWPOS_UNDEFINED},

        {"SDL_WINDOWPOS_CENTERED_MASK", SDL_WINDOWPOS_CENTERED_MASK},
        {"SDL_WINDOWPOS_CENTERED", SDL_WINDOWPOS_CENTERED},

        /* SDL_WindowEventID */
        {"SDL_WINDOWEVENT_NONE", SDL_WINDOWEVENT_NONE},
        {"SDL_WINDOWEVENT_SHOWN", SDL_WINDOWEVENT_SHOWN},
        {"SDL_WINDOWEVENT_HIDDEN", SDL_WINDOWEVENT_HIDDEN},
        {"SDL_WINDOWEVENT_EXPOSED", SDL_WINDOWEVENT_EXPOSED},
        {"SDL_WINDOWEVENT_MOVED", SDL_WINDOWEVENT_MOVED},
        {"SDL_WINDOWEVENT_RESIZED", SDL_WINDOWEVENT_RESIZED},
        {"SDL_WINDOWEVENT_SIZE_CHANGED", SDL_WINDOWEVENT_SIZE_CHANGED},
        {"SDL_WINDOWEVENT_MINIMIZED", SDL_WINDOWEVENT_MINIMIZED},
        {"SDL_WINDOWEVENT_MAXIMIZED", SDL_WINDOWEVENT_MAXIMIZED},
        {"SDL_WINDOWEVENT_RESTORED", SDL_WINDOWEVENT_RESTORED},
        {"SDL_WINDOWEVENT_ENTER", SDL_WINDOWEVENT_ENTER},
        {"SDL_WINDOWEVENT_LEAVE", SDL_WINDOWEVENT_LEAVE},
        {"SDL_WINDOWEVENT_FOCUS_GAINED", SDL_WINDOWEVENT_FOCUS_GAINED},
        {"SDL_WINDOWEVENT_FOCUS_LOST", SDL_WINDOWEVENT_FOCUS_LOST},
        {"SDL_WINDOWEVENT_CLOSE", SDL_WINDOWEVENT_CLOSE},

        /* SDL_GLattr */
        {"SDL_GL_RED_SIZE", SDL_GL_RED_SIZE},
        {"SDL_GL_GREEN_SIZE", SDL_GL_GREEN_SIZE},
        {"SDL_GL_BLUE_SIZE", SDL_GL_BLUE_SIZE},
        {"SDL_GL_ALPHA_SIZE", SDL_GL_ALPHA_SIZE},
        {"SDL_GL_BUFFER_SIZE", SDL_GL_BUFFER_SIZE},
        {"SDL_GL_DOUBLEBUFFER", SDL_GL_DOUBLEBUFFER},
        {"SDL_GL_DEPTH_SIZE", SDL_GL_DEPTH_SIZE},
        {"SDL_GL_STENCIL_SIZE", SDL_GL_STENCIL_SIZE},
        {"SDL_GL_ACCUM_RED_SIZE", SDL_GL_ACCUM_RED_SIZE},
        {"SDL_GL_ACCUM_GREEN_SIZE", SDL_GL_ACCUM_GREEN_SIZE},
        {"SDL_GL_ACCUM_BLUE_SIZE", SDL_GL_ACCUM_BLUE_SIZE},
        {"SDL_GL_ACCUM_ALPHA_SIZE", SDL_GL_ACCUM_ALPHA_SIZE},
        {"SDL_GL_STEREO", SDL_GL_STEREO},
        {"SDL_GL_MULTISAMPLEBUFFERS", SDL_GL_MULTISAMPLEBUFFERS},
        {"SDL_GL_MULTISAMPLESAMPLES", SDL_GL_MULTISAMPLESAMPLES},
        {"SDL_GL_ACCELERATED_VISUAL", SDL_GL_ACCELERATED_VISUAL},
        {"SDL_GL_RETAINED_BACKING", SDL_GL_RETAINED_BACKING},
        {"SDL_GL_CONTEXT_MAJOR_VERSION", SDL_GL_CONTEXT_MAJOR_VERSION},
        {"SDL_GL_CONTEXT_MINOR_VERSION", SDL_GL_CONTEXT_MINOR_VERSION},
        {"SDL_GL_CONTEXT_EGL", SDL_GL_CONTEXT_EGL},
        {"SDL_GL_CONTEXT_FLAGS", SDL_GL_CONTEXT_FLAGS},
        {"SDL_GL_CONTEXT_PROFILE_MASK", SDL_GL_CONTEXT_PROFILE_MASK},
        {"SDL_GL_SHARE_WITH_CURRENT_CONTEXT",
         SDL_GL_SHARE_WITH_CURRENT_CONTEXT},

        /* SDL_GLprofile */
        {"SDL_GL_CONTEXT_PROFILE_CORE", SDL_GL_CONTEXT_PROFILE_CORE},
        {"SDL_GL_CONTEXT_PROFILE_COMPATIBILITY",
         SDL_GL_CONTEXT_PROFILE_COMPATIBILITY},
        {"SDL_GL_CONTEXT_PROFILE_ES", SDL_GL_CONTEXT_PROFILE_ES},

        /* SDL_GLcontextFlag */
        {"SDL_GL_CONTEXT_DEBUG_FLAG", SDL_GL_CONTEXT_DEBUG_FLAG},
        {"SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG",
         SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG},
        {"SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG",
         SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG},
        {"SDL_GL_CONTEXT_RESET_ISOLATION_FLAG",
         SDL_GL_CONTEXT_RESET_ISOLATION_FLAG},

        {NULL, 0}
    };
    const PyCSDL2_Constant *c;
    for (c = constants; c->name; c++)
        if (PyModule_AddIntConstant(m, c->name, c->value))
            return 0;

    if (PyType_Ready(&PyCSDL2_WindowType)) { return 0; }
    Py_INCREF(&PyCSDL2_WindowType);
    if (PyModule_AddObject(m, "SDL_Window", (PyObject*) &PyCSDL2_WindowType))
        return 0;

    return 1;
}

#endif /* _PYCSDL2_VIDEO_H_ */
