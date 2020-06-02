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

#ifndef _kobold_file_reader_h
#define _kobold_file_reader_h

#include "kstring.h"
#include <fstream>

namespace Kobold 
{

/*! Abstraction to read files from distinct resources abstractions 
 * (for example, direct from disk or using ogre resources manager). */
class FileReader
{
   public:
      /*! Destructor */
      virtual ~FileReader() {};

      /*! Open the stream (file).
       * \param fileName name of the file to load
       * \return true if opened, false if not */
      virtual bool open(const Kobold::String& fileName) = 0;

      /*! \return total file size in bytes */
      virtual size_t getSize() = 0;

      /*! \return true if end of file, false if not */
      virtual bool eof() = 0 ;

      /*! \return line read from the stream */
      virtual Kobold::String getLine() = 0;

      /*! Read n bytes to the stream s */
      virtual void read(char* s, size_t n) = 0;

      /*! Close the stream */
      virtual void close() = 0;
};

/*! File reader to load direct from disk with absolute or relative paths. */
class DiskFileReader : public FileReader
{
   public:
      /*! Constructor */
      DiskFileReader();
      /*! Destructor */
      virtual ~DiskFileReader();

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
      std::ifstream fileStream;  /**< File when using std full path */
      Kobold::String filename; /**< Name of the file */

};

}


#endif

