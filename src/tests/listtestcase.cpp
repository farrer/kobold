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

#include "listtestcase.h"

#include <stdio.h>

using namespace Kobold;

ElementTest::ElementTest(int id)
{
   this->id = id;
}

ListTest::ListTest(int type) : List(type)
{

}


ListTest::~ListTest()
{
   clearList();
}



ListTestCase::ListTestCase()
{
   beginList = new ListTest(LIST_TYPE_ADD_AT_BEGIN);
   endList = new ListTest(LIST_TYPE_ADD_AT_END);
}

ListTestCase::~ListTestCase()
{
   delete beginList;
   delete endList;
}

#define NUM_ELEMENTS 200

void ListTestCase::run()
{
   ElementTest* e50 = NULL;

   /* Insert some elements */
   for(int i=0; i<NUM_ELEMENTS; i++)
   {
      beginList->insert(new ElementTest(i));
      endList->insert(new ElementTest(i));

      if(i == 50)
      {
         e50 = (ElementTest*) beginList->getFirst();
      }
   }

   /* Check list size */
   assert(beginList->getTotal() == NUM_ELEMENTS);
   assert(endList->getTotal() == NUM_ELEMENTS);

   /* Must check if list order is as defined. */
   ElementTest* e1 = (ElementTest*) beginList->getLast();
   ElementTest* e2 = (ElementTest*) endList->getFirst();
   for(int i=0; i<NUM_ELEMENTS; i++)
   {
      assert(e1->id == i);
      assert(e2->id == i);

      e1 = (ElementTest*) e1->getPrevious();
      e2 = (ElementTest*) e2->getNext();
   }
   
   /* Now reverse order navigation check */
   e1 = (ElementTest*) beginList->getFirst();
   e2 = (ElementTest*) endList->getLast();
   for(int i=NUM_ELEMENTS-1; i>=0; i--)
   {
      assert(e1->id == i);
      assert(e2->id == i);
 
      e1 = (ElementTest*) e1->getNext();
      e2 = (ElementTest*) e2->getPrevious();     
   }

   /* Test insertAtBegin and insertAtEnd functions */
   ElementTest* last = (ElementTest*) endList->getLast();
   ElementTest* first = (ElementTest*) endList->getFirst();

   endList->insertAtBegin(new ElementTest(-1));
   assert(endList->getTotal() == NUM_ELEMENTS+1);
   assert(((ElementTest*) endList->getFirst())->id == -1);
   assert(endList->getFirst()->getNext() == first);

   endList->insertAtEnd(new ElementTest(-2));
   assert(endList->getTotal() == NUM_ELEMENTS+2);
   assert(((ElementTest*) endList->getLast())->id == -2);
   assert(endList->getLast()->getPrevious() == last);

   /* Test insertBefore */
   ElementTest* e = new ElementTest(-3);
   beginList->insertBefore(e, e50);
   assert(beginList->getTotal() == NUM_ELEMENTS+1);
   assert(e->getNext() == e50);
   assert(e50->getPrevious() == e);

   e = new ElementTest(-4);
   beginList->insertBefore(e, beginList->getFirst());
   assert(beginList->getTotal() == NUM_ELEMENTS+2);
   assert(e == beginList->getFirst());

   e = new ElementTest(-5);
   beginList->insertBefore(e, beginList->getFirst(), false);
   assert(beginList->getTotal() == NUM_ELEMENTS+3);
   assert(e != beginList->getFirst());

   /* Let's test a remove element without deleting it */
   beginList->removeWithoutDelete(e);
   assert(beginList->getTotal() == NUM_ELEMENTS+2);
   /* As not deleted, should not get doublefree here. */
   delete e;

   /* Remove an element and check if it doesn't exist anymore */
   beginList->remove(e50);
   e = (ElementTest*) beginList->getFirst();
   for(int i=0; i < beginList->getTotal(); i++)
   {
      assert(e->id != 50);
      e = (ElementTest*) e->getNext();
   }

   /* Last clear a list removing the last */
   while(beginList->getTotal() > 0)
   {
      beginList->remove(beginList->getLast());
   }

   /* clearList function is tested at the destructor. Done. */

}


