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

#include "list.h"
#include <stdlib.h>

namespace Kobold
{


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                             ListElement                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
ListElement::ListElement()
{
   next = NULL;
   previous = NULL;
}

/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
ListElement::~ListElement()
{
}

/***********************************************************************
 *                              getNext                                *
 ***********************************************************************/
ListElement* ListElement::getNext()
{
   return next;
}

/***********************************************************************
 *                            getPrevious                              *
 ***********************************************************************/
ListElement* ListElement::getPrevious()
{
   return previous;
}

/***********************************************************************
 *                                setNext                              *
 ***********************************************************************/
void ListElement::setNext(ListElement* obj)
{
   next = obj;
}

/***********************************************************************
 *                              setPrevious                            *
 ***********************************************************************/
void ListElement::setPrevious(ListElement* obj)
{
   previous = obj;
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                               List                                 //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
List::List(int t)
{
   first = NULL;
   total = 0;
   listType = t;
}

/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
List::~List()
{
   clear();
}

/***********************************************************************
 *                               clear                                 *
 ***********************************************************************/
void List::clearList()
{
   clear();
}
void List::clear()
{
   int i;
   ListElement* e = first;
   ListElement* paux;

   /* Delete all elements */
   for(i=0; i<total; i++)
   {
      paux = e;
      e = e->getNext();
      delete paux;
   }

   first = NULL;
   total = 0;
}

/***********************************************************************
 *                               insert                                *
 ***********************************************************************/
bool List::insert(ListElement* obj)
{
   if(obj == NULL)
   {
      return false;
   }

   if(listType == LIST_TYPE_ADD_AT_BEGIN)
   {
      return insertAtBegin(obj);
   }
   /* Else */
   return insertAtEnd(obj);
}

/***********************************************************************
 *                         insertAtBegin                               *
 ***********************************************************************/
bool List::insertAtBegin(ListElement* obj)
{
   if(total == 0)
   {
      /* It's the only element */
      obj->setNext(obj);
      obj->setPrevious(obj);
      total++;
   }
   else
   {
      /* Insert it before the first */
      insertBefore(obj, first);
   }

   /* Set as the first */
   first = obj;

   return true;
}

/***********************************************************************
 *                               insert                                *
 ***********************************************************************/
bool List::insertAtEnd(ListElement* obj)
{
   if(total == 0)
   {
      /* It's the only element */
      obj->setNext(obj);
      obj->setPrevious(obj);
      first = obj;
      total++;
   }
   else
   {
      /* Insert it before the first, without updating the first pointer */
      insertBefore(obj, first, false);
   }

   return true;
}

/***********************************************************************
 *                               insert                                *
 ***********************************************************************/
bool List::insertBefore(ListElement* obj, ListElement* beforeObj,
                        bool updateFirstPtr)
{
   if(total == 0)
   {
      /* empty list and calling to insert before something? Never! */
      return false;
   }
   
   obj->setNext(beforeObj);
   obj->setPrevious(beforeObj->getPrevious());
   obj->getNext()->setPrevious(obj);
   obj->getPrevious()->setNext(obj);
   total++;
   
   /* Update first pointer, if necessary */
   if( (updateFirstPtr) && (beforeObj == first) )
   {
      first = obj;
   }
   
   return true;
}


/***********************************************************************
 *                        removeWithoutDelete                          *
 ***********************************************************************/
bool List::removeWithoutDelete(ListElement* obj)
{
   if(obj == NULL)
   {
      return false;
   }

   /* Update the pointers */
   obj->getNext()->setPrevious(obj->getPrevious());
   obj->getPrevious()->setNext(obj->getNext());
   
   if(first == obj)
   {
      first = first->getNext();
   } 
   
   /* And dec */
   total--;
   if(total == 0)
   {
      first = NULL;
   }

   return true;
}

/***********************************************************************
 *                               remove                                *
 ***********************************************************************/
bool List::remove(ListElement* obj)
{
   if(removeWithoutDelete(obj))
   {
      /* Really remove it */
      delete obj;
      return true;
   }

   return false;
}

/***********************************************************************
 *                               getFirst                              *
 ***********************************************************************/
ListElement* List::getFirst()
{
   return first;
}

/***********************************************************************
 *                               getLast                               *
 ***********************************************************************/
ListElement* List::getLast()
{
   if(first)
   {
      return first->getPrevious();
   }
   return NULL;
}

/***********************************************************************
 *                               getTotal                              *
 ***********************************************************************/
int List::getTotal()
{
   return total;
}
    
}

