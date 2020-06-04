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

#include "ogrefilereader.h"
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreException.h>


namespace Kobold
{

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
OgreFileReader::OgreFileReader() 
{
}
 
/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
OgreFileReader::~OgreFileReader() 
{
}

/***********************************************************************
 *                                open                                 *
 ***********************************************************************/
bool OgreFileReader::open(const Kobold::String& fileName) 
{
   try
   {
      fileData = Ogre::ResourceGroupManager::getSingleton().openResource(
            fileName);
   }
   catch(const Ogre::FileNotFoundException&)
   {
      return false;
   }

   return true;
}

/***********************************************************************
 *                             getSize                                 *
 ***********************************************************************/
size_t OgreFileReader::getSize() 
{
   return fileData->size();
}

/***********************************************************************
 *                                tell                                 *
 ***********************************************************************/
size_t OgreFileReader::tell()
{
   return fileData->tell();
}

/***********************************************************************
 *                                seek                                 *
 ***********************************************************************/
bool OgreFileReader::seek(size_t pos)
{
   fileData->seek(pos);
   return true;
}

/***********************************************************************
 *                                eof                                  *
 ***********************************************************************/
bool OgreFileReader::eof() 
{
   return fileData->eof();
}

/***********************************************************************
 *                               getLine                               *
 ***********************************************************************/
Kobold::String OgreFileReader::getLine() 
{
   return fileData->getLine();
}

/***********************************************************************
 *                              read                                   *
 ***********************************************************************/
bool OgreFileReader::read(char* s, size_t n)
{
   return fileData->read(s, n) != 0;
}


/***********************************************************************
 *                                close                                *
 ***********************************************************************/
void OgreFileReader::close() 
{
   fileData->close();
}


}

