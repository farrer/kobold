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

#ifndef _kobold_parallelprocess_h
#define _kobold_parallelprocess_h

#include "koboldconfig.h"
#include <pthread.h>

namespace Kobold
{

/*! Abstract class used for creation of parallel processing classes.
 * Basically, at each step */
class ParallelProcess
{
   public:
   
      /*! Constructor */
      ParallelProcess();
   
      /*! Destructor */
      virtual ~ParallelProcess();
   
      /*! Do the step of the parallel processing 
       * @return true when continue to run, false to stop. */
      virtual bool step()=0;
   
      /*! Get the ammount of time (in ms) to sleep after each step */
      virtual unsigned int getSleepTime()=0;
   
      /*! Create a thread with the server loop */
      void createThread();
   
      /*! End the thread with the server loop */
      void endThread();
   
      /*! If the server is running on a separate thread. */
      bool isRunning();
   
      /* Tell that the thread ended.
       * \note only usefull inner the server thread. */
      void threadEnded();
   
   private:
   
      bool threadRunning;                 /**< if is running at a thread */
      pthread_t thread;                   /**< thread */
      pthread_mutex_t threadMutex; /**< Mutex for thread running check */
   
};
   
}

#endif
