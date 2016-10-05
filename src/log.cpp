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

#include "log.h"
#include <stdio.h>
#include <stdarg.h>


#if KOBOLD_HAS_OGRE == 1
   #include <OGRE/OgreLogManager.h>
#endif

using namespace Kobold;

/************************************************************************
 *                                  init                                *
 ************************************************************************/
void Log::init(bool useOgre)
{
   Log::useOgre = useOgre;
}

/************************************************************************
 *                               setLogLevel                            *
 ************************************************************************/
void Log::setLogLevel(Log::LogLevel level)
{
   Log::level = level;
#if KOBOLD_HAS_OGRE == 1
   if(useOgre)
   {
      Ogre::LogManager::getSingleton().getDefaultLog()->setLogDetail(
         getLogLevel(level));
   }
#endif
}

/************************************************************************
 *                                   add                                *
 ************************************************************************/
void Log::add(Kobold::String message)
{
   add(LOG_LEVEL_NORMAL, message.c_str());
}

/************************************************************************
 *                                   add                                *
 ************************************************************************/
void Log::add(Log::LogLevel level, const char* format, ...)
{
   if(level >= Log::level)
   {
      /* Write the error message */
      va_list arg;

      va_start(arg, format);
#if KOBOLD_HAS_OGRE == 1
      if(useOgre)
      {
         /* Print message to buffer */
         char buf[512];
         vsnprintf(&buf[0], 512, format, arg);

         /* Define message level */
         Ogre::LogMessageLevel messageLevel = getLevel(level);

         Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(buf, 
               messageLevel);
      } 
      else
      {
#endif
         /* Direct print message to std::out */
         vprintf(format, arg);
#if KOBOLD_HAS_OGRE == 1
      }
#endif
      va_end(arg);

      if(!useOgre)
      {
         printf("\n");
      }
   }
}

#if KOBOLD_HAS_OGRE == 1
/************************************************************************
 *                                getLevel                              *
 ************************************************************************/
Ogre::LogMessageLevel Log::getLevel(LogLevel level)
{
   switch(level)
   {
      case LOG_LEVEL_DEBUG:
         return Ogre::LML_TRIVIAL;
      case LOG_LEVEL_ERROR:
         return Ogre::LML_CRITICAL;
      default:
      case LOG_LEVEL_NORMAL:
         return Ogre::LML_NORMAL;
   }

}

/************************************************************************
 *                                getLevel                              *
 ************************************************************************/
Ogre::LoggingLevel Log::getLogLevel(LogLevel level)
{
   switch(level)
   {
      case LOG_LEVEL_DEBUG:
         return Ogre::LL_BOREME;
      case LOG_LEVEL_ERROR:
         return Ogre::LL_LOW;
      default:
      case LOG_LEVEL_NORMAL:
         return Ogre::LL_NORMAL;
   }

}
#endif

/************************************************************************
 *                              static memebers                         *
 ************************************************************************/
Log::LogLevel Log::level = LOG_LEVEL_NORMAL;
bool Log::useOgre = false;

