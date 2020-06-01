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
#include <OGRE/OgreDataStream.h>

namespace Kobold 
{

/*! Stream used to load file for DefParser */
class OgreDefStream : public DefStream
{
   public:
      /*! Constructor */
      OgreDefStream();
      /*! Destructor */
      virtual ~OgreDefStream();

      /*! Open the stream (file).
       * \param fileName name of the file to load
       * \return true if opened, false if not */
      virtual bool open(const Kobold::String& fileName);

      /*! \return true if end of file, false if not */
      virtual bool eof();

      /*! \return line read from the stream */
      virtual Kobold::String getLine();

      /*! Close the stream */
      virtual void close();

   private:
      Ogre::DataStreamPtr fileData; /**< Data for loading file within ogre */

};

class OgreDefParser : public DefParser 
{
   public:
      OgreDefParser();
      virtual ~OgreDefParser();

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

