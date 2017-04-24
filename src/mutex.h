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

#ifndef _kobold_mutex_h
#define _kobold_mutex_h

#include "koboldconfig.h"

#if KOBOLD_HAS_SDL == 1
   #include <SDL2/SDL.h>
#else
   #include <pthread.h>
#endif

namespace Kobold
{

/*! The platform/implementation independent Mutex wrapper. */
class Mutex
{
   public:
      /*! Mutex contructor */
      Mutex();
      /*! Mutex destructor */
      ~Mutex();

      /*! Lock the mutex, waiting if already locked */
      void lock();
      /*! Unlock the locked mutex */
      void unlock();

   private:
#if KOBOLD_HAS_SDL == 1
      SDL_mutex* mutex;      /**< Mutex implemented by SDL */
#else
      pthread_mutex_t mutex; /**< Mutex implemented by Posix Thread */
#endif

};

}

#endif

