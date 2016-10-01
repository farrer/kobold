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

#ifndef _kobold_userinfo_h
#define _kobold_userinfo_h

#include "koboldconfig.h"
#include "platform.h"
#include "kstring.h"

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_ANDROID
   #include <jni.h>
#endif

namespace Kobold
{

/*! The User Info Class define the user name and home dir (where will save
 * all needed files like options, saves, etc) */
class UserInfo
{
   public:
      /*! Get all user info from the system.
       * \param packageName -> name of the package using Kobold
       * \param userHome path to user home. "" to check automatically.
       * \note -> this function is usually called at 
       *          the beggining of the program, a single time */
      static void getValuesFromSystem(Kobold::String packageName,
                               Kobold::String userHomePath="");

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_ANDROID
      /*! Define directories from JAVA android code
       * \param env JNI enviroment used
       * \param home directory where app will use to save files
       * \param cache diretory to save temporary files */
      static void setAndroidDirectories(JNIEnv* env, jstring home, 
            jstring cache);
#endif

      /*! Get The User Login Name */
      static Kobold::String getUserName();

      /*! Get the User Home */
      static Kobold::String getUserHome();

      /*! Get the Directory where will save user files */
      static Kobold::String getSaveDirectory();

      /*! Get the Directory where will save user cache files */
      static Kobold::String getCacheDirectory();
   
      /*! Get the Directory where will save user temporary files */
      static Kobold::String getTempDirectory();
   
      /*! Get the system language */
      static Kobold::String getLanguage();
   
      /*! Get '|' separated list of valid IP address of the current system. */
      static Kobold::String getIpAddress();


   private:
      /* Avoid instances */
      UserInfo(){};

      /*! Create directories, if they aren't found */
      static void createDirectories();
   
      /*! Get the list of valid IP addresses.  */
      static void getIPs();

      static Kobold::String userName;    /**< The User Name */
      static Kobold::String userHome;    /**< The User Home */
      static Kobold::String userTemp;    /**< The User temporary folder */
      static Kobold::String language;    /**< Current language */
      static Kobold::String ips; /**< Current IPs */
};

}

#endif

