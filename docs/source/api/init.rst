Initialization and Shutdown
===========================
.. module:: csdl2

.. function:: SDL_Init(flags: int) -> None

   Initializes the subsystems specified by `flags`, which is one or more of the
   following constants OR'ed together:

   * :const:`SDL_INIT_TIMER`
   * :const:`SDL_INIT_AUDIO`
   * :const:`SDL_INIT_VIDEO` (implies :const:`SDL_INIT_EVENTS`)
   * :const:`SDL_INIT_JOYSTICK` (implies :const:`SDL_INIT_EVENTS`)
   * :const:`SDL_INIT_HAPTIC`
   * :const:`SDL_INIT_GAMECONTROLLER` (implies :const:`SDL_INIT_JOYSTICK`)

   Alternatively, pass :const:`SDL_INIT_EVERYTHING` to initialize all
   subsystems.

   Unless the :const:`SDL_INIT_NOPARACHUTE` flag is set, it will install
   cleanup signal handlers for some commonly ignored fatal signals like
   SIGSEGV.

   :param int flags: subsystems to initialize, OR'ed together
   :returns: None
   :raises RuntimeError: if any subsystem initialization failed.

.. py:data:: SDL_INIT_TIMER
             SDL_INIT_AUDIO
             SDL_INIT_VIDEO
             SDL_INIT_JOYSTICK
             SDL_INIT_HAPTIC
             SDL_INIT_GAMECONTROLLER
             SDL_INIT_EVENTS
             SDL_INIT_NOPARACHUTE
             SDL_INIT_EVERYTHING

   Flags that may be given to :func:`SDL_Init`, SDL_InitSubSystem,
   SDL_QuitSubSystem and SDL_WasInit.
