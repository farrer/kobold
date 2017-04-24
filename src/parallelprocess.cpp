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

#include "parallelprocess.h"
#include <timer.h>

using namespace Kobold;

/****************************************************************
 *                     parallelProcessThreadProc                *
 ****************************************************************/
void* parallelProcessThreadProc(void* arg)
{
   ParallelProcess* process = (ParallelProcess*) arg;
   
   unsigned int delayTime = process->getSleepTime();
   
   while(process->isRunning() && (process->step()))
   {
      if(delayTime != 0)
      {
         Kobold::timer_Delay(delayTime);
      }
   }
   
   process->threadEnded();
   
   return NULL;
}

/****************************************************************
 *                          Constructor                         *
 ****************************************************************/
ParallelProcess::ParallelProcess()
{
   threadRunning = false;
   pthread_mutex_init(&threadMutex, NULL);
}

/****************************************************************
 *                           Destructor                         *
 ****************************************************************/
ParallelProcess::~ParallelProcess()
{
   if(isRunning())
   {
      endThread();
   }
   pthread_mutex_destroy(&threadMutex);
}

/***********************************************************************
 *                               isRunning                             *
 ***********************************************************************/
bool ParallelProcess::isRunning()
{
   bool res;
   
   pthread_mutex_lock(&threadMutex);
   res = threadRunning;
   pthread_mutex_unlock(&threadMutex);
   
   return res;
}

/***********************************************************************
 *                              createThread                           *
 ***********************************************************************/
void ParallelProcess::createThread()
{
   if(isRunning())
   {
      endThread();
   }
   pthread_mutex_lock(&threadMutex);
   
   pthread_create(&thread, NULL, parallelProcessThreadProc, (void*)this);
   threadRunning = true;
   
   pthread_mutex_unlock(&threadMutex);
}

/***********************************************************************
 *                               endThread                             *
 ***********************************************************************/
void ParallelProcess::endThread()
{
   pthread_mutex_lock(&threadMutex);
   if(threadRunning)
   {
      threadRunning = false;
      pthread_mutex_unlock(&threadMutex);
      pthread_join(thread, NULL);
   }
   else
   {
      pthread_mutex_unlock(&threadMutex);
   }
}

/***********************************************************************
 *                             threadEnded                             *
 ***********************************************************************/
void ParallelProcess::threadEnded()
{
   pthread_mutex_lock(&threadMutex);
   threadRunning = false;
   pthread_mutex_unlock(&threadMutex);
}

