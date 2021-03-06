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

#include "defparser.h"
#include "log.h"
#include <iostream>

namespace Kobold
{

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                                DefTuple                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
DefTuple::DefTuple()
{
   value = "";
   key = "";
}

/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
DefTuple::~DefTuple()
{
}

/***********************************************************************
 *                              setValue                               *
 ***********************************************************************/
void DefTuple::setValue(const Kobold::String& v)
{
   value = v;
}

/***********************************************************************
 *                               setKey                                *
 ***********************************************************************/
void DefTuple::setKey(const Kobold::String& k)
{
   key = k;
}

/***********************************************************************
 *                              getValue                               *
 ***********************************************************************/
const Kobold::String& DefTuple::getValue() const
{
   return value;
}


/***********************************************************************
 *                               getKey                                *
 ***********************************************************************/
const Kobold::String& DefTuple::getKey() const
{
   return key;
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                               DefParser                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

/***********************************************************************
 *                            Constructor                              *
 ***********************************************************************/
DefParser::DefParser() : List(LIST_TYPE_ADD_AT_END)
{
   curTuple = NULL;
}

/***********************************************************************
 *                             Destructor                              *
 ***********************************************************************/
DefParser::~DefParser()
{
   clear();
}

/***********************************************************************
 *                               clear                                 *
 ***********************************************************************/
void DefParser::doClear()
{
   clear();
   curTuple = NULL;
}

/***********************************************************************
 *                            insertTuple                              *
 ***********************************************************************/
void DefParser::insertTuple(const Kobold::String& key, 
      const Kobold::String& value)
{
   DefTuple* tuple = new DefTuple();
 
   /* Set tuple values */
   tuple->setKey(key);
   tuple->setValue(value);

   insert(tuple);
}

/***********************************************************************
 *                            getNextTuple                             *
 ***********************************************************************/
bool DefParser::getNextTuple(Kobold::String& key, Kobold::String& value)
{
   if(getTotal() <= 0)
   {
      /* No tuples to get */
      return false;
   }

   if(curTuple == NULL)
   {
      /* Will get first tuple */
      curTuple = (DefTuple*) getFirst();
   }
   else if(curTuple->getNext() == getFirst())
   {
      /* No more tuples to get */
      return false;
   }
   else
   {
      /* Get the Next Tuple */
      curTuple = (DefTuple*) curTuple->getNext();
   }

   /* Set the tuple */
   key = curTuple->getKey();
   value = curTuple->getValue();
  
   return true;
}

/***********************************************************************
 *                                load                                 *
 ***********************************************************************/
bool DefParser::load(const Kobold::String& fileName, bool stringFile)
{
   DiskFileReader streamStd;
   return load(fileName, stringFile, streamStd);
}

/***********************************************************************
 *                                load                                 *
 ***********************************************************************/
bool DefParser::load(const Kobold::String& fileName, bool stringFile, 
            FileReader& stream)
{
   Kobold::String strBuffer, strKey, strData;
   Kobold::String::size_type pos;
   int line;

   /* Clear any previous loaded tuples. */
   doClear();

   /* Open the Definition File */
   if(!stream.open(fileName.c_str())) 
   {
      Kobold::Log::add(LOG_LEVEL_ERROR,
            "defParser: Couldn't open file: '%s'", fileName.c_str());
      return false;
   }
   
   for(line = 1; !stream.eof(); line++)
   {
      /* Get the line */
      strBuffer = stream.getLine();

      /* Find First non white space character */ 
      pos = strBuffer.find_first_not_of(" \t");

      /* Ignore empty lines and comented ones */
      if( (pos != Kobold::String::npos) && (strBuffer[pos] != '\n') && 
          (strBuffer[pos] != '\r') && (strBuffer[pos] != 0) && 
          (strBuffer[pos] != '#') )
      {
          if(stringFile)
          {
             if(strBuffer[pos] != '"')
             {
                Kobold::Log::add(LOG_LEVEL_NORMAL, 
                      "defParser: Was expecting \" at key '%s'", 
                      strBuffer.c_str());
                /* Invalid string file! */
                stream.close();
                return false;
             }
             pos += 1;
             /* Get the key up to " or = */
             strKey = strBuffer.substr(pos,
                         strBuffer.find_first_of("\"=\n", pos) - pos);
             pos += strKey.size();
             
             /* Get the '"' character */
             pos = strBuffer.find_first_not_of(" \t\n", pos);
             if((pos == Kobold::String::npos) || (strBuffer[pos] != '"'))
             {
                stream.close();
                Kobold::Log::add(LOG_LEVEL_NORMAL,
                   "defParser: Was expecting trail \" at key '%s'",
                   strBuffer.c_str());
                return false;
             }
             pos = pos + 1;
          }
          else
          {
             /* Get the key */
             strKey = strBuffer.substr(pos,
                              strBuffer.find_first_of(" =\t\n\r", pos) - pos);
             pos += strKey.size();
          }

          /* Get the '=' character */
          pos = strBuffer.find_first_not_of(" \t", pos);
          if((pos == Kobold::String::npos) || (strBuffer[pos] != '='))
          {
             Kobold::Log::add(LOG_LEVEL_NORMAL, 
                "defParser: Was expecting '=' at '%s'", strBuffer.c_str());
             stream.close();
             return false;
          }

          /* find the first non-whitespace after the '=' */
          pos = strBuffer.find_first_not_of(" \t", pos + 1);

          /* get the data */
          if(pos != Kobold::String::npos)
          {
             strData = strBuffer.substr(pos, strBuffer.length() - pos);
          }
          else
          {
             strData = "";
          }

          /* Delete last character if it is an \n or #13.
           * This is an issue that happens mainly on windows.
           * Also, delete it while is an space or " */
          while( (strData.length() > 0) &&
                 ( (strData[strData.length()-1] == '\n') ||
                   (strData[strData.length()-1] == 13) ||
                   (strData[strData.length()-1] == ' ') ||
                   (strData[strData.length()-1] == '"')) )
          {
             strData.erase(strData.length()-1);
          }
         
         /* Delete first character if it is an " */
         if( (strData.length() > 0) && (strData[0] == '"') )
         {
            strData = strData.erase(0,1);
         }

          /* Insert a tuple */
          insertTuple(strKey, strData);
      }
   }

   /* Close input */
   stream.close();
   
   return true;
}

}

