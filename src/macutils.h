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

#ifndef _kobold_mac_utils_h
#define _kobold_mac_utils_h

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_MACOS || \
    KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS

#include "koboldconfig.h"
#include "platform.h"
#include "kstring.h"

namespace Kobold
{
   /*! Retrieve a the app bundle path */
   Kobold::String macBundlePath();
}

#endif

#endif

