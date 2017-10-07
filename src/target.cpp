/*
 Kobold - Multiplatform Game Utility Library
 Copyright (C) DNTeam <goblin@dnteam.org>
 
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

#include "target.h"

using namespace Kobold;


/***********************************************************************
 *                              Constructor                            *
 ***********************************************************************/
Target::Target()
{
   current = 0.0f;
   vTarget = 0.0f;
   delta = 0.0f;
   lastDelta = 0.0f;

   nUpdate = false;
}

/***********************************************************************
 *                               Destructor                            *
 ***********************************************************************/
Target::~Target()
{
}

/***********************************************************************
 *                              getTarget                              *
 ***********************************************************************/
const float Target::getTarget() const
{
   if(nUpdate) 
   {
      return vTarget;
   }
   return current;
}

/***********************************************************************
 *                            setCurrent                               *
 ***********************************************************************/
void Target::setCurrent(float v)
{
   current  = v;
   nUpdate = false;
}

/***********************************************************************
 *                              setTarget                              *
 ***********************************************************************/
void Target::setTarget(float t, int nSteps)
{
   /* Define Target and calculate delta */
   vTarget = t;
   delta = (vTarget - current) / float(nSteps);
   nUpdate = true;
}

/***********************************************************************
 *                              setTarget                              *
 ***********************************************************************/
void Target::setTargetAndVelocity(float t, float vel)
{
   /* Define Target and delta to the desired values */
   vTarget = t;
   delta = vel;
   nUpdate = true;

   /* Verify delta signal */
   if(  ( (vTarget < current) && (delta > 0) ) ||
        ( (vTarget > current) && (delta < 0) ) )
   {
      delta *= -1;
   }
}

/***********************************************************************
 *                               update                                *
 ***********************************************************************/
void Target::update()
{
   if(nUpdate)
   {
      /* Verify if reached the Target */
      if( ( (delta > 0) && ((current+delta) >= vTarget) ) ||
          ( (delta < 0) && ((current+delta) <= vTarget) ) )
      {
         /* At Target, done! */
         lastDelta = vTarget - current;
         current = vTarget;
         nUpdate = false;
         return;
      }
      else if(delta == 0)
      {
         nUpdate = false;
         return;
      }

      /* Update value */
      current += delta;
      lastDelta = delta;
   }
   else
   {
      lastDelta = 0.0f;
   }
}


