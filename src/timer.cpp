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

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS
   #include <SDL2/SDL.h>
#else
   #include "errno.h"
   #include <sys/time.h>
   #include <sys/select.h>
#endif

namespace Kobold
{

static struct timeval ticks_start;
static bool started_ticks = false;

/***********************************************************************
 *                           timer_getTicks()                          *
 ***********************************************************************/
unsigned long timer_getTicks()
{
#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS
   return SDL_GetTicks();
#else
   if(!started_ticks)
   {
      started_ticks = true;
      gettimeofday(&ticks_start, NULL);
      return 0;
   }

   unsigned long ticks;
   struct timeval now;
   gettimeofday(&now, NULL);
   ticks = (now.tv_sec - ticks_start.tv_sec) * 1000 + 
           (now.tv_usec - ticks_start.tv_usec) / 1000;
   return ticks;
#endif
}

/***********************************************************************
 *                              timer_Delay                            *
 ***********************************************************************/
void timer_Delay(unsigned int ms)
{
#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS
   SDL_Delay(ms);
#else
   int was_error;
   struct timeval tv;
   unsigned long then, now, elapsed;

   /* Set the timeout interval */
   then = timer_getTicks();

   do 
   {
      errno = 0;

      /* Calculate the time interval left (in case of interrupt) */
      now = timer_getTicks();
      elapsed = (now-then);
      then = now;
      if(elapsed >= ms) 
      {
         break;
      }
      ms -= elapsed;
      tv.tv_sec = ms/1000;
      tv.tv_usec = (ms%1000)*1000;

      was_error = select(0, NULL, NULL, NULL, &tv);
   } while(was_error && (errno == EINTR));
#endif
}

   
/***********************************************************************
 *                             Constructor                             *
 ***********************************************************************/
Timer::Timer()
{
   ticks = timer_getTicks();
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
      acumulated += timer_getTicks() - ticks;
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
   ticks = timer_getTicks();
}

/***********************************************************************
 *                                reset                                *
 ***********************************************************************/
void Timer::reset()
{
   paused = false;
   acumulated = 0;
   ticks = timer_getTicks();
}

/***********************************************************************
 *                                reset                                *
 ***********************************************************************/
void Timer::reset(unsigned long ms)
{
   paused = false;
   acumulated = ms;
   ticks = timer_getTicks();
}

/***********************************************************************
 *                             getMilliseconds                         *
 ***********************************************************************/
unsigned long Timer::getMilliseconds()
{
   unsigned long passed = timer_getTicks() - ticks;

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
