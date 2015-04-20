Event Handling
==============
.. module:: csdl2

Event handling allows your application to receive input from the user. Event
handling is initialized with a call to:

>>> from csdl2 import *
>>> SDL_Init(SDL_INIT_EVENTS)

SDL stores each event as a SDL_Event in an event queue. SDL_Event structures
are read from the queue with the SDL_PollEvent function and it is then up to
the application to process the information stored with them.

.. class:: SDL_Event

   A union that contains structures for the different event types.

   .. attribute:: type

      An int specifying the event type. Use the event type's
      corresponding attribute to get/set information about the event:

      +----------------------------------------+----------------------------+
      | Value of :attr:`type`                  | Attr of :class:`SDL_Event` |
      +========================================+============================+
      | :const:`SDL_CONTROLLERAXISMOTION`      | :attr:`SDL_Event.caxis`    |
      +----------------------------------------+----------------------------+
      | :const:`SDL_CONTROLLERBUTTONDOWN`,     | :attr:`SDL_Event.cbutton`  |
      | :const:`SDL_CONTROLLERBUTTONUP`        |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_CONTROLLERDEVICEADDED`,    | :attr:`SDL_Event.cdevice`  |
      | :const:`SDL_CONTROLLERDEVICEREMOVED`,  |                            |
      | :const:`SDL_CONTROLLERDEVICEREMAPPED`  |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_DOLLARGESTURE`,            | :attr:`SDL_Event.dgesture` |
      | :const:`SDL_DOLLARRECORD`              |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_DROPFILE`                  | :attr:`SDL_Event.drop`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_FINGERMOTION`,             | :attr:`SDL_Event.tfinger`  |
      | :const:`SDL_FINGERDOWN`,               |                            |
      | :const:`SDL_FINGERUP`                  |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_KEYDOWN`,                  | :attr:`SDL_Event.key`      |
      | :const:`SDL_KEYUP`                     |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_JOYAXISMOTION`             | :attr:`SDL_Event.jaxis`    |
      +----------------------------------------+----------------------------+
      | :const:`SDL_JOYBALLMOTION`             | :attr:`SDL_Event.jball`    |
      +----------------------------------------+----------------------------+
      | :const:`SDL_JOYHATMOTION`              | :attr:`SDL_Event.jhat`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_JOYBUTTONDOWN`,            | :attr:`SDL_Event.jbutton`  |
      | :const:`SDL_JOYBUTTONUP`               |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_JOYDEVICEADDED`,           | :attr:`SDL_Event.jdevice`  |
      | :const:`SDL_JOYDEVICEREMOVED`          |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_MOUSEMOTION`               | :attr:`SDL_Event.motion`   |
      +----------------------------------------+----------------------------+
      | :const:`SDL_MOUSEBUTTONDOWN`,          | :attr:`SDL_Event.button`   |
      | :const:`SDL_MOUSEBUTTONUP`             |                            |
      +----------------------------------------+----------------------------+
      | :const:`SDL_MOUSEWHEEL`                | :attr:`SDL_Event.wheel`    |
      +----------------------------------------+----------------------------+
      | :const:`SDL_MULTIGESTURE`              | :attr:`SDL_Event.mgesture` |
      +----------------------------------------+----------------------------+
      | :const:`SDL_QUIT`                      | :attr:`SDL_Event.quit`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_SYSWMEVENT`                | :attr:`SDL_Event.syswm`    |
      +----------------------------------------+----------------------------+
      | :const:`SDL_TEXTEDITING`               | :attr:`SDL_Event.edit`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_TEXTINPUT`                 | :attr:`SDL_Event.text`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_USEREVENT`                 | :attr:`SDL_Event.user`     |
      +----------------------------------------+----------------------------+
      | :const:`SDL_WINDOWEVENT`               | :attr:`SDL_Event.window`   |
      +----------------------------------------+----------------------------+

.. data:: SDL_QUIT

   User-requested quit.

.. data:: SDL_APP_TERMINATING

   The application is being terminated by the OS. Called on iOS in
   applicationWillTerminate(). Called on Android in onDestroy().

.. data:: SDL_APP_LOWMEMORY

   The application is low on memory, free memory if possible. Called on iOS in
   applicationDidReceiveMemoryWarning(). Called on Android in onLowMemory().

.. data:: SDL_APP_WILLENTERBACKGROUND

   The application is about to enter the background. Called on iOS in
   applicationWillResignActive(). Called on Android in onPause().

.. data:: SDL_APP_DIDENTERBACKGROUND

   The application did enter the background and may not get CPU for some time.
   Called on iOS in applicationDidEnterBackground(). Called on Android in
   onPause().

.. data:: SDL_APP_WILLENTERFOREGROUND

   The application is about to enter the foreground. Called on iOS in
   applicationWillEnterForeground(). Called on Android in onResume().

.. data:: SDL_APP_DIDENTERFOREGROUND

   The application is now interactive. Called on iOS in
   applicationDidBecomeActive(). Called on Android in onResume().

.. data:: SDL_WINDOWEVENT

   Window state change.

.. data:: SDL_SYSWMEVENT

   System specific event.

.. data:: SDL_KEYDOWN

   Key pressed.

.. data:: SDL_KEYUP

   Key released.

.. data:: SDL_TEXTEDITING

   Keyboard text editing (composition).

.. data:: SDL_TEXTINPUT

   Keyboard text input.

.. data:: SDL_MOUSEMOTION

   Mouse moved.

.. data:: SDL_MOUSEBUTTONDOWN

   Mouse button pressed.

.. data:: SDL_MOUSEBUTTONUP

   Mouse button released.

.. data:: SDL_MOUSEWHEEL

   Mouse wheel motion.

.. data:: SDL_JOYAXISMOTION

   Joystick axis motion.

.. data:: SDL_JOYBALLMOTION

   Joystick trackball motion.

.. data:: SDL_JOYHATMOTION

   Joystick hat position change.

.. data:: SDL_JOYBUTTONDOWN

   Joystick button pressed.

.. data:: SDL_JOYBUTTONUP

   Joystick button released.

.. data:: SDL_JOYDEVICEADDED

   A new joystick has been inserted into the system.

.. data:: SDL_JOYDEVICEREMOVED

   An opened joystick has been removed.

.. data:: SDL_CONTROLLERAXISMOTION

   Game controller axis motion.

.. data:: SDL_CONTROLLERBUTTONDOWN

   Game controller button pressed.

.. data:: SDL_CONTROLLERBUTTONUP

   Game controller button released.

.. data:: SDL_CONTROLLERDEVICEADDED

   A new game controller has been inserted into the system.

.. data:: SDL_CONTROLLERDEVICEREMOVED

   A opened game controller has been removed.

.. data:: SDL_CONTROLLERDEVICEREMAPPED

   The controller mapping was updated.

.. data:: SDL_FINGERDOWN

   User has touched input device.

.. data:: SDL_FINGERUP

   User stopped touching input device.

.. data:: SDL_FINGERMOTION

   User is dragging finger on input device.

.. data:: SDL_DOLLARGESTURE

   User made a dollar gesture.

.. data:: SDL_DOLLARRECORD

   When recording a gesture with SDL_RecordGesture, the user made a dollar
   gesture that was recorded.

.. data:: SDL_MULTIGESTURE

   User made a gesture with multiple fingers.

.. data:: SDL_CLIPBOARDUPDATE

   The clipboard changed.

.. data:: SDL_DROPFILE

   The system requests a file open.

.. data:: SDL_USEREVENT
          SDL_LASTEVENT

   Events :const:`SDL_USEREVENT` through :const:`SDL_LASTEVENT` are for your
   use, and should be allocated with SDL_RegisterEvents

.. function:: SDL_PeepEvents(events, numevents: int, action: int, minType: int, maxType: int) -> int

   If `action` is :const:`SDL_ADDEVENT`, up to `numevents` events will be added
   to the back of the event queue. Returns the number of events added.

   If `action` is :const:`SDL_PEEKEVENT`, up to `numevents` events from the
   front of the event queue, within `minType` and `maxType`, will be returned
   in `events`, but will not be removed from the queue. Returns number of
   events peeked.

   If `action` is :const:`SDL_GETEVENT`, up to `numevents` events from the
   front of the event queue, within `minType` and `maxType`, will be returned
   in `events`, and will be removed from the queue. Returns number of events
   retrieved.

   :param SDL_Event events: Either a :class:`SDL_Event` object, or a buffer of
                            equivalent size.
   :param int numevents: If `action` is :const:`SDL_ADDEVENT`, the number of
                         events to add to the event queue. If `action` is
                         :const:`SDL_PEEKEVENT` or :const:`SDL_GETEVENT`, the
                         maximum number of events to retrieve.
   :param int action: One of :const:`SDL_ADDEVENT`, :const:`SDL_PEEKEVENT`
                      or :const:`SDL_GETEVENT`.
   :param int minType: minimum value of the event type to be considered.
                       :const:`SDL_FIRSTEVENT` is a safe choice.
   :param int maxType: maximum value of the event type to be considered.
                       :const:`SDL_LASTEVENT` is a safe choice.
   :returns: Number of events added to the event queue for
             :const:`SDL_ADDEVENT`, number of events retrieved from the event
             queue for :const:`SDL_PEEKEVENT` and :const:`SDL_GETEVENT`.
   :raises BufferError: The provided `events` buffer is of the wrong size, or
                        is not writable if `action` is :const:`SDL_PEEKEVENT`
                        or :const:`SDL_GETEVENT`.

.. data:: SDL_ADDEVENT
          SDL_PEEKEVENT
          SDL_GETEVENT

   Possible actions for :func:`SDL_PeepEvents`.
