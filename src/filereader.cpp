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

#include "filereader.h"
#include <sys/stat.h>

namespace Kobold
{

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
DiskFileReader::DiskFileReader() 
{
}
 
/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
DiskFileReader::~DiskFileReader() 
{
}

/***********************************************************************
 *                                open                                 *
 ***********************************************************************/
bool DiskFileReader::open(const Kobold::String& fileName) 
{
   this->filename = fileName;
   this->fileStream.open(fileName.c_str(), std::ios::in | std::ios::binary);
   if(!this->fileStream)
   {
      return false;
   }

   return true;
}

/***********************************************************************
 *                              getSize                                *
 ***********************************************************************/
size_t DiskFileReader::getSize() 
{
   struct stat st;
   stat(filename.c_str(), &st);
   return st.st_size;
}

/***********************************************************************
 *                                eof                                  *
 ***********************************************************************/
bool DiskFileReader::eof() 
{
   return fileStream.eof();
}

/***********************************************************************
 *                               getLine                               *
 ***********************************************************************/
Kobold::String DiskFileReader::getLine() 
{
   Kobold::String strBuffer;
   getline(fileStream, strBuffer);
   return strBuffer;
}

/***********************************************************************
 *                                read                                 *
 ***********************************************************************/
void DiskFileReader::read(char* s, size_t n)
{
   fileStream.read(s, n);
}

/***********************************************************************
 *                                close                                *
 ***********************************************************************/
void DiskFileReader::close() 
{
   fileStream.close();
}

}

