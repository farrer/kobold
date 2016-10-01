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

#ifndef _kobold_platform_h
#define _kobold_platform_h

#include "koboldconfig.h"

#define KOBOLD_PLATFORM_LINUX       1
#define KOBOLD_PLATFORM_WINDOWS     2
#define KOBOLD_PLATFORM_MACOS       3
#define KOBOLD_PLATFORM_IOS         4
#define KOBOLD_PLATFORM_ANDROID     5

/* Check platform */
#if (defined( __WIN32__ ) || defined( _WIN32 )) && !defined(__ANDROID__)
   /* Windows */
   #define KOBOLD_PLATFORM KOBOLD_PLATFORM_WINDOWS
#elif defined( __APPLE_CC__)
   #if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 60000 || \
       __IPHONE_OS_VERSION_MIN_REQUIRED >= 60000
      /* IOS */
      #define KOBOLD_PLATFORM KOBOLD_PLATFORM_IOS
   #else
      /* MacOS */
      #define KOBOLD_PLATFORM KOBOLD_PLATFORM_MACOS
   #endif
#elif defined(__ANDROID__)
   /* Android */
   #define KOBOLD_PLATFORM KOBOLD_PLATFORM_ANDROID
#else
   /* Must be unix-like */
   #define KOBOLD_PLATFORM KOBOLD_PLATFORM_LINUX
#endif

#endif

