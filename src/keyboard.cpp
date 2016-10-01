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

#include "keyboard.h"

using namespace Kobold;

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS


#define KEYBOARD_UPDATE_RATE  80

/*****************************************************************
 *                         updateState                           *
 *****************************************************************/
void Keyboard::updateState()
{
   keys = SDL_GetKeyboardState(NULL);

   /* Check on-editing keys */
   if(editor)
   {
      Uint32 curTicks = SDL_GetTicks();
      bool elapsed = (curTicks - lastKeyCheck) >= KEYBOARD_UPDATE_RATE;

      /* Check stop text edit keys */
      if((isKeyPressed(KOBOLD_KEY_ESCAPE)) ||
         (isKeyPressed(KOBOLD_KEY_RETURN)) ||
         (isKeyPressed(KOBOLD_KEY_KP_ENTER)))
      {
         stopEditingText();
         return;
      }

      if(elapsed)
      {
         /* Check sent to init */
         if(isKeyPressed(KOBOLD_KEY_HOME))
         {
            lastKeyCheck = curTicks;
            editor->sendCursorToInit();
         }
         /* Check sent to end */
         else if(isKeyPressed(KOBOLD_KEY_END))
         {
            lastKeyCheck = curTicks;
            editor->sendCursorToEnd();
         }
         /* Check Move right */
         else if(isKeyPressed(KOBOLD_KEY_RIGHT))
         {
            lastKeyCheck = curTicks;
            editor->changeCursorPosition(1);
         }
         /* Check Move left */
         else if(isKeyPressed(KOBOLD_KEY_LEFT))
         {
            lastKeyCheck = curTicks;
            editor->changeCursorPosition(-1);
         }
         /* Check delete after cursor */
         else if(isKeyPressed(KOBOLD_KEY_DELETE))
         {
            lastKeyCheck = curTicks;
            editor->deleteCharacterFromCursor(true);
         }
         /* Check delete before cursor */
         else if(isKeyPressed(KOBOLD_KEY_BACKSPACE))
         {
            lastKeyCheck = curTicks;
            editor->deleteCharacterFromCursor(false);
         }
      }
   }
}

/*****************************************************************
 *                        isKeyPressed                           *
 *****************************************************************/
bool Keyboard::isKeyPressed(Kobold::KeyCodes key)
{
   return keys[key];
}

/*****************************************************************
 *                      startEditingText                         *
 *****************************************************************/
void Keyboard::startEditingText(KeyboardTextEditor* editor)
{
   if(Keyboard::editor)
   {
      /* Must end the editing of the current one */
      Keyboard::editor->doneWithEditing();
   }
   else
   {
      /* Must start sdl input */
      SDL_StartTextInput();
   }

   /* Define current editor */
   Keyboard::editor = editor;
}

/*****************************************************************
 *                       stopEditingText                         *
 *****************************************************************/
void Keyboard::stopEditingText()
{
   if(editor)
   {
      editor->doneWithEditing();
      SDL_StopTextInput();
      editor = NULL;
   }
}

/*****************************************************************
 *                        isEditingText                          *
 *****************************************************************/
bool Keyboard::isEditingText()
{
   return (editor != NULL);
}

/*****************************************************************
 *                          getEditor                            *
 *****************************************************************/
KeyboardTextEditor* Keyboard::getEditor()
{
   return editor;
}

/*****************************************************************
 *                         updateByEvent                         *
 *****************************************************************/
void Keyboard::updateByEvent(SDL_Event event)
{
   if(editor)
   {
      switch (event.type) 
      {
         case SDL_TEXTINPUT:
            /* Add new text onto the end of our text */
            editor->appendToCursor(event.text.text);
         break;
         case SDL_TEXTEDITING:
            //TODO: if we'll support ISM.
         break;
      }
   }
}


/*****************************************************************
 *                        static members                         *
 *****************************************************************/
const Uint8* Keyboard::keys = NULL;
KeyboardTextEditor* Keyboard::editor = NULL;
Uint32 Keyboard::lastKeyCheck = 0;

#endif
