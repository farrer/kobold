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

#include "readwritelock.h"
#include <assert.h>
using namespace Kobold;

/**************************************************************************
 *                              Constructor                               *
 **************************************************************************/
ReadWriteLock::ReadWriteLock()
{
   readers = 0;
}

/**************************************************************************
 *                               Destructor                               *
 **************************************************************************/
ReadWriteLock::~ReadWriteLock()
{
   assert(readers == 0);
}

/**************************************************************************
 *                              lockForRead                               *
 **************************************************************************/
void ReadWriteLock::lockForRead()
{
   readMutex.lock();
   readers++;
   if(readers == 1)
   {
      /* first reader, must now allow any writer while there's 
       * someone reading */
      writeMutex.lock();
   }
   readMutex.unlock();
}

/**************************************************************************
 *                             unlockForRead                              *
 **************************************************************************/
void ReadWriteLock::unlockForRead()
{
   readMutex.lock();
   assert(readers > 0);
   readers--;
   if(readers == 0)
   {
      /* No more readers, an writer should be allowed. */
      writeMutex.unlock();
   }
   readMutex.unlock();
}

/**************************************************************************
 *                              lockForWrite                              *
 **************************************************************************/
void ReadWriteLock::lockForWrite()
{
   writeMutex.lock();
}

/**************************************************************************
 *                            unlockForWrite                              *
 **************************************************************************/
void ReadWriteLock::unlockForWrite()
{
   writeMutex.unlock();
}

