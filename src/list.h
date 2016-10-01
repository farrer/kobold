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

#ifndef _kobold_list_h
#define _kobold_list_h

#include "koboldconfig.h"

namespace Kobold
{

/*! The List types */
enum
{
   LIST_TYPE_ADD_AT_BEGIN=0,
   LIST_TYPE_ADD_AT_END
};

/*! Basic class for elements that could be contained by a List. It implements
 * next and previous pointers. 
 * \note This way an ListElement must be only contained by a single list,
 *       otherwise those pointers will be overidden. */
class ListElement
{
   public:
      /*! Constructor */
      ListElement();
      /*! Destructor */
      virtual ~ListElement();

      /*! Get the next element
       * \return pointer to the next element */
      ListElement* getNext();
      /*! Get the previous element
       * \return pointer to the previous element */
      ListElement* getPrevious();

      /*! Set the next element
       * \param obj -> pointer to the next element on the List */
      void setNext(ListElement* obj);
      /*! Set the previous element
       * \param obj -> pointer to the previous element on the List */
      void setPrevious(ListElement* obj);

   protected:

      ListElement* next;           /**< Next on List */
      ListElement* previous;       /**< Previous on List */

};

/*! A basic chained list implementation. 
 *  \note The advantage of using this in some cases instead of the std::list
 *       is that while having the pointer reference we can easily walk through
 *       the list, and also that all elements will be deleted at list's 
 *       destructor. In cases thi isn't desirable, just use std::list 
 *       instead if List. */
class List
{
   public:
      /*! Constructor 
       * param t -> List type */
      List(int t=LIST_TYPE_ADD_AT_BEGIN);
      /*! Destructor 
       * \note: any remaining list elements in the list will be
       * deleted in this call. */
      ~List();

      /*! Clear all List elements */
      void clearList();

      /*! Insert an element on the List, at the default position
       * \param obj -> object to insert
       * \return true if ok */
      bool insert(ListElement* obj);

      /*! Insert element at the List's begin 
       * \param obj -> object to insert
       * \return true if ok */
      bool insertAtBegin(ListElement* obj);

      /*! Insert element at List's end 
       * \param obj -> object to insert
       * \return true if ok */
      bool insertAtEnd(ListElement* obj);
   
      /*! Insert the element before another element on list
       * \param obj -> object to insert
       * \param beforeObj -> reference object
       * \param updateFirstPtr -> true to update first pointer if necessary,
       *                          false to kept it untouched.
       * return true if ok */
      bool insertBefore(ListElement* obj, ListElement* beforeObj,
                        bool updateFirstPtr = true);

      /*! Remove an element from the List
       * \param obj -> element to remove
       * \note This function will delete the 
       *       element's pointer when returning true.
       * \return true if ok */
      bool remove(ListElement* obj);

      /*! Only remove the element from the List, without deleting it
       * \param obj -> obj to remove
       * \return true if ok */
      bool removeWithoutDelete(ListElement* obj);

       /*! Get total elements on the List
       * \return total elements on the List */
      int getTotal();

      /*! Get the first element
       * \return pointer to the first element */
      ListElement* getFirst();
   
      /*! Get the last element
       * \return pointer to the last element of list. */
      ListElement* getLast();

   protected:

      ListElement* first;             /**< Pointer to the first List element */
      int total;                      /**< Total elements on the List */

   private:
      int listType;                   /**< List type (FIFO, LIFO) */
};

}

#endif

