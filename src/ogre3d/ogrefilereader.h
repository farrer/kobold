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
      bool open(const Kobold::String& fileName) override;

      /*! \return total file size in bytes */
      size_t getSize() override;

      /*! \return current position */
      size_t tell() override;

      /*! Seek for an specific position */
      bool seek(size_t pos) override;

      /*! \return true if end of file, false if not */
      bool eof() override;

      /*! \return line read from the stream */
      Kobold::String getLine() override;

      /*! Read n bytes to the stream s */
      bool read(char* s, size_t n) override;

      /*! Close the stream */
      void close() override;

   private:
      Ogre::DataStreamPtr fileData; /**< Data for loading file within ogre */

};


}


#endif

