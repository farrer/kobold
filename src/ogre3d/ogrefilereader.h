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

#ifndef _kobold_ogre_file_reader_h
#define _kobold_ogre_file_reader_h

#include "../filereader.h"
#include <OGRE/OgreDataStream.h>

namespace Kobold
{

/*! File reader to load files using ogre resource manager system. */
class OgreFileReader : public FileReader
{
   public:
      /*! Constructor */
      OgreFileReader();
      /*! Destructor */
      virtual ~OgreFileReader();

      /*! Open the stream (file).
       * \param fileName name of the file to load
       * \return true if opened, false if not */
      virtual bool open(const Kobold::String& fileName);

      /*! \return total file size in bytes */
      virtual size_t getSize();

      /*! \return true if end of file, false if not */
      virtual bool eof();

      /*! \return line read from the stream */
      virtual Kobold::String getLine();

      /*! Read n bytes to the stream s */
      virtual void read(char* s, size_t n);

      /*! Close the stream */
      virtual void close();

   private:
      Ogre::DataStreamPtr fileData; /**< Data for loading file within ogre */

};


}


#endif

