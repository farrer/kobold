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

#ifndef _kobold_rwlock_h
#define _kobold_rwlock_h

#include "koboldconfig.h"
#include "mutex.h"

namespace Kobold
{

/*! Implements a simple Read-Write-Lock. Multiple readers are permited at the
 * same time. Only a writer is allowed. */
class ReadWriteLock
{
   public:
      /*! Constructor */
      ReadWriteLock();
      /*! Destructor */
      ~ReadWriteLock();

      /*! Lock for read-access */
      void lockForRead();
      /*! Unlock a read-access lock */
      void unlockForRead();

      /*! Lock for write access */
      void lockForWrite();
      /*! Unlock a write-access lock */
      void unlockForWrite();

   private:
      Mutex readMutex;   /**< Mutex for read access */
      Mutex writeMutex;  /**< Mutex for write access */
      int readers;       /**< Current number of readers */
};

}

#endif


