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
#ifndef _PYCSDL2_H_
#define _PYCSDL2_H_
/**
 * \file pycsdl2.h
 * \brief pycsdl2 public API header
 */
#ifdef __cplusplus
extern "C" {
#endif
#include <Python.h>
#include "SDL.h"
#include "SDL_shape.h"
#include "SDL_syswm.h"

/* SDL_assert.h */

/** \brief Function pointer type of \c SDL_ReportAssertion() */
typedef SDL_assert_state (SDLCALL *SDL_ReportAssertion_pfn)(
        SDL_assert_data *data, const char *func, const char *file, int line);

/** \brief Function pointer type of \c SDL_SetAssertionHandler() */
typedef void (SDLCALL *SDL_SetAssertionHandler_pfn)(
        SDL_AssertionHandler handler, void *userdata);

/** \brief Function pointer type of \c SDL_GetAssertionReport() */
typedef const SDL_assert_data *(SDLCALL *SDL_GetAssertionReport_pfn)(void);

/** \brief Function pointer typedef for \c SDL_ResetAssertionReport() */
typedef void (SDLCALL *SDL_ResetAssertionReport_pfn)(void);

/* SDL_atomic.h */

/** \brief Function pointer type of \c SDL_AtomicTryLock() */
typedef SDL_bool (SDLCALL *SDL_AtomicTryLock_pfn)(SDL_SpinLock *lock);

/** \brief Function pointer type of \c SDL_AtomicLock() */
typedef void (SDLCALL *SDL_AtomicLock_pfn)(SDL_SpinLock *lock);

/** \brief Function pointer type of \c SDL_AtomicUnlock() */
typedef void (SDLCALL *SDL_AtomicUnlock_pfn)(SDL_SpinLock *lock);

#if !defined(SDL_MemoryBarrierRelease) || DOXYGEN
/** \brief Function pointer type of \c SDL_MemoryBarrierRelease() */
typedef void (SDLCALL *SDL_MemoryBarrierRelease_pfn)(void);
#endif

#if !defined(SDL_MemoryBarrierAcquire) || DOXYGEN
/** \brief Function pointer type of \c SDL_MemoryBarrierAcquire() */
typedef void (SDLCALL *SDL_MemoryBarrierAcquire_pfn)(void);
#endif

/** \brief Function pointer type of \c SDL_AtomicCAS() */
typedef SDL_bool (SDLCALL *SDL_AtomicCAS_pfn)(SDL_atomic_t *a, int oldval,
                                              int newval);

/** \brief Function pointer type of \c SDL_AtomicCASPtr() */
typedef SDL_bool (SDLCALL *SDL_AtomicCASPtr_pfn)(void **a, void *oldval,
                                                 void *newval);

/* SDL_audio.h */

/** \brief Function pointer type of \c SDL_GetNumAudioDrivers() */
typedef int (SDLCALL *SDL_GetNumAudioDrivers_pfn)(void);

/** \brief Function pointer type of \c SDL_GetAudioDriver() */
typedef const char* (SDLCALL *SDL_GetAudioDriver_pfn)(int index);

/** \brief Function pointer type of \c SDL_AudioInit() */
typedef int (SDLCALL *SDL_AudioInit_pfn)(const char *driver_name);

/** \brief Function pointer type of \c SDL_AudioQuit() */
typedef void (SDLCALL *SDL_AudioQuit_pfn)(void);

/** \brief Function pointer type of \c SDL_GetCurrentAudioDriver() */
typedef const char* (SDLCALL *SDL_GetCurrentAudioDriver_pfn)(void);

/** \brief Function pointer type of \c SDL_OpenAudio() */
typedef int (SDLCALL *SDL_OpenAudio_pfn)(SDL_AudioSpec *desired,
                                         SDL_AudioSpec *obtained);

/** \brief Function pointer type of \c SDL_GetNumAudioDevices() */
typedef int (SDLCALL *SDL_GetNumAudioDevices_pfn)(int iscapture);

/** \brief Function pointer type of \c SDL_GetAudioDeviceName() */
typedef const char* (SDLCALL *SDL_GetAudioDeviceName_pfn)(int index,
                                                          int iscapture);

/** \brief Function pointer type of \c SDL_OpenAudioDevice() */
typedef SDL_AudioDeviceID (SDLCALL *SDL_OpenAudioDevice_pfn)(
        const char *device, int iscapture, const SDL_AudioSpec *desired,
        SDL_AudioSpec *obtained, int allowed_changes);

/** \brief Function pointer type of \c SDL_GetAudioStatus() */
typedef SDL_AudioStatus (SDLCALL *SDL_GetAudioStatus_pfn)(void);

/** \brief Function pointer type of \c SDL_GetAudioDeviceStatus() */
typedef SDL_AudioStatus (SDLCALL *SDL_GetAudioDeviceStatus_pfn)(
        SDL_AudioDeviceID dev);

/** \brief Function pointer type of \c SDL_PauseAudio() */
typedef void (SDLCALL *SDL_PauseAudio_pfn)(int pause_on);

/** \brief Function pointer type of \c SDL_PauseAudioDevice() */
typedef void (SDLCALL *SDL_PauseAudioDevice_pfn)(SDL_AudioDeviceID dev,
                                                 int pause_on);

/** \brief Function pointer type of \c SDL_LoadWAV_RW() */
typedef SDL_AudioSpec* (SDLCALL *SDL_LoadWAV_RW_pfn)(SDL_RWops *src,
                                                     int freesrc,
                                                     SDL_AudioSpec *spec,
                                                     Uint8 **audio_buf,
                                                     Uint32 *audio_len);

/** \brief Function pointer type of \c SDL_FreeWAV() */
typedef void (SDLCALL *SDL_FreeWAV_pfn)(Uint8 *audio_buf);

/** \brief Function pointer type of \c SDL_BuildAudioCVT() */
typedef int (SDLCALL *SDL_BuildAudioCVT_pfn)(SDL_AudioCVT *cvt,
                                             SDL_AudioFormat src_format,
                                             Uint8 src_channels, int src_rate,
                                             SDL_AudioFormat dst_format,
                                             Uint8 dst_channels, int dst_rate);

/** \brief Function pointer type of \c SDL_ConvertAudio() */
typedef int (SDLCALL *SDL_ConvertAudio_pfn)(SDL_AudioCVT *cvt);

/** \brief Function pointer type of \c SDL_MixAudio() */
typedef void (SDLCALL *SDL_MixAudio_pfn)(Uint8 *dst, const Uint8 *src,
        Uint32 len, int volume);

/** \brief Function pointer type of \c SDL_MixAudioFormat() */
typedef void (SDLCALL *SDL_MixAudioFormat_pfn)(Uint8 *dst, const Uint8 *src,
        SDL_AudioFormat format, Uint32 len, int volume);

/** \brief Function pointer type of \c SDL_LockAudio() */
typedef void (SDLCALL *SDL_LockAudio_pfn)(void);

/** \brief Function pointer type of \c SDL_LockAudioDevice() */
typedef void (SDLCALL *SDL_LockAudioDevice_pfn)(SDL_AudioDeviceID dev);

/** \brief Function pointer type of \c SDL_UnlockAudio() */
typedef void (SDLCALL *SDL_UnlockAudio_pfn)(void);

/** \brief Function pointer type of \c SDL_UnlockAudioDevice() */
typedef void (SDLCALL *SDL_UnlockAudioDevice_pfn)(SDL_AudioDeviceID dev);

/** \brief Function pointer type of \c SDL_CloseAudio() */
typedef void (SDLCALL *SDL_CloseAudio_pfn)(void);

/** \brief Function pointer type of \c SDL_CloseAudioDevice() */
typedef void (SDLCALL *SDL_CloseAudioDevice_pfn)(SDL_AudioDeviceID dev);

/* SDL_clipboard.h */

/** \brief Function pointer type of \c SDL_SetClipboardText() */
typedef int (SDLCALL *SDL_SetClipboardText_pfn)(const char *text);

/** \brief Function pointer type of \c SDL_GetClipboardText() */
typedef char* (SDLCALL *SDL_GetClipboardText_pfn)(void);

/** \brief Function pointer type of \c SDL_HasClipboardText() */
typedef SDL_bool (SDLCALL *SDL_HasClipboardText_pfn)(void);

/* SDL_cpuinfo.h */

/** \brief Function pointer type of \c SDL_GetCPUCount() */
typedef int (SDLCALL *SDL_GetCPUCount_pfn)(void);

/** \brief Function pointer type of \c SDL_GetCPUCacheLineSize() */
typedef int (SDLCALL *SDL_GetCPUCacheLineSize_pfn)(void);

/** \brief Function pointer type of \c SDL_HasRDTSC() */
typedef SDL_bool (SDLCALL *SDL_HasRDTSC_pfn)(void);

/** \brief Function pointer type of \c SDL_HasAltiVec() */
typedef SDL_bool (SDLCALL *SDL_HasAltiVec_pfn)(void);

/** \brief Function pointer type of \c SDL_HasMMX() */
typedef SDL_bool (SDLCALL *SDL_HasMMX_pfn)(void);

/** \brief Function pointer type of \c SDL_Has3DNow() */
typedef SDL_bool (SDLCALL *SDL_Has3DNow_pfn)(void);

/** \brief Function pointer type of \c SDL_HasSSE() */
typedef SDL_bool (SDLCALL *SDL_HasSSE_pfn)(void);

/** \brief Function pointer type of \c SDL_HasSSE2() */
typedef SDL_bool (SDLCALL *SDL_HasSSE2_pfn)(void);

/** \brief Function pointer type of \c SDL_HasSSE3() */
typedef SDL_bool (SDLCALL *SDL_HasSSE3_pfn)(void);

/** \brief Function pointer type of \c SDL_HasSSE41() */
typedef SDL_bool (SDLCALL *SDL_HasSSE41_pfn)(void);

/** \brief Function pointer type of \c SDL_HasSSE42() */
typedef SDL_bool (SDLCALL *SDL_HasSSE42_pfn)(void);

/* SDL_error.h */

/** \brief Function pointer type of \c SDL_SetError() */
typedef int (SDLCALL *SDL_SetError_pfn)(const char *fmt, ...);

/** \brief Function pointer type of \c SDL_GetError() */
typedef const char* (SDLCALL *SDL_GetError_pfn)(void);

/** \brief Function pointer type of \c SDL_ClearError() */
typedef void (SDLCALL *SDL_ClearError_pfn)(void);

/** \brief Function pointer type of \c SDL_Error() */
typedef int (SDLCALL *SDL_Error_pfn)(SDL_errorcode code);

/* SDL_events.h */

/** \brief Function pointer type of \c SDL_PumpEvents() */
typedef void (SDLCALL *SDL_PumpEvents_pfn)(void);

/** \brief Function pointer type of \c SDL_PeepEvents() */
typedef int (SDLCALL *SDL_PeepEvents_pfn)(SDL_Event *events, int numevents,
                                          SDL_eventaction action,
                                          Uint32 minType, Uint32 maxType);

/** \brief Function pointer type of \c SDL_HasEvent() */
typedef SDL_bool (SDLCALL *SDL_HasEvent_pfn)(Uint32 type);

/** \brief Function pointer type of \c SDL_HasEvents() */
typedef SDL_bool (SDLCALL *SDL_HasEvents_pfn)(Uint32 minType, Uint32 maxType);

/** \brief Function pointer type of \c SDL_FlushEvent() */
typedef void (SDLCALL *SDL_FlushEvent_pfn)(Uint32 type);

/** \brief Function pointer type of \c SDL_FlushEvents() */
typedef void (SDLCALL *SDL_FlushEvents_pfn)(Uint32 minType, Uint32 maxType);

/** \brief Function pointer type of \c SDL_PollEvent() */
typedef int (SDLCALL *SDL_PollEvent_pfn)(SDL_Event *event);

/** \brief Function pointer type of \c SDL_WaitEvent() */
typedef int (SDLCALL *SDL_WaitEvent_pfn)(SDL_Event *event);

/** \brief Function pointer type of \c SDL_WaitEventTimeout() */
typedef int (SDLCALL *SDL_WaitEventTimeout_pfn)(SDL_Event *event, int timeout);

/** \brief Function pointer type of \c SDL_PushEvent() */
typedef int (SDLCALL *SDL_PushEvent_pfn)(SDL_Event *event);

/** \brief Function pointer type of \c SDL_SetEventFilter() */
typedef void (SDLCALL *SDL_SetEventFilter_pfn)(SDL_EventFilter filter,
                                               void *userdata);

/** \brief Function pointer type of \c SDL_GetEventFilter() */
typedef SDL_bool (SDLCALL *SDL_GetEventFilter_pfn)(SDL_EventFilter *filter,
                                                   void **userdata);

/** \brief Function pointer type of \c SDL_AddEventWatch() */
typedef void (SDLCALL *SDL_AddEventWatch_pfn)(SDL_EventFilter filter,
                                              void *userdata);

/** \brief Function pointer type of \c SDL_DelEventWatch() */
typedef void (SDLCALL *SDL_DelEventWatch_pfn)(SDL_EventFilter filter,
                                              void *userdata);

/** \brief Function pointer type of \c SDL_FilterEvents() */
typedef void (SDLCALL *SDL_FilterEvents_pfn)(SDL_EventFilter filter,
                                             void *userdata);

/** \brief Function pointer type of \c SDL_EventState() */
typedef Uint8 (SDLCALL *SDL_EventState_pfn)(Uint32 type, int state);

/** \brief Function pointer type of \c SDL_RegisterEvents() */
typedef Uint32 (SDLCALL *SDL_RegisterEvents_pfn)(int numevents);

/* SDL_gamecontroller.h */

/** \brief Function pointer type of \c SDL_GameControllerAddMapping() */
typedef int (SDLCALL *SDL_GameControllerAddMapping_pfn)(
        const char *mappingString);

/** \brief Function pointer type of \c SDL_GameControllerMappingForGUID() */
typedef char* (SDLCALL *SDL_GameControllerMappingForGUID_pfn)(
        SDL_JoystickGUID guid);

/** \brief Function pointer type of \c SDL_GameControllerMapping() */
typedef char* (SDLCALL *SDL_GameControllerMapping_pfn)(
        SDL_GameController *gamecontroller);

/** \brief Function pointer type of \c SDL_IsGameController() */
typedef SDL_bool (SDLCALL *SDL_IsGameController_pfn)(int joystick_index);

/** \brief Function pointer type of \c SDL_GameControllerNameForIndex() */
typedef const char* (SDLCALL *SDL_GameControllerNameForIndex_pfn)(
        int joystick_index);

/** \brief Function pointer type of \c SDL_GameControllerOpen() */
typedef SDL_GameController* (SDLCALL *SDL_GameControllerOpen_pfn)(
        int joystick_index);

/** \brief Function pointer type of \c SDL_GameControllerName() */
typedef const char* (SDLCALL *SDL_GameControllerName_pfn)(
        SDL_GameController *gamecontroller);

/** \brief Function pointer type of \c SDL_GameControllerGetAttached() */
typedef SDL_bool (SDLCALL *SDL_GameControllerGetAttached_pfn)(
        SDL_GameController *gamecontroller);

/** \brief Function pointer type of \c SDL_GameControllerGetJoystick() */
typedef SDL_Joystick* (SDLCALL *SDL_GameControllerGetJoystick_pfn)(
        SDL_GameController *gamecontroller);

/** \brief Function pointer type of \c SDL_GameControllerEventState() */
typedef int (SDLCALL *SDL_GameControllerEventState_pfn)(int state);

/** \brief Function pointer type of \c SDL_GameControllerUpdate() */
typedef void (SDLCALL *SDL_GameControllerUpdate_pfn)(void);

/** \brief Function pointer type of \c SDL_GameControllerGetAxisFromString() */
typedef SDL_GameControllerAxis
    (SDLCALL *SDL_GameControllerGetAxisFromString_pfn)(const char *pchString);

/** \brief Function pointer type of \c SDL_GameControllerGetStringForAxis() */
typedef const char* (SDLCALL *SDL_GameControllerGetStringForAxis_pfn)(
        SDL_GameControllerAxis axis);

/** \brief Function pointer type of \c SDL_GameControllerGetBindForAxis() */
typedef SDL_GameControllerButtonBind (SDLCALL
        *SDL_GameControllerGetBindForAxis_pfn)(
            SDL_GameController *gamecontroller, SDL_GameControllerAxis axis);

/** \brief Function pointer type of \c SDL_GameControllerGetAxis() */
typedef Sint16 (SDLCALL *SDL_GameControllerGetAxis_pfn)(
        SDL_GameController *gamecontroller, SDL_GameControllerAxis axis);

/** \brief Function pointer type of \c SDL_GameControllerGetButtonFromString() */
typedef SDL_GameControllerButton
    (SDLCALL *SDL_GameControllerGetButtonFromString_pfn)(
            const char *pchString);

/** \brief Function pointer type of \c SDL_GameControllerGetStringForButton() */
typedef const char* (SDLCALL *SDL_GameControllerGetStringForButton_pfn)(
        SDL_GameControllerButton button);

/** \brief Function pointer type of \c SDL_GameControllerGetBindForButton() */
typedef SDL_GameControllerButtonBind
    (SDLCALL *SDL_GameControllerGetBindForButton_pfn)(
            SDL_GameController *gamecontroller,
            SDL_GameControllerButton button);

/** \brief Function pointer type of \c SDL_GameControllerGetButton() */
typedef Uint8 (SDLCALL *SDL_GameControllerGetButton_pfn)(
        SDL_GameController *gamecontroller, SDL_GameControllerButton button);

/** \brief Function pointer type of \c SDL_GameControllerClose() */
typedef void (SDLCALL *SDL_GameControllerClose_pfn)(
        SDL_GameController *gamecontroller);

/* SDL_gesture.h */

/** \brief Function pointer type of \c SDL_RecordGesture() */
typedef int (SDLCALL *SDL_RecordGesture_pfn)(SDL_TouchID touchId);

/** \brief Function pointer type of \c SDL_SaveAllDollarTemplates() */
typedef int (SDLCALL *SDL_SaveAllDollarTemplates_pfn)(SDL_RWops *dst);

/** \brief Function pointer type of \c SDL_SaveDollarTemplate() */
typedef int (SDLCALL *SDL_SaveDollarTemplate_pfn)(SDL_GestureID gestureId,
                                                  SDL_RWops *dst);

/** \brief Function pointer type of \c SDL_LoadDollarTemplates() */
typedef int (SDLCALL *SDL_LoadDollarTemplates_pfn)(SDL_TouchID touchId,
                                                   SDL_RWops *src);

/* SDL.h */

/** \brief Function pointer type of \c SDL_Init() */
typedef int (SDLCALL *SDL_Init_pfn)(Uint32 flags);

/** \brief Function pointer type of \c SDL_InitSubSystem() */
typedef int (SDLCALL *SDL_InitSubSystem_pfn)(Uint32 flags);

/** \brief Function pointer type of \c SDL_QuitSubSystem() */
typedef void (SDLCALL *SDL_QuitSubSystem_pfn)(Uint32 flags);

/** \brief Function pointer type of \c SDL_WasInit() */
typedef Uint32 (SDLCALL *SDL_WasInit_pfn)(Uint32 flags);

/** \brief Function pointer type of \c SDL_Quit() */
typedef void (SDLCALL *SDL_Quit_pfn)(void);

/* SDL_haptic.h */

/** \brief Function pointer type of \c SDL_NumHaptics() */
typedef int (SDLCALL *SDL_NumHaptics_pfn)(void);

/** \brief Function pointer type of \c SDL_HapticName() */
typedef const char* (SDLCALL *SDL_HapticName_pfn)(int device_index);

/** \brief Function pointer type of \c SDL_HapticOpen() */
typedef SDL_Haptic* (SDLCALL *SDL_HapticOpen_pfn)(int device_index);

/** \brief Function pointer type of \c SDL_HapticOpened() */
typedef int (SDLCALL *SDL_HapticOpened_pfn)(int device_index);

/** \brief Function pointer type of \c SDL_HapticIndex() */
typedef int (SDLCALL *SDL_HapticIndex_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_MouseIsHaptic() */
typedef int (SDLCALL *SDL_MouseIsHaptic_pfn)(void);

/** \brief Function pointer type of \c SDL_HapticOpenFromMouse() */
typedef SDL_Haptic* (SDLCALL *SDL_HapticOpenFromMouse_pfn)(void);

/** \brief Function pointer type of \c SDL_JoystickIsHaptic() */
typedef int (SDLCALL *SDL_JoystickIsHaptic_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_HapticOpenFromJoystick() */
typedef SDL_Haptic* (SDLCALL *SDL_HapticOpenFromJoystick_pfn)(
        SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_HapticClose() */
typedef void (SDLCALL *SDL_HapticClose_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticNumEffects() */
typedef int (SDLCALL *SDL_HapticNumEffects_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticNumEffectsPlaying() */
typedef int (SDLCALL *SDL_HapticNumEffectsPlaying_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticQuery() */
typedef unsigned int (SDLCALL *SDL_HapticQuery_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticNumAxes() */
typedef int (SDLCALL *SDL_HapticNumAxes_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticEffectSupported() */
typedef int (SDLCALL *SDL_HapticEffectSupported_pfn)(SDL_Haptic *haptic,
                                                     SDL_HapticEffect *effect);

/** \brief Function pointer type of \c SDL_HapticNewEffect() */
typedef int (SDLCALL *SDL_HapticNewEffect_pfn)(SDL_Haptic *haptic,
                                               SDL_HapticEffect *effect);

/** \brief Function pointer type of \c SDL_HapticUpdateEffect() */
typedef int (SDLCALL *SDL_HapticUpdateEffect_pfn)(SDL_Haptic *haptic,
                                                  int effect,
                                                  SDL_HapticEffect *data);

/** \brief Function pointer type of \c SDL_HapticRunEffect() */
typedef int (SDLCALL *SDL_HapticRunEffect_pfn)(SDL_Haptic *haptic, int effect,
                                               Uint32 iterations);

/** \brief Function pointer type of \c SDL_HapticStopEffect() */
typedef int (SDLCALL *SDL_HapticStopEffect_pfn)(SDL_Haptic *haptic,
                                                int effect);

/** \brief Function pointer type of \c SDL_HapticDestroyEffect() */
typedef void (SDLCALL *SDL_HapticDestroyEffect_pfn)(SDL_Haptic *haptic,
                                                    int effect);

/** \brief Function pointer type of \c SDL_HapticGetEffectStatus() */
typedef int (SDLCALL *SDL_HapticGetEffectStatus_pfn)(SDL_Haptic *haptic,
                                                     int effect);

/** \brief Function pointer type of \c SDL_HapticSetGain() */
typedef int (SDLCALL *SDL_HapticSetGain_pfn)(SDL_Haptic *haptic, int gain);

/** \brief Function pointer type of \c SDL_HapticSetAutocenter() */
typedef int (SDLCALL *SDL_HapticSetAutocenter_pfn)(SDL_Haptic *haptic,
                                                   int autocenter);

/** \brief Function pointer type of \c SDL_HapticPause() */
typedef int (SDLCALL *SDL_HapticPause_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticUnpause() */
typedef int (SDLCALL *SDL_HapticUnpause_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticStopAll() */
typedef int (SDLCALL *SDL_HapticStopAll_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticRumbleSupported() */
typedef int (SDLCALL *SDL_HapticRumbleSupported_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticRumbleInit() */
typedef int (SDLCALL *SDL_HapticRumbleInit_pfn)(SDL_Haptic *haptic);

/** \brief Function pointer type of \c SDL_HapticRumblePlay() */
typedef int (SDLCALL *SDL_HapticRumblePlay_pfn)(SDL_Haptic *haptic,
                                                float strength,
                                                Uint32 length);

/** \brief Function pointer type of \c SDL_HapticRumbleStop() */
typedef int (SDLCALL *SDL_HapticRumbleStop_pfn)(SDL_Haptic *haptic);

/* SDL_hints.h */

/** \brief Function pointer type of \c SDL_SetHintWithPriority() */
typedef SDL_bool (SDLCALL *SDL_SetHintWithPriority_pfn)(
        const char *name, const char *value, SDL_HintPriority priority);

/** \brief Function pointer type of \c SDL_SetHint() */
typedef SDL_bool (SDLCALL *SDL_SetHint_pfn)(const char *name,
                                            const char *value);

/** \brief Function pointer type of \c SDL_GetHint() */
typedef const char* (SDLCALL *SDL_GetHint_pfn)(const char *name);

/** \brief Function pointer type of \c SDL_AddHintCallback() */
typedef void (SDLCALL *SDL_AddHintCallback_pfn)(const char *name,
                                                SDL_HintCallback callback,
                                                void *userdata);

/** \brief Function pointer type of \c SDL_DelHintCallback() */
typedef void (SDLCALL *SDL_DelHintCallback_pfn)(const char *name,
                                                SDL_HintCallback callback,
                                                void *userdata);

/** \brief Function pointer type of \c SDL_ClearHints() */
typedef void (SDLCALL *SDL_ClearHints_pfn)(void);

/* SDL_joystick.h */

/** \brief Function pointer type of \c SDL_NumJoysticks() */
typedef int (SDLCALL *SDL_NumJoysticks_pfn)(void);

/** \brief Function pointer type of \c SDL_JoystickNameForIndex() */
typedef const char* (SDLCALL *SDL_JoystickNameForIndex_pfn)(int device_index);

/** \brief Function pointer type of \c SDL_JoystickOpen() */
typedef SDL_Joystick* (SDLCALL *SDL_JoystickOpen_pfn)(int device_index);

/** \brief Function pointer type of \c SDL_JoystickName() */
typedef const char* (SDLCALL *SDL_JoystickName_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickGetDeviceGUID() */
typedef SDL_JoystickGUID (SDLCALL *SDL_JoystickGetDeviceGUID_pfn)(
        int device_index);

/** \brief Function pointer type of \c SDL_JoystickGetGUID() */
typedef SDL_JoystickGUID (SDLCALL *SDL_JoystickGetGUID_pfn)(
        SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickGetGUIDString() */
typedef void (SDLCALL *SDL_JoystickGetGUIDString_pfn)(SDL_JoystickGUID guid,
                                                      char *pszGUID,
                                                      int cbGUID);

/** \brief Function pointer type of \c SDL_JoystickGetGUIDFromString() */
typedef SDL_JoystickGUID (SDLCALL *SDL_JoystickGetGUIDFromString_pfn)(
        const char *pchGUID);

/** \brief Function pointer type of \c SDL_JoystickGetAttached() */
typedef SDL_bool (SDLCALL *SDL_JoystickGetAttached_pfn)(
        SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickInstanceID() */
typedef SDL_JoystickID (SDLCALL *SDL_JoystickInstanceID_pfn)(
        SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickNumAxes() */
typedef int (SDLCALL *SDL_JoystickNumAxes_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickNumBalls() */
typedef int (SDLCALL *SDL_JoystickNumBalls_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickNumHats() */
typedef int (SDLCALL *SDL_JoystickNumHats_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickNumButtons() */
typedef int (SDLCALL *SDL_JoystickNumButtons_pfn)(SDL_Joystick *joystick);

/** \brief Function pointer type of \c SDL_JoystickUpdate() */
typedef void (SDLCALL *SDL_JoystickUpdate_pfn)(void);

/** \brief Function pointer type of \c SDL_JoystickEventState() */
typedef int (SDLCALL *SDL_JoystickEventState_pfn)(int state);

/** \brief Function pointer type of \c SDL_JoystickGetAxis() */
typedef Sint16 (SDLCALL *SDL_JoystickGetAxis_pfn)(SDL_Joystick *joystick,
                                                  int axis);

/** \brief Function pointer type of \c SDL_JoystickGetHat() */
typedef Uint8 (SDLCALL *SDL_JoystickGetHat_pfn)(SDL_Joystick *joystick,
                                                int hat);

/** \brief Function pointer type of \c SDL_JoystickGetBall() */
typedef int (SDLCALL *SDL_JoystickGetBall_pfn)(SDL_Joystick *joystick,
                                               int ball, int *dx, int *dy);

/** \brief Function pointer type of \c SDL_JoystickGetButton() */
typedef Uint8 (SDLCALL *SDL_JoystickGetButton_pfn)(SDL_Joystick *joystick,
                                                   int button);

/** \brief Function pointer type of \c SDL_JoystickClose() */
typedef void (SDLCALL *SDL_JoystickClose_pfn)(SDL_Joystick *joystick);

/* SDL_keyboard.h */

/** \brief Function pointer type of \c SDL_GetKeyboardFocus() */
typedef SDL_Window* (SDLCALL *SDL_GetKeyboardFocus_pfn)(void);

/** \brief Function pointer type of \c SDL_GetKeyboardState() */
typedef const Uint8* (SDLCALL *SDL_GetKeyboardState_pfn)(int *numkeys);

/** \brief Function pointer type of \c SDL_GetModState() */
typedef SDL_Keymod (SDLCALL *SDL_GetModState_pfn)(void);

/** \brief Function pointer type of \c SDL_SetModState() */
typedef void (SDLCALL *SDL_SetModState_pfn)(SDL_Keymod modstate);

/** \brief Function pointer type of \c SDL_GetKeyFromScancode() */
typedef SDL_Keycode (SDLCALL *SDL_GetKeyFromScancode_pfn)(
        SDL_Scancode scancode);

/** \brief Function pointer type of \c SDL_GetScancodeFromKey() */
typedef SDL_Scancode (SDLCALL *SDL_GetScancodeFromKey_pfn)(SDL_Keycode key);

/** \brief Function pointer type of \c SDL_GetScancodeName() */
typedef const char* (SDLCALL *SDL_GetScancodeName_pfn)(SDL_Scancode scancode);

/** \brief Function pointer type of \c SDL_GetScancodeFromName() */
typedef SDL_Scancode (SDLCALL *SDL_GetScancodeFromName_pfn)(const char *name);

/** \brief Function pointer type of \c SDL_GetKeyName() */
typedef const char* (SDLCALL *SDL_GetKeyName_pfn)(SDL_Keycode key);

/** \brief Function pointer type of \c SDL_GetKeyFromName() */
typedef SDL_Keycode (SDLCALL *SDL_GetKeyFromName_pfn)(const char *name);

/** \brief Function pointer type of \c SDL_StartTextInput() */
typedef void (SDLCALL *SDL_StartTextInput_pfn)(void);

/** \brief Function pointer type of \c SDL_IsTextInputActive() */
typedef SDL_bool (SDLCALL *SDL_IsTextInputActive_pfn)(void);

/** \brief Function pointer type of \c SDL_StopTextInput() */
typedef void (SDLCALL *SDL_StopTextInput_pfn)(void);

/** \brief Function pointer type of \c SDL_SetTextInputRect() */
typedef void (SDLCALL *SDL_SetTextInputRect_pfn)(SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_HasScreenKeyboardSupport() */
typedef SDL_bool (SDLCALL *SDL_HasScreenKeyboardSupport_pfn)(void);

/** \brief Function pointer type of \c SDL_IsScreenKeyboardShown() */
typedef SDL_bool (SDLCALL *SDL_IsScreenKeyboardShown_pfn)(SDL_Window *window);

/* SDL_loadso.h */

/** \brief Function pointer type of \c SDL_LoadObject() */
typedef void* (SDLCALL *SDL_LoadObject_pfn)(const char *sofile);

/** \brief Function pointer type of \c SDL_LoadFunction() */
typedef void* (SDLCALL *SDL_LoadFunction_pfn)(void *handle, const char *name);

/** \brief Function pointer type of \c SDL_UnloadObject() */
typedef void (SDLCALL *SDL_UnloadObject_pfn)(void *handle);

/* SDL_log.h */

/** \brief Function pointer type of \c SDL_LogSetAllPriority() */
typedef void (SDLCALL *SDL_LogSetAllPriority_pfn)(SDL_LogPriority priority);

/** \brief Function pointer type of \c SDL_LogSetPriority() */
typedef void (SDLCALL *SDL_LogSetPriority_pfn)(int category,
                                               SDL_LogPriority priority);

/** \brief Function pointer type of \c SDL_LogGetPriority() */
typedef SDL_LogPriority (SDLCALL *SDL_LogGetPriority_pfn)(int category);

/** \brief Function pointer type of \c SDL_LogResetPriorities() */
typedef void (SDLCALL *SDL_LogResetPriorities_pfn)(void);

/** \brief Function pointer type of \c SDL_Log() */
typedef void (SDLCALL *SDL_Log_pfn)(const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogVerbose() */
typedef void (SDLCALL *SDL_LogVerbose_pfn)(int category, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogDebug() */
typedef void (SDLCALL *SDL_LogDebug_pfn)(int category, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogInfo() */
typedef void (SDLCALL *SDL_LogInfo_pfn)(int category, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogWarn() */
typedef void (SDLCALL *SDL_LogWarn_pfn)(int category, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogError() */
typedef void (SDLCALL *SDL_LogError_pfn)(int category, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogCritical() */
typedef void (SDLCALL *SDL_LogCritical_pfn)(int category,
                                            const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogMessage() */
typedef void (SDLCALL *SDL_LogMessage_pfn)(int category,
                                           SDL_LogPriority priority,
                                           const char *fmt, ...);

/** \brief Function pointer type of \c SDL_LogMessageV() */
typedef void (SDLCALL *SDL_LogMessageV_pfn)(int category,
                                            SDL_LogPriority priority,
                                            const char *fmt, va_list ap);

/** \brief Function pointer type of \c SDL_LogGetOutputFunction() */
typedef void
    (SDLCALL *SDL_LogGetOutputFunction_pfn)(SDL_LogOutputFunction *callback,
                                            void **userdata);

/** \brief Function pointer type of \c SDL_LogSetOutputFunction() */
typedef void
    (SDLCALL *SDL_LogSetOutputFunction_pfn)(SDL_LogOutputFunction callback,
                                            void *userdata);

/* SDL_main.h */

/** \brief Function pointer type of \c SDL_SetMainReady() */
typedef void (SDLCALL *SDL_SetMainReady_pfn)(void);

#if defined(__WIN32__) || DOXYGEN
/** \brief Function pointer type of \c SDL_RegisterApp() */
typedef int (SDLCALL *SDL_RegisterApp_pfn)(char *name, Uint32 style,
                                           void *hInst);

/** \brief Function pointer type of \c SDL_UnregisterApp() */
typedef void (SDLCALL *SDL_UnregisterApp_pfn)(void);
#endif /* __WIN32__ */

/* SDL_messagebox.h */

/** \brief Function pointer type of \c SDL_ShowMessageBox() */
typedef int (SDLCALL *SDL_ShowMessageBox_pfn)(
        const SDL_MessageBoxData *messageboxdata, int *buttonid);

/** \brief Function pointer type of \c SDL_ShowSimpleMessageBox() */
typedef int (SDLCALL *SDL_ShowSimpleMessageBox_pfn)(Uint32 flags,
                                                    const char *title,
                                                    const char *message,
                                                    SDL_Window *window);

/* SDL_mouse.h */

/** \brief Function pointer type of \c SDL_GetMouseFocus() */
typedef SDL_Window* (SDLCALL *SDL_GetMouseFocus_pfn)(void);

/** \brief Function pointer type of \c SDL_GetMouseState() */
typedef Uint32 (SDLCALL *SDL_GetMouseState_pfn)(int *x, int *y);

/** \brief Function pointer type of \c SDL_GetRelativeMouseState() */
typedef Uint32 (SDLCALL *SDL_GetRelativeMouseState_pfn)(int *x, int *y);

/** \brief Function pointer type of \c SDL_WarpMouseInWindow() */
typedef void (SDLCALL *SDL_WarpMouseInWindow_pfn)(SDL_Window *window, int x,
                                                  int y);

/** \brief Function pointer type of \c SDL_SetRelativeMouseMode() */
typedef int (SDLCALL *SDL_SetRelativeMouseMode_pfn)(SDL_bool enabled);

/** \brief Function pointer type of \c SDL_GetRelativeMouseMode() */
typedef SDL_bool (SDLCALL *SDL_GetRelativeMouseMode_pfn)(void);

/** \brief Function pointer type of \c SDL_CreateCursor() */
typedef SDL_Cursor* (SDLCALL *SDL_CreateCursor_pfn)(const Uint8 *data,
                                                    const Uint8 *mask, int w,
                                                    int h, int hot_x,
                                                    int hot_y);

/** \brief Function pointer type of \c SDL_CreateColorCursor() */
typedef SDL_Cursor* (SDLCALL *SDL_CreateColorCursor_pfn)(SDL_Surface *surface,
                                                         int hot_x, int hot_y);

/** \brief Function pointer type of \c SDL_CreateSystemCursor() */
typedef SDL_Cursor* (SDLCALL *SDL_CreateSystemCursor_pfn)(SDL_SystemCursor id);

/** \brief Function pointer type of \c SDL_SetCursor() */
typedef void (SDLCALL *SDL_SetCursor_pfn)(SDL_Cursor *cursor);

/** \brief Function pointer type of \c SDL_GetCursor() */
typedef SDL_Cursor* (SDLCALL *SDL_GetCursor_pfn)(void);

/** \brief Function pointer type of \c SDL_GetDefaultCursor() */
typedef SDL_Cursor* (SDLCALL *SDL_GetDefaultCursor_pfn)(void);

/** \brief Function pointer type of \c SDL_FreeCursor() */
typedef void (SDLCALL *SDL_FreeCursor_pfn)(SDL_Cursor *cursor);

/** \brief Function pointer type of \c SDL_ShowCursor() */
typedef int (SDLCALL *SDL_ShowCursor_pfn)(int toggle);

/* SDL_mutex.h */

/** \brief Function pointer type of \c SDL_CreateMutex() */
typedef SDL_mutex* (SDLCALL *SDL_CreateMutex_pfn)(void);

/** \brief Function pointer type of \c SDL_LockMutex() */
typedef int (SDLCALL *SDL_LockMutex_pfn)(SDL_mutex *mutex);

/** \brief Function pointer type of \c SDL_TryLockMutex() */
typedef int (SDLCALL *SDL_TryLockMutex_pfn)(SDL_mutex *mutex);

/** \brief Function pointer type of \c SDL_UnlockMutex() */
typedef int (SDLCALL *SDL_UnlockMutex_pfn)(SDL_mutex *mutex);

/** \brief Function pointer type of \c SDL_DestroyMutex() */
typedef void (SDLCALL *SDL_DestroyMutex_pfn)(SDL_mutex *mutex);

/** \brief Function pointer type of \c SDL_CreateSemaphore() */
typedef SDL_sem* (SDLCALL *SDL_CreateSemaphore_pfn)(Uint32 initial_value);

/** \brief Function pointer type of \c SDL_DestroySemaphore() */
typedef void (SDLCALL *SDL_DestroySemaphore_pfn)(SDL_sem *sem);

/** \brief Function pointer type of \c SDL_SemWait() */
typedef int (SDLCALL *SDL_SemWait_pfn)(SDL_sem *sem);

/** \brief Function pointer type of \c SDL_SemTryWait() */
typedef int (SDLCALL *SDL_SemTryWait_pfn)(SDL_sem *sem);

/** \brief Function pointer type of \c SDL_SemWaitTimeout() */
typedef int (SDLCALL *SDL_SemWaitTimeout_pfn)(SDL_sem *sem, Uint32 ms);

/** \brief Function pointer type of \c SDL_SemPost() */
typedef int (SDLCALL *SDL_SemPost_pfn)(SDL_sem *sem);

/** \brief Function pointer type of \c SDL_SemValue() */
typedef Uint32 (SDLCALL *SDL_SemValue_pfn)(SDL_sem *sem);

/** \brief Function pointer type of \c SDL_CreateCond() */
typedef SDL_cond* (SDLCALL *SDL_CreateCond_pfn)(void);

/** \brief Function pointer type of \c SDL_DestroyCond() */
typedef void (SDLCALL *SDL_DestroyCond_pfn)(SDL_cond *cond);

/** \brief Function pointer type of \c SDL_CondSignal() */
typedef int (SDLCALL *SDL_CondSignal_pfn)(SDL_cond *cond);

/** \brief Function pointer type of \c SDL_CondBroadcast() */
typedef int (SDLCALL *SDL_CondBroadcast_pfn)(SDL_cond *cond);

/** \brief Function pointer type of \c SDL_CondWait() */
typedef int (SDLCALL *SDL_CondWait_pfn)(SDL_cond *cond, SDL_mutex *mutex);

/** \brief Function pointer type of \c SDL_CondWaitTimeout() */
typedef int (SDLCALL *SDL_CondWaitTimeout_pfn)(SDL_cond *cond,
                                               SDL_mutex *mutex, Uint32 ms);

/* SDL_pixels.h */

/** \brief Function pointer type of \c SDL_GetPixelFormatName() */
typedef const char* (SDLCALL *SDL_GetPixelFormatName_pfn)(Uint32 format);

/** \brief Function pointer type of \c SDL_PixelFormatEnumToMasks() */
typedef SDL_bool (SDLCALL *SDL_PixelFormatEnumToMasks_pfn)(Uint32 format,
                                                           int *bpp,
                                                           Uint32 *Rmask,
                                                           Uint32 *Gmask,
                                                           Uint32 *Bmask,
                                                           Uint32 *Amask);

/** \brief Function pointer type of \c SDL_MasksToPixelFormatEnum() */
typedef Uint32 (SDLCALL *SDL_MasksToPixelFormatEnum_pfn)(int bpp, Uint32 Rmask,
                                                         Uint32 Gmask,
                                                         Uint32 Bmask,
                                                         Uint32 Amask);

/** \brief Function pointer type of \c SDL_AllocFormat() */
typedef SDL_PixelFormat* (SDLCALL *SDL_AllocFormat_pfn)(Uint32 pixel_format);

/** \brief Function pointer type of \c SDL_FreeFormat() */
typedef void (SDLCALL *SDL_FreeFormat_pfn)(SDL_PixelFormat *format);

/** \brief Function pointer type of \c SDL_AllocPalette() */
typedef SDL_Palette* (SDLCALL *SDL_AllocPalette_pfn)(int ncolors);

/** \brief Function pointer type of \c SDL_SetPixelFormatPalette() */
typedef int (SDLCALL *SDL_SetPixelFormatPalette_pfn)(SDL_PixelFormat *format,
                                                     SDL_Palette *palette);

/** \brief Function pointer type of \c SDL_SetPaletteColors() */
typedef int (SDLCALL *SDL_SetPaletteColors_pfn)(SDL_Palette *palette,
                                                const SDL_Color *colors,
                                                int firstcolor, int ncolors);

/** \brief Function pointer type of \c SDL_FreePalette() */
typedef void (SDLCALL *SDL_FreePalette_pfn)(SDL_Palette *palette);

/** \brief Function pointer type of \c SDL_MapRGB() */
typedef Uint32 (SDLCALL *SDL_MapRGB_pfn)(const SDL_PixelFormat *format,
                                         Uint8 r, Uint8 g, Uint8 b);

/** \brief Function pointer type of \c SDL_MapRGBA() */
typedef Uint32 (SDLCALL *SDL_MapRGBA_pfn)(const SDL_PixelFormat *format,
                                          Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/** \brief Function pointer type of \c SDL_GetRGB() */
typedef void (SDLCALL *SDL_GetRGB_pfn)(Uint32 pixel,
                                       const SDL_PixelFormat *format,
                                       Uint8 *r, Uint8 *g, Uint8 *b);

/** \brief Function pointer type of \c SDL_GetRGBA() */
typedef void (SDLCALL *SDL_GetRGBA_pfn)(Uint32 pixel,
                                        const SDL_PixelFormat *format,
                                        Uint8 *r, Uint8 *g, Uint8 *b,
                                        Uint8 *a);

/** \brief Function pointer type of \c SDL_CalculateGammaRamp() */
typedef void (SDLCALL *SDL_CalculateGammaRamp_pfn)(float gamma, Uint16 *ramp);

/* SDL_platform.h */

/** \brief Function pointer type of \c SDL_GetPlatform() */
typedef const char* (SDLCALL *SDL_GetPlatform_pfn)(void);

/* SDL_power.h */

/** \brief Function pointer type of \c SDL_GetPowerInfo() */
typedef SDL_PowerState (SDLCALL *SDL_GetPowerInfo_pfn)(int *secs, int *pct);

/* SDL_rect.h */

/** \brief Function pointer type of \c SDL_HasIntersection() */
typedef SDL_bool (SDLCALL *SDL_HasIntersection_pfn)(const SDL_Rect *A,
                                                    const SDL_Rect *B);

/** \brief Function pointer type of \c SDL_IntersectRect() */
typedef SDL_bool (SDLCALL *SDL_IntersectRect_pfn)(const SDL_Rect *A,
                                                  const SDL_Rect *B,
                                                  SDL_Rect *result);

/** \brief Function pointer type of \c SDL_UnionRect() */
typedef void (SDLCALL *SDL_UnionRect_pfn)(const SDL_Rect *A, const SDL_Rect *B,
                                          SDL_Rect *result);

/** \brief Function pointer type of \c SDL_EnclosePoints() */
typedef SDL_bool (SDLCALL *SDL_EnclosePoints_pfn)(const SDL_Point *points,
                                                  int count,
                                                  const SDL_Rect *clip,
                                                  SDL_Rect *result);

/** \brief Function pointer type of \c SDL_IntersectRectAndLine() */
typedef SDL_bool (SDLCALL *SDL_IntersectRectAndLine_pfn)(const SDL_Rect *rect,
                                                         int *X1, int *Y1,
                                                         int *X2, int *Y2);

/* SDL_render.h */

/** \brief Function pointer type of \c SDL_GetNumRenderDrivers() */
typedef int (SDLCALL *SDL_GetNumRenderDrivers_pfn)(void);

/** \brief Function pointer type of \c SDL_GetRenderDriverInfo() */
typedef int (SDLCALL *SDL_GetRenderDriverInfo_pfn)(int index,
                                                   SDL_RendererInfo *info);

/** \brief Function pointer type of \c SDL_CreateWindowAndRenderer() */
typedef int (SDLCALL *SDL_CreateWindowAndRenderer_pfn)(
        int width, int height, Uint32 window_flags, SDL_Window **window,
        SDL_Renderer **renderer);

/** \brief Function pointer type of \c SDL_CreateRenderer() */
typedef SDL_Renderer* (SDLCALL *SDL_CreateRenderer_pfn)(SDL_Window *window,
                                                        int index,
                                                        Uint32 flags);

/** \brief Function pointer type of \c SDL_CreateSoftwareRenderer() */
typedef SDL_Renderer* (SDLCALL *SDL_CreateSoftwareRenderer_pfn)(
        SDL_Surface *surface);

/** \brief Function pointer type of \c SDL_GetRenderer() */
typedef SDL_Renderer* (SDLCALL *SDL_GetRenderer_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_GetRendererInfo() */
typedef int (SDLCALL *SDL_GetRendererInfo_pfn)(SDL_Renderer *renderer,
                                               SDL_RendererInfo *info);

/** \brief Function pointer type of \c SDL_GetRendererOutputSize() */
typedef int (SDLCALL *SDL_GetRendererOutputSize_pfn)(SDL_Renderer *renderer,
                                                     int *w, int *h);

/** \brief Function pointer type of \c SDL_CreateTexture() */
typedef SDL_Texture* (SDLCALL *SDL_CreateTexture_pfn)(SDL_Renderer *renderer,
                                                      Uint32 format,
                                                      int access, int w,
                                                      int h);

/** \brief Function pointer type of \c SDL_CreateTextureFromSurface() */
typedef SDL_Texture* (SDLCALL *SDL_CreateTextureFromSurface_pfn)(
        SDL_Renderer *renderer, SDL_Surface *surface);

/** \brief Function pointer type of \c SDL_QueryTexture() */
typedef int (SDLCALL *SDL_QueryTexture_pfn)(SDL_Texture *texture,
                                            Uint32 *format, int *access,
                                            int *w, int *h);

/** \brief Function pointer type of \c SDL_SetTextureColorMod() */
typedef int (SDLCALL *SDL_SetTextureColorMod_pfn)(SDL_Texture *texture,
                                                  Uint8 r, Uint8 g, Uint8 b);

/** \brief Function pointer type of \c SDL_GetTextureColorMod() */
typedef int (SDLCALL *SDL_GetTextureColorMod_pfn)(SDL_Texture *texture,
                                                  Uint8 *r, Uint8 *g,
                                                  Uint8 *b);

/** \brief Function pointer type of \c SDL_SetTextureAlphaMod() */
typedef int (SDLCALL *SDL_SetTextureAlphaMod_pfn)(SDL_Texture *texture,
                                                  Uint8 alpha);

/** \brief Function pointer type of \c SDL_GetTextureAlphaMod() */
typedef int (SDLCALL *SDL_GetTextureAlphaMod_pfn)(SDL_Texture *texture,
                                                  Uint8 *alpha);

/** \brief Function pointer type of \c SDL_SetTextureBlendMode() */
typedef int (SDLCALL *SDL_SetTextureBlendMode_pfn)(SDL_Texture *texture,
                                                   SDL_BlendMode blendMode);

/** \brief Function pointer type of \c SDL_GetTextureBlendMode() */
typedef int (SDLCALL *SDL_GetTextureBlendMode_pfn)(SDL_Texture *texture,
                                                   SDL_BlendMode *blendMode);

/** \brief Function pointer type of \c SDL_UpdateTexture() */
typedef int (SDLCALL *SDL_UpdateTexture_pfn)(SDL_Texture *texture,
                                             const SDL_Rect *rect,
                                             const void *pixels, int pitch);

/** \brief Function pointer type of \c SDL_LockTexture() */
typedef int (SDLCALL *SDL_LockTexture_pfn)(SDL_Texture *texture,
                                           const SDL_Rect *rect, void **pixels,
                                           int *pitch);

/** \brief Function pointer type of \c SDL_UnlockTexture() */
typedef void (SDLCALL *SDL_UnlockTexture_pfn)(SDL_Texture *texture);

/** \brief Function pointer type of \c SDL_RenderTargetSupported() */
typedef SDL_bool (SDLCALL *SDL_RenderTargetSupported_pfn)(
        SDL_Renderer *renderer);

/** \brief Function pointer type of \c SDL_SetRenderTarget() */
typedef int (SDLCALL *SDL_SetRenderTarget_pfn)(SDL_Renderer *renderer,
                                               SDL_Texture *texture);

/** \brief Function pointer type of \c SDL_GetRenderTarget() */
typedef SDL_Texture* (SDLCALL *SDL_GetRenderTarget_pfn)(
        SDL_Renderer *renderer);

/** \brief Function pointer type of \c SDL_RenderSetLogicalSize() */
typedef int (SDLCALL *SDL_RenderSetLogicalSize_pfn)(SDL_Renderer *renderer,
                                                    int w, int h);

/** \brief Function pointer type of \c SDL_RenderGetLogicalSize() */
typedef void (SDLCALL *SDL_RenderGetLogicalSize_pfn)(SDL_Renderer *renderer,
                                                     int *w, int *h);

/** \brief Function pointer type of \c SDL_RenderSetViewport() */
typedef int (SDLCALL *SDL_RenderSetViewport_pfn)(SDL_Renderer *renderer,
                                                 const SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderGetViewport() */
typedef void (SDLCALL *SDL_RenderGetViewport_pfn)(SDL_Renderer *renderer,
                                                  SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderSetClipRect() */
typedef int (SDLCALL *SDL_RenderSetClipRect_pfn)(SDL_Renderer *renderer,
                                                 const SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderGetClipRect() */
typedef void (SDLCALL *SDL_RenderGetClipRect_pfn)(SDL_Renderer *renderer,
                                                  SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderSetScale() */
typedef int (SDLCALL *SDL_RenderSetScale_pfn)(SDL_Renderer *renderer,
                                              float scaleX, float scaleY);

/** \brief Function pointer type of \c SDL_RenderGetScale() */
typedef void (SDLCALL *SDL_RenderGetScale_pfn)(SDL_Renderer *renderer,
                                               float *scaleX, float *scaleY);

/** \brief Function pointer type of \c SDL_SetRenderDrawColor() */
typedef int (SDLCALL *SDL_SetRenderDrawColor_pfn)(SDL_Renderer *renderer,
                                                  Uint8 r, Uint8 g, Uint8 b,
                                                  Uint8 a);

/** \brief Function pointer type of \c SDL_GetRenderDrawColor() */
typedef int (SDLCALL *SDL_GetRenderDrawColor_pfn)(SDL_Renderer *renderer,
                                                  Uint8 *r, Uint8 *g, Uint8 *b,
                                                  Uint8 *a);

/** \brief Function pointer type of \c SDL_SetRenderDrawBlendMode() */
typedef int (SDLCALL *SDL_SetRenderDrawBlendMode_pfn)(SDL_Renderer *renderer,
                                                      SDL_BlendMode blendMode);

/** \brief Function pointer type of \c SDL_GetRenderDrawBlendMode() */
typedef int (SDLCALL *SDL_GetRenderDrawBlendMode_pfn)(SDL_Renderer *renderer,
                                                      SDL_BlendMode *blendMode
                                                      );

/** \brief Function pointer type of \c SDL_RenderClear() */
typedef int (SDLCALL *SDL_RenderClear_pfn)(SDL_Renderer *renderer);

/** \brief Function pointer type of \c SDL_RenderDrawPoint() */
typedef int (SDLCALL *SDL_RenderDrawPoint_pfn)(SDL_Renderer *renderer, int x,
                                               int y);

/** \brief Function pointer type of \c SDL_RenderDrawPoints() */
typedef int (SDLCALL *SDL_RenderDrawPoints_pfn)(SDL_Renderer *renderer,
                                                const SDL_Point *points,
                                                int count);

/** \brief Function pointer type of \c SDL_RenderDrawLine() */
typedef int (SDLCALL *SDL_RenderDrawLine_pfn)(SDL_Renderer *renderer, int x1,
                                              int y1, int x2, int y2);

/** \brief Function pointer type of \c SDL_RenderDrawLines() */
typedef int (SDLCALL *SDL_RenderDrawLines_pfn)(SDL_Renderer *renderer,
                                               const SDL_Point *points,
                                               int count);

/** \brief Function pointer type of \c SDL_RenderDrawRect() */
typedef int (SDLCALL *SDL_RenderDrawRect_pfn)(SDL_Renderer *renderer,
                                              const SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderDrawRects() */
typedef int (SDLCALL *SDL_RenderDrawRects_pfn)(SDL_Renderer *renderer,
                                               const SDL_Rect *rects,
                                               int count);

/** \brief Function pointer type of \c SDL_RenderFillRect() */
typedef int (SDLCALL *SDL_RenderFillRect_pfn)(SDL_Renderer *renderer,
                                              const SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_RenderFillRects() */
typedef int (SDLCALL *SDL_RenderFillRects_pfn)(SDL_Renderer *renderer,
                                               const SDL_Rect *rects,
                                               int count);

/** \brief Function pointer type of \c SDL_RenderCopy() */
typedef int (SDLCALL *SDL_RenderCopy_pfn)(SDL_Renderer *renderer,
                                          SDL_Texture *texture,
                                          const SDL_Rect *srcrect,
                                          const SDL_Rect *dstrect);

/** \brief Function pointer type of \c SDL_RenderCopyEx() */
typedef int (SDLCALL *SDL_RenderCopyEx_pfn)(SDL_Renderer *renderer,
                                            SDL_Texture *texture,
                                            const SDL_Rect *srcrect,
                                            const SDL_Rect *dstrect,
                                            const double angle,
                                            const SDL_Point *center,
                                            const SDL_RendererFlip flip);

/** \brief Function pointer type of \c SDL_RenderReadPixels() */
typedef int (SDLCALL *SDL_RenderReadPixels_pfn)(SDL_Renderer *renderer,
                                                const SDL_Rect *rect,
                                                Uint32 format, void *pixels,
                                                int pitch);

/** \brief Function pointer type of \c SDL_RenderPresent() */
typedef void (SDLCALL *SDL_RenderPresent_pfn)(SDL_Renderer *renderer);

/** \brief Function pointer type of \c SDL_DestroyTexture() */
typedef void (SDLCALL *SDL_DestroyTexture_pfn)(SDL_Texture *texture);

/** \brief Function pointer type of \c SDL_DestroyRenderer() */
typedef void (SDLCALL *SDL_DestroyRenderer_pfn)(SDL_Renderer *renderer);

/** \brief Function pointer type of \c SDL_GL_BindTexture() */
typedef int (SDLCALL *SDL_GL_BindTexture_pfn)(SDL_Texture *texture,
                                              float *texw, float *texh);

/** \brief Function pointer type of \c SDL_GL_UnbindTexture() */
typedef int (SDLCALL *SDL_GL_UnbindTexture_pfn)(SDL_Texture *texture);

/* SDL_rwops.h */

/** \brief Function pointer type of \c SDL_RWFromFile() */
typedef SDL_RWops* (SDLCALL *SDL_RWFromFile_pfn)(const char *file,
                                                 const char *mode);

#if defined(HAVE_STDIO_H) || DOXYGEN
/** \brief Function pointer type of \c SDL_RWFromFP() */
typedef SDL_RWops* (SDLCALL *SDL_RWFromFP_pfn)(FILE *fp, SDL_bool autoclose);
#else
typedef SDL_RWops* (SDLCALL *SDL_RWFromFP_pfn)(void *fp, SDL_bool autoclose);
#endif

/** \brief Function pointer type of \c SDL_RWFromMem() */
typedef SDL_RWops* (SDLCALL *SDL_RWFromMem_pfn)(void *mem, int size);

/** \brief Function pointer type of \c SDL_RWFromConstMem() */
typedef SDL_RWops* (SDLCALL *SDL_RWFromConstMem_pfn)(const void *mem,
                                                     int size);

/** \brief Function pointer type of \c SDL_AllocRW() */
typedef SDL_RWops* (SDLCALL *SDL_AllocRW_pfn)(void);

/** \brief Function pointer type of \c SDL_FreeRW() */
typedef void (SDLCALL *SDL_FreeRW_pfn)(SDL_RWops *area);

/** \brief Function pointer type of \c SDL_ReadU8() */
typedef Uint8 (SDLCALL *SDL_ReadU8_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadLE16() */
typedef Uint16 (SDLCALL *SDL_ReadLE16_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadBE16() */
typedef Uint16 (SDLCALL *SDL_ReadBE16_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadLE32() */
typedef Uint32 (SDLCALL *SDL_ReadLE32_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadBE32() */
typedef Uint32 (SDLCALL *SDL_ReadBE32_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadLE64() */
typedef Uint64 (SDLCALL *SDL_ReadLE64_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_ReadBE64() */
typedef Uint64 (SDLCALL *SDL_ReadBE64_pfn)(SDL_RWops *src);

/** \brief Function pointer type of \c SDL_WriteU8() */
typedef size_t (SDLCALL *SDL_WriteU8_pfn)(SDL_RWops *dst, Uint8 value);

/** \brief Function pointer type of \c SDL_WriteLE16() */
typedef size_t (SDLCALL *SDL_WriteLE16_pfn)(SDL_RWops *dst, Uint16 value);

/** \brief Function pointer type of \c SDL_WriteBE16() */
typedef size_t (SDLCALL *SDL_WriteBE16_pfn)(SDL_RWops *dst, Uint16 value);

/** \brief Function pointer type of \c SDL_WriteLE32() */
typedef size_t (SDLCALL *SDL_WriteLE32_pfn)(SDL_RWops *dst, Uint32 value);

/** \brief Function pointer type of \c SDL_WriteBE32() */
typedef size_t (SDLCALL *SDL_WriteBE32_pfn)(SDL_RWops *dst, Uint32 value);

/** \brief Function pointer type of \c SDL_WriteLE64() */
typedef size_t (SDLCALL *SDL_WriteLE64_pfn)(SDL_RWops *dst, Uint64 value);

/** \brief Function pointer type of \c SDL_WriteBE64() */
typedef size_t (SDLCALL *SDL_WriteBE64_pfn)(SDL_RWops *dst, Uint64 value);

/* SDL_shape.h */

/** \brief Function pointer type of \c SDL_CreateShapedWindow() */
typedef SDL_Window* (SDLCALL *SDL_CreateShapedWindow_pfn)(const char *title,
                                                          unsigned int x,
                                                          unsigned int y,
                                                          unsigned int w,
                                                          unsigned int h,
                                                          Uint32 flags);

/** \brief Function pointer type of \c SDL_IsShapedWindow() */
typedef SDL_bool (SDLCALL *SDL_IsShapedWindow_pfn)(const SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowShape() */
typedef int (SDLCALL *SDL_SetWindowShape_pfn)(SDL_Window *window,
                                              SDL_Surface *shape,
                                              SDL_WindowShapeMode *shape_mode);

/** \brief Function pointer type of \c SDL_GetShapedWindowMode() */
typedef int (SDLCALL *SDL_GetShapedWindowMode_pfn)(
        SDL_Window *window, SDL_WindowShapeMode *shape_mode);

/* SDL_stdinc.h */

/** \brief Function pointer type of \c SDL_malloc() */
typedef void* (SDLCALL *SDL_malloc_pfn)(size_t size);

/** \brief Function pointer type of \c SDL_calloc() */
typedef void* (SDLCALL *SDL_calloc_pfn)(size_t nmemb, size_t size);

/** \brief Function pointer type of \c SDL_realloc() */
typedef void* (SDLCALL *SDL_realloc_pfn)(void *mem, size_t size);

/** \brief Function pointer type of \c SDL_free() */
typedef void (SDLCALL *SDL_free_pfn)(void *mem);

/** \brief Function pointer type of \c SDL_getenv() */
typedef char* (SDLCALL *SDL_getenv_pfn)(const char *name);

/** \brief Function pointer type of \c SDL_setenv() */
typedef int (SDLCALL *SDL_setenv_pfn)(const char *name, const char *value,
                              int overwrite);

/** \brief Function pointer type of \c SDL_qsort() */
typedef void (SDLCALL *SDL_qsort_pfn)(void *base, size_t nmemb, size_t size,
                              int (*compare)(const void*, const void*));

/** \brief Function pointer type of \c SDL_abs() */
typedef int (SDLCALL *SDL_abs_pfn)(int x);

/** \brief Function pointer type of \c SDL_isdigit() */
typedef int (SDLCALL *SDL_isdigit_pfn)(int x);

/** \brief Function pointer type of \c SDL_isspace() */
typedef int (SDLCALL *SDL_isspace_pfn)(int x);

/** \brief Function pointer type of \c SDL_toupper() */
typedef int (SDLCALL *SDL_toupper_pfn)(int x);

/** \brief Function pointer type of \c SDL_tolower() */
typedef int (SDLCALL *SDL_tolower_pfn)(int x);

/** \brief Function pointer type of \c SDL_memset() */
typedef void* (SDLCALL *SDL_memset_pfn)(void *dst, int c, size_t len);

/** \brief Function pointer type of \c SDL_memcpy() */
typedef void* (SDLCALL *SDL_memcpy_pfn)(void *dst, const void *src,
                                        size_t len);

/** \brief Function pointer type of \c SDL_memmove() */
typedef void* (SDLCALL *SDL_memmove_pfn)(void *dst, const void *src,
                                         size_t len);

/** \brief Function pointer type of \c SDL_memcmp() */
typedef int (SDLCALL *SDL_memcmp_pfn)(const void *s1, const void *s2,
                                      size_t len);

/** \brief Function pointer type of \c SDL_wcslen() */
typedef size_t (SDLCALL *SDL_wcslen_pfn)(const wchar_t *wstr);

/** \brief Function pointer type of \c SDL_wcslcpy() */
typedef size_t (SDLCALL *SDL_wcslcpy_pfn)(wchar_t *dst, const wchar_t *src,
                                  size_t maxlen);

/** \brief Function pointer type of \c SDL_wcslcat() */
typedef size_t (SDLCALL *SDL_wcslcat_pfn)(wchar_t *dst, const wchar_t *src,
                                  size_t maxlen);

/** \brief Function pointer type of \c SDL_strlen() */
typedef size_t (SDLCALL *SDL_strlen_pfn)(const char *str);

/** \brief Function pointer type of \c SDL_strlcpy() */
typedef size_t (SDLCALL *SDL_strlcpy_pfn)(char *dst, const char *src,
                                          size_t maxlen);

/** \brief Function pointer type of \c SDL_utf8strlcpy() */
typedef size_t (SDLCALL *SDL_utf8strlcpy_pfn)(char *dst, const char *src,
                                              size_t dst_bytes);

/** \brief Function pointer type of \c SDL_strlcat() */
typedef size_t (SDLCALL *SDL_strlcat_pfn)(char *dst, const char *src,
                                          size_t maxlen);

/** \brief Function pointer type of \c SDL_strdup() */
typedef char* (SDLCALL *SDL_strdup_pfn)(const char *str);

/** \brief Function pointer type of \c SDL_strrev() */
typedef char* (SDLCALL *SDL_strrev_pfn)(char *str);

/** \brief Function pointer type of \c SDL_strupr() */
typedef char* (SDLCALL *SDL_strupr_pfn)(char *str);

/** \brief Function pointer type of \c SDL_strlwr() */
typedef char* (SDLCALL *SDL_strlwr_pfn)(char *str);

/** \brief Function pointer type of \c SDL_strchr() */
typedef char* (SDLCALL *SDL_strchr_pfn)(const char *str, int c);

/** \brief Function pointer type of \c SDL_strrchr() */
typedef char* (SDLCALL *SDL_strrchr_pfn)(const char *str, int c);

/** \brief Function pointer type of \c SDL_strstr() */
typedef char* (SDLCALL *SDL_strstr_pfn)(const char *haystack,
                                        const char *needle);

/** \brief Function pointer type of \c SDL_itoa() */
typedef char* (SDLCALL *SDL_itoa_pfn)(int value, char *str, int radix);

/** \brief Function pointer type of \c SDL_uitoa() */
typedef char* (SDLCALL *SDL_uitoa_pfn)(unsigned int value, char *str,
                                       int radix);

/** \brief Function pointer type of \c SDL_ltoa() */
typedef char* (SDLCALL *SDL_ltoa_pfn)(long value, char *str, int radix);

/** \brief Function pointer type of \c SDL_ultoa() */
typedef char* (SDLCALL *SDL_ultoa_pfn)(unsigned long value, char *str,
                                       int radix);

/** \brief Function pointer type of \c SDL_lltoa() */
typedef char* (SDLCALL *SDL_lltoa_pfn)(Sint64 value, char *str, int radix);

/** \brief Function pointer type of \c SDL_ulltoa() */
typedef char* (SDLCALL *SDL_ulltoa_pfn)(Uint64 value, char *str, int radix);

/** \brief Function pointer type of \c SDL_atoi() */
typedef int (SDLCALL *SDL_atoi_pfn)(const char *str);

/** \brief Function pointer type of \c SDL_atof() */
typedef double (SDLCALL *SDL_atof_pfn)(const char *str);

/** \brief Function pointer type of \c SDL_strtol() */
typedef long (SDLCALL *SDL_strtol_pfn)(const char *str, char **endp, int base);

/** \brief Function pointer type of \c SDL_strtoul() */
typedef unsigned long (SDLCALL *SDL_strtoul_pfn)(const char *str, char **endp,
                                                 int base);

/** \brief Function pointer type of \c SDL_strtoll() */
typedef Sint64 (SDLCALL *SDL_strtoll_pfn)(const char *str, char **endp,
                                          int base);

/** \brief Function pointer type of \c SDL_strtoull() */
typedef Uint64 (SDLCALL *SDL_strtoull_pfn)(const char *str, char **endp,
                                           int base);

/** \brief Function pointer type of \c SDL_strtod() */
typedef double (SDLCALL *SDL_strtod_pfn)(const char *str, char **endp);

/** \brief Function pointer type of \c SDL_strcmp() */
typedef int (SDLCALL *SDL_strcmp_pfn)(const char *str1, const char *str2);

/** \brief Function pointer type of \c SDL_strncmp() */
typedef int (SDLCALL *SDL_strncmp_pfn)(const char *str1, const char *str2,
                                       size_t maxlen);

/** \brief Function pointer type of \c SDL_strcasecmp() */
typedef int (SDLCALL *SDL_strcasecmp_pfn)(const char *str1, const char *str2);

/** \brief Function pointer type of \c SDL_strncasecmp() */
typedef int (SDLCALL *SDL_strncasecmp_pfn)(const char *str1, const char *str2,
                                           size_t len);

/** \brief Function pointer type of \c SDL_sscanf() */
typedef int (SDLCALL *SDL_sscanf_pfn)(const char *text, const char *fmt, ...);

/** \brief Function pointer type of \c SDL_snprintf() */
typedef int (SDLCALL *SDL_snprintf_pfn)(char *text, size_t maxlen,
                                        const char *fmt, ...);

/** \brief Function pointer type of \c SDL_vsnprintf() */
typedef int (SDLCALL *SDL_vsnprintf_pfn)(char *text, size_t maxlen,
                                         const char *fmt, va_list ap);

/** \brief Function pointer type of \c SDL_atan() */
typedef double (SDLCALL *SDL_atan_pfn)(double x);

/** \brief Function pointer type of \c SDL_atan2() */
typedef double (SDLCALL *SDL_atan2_pfn)(double x, double y);

/** \brief Function pointer type of \c SDL_ceil() */
typedef double (SDLCALL *SDL_ceil_pfn)(double x);

/** \brief Function pointer type of \c SDL_copysign() */
typedef double (SDLCALL *SDL_copysign_pfn)(double x, double y);

/** \brief Function pointer type of \c SDL_cos() */
typedef double (SDLCALL *SDL_cos_pfn)(double x);

/** \brief Function pointer type of \c SDL_cosf() */
typedef float (SDLCALL *SDL_cosf_pfn)(float x);

/** \brief Function pointer type of \c SDL_fabs() */
typedef double (SDLCALL *SDL_fabs_pfn)(double x);

/** \brief Function pointer type of \c SDL_floor() */
typedef double (SDLCALL *SDL_floor_pfn)(double x);

/** \brief Function pointer type of \c SDL_log() */
typedef double (SDLCALL *SDL_log_pfn)(double x);

/** \brief Function pointer type of \c SDL_pow() */
typedef double (SDLCALL *SDL_pow_pfn)(double x, double y);

/** \brief Function pointer type of \c SDL_scalbn() */
typedef double (SDLCALL *SDL_scalbn_pfn)(double x, int n);

/** \brief Function pointer type of \c SDL_sin() */
typedef double (SDLCALL *SDL_sin_pfn)(double x);

/** \brief Function pointer type of \c SDL_sinf() */
typedef float (SDLCALL *SDL_sinf_pfn)(float x);

/** \brief Function pointer type of \c SDL_sqrt() */
typedef double (SDLCALL *SDL_sqrt_pfn)(double x);

/** \brief Function pointer type of \c SDL_iconv_open() */
typedef SDL_iconv_t (SDLCALL *SDL_iconv_open_pfn)(const char *tocode,
                                                  const char *fromcode);

/** \brief Function pointer type of \c SDL_iconv_close() */
typedef int (SDLCALL *SDL_iconv_close_pfn)(SDL_iconv_t cd);

/** \brief Function pointer type of \c SDL_iconv() */
typedef size_t (SDLCALL *SDL_iconv_pfn)(SDL_iconv_t cd, const char **inbuf,
                                        size_t *inbytesleft, char **outbuf,
                                        size_t *outbytesleft);

/** \brief Function pointer type of \c SDL_iconv_string() */
typedef char* (SDLCALL *SDL_iconv_string_pfn)(const char *tocode,
                                              const char *fromcode,
                                              const char *inbuf,
                                              size_t inbytesleft);

/* SDL_surface.h */

/** \brief Function pointer type of \c SDL_CreateRGBSurface() */
typedef SDL_Surface* (SDLCALL *SDL_CreateRGBSurface_pfn)(Uint32 flags,
                                                         int width, int height,
                                                         int depth,
                                                         Uint32 Rmask,
                                                         Uint32 Gmask,
                                                         Uint32 Bmask,
                                                         Uint32 Amask);

/** \brief Function pointer type of \c SDL_CreateRGBSurfaceFrom() */
typedef SDL_Surface* (SDLCALL *SDL_CreateRGBSurfaceFrom_pfn)(void *pixels,
                                                             int width,
                                                             int height,
                                                             int depth,
                                                             int pitch,
                                                             Uint32 Rmask,
                                                             Uint32 Gmask,
                                                             Uint32 Bmask,
                                                             Uint32 Amask);

/** \brief Function pointer type of \c SDL_FreeSurface() */
typedef void (SDLCALL *SDL_FreeSurface_pfn)(SDL_Surface *surface);

/** \brief Function pointer type of \c SDL_SetSurfacePalette() */
typedef int (SDLCALL *SDL_SetSurfacePalette_pfn)(SDL_Surface *surface,
                                                 SDL_Palette *palette);

/** \brief Function pointer type of \c SDL_LockSurface() */
typedef int (SDLCALL *SDL_LockSurface_pfn)(SDL_Surface *surface);

/** \brief Function pointer type of \c SDL_UnlockSurface() */
typedef void (SDLCALL *SDL_UnlockSurface_pfn)(SDL_Surface *surface);

/** \brief Function pointer type of \c SDL_LoadBMP_RW() */
typedef SDL_Surface* (SDLCALL *SDL_LoadBMP_RW_pfn)(SDL_RWops *src,
                                                   int freesrc);

/** \brief Function pointer type of \c SDL_SaveBMP_RW() */
typedef int (SDLCALL *SDL_SaveBMP_RW_pfn)(SDL_Surface *surface, SDL_RWops *dst,
                                          int freedst);

/** \brief Function pointer type of \c SDL_SetSurfaceRLE() */
typedef int (SDLCALL *SDL_SetSurfaceRLE_pfn)(SDL_Surface *surface, int flag);

/** \brief Function pointer type of \c SDL_SetColorKey() */
typedef int (SDLCALL *SDL_SetColorKey_pfn)(SDL_Surface *surface, int flag,
                                           Uint32 key);

/** \brief Function pointer type of \c SDL_GetColorKey() */
typedef int (SDLCALL *SDL_GetColorKey_pfn)(SDL_Surface *surface, Uint32 *key);

/** \brief Function pointer type of \c SDL_SetSurfaceColorMod() */
typedef int (SDLCALL *SDL_SetSurfaceColorMod_pfn)(SDL_Surface *surface,
                                                  Uint8 r, Uint8 g, Uint8 b);

/** \brief Function pointer type of \c SDL_GetSurfaceColorMod() */
typedef int (SDLCALL *SDL_GetSurfaceColorMod_pfn)(SDL_Surface *surface,
                                                  Uint8 *r, Uint8 *g,
                                                  Uint8 *b);

/** \brief Function pointer type of \c SDL_SetSurfaceAlphaMod() */
typedef int (SDLCALL *SDL_SetSurfaceAlphaMod_pfn)(SDL_Surface *surface,
                                                  Uint8 alpha);

/** \brief Function pointer type of \c SDL_GetSurfaceAlphaMod() */
typedef int (SDLCALL *SDL_GetSurfaceAlphaMod_pfn)(SDL_Surface *surface,
                                                  Uint8 *alpha);

/** \brief Function pointer type of \c SDL_SetSurfaceBlendMode() */
typedef int (SDLCALL *SDL_SetSurfaceBlendMode_pfn)(SDL_Surface *surface,
                                                   SDL_BlendMode blendMode);

/** \brief Function pointer type of \c SDL_GetSurfaceBlendMode() */
typedef int (SDLCALL *SDL_GetSurfaceBlendMode_pfn)(SDL_Surface *surface,
                                                   SDL_BlendMode *blendMode);

/** \brief Function pointer type of \c SDL_SetClipRect() */
typedef SDL_bool (SDLCALL *SDL_SetClipRect_pfn)(SDL_Surface *surface,
                                                const SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_GetClipRect() */
typedef void (SDLCALL *SDL_GetClipRect_pfn)(SDL_Surface *surface,
                                            SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_ConvertSurface() */
typedef SDL_Surface* (SDLCALL *SDL_ConvertSurface_pfn)(
        SDL_Surface *src, SDL_PixelFormat *fmt, Uint32 flags);

/** \brief Function pointer type of \c SDL_ConvertSurfaceFormat() */
typedef SDL_Surface* (SDLCALL *SDL_ConvertSurfaceFormat_pfn)(
        SDL_Surface *src, Uint32 pixel_format, Uint32 flags);

/** \brief Function pointer type of \c SDL_ConvertPixels() */
typedef int (SDLCALL *SDL_ConvertPixels_pfn)(int width, int height,
                                             Uint32 src_format,
                                             const void *src, int src_pitch,
                                             Uint32 dst_format, void *dst,
                                             int dst_pitch);

/** \brief Function pointer type of \c SDL_FillRect() */
typedef int (SDLCALL *SDL_FillRect_pfn)(SDL_Surface *dst, const SDL_Rect *rect,
                                        Uint32 color);

/** \brief Function pointer type of \c SDL_FillRects() */
typedef int (SDLCALL *SDL_FillRects_pfn)(SDL_Surface *dst,
                                         const SDL_Rect *rects, int count,
                                         Uint32 color);

/** \brief Function pointer type of \c SDL_UpperBlit() */
typedef int (SDLCALL *SDL_UpperBlit_pfn)(SDL_Surface *src,
                                         const SDL_Rect *srcrect,
                                         SDL_Surface *dst, SDL_Rect *dstrect);

/** \brief Function pointer type of \c SDL_LowerBlit() */
typedef int (SDLCALL *SDL_LowerBlit_pfn)(SDL_Surface *src, SDL_Rect *srcrect,
                                         SDL_Surface *dst, SDL_Rect *dstrect);

/** \brief Function pointer type of \c SDL_SoftStretch() */
typedef int (SDLCALL *SDL_SoftStretch_pfn)(SDL_Surface *src,
                                           const SDL_Rect *srcrect,
                                           SDL_Surface *dst,
                                           const SDL_Rect *dstrect);

/** \brief Function pointer type of \c SDL_UpperBlitScaled() */
typedef int (SDLCALL *SDL_UpperBlitScaled_pfn)(SDL_Surface *src,
                                               const SDL_Rect *srcrect,
                                               SDL_Surface *dst,
                                               SDL_Rect *dstrect);

/** \brief Function pointer type of \c SDL_LowerBlitScaled() */
typedef int (SDLCALL *SDL_LowerBlitScaled_pfn)(SDL_Surface *src,
                                               SDL_Rect *srcrect,
                                               SDL_Surface *dst,
                                               SDL_Rect *dstrect);

/* SDL_system.h */

#if defined(__IPHONEOS__) && __IPHONEOS__ || DOXYGEN
/** \brief Function pointer type of \c SDL_iPhoneSetAnimationCallback() */
typedef int (SDLCALL *SDL_iPhoneSetAnimationCallback_pfn)(SDL_Window *window,
        int interval, void (*callback)(void*), void *callbackParam);

/** \brief Function pointer type of \c SDL_iPhoneSetEventPump() */
typedef void (SDLCALL *SDL_iPhoneSetEventPump_pfn)(SDL_bool enabled);
#endif

#if defined(__ANDROID__) && __ANDROID__ || DOXYGEN
/** \brief Function pointer type of \c SDL_AndroidGetJNIEnv() */
typedef void* (SDLCALL *SDL_AndroidGetJNIEnv_pfn)(void);

/** \brief Function pointer type of \c SDL_AndroidGetActivity() */
typedef void* (SDLCALL *SDL_AndroidGetActivity_pfn)(void);

/** \brief Function pointer type of \c SDL_AndroidGetInternalStoragePath() */
typedef const char* (SDLCALL *SDL_AndroidGetInternalStoragePath_pfn)(void);

/** \brief Function pointer type of \c SDL_AndroidGetExternalStorageState() */
typedef int (SDLCALL *SDL_AndroidGetExternalStorageState_pfn)(void);

/** \brief Function pointer type of \c SDL_AndroidGetExternalStoragePath() */
typedef const char* (SDLCALL *SDL_AndroidGetExternalStoragePath_pfn)(void);
#endif

/* SDL_syswm.h */

/** \brief Function pointer type of \c SDL_GetWindowWMInfo() */
typedef SDL_bool (SDLCALL *SDL_GetWindowWMInfo_pfn)(SDL_Window *window,
                                                    SDL_SysWMinfo *info);

/* SDL_thread.h */

#if defined(__WIN32__) && !defined(HAVE_LIBC)
typedef SDL_Thread* (SDLCALL *SDL_CreateThread_pfn)(
        SDL_ThreadFunction fn, const char *name, void *data,
     pfnSDL_CurrentBeginThread pfnBeginThread,
     pfnSDL_CurrentEndThread pfnEndThread);
#else
/** \brief Function pointer type of \c SDL_CreateThread() */
typedef SDL_Thread* (SDLCALL *SDL_CreateThread_pfn)(SDL_ThreadFunction fn,
                                                    const char *name,
                                                    void *data);
#endif

/** \brief Function pointer type of \c SDL_GetThreadName() */
typedef const char* (SDLCALL *SDL_GetThreadName_pfn)(SDL_Thread *thread);

/** \brief Function pointer type of \c SDL_ThreadID() */
typedef SDL_threadID (SDLCALL *SDL_ThreadID_pfn)(void);

/** \brief Function pointer type of \c SDL_GetThreadID() */
typedef SDL_threadID (SDLCALL *SDL_GetThreadID_pfn)(SDL_Thread *thread);

/** \brief Function pointer type of \c SDL_SetThreadPriority() */
typedef int (SDLCALL *SDL_SetThreadPriority_pfn)(SDL_ThreadPriority priority);

/** \brief Function pointer type of \c SDL_WaitThread() */
typedef void (SDLCALL *SDL_WaitThread_pfn)(SDL_Thread *thread, int *status);

/** \brief Function pointer type of \c SDL_TLSCreate() */
typedef SDL_TLSID (SDLCALL *SDL_TLSCreate_pfn)(void);

/** \brief Function pointer type of \c SDL_TLSGet() */
typedef void* (SDLCALL *SDL_TLSGet_pfn)(SDL_TLSID id);

/** \brief Function pointer type of \c SDL_TLSSet() */
typedef int (SDLCALL *SDL_TLSSet_pfn)(SDL_TLSID id, const void *value,
                                      void (*destructor)(void*));

/* SDL_timer.h */

/** \brief Function pointer type of \c SDL_GetTicks() */
typedef Uint32 (SDLCALL *SDL_GetTicks_pfn)(void);

/** \brief Function pointer type of \c SDL_GetPerformanceCounter() */
typedef Uint64 (SDLCALL *SDL_GetPerformanceCounter_pfn)(void);

/** \brief Function pointer type of \c SDL_GetPerformanceFrequency() */
typedef Uint64 (SDLCALL *SDL_GetPerformanceFrequency_pfn)(void);

/** \brief Function pointer type of \c SDL_Delay() */
typedef void (SDLCALL *SDL_Delay_pfn)(Uint32 ms);

/** \brief Function pointer type of \c SDL_AddTimer() */
typedef SDL_TimerID (SDLCALL *SDL_AddTimer_pfn)(Uint32 interval,
                                                SDL_TimerCallback callback,
                                                void *param);

/** \brief Function pointer type of \c SDL_RemoveTimer() */
typedef SDL_bool (SDLCALL *SDL_RemoveTimer_pfn)(SDL_TimerID id);

/* SDL_touch.h (4) */

/** \brief Function pointer type of \c SDL_GetNumTouchDevices() */
typedef int (SDLCALL *SDL_GetNumTouchDevices_pfn)(void);

/** \brief Function pointer type of \c SDL_GetTouchDevice() */
typedef SDL_TouchID (SDLCALL *SDL_GetTouchDevice_pfn)(int index);

/** \brief Function pointer type of \c SDL_GetNumTouchFingers() */
typedef int (SDLCALL *SDL_GetNumTouchFingers_pfn)(SDL_TouchID touchID);

/** \brief Function pointer type of \c SDL_GetTouchFinger() */
typedef SDL_Finger* (SDLCALL *SDL_GetTouchFinger_pfn)(SDL_TouchID touchID,
                                                      int index);

/* SDL_version.h */

/** \brief Function pointer type of \c SDL_GetVersion() */
typedef void (SDLCALL *SDL_GetVersion_pfn)(SDL_version *ver);

/** \brief Function pointer type of \c SDL_GetRevision() */
typedef const char* (SDLCALL *SDL_GetRevision_pfn)(void);

/** \brief Function pointer type of \c SDL_GetRevisionNumber() */
typedef int (SDLCALL *SDL_GetRevisionNumber_pfn)(void);

/* SDL_video.h */

/** \brief Function pointer type of \c SDL_GetNumVideoDrivers() */
typedef int (SDLCALL *SDL_GetNumVideoDrivers_pfn)(void);

/** \brief Function pointer type of \c SDL_GetVideoDriver() */
typedef const char* (SDLCALL *SDL_GetVideoDriver_pfn)(int index);

/** \brief Function pointer type of \c SDL_VideoInit() */
typedef int (SDLCALL *SDL_VideoInit_pfn)(const char *driver_name);

/** \brief Function pointer type of \c SDL_VideoQuit() */
typedef void (SDLCALL *SDL_VideoQuit_pfn)(void);

/** \brief Function pointer type of \c SDL_GetCurrentVideoDriver() */
typedef const char *(SDLCALL *SDL_GetCurrentVideoDriver_pfn)(void);

/** \brief Function pointer type of \c SDL_GetNumVideoDisplays() */
typedef int (SDLCALL *SDL_GetNumVideoDisplays_pfn)(void);

/** \brief Function pointer type of \c SDL_GetDisplayName() */
typedef const char *(SDLCALL *SDL_GetDisplayName_pfn)(int displayIndex);

/** \brief Function pointer type of \c SDL_GetDisplayBounds() */
typedef int (SDLCALL *SDL_GetDisplayBounds_pfn)(int displayIndex,
                                                SDL_Rect *rect);

/** \brief Function pointer type of \c SDL_GetNumDisplayModes() */
typedef int (SDLCALL *SDL_GetNumDisplayModes_pfn)(int displayIndex);

/** \brief Function pointer type of \c SDL_GetDisplayMode() */
typedef int (SDLCALL *SDL_GetDisplayMode_pfn)(int displayIndex, int modeIndex,
                                              SDL_DisplayMode *mode);

/** \brief Function pointer type of \c SDL_GetDesktopDisplayMode() */
typedef int (SDLCALL *SDL_GetDesktopDisplayMode_pfn)(int displayIndex,
                                                     SDL_DisplayMode *mode);

/** \brief Function pointer type of \c SDL_GetCurrentDisplayMode() */
typedef int (SDLCALL *SDL_GetCurrentDisplayMode_pfn)(int displayIndex,
                                                     SDL_DisplayMode *mode);

/** \brief Function pointer type of \c SDL_GetClosestDisplayMode() */
typedef SDL_DisplayMode *(SDLCALL *SDL_GetClosestDisplayMode_pfn)(
        int displayIndex, const SDL_DisplayMode *mode,
        SDL_DisplayMode *closest);

/** \brief Function pointer type of \c SDL_GetWindowDisplayIndex() */
typedef int (SDLCALL *SDL_GetWindowDisplayIndex_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowDisplayMode() */
typedef int (SDLCALL *SDL_SetWindowDisplayMode_pfn)(SDL_Window *window,
                                                    const SDL_DisplayMode *mode
                                                    );

/** \brief Function pointer type of \c SDL_GetWindowDisplayMode() */
typedef int (SDLCALL *SDL_GetWindowDisplayMode_pfn)(SDL_Window *window,
                                                    SDL_DisplayMode *mode);

/** \brief Function pointer type of \c SDL_GetWindowPixelFormat() */
typedef Uint32 (SDLCALL *SDL_GetWindowPixelFormat_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_CreateWindow() */
typedef SDL_Window *(SDLCALL *SDL_CreateWindow_pfn)(const char *title, int x,
                                                    int y, int w, int h,
                                                    Uint32 flags);

/** \brief Function pointer type of \c SDL_CreateWindowFrom() */
typedef SDL_Window *(SDLCALL *SDL_CreateWindowFrom_pfn)(const void *data);

/** \brief Function pointer type of \c SDL_GetWindowID() */
typedef Uint32 (SDLCALL *SDL_GetWindowID_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_GetWindowFromID() */
typedef SDL_Window *(SDLCALL *SDL_GetWindowFromID_pfn)(Uint32 id);

/** \brief Function pointer type of \c SDL_GetWindowFlags() */
typedef Uint32 (SDLCALL *SDL_GetWindowFlags_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowTitle() */
typedef void (SDLCALL *SDL_SetWindowTitle_pfn)(SDL_Window *window,
                                               const char *title);

/** \brief Function pointer type of \c SDL_GetWindowTitle() */
typedef const char *(SDLCALL *SDL_GetWindowTitle_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowIcon() */
typedef void (SDLCALL *SDL_SetWindowIcon_pfn)(SDL_Window *window,
                                              SDL_Surface *icon);

/** \brief Function pointer type of \c SDL_SetWindowData() */
typedef void *(SDLCALL *SDL_SetWindowData_pfn)(SDL_Window *window,
                                               const char *name,
                                               void *userdata);

/** \brief Function pointer type of \c SDL_GetWindowData() */
typedef void *(SDLCALL *SDL_GetWindowData_pfn)(SDL_Window *window,
                                               const char *name);

/** \brief Function pointer type of \c SDL_SetWindowPosition() */
typedef void (SDLCALL *SDL_SetWindowPosition_pfn)(SDL_Window *window, int x,
                                                  int y);

/** \brief Function pointer type of \c SDL_GetWindowPosition() */
typedef void (SDLCALL *SDL_GetWindowPosition_pfn)(SDL_Window *window, int *x,
                                                  int *y);

/** \brief Function pointer type of \c SDL_SetWindowSize() */
typedef void (SDLCALL *SDL_SetWindowSize_pfn)(SDL_Window *window, int w,
                                              int h);

/** \brief Function pointer type of \c SDL_GetWindowSize() */
typedef void (SDLCALL *SDL_GetWindowSize_pfn)(SDL_Window *window, int *w,
                                              int *h);

/** \brief Function pointer type of \c SDL_SetWindowMinimumSize() */
typedef void (SDLCALL *SDL_SetWindowMinimumSize_pfn)(SDL_Window *window,
                                                     int min_w, int min_h);

/** \brief Function pointer type of \c SDL_GetWindowMinimumSize() */
typedef void (SDLCALL *SDL_GetWindowMinimumSize_pfn)(SDL_Window *window,
                                                     int *w, int *h);

/** \brief Function pointer type of \c SDL_SetWindowMaximumSize() */
typedef void (SDLCALL *SDL_SetWindowMaximumSize_pfn)(SDL_Window *window,
                                                     int max_w, int max_h);

/** \brief Function pointer type of \c SDL_GetWindowMaximumSize() */
typedef void (SDLCALL *SDL_GetWindowMaximumSize_pfn)(SDL_Window *window,
                                                     int *w, int *h);

/** \brief Function pointer type of \c SDL_SetWindowBordered() */
typedef void (SDLCALL *SDL_SetWindowBordered_pfn)(SDL_Window *window,
                                                  SDL_bool bordered);

/** \brief Function pointer type of \c SDL_ShowWindow() */
typedef void (SDLCALL *SDL_ShowWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_HideWindow() */
typedef void (SDLCALL *SDL_HideWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_RaiseWindow() */
typedef void (SDLCALL *SDL_RaiseWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_MaximizeWindow() */
typedef void (SDLCALL *SDL_MaximizeWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_MinimizeWindow() */
typedef void (SDLCALL *SDL_MinimizeWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_RestoreWindow() */
typedef void (SDLCALL *SDL_RestoreWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowFullscreen() */
typedef int (SDLCALL *SDL_SetWindowFullscreen_pfn)(SDL_Window *window,
                                                   Uint32 flags);

/** \brief Function pointer type of \c SDL_GetWindowSurface() */
typedef SDL_Surface *(SDLCALL *SDL_GetWindowSurface_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_UpdateWindowSurface() */
typedef int (SDLCALL *SDL_UpdateWindowSurface_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_UpdateWindowSurfaceRects() */
typedef int (SDLCALL *SDL_UpdateWindowSurfaceRects_pfn)(SDL_Window *window,
                                                        const SDL_Rect *rects,
                                                        int numrects);

/** \brief Function pointer type of \c SDL_SetWindowGrab() */
typedef void (SDLCALL *SDL_SetWindowGrab_pfn)(SDL_Window *window,
                                              SDL_bool grabbed);

/** \brief Function pointer type of \c SDL_GetWindowGrab() */
typedef SDL_bool (SDLCALL *SDL_GetWindowGrab_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowBrightness() */
typedef int (SDLCALL *SDL_SetWindowBrightness_pfn)(SDL_Window *window,
                                                   float brightness);

/** \brief Function pointer type of \c SDL_GetWindowBrightness() */
typedef float (SDLCALL *SDL_GetWindowBrightness_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_SetWindowGammaRamp() */
typedef int (SDLCALL *SDL_SetWindowGammaRamp_pfn)(SDL_Window *window,
                                                  const Uint16 *red,
                                                  const Uint16 *green,
                                                  const Uint16 *blue);

/** \brief Function pointer type of \c SDL_GetWindowGammaRamp() */
typedef int (SDLCALL *SDL_GetWindowGammaRamp_pfn)(SDL_Window *window,
                                                  Uint16 *red, Uint16 *green,
                                                  Uint16 *blue);

/** \brief Function pointer type of \c SDL_DestroyWindow() */
typedef void (SDLCALL *SDL_DestroyWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_IsScreenSaverEnabled() */
typedef SDL_bool (SDLCALL *SDL_IsScreenSaverEnabled_pfn)(void);

/** \brief Function pointer type of \c SDL_EnableScreenSaver() */
typedef void (SDLCALL *SDL_EnableScreenSaver_pfn)(void);

/** \brief Function pointer type of \c SDL_DisableScreenSaver() */
typedef void (SDLCALL *SDL_DisableScreenSaver_pfn)(void);

/** \brief Function pointer type of \c SDL_GL_LoadLibrary() */
typedef int (SDLCALL *SDL_GL_LoadLibrary_pfn)(const char *path);

/** \brief Function pointer type of \c SDL_GL_GetProcAddress() */
typedef void *(SDLCALL *SDL_GL_GetProcAddress_pfn)(const char *proc);

/** \brief Function pointer type of \c SDL_GL_UnloadLibrary() */
typedef void (SDLCALL *SDL_GL_UnloadLibrary_pfn)(void);

/** \brief Function pointer type of \c SDL_GL_ExtensionSupported() */
typedef SDL_bool (SDLCALL *SDL_GL_ExtensionSupported_pfn)(
        const char *extension);

/** \brief Function pointer type of \c SDL_GL_SetAttribute() */
typedef int (SDLCALL *SDL_GL_SetAttribute_pfn)(SDL_GLattr attr, int value);

/** \brief Function pointer type of \c SDL_GL_GetAttribute() */
typedef int (SDLCALL *SDL_GL_GetAttribute_pfn)(SDL_GLattr attr, int *value);

/** \brief Function pointer type of \c SDL_GL_CreateContext() */
typedef SDL_GLContext (SDLCALL *SDL_GL_CreateContext_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_GL_MakeCurrent() */
typedef int (SDLCALL *SDL_GL_MakeCurrent_pfn)(SDL_Window *window,
                                              SDL_GLContext context);

/** \brief Function pointer type of \c SDL_GL_GetCurrentWindow() */
typedef SDL_Window *(SDLCALL *SDL_GL_GetCurrentWindow_pfn)(void);

/** \brief Function pointer type of \c SDL_GL_GetCurrentContext() */
typedef SDL_GLContext (SDLCALL *SDL_GL_GetCurrentContext_pfn)(void);

/** \brief Function pointer type of \c SDL_GL_SetSwapInterval() */
typedef int (SDLCALL *SDL_GL_SetSwapInterval_pfn)(int interval);

/** \brief Function pointer type of \c SDL_GL_GetSwapInterval() */
typedef int (SDLCALL *SDL_GL_GetSwapInterval_pfn)(void);

/** \brief Function pointer type of \c SDL_GL_SwapWindow() */
typedef void (SDLCALL *SDL_GL_SwapWindow_pfn)(SDL_Window *window);

/** \brief Function pointer type of \c SDL_GL_DeleteContext() */
typedef void (SDLCALL *SDL_GL_DeleteContext_pfn)(SDL_GLContext context);

/**
 * \brief pycsdl2's C API
 *
 * This struct is used to hold pointers to functions and data that csdl2
 * exposes to other extensions. csdl2 exposes this struct through
 * PyCSDL2_Import().
 *
 * Currently, function pointers to SDL functions are exposed in this struct.
 * For example, to call \c SDL_Log() :
 * \code
 * PyCSDL2_Import()->_SDL_Log("Hello World!");
 * \endcode
 */
typedef struct PyCSDL2_CAPI {
/* SDL_assert.h */
    /** \brief Pointer to \c SDL_ReportAssertion() */
    SDL_ReportAssertion_pfn _SDL_ReportAssertion;
    /** \brief Pointer to \c SDL_SetAssertionHandler() */
    SDL_SetAssertionHandler_pfn _SDL_SetAssertionHandler;
    /** \brief Pointer to \c SDL_GetAssertionReport() */
    SDL_GetAssertionReport_pfn _SDL_GetAssertionReport;
    /** \brief Pointer to \c SDL_ResetAssertionReport() */
    SDL_ResetAssertionReport_pfn _SDL_ResetAssertionReport;
/* SDL_atomic.h */
    /** \brief Pointer to \c SDL_AtomicTryLock() */
    SDL_AtomicTryLock_pfn _SDL_AtomicTryLock;
    /** \brief Pointer to \c SDL_AtomicLock() */
    SDL_AtomicLock_pfn _SDL_AtomicLock;
    /** \brief Pointer to \c SDL_AtomicUnlock() */
    SDL_AtomicUnlock_pfn _SDL_AtomicUnlock;
#if !defined(SDL_MemoryBarrierRelease) || DOXYGEN
    /** \brief Pointer to \c SDL_MemoryBarrierRelease() */
    SDL_MemoryBarrierRelease_pfn _SDL_MemoryBarrierRelease;
#else
    void *__pad1;
#endif
#if !defined(SDL_MemoryBarrierAcquire) || DOXYGEN
    /** \brief Pointer to \c SDL_MemoryBarrierAcquire() */
    SDL_MemoryBarrierAcquire_pfn _SDL_MemoryBarrierAcquire;
#else
    void *__pad2;
#endif
#if !defined(SDL_AtomicCAS) || DOXYGEN
    /** \brief Pointer to \c SDL_AtomicCAS() */
    SDL_AtomicCAS_pfn _SDL_AtomicCAS;
#else
    void *__pad3;
#endif
#if !defined(SDL_AtomicCASPtr) || DOXYGEN
    /** \brief Pointer to \c SDL_AtomicCASPtr() */
    SDL_AtomicCASPtr_pfn _SDL_AtomicCASPtr;
#else
    void *__pad4;
#endif
/* SDL_audio.h */
    /** \brief Pointer to \c SDL_GetNumAudioDrivers() */
    SDL_GetNumAudioDrivers_pfn _SDL_GetNumAudioDrivers;
    /** \brief Pointer to \c SDL_GetAudioDriver() */
    SDL_GetAudioDriver_pfn _SDL_GetAudioDriver;
    /** \brief Pointer to \c SDL_AudioInit() */
    SDL_AudioInit_pfn _SDL_AudioInit;
    /** \brief Pointer to \c SDL_AudioQuit() */
    SDL_AudioQuit_pfn _SDL_AudioQuit;
    /** \brief Pointer to \c SDL_GetCurrentAudioDriver() */
    SDL_GetCurrentAudioDriver_pfn _SDL_GetCurrentAudioDriver;
    /** \brief Pointer to \c SDL_OpenAudio() */
    SDL_OpenAudio_pfn _SDL_OpenAudio;
    /** \brief Pointer to \c SDL_GetNumAudioDevices() */
    SDL_GetNumAudioDevices_pfn _SDL_GetNumAudioDevices;
    /** \brief Pointer to \c SDL_GetAudioDeviceName() */
    SDL_GetAudioDeviceName_pfn _SDL_GetAudioDeviceName;
    /** \brief Pointer to \c SDL_OpenAudioDevice() */
    SDL_OpenAudioDevice_pfn _SDL_OpenAudioDevice;
    /** \brief Pointer to \c SDL_GetAudioStatus() */
    SDL_GetAudioStatus_pfn _SDL_GetAudioStatus;
    /** \brief Pointer to \c SDL_GetAudioDeviceStatus() */
    SDL_GetAudioDeviceStatus_pfn _SDL_GetAudioDeviceStatus;
    /** \brief Pointer to \c SDL_PauseAudio() */
    SDL_PauseAudio_pfn _SDL_PauseAudio;
    /** \brief Pointer to \c SDL_PauseAudioDevice() */
    SDL_PauseAudioDevice_pfn _SDL_PauseAudioDevice;
    /** \brief Pointer to \c SDL_LoadWAV_RW() */
    SDL_LoadWAV_RW_pfn _SDL_LoadWAV_RW;
    /** \brief Pointer to \c SDL_FreeWAV() */
    SDL_FreeWAV_pfn _SDL_FreeWAV;
    /** \brief Pointer to \c SDL_BuildAudioCVT() */
    SDL_BuildAudioCVT_pfn _SDL_BuildAudioCVT;
    /** \brief Pointer to \c SDL_ConvertAudio() */
    SDL_ConvertAudio_pfn _SDL_ConvertAudio;
    /** \brief Pointer to \c SDL_MixAudio() */
    SDL_MixAudio_pfn _SDL_MixAudio;
    /** \brief Pointer to \c SDL_MixAudioFormat() */
    SDL_MixAudioFormat_pfn _SDL_MixAudioFormat;
    /** \brief Pointer to \c SDL_LockAudio() */
    SDL_LockAudio_pfn _SDL_LockAudio;
    /** \brief Pointer to \c SDL_LockAudioDevice() */
    SDL_LockAudioDevice_pfn _SDL_LockAudioDevice;
    /** \brief Pointer to \c SDL_UnlockAudio() */
    SDL_UnlockAudio_pfn _SDL_UnlockAudio;
    /** \brief Pointer to \c SDL_UnlockAudioDevice() */
    SDL_UnlockAudioDevice_pfn _SDL_UnlockAudioDevice;
    /** \brief Pointer to \c SDL_CloseAudio() */
    SDL_CloseAudio_pfn _SDL_CloseAudio;
    /** \brief Pointer to \c SDL_CloseAudioDevice() */
    SDL_CloseAudioDevice_pfn _SDL_CloseAudioDevice;
/* SDL_clipboard.h */
    /** \brief Pointer to \c SDL_SetClipboardText() */
    SDL_SetClipboardText_pfn _SDL_SetClipboardText;
    /** \brief Pointer to \c SDL_GetClipboardText() */
    SDL_GetClipboardText_pfn _SDL_GetClipboardText;
    /** \brief Pointer to \c SDL_HasClipboardText() */
    SDL_HasClipboardText_pfn _SDL_HasClipboardText;
/* SDL_cpuinfo.h */
    /** \brief Pointer to \c SDL_GetCPUCount() */
    SDL_GetCPUCount_pfn _SDL_GetCPUCount;
    /** \brief Pointer to \c SDL_GetCPUCacheLineSize() */
    SDL_GetCPUCacheLineSize_pfn _SDL_GetCPUCacheLineSize;
    /** \brief Pointer to \c SDL_HasRDTSC() */
    SDL_HasRDTSC_pfn _SDL_HasRDTSC;
    /** \brief Pointer to \c SDL_HasAltiVec() */
    SDL_HasAltiVec_pfn _SDL_HasAltiVec;
    /** \brief Pointer to \c SDL_HasMMX() */
    SDL_HasMMX_pfn _SDL_HasMMX;
    /** \brief Pointer to \c SDL_Has3DNow() */
    SDL_Has3DNow_pfn _SDL_Has3DNow;
    /** \brief Pointer to \c SDL_HasSSE() */
    SDL_HasSSE_pfn _SDL_HasSSE;
    /** \brief Pointer to \c SDL_HasSSE2() */
    SDL_HasSSE2_pfn _SDL_HasSSE2;
    /** \brief Pointer to \c SDL_HasSSE3() */
    SDL_HasSSE3_pfn _SDL_HasSSE3;
    /** \brief Pointer to \c SDL_HasSSE41() */
    SDL_HasSSE41_pfn _SDL_HasSSE41;
    /** \brief Pointer to \c SDL_HasSSE42() */
    SDL_HasSSE42_pfn _SDL_HasSSE42;
/* SDL_error.h */
    /** \brief Pointer to \c SDL_SetError() */
    SDL_SetError_pfn _SDL_SetError;
    /** \brief Pointer to \c SDL_GetError() */
    SDL_GetError_pfn _SDL_GetError;
    /** \brief Pointer to \c SDL_ClearError() */
    SDL_ClearError_pfn _SDL_ClearError;
    /** \brief Pointer to \c SDL_Error() */
    SDL_Error_pfn _SDL_Error;
/* SDL_events.h */
    /** \brief Pointer to \c SDL_PumpEvents() */
    SDL_PumpEvents_pfn _SDL_PumpEvents;
    /** \brief Pointer to \c SDL_PeepEvents() */
    SDL_PeepEvents_pfn _SDL_PeepEvents;
    /** \brief Pointer to \c SDL_HasEvent() */
    SDL_HasEvent_pfn _SDL_HasEvent;
    /** \brief Pointer to \c SDL_HasEvents() */
    SDL_HasEvents_pfn _SDL_HasEvents;
    /** \brief Pointer to \c SDL_FlushEvent() */
    SDL_FlushEvent_pfn _SDL_FlushEvent;
    /** \brief Pointer to \c SDL_FlushEvents() */
    SDL_FlushEvents_pfn _SDL_FlushEvents;
    /** \brief Pointer to \c SDL_PollEvent() */
    SDL_PollEvent_pfn _SDL_PollEvent;
    /** \brief Pointer to \c SDL_WaitEvent() */
    SDL_WaitEvent_pfn _SDL_WaitEvent;
    /** \brief Pointer to \c SDL_WaitEventTimeout() */
    SDL_WaitEventTimeout_pfn _SDL_WaitEventTimeout;
    /** \brief Pointer to \c SDL_PushEvent() */
    SDL_PushEvent_pfn _SDL_PushEvent;
    /** \brief Pointer to \c SDL_SetEventFilter() */
    SDL_SetEventFilter_pfn _SDL_SetEventFilter;
    /** \brief Pointer to \c SDL_GetEventFilter() */
    SDL_GetEventFilter_pfn _SDL_GetEventFilter;
    /** \brief Pointer to \c SDL_AddEventWatch() */
    SDL_AddEventWatch_pfn _SDL_AddEventWatch;
    /** \brief Pointer to \c SDL_DelEventWatch() */
    SDL_DelEventWatch_pfn _SDL_DelEventWatch;
    /** \brief Pointer to \c SDL_FilterEvents() */
    SDL_FilterEvents_pfn _SDL_FilterEvents;
    /** \brief Pointer to \c SDL_EventState() */
    SDL_EventState_pfn _SDL_EventState;
    /** \brief Pointer to \c SDL_RegisterEvents() */
    SDL_RegisterEvents_pfn _SDL_RegisterEvents;
/* SDL_gamecontroller.h */
    /** \brief Pointer to \c SDL_GameControllerAddMapping() */
    SDL_GameControllerAddMapping_pfn _SDL_GameControllerAddMapping;
    /** \brief Pointer to \c SDL_GameControllerMappingForGUID() */
    SDL_GameControllerMappingForGUID_pfn _SDL_GameControllerMappingForGUID;
    /** \brief Pointer to \c SDL_GameControllerMapping() */
    SDL_GameControllerMapping_pfn _SDL_GameControllerMapping;
    /** \brief Pointer to \c SDL_IsGameController() */
    SDL_IsGameController_pfn _SDL_IsGameController;
    /** \brief Pointer to \c SDL_GameControllerNameForIndex() */
    SDL_GameControllerNameForIndex_pfn _SDL_GameControllerNameForIndex;
    /** \brief Pointer to \c SDL_GameControllerOpen() */
    SDL_GameControllerOpen_pfn _SDL_GameControllerOpen;
    /** \brief Pointer to \c SDL_GameControllerName() */
    SDL_GameControllerName_pfn _SDL_GameControllerName;
    /** \brief Pointer to \c SDL_GameControllerGetAttached() */
    SDL_GameControllerGetAttached_pfn _SDL_GameControllerGetAttached;
    /** \brief Pointer to \c SDL_GameControllerGetJoystick() */
    SDL_GameControllerGetJoystick_pfn _SDL_GameControllerGetJoystick;
    /** \brief Pointer to \c SDL_GameControllerEventState() */
    SDL_GameControllerEventState_pfn _SDL_GameControllerEventState;
    /** \brief Pointer to \c SDL_GameControllerUpdate() */
    SDL_GameControllerUpdate_pfn _SDL_GameControllerUpdate;
    /** \brief Pointer to \c SDL_GameControllerGetAxisFromString() */
    SDL_GameControllerGetAxisFromString_pfn _SDL_GameControllerGetAxisFromString;
    /** \brief Pointer to \c SDL_GameControllerGetStringForAxis() */
    SDL_GameControllerGetStringForAxis_pfn _SDL_GameControllerGetStringForAxis;
    /** \brief Pointer to \c SDL_GameControllerGetBindForAxis() */
    SDL_GameControllerGetBindForAxis_pfn _SDL_GameControllerGetBindForAxis;
    /** \brief Pointer to \c SDL_GameControllerGetAxis() */
    SDL_GameControllerGetAxis_pfn _SDL_GameControllerGetAxis;
    /** \brief Pointer to \c SDL_GameControllerGetButtonFromString() */
    SDL_GameControllerGetButtonFromString_pfn _SDL_GameControllerGetButtonFromString;
    /** \brief Pointer to \c SDL_GameControllerGetStringForButton() */
    SDL_GameControllerGetStringForButton_pfn _SDL_GameControllerGetStringForButton;
    /** \brief Pointer to \c SDL_GameControllerGetBindForButton() */
    SDL_GameControllerGetBindForButton_pfn _SDL_GameControllerGetBindForButton;
    /** \brief Pointer to \c SDL_GameControllerGetButton() */
    SDL_GameControllerGetButton_pfn _SDL_GameControllerGetButton;
    /** \brief Pointer to \c SDL_GameControllerClose() */
    SDL_GameControllerClose_pfn _SDL_GameControllerClose;
/* SDL_gesture.h */
    /** \brief Pointer to \c SDL_RecordGesture() */
    SDL_RecordGesture_pfn _SDL_RecordGesture;
    /** \brief Pointer to \c SDL_SaveAllDollarTemplates() */
    SDL_SaveAllDollarTemplates_pfn _SDL_SaveAllDollarTemplates;
    /** \brief Pointer to \c SDL_SaveDollarTemplate() */
    SDL_SaveDollarTemplate_pfn _SDL_SaveDollarTemplate;
    /** \brief Pointer to \c SDL_LoadDollarTemplates() */
    SDL_LoadDollarTemplates_pfn _SDL_LoadDollarTemplates;
/* SDL.h */
    /** \brief Pointer to \c SDL_Init() */
    SDL_Init_pfn _SDL_Init;
    /** \brief Pointer to \c SDL_InitSubSystem() */
    SDL_InitSubSystem_pfn _SDL_InitSubSystem;
    /** \brief Pointer to \c SDL_QuitSubSystem() */
    SDL_QuitSubSystem_pfn _SDL_QuitSubSystem;
    /** \brief Pointer to \c SDL_WasInit() */
    SDL_WasInit_pfn _SDL_WasInit;
    /** \brief Pointer to \c SDL_Quit() */
    SDL_Quit_pfn _SDL_Quit;
/* SDL_haptic.h */
    /** \brief Pointer to \c SDL_NumHaptics() */
    SDL_NumHaptics_pfn _SDL_NumHaptics;
    /** \brief Pointer to \c SDL_HapticName() */
    SDL_HapticName_pfn _SDL_HapticName;
    /** \brief Pointer to \c SDL_HapticOpen() */
    SDL_HapticOpen_pfn _SDL_HapticOpen;
    /** \brief Pointer to \c SDL_HapticOpened() */
    SDL_HapticOpened_pfn _SDL_HapticOpened;
    /** \brief Pointer to \c SDL_HapticIndex() */
    SDL_HapticIndex_pfn _SDL_HapticIndex;
    /** \brief Pointer to \c SDL_MouseIsHaptic() */
    SDL_MouseIsHaptic_pfn _SDL_MouseIsHaptic;
    /** \brief Pointer to \c SDL_HapticOpenFromMouse() */
    SDL_HapticOpenFromMouse_pfn _SDL_HapticOpenFromMouse;
    /** \brief Pointer to \c SDL_JoystickIsHaptic() */
    SDL_JoystickIsHaptic_pfn _SDL_JoystickIsHaptic;
    /** \brief Pointer to \c SDL_HapticOpenFromJoystick() */
    SDL_HapticOpenFromJoystick_pfn _SDL_HapticOpenFromJoystick;
    /** \brief Pointer to \c SDL_HapticClose() */
    SDL_HapticClose_pfn _SDL_HapticClose;
    /** \brief Pointer to \c SDL_HapticNumEffects() */
    SDL_HapticNumEffects_pfn _SDL_HapticNumEffects;
    /** \brief Pointer to \c SDL_HapticNumEffectsPlaying() */
    SDL_HapticNumEffectsPlaying_pfn _SDL_HapticNumEffectsPlaying;
    /** \brief Pointer to \c SDL_HapticQuery() */
    SDL_HapticQuery_pfn _SDL_HapticQuery;
    /** \brief Pointer to \c SDL_HapticNumAxes() */
    SDL_HapticNumAxes_pfn _SDL_HapticNumAxes;
    /** \brief Pointer to \c SDL_HapticEffectSupported() */
    SDL_HapticEffectSupported_pfn _SDL_HapticEffectSupported;
    /** \brief Pointer to \c SDL_HapticNewEffect() */
    SDL_HapticNewEffect_pfn _SDL_HapticNewEffect;
    /** \brief Pointer to \c SDL_HapticUpdateEffect() */
    SDL_HapticUpdateEffect_pfn _SDL_HapticUpdateEffect;
    /** \brief Pointer to \c SDL_HapticRunEffect() */
    SDL_HapticRunEffect_pfn _SDL_HapticRunEffect;
    /** \brief Pointer to \c SDL_HapticStopEffect() */
    SDL_HapticStopEffect_pfn _SDL_HapticStopEffect;
    /** \brief Pointer to \c SDL_HapticDestroyEffect() */
    SDL_HapticDestroyEffect_pfn _SDL_HapticDestroyEffect;
    /** \brief Pointer to \c SDL_HapticGetEffectStatus() */
    SDL_HapticGetEffectStatus_pfn _SDL_HapticGetEffectStatus;
    /** \brief Pointer to \c SDL_HapticSetGain() */
    SDL_HapticSetGain_pfn _SDL_HapticSetGain;
    /** \brief Pointer to \c SDL_HapticSetAutocenter() */
    SDL_HapticSetAutocenter_pfn _SDL_HapticSetAutocenter;
    /** \brief Pointer to \c SDL_HapticPause() */
    SDL_HapticPause_pfn _SDL_HapticPause;
    /** \brief Pointer to \c SDL_HapticUnpause() */
    SDL_HapticUnpause_pfn _SDL_HapticUnpause;
    /** \brief Pointer to \c SDL_HapticStopAll() */
    SDL_HapticStopAll_pfn _SDL_HapticStopAll;
    /** \brief Pointer to \c SDL_HapticRumbleSupported() */
    SDL_HapticRumbleSupported_pfn _SDL_HapticRumbleSupported;
    /** \brief Pointer to \c SDL_HapticRumbleInit() */
    SDL_HapticRumbleInit_pfn _SDL_HapticRumbleInit;
    /** \brief Pointer to \c SDL_HapticRumblePlay() */
    SDL_HapticRumblePlay_pfn _SDL_HapticRumblePlay;
    /** \brief Pointer to \c SDL_HapticRumbleStop() */
    SDL_HapticRumbleStop_pfn _SDL_HapticRumbleStop;
/* SDL_hints.h */
    /** \brief Pointer to \c SDL_SetHintWithPriority() */
    SDL_SetHintWithPriority_pfn _SDL_SetHintWithPriority;
    /** \brief Pointer to \c SDL_SetHint() */
    SDL_SetHint_pfn _SDL_SetHint;
    /** \brief Pointer to \c SDL_GetHint() */
    SDL_GetHint_pfn _SDL_GetHint;
    /** \brief Pointer to \c SDL_AddHintCallback() */
    SDL_AddHintCallback_pfn _SDL_AddHintCallback;
    /** \brief Pointer to \c SDL_DelHintCallback() */
    SDL_DelHintCallback_pfn _SDL_DelHintCallback;
    /** \brief Pointer to \c SDL_ClearHints() */
    SDL_ClearHints_pfn _SDL_ClearHints;
/* SDL_joystick.h */
    /** \brief Pointer to \c SDL_NumJoysticks() */
    SDL_NumJoysticks_pfn _SDL_NumJoysticks;
    /** \brief Pointer to \c SDL_JoystickNameForIndex() */
    SDL_JoystickNameForIndex_pfn _SDL_JoystickNameForIndex;
    /** \brief Pointer to \c SDL_JoystickOpen() */
    SDL_JoystickOpen_pfn _SDL_JoystickOpen;
    /** \brief Pointer to \c SDL_JoystickName() */
    SDL_JoystickName_pfn _SDL_JoystickName;
    /** \brief Pointer to \c SDL_JoystickGetDeviceGUID() */
    SDL_JoystickGetDeviceGUID_pfn _SDL_JoystickGetDeviceGUID;
    /** \brief Pointer to \c SDL_JoystickGetGUID() */
    SDL_JoystickGetGUID_pfn _SDL_JoystickGetGUID;
    /** \brief Pointer to \c SDL_JoystickGetGUIDString() */
    SDL_JoystickGetGUIDString_pfn _SDL_JoystickGetGUIDString;
    /** \brief Pointer to \c SDL_JoystickGetGUIDFromString() */
    SDL_JoystickGetGUIDFromString_pfn _SDL_JoystickGetGUIDFromString;
    /** \brief Pointer to \c SDL_JoystickGetAttached() */
    SDL_JoystickGetAttached_pfn _SDL_JoystickGetAttached;
    /** \brief Pointer to \c SDL_JoystickInstanceID() */
    SDL_JoystickInstanceID_pfn _SDL_JoystickInstanceID;
    /** \brief Pointer to \c SDL_JoystickNumAxes() */
    SDL_JoystickNumAxes_pfn _SDL_JoystickNumAxes;
    /** \brief Pointer to \c SDL_JoystickNumBalls() */
    SDL_JoystickNumBalls_pfn _SDL_JoystickNumBalls;
    /** \brief Pointer to \c SDL_JoystickNumHats() */
    SDL_JoystickNumHats_pfn _SDL_JoystickNumHats;
    /** \brief Pointer to \c SDL_JoystickNumButtons() */
    SDL_JoystickNumButtons_pfn _SDL_JoystickNumButtons;
    /** \brief Pointer to \c SDL_JoystickUpdate() */
    SDL_JoystickUpdate_pfn _SDL_JoystickUpdate;
    /** \brief Pointer to \c SDL_JoystickEventState() */
    SDL_JoystickEventState_pfn _SDL_JoystickEventState;
    /** \brief Pointer to \c SDL_JoystickGetAxis() */
    SDL_JoystickGetAxis_pfn _SDL_JoystickGetAxis;
    /** \brief Pointer to \c SDL_JoystickGetHat() */
    SDL_JoystickGetHat_pfn _SDL_JoystickGetHat;
    /** \brief Pointer to \c SDL_JoystickGetBall() */
    SDL_JoystickGetBall_pfn _SDL_JoystickGetBall;
    /** \brief Pointer to \c SDL_JoystickGetButton() */
    SDL_JoystickGetButton_pfn _SDL_JoystickGetButton;
    /** \brief Pointer to \c SDL_JoystickClose() */
    SDL_JoystickClose_pfn _SDL_JoystickClose;
/* SDL_keyboard.h */
    /** \brief Pointer to \c SDL_GetKeyboardFocus() */
    SDL_GetKeyboardFocus_pfn _SDL_GetKeyboardFocus;
    /** \brief Pointer to \c SDL_GetKeyboardState() */
    SDL_GetKeyboardState_pfn _SDL_GetKeyboardState;
    /** \brief Pointer to \c SDL_GetModState() */
    SDL_GetModState_pfn _SDL_GetModState;
    /** \brief Pointer to \c SDL_SetModState() */
    SDL_SetModState_pfn _SDL_SetModState;
    /** \brief Pointer to \c SDL_GetKeyFromScancode() */
    SDL_GetKeyFromScancode_pfn _SDL_GetKeyFromScancode;
    /** \brief Pointer to \c SDL_GetScancodeFromKey() */
    SDL_GetScancodeFromKey_pfn _SDL_GetScancodeFromKey;
    /** \brief Pointer to \c SDL_GetScancodeName() */
    SDL_GetScancodeName_pfn _SDL_GetScancodeName;
    /** \brief Pointer to \c SDL_GetScancodeFromName() */
    SDL_GetScancodeFromName_pfn _SDL_GetScancodeFromName;
    /** \brief Pointer to \c SDL_GetKeyName() */
    SDL_GetKeyName_pfn _SDL_GetKeyName;
    /** \brief Pointer to \c SDL_GetKeyFromName() */
    SDL_GetKeyFromName_pfn _SDL_GetKeyFromName;
    /** \brief Pointer to \c SDL_StartTextInput() */
    SDL_StartTextInput_pfn _SDL_StartTextInput;
    /** \brief Pointer to \c SDL_IsTextInputActive() */
    SDL_IsTextInputActive_pfn _SDL_IsTextInputActive;
    /** \brief Pointer to \c SDL_StopTextInput() */
    SDL_StopTextInput_pfn _SDL_StopTextInput;
    /** \brief Pointer to \c SDL_SetTextInputRect() */
    SDL_SetTextInputRect_pfn _SDL_SetTextInputRect;
    /** \brief Pointer to \c SDL_HasScreenKeyboardSupport() */
    SDL_HasScreenKeyboardSupport_pfn _SDL_HasScreenKeyboardSupport;
    /** \brief Pointer to \c SDL_IsScreenKeyboardShown() */
    SDL_IsScreenKeyboardShown_pfn _SDL_IsScreenKeyboardShown;
/* SDL_loadso.h */
    /** \brief Pointer to \c SDL_LoadObject() */
    SDL_LoadObject_pfn _SDL_LoadObject;
    /** \brief Pointer to \c SDL_LoadFunction() */
    SDL_LoadFunction_pfn _SDL_LoadFunction;
    /** \brief Pointer to \c SDL_UnloadObject() */
    SDL_UnloadObject_pfn _SDL_UnloadObject;
/* SDL_log.h */
    /** \brief Pointer to \c SDL_LogSetAllPriority() */
    SDL_LogSetAllPriority_pfn _SDL_LogSetAllPriority;
    /** \brief Pointer to \c SDL_LogSetPriority() */
    SDL_LogSetPriority_pfn _SDL_LogSetPriority;
    /** \brief Pointer to \c SDL_LogGetPriority() */
    SDL_LogGetPriority_pfn _SDL_LogGetPriority;
    /** \brief Pointer to \c SDL_LogResetPriorities() */
    SDL_LogResetPriorities_pfn _SDL_LogResetPriorities;
    /** \brief Pointer to \c SDL_Log() */
    SDL_Log_pfn _SDL_Log;
    /** \brief Pointer to \c SDL_LogVerbose() */
    SDL_LogVerbose_pfn _SDL_LogVerbose;
    /** \brief Pointer to \c SDL_LogDebug() */
    SDL_LogDebug_pfn _SDL_LogDebug;
    /** \brief Pointer to \c SDL_LogInfo() */
    SDL_LogInfo_pfn _SDL_LogInfo;
    /** \brief Pointer to \c SDL_LogWarn() */
    SDL_LogWarn_pfn _SDL_LogWarn;
    /** \brief Pointer to \c SDL_LogError() */
    SDL_LogError_pfn _SDL_LogError;
    /** \brief Pointer to \c SDL_LogCritical() */
    SDL_LogCritical_pfn _SDL_LogCritical;
    /** \brief Pointer to \c SDL_LogMessage() */
    SDL_LogMessage_pfn _SDL_LogMessage;
    /** \brief Pointer to \c SDL_LogMessageV() */
    SDL_LogMessageV_pfn _SDL_LogMessageV;
    /** \brief Pointer to \c SDL_LogGetOutputFunction() */
    SDL_LogGetOutputFunction_pfn _SDL_LogGetOutputFunction;
    /** \brief Pointer to \c SDL_LogSetOutputFunction() */
    SDL_LogSetOutputFunction_pfn _SDL_LogSetOutputFunction;
/* SDL_main.h */
    /** \brief Pointer to \c SDL_SetMainReady() */
    SDL_SetMainReady_pfn _SDL_SetMainReady;
#if defined(__WIN32__) || DOXYGEN
    /** \brief Pointer to \c SDL_RegisterApp() */
    SDL_RegisterApp_pfn _SDL_RegisterApp;
    /** \brief Pointer to \c SDL_UnregisterApp() */
    SDL_UnregisterApp_pfn _SDL_UnregisterApp;
#else
    void *__pad5;
    void *__pad6;
#endif /* __WIN32__ */
/* SDL_messagebox.h */
    /** \brief Pointer to \c SDL_ShowMessageBox() */
    SDL_ShowMessageBox_pfn _SDL_ShowMessageBox;
    /** \brief Pointer to \c SDL_ShowSimpleMessageBox() */
    SDL_ShowSimpleMessageBox_pfn _SDL_ShowSimpleMessageBox;
/* SDL_mouse.h */
    /** \brief Pointer to \c SDL_GetMouseFocus() */
    SDL_GetMouseFocus_pfn _SDL_GetMouseFocus;
    /** \brief Pointer to \c SDL_GetMouseState() */
    SDL_GetMouseState_pfn _SDL_GetMouseState;
    /** \brief Pointer to \c SDL_GetRelativeMouseState() */
    SDL_GetRelativeMouseState_pfn _SDL_GetRelativeMouseState;
    /** \brief Pointer to \c SDL_WarpMouseInWindow() */
    SDL_WarpMouseInWindow_pfn _SDL_WarpMouseInWindow;
    /** \brief Pointer to \c SDL_SetRelativeMouseMode() */
    SDL_SetRelativeMouseMode_pfn _SDL_SetRelativeMouseMode;
    /** \brief Pointer to \c SDL_GetRelativeMouseMode() */
    SDL_GetRelativeMouseMode_pfn _SDL_GetRelativeMouseMode;
    /** \brief Pointer to \c SDL_CreateCursor() */
    SDL_CreateCursor_pfn _SDL_CreateCursor;
    /** \brief Pointer to \c SDL_CreateColorCursor() */
    SDL_CreateColorCursor_pfn _SDL_CreateColorCursor;
    /** \brief Pointer to \c SDL_CreateSystemCursor() */
    SDL_CreateSystemCursor_pfn _SDL_CreateSystemCursor;
    /** \brief Pointer to \c SDL_SetCursor() */
    SDL_SetCursor_pfn _SDL_SetCursor;
    /** \brief Pointer to \c SDL_GetCursor() */
    SDL_GetCursor_pfn _SDL_GetCursor;
    /** \brief Pointer to \c SDL_GetDefaultCursor() */
    SDL_GetDefaultCursor_pfn _SDL_GetDefaultCursor;
    /** \brief Pointer to \c SDL_FreeCursor() */
    SDL_FreeCursor_pfn _SDL_FreeCursor;
    /** \brief Pointer to \c SDL_ShowCursor() */
    SDL_ShowCursor_pfn _SDL_ShowCursor;
/* SDL_mutex.h */
    /** \brief Pointer to \c SDL_CreateMutex() */
    SDL_CreateMutex_pfn _SDL_CreateMutex;
    /** \brief Pointer to \c SDL_LockMutex() */
    SDL_LockMutex_pfn _SDL_LockMutex;
    /** \brief Pointer to \c SDL_TryLockMutex() */
    SDL_TryLockMutex_pfn _SDL_TryLockMutex;
    /** \brief Pointer to \c SDL_UnlockMutex() */
    SDL_UnlockMutex_pfn _SDL_UnlockMutex;
    /** \brief Pointer to \c SDL_DestroyMutex() */
    SDL_DestroyMutex_pfn _SDL_DestroyMutex;
    /** \brief Pointer to \c SDL_CreateSemaphore() */
    SDL_CreateSemaphore_pfn _SDL_CreateSemaphore;
    /** \brief Pointer to \c SDL_DestroySemaphore() */
    SDL_DestroySemaphore_pfn _SDL_DestroySemaphore;
    /** \brief Pointer to \c SDL_SemWait() */
    SDL_SemWait_pfn _SDL_SemWait;
    /** \brief Pointer to \c SDL_SemTryWait() */
    SDL_SemTryWait_pfn _SDL_SemTryWait;
    /** \brief Pointer to \c SDL_SemWaitTimeout() */
    SDL_SemWaitTimeout_pfn _SDL_SemWaitTimeout;
    /** \brief Pointer to \c SDL_SemPost() */
    SDL_SemPost_pfn _SDL_SemPost;
    /** \brief Pointer to \c SDL_SemValue() */
    SDL_SemValue_pfn _SDL_SemValue;
    /** \brief Pointer to \c SDL_CreateCond() */
    SDL_CreateCond_pfn _SDL_CreateCond;
    /** \brief Pointer to \c SDL_DestroyCond() */
    SDL_DestroyCond_pfn _SDL_DestroyCond;
    /** \brief Pointer to \c SDL_CondSignal() */
    SDL_CondSignal_pfn _SDL_CondSignal;
    /** \brief Pointer to \c SDL_CondBroadcast() */
    SDL_CondBroadcast_pfn _SDL_CondBroadcast;
    /** \brief Pointer to \c SDL_CondWait() */
    SDL_CondWait_pfn _SDL_CondWait;
    /** \brief Pointer to \c SDL_CondWaitTimeout() */
    SDL_CondWaitTimeout_pfn _SDL_CondWaitTimeout;
/* SDL_pixels.h */
    /** \brief Pointer to \c SDL_GetPixelFormatName() */
    SDL_GetPixelFormatName_pfn _SDL_GetPixelFormatName;
    /** \brief Pointer to \c SDL_PixelFormatEnumToMasks() */
    SDL_PixelFormatEnumToMasks_pfn _SDL_PixelFormatEnumToMasks;
    /** \brief Pointer to \c SDL_MasksToPixelFormatEnum() */
    SDL_MasksToPixelFormatEnum_pfn _SDL_MasksToPixelFormatEnum;
    /** \brief Pointer to \c SDL_AllocFormat() */
    SDL_AllocFormat_pfn _SDL_AllocFormat;
    /** \brief Pointer to \c SDL_FreeFormat() */
    SDL_FreeFormat_pfn _SDL_FreeFormat;
    /** \brief Pointer to \c SDL_AllocPalette() */
    SDL_AllocPalette_pfn _SDL_AllocPalette;
    /** \brief Pointer to \c SDL_SetPixelFormatPalette() */
    SDL_SetPixelFormatPalette_pfn _SDL_SetPixelFormatPalette;
    /** \brief Pointer to \c SDL_SetPaletteColors() */
    SDL_SetPaletteColors_pfn _SDL_SetPaletteColors;
    /** \brief Pointer to \c SDL_FreePalette() */
    SDL_FreePalette_pfn _SDL_FreePalette;
    /** \brief Pointer to \c SDL_MapRGB() */
    SDL_MapRGB_pfn _SDL_MapRGB;
    /** \brief Pointer to \c SDL_MapRGBA() */
    SDL_MapRGBA_pfn _SDL_MapRGBA;
    /** \brief Pointer to \c SDL_GetRGB() */
    SDL_GetRGB_pfn _SDL_GetRGB;
    /** \brief Pointer to \c SDL_GetRGBA() */
    SDL_GetRGBA_pfn _SDL_GetRGBA;
    /** \brief Pointer to \c SDL_CalculateGammaRamp() */
    SDL_CalculateGammaRamp_pfn _SDL_CalculateGammaRamp;
/* SDL_platform.h */
    /** \brief Pointer to \c SDL_GetPlatform() */
    SDL_GetPlatform_pfn _SDL_GetPlatform;
/* SDL_power.h */
    /** \brief Pointer to \c SDL_GetPowerInfo() */
    SDL_GetPowerInfo_pfn _SDL_GetPowerInfo;
/* SDL_rect.h */
    /** \brief Pointer to \c SDL_HasIntersection() */
    SDL_HasIntersection_pfn _SDL_HasIntersection;
    /** \brief Pointer to \c SDL_IntersectRect() */
    SDL_IntersectRect_pfn _SDL_IntersectRect;
    /** \brief Pointer to \c SDL_UnionRect() */
    SDL_UnionRect_pfn _SDL_UnionRect;
    /** \brief Pointer to \c SDL_EnclosePoints() */
    SDL_EnclosePoints_pfn _SDL_EnclosePoints;
    /** \brief Pointer to \c SDL_IntersectRectAndLine() */
    SDL_IntersectRectAndLine_pfn _SDL_IntersectRectAndLine;
/* SDL_render.h */
    /** \brief Pointer to \c SDL_GetNumRenderDrivers() */
    SDL_GetNumRenderDrivers_pfn _SDL_GetNumRenderDrivers;
    /** \brief Pointer to \c SDL_GetRenderDriverInfo() */
    SDL_GetRenderDriverInfo_pfn _SDL_GetRenderDriverInfo;
    /** \brief Pointer to \c SDL_CreateWindowAndRenderer() */
    SDL_CreateWindowAndRenderer_pfn _SDL_CreateWindowAndRenderer;
    /** \brief Pointer to \c SDL_CreateRenderer() */
    SDL_CreateRenderer_pfn _SDL_CreateRenderer;
    /** \brief Pointer to \c SDL_CreateSoftwareRenderer() */
    SDL_CreateSoftwareRenderer_pfn _SDL_CreateSoftwareRenderer;
    /** \brief Pointer to \c SDL_GetRenderer() */
    SDL_GetRenderer_pfn _SDL_GetRenderer;
    /** \brief Pointer to \c SDL_GetRendererInfo() */
    SDL_GetRendererInfo_pfn _SDL_GetRendererInfo;
    /** \brief Pointer to \c SDL_GetRendererOutputSize() */
    SDL_GetRendererOutputSize_pfn _SDL_GetRendererOutputSize;
    /** \brief Pointer to \c SDL_CreateTexture() */
    SDL_CreateTexture_pfn _SDL_CreateTexture;
    /** \brief Pointer to \c SDL_CreateTextureFromSurface() */
    SDL_CreateTextureFromSurface_pfn _SDL_CreateTextureFromSurface;
    /** \brief Pointer to \c SDL_QueryTexture() */
    SDL_QueryTexture_pfn _SDL_QueryTexture;
    /** \brief Pointer to \c SDL_SetTextureColorMod() */
    SDL_SetTextureColorMod_pfn _SDL_SetTextureColorMod;
    /** \brief Pointer to \c SDL_GetTextureColorMod() */
    SDL_GetTextureColorMod_pfn _SDL_GetTextureColorMod;
    /** \brief Pointer to \c SDL_SetTextureAlphaMod() */
    SDL_SetTextureAlphaMod_pfn _SDL_SetTextureAlphaMod;
    /** \brief Pointer to \c SDL_GetTextureAlphaMod() */
    SDL_GetTextureAlphaMod_pfn _SDL_GetTextureAlphaMod;
    /** \brief Pointer to \c SDL_SetTextureBlendMode() */
    SDL_SetTextureBlendMode_pfn _SDL_SetTextureBlendMode;
    /** \brief Pointer to \c SDL_GetTextureBlendMode() */
    SDL_GetTextureBlendMode_pfn _SDL_GetTextureBlendMode;
    /** \brief Pointer to \c SDL_UpdateTexture() */
    SDL_UpdateTexture_pfn _SDL_UpdateTexture;
    /** \brief Pointer to \c SDL_LockTexture() */
    SDL_LockTexture_pfn _SDL_LockTexture;
    /** \brief Pointer to \c SDL_UnlockTexture() */
    SDL_UnlockTexture_pfn _SDL_UnlockTexture;
    /** \brief Pointer to \c SDL_RenderTargetSupported() */
    SDL_RenderTargetSupported_pfn _SDL_RenderTargetSupported;
    /** \brief Pointer to \c SDL_SetRenderTarget() */
    SDL_SetRenderTarget_pfn _SDL_SetRenderTarget;
    /** \brief Pointer to \c SDL_GetRenderTarget() */
    SDL_GetRenderTarget_pfn _SDL_GetRenderTarget;
    /** \brief Pointer to \c SDL_RenderSetLogicalSize() */
    SDL_RenderSetLogicalSize_pfn _SDL_RenderSetLogicalSize;
    /** \brief Pointer to \c SDL_RenderGetLogicalSize() */
    SDL_RenderGetLogicalSize_pfn _SDL_RenderGetLogicalSize;
    /** \brief Pointer to \c SDL_RenderSetViewport() */
    SDL_RenderSetViewport_pfn _SDL_RenderSetViewport;
    /** \brief Pointer to \c SDL_RenderGetViewport() */
    SDL_RenderGetViewport_pfn _SDL_RenderGetViewport;
    /** \brief Pointer to \c SDL_RenderSetClipRect() */
    SDL_RenderSetClipRect_pfn _SDL_RenderSetClipRect;
    /** \brief Pointer to \c SDL_RenderGetClipRect() */
    SDL_RenderGetClipRect_pfn _SDL_RenderGetClipRect;
    /** \brief Pointer to \c SDL_RenderSetScale() */
    SDL_RenderSetScale_pfn _SDL_RenderSetScale;
    /** \brief Pointer to \c SDL_RenderGetScale() */
    SDL_RenderGetScale_pfn _SDL_RenderGetScale;
    /** \brief Pointer to \c SDL_SetRenderDrawColor() */
    SDL_SetRenderDrawColor_pfn _SDL_SetRenderDrawColor;
    /** \brief Pointer to \c SDL_GetRenderDrawColor() */
    SDL_GetRenderDrawColor_pfn _SDL_GetRenderDrawColor;
    /** \brief Pointer to \c SDL_SetRenderDrawBlendMode() */
    SDL_SetRenderDrawBlendMode_pfn _SDL_SetRenderDrawBlendMode;
    /** \brief Pointer to \c SDL_GetRenderDrawBlendMode() */
    SDL_GetRenderDrawBlendMode_pfn _SDL_GetRenderDrawBlendMode;
    /** \brief Pointer to \c SDL_RenderClear() */
    SDL_RenderClear_pfn _SDL_RenderClear;
    /** \brief Pointer to \c SDL_RenderDrawPoint() */
    SDL_RenderDrawPoint_pfn _SDL_RenderDrawPoint;
    /** \brief Pointer to \c SDL_RenderDrawPoints() */
    SDL_RenderDrawPoints_pfn _SDL_RenderDrawPoints;
    /** \brief Pointer to \c SDL_RenderDrawLine() */
    SDL_RenderDrawLine_pfn _SDL_RenderDrawLine;
    /** \brief Pointer to \c SDL_RenderDrawLines() */
    SDL_RenderDrawLines_pfn _SDL_RenderDrawLines;
    /** \brief Pointer to \c SDL_RenderDrawRect() */
    SDL_RenderDrawRect_pfn _SDL_RenderDrawRect;
    /** \brief Pointer to \c SDL_RenderDrawRects() */
    SDL_RenderDrawRects_pfn _SDL_RenderDrawRects;
    /** \brief Pointer to \c SDL_RenderFillRect() */
    SDL_RenderFillRect_pfn _SDL_RenderFillRect;
    /** \brief Pointer to \c SDL_RenderFillRects() */
    SDL_RenderFillRects_pfn _SDL_RenderFillRects;
    /** \brief Pointer to \c SDL_RenderCopy() */
    SDL_RenderCopy_pfn _SDL_RenderCopy;
    /** \brief Pointer to \c SDL_RenderCopyEx() */
    SDL_RenderCopyEx_pfn _SDL_RenderCopyEx;
    /** \brief Pointer to \c SDL_RenderReadPixels() */
    SDL_RenderReadPixels_pfn _SDL_RenderReadPixels;
    /** \brief Pointer to \c SDL_RenderPresent() */
    SDL_RenderPresent_pfn _SDL_RenderPresent;
    /** \brief Pointer to \c SDL_DestroyTexture() */
    SDL_DestroyTexture_pfn _SDL_DestroyTexture;
    /** \brief Pointer to \c SDL_DestroyRenderer() */
    SDL_DestroyRenderer_pfn _SDL_DestroyRenderer;
    /** \brief Pointer to \c SDL_GL_BindTexture() */
    SDL_GL_BindTexture_pfn _SDL_GL_BindTexture;
    /** \brief Pointer to \c SDL_GL_UnbindTexture() */
    SDL_GL_UnbindTexture_pfn _SDL_GL_UnbindTexture;
/* SDL_rwops.h */
    /** \brief Pointer to \c SDL_RWFromFile() */
    SDL_RWFromFile_pfn _SDL_RWFromFile;
    /** \brief Pointer to \c SDL_RWFromFP() */
    SDL_RWFromFP_pfn _SDL_RWFromFP;
    /** \brief Pointer to \c SDL_RWFromMem() */
    SDL_RWFromMem_pfn _SDL_RWFromMem;
    /** \brief Pointer to \c SDL_RWFromConstMem() */
    SDL_RWFromConstMem_pfn _SDL_RWFromConstMem;
    /** \brief Pointer to \c SDL_AllocRW() */
    SDL_AllocRW_pfn _SDL_AllocRW;
    /** \brief Pointer to \c SDL_FreeRW() */
    SDL_FreeRW_pfn _SDL_FreeRW;
    /** \brief Pointer to \c SDL_ReadU8() */
    SDL_ReadU8_pfn _SDL_ReadU8;
    /** \brief Pointer to \c SDL_ReadLE16() */
    SDL_ReadLE16_pfn _SDL_ReadLE16;
    /** \brief Pointer to \c SDL_ReadBE16() */
    SDL_ReadBE16_pfn _SDL_ReadBE16;
    /** \brief Pointer to \c SDL_ReadLE32() */
    SDL_ReadLE32_pfn _SDL_ReadLE32;
    /** \brief Pointer to \c SDL_ReadBE32() */
    SDL_ReadBE32_pfn _SDL_ReadBE32;
    /** \brief Pointer to \c SDL_ReadLE64() */
    SDL_ReadLE64_pfn _SDL_ReadLE64;
    /** \brief Pointer to \c SDL_ReadBE64() */
    SDL_ReadBE64_pfn _SDL_ReadBE64;
    /** \brief Pointer to \c SDL_WriteU8() */
    SDL_WriteU8_pfn _SDL_WriteU8;
    /** \brief Pointer to \c SDL_WriteLE16() */
    SDL_WriteLE16_pfn _SDL_WriteLE16;
    /** \brief Pointer to \c SDL_WriteBE16() */
    SDL_WriteBE16_pfn _SDL_WriteBE16;
    /** \brief Pointer to \c SDL_WriteLE32() */
    SDL_WriteLE32_pfn _SDL_WriteLE32;
    /** \brief Pointer to \c SDL_WriteBE32() */
    SDL_WriteBE32_pfn _SDL_WriteBE32;
    /** \brief Pointer to \c SDL_WriteLE64() */
    SDL_WriteLE64_pfn _SDL_WriteLE64;
    /** \brief Pointer to \c SDL_WriteBE64() */
    SDL_WriteBE64_pfn _SDL_WriteBE64;
/* SDL_shape.h */
    /** \brief Pointer to \c SDL_CreateShapedWindow() */
    SDL_CreateShapedWindow_pfn _SDL_CreateShapedWindow;
    /** \brief Pointer to \c SDL_IsShapedWindow() */
    SDL_IsShapedWindow_pfn _SDL_IsShapedWindow;
    /** \brief Pointer to \c SDL_SetWindowShape() */
    SDL_SetWindowShape_pfn _SDL_SetWindowShape;
    /** \brief Pointer to \c SDL_GetShapedWindowMode() */
    SDL_GetShapedWindowMode_pfn _SDL_GetShapedWindowMode;
/* SDL_stdinc.h */
    /** \brief Pointer to \c SDL_malloc() */
    SDL_malloc_pfn _SDL_malloc;
    /** \brief Pointer to \c SDL_calloc() */
    SDL_calloc_pfn _SDL_calloc;
    /** \brief Pointer to \c SDL_realloc() */
    SDL_realloc_pfn _SDL_realloc;
    /** \brief Pointer to \c SDL_free() */
    SDL_free_pfn _SDL_free;
    /** \brief Pointer to \c SDL_getenv() */
    SDL_getenv_pfn _SDL_getenv;
    /** \brief Pointer to \c SDL_setenv() */
    SDL_setenv_pfn _SDL_setenv;
    /** \brief Pointer to \c SDL_qsort() */
    SDL_qsort_pfn _SDL_qsort;
    /** \brief Pointer to \c SDL_abs() */
    SDL_abs_pfn _SDL_abs;
    /** \brief Pointer to \c SDL_isdigit() */
    SDL_isdigit_pfn _SDL_isdigit;
    /** \brief Pointer to \c SDL_isspace() */
    SDL_isspace_pfn _SDL_isspace;
    /** \brief Pointer to \c SDL_toupper() */
    SDL_toupper_pfn _SDL_toupper;
    /** \brief Pointer to \c SDL_tolower() */
    SDL_tolower_pfn _SDL_tolower;
    /** \brief Pointer to \c SDL_memset() */
    SDL_memset_pfn _SDL_memset;
    /** \brief Pointer to \c SDL_memcpy() */
    SDL_memcpy_pfn _SDL_memcpy;
    /** \brief Pointer to \c SDL_memmove() */
    SDL_memmove_pfn _SDL_memmove;
    /** \brief Pointer to \c SDL_memcmp() */
    SDL_memcmp_pfn _SDL_memcmp;
    /** \brief Pointer to \c SDL_wcslen() */
    SDL_wcslen_pfn _SDL_wcslen;
    /** \brief Pointer to \c SDL_wcslcpy() */
    SDL_wcslcpy_pfn _SDL_wcslcpy;
    /** \brief Pointer to \c SDL_wcslcat() */
    SDL_wcslcat_pfn _SDL_wcslcat;
    /** \brief Pointer to \c SDL_strlen() */
    SDL_strlen_pfn _SDL_strlen;
    /** \brief Pointer to \c SDL_strlcpy() */
    SDL_strlcpy_pfn _SDL_strlcpy;
    /** \brief Pointer to \c SDL_utf8strlcpy() */
    SDL_utf8strlcpy_pfn _SDL_utf8strlcpy;
    /** \brief Pointer to \c SDL_strlcat() */
    SDL_strlcat_pfn _SDL_strlcat;
    /** \brief Pointer to \c SDL_strdup() */
    SDL_strdup_pfn _SDL_strdup;
    /** \brief Pointer to \c SDL_strrev() */
    SDL_strrev_pfn _SDL_strrev;
    /** \brief Pointer to \c SDL_strupr() */
    SDL_strupr_pfn _SDL_strupr;
    /** \brief Pointer to \c SDL_strlwr() */
    SDL_strlwr_pfn _SDL_strlwr;
    /** \brief Pointer to \c SDL_strchr() */
    SDL_strchr_pfn _SDL_strchr;
    /** \brief Pointer to \c SDL_strrchr() */
    SDL_strrchr_pfn _SDL_strrchr;
    /** \brief Pointer to \c SDL_strstr() */
    SDL_strstr_pfn _SDL_strstr;
    /** \brief Pointer to \c SDL_itoa() */
    SDL_itoa_pfn _SDL_itoa;
    /** \brief Pointer to \c SDL_uitoa() */
    SDL_uitoa_pfn _SDL_uitoa;
    /** \brief Pointer to \c SDL_ltoa() */
    SDL_ltoa_pfn _SDL_ltoa;
    /** \brief Pointer to \c SDL_ultoa() */
    SDL_ultoa_pfn _SDL_ultoa;
    /** \brief Pointer to \c SDL_lltoa() */
    SDL_lltoa_pfn _SDL_lltoa;
    /** \brief Pointer to \c SDL_ulltoa() */
    SDL_ulltoa_pfn _SDL_ulltoa;
    /** \brief Pointer to \c SDL_atoi() */
    SDL_atoi_pfn _SDL_atoi;
    /** \brief Pointer to \c SDL_atof() */
    SDL_atof_pfn _SDL_atof;
    /** \brief Pointer to \c SDL_strtol() */
    SDL_strtol_pfn _SDL_strtol;
    /** \brief Pointer to \c SDL_strtoul() */
    SDL_strtoul_pfn _SDL_strtoul;
    /** \brief Pointer to \c SDL_strtoll() */
    SDL_strtoll_pfn _SDL_strtoll;
    /** \brief Pointer to \c SDL_strtoull() */
    SDL_strtoull_pfn _SDL_strtoull;
    /** \brief Pointer to \c SDL_strtod() */
    SDL_strtod_pfn _SDL_strtod;
    /** \brief Pointer to \c SDL_strcmp() */
    SDL_strcmp_pfn _SDL_strcmp;
    /** \brief Pointer to \c SDL_strncmp() */
    SDL_strncmp_pfn _SDL_strncmp;
    /** \brief Pointer to \c SDL_strcasecmp() */
    SDL_strcasecmp_pfn _SDL_strcasecmp;
    /** \brief Pointer to \c SDL_strncasecmp() */
    SDL_strncasecmp_pfn _SDL_strncasecmp;
    /** \brief Pointer to \c SDL_sscanf() */
    SDL_sscanf_pfn _SDL_sscanf;
    /** \brief Pointer to \c SDL_snprintf() */
    SDL_snprintf_pfn _SDL_snprintf;
    /** \brief Pointer to \c SDL_vsnprintf() */
    SDL_vsnprintf_pfn _SDL_vsnprintf;
    /** \brief Pointer to \c SDL_atan() */
    SDL_atan_pfn _SDL_atan;
    /** \brief Pointer to \c SDL_atan2() */
    SDL_atan2_pfn _SDL_atan2;
    /** \brief Pointer to \c SDL_ceil() */
    SDL_ceil_pfn _SDL_ceil;
    /** \brief Pointer to \c SDL_copysign() */
    SDL_copysign_pfn _SDL_copysign;
    /** \brief Pointer to \c SDL_cos() */
    SDL_cos_pfn _SDL_cos;
    /** \brief Pointer to \c SDL_cosf() */
    SDL_cosf_pfn _SDL_cosf;
    /** \brief Pointer to \c SDL_fabs() */
    SDL_fabs_pfn _SDL_fabs;
    /** \brief Pointer to \c SDL_floor() */
    SDL_floor_pfn _SDL_floor;
    /** \brief Pointer to \c SDL_log() */
    SDL_log_pfn _SDL_log;
    /** \brief Pointer to \c SDL_pow() */
    SDL_pow_pfn _SDL_pow;
    /** \brief Pointer to \c SDL_scalbn() */
    SDL_scalbn_pfn _SDL_scalbn;
    /** \brief Pointer to \c SDL_sin() */
    SDL_sin_pfn _SDL_sin;
    /** \brief Pointer to \c SDL_sinf() */
    SDL_sinf_pfn _SDL_sinf;
    /** \brief Pointer to \c SDL_sqrt() */
    SDL_sqrt_pfn _SDL_sqrt;
    /** \brief Pointer to \c SDL_iconv_open() */
    SDL_iconv_open_pfn _SDL_iconv_open;
    /** \brief Pointer to \c SDL_iconv_close() */
    SDL_iconv_close_pfn _SDL_iconv_close;
    /** \brief Pointer to \c SDL_iconv() */
    SDL_iconv_pfn _SDL_iconv;
    /** \brief Pointer to \c SDL_iconv_string() */
    SDL_iconv_string_pfn _SDL_iconv_string;
/* SDL_surface.h */
    /** \brief Pointer to \c SDL_CreateRGBSurface() */
    SDL_CreateRGBSurface_pfn _SDL_CreateRGBSurface;
    /** \brief Pointer to \c SDL_CreateRGBSurfaceFrom() */
    SDL_CreateRGBSurfaceFrom_pfn _SDL_CreateRGBSurfaceFrom;
    /** \brief Pointer to \c SDL_FreeSurface() */
    SDL_FreeSurface_pfn _SDL_FreeSurface;
    /** \brief Pointer to \c SDL_SetSurfacePalette() */
    SDL_SetSurfacePalette_pfn _SDL_SetSurfacePalette;
    /** \brief Pointer to \c SDL_LockSurface() */
    SDL_LockSurface_pfn _SDL_LockSurface;
    /** \brief Pointer to \c SDL_UnlockSurface() */
    SDL_UnlockSurface_pfn _SDL_UnlockSurface;
    /** \brief Pointer to \c SDL_LoadBMP_RW() */
    SDL_LoadBMP_RW_pfn _SDL_LoadBMP_RW;
    /** \brief Pointer to \c SDL_SaveBMP_RW() */
    SDL_SaveBMP_RW_pfn _SDL_SaveBMP_RW;
    /** \brief Pointer to \c SDL_SetSurfaceRLE() */
    SDL_SetSurfaceRLE_pfn _SDL_SetSurfaceRLE;
    /** \brief Pointer to \c SDL_SetColorKey() */
    SDL_SetColorKey_pfn _SDL_SetColorKey;
    /** \brief Pointer to \c SDL_GetColorKey() */
    SDL_GetColorKey_pfn _SDL_GetColorKey;
    /** \brief Pointer to \c SDL_SetSurfaceColorMod() */
    SDL_SetSurfaceColorMod_pfn _SDL_SetSurfaceColorMod;
    /** \brief Pointer to \c SDL_GetSurfaceColorMod() */
    SDL_GetSurfaceColorMod_pfn _SDL_GetSurfaceColorMod;
    /** \brief Pointer to \c SDL_SetSurfaceAlphaMod() */
    SDL_SetSurfaceAlphaMod_pfn _SDL_SetSurfaceAlphaMod;
    /** \brief Pointer to \c SDL_GetSurfaceAlphaMod() */
    SDL_GetSurfaceAlphaMod_pfn _SDL_GetSurfaceAlphaMod;
    /** \brief Pointer to \c SDL_SetSurfaceBlendMode() */
    SDL_SetSurfaceBlendMode_pfn _SDL_SetSurfaceBlendMode;
    /** \brief Pointer to \c SDL_GetSurfaceBlendMode() */
    SDL_GetSurfaceBlendMode_pfn _SDL_GetSurfaceBlendMode;
    /** \brief Pointer to \c SDL_SetClipRect() */
    SDL_SetClipRect_pfn _SDL_SetClipRect;
    /** \brief Pointer to \c SDL_GetClipRect() */
    SDL_GetClipRect_pfn _SDL_GetClipRect;
    /** \brief Pointer to \c SDL_ConvertSurface() */
    SDL_ConvertSurface_pfn _SDL_ConvertSurface;
    /** \brief Pointer to \c SDL_ConvertSurfaceFormat() */
    SDL_ConvertSurfaceFormat_pfn _SDL_ConvertSurfaceFormat;
    /** \brief Pointer to \c SDL_ConvertPixels() */
    SDL_ConvertPixels_pfn _SDL_ConvertPixels;
    /** \brief Pointer to \c SDL_FillRect() */
    SDL_FillRect_pfn _SDL_FillRect;
    /** \brief Pointer to \c SDL_FillRects() */
    SDL_FillRects_pfn _SDL_FillRects;
    /** \brief Pointer to \c SDL_UpperBlit() */
    SDL_UpperBlit_pfn _SDL_UpperBlit;
    /** \brief Pointer to \c SDL_LowerBlit() */
    SDL_LowerBlit_pfn _SDL_LowerBlit;
    /** \brief Pointer to \c SDL_SoftStretch() */
    SDL_SoftStretch_pfn _SDL_SoftStretch;
    /** \brief Pointer to \c SDL_UpperBlitScaled() */
    SDL_UpperBlitScaled_pfn _SDL_UpperBlitScaled;
    /** \brief Pointer to \c SDL_LowerBlitScaled() */
    SDL_LowerBlitScaled_pfn _SDL_LowerBlitScaled;
/* SDL_system.h */
#if defined(__IPHONEOS__) && __IPHONEOS__ || DOXYGEN
    /** \brief Pointer to \c SDL_iPhoneSetAnimationCallback() */
    SDL_iPhoneSetAnimationCallback_pfn _SDL_iPhoneSetAnimationCallback;
    /** \brief Pointer to \c SDL_iPhoneSetEventPump() */
    SDL_iPhoneSetEventPump_pfn _SDL_iPhoneSetEventPump;
#else
    void *__pad7;
    void *__pad8;
#endif /* __IPHONEOS__ */
#if defined(__ANDROID__) && __ANDROID__ || DOXYGEN
    /** \brief Pointer to \c SDL_AndroidGetJNIEnv() */
    SDL_AndroidGetJNIEnv_pfn _SDL_AndroidGetJNIEnv;
    /** \brief Pointer to \c SDL_AndroidGetActivity() */
    SDL_AndroidGetActivity_pfn _SDL_AndroidGetActivity;
    /** \brief Pointer to \c SDL_AndroidGetInternalStoragePath() */
    SDL_AndroidGetInternalStoragePath_pfn _SDL_AndroidGetInternalStoragePath;
    /** \brief Pointer to \c SDL_AndroidGetExternalStorageState() */
    SDL_AndroidGetExternalStorageState_pfn _SDL_AndroidGetExternalStorageState;
    /** \brief Pointer to \c SDL_AndroidGetExternalStoragePath() */
    SDL_AndroidGetExternalStoragePath_pfn _SDL_AndroidGetExternalStoragePath;
#else
    void *__pad9;
    void *__pad10;
    void *__pad11;
    void *__pad12;
    void *__pad13;
#endif /* __ANDROID__ */
/* SDL_syswm.h */
    /** \brief Pointer to \c SDL_GetWindowWMInfo() */
    SDL_GetWindowWMInfo_pfn _SDL_GetWindowWMInfo;
/* SDL_thread.h */
    /** \brief Pointer to \c SDL_CreateThread() */
    SDL_CreateThread_pfn _SDL_CreateThread;
    /** \brief Pointer to \c SDL_GetThreadName() */
    SDL_GetThreadName_pfn _SDL_GetThreadName;
    /** \brief Pointer to \c SDL_ThreadID() */
    SDL_ThreadID_pfn _SDL_ThreadID;
    /** \brief Pointer to \c SDL_GetThreadID() */
    SDL_GetThreadID_pfn _SDL_GetThreadID;
    /** \brief Pointer to \c SDL_SetThreadPriority() */
    SDL_SetThreadPriority_pfn _SDL_SetThreadPriority;
    /** \brief Pointer to \c SDL_WaitThread() */
    SDL_WaitThread_pfn _SDL_WaitThread;
    /** \brief Pointer to \c SDL_TLSCreate() */
    SDL_TLSCreate_pfn _SDL_TLSCreate;
    /** \brief Pointer to \c SDL_TLSGet() */
    SDL_TLSGet_pfn _SDL_TLSGet;
    /** \brief Pointer to \c SDL_TLSSet() */
    SDL_TLSSet_pfn _SDL_TLSSet;
/* SDL_timer.h */
    /** \brief Pointer to \c SDL_GetTicks() */
    SDL_GetTicks_pfn _SDL_GetTicks;
    /** \brief Pointer to \c SDL_GetPerformanceCounter() */
    SDL_GetPerformanceCounter_pfn _SDL_GetPerformanceCounter;
    /** \brief Pointer to \c SDL_GetPerformanceFrequency() */
    SDL_GetPerformanceFrequency_pfn _SDL_GetPerformanceFrequency;
    /** \brief Pointer to \c SDL_Delay() */
    SDL_Delay_pfn _SDL_Delay;
    /** \brief Pointer to \c SDL_AddTimer() */
    SDL_AddTimer_pfn _SDL_AddTimer;
    /** \brief Pointer to \c SDL_RemoveTimer() */
    SDL_RemoveTimer_pfn _SDL_RemoveTimer;
/* SDL_touch.h */
    /** \brief Pointer to \c SDL_GetNumTouchDevices() */
    SDL_GetNumTouchDevices_pfn _SDL_GetNumTouchDevices;
    /** \brief Pointer to \c SDL_GetTouchDevice() */
    SDL_GetTouchDevice_pfn _SDL_GetTouchDevice;
    /** \brief Pointer to \c SDL_GetNumTouchFingers() */
    SDL_GetNumTouchFingers_pfn _SDL_GetNumTouchFingers;
    /** \brief Pointer to \c SDL_GetTouchFinger() */
    SDL_GetTouchFinger_pfn _SDL_GetTouchFinger;
/* SDL_version.h */
    /** \brief Pointer to \c SDL_GetVersion() */
    SDL_GetVersion_pfn _SDL_GetVersion;
    /** \brief Pointer to \c SDL_GetRevision() */
    SDL_GetRevision_pfn _SDL_GetRevision;
    /** \brief Pointer to \c SDL_GetRevisionNumber() */
    SDL_GetRevisionNumber_pfn _SDL_GetRevisionNumber;
/* SDL_video.h */
    /** \brief Pointer to \c SDL_GetNumVideoDrivers() */
    SDL_GetNumVideoDrivers_pfn _SDL_GetNumVideoDrivers;
    /** \brief Pointer to \c SDL_GetVideoDriver() */
    SDL_GetVideoDriver_pfn _SDL_GetVideoDriver;
    /** \brief Pointer to \c SDL_VideoInit() */
    SDL_VideoInit_pfn _SDL_VideoInit;
    /** \brief Pointer to \c SDL_VideoQuit() */
    SDL_VideoQuit_pfn _SDL_VideoQuit;
    /** \brief Pointer to \c SDL_GetCurrentVideoDriver() */
    SDL_GetCurrentVideoDriver_pfn _SDL_GetCurrentVideoDriver;
    /** \brief Pointer to \c SDL_GetNumVideoDisplays() */
    SDL_GetNumVideoDisplays_pfn _SDL_GetNumVideoDisplays;
    /** \brief Pointer to \c SDL_GetDisplayName() */
    SDL_GetDisplayName_pfn _SDL_GetDisplayName;
    /** \brief Pointer to \c SDL_GetDisplayBounds() */
    SDL_GetDisplayBounds_pfn _SDL_GetDisplayBounds;
    /** \brief Pointer to \c SDL_GetNumDisplayModes() */
    SDL_GetNumDisplayModes_pfn _SDL_GetNumDisplayModes;
    /** \brief Pointer to \c SDL_GetDisplayMode() */
    SDL_GetDisplayMode_pfn _SDL_GetDisplayMode;
    /** \brief Pointer to \c SDL_GetDesktopDisplayMode() */
    SDL_GetDesktopDisplayMode_pfn _SDL_GetDesktopDisplayMode;
    /** \brief Pointer to \c SDL_GetCurrentDisplayMode() */
    SDL_GetCurrentDisplayMode_pfn _SDL_GetCurrentDisplayMode;
    /** \brief Pointer to \c SDL_GetClosestDisplayMode() */
    SDL_GetClosestDisplayMode_pfn _SDL_GetClosestDisplayMode;
    /** \brief Pointer to \c SDL_GetWindowDisplayIndex() */
    SDL_GetWindowDisplayIndex_pfn _SDL_GetWindowDisplayIndex;
    /** \brief Pointer to \c SDL_SetWindowDisplayMode() */
    SDL_SetWindowDisplayMode_pfn _SDL_SetWindowDisplayMode;
    /** \brief Pointer to \c SDL_GetWindowDisplayMode() */
    SDL_GetWindowDisplayMode_pfn _SDL_GetWindowDisplayMode;
    /** \brief Pointer to \c SDL_GetWindowPixelFormat() */
    SDL_GetWindowPixelFormat_pfn _SDL_GetWindowPixelFormat;
    /** \brief Pointer to \c SDL_CreateWindow() */
    SDL_CreateWindow_pfn _SDL_CreateWindow;
    /** \brief Pointer to \c SDL_CreateWindowFrom() */
    SDL_CreateWindowFrom_pfn _SDL_CreateWindowFrom;
    /** \brief Pointer to \c SDL_GetWindowID() */
    SDL_GetWindowID_pfn _SDL_GetWindowID;
    /** \brief Pointer to \c SDL_GetWindowFromID() */
    SDL_GetWindowFromID_pfn _SDL_GetWindowFromID;
    /** \brief Pointer to \c SDL_GetWindowFlags() */
    SDL_GetWindowFlags_pfn _SDL_GetWindowFlags;
    /** \brief Pointer to \c SDL_SetWindowTitle() */
    SDL_SetWindowTitle_pfn _SDL_SetWindowTitle;
    /** \brief Pointer to \c SDL_GetWindowTitle() */
    SDL_GetWindowTitle_pfn _SDL_GetWindowTitle;
    /** \brief Pointer to \c SDL_SetWindowIcon() */
    SDL_SetWindowIcon_pfn _SDL_SetWindowIcon;
    /** \brief Pointer to \c SDL_SetWindowData() */
    SDL_SetWindowData_pfn _SDL_SetWindowData;
    /** \brief Pointer to \c SDL_GetWindowData() */
    SDL_GetWindowData_pfn _SDL_GetWindowData;
    /** \brief Pointer to \c SDL_SetWindowPosition() */
    SDL_SetWindowPosition_pfn _SDL_SetWindowPosition;
    /** \brief Pointer to \c SDL_GetWindowPosition() */
    SDL_GetWindowPosition_pfn _SDL_GetWindowPosition;
    /** \brief Pointer to \c SDL_SetWindowSize() */
    SDL_SetWindowSize_pfn _SDL_SetWindowSize;
    /** \brief Pointer to \c SDL_GetWindowSize() */
    SDL_GetWindowSize_pfn _SDL_GetWindowSize;
    /** \brief Pointer to \c SDL_SetWindowMinimumSize() */
    SDL_SetWindowMinimumSize_pfn _SDL_SetWindowMinimumSize;
    /** \brief Pointer to \c SDL_GetWindowMinimumSize() */
    SDL_GetWindowMinimumSize_pfn _SDL_GetWindowMinimumSize;
    /** \brief Pointer to \c SDL_SetWindowMaximumSize() */
    SDL_SetWindowMaximumSize_pfn _SDL_SetWindowMaximumSize;
    /** \brief Pointer to \c SDL_GetWindowMaximumSize() */
    SDL_GetWindowMaximumSize_pfn _SDL_GetWindowMaximumSize;
    /** \brief Pointer to \c SDL_SetWindowBordered() */
    SDL_SetWindowBordered_pfn _SDL_SetWindowBordered;
    /** \brief Pointer to \c SDL_ShowWindow() */
    SDL_ShowWindow_pfn _SDL_ShowWindow;
    /** \brief Pointer to \c SDL_HideWindow() */
    SDL_HideWindow_pfn _SDL_HideWindow;
    /** \brief Pointer to \c SDL_RaiseWindow() */
    SDL_RaiseWindow_pfn _SDL_RaiseWindow;
    /** \brief Pointer to \c SDL_MaximizeWindow() */
    SDL_MaximizeWindow_pfn _SDL_MaximizeWindow;
    /** \brief Pointer to \c SDL_MinimizeWindow() */
    SDL_MinimizeWindow_pfn _SDL_MinimizeWindow;
    /** \brief Pointer to \c SDL_RestoreWindow() */
    SDL_RestoreWindow_pfn _SDL_RestoreWindow;
    /** \brief Pointer to \c SDL_SetWindowFullscreen() */
    SDL_SetWindowFullscreen_pfn _SDL_SetWindowFullscreen;
    /** \brief Pointer to \c SDL_GetWindowSurface() */
    SDL_GetWindowSurface_pfn _SDL_GetWindowSurface;
    /** \brief Pointer to \c SDL_UpdateWindowSurface() */
    SDL_UpdateWindowSurface_pfn _SDL_UpdateWindowSurface;
    /** \brief Pointer to \c SDL_UpdateWindowSurfaceRects() */
    SDL_UpdateWindowSurfaceRects_pfn _SDL_UpdateWindowSurfaceRects;
    /** \brief Pointer to \c SDL_SetWindowGrab() */
    SDL_SetWindowGrab_pfn _SDL_SetWindowGrab;
    /** \brief Pointer to \c SDL_GetWindowGrab() */
    SDL_GetWindowGrab_pfn _SDL_GetWindowGrab;
    /** \brief Pointer to \c SDL_SetWindowBrightness() */
    SDL_SetWindowBrightness_pfn _SDL_SetWindowBrightness;
    /** \brief Pointer to \c SDL_GetWindowBrightness() */
    SDL_GetWindowBrightness_pfn _SDL_GetWindowBrightness;
    /** \brief Pointer to \c SDL_SetWindowGammaRamp() */
    SDL_SetWindowGammaRamp_pfn _SDL_SetWindowGammaRamp;
    /** \brief Pointer to \c SDL_GetWindowGammaRamp() */
    SDL_GetWindowGammaRamp_pfn _SDL_GetWindowGammaRamp;
    /** \brief Pointer to \c SDL_DestroyWindow() */
    SDL_DestroyWindow_pfn _SDL_DestroyWindow;
    /** \brief Pointer to \c SDL_IsScreenSaverEnabled() */
    SDL_IsScreenSaverEnabled_pfn _SDL_IsScreenSaverEnabled;
    /** \brief Pointer to \c SDL_EnableScreenSaver() */
    SDL_EnableScreenSaver_pfn _SDL_EnableScreenSaver;
    /** \brief Pointer to \c SDL_DisableScreenSaver() */
    SDL_DisableScreenSaver_pfn _SDL_DisableScreenSaver;
    /** \brief Pointer to \c SDL_GL_LoadLibrary() */
    SDL_GL_LoadLibrary_pfn _SDL_GL_LoadLibrary;
    /** \brief Pointer to \c SDL_GL_GetProcAddress() */
    SDL_GL_GetProcAddress_pfn _SDL_GL_GetProcAddress;
    /** \brief Pointer to \c SDL_GL_UnloadLibrary() */
    SDL_GL_UnloadLibrary_pfn _SDL_GL_UnloadLibrary;
    /** \brief Pointer to \c SDL_GL_ExtensionSupported() */
    SDL_GL_ExtensionSupported_pfn _SDL_GL_ExtensionSupported;
    /** \brief Pointer to \c SDL_GL_SetAttribute() */
    SDL_GL_SetAttribute_pfn _SDL_GL_SetAttribute;
    /** \brief Pointer to \c SDL_GL_GetAttribute() */
    SDL_GL_GetAttribute_pfn _SDL_GL_GetAttribute;
    /** \brief Pointer to \c SDL_GL_CreateContext() */
    SDL_GL_CreateContext_pfn _SDL_GL_CreateContext;
    /** \brief Pointer to \c SDL_GL_MakeCurrent() */
    SDL_GL_MakeCurrent_pfn _SDL_GL_MakeCurrent;
    /** \brief Pointer to \c SDL_GL_GetCurrentWindow() */
    SDL_GL_GetCurrentWindow_pfn _SDL_GL_GetCurrentWindow;
    /** \brief Pointer to \c SDL_GL_GetCurrentContext() */
    SDL_GL_GetCurrentContext_pfn _SDL_GL_GetCurrentContext;
    /** \brief Pointer to \c SDL_GL_SetSwapInterval() */
    SDL_GL_SetSwapInterval_pfn _SDL_GL_SetSwapInterval;
    /** \brief Pointer to \c SDL_GL_GetSwapInterval() */
    SDL_GL_GetSwapInterval_pfn _SDL_GL_GetSwapInterval;
    /** \brief Pointer to \c SDL_GL_SwapWindow() */
    SDL_GL_SwapWindow_pfn _SDL_GL_SwapWindow;
    /** \brief Pointer to \c SDL_GL_DeleteContext() */
    SDL_GL_DeleteContext_pfn _SDL_GL_DeleteContext;
} PyCSDL2_CAPI;

#ifndef PYCSDL2_MODULE

/**
 * \brief Imports csdl2 and returns its PyCSDL2_CAPI.
 * \returns const pointer to PyCSDL2_CAPI, or NULL when an exception occurred.
 */
static const PyCSDL2_CAPI *PyCSDL2_Import(void)
{
    static const PyCSDL2_CAPI *capi;

    if (!capi)
        capi = (const PyCSDL2_CAPI*) PyCapsule_Import("csdl2._C_API", 0);
    return capi;
}

#endif /* PYCSDL2_MODULE */

#ifdef __cplusplus
}
#endif
#endif /* _PYCSDL2_H_ */
