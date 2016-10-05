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

#ifndef _kobold_log_h
#define _kobold_log_h

#include "kstring.h"
#include "koboldconfig.h"

#if KOBOLD_HAS_OGRE == 1
   #include <OGRE/OgreLog.h>
#endif

namespace Kobold
{
   /*! The Log abstractor class. Will use Ogre::Log when using OGRE,
    * otherwise, just outputs to std::out. */
   class Log
   {
      public:
         enum LogLevel
         {
            LOG_LEVEL_DEBUG,
            LOG_LEVEL_NORMAL,
            LOG_LEVEL_ERROR
         };

         /*! Init the log system.
          * \param useOgre if should use OgreLog if available */
         static void init(bool useOgre);

         /*! Define log level to use
          * \param level new log level to use */
         static void setLogLevel(LogLevel level);
         /*! Add a message to log, at default normal level */
         static void add(Kobold::String message);
         /*! Add a formated message to log */
         static void add(LogLevel level, const char* format, ...);

      private:

#if KOBOLD_HAS_OGRE == 1
         /*! Convert Kobold log level to ogre's */
         static Ogre::LogMessageLevel getLevel(LogLevel level);
         static Ogre::LoggingLevel getLogLevel(LogLevel level);
#endif

         Log(){};
         
         static LogLevel level; /**< Current log level */
         static bool useOgre;   /**< If should use ogre log */
   };
}

#endif

