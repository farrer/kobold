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

#ifndef _kobold_iad_view_h
#define _kobold_iad_view_h

#import <UIKit/UIKit.h>
#import <iAd/iAd.h>
#import <iAd/ADBannerView.h>

@interface iAdViewController : UIViewController<ADBannerViewDelegate>
{
   ADBannerView* adView; /**< The view related to the ads */
   UIView* pView;        /**< the pointer to the ogre UIVIew */
   bool isVisible;       /**< If the iAdView is currently visible or not. */
   bool showAtScreenTop; /**< If defined to display at screen top or bottom */
}

/*! Create the banner view as portrait mode
 * \param ogreView pointer to the UIView used by ogre window. */
- (void)loadBannerView:(UIView*) ogreView;
/*! Create the banner view as landscape mode
 * \param ogreView pointer to the UIView used by ogre window. */
- (void)loadLandscapeBannerView:(UIView*) ogreView;

@end

@implementation iAdViewController;

/********************************************************************
 *                           loadBannerView                         *
 ********************************************************************/
- (void)loadBannerView:(UIView*) ogreView
{
   pView = ogreView;
   adView = [[ADBannerView alloc] initWithFrame:CGRectZero];
   adView.delegate = self;
   isVisible = false;
   showAtScreenTop = true;
}

/********************************************************************
 *                      loadLandscapeBannerView                     *
 ********************************************************************/
-(void)loadLandscapeBannerView:(UIView*) ogreView
{
   pView = ogreView;
   adView = [[ADBannerView alloc] initWithFrame:CGRectMake(0.0,0.0,ogreView.frame.size.width,0.0)];
   adView.delegate = self;
   showAtScreenTop = false;
   isVisible = false;
   
   /* Set it to the screen bottom. */
   CGRect frame = adView.frame;
   frame.origin.y = ogreView.frame.size.height-frame.size.height;
   frame.origin.x = 0.0f;
   adView.frame = frame;
}

/********************************************************************
 *                      didReceiveMemoryWarning                     *
 ********************************************************************/
- (void)didReceiveMemoryWarning
{
   [super didReceiveMemoryWarning];
}

/********************************************************************
 *                        bannerViewDidLoadAd                       *
 ********************************************************************/
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
   if(!isVisible)
   {
      /* If banner isn't part of view hierarchy, add it */
      if(adView.superview == nil)
      {
         [pView addSubview:adView];
      }
      
      [UIView beginAnimations:@"animateAdBannerOn" context:NULL];
      
      /* Set the banner position to be visible */
      banner.frame = CGRectOffset(banner.frame, 0, 0);
      
      [UIView commitAnimations];
      
      isVisible = true;
   }
}

/********************************************************************
 *                      loadLandscapeBannerView                     *
 ********************************************************************/
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
   NSLog(@"Banner view is beginning an ad action");
   /* TODO: must pause application. */
   return YES;
}

/********************************************************************
 *                      loadLandscapeBannerView                     *
 ********************************************************************/
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
   NSLog(@"Failed to retrieve ad");
   if(isVisible)
   {
      [UIView beginAnimations:@"animateAdBannerOff" context:NULL];
      
      /* Set the banner framw to an area not visible */
      if(showAtScreenTop)
      {
         banner.frame = CGRectOffset(banner.frame, 0, -banner.frame.size.height);
      }
      else
      {
         banner.frame = CGRectOffset(banner.frame, 0, banner.frame.size.height);
      }
      
      [UIView commitAnimations];
      
      isVisible = false;
   }
}

@end

#endif
