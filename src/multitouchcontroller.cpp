/*
 Kobold - Multiplatform Game Utility Library
 Copyright (C) DNTeam <goblin@dnteam.org>
 
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

#include "multitouchcontroller.h"
#include "log.h"

#if KOBOLD_HAS_OGRE == 1
   #include <OGRE/OgreMath.h>
#else
   #include <stdlib.h>
#endif

using namespace Kobold;

/**************************************************************************
 *                                                                        *
 *                              TouchInfo                                 *
 *                                                                        *
 **************************************************************************/


TouchInfo& TouchInfo::operator=(TouchInfo t)
{
   this->state = t.state;
   this->x = t.x;
   this->y = t.y;
   this->prevX = t.prevX;
   this->prevY = t.prevY;

   return *this;
}

bool TouchInfo::equalPosition(TouchInfo t)
{
   return (this->x == t.x) && (this->y == t.y);
}

/**************************************************************************
 *                                                                        *
 *                                 TouchesList                            *
 *                                                                        *
 **************************************************************************/

/********************************************************************
 *                           Constructor                            *
 ********************************************************************/
TouchesList::TouchesList():Kobold::List(Kobold::LIST_TYPE_ADD_AT_END)
{
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/
TouchesList::~TouchesList()
{
   clear();
}

/********************************************************************
 *                            getTouch                              *
 ********************************************************************/
Touch* TouchesList::getTouch(int x, int y)
{
   int i;
   Touch* t = (Touch*)first;
   
   for(i=0; i < total; i++)
   {
      if( (t->info.x == x) && (t->info.y == y) )
      {
         return t;
      }
      t = (Touch*)t->getNext();
   }
   return NULL;
}

/**************************************************************************
 *                                                                        *
 *                        multitouchesController                          *
 *                                                                        *
 **************************************************************************/

/********************************************************************
 *                               init                               *
 ********************************************************************/
void MultiTouchController::init(int scaleFactor)
{
   if(touches)
   {
      finish();
   }
   scale = scaleFactor;
   orientation = Kobold::ORIENTATION_DEGREE_0;
   touches = new TouchesList();
   pthread_mutex_init(&mutex, NULL);
}

/********************************************************************
 *                          setOrientation                          *
 ********************************************************************/
void MultiTouchController::setOrientation(ViewOrientation ori, int w, int h)
{
   orientation = ori;
   width = w;
   height = h;
}

/********************************************************************
 *                             finish                               *
 ********************************************************************/
void MultiTouchController::finish()
{
   if(touches)
   {
      delete touches;
   }
   pthread_mutex_destroy(&mutex);
}

/********************************************************************
 *                         convertOrientation                       *
 ********************************************************************/
void MultiTouchController::convertOrientation(int& x, int& y)
{
   int prvX = x;
   int prvY = y;
   switch(orientation)
   {
      case Kobold::ORIENTATION_DEGREE_0:
      break;
      case Kobold::ORIENTATION_DEGREE_90:
         x = width - prvY;
         y = prvX;
      break;
      case Kobold::ORIENTATION_DEGREE_180:
         x = width - prvX;
         y = height - prvY;
      break;
      case Kobold::ORIENTATION_DEGREE_270:
         x = prvY;
         y = height - prvX;
      break;
   }
}

/********************************************************************
 *                             touchBegan                           *
 ********************************************************************/
void MultiTouchController::touchBegan(int x, int y)
{
   convertOrientation(x, y);
   
   x *= scale;
   y *= scale;
   
   pthread_mutex_lock(&mutex);
   
   /* Create new touch */
   Touch* t = new Touch();
   touches->insert(t);

   /* Set touch values */
   t->info.prevX = -1;
   t->info.prevY = -1;
   t->info.x = x;
   t->info.y = y;
   t->info.state = TOUCH_PRESSING;

   pthread_mutex_unlock(&mutex);
}

/********************************************************************
 *                             touchMoved                           *
 ********************************************************************/
void MultiTouchController::touchMoved(int prevX, int prevY, int x, int y)
{
   convertOrientation(prevX, prevY);
   prevX *= scale;
   prevY *= scale;
   convertOrientation(x, y);
   x *= scale;
   y *= scale;
   
   /* Search for the touch on the list */ 
   pthread_mutex_lock(&mutex);
   Touch* t = touches->getTouch(prevX, prevY);
   if(t)
   {
      t->info.prevX = prevX;
      t->info.prevY = prevY;
      t->info.x = x;
      t->info.y = y;
      
      /* Avoid receive "move" state within a minimun variation */
#if KOBOLD_HAS_OGRE == 1
      if((Ogre::Math::Abs(x-prevX) > 2.0f) ||
         (Ogre::Math::Abs(y-prevY) > 2.0f) )
#else
      if((abs(x - prevX) > 2) || (abs(y - prevY) > 2) )
#endif
      {
         t->info.state = TOUCH_MOVED;
      }
      else
      {
         t->info.state = TOUCH_PRESSING;
      }
   }
   else
   {
      /* Couldn't find touch!!!! */
      Log::add(Log::LOG_LEVEL_ERROR, "Couldn't find (move): %d %d", 
            prevX, prevY);
   }
   pthread_mutex_unlock(&mutex);
}

/********************************************************************
 *                             touchEnded                           *
 ********************************************************************/
void MultiTouchController::touchEnded(int prevX, int prevY, int x, int y)
{
   convertOrientation(prevX, prevY);
   prevX *= scale;
   prevY *= scale;
   convertOrientation(x, y);
   x *= scale;
   y *= scale;

   /* Search for the touch on the list (with previous, as the IOS, bizounsly,
    * sometimes changes the current a little when touchEnded after a move) */ 
   pthread_mutex_lock(&mutex);
   Touch* t = touches->getTouch(prevX,prevY);
   if(t)
   {
      t->info.state = TOUCH_RELEASED;
   }
   else
   {
      t = touches->getTouch(x, y);
      if(t)
      {
         t->info.state = TOUCH_RELEASED;
      }
      else
      {
         Log::add(Log::LOG_LEVEL_ERROR, "Really couldn't find\n");
      }
   }
   pthread_mutex_unlock(&mutex);
}

/********************************************************************
 *                           touchCanceled                          *
 ********************************************************************/
void MultiTouchController::touchCanceled(int x, int y)
{
   convertOrientation(x, y);
   x *= scale;
   y *= scale;
   
   /* Search for the touch on the list */ 
   pthread_mutex_lock(&mutex);
   Touch* t = touches->getTouch(x,y);
   if(t)
   {
      touches->remove(t);
   }
   else
   {
      /* Couldn't find touch!!!! */
      Log::add(Log::LOG_LEVEL_ERROR, "Couldn't find (canceled): %d %d", x, y);
   }
   pthread_mutex_unlock(&mutex);
}

/********************************************************************
 *                            totalTouches                          *
 ********************************************************************/
int MultiTouchController::totalTouches()
{
   return curTotalTouches;
}

/********************************************************************
 *                               update                             *
 ********************************************************************/
void MultiTouchController::update()
{
   pthread_mutex_lock(&mutex);
   
   curTotalTouches = touches->getTotal();
   if(touches->getTotal() > 0)
   {
      /* Copy info to 'public' vector.  */
      Touch* curTouch = (Touch*) touches->getFirst();
      for(int i = 0; i < touches->getTotal(); i++)
      {
         threatTouches[i] = curTouch->info;
         curTouch = (Touch*) curTouch->getNext();
      }

      clearStates();
   }

   pthread_mutex_unlock(&mutex);
}

/********************************************************************
 *                            clearStates                           *
 ********************************************************************/
void MultiTouchController::clearStates()
{
   Touch* aux;
   Touch* t;
   
   if(touches->getTotal() == 0)
   {
      /* No touches, do nothing */
      return;
   }
   t = (Touch*)touches->getFirst();
   
   do 
   {
      aux = t;
      t = (Touch*)t->getNext();
      if(aux->info.state == TOUCH_RELEASED)
      {
         /* Released: no more touch. */
         touches->remove(aux);
      }
   }while( (touches->getTotal() > 0) && (t != (Touch*)touches->getFirst()));
}

/********************************************************************
 *                              getTouch                            *
 ********************************************************************/
void MultiTouchController::getTouch(int n, TouchInfo& retInfo)
{
   if(n >= totalTouches())
   {
      retInfo.state = TOUCH_NONE;
      return;
   }
   
   retInfo = threatTouches[n];
}

TouchesList* MultiTouchController::touches = NULL;
ViewOrientation MultiTouchController::orientation=Kobold::ORIENTATION_DEGREE_0;
int MultiTouchController::scale = 1;
int MultiTouchController::width = 0;
int MultiTouchController::height = 0;
pthread_mutex_t MultiTouchController::mutex;
int MultiTouchController::curTotalTouches = 0;
TouchInfo MultiTouchController::threatTouches[MAX_TOUCHES_TO_THREAT];

