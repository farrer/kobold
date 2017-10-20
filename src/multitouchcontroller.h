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

#ifndef _kobold_multitouch_controller_h
#define _kobold_multitouch_controller_h

#include "koboldconfig.h"
#include "platform.h"

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS ||\
    KOBOLD_PLATFORM == KOBOLD_PLATFORM_ANDROID

#include "list.h"
#include <pthread.h>

namespace Kobold
{

#define TOUCH_NONE         -1    /**< No touch info */
#define TOUCH_PRESSING      0    /**< Finger pressing */
#define TOUCH_MOVED         1    /**< Finger moved */
#define TOUCH_RELEASED      2    /**< Finger released */
#define MAX_TOUCHES_TO_THREAT 8 /**< Maximun number of simultaneous fingers. */

/*! Possible orientation angles for current view */
enum ViewOrientation
{
   ORIENTATION_DEGREE_0,
   ORIENTATION_DEGREE_90,
   ORIENTATION_DEGREE_180,
   ORIENTATION_DEGREE_270
};

class TouchInfo
{
   public:
      TouchInfo& operator=(TouchInfo t);

      /*! Return if current touch position is the same of another touch.
       *  \param t -> touch to compare current position with this one. */
      bool equalPosition(TouchInfo t);

      int state;   /**< Current touch state constant */
      int prevX;   /**< Previous x position (when moved) */
      int prevY;   /**< Previous y position (when moved) */
      int x;       /**< Current x position */
      int y;       /**< Current y position */
};
   
/*! A single touch representation */
class Touch: public Kobold::ListElement
{
   public:
      TouchInfo info;
};

/*! A list of active touches */
class TouchesList: public Kobold::List
{
   public:
      /*! Constructor */
      TouchesList();
      /*! Destructor */
      ~TouchesList();

      /*! Get touch with current position (x,y)
       * \return pointer to found touch or NULL  */
      Touch* getTouch(int x, int y);
};

/*! The multitouch controller, receives input on a thread and usually treat
 * those on another thread.
 * \note Obviously, this static class is tread safe. */
class MultiTouchController
{
   public:
      /*! Init the use of the multitouch controller
       * \param scaleFactor when using retina display should be 2.
       *         Otherwise, just 1. */
      static void init(int scaleFactor);
      /*! finish the use of the multitouch controller */
      static void finish();
    
      /*! Update current touches to threat.
       * \note This functions is usually called once in a loop, before
       *       starting to init its threat.*/
      static void update();

      /*! Get total touches current active on controller */
      static int totalTouches();
   
      /*! Get n-th touch to threat on the controller */
      static void getTouch(int n, TouchInfo& retTouch);
   
      /*! Tell controller a new finger appears */
      static void touchBegan(int x, int y);
      /*! Tell controller a finger moved */
      static void touchMoved(int prevX, int prevY, int x, int y);
      /*! Tell controller a finger is released */
      static void touchEnded(int prevX, int prevY, int x, int y);
      /*! Tell controller that a touch have ended */
      static void touchCanceled(int x, int y);
   
      /*! Set current screen orientation angle to ori */
      static void setOrientation(ViewOrientation ori, int w, int h);

   protected:
      /*! Clear states */
      static void clearStates();

      /*! Convert Touch coordinate to screen orieantion */
      static void convertOrientation(int& x, int& y);

   private:
      /*! Instances aren't allowed. */
      MultiTouchController(){};
   
      static TouchesList* touches;/**< List of active touches (synchronized) */
      static ViewOrientation orientation;     /**< Current screen orientation */
      static int scale;           /**< Scale factor */
      static int width;
      static int height;

      static pthread_mutex_t mutex; /**< Our mutex. */
      static int curTotalTouches; /**< Current number of touches to treat */
      static TouchInfo threatTouches[MAX_TOUCHES_TO_THREAT]; /**< Touches */
};


}

#endif

#endif

