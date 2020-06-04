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

namespace Kobold
{
   /*! The log level */
   enum LogLevel
   {
      LOG_LEVEL_DEBUG,
      LOG_LEVEL_NORMAL,
      LOG_LEVEL_ERROR
   };

   /*! Abstract class for log implementations */
   class BaseLog
   {
      public:
         BaseLog();
         virtual ~BaseLog();
         /*! Define log level to use
          * \param level new log level to use */
         virtual void setLogLevel(const LogLevel& level);
         /*! \return current log level */
         const LogLevel& getLogLevel();
         /*! Add a message to log, at default normal level */
         virtual void add(const Kobold::String& message) = 0;
         /*! \return if should add line break after the message */
         virtual bool shouldAddLineBreak() = 0;
      protected:
         LogLevel level; /**< Current log level */
   };

   /*! Default log implementation, putting output to std::out */
   class DefaultLog : public BaseLog
   {
      public:
         DefaultLog();
         virtual ~DefaultLog();
         /*! Add a message to log, at default normal level */
         void add(const Kobold::String& message) override;
         bool shouldAddLineBreak() override { return true; };
   };


   /*! The Log static class, using the desired log as output. */
   class Log
   {
      public:
         /*! Init the log system.
          * \param log pointer to the log to use. */
         static void init(BaseLog* log);

         /*! Define log level to use
          * \param level new log level to use */
         static void setLogLevel(const LogLevel& level);
         /*! Add a message to log, at default normal level */
         static void add(const Kobold::String& message);
         /*! Add a formated message to log */
         static void add(const LogLevel& level, const char* format, ...);

      private:
         Log(){};
         
         static BaseLog* log; /**< log to use */
   };
}

#endif

