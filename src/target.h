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

#ifndef _kobold_target_h
#define _kobold_target_h

namespace Kobold
{

#define TARGET_DEFAULT_STEPS  10

/*! The Target class represents a single float value that
 * will modify to a Target value with some updates. */
class Target
{
   public:
      /*! Constructor */
      Target();
      /*! Destructor */
      ~Target();

      /*! Set the Target */
      void setTarget(float t, int nSteps=TARGET_DEFAULT_STEPS);
      
      /*! Set Target and update velocity */
      void setTargetAndVelocity(float t, float vel);

      /*! Set the current value */
      void setCurrent(float v);

      /*! Update values */
      void update();

      /*! Verify if Target needs to update or not */
      const bool needUpdate() const { return nUpdate; };
      /*! Get the current value */
      const float getValue() const { return current; };

      /*! Get the last delta used to update Target */
      const float getLastDelta() const { return lastDelta; };

      /*! Get current target, if any, or value if none */
      const float getTarget() const;

   protected:
      float current;   /**< The current value */
      float vTarget;   /**< The Target value */
      float delta;     /**< The delta to change Target */

      float lastDelta; /**< last delta used */

      bool nUpdate;      /**< Flag if value need to be updated or not */
};

}

#endif

