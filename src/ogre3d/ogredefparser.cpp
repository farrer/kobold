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

#include "ogredefparser.h"
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreException.h>

namespace Kobold {

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                            OgreDefStream                              //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
OgreDefStream::OgreDefStream() 
{
}
 
/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
OgreDefStream::~OgreDefStream() 
{
}

/***********************************************************************
 *                                open                                 *
 ***********************************************************************/
bool OgreDefStream::open(const Kobold::String& fileName) 
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
 *                                eof                                  *
 ***********************************************************************/
bool OgreDefStream::eof() 
{
   return fileData->eof();
}

/***********************************************************************
 *                               getLine                               *
 ***********************************************************************/
Kobold::String OgreDefStream::getLine() 
{
   return fileData->getLine();
}

/***********************************************************************
 *                                close                                *
 ***********************************************************************/
void OgreDefStream::close() 
{
   fileData->close();
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                            OgreDefParser                              //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
OgreDefParser::OgreDefParser() 
{
}
 
/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
OgreDefParser::~OgreDefParser() 
{
}

/***********************************************************************
 *                                load                                 *
 ***********************************************************************/
bool OgreDefParser::load(const Kobold::String& fileName, bool fullPath,
      bool stringFile) 
{
   if(fullPath) 
   {
      DefStreamStd stream;
      return DefParser::load(fileName, stringFile, stream);
   }
   else 
   {
      OgreDefStream stream;
      return DefParser::load(fileName, stringFile, stream);
   }
}

}

