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

#ifndef _kobold_ogre_log_h
#define _kobold_ogre_log_h

#include "../log.h"
#include <OGRE/OgreLog.h>

namespace Kobold
{

   /*! Log implementation, using Ogre::Log as default output */
   class OgreLog : public BaseLog
   {
      public:
         OgreLog();
         virtual ~OgreLog();
         /*! Define log level to use
          * \param level new log level to use */
         void setLogLevel(const LogLevel& level) override;
         /*! Add a message to log, at default normal level */
         void add(const Kobold::String& message) override;

      private:
         /*! Convert Kobold log level to ogre's */
         const Ogre::LogMessageLevel getLevel(const LogLevel& level);
         const Ogre::LoggingLevel getLogLevel(const LogLevel& level);
   };

}

#endif


