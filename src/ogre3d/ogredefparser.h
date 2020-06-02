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

#ifndef _kobold_ogre_def_parser_h
#define _kobold_ogre_def_parser_h

#include "../defparser.h"

namespace Kobold 
{

class OgreDefParser : public DefParser 
{
   public:
      OgreDefParser();
      virtual ~OgreDefParser();
      

      bool load(const Kobold::String& fileName, bool stringFile) override;

      /*! Load File. Could be called multiple times, for distinct file load
       * with the same structure. Each time it's called, the old structure
       * is freed and a new one is created with all information loaded. 
       * \param fileName -> file name to load
       * \param fullPath -> when using fullPath in fileName
       * \param stringFile -> true to load an "string a" = "string b"
       *                       like file (i18n is one of this type).
       * \note -> fullPath == false will use OgreResources as Path */
      bool load(const Kobold::String& fileName, bool fullPath,
                bool stringFile);
};

}

#endif

