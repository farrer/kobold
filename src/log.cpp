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
using namespace Kobold;

/************************************************************************
 *                               setLogLevel                            *
 ************************************************************************/
void Log::setLogLevel(Log::LogLevel level)
{
   Log::level = level;
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
      vprintf(format, arg);
      va_end(arg);

      printf("\n");
   }
}

/************************************************************************
 *                              static memebers                         *
 ************************************************************************/
Log::LogLevel Log::level = LOG_LEVEL_NORMAL;

