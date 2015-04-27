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
 * \file methods.h
 * \brief csdl2 list of module methods.
 */
#ifndef _PYCSDL2_METHODS_H_
#define _PYCSDL2_METHODS_H_
#include <Python.h>
#include "../include/pycsdl2.h"
#include "distutils.h"
#include "error.h"
#include "events.h"
#include "init.h"
#include "pixels.h"
#include "rect.h"
#include "render.h"
#include "rwops.h"
#include "surface.h"
#include "video.h"

/**
 * \brief csdl2 methods definitions.
 *
 * \sa PyCSDL2_Module
 */
static PyMethodDef PyCSDL2_Methods[] = {

    /* distutils.h */

    {"PyCSDL2_GetSystemSDL",
     (PyCFunction) PyCSDL2_GetSystemSDL,
     METH_VARARGS | METH_KEYWORDS,
     "PyCSDL2_GetSystemSDL() -> dict or None\n"
     "\n"
     "Returns a dict with the keys 'include_dirs', 'define_macros',\n"
     "'undef_macros', 'extra_compile_args', 'library_dirs', 'libraries',\n"
     "'runtime_library_dirs' and 'extra_link_args' corresponding to\n"
     "attributes of the same name in distutils.extension.Extension which\n"
     "were used to link csdl2 against the system's SDL2 library. Returns\n"
     "None if csdl2 was statically linked to SDL2."},

    /* events.h */

    {"SDL_PumpEvents",
     (PyCFunction) PyCSDL2_PumpEvents,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_PumpEvents() -> None\n"
     "\n"
     "Pumps the event loop, gathering events from the input devices.\n"
     "\n"
     "This function updates the event queue and internal input device\n"
     "state.\n"
     "\n"
     "SDL_PollEvent() and SDL_WaitEvent() implicitly calls this\n"
     "function.\n"
     "\n"
     "This should only be run in the thread that sets the video mode.\n"
    },

    {"SDL_PeepEvents",
     (PyCFunction) PyCSDL2_PeepEvents,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_PeepEvents(events, numevents: int, action: int, minType: int,\n"
     "               maxType: int) -> int\n"
     "\n"
     "If `action` is SDL_ADDEVENT, up to `numevents` events from `events`\n"
     "will be added to the back of the event queue. Returns the number of\n"
     "events added.\n"
     "\n"
     "If `action` is SDL_PEEKEVENT, up to `numevents` events from the front\n"
     "of the event queue, within the specified `minType` and `maxType`, will\n"
     "be returned in `events`, but will not be removed from the queue.\n"
     "Returns the number of events peeked.\n"
     "\n"
     "If `action` is SDL_GETEVENT, up to `numevents` events from the front\n"
     "of the event queue, within the specified `minType` and `maxType`, will\n"
     "be returned in `events`, and removed from the queue. Returns the\n"
     "number of events retrieved.\n"
    },

    {"SDL_FlushEvents",
     (PyCFunction) PyCSDL2_FlushEvents,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FlushEvents(minType: int, maxType: int) -> None\n"
     "\n"
     "Removes all events from the event queue within the specified `minType`\n"
     "and `maxType`.\n"
     "\n"
     "This function only affects currently queued events. If you wish to\n"
     "make sure that all pending OS events are flushed, you can call\n"
     "SDL_PumpEvents() on the main thread immediately before\n"
     "SDL_FlushEvents().\n"
    },

    {"SDL_PollEvent",
     (PyCFunction) PyCSDL2_PollEvent,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_PollEvent(event) -> bool\n"
     "\n"
     "Polls for currently pending events.\n"
     "\n"
     "If `event` is not None, the next event is removed from the queue and\n"
     "stored in `event`.\n"
     "\n"
     "If `event` is None, no event will be removed from the queue.\n"
     "\n"
     "Returns True if there are events in the queue, False otherwise.\n"
    },

    {"SDL_PushEvent",
     (PyCFunction) PyCSDL2_PushEvent,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_PushEvent(event) -> bool\n"
     "\n"
     "Copies `event` into the event queue. Returns True on success, or False\n"
     "if the event was filtered.\n"
     "\n"
     "For pushing application-specific events, please use\n"
     "SDL_RegisterEvents() to get an event type that does not conflict with\n"
     "other code that also wants its own custom event types.\n"
    },

    /* init.h */

    {"SDL_Init",
     (PyCFunction) PyCSDL2_Init,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_Init(flags: int) -> None\n"
     "\n"
     "Initializes the subsystems specified by `flags`, which is one or more\n"
     "of the following constants OR'ed together:\n"
     "\n"
     "* SDL_INIT_TIMER\n"
     "* SDL_INIT_AUDIO\n"
     "* SDL_INIT_VIDEO (implies SDL_INIT_EVENTS)\n"
     "* SDL_INIT_JOYSTICK (implies SDL_INIT_EVENTS)\n"
     "* SDL_INIT_HAPTIC\n"
     "* SDL_INIT_GAMECONTROLLER (implies SDL_INIT_JOYSTICK)\n"
     "* SDL_INIT_EVENTS\n"
     "\n"
     "Alternatively, pass SDL_INIT_EVERYTHING to initialize all subsystems.\n"
     "\n"
     "Unless the SDL_INIT_NOPARACHUTE flag is set, it will install cleanup\n"
     "signal handlers for some commonly ignored fatal signals like SIGSEGV.\n"
    },

    /* pixels.h */

    {"SDL_AllocFormat",
     (PyCFunction) PyCSDL2_AllocFormat,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_AllocFormat(pixel_format: int) -> SDL_PixelFormat\n"
     "\n"
     "Returns a SDL_PixelFormat corresponding to `pixel_format`, where\n"
     "`pixel_format` is one of the SDL_PIXELFORMAT_* constants.\n"
    },

    {"SDL_FreeFormat",
     (PyCFunction) PyCSDL2_FreeFormat,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FreeFormat(format: SDL_PixelFormat) -> None\n"
     "\n"
     "Frees the SDL_PixelFormat `format`.\n"
     "\n"
     "There is no need to manually call this function. SDL_PixelFormat will\n"
     "automatically call this function as part of its destructor.\n"
    },

    {"SDL_AllocPalette",
     (PyCFunction) PyCSDL2_AllocPalette,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_AllocPalette(ncolors: int) -> SDL_Palette\n"
     "\n"
     "Returns a new SDL_Palette with `ncolors` number of colors.\n"
     "\n"
     "The color values are initialized to white.\n"
    },

    {"SDL_FreePalette",
     (PyCFunction) PyCSDL2_FreePalette,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FreePalette(palette: SDL_Palette) -> None\n"
     "\n"
     "Frees the SDL_Palette `palette`.\n"
     "\n"
     "There is no need to manually call this function. SDL_Palette will\n"
     "automatically call this function as part of its destructor.\n"
    },

    /* rect.h */

    {"SDL_HasIntersection",
     (PyCFunction) PyCSDL2_HasIntersection,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_HasIntersection(A: SDL_Rect, B: SDL_Rect) -> bool\n"
     "\n"
     "Returns True if rectangles `A` and `B` are intersecting, False\n"
     "otherwise. If either argument is None the function will return\n"
     "False.\n"
    },

    /* render.h */

    {"SDL_CreateRenderer",
     (PyCFunction) PyCSDL2_CreateRenderer,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateRenderer(window: SDL_Window, index: int, flags: int)\n"
     "    -> SDL_Renderer\n"
     "\n"
     "Creates a SDL_Renderer for `window`. `index` is the index of the\n"
     "rendering driver to initialize, or -1 to initialize the first one\n"
     "supporting `flags`. `flags` can be 0, or one or more SDL_RENDERER_*\n"
     "flags OR'ed together.\n"
    },

    {"SDL_CreateSoftwareRenderer",
     (PyCFunction) PyCSDL2_CreateSoftwareRenderer,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateSoftwareRenderer(surface: SDL_Surface) -> SDL_Renderer\n"
     "\n"
     "Creates a SDL_Renderer for `surface`.\n"
    },

    {"SDL_SetRenderDrawColor",
     (PyCFunction) PyCSDL2_SetRenderDrawColor,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: int, g: int, b: int,\n"
     "                       a: int) -> None\n"
     "\n"
     "Sets the color used for drawing primitives and for SDL_RenderClear()\n"
    },

    {"SDL_DestroyRenderer",
     (PyCFunction) PyCSDL2_DestroyRenderer,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_DestroyRenderer(renderer: SDL_Renderer) -> None\n"
     "\n"
     "Destroys `renderer`, freeing up its associated SDL_Texture's and\n"
     "resources.\n"
     "\n"
     "There is no need to manually call this function. SDL_Renderer will\n"
     "automatically call this function as part of its destructor.\n"
     "\n"
     "Once destroyed, do not access the renderer. Doing so will at best\n"
     "raise errors and at worse crash the interpreter.\n"
    },

    /* rwops.h */

    {"SDL_RWFromFile",
     (PyCFunction) PyCSDL2_RWFromFile,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWFromFile(file: str, mode: str) -> SDL_RWops\n"
     "\n"
     "Creates a SDL_RWops for reading from and/or writing to `file`.\n"
     "\n"
     "`mode` is one of the following:\n"
     "\n"
     "* 'r'  -- Open a file for reading. The file must exist.\n"
     "* 'w'  -- Create an empty file for writing. If a file with the same\n"
     "  name already exists its content is erased and the file is treated\n"
     "  as a new empty file.\n"
     "* 'a'  -- Append to a file. Writing operations append data at the end\n"
     "  of the file. The file is created if it does not exist.\n"
     "* 'r+' -- Open a file for both reading and writing. The file must\n"
     "  exist.\n"
     "* 'w+' -- Create an empty file for both reading and writing. If a file\n"
     "  with the same name already exists its contents are erased and the\n"
     "  file is treated as a new empty file.\n"
     "* 'a+' -- Open a file for reading and appending. All writing\n"
     "  operations are performed at the end of the file. You can seek the\n"
     "  internal pointer to anywhere in the file for reading, but writing\n"
     "  operations will move it back to the end of the file. The file is\n"
     "  created if it does not exist.\n"
    },

    {"SDL_AllocRW",
     (PyCFunction) PyCSDL2_AllocRW,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_AllocRW() -> SDL_RWops\n"
     "\n"
     "Allocates and returns a new SDL_RWops structure.\n"
    },

    {"SDL_FreeRW",
     (PyCFunction) PyCSDL2_FreeRW,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FreeRW(area: SDL_RWops) -> None\n"
     "\n"
     "Frees a SDL_RWops structure allocated by SDL_AllocRW()\n"
    },

    /* surface.h */

    {"SDL_MUSTLOCK",
     (PyCFunction) PyCSDL2_MUSTLOCK,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_MUSTLOCK(surface: SDL_Surface) -> bool\n"
     "\n"
     "Returns True if `surface` needs to be locked before access.\n"
    },

    {"SDL_CreateRGBSurface",
     (PyCFunction) PyCSDL2_CreateRGBSurface,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateRGBSurface(flags: int, width: int, height: int, depth: int,\n"
     "                     Rmask: int, Gmask: int, Bmask: int, Amask: int)\n"
     "                    -> SDL_Surface\n"
     "\n"
     "Creates and returns a new SDL_Surface with the specified properties:\n"
     "\n"
     "flags\n"
     "    The flags are unused and should be set to 0.\n"
     "\n"
     "width\n"
     "    The width of the surface in pixels.\n"
     "\n"
     "height\n"
     "    The height of the surface in pixels.\n"
     "\n"
     "depth\n"
     "    The depth of the surface in bits. If `depth` is 4 or 8 bits, an\n"
     "    empty palette is allocated for the surface. If `depth` is greater\n"
     "    than 8 bits, the pixel format is set using the `[RGBA]mask`\n"
     "    parameters.\n"
     "\n"
     "Rmask, Gmask, Bmask, Amask\n"
     "    These parameters are the bitmasks used to extract that color from\n"
     "    a pixel. Setting them to 0 sets a default value based on the\n"
     "    depth. Setting `Amask` to 0 results in an `Amask` of 0.\n"
    },

    {"SDL_CreateRGBSurfaceFrom",
     (PyCFunction) PyCSDL2_CreateRGBSurfaceFrom,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateRGBSurfaceFrom(pixels: buffer, width: int, height: int,\n"
     "                         depth: int, pitch: int, Rmask: int,\n"
     "                         Gmask: int, Bmask: int, Amask: int)\n"
     "    -> SDL_Surface\n"
     "\n"
     "Creates and returns a new SDL_Surface with the specified properties:\n"
     "\n"
     "pixels\n"
     "    A buffer containing the pixel data.\n"
     "\n"
     "width\n"
     "    The width of the surface in pixels.\n"
     "\n"
     "height\n"
     "    The height of the surface in pixels.\n"
     "\n"
     "depth\n"
     "    The depth of the surface in bits. If `depth` is 4 or 8 bits, an\n"
     "    empty palette is allocated for the surface. If `depth` is greater\n"
     "    than 8 bits, the pixel format is set using the `[RGBA]mask`\n"
     "    parameters.\n"
     "\n"
     "Rmask, Gmask, Bmask, Amask\n"
     "    These parameters are the bitmasks used to extract that color from\n"
     "    a pixel. Setting them to 0 sets a default value based on the\n"
     "    depth. Setting `Amask` to 0 results in an `Amask` of 0.\n"
    },

    {"SDL_FreeSurface",
     (PyCFunction) PyCSDL2_FreeSurface,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FreeSurface(surface: SDL_Surface) -> None\n"
     "\n"
     "Frees the surface.\n"
     "\n"
     "There is no need to manually call this function. SDL_Surface will\n"
     "automatically call this function as part of its destructor.\n"
     "\n"
     "Once freed, do not access the surface. Doing so will at best raise\n"
     "errors and at worse crash the interpreter.\n"
    },

    /* video.h */

    {"SDL_CreateWindow",
     (PyCFunction) PyCSDL2_CreateWindow,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateWindow(title: str, x: int, y: int, w: int, h: int,\n"
     "                 flags: int) -> SDL_Window\n"
     "\n"
     "Create a window with the specified `title`, position (`x`, `y`),\n"
     "dimensions `w` x `h`, and flags `flags`.\n"
     "\n"
     "`flags` can be one or more of following OR'ed together:\n"
     "`SDL_WINDOW_FULLSCREEN`, `SDL_WINDOW_OPENGL`, `SDL_WINDOW_SHOWN`,\n"
     "`SDL_WINDOW_HIDDEN`, `SDL_WINDOW_BORDERLESS`, `SDL_WINDOW_RESIZABLE`,\n"
     "`SDL_WINDOW_RESIZABLE`, `SDL_WINDOW_MINIMIZED`,\n"
     "`SDL_WINDOW_MAXIMIZED`, `SDL_WINDOW_INPUT_GRABBED`,\n"
     "`SDL_WINDOW_INPUT_FOCUS`, `SDL_WINDOW_MOUSE_FOCUS`,\n"
     "`SDL_WINDOW_FULLSCREEN_DESKTOP`.\n"},

    {"SDL_DestroyWindow",
     (PyCFunction) PyCSDL2_DestroyWindow,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_DestroyWindow(window: SDL_Surface) -> None\n"
     "\n"
     "Destroys a window, freeing up its resources.\n"
     "\n"
     "There is no need to manually call this function. SDL_Window will\n"
     "automatically call it as part of its destructor.\n"
     "\n"
     "Once destroyed, do not access the window. Doing so will at best raise\n"
     "errors and at worse crash the interpreter.\n"
    },

    /* End */
    {0}
};

#endif /* _PYCSDL2_METHODS_H_ */
