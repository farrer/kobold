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

#include "mutex.h"
#include "log.h"
using namespace Kobold;

/**************************************************************************
 *                               Constructor                              *
 **************************************************************************/
Mutex::Mutex()
{
#if KOBOLD_HAS_SDL == 1
   mutex = SDL_CreateMutex();
#else
   pthread_mutexattr_init(&attr);
   pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

   pthread_mutex_init(&mutex, &attr);
#endif
}

/**************************************************************************
 *                                Destructor                              *
 **************************************************************************/
Mutex::~Mutex()
{
#if KOBOLD_HAS_SDL == 1
   SDL_DestroyMutex(mutex);
#else
   pthread_mutex_destroy(&mutex);
   pthread_mutexattr_destroy(&attr);
#endif
}

/**************************************************************************
 *                                   lock                                 *
 **************************************************************************/
void Mutex::lock()
{
#if KOBOLD_HAS_SDL == 1
   if(SDL_LockMutex(mutex) != 0)
   {
      Log::add(LOG_LEVEL_ERROR, "Error: Couldn't lock mutex!");
   }
#else
   pthread_mutex_lock(&mutex);
#endif
}

/**************************************************************************
 *                                  unlock                                *
 **************************************************************************/
void Mutex::unlock()
{
#if KOBOLD_HAS_SDL == 1
   SDL_UnlockMutex(mutex);
#else
   pthread_mutex_unlock(&mutex);
#endif

}


