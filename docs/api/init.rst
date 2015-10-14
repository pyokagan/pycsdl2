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

.. function:: SDL_WasInit(flags) -> int

   Return a mask of the specified subsystems which have previously been
   initialized.

   :param int flags: :ref:`subsystem-flags` of subsystems to query, OR'd
                     together.
   :returns: The initialization status of the specified subsystems, or a mask
             of all initialized subsystems if `flags` is 0.

Shutdown
--------
.. function:: SDL_QuitSubSystem(flags)

   Shut down specific subsystems.

   Subsystem initialization is ref-counted. :func:`SDL_QuitSubSystem` will
   decrement the refcount for each of the specified subsystems, and if the
   refcount of a subsystem reached 0 that subsystem is shut down.

   :param int flags: :ref:`subsystem-flags` of subsystems to shut down, OR'd
                     together.

   .. note::

      If you start a subsystem using a call to that subsystem's init function
      (e.g. :func:`SDL_VideoInit`) instead of :func:`SDL_Init` or
      :func:`SDL_InitSubSystem`, :func:`SDL_QuitSubSystem` will not work. You
      will need to use that subsystem's quit function (e.g.
      :func:`SDL_VideoQuit`) directly instead.

   .. note::

      You still need to call :func:`SDL_Quit` even if you close all open
      subsystems with :func:`SDL_QuitSubSystem`.
