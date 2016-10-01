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

#include "timer.h"
#include "platform.h"

#include <SDL2/SDL.h>

namespace Kobold
{

/***********************************************************************
 *                              timer_Delay                            *
 ***********************************************************************/
void timer_Delay(unsigned int ms)
{
   SDL_Delay(ms);
}
   
/***********************************************************************
 *                             Constructor                             *
 ***********************************************************************/
Timer::Timer()
{
   ticks = SDL_GetTicks();
   acumulated = 0;
   paused = false;
}

/***********************************************************************
 *                              Destructor                             *
 ***********************************************************************/
Timer::~Timer()
{
}

/***********************************************************************
 *                                 pause                               *
 ***********************************************************************/
void Timer::pause()
{
   if(!paused)
   {
      paused = true;
      acumulated += SDL_GetTicks() - ticks;
   }
}
  
/***********************************************************************
 *                               isPaused                              *
 ***********************************************************************/
bool Timer::isPaused()
{
   return paused;
}

/***********************************************************************
 *                               resume                                *
 ***********************************************************************/
void Timer::resume()
{
   paused = false;
   ticks = SDL_GetTicks();
}

/***********************************************************************
 *                                reset                                *
 ***********************************************************************/
void Timer::reset()
{
   paused = false;
   acumulated = 0;
   ticks = SDL_GetTicks();
}

/***********************************************************************
 *                                reset                                *
 ***********************************************************************/
void Timer::reset(unsigned long ms)
{
   paused = false;
   acumulated = ms;
   ticks = SDL_GetTicks();
}

/***********************************************************************
 *                             getMilliseconds                         *
 ***********************************************************************/
unsigned long Timer::getMilliseconds()
{
   unsigned long passed = SDL_GetTicks() - ticks;

   if(!paused)
   {
      return acumulated + passed;
   }
   else
   {
      return acumulated;
   }
}

}
