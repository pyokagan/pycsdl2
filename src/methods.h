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

    /* audio.h */

    {"SDL_OpenAudioDevice",
     (PyCFunction) PyCSDL2_OpenAudioDevice,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_OpenAudioDevice(device: str or None, iscapture: bool,\n"
     "                    desired: SDL_AudioSpec,\n"
     "                    obtained: SDL_AudioSpec or None,\n"
     "                    allowed_changes: int) -> SDL_AudioDevice\n"
     "\n"
     "Opens a specific audio device.\n"
     "\n"
     "device\n"
     "    The device name as reported by SDL_GetAudioDeviceName(). If None,\n"
     "    the default device is used.\n"
     "\n"
     "iscapture\n"
     "    True to specify the device should be obtained for recording, not\n"
     "    playback.\n"
     "\n"
     "desired\n"
     "    A SDL_AudioSpec specifying the audio callback and desired output\n"
     "    format.\n"
     "\n"
     "obtained\n"
     "    If a SDL_AudioSpec is provided, it will be filled in with the\n"
     "    actual output format. Depending on the value of `allowed_changes`,\n"
     "    this can differ from the `desired` SDL_AudioSpec.\n"
     "\n"
     "allowed_changes\n"
     "    If set to 0, SDL will transparently handle all differences between\n"
     "    the `desired` output format and the actual hardware. This handling\n"
     "    can be selectively disabled by specifying zero or more of the\n"
     "    following flags OR'd together:\n"
     "\n"
     "    * SDL_AUDIO_ALLOW_FREQUENCY_CHANGE\n"
     "    * SDL_AUDIO_ALLOW_FORMAT_CHANGE\n"
     "    * SDL_AUDIO_ALLOW_CHANNELS_CHANGE\n"
     "    * SDL_AUDIO_ALLOW_ANY_CHANGE\n"
     "\n"
     "    If these flags are set, the corresponding fields in the `obtained`\n"
     "    SDL_AudioSpec will be set to the values of the actual hardware\n"
     "    audio output format.\n"
     "\n"
     "Newly-opened audio devices start in the paused state. Use\n"
     "SDL_PauseAudioDevice() to unpause the device and start playing\n"
     "sound.\n"
    },

    {"SDL_PauseAudioDevice",
     (PyCFunction) PyCSDL2_PauseAudioDevice,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_PauseAudioDevice(dev: SDL_AudioDevice, pause_on: bool) -> None\n"
     "\n"
     "Pause or unpause audio playback on the specified device. If `pause_on`\n"
     "is True, the device `dev` will be paused, and if `pause_on` is False,\n"
     "the device `dev` will be unpaused.\n"
     "\n"
     "When the device is paused, silence will be written to the audio device\n"
     "and the audio callback is guaranteed to not be called.\n"
    },

    {"SDL_LoadWAV_RW",
     (PyCFunction) PyCSDL2_LoadWAV_RW,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_LoadWAV_RW(src: SDL_RWops, freesrc: bool)\n"
     "    -> (SDL_AudioSpec, buffer, int)\n"
     "\n"
     "Loads a WAVE from the SDL_RWops data source. Returns a 3-tuple\n"
     "containing a SDL_AudioSpec, a byte buffer, and the buffer's size in\n"
     "bytes as an integer. The SDL_AudioSpec is filled with the audio data\n"
     "format of the wave source data, and the byte buffer contains the audio\n"
     "data. If `freesrc` is True, the data source will be freed.\n"
    },

    {"SDL_LoadWAV",
     (PyCFunction) PyCSDL2_LoadWAV,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_LoadWAV(file: str) -> (SDL_AudioSpec, buffer, int)\n"
     "\n"
     "Loads a WAVE from `file`. Returns a 3-tuple containing a\n"
     "SDL_AudioSpec, a byte buffer and the buffer's size in bytes as an\n"
     "integer. The SDL_AudioSpec is filled with the audio data format of\n"
     "the wave source data, and the byte buffer contains the audio data.\n"
    },

    {"SDL_FreeWAV",
     (PyCFunction) PyCSDL2_FreeWAV,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_FreeWAV(audio_buf) -> None\n"
     "\n"
     "Frees the wave data buffer allocated by SDL_LoadWAV() or\n"
     "SDL_LoadWAV_RW().\n"
     "\n"
     "There is no need to explicitly call this function. The buffer returned\n"
     "by SDL_LoadWAV() or SDL_LoadWAV_RW() will automatically call this\n"
     "function as part of its destructor.\n"
    },

    {"SDL_CloseAudioDevice",
     (PyCFunction) PyCSDL2_CloseAudioDevice,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CloseAudioDevice(dev: SDL_AudioDevice) -> None\n"
     "\n"
     "Shuts down audio processing and closes the specified device.\n"
     "\n"
     "There is no need to explictly call this function. SDL_AudioDevice will\n"
     "automatically call this function as part of its destructor.\n"
    },

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

    {"SDL_CreateTexture",
     (PyCFunction) PyCSDL2_CreateTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateTexture(renderer: SDL_Renderer, format: int, access: int,\n"
     "                  w: int, h: int) -> SDL_Texture\n"
     "\n"
     "Creates a texture for a rendering context with the specified\n"
     "properties:\n"
     "\n"
     "renderer\n"
     "    The rendering context.\n"
     "\n"
     "format\n"
     "    One of the SDL_PIXELFORMAT_* constants. Defines the pixel format\n"
     "    of the texture.\n"
     "\n"
     "access\n"
     "    One of the SDL_TEXTUREACCESS_* constants. Defines how the texture\n"
     "    can be accessed:\n"
     "\n"
     "    * SDL_TEXTUREACCESS_STATIC -- changes rarely, not lockable.\n"
     "    * SDL_TEXTUREACCESS_STREAMING -- changes frequently, lockable.\n"
     "    * SDL_TEXTUREACCESS_TARGET -- can be used as a render target.\n"
     "\n"
     "w\n"
     "    Width of the texture in pixels.\n"
     "\n"
     "h\n"
     "    Height of the texture in pixels.\n"
    },

    {"SDL_CreateTextureFromSurface",
     (PyCFunction) PyCSDL2_CreateTextureFromSurface,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_CreateTextureFromSurface(renderer: SDL_Renderer,\n"
     "                             surface: SDL_Surface) -> SDL_Texture\n"
     "\n"
     "Creates a texture for a rendering context with the pixel data of an\n"
     "existing surface.\n"
     "\n"
     "The surface is not modified or freed by this function. The texture\n"
     "will be created with SDL_TEXTUREACCESS_STATIC.\n"
    },

    {"SDL_QueryTexture",
     (PyCFunction) PyCSDL2_QueryTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_QueryTexture(texture: SDL_Texture) -> (int, int, int, int)\n"
     "\n"
     "Query the attributes of a texture, returning a (int, int, int, int)\n"
     "tuple with the following:\n"
     "\n"
     "* The texture's raw pixel format. One of the SDL_PIXELFORMAT_*\n"
     "  constants.\n"
     "* The texture's access. One of the SDL_TEXTUREACCESS_* constants.\n"
     "* The texture's width, in pixels.\n"
     "* The texture's height, in pixels.\n"
    },

    {"SDL_SetTextureColorMod",
     (PyCFunction) PyCSDL2_SetTextureColorMod,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_SetTextureColorMod(texture: SDL_Texture, r: int, g: int, b: int)\n"
     "    -> None\n"
     "\n"
     "Sets an additional color value (r, g, b) used in render copy\n"
     "operations.\n"
     "\n"
     "When the texture is rendered, during the copy operation each source\n"
     "color channel is modulated by the appropriate color value according\n"
     "to the following formula:\n"
     "\n"
     "    srcC = srcC * (color / 255)\n"
    },

    {"SDL_GetTextureColorMod",
     (PyCFunction) PyCSDL2_GetTextureColorMod,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_GetTextureColorMod(texture: SDL_Texture) -> (int, int, int)\n"
     "\n"
     "Returns the additional color value (r, hg, b) multiplied into render\n"
     "copy operations.\n"
    },

    {"SDL_SetTextureAlphaMod",
     (PyCFunction) PyCSDL2_SetTextureAlphaMod,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_SetTextureAlphaMod(texture: SDL_Texture, alpha: int) -> None\n"
     "\n"
     "Sets an additional alpha value multiplied into render copy operations.\n"
     "The alpha value must be within the range 0-255.\n"
     "\n"
     "When the texture is rendered, during the copy operation the source\n"
     "alpha value would be modulated by this alpha value according to the\n"
     "following formula:\n"
     "\n"
     "    srcA - srcA * (alpha / 255)\n"
    },

    {"SDL_GetTextureAlphaMod",
     (PyCFunction) PyCSDL2_GetTextureAlphaMod,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_GetTextureAlphaMod(texture: SDL_Texture) -> int\n"
     "\n"
     "Returns the additional alpha value multiplied into render copy\n"
     "operations. It is within the range 0-255.\n"
    },

    {"SDL_SetTextureBlendMode",
     (PyCFunction) PyCSDL2_SetTextureBlendMode,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_SetTextureBlendMode(texture: SDL_Texture, blendMode: int) -> None\n"
     "\n"
     "Sets the blend mode for a texture, where `blendMode` is one of:\n"
     "\n"
     "SDL_BLENDMODE_NONE:\n"
     "    No blending.\n"
     "    dstRGBA = srcRGBA\n"
     "\n"
     "SDL_BLENDMODE_ADD:\n"
     "    Alpha blending.\n"
     "    dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))\n"
     "    dstA = srcA + (dstA * (1-srcA))\n"
     "\n"
     "SDL_BLENDMODE_ADD:\n"
     "    Additive blending.\n"
     "    dstRGB = (srcRGB * srcA) + dstRGB\n"
     "    dstA = dstA\n"
     "\n"
     "SDL_BLENDMODE_MOD:\n"
     "    Color modulate.\n"
     "    dstRGB = srcRGB * dstRGB\n"
     "    dstA = dstA\n"
    },

    {"SDL_GetTextureBlendMode",
     (PyCFunction) PyCSDL2_GetTextureBlendMode,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_GetTextureBlendMode(texture: SDL_Texture) -> int\n"
     "\n"
     "Returns the blend mode used for texture copy operations. It is one of\n"
     "the SDL_BLENDMODE_* constants.\n"
    },

    {"SDL_UpdateTexture",
     (PyCFunction) PyCSDL2_UpdateTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_UpdateTexture(texture: SDL_Texture, rect: SDL_Rect, pixels: buffer,\n"
     "                  pitch: int) -> None\n"
     "\n"
     "Updates the given texture rectangle with new pixel data.\n"
     "\n"
     "texture\n"
     "    The texture to update.\n"
     "\n"
     "rect\n"
     "    The area to update, or None to update the entire texture.\n"
     "\n"
     "pixels\n"
     "    The raw pixel data.\n"
     "\n"
     "pitch\n"
     "    The number of bytes in a row of pixel data, including padding\n"
     "    between lines.\n"
    },

    {"SDL_LockTexture",
     (PyCFunction) PyCSDL2_LockTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_LockTexture(texture: SDL_Texture, rect: SDL_Rect) -> (buffer, int)\n"
     "\n"
     "Locks a portion of the texture for write-only pixel access.\n"
     "\n"
     "texture\n"
     "    The texture to update.\n"
     "\n"
     "rect\n"
     "    The area to lock for access, or None to lock the entire texture.\n"
     "\n"
     "Returns a tuple (pixels, pitch), where `pixels` is a buffer with the\n"
     "locked pixel data, and `pitch` is the integer length of one row in\n"
     "bytes.\n"
    },

    {"SDL_UnlockTexture",
     (PyCFunction) PyCSDL2_UnlockTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_UnlockTexture(texture: SDL_Texture) -> None\n"
     "\n"
     "Unlocks a texture, uploading any changes to video memory.\n"
    },

    {"SDL_SetRenderDrawColor",
     (PyCFunction) PyCSDL2_SetRenderDrawColor,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: int, g: int, b: int,\n"
     "                       a: int) -> None\n"
     "\n"
     "Sets the color used for drawing primitives and for SDL_RenderClear()\n"
    },

    {"SDL_GetRenderDrawColor",
     (PyCFunction) PyCSDL2_GetRenderDrawColor,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_GetRenderDrawColor(renderer: SDL_Renderer) -> (int, int, int, int)\n"
     "\n"
     "Returns the color (r, g, b, a) used for drawing operations.\n"
    },

    {"SDL_RenderClear",
     (PyCFunction) PyCSDL2_RenderClear,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RenderClear(renderer: SDL_Renderer) -> None\n"
     "\n"
     "Clears the current rendering target with the current drawing color.\n"
     "The entire rendering target is cleared, ignoring the viewport.\n"
    },

    {"SDL_RenderFillRect",
     (PyCFunction) PyCSDL2_RenderFillRect,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RenderFillRect(renderer: SDL_Renderer, rect: SDL_Rect or None)\n"
     "    -> None\n"
     "\n"
     "Fills a rectangle `rect` on the current rendering target with the\n"
     "current drawing color.\n"
     "\n"
     "If `rect` is None, the entire rendering target will be filled.\n"
    },

    {"SDL_RenderCopy",
     (PyCFunction) PyCSDL2_RenderCopy,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RenderCopy(renderer: SDL_Renderer, texture: SDL_Texture,\n"
     "               srcrect: SDL_Rect, dstrect: SDL_Rect) -> None\n"
     "\n"
     "Copies a portion of the texture to the current rendering target.\n"
     "\n"
     "renderer\n"
     "    The rendering context.\n"
     "\n"
     "texture\n"
     "    The source texture.\n"
     "\n"
     "srcrect\n"
     "    The source rectangle, or None for the entire texture.\n"
     "\n"
     "dstrect\n"
     "    The destination rectangle, or None for the entire rendering target.\n"
     "    The texture will be stretched to fill the given rectangle.\n"
    },

    {"SDL_RenderCopyEx",
     (PyCFunction) PyCSDL2_RenderCopyEx,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RenderCopyEx(renderer: SDL_Renderer, texture: SDL_Texture,\n"
     "                 srcrect: SDL_Rect, dstrect: SDL_Rect, angle: float,\n"
     "                 center: SDL_Point, flip: int) -> None\n"
     "\n"
     "Copies a portion of the texture to the current rendering target,\n"
     "optionally rotating it by an angle around the given center and also\n"
     "flipping it top-bottom and/or left-right.\n"
     "\n"
     "renderer\n"
     "    The rendering context.\n"
     "\n"
     "texture\n"
     "    The source texture.\n"
     "\n"
     "srcrect\n"
     "    The source rectangle, or None for the entire texture.\n"
     "\n"
     "dstrect\n"
     "    The destination rectangle, or None for the entire rendering\n"
     "    target. The texture will be stretched to fill the given rectangle.\n"
     "\n"
     "angle\n"
     "    An angle in degrees that indicates the rotation that will be\n"
     "    applied to `dstrect`.\n"
     "\n"
     "center\n"
     "    The point around which `dstrect` will be rotated. If None,\n"
     "    rotation will be done around ``(dstrect.w/2, dstrect.h/2)``.\n"
     "\n"
     "flip\n"
     "    Indicates which flipping actions should be performed on the\n"
     "    texture. One or more of SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL and/or\n"
     "    SDL_FLIP_VERTICAL OR'd together.\n"
    },

    {"SDL_RenderPresent",
     (PyCFunction) PyCSDL2_RenderPresent,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RenderPresent(renderer: SDL_Renderer) -> None\n"
     "\n"
     "Updates the screen with any rendering performed since the previous\n"
     "call.\n"
    },

    {"SDL_DestroyTexture",
     (PyCFunction) PyCSDL2_DestroyTexture,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_DestroyTexture(texture: SDL_Texture) -> None\n"
     "\n"
     "Destroys the specified texture, freeing its resources.\n"
     "\n"
     "There is no need to explictly call this function. SDL_Texture will\n"
     "automatically call it upon cleanup.\n"
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

    {"SDL_RWsize",
     (PyCFunction) PyCSDL2_RWsize,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWsize(context: SDL_RWops) -> int\n"
     "\n"
     "Returns the size of the data stream in the SDL_RWops context.\n"
    },

    {"SDL_RWseek",
     (PyCFunction) PyCSDL2_RWseek,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWseek(context: SDL_RWops, offset: int, whence: int) -> int\n"
     "\n"
     "Seeks to `offset` relative to `whence`, where `whence` is one of:\n"
     "\n"
     "    * RW_SEEK_SET -- seek from the beginning of data\n"
     "    * RW_SEEK_CUR -- seek relative to the current read point\n"
     "    * RW_SEEK_END -- seek relative to the end of data\n"
     "\n"
     "Returns the final offset in the data stream after the seek.\n"
    },

    {"SDL_RWread",
     (PyCFunction) PyCSDL2_RWread,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWread(context: SDL_RWops, ptr: buffer, size: int, maxnum: int)\n"
     "    -> int\n"
     "\n"
     "Reads up to `maxnum` objects, each of size `size` bytes, from the data\n"
     "source to the buffer `ptr`. Returns the number of objects read, or 0\n"
     "at the end of file. This function may read less objects than\n"
     "requested.\n"
    },

    {"SDL_RWwrite",
     (PyCFunction) PyCSDL2_RWwrite,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWwrite(context: SDL_RWops, ptr: buffer, size: int, num: int)\n"
     "    -> int\n"
     "\n"
     "Writes exactly `num` objects, each `size` bytes, from the buffer\n"
     "`ptr`. If this fails for any reason, it will return less than `num`\n"
     "to show how far the write progressed. On success, it returns `num`.\n"
    },

    {"SDL_RWclose",
     (PyCFunction) PyCSDL2_RWclose,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_RWclose(context: SDL_RWops) -> None\n"
     "\n"
     "Closes and cleans up the data stream. The SDL_RWops object will\n"
     "be freed.\n"
     "\n"
     "Note that even if an error occurs, the SDL_RWops object will still be\n"
     "invalidated.\n"
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

    {"SDL_GetWindowTitle",
     (PyCFunction) PyCSDL2_GetWindowTitle,
     METH_VARARGS | METH_KEYWORDS,
     "SDL_GetWindowTitle(window: SDL_Window) -> str\n"
     "\n"
     "Returns the title of the window, or an empty string if there is no\n"
     "title.\n"
    },

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
