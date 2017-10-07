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

#include "kstring.h"

#if KOBOLD_HAS_OGRE == 1
   #include <OGRE/OgreStringConverter.h>
#else
   #include <sstream>
   #include <string>
#endif

using namespace Kobold;

/************************************************************************
 *                              replaceAll                              *
 ************************************************************************/
String StringUtil::replaceAll(const String& s, char orig, char dest)
{
#if KOBOLD_HAS_OGRE == 1
   char o[2];
   o[0] = orig;
   o[1] = '\0';
   char d[2];
   d[0] = dest;
   d[1] = '\0';
   return Ogre::StringUtil::replaceAll(s, o, d);
#else
   String ret = s;
   std::replace(ret.begin(), ret.end(), orig, dest);
   return ret;
#endif
}

/************************************************************************
 *                              toLowerCase                             *
 ************************************************************************/
String StringUtil::toLowerCase(const String& s)
{
#if KOBOLD_HAS_OGRE == 1
   String ret = s;
   Ogre::StringUtil::toLowerCase(ret);
   return ret;
#else
   String ret = s;
   std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
   return ret;
#endif
}

/************************************************************************
 *                              toLowerCase                             *
 ************************************************************************/
String StringUtil::toString(int val)
{
#if KOBOLD_HAS_OGRE == 1
  return Ogre::StringConverter::toString(val);
#else
  std::ostringstream s;
  s << val;
  return s.str();
#endif

}

/************************************************************************
 *                               endsWith                               *
 ************************************************************************/
bool StringUtil::endsWith(const String& s, char c)
{
   if(s.length() > 0)
   {
      return s[s.length() - 1] == c;
   }

   return false;
}


