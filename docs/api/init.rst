Initialization and Shutdown
===========================
.. currentmodule:: csdl2

.. _subsystem-flags:

Subsystem Flags
---------------
.. data:: SDL_INIT_TIMER

   Timer subsystem.

.. data:: SDL_INIT_AUDIO

   Audio subsystem.

.. data:: SDL_INIT_VIDEO

   Video subsystem. (Implies :const:`SDL_INIT_EVENTS`)

.. data:: SDL_INIT_JOYSTICK

   Joystick subsystem. (Implies :const:`SDL_INIT_EVENTS`)

.. data:: SDL_INIT_HAPTIC

   Haptic (force feedback) subsystem.

.. data:: SDL_INIT_GAMECONTROLLER

   Controller subsystem. (Implies :const:`SDL_INIT_JOYSTICK`)

.. data:: SDL_INIT_EVENTS

   Events subsystem.

.. data:: SDL_INIT_EVERYTHING

   Initialize all subsystems.

.. data:: SDL_INIT_NOPARACHUTE

   This flag is provided for compatibility and is ignored.

Initialization
--------------
.. function:: SDL_Init(flags)

   Initializes the SDL library. This must be called before using any other SDL
   function.

   :param int flags: :ref:`subsystem-flags` of subsystems to initialize, OR'd
                     together.

.. function:: SDL_InitSubSystem(flags)

   Initialize specific subsystems.

   Subsystem initialization is ref-counted. You must call
   :func:`SDL_QuitSubSystem` for each :func:`SDL_InitSubSystem` to correctly
   shutdown a subsystem manually (or call :func:`SDL_Quit` to force a
   shutdown). If a subsystem is already loaded then this call will increase the
   refcount and return.

   :param int flags: :ref:`subsystem-flags` of subsystems to initialize, OR'd
                     together.
