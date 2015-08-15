Rectangle Functions
===================
.. currentmodule:: csdl2

.. class:: SDL_Point(x: int =0, y: int =0)

   A 2d point.

   .. attribute:: x

      The x location of the point.

   .. attribute:: y

      The y location of the point.

.. class:: SDL_Rect(x: int =0, y: int =0, w: int =0, h: int =0)

   A 2d rectangle with its origin at the upper left.

   .. attribute:: x

      The x location of the rectangle's upper left corner.

   .. attribute:: y

      The y location of the rectangle's upper left corner.

   .. attribute:: w

      The width of the rectangle.

   .. attribute:: h

      The height of the rectangle.

.. function:: SDL_HasIntersection(A: SDL_Rect, B: SDL_Rect) -> bool

   Determines if two rectangles intersect.

   :param A: First rectangle.
   :type A: :class:`SDL_Rect` or None
   :param B: Second rectangle.
   :type B: :class:`SDL_Rect` or None
   :returns: True if there is an intersection, False otherwise. If `A` and/or
             `B` are None, the function will return False.
