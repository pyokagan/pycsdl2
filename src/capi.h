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
 * \file capi.h
 * \brief csdl2's C API
 *
 * This file implements functionality to expose csdl2's C API to other
 * extensions so that these extensions can use csdl2's functionality.
 */
#ifndef _PYCSDL2_CAPI_H_
#define _PYCSDL2_CAPI_H_
#include <Python.h>
#include "../include/pycsdl2.h"

/**
 * \brief Initializes csdl2's PyCSDL2_CAPI PyCapsule
 *
 * Initialize csdl2's PyCSDL2_CAPI PyCapsule object and adds it to the module m
 * with the name "_C_API". The PyCSDL2_CAPI can thus be retrieved with:
 * \code
 * (PyCSDL2_CAPI*) PyCapsule_Import("csdl2._C_API", 0);
 * \endcode
 *
 * \param m the csdl2 module object
 * \returns 1 on success, 0 on failure
 */
static int
PyCSDL2_initcapi(PyObject *m)
{
    static const PyCSDL2_CAPI api = {
/* SDL_assert.h */
        SDL_ReportAssertion,
        SDL_SetAssertionHandler,
        SDL_GetAssertionReport,
        SDL_ResetAssertionReport,
/* SDL_atomic.h */
        SDL_AtomicTryLock,
        SDL_AtomicLock,
        SDL_AtomicUnlock,
#ifndef SDL_MemoryBarrierRelease
        SDL_MemoryBarrierRelease,
#else
        NULL,
#endif
#ifndef SDL_MemoryBarrierAcquire
        SDL_MemoryBarrierAcquire,
#else
        NULL,
#endif
#ifndef SDL_AtomicCAS
        SDL_AtomicCAS,
#else
        NULL,
#endif
#ifndef SDL_AtomicCASPtr
        SDL_AtomicCASPtr,
#else
        NULL,
#endif
/* SDL_audio.h */
        SDL_GetNumAudioDrivers,
        SDL_GetAudioDriver,
        SDL_AudioInit,
        SDL_AudioQuit,
        SDL_GetCurrentAudioDriver,
        SDL_OpenAudio,
        SDL_GetNumAudioDevices,
        SDL_GetAudioDeviceName,
        SDL_OpenAudioDevice,
        SDL_GetAudioStatus,
        SDL_GetAudioDeviceStatus,
        SDL_PauseAudio,
        SDL_PauseAudioDevice,
        SDL_LoadWAV_RW,
        SDL_FreeWAV,
        SDL_BuildAudioCVT,
        SDL_ConvertAudio,
        SDL_MixAudio,
        SDL_MixAudioFormat,
        SDL_LockAudio,
        SDL_LockAudioDevice,
        SDL_UnlockAudio,
        SDL_UnlockAudioDevice,
        SDL_CloseAudio,
        SDL_CloseAudioDevice,
/* SDL_clipboard.h */
        SDL_SetClipboardText,
        SDL_GetClipboardText,
        SDL_HasClipboardText,
/* SDL_cpuinfo.h */
        SDL_GetCPUCount,
        SDL_GetCPUCacheLineSize,
        SDL_HasRDTSC,
        SDL_HasAltiVec,
        SDL_HasMMX,
        SDL_Has3DNow,
        SDL_HasSSE,
        SDL_HasSSE2,
        SDL_HasSSE3,
        SDL_HasSSE41,
        SDL_HasSSE42,
/* SDL_error.h */
        SDL_SetError,
        SDL_GetError,
        SDL_ClearError,
        SDL_Error,
/* SDL_events.h */
        SDL_PumpEvents,
        SDL_PeepEvents,
        SDL_HasEvent,
        SDL_HasEvents,
        SDL_FlushEvent,
        SDL_FlushEvents,
        SDL_PollEvent,
        SDL_WaitEvent,
        SDL_WaitEventTimeout,
        SDL_PushEvent,
        SDL_SetEventFilter,
        SDL_GetEventFilter,
        SDL_AddEventWatch,
        SDL_DelEventWatch,
        SDL_FilterEvents,
        SDL_EventState,
        SDL_RegisterEvents,
/* SDL_gamecontroller.h */
        SDL_GameControllerAddMapping,
        SDL_GameControllerMappingForGUID,
        SDL_GameControllerMapping,
        SDL_IsGameController,
        SDL_GameControllerNameForIndex,
        SDL_GameControllerOpen,
        SDL_GameControllerName,
        SDL_GameControllerGetAttached,
        SDL_GameControllerGetJoystick,
        SDL_GameControllerEventState,
        SDL_GameControllerUpdate,
        SDL_GameControllerGetAxisFromString,
        SDL_GameControllerGetStringForAxis,
        SDL_GameControllerGetBindForAxis,
        SDL_GameControllerGetAxis,
        SDL_GameControllerGetButtonFromString,
        SDL_GameControllerGetStringForButton,
        SDL_GameControllerGetBindForButton,
        SDL_GameControllerGetButton,
        SDL_GameControllerClose,
/* SDL_gesture.h */
        SDL_RecordGesture,
        SDL_SaveAllDollarTemplates,
        SDL_SaveDollarTemplate,
        SDL_LoadDollarTemplates,
/* SDL.h */
        SDL_Init,
        SDL_InitSubSystem,
        SDL_QuitSubSystem,
        SDL_WasInit,
        SDL_Quit,
/* SDL_haptic.h */
        SDL_NumHaptics,
        SDL_HapticName,
        SDL_HapticOpen,
        SDL_HapticOpened,
        SDL_HapticIndex,
        SDL_MouseIsHaptic,
        SDL_HapticOpenFromMouse,
        SDL_JoystickIsHaptic,
        SDL_HapticOpenFromJoystick,
        SDL_HapticClose,
        SDL_HapticNumEffects,
        SDL_HapticNumEffectsPlaying,
        SDL_HapticQuery,
        SDL_HapticNumAxes,
        SDL_HapticEffectSupported,
        SDL_HapticNewEffect,
        SDL_HapticUpdateEffect,
        SDL_HapticRunEffect,
        SDL_HapticStopEffect,
        SDL_HapticDestroyEffect,
        SDL_HapticGetEffectStatus,
        SDL_HapticSetGain,
        SDL_HapticSetAutocenter,
        SDL_HapticPause,
        SDL_HapticUnpause,
        SDL_HapticStopAll,
        SDL_HapticRumbleSupported,
        SDL_HapticRumbleInit,
        SDL_HapticRumblePlay,
        SDL_HapticRumbleStop,
/* SDL_hints.h */
        SDL_SetHintWithPriority,
        SDL_SetHint,
        SDL_GetHint,
        SDL_AddHintCallback,
        SDL_DelHintCallback,
        SDL_ClearHints,
/* SDL_joystick.h */
        SDL_NumJoysticks,
        SDL_JoystickNameForIndex,
        SDL_JoystickOpen,
        SDL_JoystickName,
        SDL_JoystickGetDeviceGUID,
        SDL_JoystickGetGUID,
        SDL_JoystickGetGUIDString,
        SDL_JoystickGetGUIDFromString,
        SDL_JoystickGetAttached,
        SDL_JoystickInstanceID,
        SDL_JoystickNumAxes,
        SDL_JoystickNumBalls,
        SDL_JoystickNumHats,
        SDL_JoystickNumButtons,
        SDL_JoystickUpdate,
        SDL_JoystickEventState,
        SDL_JoystickGetAxis,
        SDL_JoystickGetHat,
        SDL_JoystickGetBall,
        SDL_JoystickGetButton,
        SDL_JoystickClose,
/* SDL_keyboard.h */
        SDL_GetKeyboardFocus,
        SDL_GetKeyboardState,
        SDL_GetModState,
        SDL_SetModState,
        SDL_GetKeyFromScancode,
        SDL_GetScancodeFromKey,
        SDL_GetScancodeName,
        SDL_GetScancodeFromName,
        SDL_GetKeyName,
        SDL_GetKeyFromName,
        SDL_StartTextInput,
        SDL_IsTextInputActive,
        SDL_StopTextInput,
        SDL_SetTextInputRect,
        SDL_HasScreenKeyboardSupport,
        SDL_IsScreenKeyboardShown,
/* SDL_loadso.h */
        SDL_LoadObject,
        SDL_LoadFunction,
        SDL_UnloadObject,
/* SDL_log.h */
        SDL_LogSetAllPriority,
        SDL_LogSetPriority,
        SDL_LogGetPriority,
        SDL_LogResetPriorities,
        SDL_Log,
        SDL_LogVerbose,
        SDL_LogDebug,
        SDL_LogInfo,
        SDL_LogWarn,
        SDL_LogError,
        SDL_LogCritical,
        SDL_LogMessage,
        SDL_LogMessageV,
        SDL_LogGetOutputFunction,
        SDL_LogSetOutputFunction,
/* SDL_main.h */
        SDL_SetMainReady,
#ifdef __WIN32__
        SDL_RegisterApp,
        SDL_UnregisterApp,
#else
        NULL,
        NULL,
#endif
/* SDL_messagebox.h */
        SDL_ShowMessageBox,
        SDL_ShowSimpleMessageBox,
/* SDL_mouse.h */
        SDL_GetMouseFocus,
        SDL_GetMouseState,
        SDL_GetRelativeMouseState,
        SDL_WarpMouseInWindow,
        SDL_SetRelativeMouseMode,
        SDL_GetRelativeMouseMode,
        SDL_CreateCursor,
        SDL_CreateColorCursor,
        SDL_CreateSystemCursor,
        SDL_SetCursor,
        SDL_GetCursor,
        SDL_GetDefaultCursor,
        SDL_FreeCursor,
        SDL_ShowCursor,
/* SDL_mutex.h */
        SDL_CreateMutex,
        SDL_LockMutex,
        SDL_TryLockMutex,
        SDL_UnlockMutex,
        SDL_DestroyMutex,
        SDL_CreateSemaphore,
        SDL_DestroySemaphore,
        SDL_SemWait,
        SDL_SemTryWait,
        SDL_SemWaitTimeout,
        SDL_SemPost,
        SDL_SemValue,
        SDL_CreateCond,
        SDL_DestroyCond,
        SDL_CondSignal,
        SDL_CondBroadcast,
        SDL_CondWait,
        SDL_CondWaitTimeout,
/* SDL_pixels.h */
        SDL_GetPixelFormatName,
        SDL_PixelFormatEnumToMasks,
        SDL_MasksToPixelFormatEnum,
        SDL_AllocFormat,
        SDL_FreeFormat,
        SDL_AllocPalette,
        SDL_SetPixelFormatPalette,
        SDL_SetPaletteColors,
        SDL_FreePalette,
        SDL_MapRGB,
        SDL_MapRGBA,
        SDL_GetRGB,
        SDL_GetRGBA,
        SDL_CalculateGammaRamp,
/* SDL_platform.h */
        SDL_GetPlatform,
/* SDL_power.h */
        SDL_GetPowerInfo,
/* SDL_rect.h */
        SDL_HasIntersection,
        SDL_IntersectRect,
        SDL_UnionRect,
        SDL_EnclosePoints,
        SDL_IntersectRectAndLine,
/* SDL_render.h */
        SDL_GetNumRenderDrivers,
        SDL_GetRenderDriverInfo,
        SDL_CreateWindowAndRenderer,
        SDL_CreateRenderer,
        SDL_CreateSoftwareRenderer,
        SDL_GetRenderer,
        SDL_GetRendererInfo,
        SDL_GetRendererOutputSize,
        SDL_CreateTexture,
        SDL_CreateTextureFromSurface,
        SDL_QueryTexture,
        SDL_SetTextureColorMod,
        SDL_GetTextureColorMod,
        SDL_SetTextureAlphaMod,
        SDL_GetTextureAlphaMod,
        SDL_SetTextureBlendMode,
        SDL_GetTextureBlendMode,
        SDL_UpdateTexture,
        SDL_LockTexture,
        SDL_UnlockTexture,
        SDL_RenderTargetSupported,
        SDL_SetRenderTarget,
        SDL_GetRenderTarget,
        SDL_RenderSetLogicalSize,
        SDL_RenderGetLogicalSize,
        SDL_RenderSetViewport,
        SDL_RenderGetViewport,
        SDL_RenderSetClipRect,
        SDL_RenderGetClipRect,
        SDL_RenderSetScale,
        SDL_RenderGetScale,
        SDL_SetRenderDrawColor,
        SDL_GetRenderDrawColor,
        SDL_SetRenderDrawBlendMode,
        SDL_GetRenderDrawBlendMode,
        SDL_RenderClear,
        SDL_RenderDrawPoint,
        SDL_RenderDrawPoints,
        SDL_RenderDrawLine,
        SDL_RenderDrawLines,
        SDL_RenderDrawRect,
        SDL_RenderDrawRects,
        SDL_RenderFillRect,
        SDL_RenderFillRects,
        SDL_RenderCopy,
        SDL_RenderCopyEx,
        SDL_RenderReadPixels,
        SDL_RenderPresent,
        SDL_DestroyTexture,
        SDL_DestroyRenderer,
        SDL_GL_BindTexture,
        SDL_GL_UnbindTexture,
/* SDL_rwops.h */
        SDL_RWFromFile,
        SDL_RWFromFP,
        SDL_RWFromMem,
        SDL_RWFromConstMem,
        SDL_AllocRW,
        SDL_FreeRW,
        SDL_ReadU8,
        SDL_ReadLE16,
        SDL_ReadBE16,
        SDL_ReadLE32,
        SDL_ReadBE32,
        SDL_ReadLE64,
        SDL_ReadBE64,
        SDL_WriteU8,
        SDL_WriteLE16,
        SDL_WriteBE16,
        SDL_WriteLE32,
        SDL_WriteBE32,
        SDL_WriteLE64,
        SDL_WriteBE64,
/* SDL_shape.h */
        SDL_CreateShapedWindow,
        SDL_IsShapedWindow,
        SDL_SetWindowShape,
        SDL_GetShapedWindowMode,
/* SDL_stdinc.h */
        SDL_malloc,
        SDL_calloc,
        SDL_realloc,
        SDL_free,
        SDL_getenv,
        SDL_setenv,
        SDL_qsort,
        SDL_abs,
        SDL_isdigit,
        SDL_isspace,
        SDL_toupper,
        SDL_tolower,
        SDL_memset,
        SDL_memcpy,
        SDL_memmove,
        SDL_memcmp,
        SDL_wcslen,
        SDL_wcslcpy,
        SDL_wcslcat,
        SDL_strlen,
        SDL_strlcpy,
        SDL_utf8strlcpy,
        SDL_strlcat,
        SDL_strdup,
        SDL_strrev,
        SDL_strupr,
        SDL_strlwr,
        SDL_strchr,
        SDL_strrchr,
        SDL_strstr,
        SDL_itoa,
        SDL_uitoa,
        SDL_ltoa,
        SDL_ultoa,
        SDL_lltoa,
        SDL_ulltoa,
        SDL_atoi,
        SDL_atof,
        SDL_strtol,
        SDL_strtoul,
        SDL_strtoll,
        SDL_strtoull,
        SDL_strtod,
        SDL_strcmp,
        SDL_strncmp,
        SDL_strcasecmp,
        SDL_strncasecmp,
        SDL_sscanf,
        SDL_snprintf,
        SDL_vsnprintf,
        SDL_atan,
        SDL_atan2,
        SDL_ceil,
        SDL_copysign,
        SDL_cos,
        SDL_cosf,
        SDL_fabs,
        SDL_floor,
        SDL_log,
        SDL_pow,
        SDL_scalbn,
        SDL_sin,
        SDL_sinf,
        SDL_sqrt,
        SDL_iconv_open,
        SDL_iconv_close,
        SDL_iconv,
        SDL_iconv_string,
/* SDL_surface.h */
        SDL_CreateRGBSurface,
        SDL_CreateRGBSurfaceFrom,
        SDL_FreeSurface,
        SDL_SetSurfacePalette,
        SDL_LockSurface,
        SDL_UnlockSurface,
        SDL_LoadBMP_RW,
        SDL_SaveBMP_RW,
        SDL_SetSurfaceRLE,
        SDL_SetColorKey,
        SDL_GetColorKey,
        SDL_SetSurfaceColorMod,
        SDL_GetSurfaceColorMod,
        SDL_SetSurfaceAlphaMod,
        SDL_GetSurfaceAlphaMod,
        SDL_SetSurfaceBlendMode,
        SDL_GetSurfaceBlendMode,
        SDL_SetClipRect,
        SDL_GetClipRect,
        SDL_ConvertSurface,
        SDL_ConvertSurfaceFormat,
        SDL_ConvertPixels,
        SDL_FillRect,
        SDL_FillRects,
        SDL_UpperBlit,
        SDL_LowerBlit,
        SDL_SoftStretch,
        SDL_UpperBlitScaled,
        SDL_LowerBlitScaled,
/* SDL_system.h */
#if defined(__IPHONEOS__) && __IPHONEOS__
        SDL_iPhoneSetAnimationCallback,
        SDL_iPhoneSetEventPump,
#else
        NULL,
        NULL,
#endif /* __IPHONEOS__ */
#if defined(__ANDROID__) && __ANDROID__
        SDL_AndroidGetJNIEnv,
        SDL_AndroidGetActivity,
        SDL_AndroidGetInternalStoragePath,
        SDL_AndroidGetExternalStorageState,
        SDL_AndroidGetExternalStoragePath,
#else
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
#endif /* __ANDROID__ */
/* SDL_syswm.h */
        SDL_GetWindowWMInfo,
/* SDL_thread.h */
        SDL_CreateThread,
        SDL_GetThreadName,
        SDL_ThreadID,
        SDL_GetThreadID,
        SDL_SetThreadPriority,
        SDL_WaitThread,
        SDL_TLSCreate,
        SDL_TLSGet,
        SDL_TLSSet,
/* SDL_timer.h */
        SDL_GetTicks,
        SDL_GetPerformanceCounter,
        SDL_GetPerformanceFrequency,
        SDL_Delay,
        SDL_AddTimer,
        SDL_RemoveTimer,
/* SDL_touch.h */
        SDL_GetNumTouchDevices,
        SDL_GetTouchDevice,
        SDL_GetNumTouchFingers,
        SDL_GetTouchFinger,
/* SDL_version.h */
        SDL_GetVersion,
        SDL_GetRevision,
        SDL_GetRevisionNumber,
/* SDL_video.h */
        SDL_GetNumVideoDrivers,
        SDL_GetVideoDriver,
        SDL_VideoInit,
        SDL_VideoQuit,
        SDL_GetCurrentVideoDriver,
        SDL_GetNumVideoDisplays,
        SDL_GetDisplayName,
        SDL_GetDisplayBounds,
        SDL_GetNumDisplayModes,
        SDL_GetDisplayMode,
        SDL_GetDesktopDisplayMode,
        SDL_GetCurrentDisplayMode,
        SDL_GetClosestDisplayMode,
        SDL_GetWindowDisplayIndex,
        SDL_SetWindowDisplayMode,
        SDL_GetWindowDisplayMode,
        SDL_GetWindowPixelFormat,
        SDL_CreateWindow,
        SDL_CreateWindowFrom,
        SDL_GetWindowID,
        SDL_GetWindowFromID,
        SDL_GetWindowFlags,
        SDL_SetWindowTitle,
        SDL_GetWindowTitle,
        SDL_SetWindowIcon,
        SDL_SetWindowData,
        SDL_GetWindowData,
        SDL_SetWindowPosition,
        SDL_GetWindowPosition,
        SDL_SetWindowSize,
        SDL_GetWindowSize,
        SDL_SetWindowMinimumSize,
        SDL_GetWindowMinimumSize,
        SDL_SetWindowMaximumSize,
        SDL_GetWindowMaximumSize,
        SDL_SetWindowBordered,
        SDL_ShowWindow,
        SDL_HideWindow,
        SDL_RaiseWindow,
        SDL_MaximizeWindow,
        SDL_MinimizeWindow,
        SDL_RestoreWindow,
        SDL_SetWindowFullscreen,
        SDL_GetWindowSurface,
        SDL_UpdateWindowSurface,
        SDL_UpdateWindowSurfaceRects,
        SDL_SetWindowGrab,
        SDL_GetWindowGrab,
        SDL_SetWindowBrightness,
        SDL_GetWindowBrightness,
        SDL_SetWindowGammaRamp,
        SDL_GetWindowGammaRamp,
        SDL_DestroyWindow,
        SDL_IsScreenSaverEnabled,
        SDL_EnableScreenSaver,
        SDL_DisableScreenSaver,
        SDL_GL_LoadLibrary,
        SDL_GL_GetProcAddress,
        SDL_GL_UnloadLibrary,
        SDL_GL_ExtensionSupported,
        SDL_GL_SetAttribute,
        SDL_GL_GetAttribute,
        SDL_GL_CreateContext,
        SDL_GL_MakeCurrent,
        SDL_GL_GetCurrentWindow,
        SDL_GL_GetCurrentContext,
        SDL_GL_SetSwapInterval,
        SDL_GL_GetSwapInterval,
        SDL_GL_SwapWindow,
        SDL_GL_DeleteContext
    };
    PyObject *capsule = PyCapsule_New((void*) &api, "csdl2._C_API", NULL);
    if (!capsule) { return 0; }
    if (PyModule_AddObject(m, "_C_API", capsule)) { return 0; }
    return 1;
}

#endif /* _PYCSDL2_CAPI_H_ */
