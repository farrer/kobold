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

#ifndef _kobold_i18n_h
#define _kobold_i18n_h

#include "koboldconfig.h"
#include "kstring.h"

namespace Kobold
{
   
class i18nFile
{
   public:
      /*! Constructor
       * \param fileName the filename (without dir) to load 
       * \param language to load the file name 
       * \note: if fileName not found on language, load en */
      i18nFile(const Kobold::String& fileName, const Kobold::String& language);
      /*! Destructor */
      ~i18nFile();
   
      /*! Try to translate the string with current file
       * \param s -> string to translate
       * \return translated string*/
      Kobold::String translate(const Kobold::String& s);
   
      /*! Get total strings loaded. */
      const int getTotal() const;
   
   protected:
   
      /*! A string element */
      class i18nString
      {
         public:
            Kobold::String strKey;    /**< The key to translate */
            Kobold::String strTrans;  /**< The key translated */
            i18nString* left;       /**< Left key on tree */
            i18nString* right;      /**< Right key on tree */
            i18nString* parent;     /**< Parent key on tree */
      };
   
      /*! Search for an string on the tree
       * \return pointer to the string element found or NULL */
      i18nString* find(const Kobold::String& s, i18nString* c);
   
      /*! Add string to the tree */
      i18nString* add(const Kobold::String& s, 
            const Kobold::String& translation);
      i18nString* add(const Kobold::String& s, 
            const Kobold::String& translation, i18nString* c);
   
      /*! Clear the list from c to all leafs */
      void clear(i18nString* c);
   
      i18nString* head; /**< Current btree head */
      int total; /**< total elements at the tree */
};
   
class i18n
{
   public:
      /*! Constructor
       * \param fileName the filename (without dir) to load
       * \param language to load the file name
       * \note: if fileName not found on language, load en */
      static void init(const Kobold::String& fileName, 
            const Kobold::String& language);
      /*! End the use of i18 system */
      static void clear();
   
      /*! Try to translate the string with current file
       * \param s -> string to translate
       * \return translated string*/
      static Kobold::String translate(const Kobold::String& s);

   private:
      i18n(){};
      static i18nFile* curFile;
};

}

#endif
