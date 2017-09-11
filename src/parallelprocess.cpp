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
#include "log.h"
#include <timer.h>

using namespace Kobold;

/****************************************************************
 *                     parallelProcessThreadProc                *
 ****************************************************************/
#if KOBOLD_HAS_SDL
int parallelProcessThreadProc(void* arg)
#else
void* parallelProcessThreadProc(void* arg)
#endif
{
   ParallelProcess* process = (ParallelProcess*) arg;
   
   unsigned int freqTime = process->getExecutionFrequency();
   Kobold::Timer timer;
   timer.reset();
   unsigned long timeElapsed;

   bool endedByStep = false;
   
   while(process->isRunning() && (!endedByStep))
   {
      endedByStep = !process->step();
      timeElapsed = timer.getMilliseconds();
      if((timeElapsed < freqTime) && (!endedByStep))
      {
         /* Must sleep until elapsed the remaining time for next step
          * call. */
         Kobold::timer_Delay(freqTime - timeElapsed);
      }
      timer.reset();
   }

   process->threadEnded(endedByStep);
   
#if KOBOLD_HAS_SDL
   return 0;
#else
   return NULL;
#endif
}

/****************************************************************
 *                          Constructor                         *
 ****************************************************************/
ParallelProcess::ParallelProcess()
{
   threadRunning = false;
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
}

/***********************************************************************
 *                               isRunning                             *
 ***********************************************************************/
bool ParallelProcess::isRunning()
{
   bool res;
   
   mutex.lock();
   res = threadRunning;
   mutex.unlock();
   
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
   mutex.lock();

#if KOBOLD_HAS_SDL
   thread = SDL_CreateThread(parallelProcessThreadProc, "koboldParallel", 
         (void*)this);
#else
   pthread_create(&thread, NULL, parallelProcessThreadProc, (void*)this);
#endif
   threadRunning = true;
  
   mutex.unlock();
}

/***********************************************************************
 *                               endThread                             *
 ***********************************************************************/
void ParallelProcess::endThread()
{
   mutex.lock();
   if(threadRunning)
   {
      threadRunning = false;
   }
   mutex.unlock();
#if KOBOLD_HAS_SDL
   int ret=0;
   SDL_WaitThread(thread, &ret);
#else
   pthread_join(thread, NULL);
#endif
}

/***********************************************************************
 *                             threadEnded                             *
 ***********************************************************************/
void ParallelProcess::threadEnded(bool endedByStep)
{
   mutex.lock();
   if(threadRunning)
   {
      threadRunning = false;
      if(endedByStep)
      {
#if KOBOLD_HAS_SDL
         SDL_DetachThread(thread);
#else
         pthread_detach(thread);
#endif
      }
   }
   mutex.unlock();
}

