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

#include "mouse.h"
using namespace Kobold;


#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS &&\
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID

/*****************************************************************
 *                         Constructor                           *
 *****************************************************************/
void Mouse::init()
{
}

/*****************************************************************
 *                          Destructor                           *
 *****************************************************************/
void Mouse::finish()
{
}

/*****************************************************************
 *                           update                              *
 *****************************************************************/
void Mouse::update()
{
   /* Get mouse state */
   relMouseX = mouseX;
   relMouseY = mouseY;
   mButton = SDL_GetMouseState(&mouseX, &mouseY);
   relMouseX -= mouseX;
   relMouseY -= mouseY;

   /* Clear event related states */
   mouseWheel = 0;
   for(int i = 0; i < MOUSE_MAX_BUTTONS; i++)
   {
      mouseButtonReleased[i] = false;
   }
}

/*****************************************************************
 *                         updateByEvent                         *
 *****************************************************************/
void Mouse::updateByEvent(SDL_Event event)
{
   if(event.type == SDL_MOUSEWHEEL)
   {
      /* Add or dec the amount moved */
      mouseWheel += event.wheel.y;
   }
   else if(event.type == SDL_MOUSEBUTTONUP)
   {
      if(event.button.button <= MOUSE_MAX_BUTTONS)
      {
         mouseButtonReleased[event.button.button - 1] = true;
      }
   }
}

/*****************************************************************
 *                             getX                              *
 *****************************************************************/
int Mouse::getX()
{
   return mouseX;
}

/*****************************************************************
 *                             getX                              *
 *****************************************************************/
int Mouse::getY()
{
   return mouseY;
}

/*****************************************************************
 *                             getX                              *
 *****************************************************************/
int Mouse::getRelativeX()
{
   return relMouseX;
}

/*****************************************************************
 *                             getX                              *
 *****************************************************************/
int Mouse::getRelativeY()
{
   return relMouseY;
}

/*****************************************************************
 *                        getRelativeWheel                       *
 *****************************************************************/
int Mouse::getRelativeWheel()
{
   return mouseWheel;
}

/*****************************************************************
 *                       isLeftButtonPressed                     *
 *****************************************************************/
bool Mouse::isLeftButtonPressed()
{
   return mButton & SDL_BUTTON(1);
}

/*****************************************************************
 *                      isMiddleButtonPressed                    *
 *****************************************************************/
bool Mouse::isMiddleButtonPressed()
{
   return mButton & SDL_BUTTON(2);
}

/*****************************************************************
 *                      isRightButtonPressed                     *
 *****************************************************************/
bool Mouse::isRightButtonPressed()
{
   return mButton & SDL_BUTTON(3);
}

/*****************************************************************
 *                       checkButtonRelease                      *
 *****************************************************************/
bool Mouse::checkButtonRelease(int buttonNumber)
{
   if(buttonNumber < MOUSE_MAX_BUTTONS)
   {
      return mouseButtonReleased[buttonNumber];
   }

   return false;
}

/*****************************************************************
 *                             Members                           *
 *****************************************************************/
Uint8 Mouse::mButton;
int Mouse::mouseX = -1;
int Mouse::mouseY = -1;
int Mouse::relMouseX = 0;
int Mouse::relMouseY = 0;
int Mouse::mouseWheel = 0;
bool Mouse::mouseButtonReleased[MOUSE_MAX_BUTTONS];



#endif

