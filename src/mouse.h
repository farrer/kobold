/*
 Kobold - Multiplatform Game Utility Library
 Copyright (C) DNTeam <kobold@dnteam.org>
 
 This file is part of Kobold.
 
 Kobold is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Kobold is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with Kobold.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _kobold_mouse_h
#define _kobold_mouse_h

#include "platform.h"

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS &&\
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID

#include <SDL2/SDL.h>

namespace Kobold
{

#define MOUSE_MAX_BUTTONS    3

/*! A mouse controller class.*/
class Mouse
{
   public:
      /*! Mouse initialize */
      static void init();
      /*! Finish the use of mouse cursor*/
      static void finish();  

      /*! Update mouse position and state 
       * \note: should be called after SDL_PumEvents or similar. */
      static void update();

      /*! Update current mouse by events. Usually used in conjunction
       * with #update */
      static void updateByEvent(SDL_Event event);

      /*! \return current cursor X coordinate on screen */
      static int getX();
      /*! \return current cursor Y coordinate on screen */
      static int getY();
      /*! \return cursor relative to last X coordinate movement  */
      static int getRelativeX();
      /*! \return cursor relative to last Y coordinate movement  */
      static int getRelativeY();
      /*! \return current cursor wheel relative state from last check */
      static int getRelativeWheel();

      /*! Check if left button is pressed */
      static bool isLeftButtonPressed();
      /*! Check if middle button is pressed */
      static bool isMiddleButtonPressed();
      /*! Check if right button is pressed */
      static bool isRightButtonPressed();
      /*! \return if mouse button released on last check. */
      static bool checkButtonRelease(int buttonNumber);


   private:
      
      static Uint8 mButton;  /**< Current button states */
      static int mouseX;     /**< Current mouse X position */
      static int mouseY;     /**< Current mouse Y position */
      static int relMouseX;  /**< Relative mouse X move from last get */
      static int relMouseY;  /**< Relative mouse Y move from last get */
      static int mouseWheel; /**< Mouse Wheel relative state */
      
      /*! Release state for each button */
      static bool mouseButtonReleased[MOUSE_MAX_BUTTONS];

};

}

#endif

#endif

