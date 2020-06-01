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
#include <iostream>
#include <stdarg.h>

using namespace Kobold;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                               BaseLog                                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/************************************************************************
 *                              constructor                             *
 ************************************************************************/
BaseLog::BaseLog() 
{
   level = LOG_LEVEL_NORMAL;
}

/************************************************************************
 *                               destructor                             *
 ************************************************************************/
BaseLog::~BaseLog() 
{
}

/************************************************************************
 *                              setLogLevel                             *
 ************************************************************************/
void BaseLog::setLogLevel(const LogLevel& level)
{
   this->level = level;
}

/************************************************************************
 *                              getLogLevel                             *
 ************************************************************************/
const LogLevel& BaseLog::getLogLevel() 
{
   return this->level;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                             DefaultLog                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/************************************************************************
 *                              constructor                             *
 ************************************************************************/
DefaultLog::DefaultLog() 
{
}

/************************************************************************
 *                               destructor                             *
 ************************************************************************/
DefaultLog::~DefaultLog() 
{
}

/************************************************************************
 *                                 add                                  *
 ************************************************************************/
void DefaultLog::add(const Kobold::String& message)
{
   std::cout << message;
}


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                 Log                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


/************************************************************************
 *                                  init                                *
 ************************************************************************/
void Log::init(BaseLog* log)
{
   Log::log = log;
}

/************************************************************************
 *                               setLogLevel                            *
 ************************************************************************/
void Log::setLogLevel(const LogLevel& level)
{
   log->setLogLevel(level);
}

/************************************************************************
 *                                   add                                *
 ************************************************************************/
void Log::add(const Kobold::String& message)
{
   if(log->getLogLevel() <= LOG_LEVEL_NORMAL)
   {
      log->add(message + "\n");
   }
}

/************************************************************************
 *                                   add                                *
 ************************************************************************/
void Log::add(const LogLevel& level, const char* format, ...)
{
   if(level >= log->getLogLevel())
   {
      /* Write the error message */
      va_list arg;

      va_start(arg, format);
      
      /* Print message to buffer */
      char buf[512];
      vsnprintf(&buf[0], 512, format, arg);

      log->add(buf);

      va_end(arg);

      log->add("\n");
   }
}

/************************************************************************
 *                              static memebers                         *
 ************************************************************************/
BaseLog* Log::log = NULL;

