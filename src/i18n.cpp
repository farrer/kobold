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

#include "i18n.h"
#include "defparser.h"
#include "log.h"

using namespace Kobold;

/****************************************************************
 *                         Constructor                          *
 ****************************************************************/
i18nFile::i18nFile(const Kobold::String& fileName, 
      const Kobold::String& language)
{
   DefParser def;
   Kobold::String key;
   Kobold::String value;
   total = 0;
   head = NULL;
   
   if(!def.load(language+Kobold::String("/")+fileName,
                false, true))
   {
      Kobold::Log::add(Kobold::String("Error: couldn't load '")+
         fileName + Kobold::String("' for language ")+
         language + Kobold::String(". Using English."));
      if(!def.load(Kobold::String("en/"+fileName), false, true))
      {
         Kobold::Log::add(
            Kobold::String("Error: couldn't load '")+
            fileName + Kobold::String("' for English. Aborting."));
      }
   }
   
   /* Insert all file. */
   while(def.getNextTuple(key, value))
   {
      add(key, value);
   }
}

/****************************************************************
 *                          Destructor                          *
 ****************************************************************/
i18nFile::~i18nFile()
{
   clear(head);
}

/****************************************************************
 *                          translate                           *
 ****************************************************************/
Kobold::String i18nFile::translate(const Kobold::String& s)
{
   i18nString* node = find(s, head);
   if(node != NULL)
   {
      if(node->strTrans.length() > 0)
      {
         Kobold::String res = node->strTrans;
         return Kobold::StringUtil::replaceAll(res, '|', '\n');
      }
   }
   
   /* Not found or empty. Use the string untraslated. */
   return Kobold::StringUtil::replaceAll(s, '|', '\n');
}

/****************************************************************
 *                          getTotal                            *
 ****************************************************************/
const int i18nFile::getTotal() const
{
   return total;
}


/****************************************************************
 *                             clear                            *
 ****************************************************************/
void i18nFile::clear(i18nString* c)
{
   if(c == NULL)
   {
      /* Nothing to clear */
      return;
   }
   
   /* Try to clear its left children */
   clear(c->left);
   /* Try to clear its right children */
   clear(c->right);
   
   /* Remove parent reference */
   if(c->parent != NULL)
   {
      if(c->parent->left == c)
      {
         c->parent->left = NULL;
      }
      if(c->parent->right == c)
      {
         c->parent->right = NULL;
      }
   }
   
   /* Finally, delete itself. */
   delete c;
}

/****************************************************************
 *                              add                             *
 ****************************************************************/
i18nFile::i18nString* i18nFile::add(const Kobold::String& s,
      const Kobold::String& translation)
{
   total++;
   
   if(head == NULL)
   {
      head = new i18nString();
      head->right = NULL;
      head->left = NULL;
      head->parent = NULL;
      head->strKey = s;
      head->strTrans = translation;
      
      return head;
   }
   
   return add(s, translation, head);
}

/****************************************************************
 *                              add                             *
 ****************************************************************/
i18nFile::i18nString* i18nFile::add(const Kobold::String& s,
      const Kobold::String& translation, i18nString* c)
{
   int compValue = s.compare(c->strKey);
   if(compValue == 0)
   {
      /* No need to insert the string itself */
      return c;
   }
   else if(compValue < 0)
   {
      /* try to insert at left branch */
      if(c->left == NULL)
      {
         c->left = new i18nString();
         c->left->right = NULL;
         c->left->left = NULL;
         c->left->parent = c;
         c->left->strKey = s;
         c->left->strTrans = translation;
         return c->left;
      }
      else
      {
         return add(s, translation, c->left);
      }
   }
   else
   {
      /* try to insert at right branch */
      if(c->right == NULL)
      {
         c->right = new i18nString();
         c->right->right = NULL;
         c->right->left = NULL;
         c->right->parent = c;
         c->right->strKey = s;
         c->right->strTrans = translation;
         return c->right;
      }
      else
      {
         return add(s, translation, c->right);
      }
   }
}

/****************************************************************
 *                            find                              *
 ****************************************************************/
i18nFile::i18nString* i18nFile::find(const Kobold::String& s, i18nString* c)
{
   if(c == NULL)
   {
      /* Not found! */
      return NULL;
   }
   
   int compValue = s.compare(c->strKey);
   if(compValue == 0)
   {
      /* Found! */
      return c;
   }
   else if(compValue < 0)
   {
      return find(s, c->left);
   }
   else
   {
      return find(s, c->right);
   }
}

/****************************************************************
 *                            init                              *
 ****************************************************************/
void i18n::init(const Kobold::String& fileName, const Kobold::String& language)
{
   curFile = new i18nFile(fileName, language);
}

/****************************************************************
 *                            clear                              *
 ****************************************************************/
void i18n::clear()
{
   if(curFile != NULL)
   {
      delete curFile;
   }
}

/****************************************************************
 *                          translate                           *
 ****************************************************************/
Kobold::String i18n::translate(const Kobold::String& s)
{
   if(curFile != NULL)
   {
      return curFile->translate(s);
   }
   return s;
}

i18nFile* i18n::curFile=NULL;

