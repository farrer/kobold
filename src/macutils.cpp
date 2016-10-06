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

#include "platform.h"

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_MACOS || \
    KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS

#include "macutils.h"

#if KOBOLD_HAS_OGRE == 1 
   #if KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS
      #include <iOS/macUtils.h>
   #else
      #include <OGRE/OSX/macUtils.h>
   #endif
#else
   #include <CoreFoundation/CoreFoundation.h>
#endif

using namespace Kobold;

/**********************************************************************
 *                            macBundlePath                           *
 **********************************************************************/
Kobold::String macBundlePath()
{
#if KOBOLD_HAS_OGRE == 1
   return Ogre::macBundlePath(); 
#else
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();

    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath(mainBundleURL, 
                                                      kCFURLPOSIXPathStyle);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return Kobold::String(path);
#endif
}

#endif

