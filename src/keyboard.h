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

#ifndef _kobold_keyboard_h
#define _kobold_keyboard_h

#include "platform.h"

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS

#include <SDL2/SDL.h>
#include "koboldconfig.h"
#include "kstring.h"
#include "keycodes.h"

namespace Kobold
{

/*! Simple abstract class for keyboard text editing. */
class KeyboardTextEditor
{
   public:
      /*! Append text to current cursor position 
       * \param textToAppend string to append to current cursor position. */
      virtual void appendToCursor(Kobold::String textToAppend)=0;

      /*! Delete a character at current cursor position.
       * \param after -> true to delete character after the cursor (like 
       *                 keyboard 'delete' key), false to delete character
       *                 before cursor (like keyboard 'backspace' key). */
      virtual void deleteCharacterFromCursor(bool after)=0;

      /*! Set current cursor position to editing text's init */
      virtual void sendCursorToInit()=0;

      /*! Set current cursor position to editing text's end */
      virtual void sendCursorToEnd()=0;
 
      /*! Change current cursor position by delta characters.
       * \param delta to change cursor. > 0 forward, < 0 backward */
      virtual void changeCursorPosition(int delta)=0;

      /*! Called when done with text editing */
      virtual void doneWithEditing()=0;
};

/*! The keyboard implementation, on top of SDL2. */
class Keyboard
{
   public:

      /*! Update current keyboard state. */
      static void updateState();

      /*! Get current keyboard state. */
      static bool isKeyPressed(Kobold::KeyCodes key);

      /*! Tell the controller that we started to edit a text. For example, 
       * when the user changed the focus to a widget of text input.
       * \param editor the current editor instance (could be a widget instance,
       *        for example). */
      static void startEditingText(KeyboardTextEditor* editor);
      /*! Tell the controller that we stoped to edit a text. For example,
       * when the focus is no more on a widget for text input. */
      static void stopEditingText();
      /*! \return if is actually editing a text */
      static bool isEditingText();

      /* \return pointer to current KeyboardTextEditor editing text */
      static KeyboardTextEditor* getEditor();

      /*! Update the keyboard by received events. Usually used for text
       * editing only.
       * \param event event received to treat. */
      static void updateByEvent(SDL_Event event);

   private:
      static const Uint8 *keys;   /**< current keyboard state */
      static KeyboardTextEditor* editor; /**< Current editor */
      static Uint32 lastKeyCheck;/**< Last ticks when checked keys for editor */
};

}

#endif

#endif


