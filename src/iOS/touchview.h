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

#ifndef _kobold_touch_view_h
#define _kobold_touch_view_h

#include "multitouchcontroller.h"

#ifdef __OBJC__

/*! View for receiveing touches in iOS and converting them to Kobold's 
 * MultiTouchController Interface. */
@interface TouchView: UIView
{
}

@end

@implementation TouchView;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
   CGPoint point, prev;
   for(UITouch *touch in touches) 
   {
      point = [touch locationInView:self];
      Kobold::MultiTouchController::touchBegan(point.x, point.y);
   }
   
   /* HACK: Now remove all canceled or ended touches 
    *       It is to avoid non ended touches... ugly! */
   for(UITouch *touch in event.allTouches)
   {
      if( (touch.phase == UITouchPhaseEnded) ||
          (touch.phase == UITouchPhaseCancelled) )
      {
         point = [touch locationInView:self];
         prev = [touch previousLocationInView:self];
         Kobold::MultiTouchController::touchEnded(prev.x, prev.y, point.x, point.y);
      }
   }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
   CGPoint curLoc;
   CGPoint prevLoc;
   CGPoint point, prev;
   for(UITouch *touch in touches) 
   {
      curLoc = [touch locationInView:self];
      prevLoc = [touch previousLocationInView:self];
      Kobold::MultiTouchController::touchMoved(prevLoc.x, prevLoc.y, curLoc.x, curLoc.y);
   }
   
   /* HACK: Now remove all canceled or ended touches
    *       It is to avoid non ended touches... ugly! */
   for(UITouch *touch in event.allTouches)
   {
      if( (touch.phase == UITouchPhaseEnded) ||
         (touch.phase == UITouchPhaseCancelled) )
      {
         point = [touch locationInView:self];
         prev = [touch previousLocationInView:self];
         Kobold::MultiTouchController::touchEnded(prev.x, prev.y, point.x, point.y);
      }
   }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
   CGPoint point;
   CGPoint prev;
   for(UITouch *touch in touches) 
   {
      point = [touch locationInView:self];
      prev = [touch previousLocationInView:self];
      Kobold::MultiTouchController::touchEnded(prev.x, prev.y, point.x, point.y);
   }
}

- (void)touchesCanceled:(NSSet *)touches withEvent:(UIEvent *)event
{
   CGPoint point;
   for(UITouch *touch in touches) 
   {
      point = [touch locationInView:self];
      Kobold::MultiTouchController::touchCanceled(point.x, point.y);
   }
}

@end

#endif

#endif

