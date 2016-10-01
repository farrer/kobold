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


#ifndef _kobold_list_test_case_h
#define _kobold_list_test_case_h

#include "../list.h"

#include "assert.h"

namespace Kobold
{

class ElementTest : public ListElement
{
   public:
      ElementTest(int id);
      int id;
};

class ListTest : public List
{
   public:
      ListTest(int type);
      ~ListTest();
};

class ListTestCase
{
   public:
      ListTestCase();
      ~ListTestCase();

      void run();

   protected:
      ListTest* beginList;
      ListTest* endList;
};


}

#endif

