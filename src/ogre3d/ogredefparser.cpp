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
#include "ogrefilereader.h"

namespace Kobold {

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
      DiskFileReader stream;
      return DefParser::load(fileName, stringFile, stream);
   }
   else 
   {
      OgreFileReader stream;
      return DefParser::load(fileName, stringFile, stream);
   }
}

}

