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

#ifndef _kobold_string_h
#define _kobold_string_h

#include "koboldconfig.h"

#if KOBOLD_HAS_OGRE == 1
   #include <OGRE/OgreString.h>
#else
   #include <string>
   #include <algorithm>
#endif

namespace Kobold
{
#if KOBOLD_HAS_OGRE == 1
   typedef Ogre::String String;
#else
   typedef std::string String;
#endif
   
   class StringUtil
   {
      public:
         /*! \return copy of s with all characters orig replaced to dest */
         static String replaceAll(String s, char orig, char dest);
         /*! \return copy of s with all characters lowercased */
         static String toLowerCase(String s);

         /*! \return if s ends with character c */
         static bool endsWith(String s, char c);
      private:
         StringUtil(){};
   };

};

#endif

