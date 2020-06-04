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

#include "ogrelog.h"
#include <OGRE/OgreLogManager.h>

namespace Kobold 
{

/************************************************************************
 *                              constructor                             *
 ************************************************************************/
OgreLog::OgreLog() 
{
}

/************************************************************************
 *                               destructor                             *
 ************************************************************************/
OgreLog::~OgreLog() 
{
}

/************************************************************************
 *                              setLogLevel                             *
 ************************************************************************/
void OgreLog::setLogLevel(const LogLevel& level)
{
   Ogre::LogManager::getSingleton().getDefaultLog()->setLogDetail(
         getLogLevel(level));
}

/************************************************************************
 *                                 add                                  *
 ************************************************************************/
void OgreLog::add(const Kobold::String& message)
{
   /* Define message level */
   Ogre::LogMessageLevel messageLevel = getLevel(level);

   Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(
         message.c_str(), messageLevel);
}

/************************************************************************
 *                                getLevel                              *
 ************************************************************************/
const Ogre::LogMessageLevel OgreLog::getLevel(const LogLevel& level)
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
const Ogre::LoggingLevel OgreLog::getLogLevel(const LogLevel& level)
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


}

