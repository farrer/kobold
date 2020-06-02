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

#ifndef _kobold_def_parser_h
#define _kobold_def_parser_h

#include "koboldconfig.h"
#include "kstring.h"
#include "list.h"
#include "filereader.h"

namespace Kobold
{

/*! The DefTuple class is a representaton of a tuple "key = value"  */
class DefTuple : public ListElement
{
   public:
      /*! Constructor */
      DefTuple();
      /*! Destructor */
      ~DefTuple();

      /*! Set the tuple value
       * \param v -> new value */
      void setValue(const Kobold::String& v);
      /*! Set the tuple Key
       * \param k -> new key */
      void setKey(const Kobold::String& k);

      /*! Get tuple value
       * \return -> current tuple value */
      const Kobold::String& getValue() const;
      /*! Get the tuple key
       * \return -> current tuple key */
      const Kobold::String& getKey() const;

   protected:
      Kobold::String value;         /**< Tuple Value */
      Kobold::String key;           /**< Tuple Key */

};

/*! The DefParser class is the implementation of a definitions
 * file parser (those with "key = value"). It generate tuples of 
 * keys and values to be interpreted by the real file interpreter. */
class DefParser : public List
{
   public:
      /*! Constructor */
      DefParser();
      /*! Destructor */
      virtual ~DefParser();

      /*! Load File. Could be called multiple times, for distinct file load
       * with the same structure. Each time it's called, the old structure
       * is freed and a new one is created with all information loaded. 
       * \param fileName -> file name to load
       * \param stringFile -> true to load an "string a" = "string b"
       *                       like file (i18n is one of this type). */
      virtual bool load(const Kobold::String& fileName, bool stringFile);

      /*! Get the next tuple from the list
       * \param key -> string with the next key
       * \param value -> string with the next value 
       * \return -> true if can get the next tuple, false if no 
       *            more tuples to get */
      bool getNextTuple(Kobold::String& key, Kobold::String& value);

   protected:

      /*! Load the definition file using a not yet opened stream */
      bool load(const Kobold::String& fileName, bool stringFile, 
            FileReader& stream);

      /** Clear and delete all created structures */
      void doClear();

      /*! Insert a tuple into linked list
       * \param key -> tuple key
       * \param value -> tuple value */
      void insertTuple(const Kobold::String& key, const Kobold::String& value);

      DefTuple* curTuple;      /**< Current Tuple */
};

}

#endif

