Display and Window Management
=============================
.. currentmodule:: csdl2

.. class:: SDL_Window

   A window.

   It cannot be initialized directly. Instead, create one with
   :func:`SDL_CreateWindow`.

Window creation
---------------
.. function:: SDL_CreateWindow(title: str, x: int, y: int, w: int, h: int, flags: int) -> SDL_Window

   Creates a window with the specified title, position, dimensions and flags.

   :param str title: Title of the window
   :param int x: X position of the window, :const:`SDL_WINDOWPOS_CENTERED` or
                 :const:`SDL_WINDOWPOS_UNDEFINED`.
   :param int y: Y position of the window, :const:`SDL_WINDOWPOS_CENTERED` or
                 :const:`SDL_WINDOWPOS_UNDEFINED`.
   :param int w: Width of the window.
   :param int h: Height of the window.
   :param int flags: 0, or one or more of the following flags OR'ed together:
                     :const:`SDL_WINDOW_FULLSCREEN`,
                     :const:`SDL_WINDOW_FULLSCREEN_DESKTOP`,
                     :const:`SDL_WINDOW_OPENGL`,
                     :const:`SDL_WINDOW_SHOWN`,
                     :const:`SDL_WINDOW_HIDDEN`,
                     :const:`SDL_WINDOW_BORDERLESS`,
                     :const:`SDL_WINDOW_RESIZABLE`,
                     :const:`SDL_WINDOW_MINIMIZED`,
                     :const:`SDL_WINDOW_MAXIMIZED`,
                     :const:`SDL_WINDOW_INPUT_GRABBED`.
   :returns: A new :class:`SDL_Window`
   :raises RuntimeError: if the Window could not be created.

.. data:: SDL_WINDOWPOS_UNDEFINED

   Used to indicate that you don't care what the window position is in any
   display.

.. data:: SDL_WINDOWPOS_CENTERED

   Used to indicate that the window position should be centered in any display.

.. data:: SDL_WINDOW_FULLSCREEN

   The window is fullscreen.

.. data:: SDL_WINDOW_OPENGL

   The window is usable with an OpenGL context.

.. data:: SDL_WINDOW_SHOWN

   The window is visible.

.. data:: SDL_WINDOW_HIDDEN

   The window is hidden.

.. data:: SDL_WINDOW_BORDERLESS

   The window has no window decoration.

.. data:: SDL_WINDOW_RESIZABLE

   The window is resizable.

.. data:: SDL_WINDOW_MINIMIZED

   The window is minimized.

.. data:: SDL_WINDOW_MAXIMIZED

   The window is maximized.

.. data:: SDL_WINDOW_INPUT_GRABBED

   The window has grabbed input focus.

.. data:: SDL_WINDOW_INPUT_FOCUS

   The window has input focus.

.. data:: SDL_WINDOW_MOUSE_FOCUS

   The window has mouse focus.

.. data:: SDL_WINDOW_FULLSCREEN_DESKTOP

   The window is exclusively fullscreen -- the screen display mode is set to
   match the window dimensions.

.. data:: SDL_WINDOW_FOREIGN

   The window was not created by SDL.

Window destruction
------------------
.. function:: SDL_DestroyWindow(window: SDL_Window) -> None

   Destroys a window, freeing up its resources.

   There is no need to manually call this function. :class:`SDL_Window` will
   automatically call it as part of its destructor.

   :param SDL_Window window: Window to be destroyed.

   .. warning:: Once destroyed, do not access the window. Doing so will at best
                raise errors and at worse crash the interpreter.

Window Properties
-----------------
.. function:: SDL_GetWindowTitle(window: SDL_Window) -> str

   Returns the title of the window.

   :param window: The window.
   :type window: :class:`SDL_Window`
   :returns: The title of the window.

Window Events
-------------
.. data:: SDL_WINDOWEVENT_NONE

   This constant is not used.

.. data:: SDL_WINDOWEVENT_SHOWN

   The value of SDL_WindowEvent.type when the Window has been shown.

.. data:: SDL_WINDOWEVENT_HIDDEN

   The value of SDL_WindowEvent.type when the window has been hidden.

.. data:: SDL_WINDOWEVENT_EXPOSED

   The value of SDL_WindowEvent.type when the Window has been exposed and
   should been redrawn.

.. data:: SDL_WINDOWEVENT_MOVED

   The value of SDL_WindowEvent.type when the window has been moved.
   SDL_WindowEvent.data1 is the new x position and SDL_WindowEvent.data2 is the
   new y position.

.. data:: SDL_WINDOWEVENT_RESIZED

   The value of SDL_WindowEvent.type when the window has been resized.
   SDL_WindowEvent.data1 is the new width and SDL_WindowEvent.data2 is the new
   height.

.. data:: SDL_WINDOWEVENT_SIZE_CHANGED

   The value of SDL_WindowEvent.type when the window size has changed, either
   as a result of an API call or through the system or user changing the window
   size. SDL_WindowEvent.data1 is the new width and SDL_WindowEvent.data2 is
   the new height.

.. data:: SDL_WINDOWEVENT_MINIMIZED

   The value of SDL_WindowEvent.type when the window has been minimized.

.. data:: SDL_WINDOWEVENT_MAXIMIZED

   The value of SDL_WindowEvent.type when the window has been maximized.

.. data:: SDL_WINDOWEVENT_RESTORED

   The value of SDL_WindowEvent.type when the window has been restored to
   normal size and position.

.. data:: SDL_WINDOWEVENT_ENTER

   The value of SDL_WindowEvent.type when the window has gained mouse focus.

.. data:: SDL_WINDOWEVENT_LEAVE

   The value of SDL_WindowEvent.type when the window has lost mouse focus.

.. data:: SDL_WINDOWEVENT_FOCUS_GAINED

   The value of SDL_WindowEvent.type when the window has gained keyboard focus.

.. data:: SDL_WINDOWEVENT_FOCUS_LOST

   The value of SDL_WindowEvent.type when the window has lost keyboard focus.

.. data:: SDL_WINDOWEVENT_CLOSE

   The value of SDL_WindowEvent.type when the window manager requests that the
   window be closed.

OpenGL configuration attributes
-------------------------------
OpenGL configuration attributes control the properties of the OpenGL context
that is created with SDL_GL_CreateContext. These attributes are set with
SDL_GL_SetAttribute and read with SDL_GL_GetAttribute.

Note that the following attributes must be set *before* the window is created
with :func:`SDL_CreateWindow`:

* :const:`SDL_GL_RED_SIZE`
* :const:`SDL_GL_GREEN_SIZE`
* :const:`SDL_GL_BLUE_SIZE`
* :const:`SDL_GL_ALPHA_SIZE`
* :const:`SDL_GL_DOUBLEBUFFER`

.. data:: SDL_GL_RED_SIZE

   OpenGL configuration attribute for the minimum number of bits for the red
   channel of the color buffer. Defaults to 3.

.. data:: SDL_GL_GREEN_SIZE

   OpenGL configuration attribute for the minimum number of bits for the green
   channel of the color buffer. Defaults to 3.

.. data:: SDL_GL_BLUE_SIZE

   OpenGL configuration attribute for the minimum number of bits for the blue
   channel of the color buffer. Defaults to 2.

.. data:: SDL_GL_ALPHA_SIZE

   OpenGL configuration attribute for the minimum number of bits for the alpha
   channel of the color buffer. Defaults to 0.

.. data:: SDL_GL_BUFFER_SIZE

   OpenGL configuration attribute for the minimum number of bits for frame
   buffer size. Defaults to 0.

.. data:: SDL_GL_DOUBLEBUFFER

   OpenGL configuration attribute for whether the output is single or double
   buffered. Defaults to double buffering on.

.. data:: SDL_GL_DEPTH_SIZE

   OpenGL configuration attribute for the minimum number of bits in the depth
   buffer. Defaults to 16.

.. data:: SDL_GL_STENCIL_SIZE

   OpenGL configuration attribute for the minimum number of bits in the stencil
   buffer. Defaults to 0.

.. data:: SDL_GL_ACCUM_RED_SIZE

   OpenGL configuration attribute for the minimum number of bits for the red
   channel of the accumulation buffer. Defaults to 0.

.. data:: SDL_GL_ACCUM_GREEN_SIZE

   OpenGL configuration attribute for the minimum number of bits for the green
   channel of the accumulation buffer. Defaults to 0.

.. data:: SDL_GL_ACCUM_BLUE_SIZE

   OpenGL configuration attribute for the the minimum number of bits for the
   blue channel of the accumulation buffer. Defaults to 0.

.. data:: SDL_GL_ACCUM_ALPHA_SIZE

   OpenGL configuration attribute for the minimum number of bits for the alpha
   channel of the accumulation buffer. Defaults to 0.

.. data:: SDL_GL_STEREO

   OpenGL configuration attribute for whether the output is stereo 3D. Defaults
   to off.

.. data:: SDL_GL_MULTISAMPLEBUFFERS

   OpenGL configuration attribute for the number of buffers used for
   multisample anti-aliasing. Defaults to 0.

.. data:: SDL_GL_MULTISAMPLESAMPLES

   OpenGL configuration attribute for the number of samples used around the
   current pixel used for multisample anti-aliasing. Defaults to 0.

.. data:: SDL_GL_ACCELERATED_VISUAL

   Set this OpenGL configuration attribute to 1 to require hardware
   acceleration, set to 0 to force software rendering. Default is to allow
   either.

.. data:: SDL_GL_CONTEXT_MAJOR_VERSION

   OpenGL configuration attribute for the OpenGL context major version.

.. data:: SDL_GL_CONTEXT_MINOR_VERSION

   OpenGL configuration attribute for the OpenGL context minor version.

.. data:: SDL_GL_CONTEXT_FLAGS

   OpenGL context creation flags. The value can be one or more of
   :const:`SDL_GL_CONTEXT_DEBUG_FLAG`,
   :const:`SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG`,
   :const:`SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG`,
   :const:`SDL_GL_CONTEXT_RESET_ISOLATION_FLAG`. Default is 0 (no flags set).

.. data:: SDL_GL_CONTEXT_PROFILE_MASK

   OpenGL context creation profile. The value must be one of
   :const:`SDL_GL_CONTEXT_PROFILE_CORE`,
   :const:`SDL_GL_CONTEXT_PROFILE_COMPATIBILITY`,
   :const:`SDL_GL_CONTEXT_PROFILE_ES`. Default depends on the platform.

.. data:: SDL_GL_SHARE_WITH_CURRENT_CONTEXT

   OpenGL configuration attribute to enable context sharing. Default is 0
   (don't share contexts).

OpenGL flags
------------
These flags are set through the :const:`SDL_GL_CONTEXT_FLAGS` OpenGL
configuration attribute.

.. data:: SDL_GL_CONTEXT_DEBUG_FLAG

   This flag maps to :const:`GLX_CONTEXT_DEBUG_BIT_ARB` in the
   `GLX_ARB_create_context`_ extension and :const:`WGL_CONTEXT_DEBUG_BIT_ARB`
   in the `WGL_ARB_create_context`_ extension, and is ignored if these
   extensions are not available. This flag puts OpenGL into a "debug" mode
   which might assist with debugging, possibly at a loss of performance.

.. data:: SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG

   This flag maps to :const:`GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB` in the
   `GLX_ARB_create_context`_ extension and
   :const:`WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB` in the
   `WGL_ARB_create_context`_ extension, and is ignored if these extensions are
   not available. This flag puts OpenGL into a "forward compatible" mode, where
   no deprecated functionality will be supported, possibly at a gain in
   performance. This only applies to OpenGL 3.0 and later contexts.

.. _`GLX_ARB_create_context`:
   https://www.opengl.org/registry/specs/ARB/glx_create_context.txt

.. _`WGL_ARB_create_context`:
   https://www.opengl.org/registry/specs/ARB/wgl_create_context.txt

.. data:: SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG

   This flag maps to :const:`GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB` in the
   `GLX_ARB_create_context_robustness`_ extenstion and
   :const:`WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB` in the
   `WGL_ARB_create_context_robustness`_ extension, and is ignored if these
   extensions are not available. This flag creates an OpenGL context that
   supports the `GL_ARB_robustness`_ extension -- a mode that offers a few APIs
   that are safer than the usual defaults.

.. _`GL_ARB_robustness`:
   https://www.opengl.org/registry/specs/ARB/robustness.txt

.. _`GLX_ARB_create_context_robustness`:
   https://www.opengl.org/registry/specs/ARB/glx_create_context_robustness.txt

.. data:: SDL_GL_CONTEXT_RESET_ISOLATION_FLAG

   This flag maps to :const:`GLX_CONTEXT_RESET_ISOLATION_BIT_ARB` in the
   `GLX_ARB_robustness_isolation`_ extension and
   :const:`WGL_CONTEXT_RESET_ISOLATION_BIT_ARB` in the
   `WGL_ARB_create_context_robustness`_ extension, and is ignored if these
   extensions are not available. This flag is intended to require OpenGL to
   make promises about what to do in the event of driver or hardware failure.

.. _`GLX_ARB_robustness_isolation`:
   https://www.opengl.org/registry/specs/ARB/glx_robustness_isolation.txt

.. _`WGL_ARB_create_context_robustness`:
   https://www.opengl.org/registry/specs/ARB/wgl_create_context_robustness.txt

OpenGL Profiles
---------------
These profile constants are used with SDL_GL_SetAttribute and
:const:`SDL_GL_CONTEXT_PROFILE_MASK`. Note that these profiles are mutually
exclusive and SDL_GL_SetAttribute accepts at most one of them. Setting
:const:`SDL_GL_CONTEXT_PROFILE_MASK` to 0 leaves the choice of profile up to
SDL. Should be used in conjunction with :const:`SDL_GL_CONTEXT_MAJOR_VERSION`
and :const:`SDL_GL_CONTEXT_MINOR_VERSION` as OpenGL profiles are defined
relative to a particular version of OpenGL. There is no way to distinguish
between the common and common lite profiles of OpenGL ES versions 1.0 and 1.1.

.. data:: SDL_GL_CONTEXT_PROFILE_CORE

   Core profile. Deprecated functions are disabled.

.. data:: SDL_GL_CONTEXT_PROFILE_COMPATIBILITY

   Compatibility profile. Deprecated functions are allowed.

.. data:: SDL_GL_CONTEXT_PROFILE_ES

   OpenGL ES context. Only a subset of base OpenGL functionality is allowed.
