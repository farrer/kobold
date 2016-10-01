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

#ifndef _kobold_timer_h
#define _kobold_timer_h

#include "koboldconfig.h"

namespace Kobold
{

/*! A delay (sleep) function. Sleep for an amount of time.
 * @param ms milliseconds to wait */
void timer_Delay(unsigned int ms);

/*! The timer class */
class Timer
{
   public:
      /*! Constructor */
      Timer();
      /*! Destructor */
      ~Timer();

      /*! Pause the timer */
      void pause();

      /*! Resume the timer */
      void resume();

      /*! Reset the timer */
      void reset();

      /*! Reset the timer, setting its initial value to ms
       * \ms -> milliseconds on accumulated. */
      void reset(unsigned long ms);
   
      /*! Verify if the timer is currently paused. */
      bool isPaused();

      /*! Get the number of milliseconds
       * \return milliseconds passed */
      unsigned long getMilliseconds();

   protected:
      unsigned long ticks; /**< started ticks */

      unsigned long acumulated;  /**< acumulated milliseconds */
      bool paused;               /**< If timer is paused or not */
};

}

#endif

