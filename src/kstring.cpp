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

#include <sstream>
#include <string>
#include <algorithm>

using namespace Kobold;

/************************************************************************
 *                              replaceAll                              *
 ************************************************************************/
String StringUtil::replaceAll(const String& s, char orig, char dest)
{
   String ret = s;
   std::replace(ret.begin(), ret.end(), orig, dest);
   return ret;
}

/************************************************************************
 *                              toLowerCase                             *
 ************************************************************************/
String StringUtil::toLowerCase(const String& s)
{
   String ret = s;
   std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
   return ret;
}

/************************************************************************
 *                              toLowerCase                             *
 ************************************************************************/
String StringUtil::toString(int val)
{
  std::ostringstream s;
  s << val;
  return s.str();
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


