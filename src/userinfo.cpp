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

#include "userinfo.h"
#include "platform.h"

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_WINDOWS
   #include <windows.h>
#elif KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS
   #include <pwd.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/stat.h>
#else
   #include <sys/stat.h>
#endif

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_WINDOWS && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
   #include <arpa/inet.h>
   #include <ifaddrs.h>
   #include <netdb.h>
#endif

using namespace Kobold;

/****************************************************************
 *                      getValuesFromSystem                     *
 ****************************************************************/
void UserInfo::getValuesFromSystem(const Kobold::String& packageName,
      const Kobold::String& userHomePath)
{
   #if KOBOLD_PLATFORM == KOBOLD_PLATFORM_WINDOWS
      language = "en";
      char buffer[512];
      DWORD bufSize = sizeof(buffer);

      /* Try to define windows user�s name */
      if(GetUserName(&buffer[0], &bufSize))
      {
         userName = buffer;
      }
      else
      {
         userName = "Don Ramon";
      }
      
      /* Try to define windows user�s home */
      if(ExpandEnvironmentStrings("%USERPROFILE%",&buffer[0],512) != 0)
      {
          userHome = buffer;
          userHome += "/.";
          userHome += packageName;
          userHome += "/";
      }
      else
      {
         userHome = "./"; 
      }
      userTemp = "./";
   #elif KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS
         //TODO!
   #elif KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
      language = "en";
      /* Get all Current User's Info (so more clean, isn't it?) */
      struct passwd *info;
      info = getpwuid(getuid());
      userName = info->pw_name;
      userHome = info->pw_dir;

      #if KOBOLD_PLATFORM == KOBOLD_PLATFORM_MACOS
         userHome += "/Library/Application Support/";
      #else
         userHome += "/.";
      #endif

      userHome += packageName;
      userHome += "/";
      userTemp = "/tmp/";
   #else 
      //ANDROID
      /* Home and temp were defined externally from Java code. */
      language = "en";
      userName = "androidUser";
   #endif

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
   if(userHomePath != "")
   {
#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_APPLE_IOS
      /* Remove file::// */
      userHomePath.erase(0,7);
#endif
      userHome = userHomePath;
   }
#endif
   
   /* Verify if both dirs ended with '/' */
   if(!Kobold::StringUtil::endsWith(userHome, '/'))
   {
      userHome += "/";
   }
   if(!Kobold::StringUtil::endsWith(userTemp, '/'))
   {
      userTemp += "/";
   }
   
   /* Put the language lowercase */
   language = Kobold::StringUtil::toLowerCase(language);

   /* Create directories */
   createDirectories();
   
   /* Get all valid ips associated with interfaces. */
   getIPs();
}

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_ANDROID
/****************************************************************
 *                   setAndroidDirectories                      *
 ****************************************************************/
void UserInfo::setAndroidDirectories(JNIEnv* env, jstring home, jstring cache)
{
  const char* h = env->GetStringUTFChars(home, NULL);
  userHome = Kobold::String(h);
  env->ReleaseStringUTFChars(home, h);
  
  const char* t = env->GetStringUTFChars(cache, NULL);
  userTemp = Kobold::String(t);
  env->ReleaseStringUTFChars(cache, t);
}
#endif

/****************************************************************
 *                     createDirectories                        *
 ****************************************************************/
void UserInfo::createDirectories()
{
   #if KOBOLD_PLATFORM == KOBOLD_PLATFORM_WINDOWS
      CreateDirectory(getUserHome().c_str(),NULL);
      CreateDirectory(getSaveDirectory().c_str(), NULL);
      CreateDirectory(getCacheDirectory().c_str(), NULL);
   #else
      #if KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
         mkdir(getUserHome().c_str(),0755);
         mkdir(getCacheDirectory().c_str(), 0755);
      #endif
      mkdir(getSaveDirectory().c_str(), 0755);
   #endif
}

/****************************************************************
 *                          getIPs()                            *
 ****************************************************************/
void UserInfo::getIPs()
{
   /* Based on example code from getifaddrs man page. */
#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_WINDOWS && \
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
   struct ifaddrs *ifaddr, *ifa;
   int family;
   char host[NI_MAXHOST];
   Kobold::String curIp;
   
   if(getifaddrs(&ifaddr) == -1)
   {
      return;
   }
      
   /* Walk through linked list, maintaining head pointer so we
      can free list later */
   for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
   {
      if(ifa->ifa_addr == NULL)
      {
         continue;
      }
      family = ifa->ifa_addr->sa_family;
      
      /* FIXME: ignoring IPv6 interfaces for now. */
      if(family == AF_INET)
      {
         if(getnameinfo(ifa->ifa_addr,
                         (family == AF_INET) ? sizeof(struct sockaddr_in) :
                         sizeof(struct sockaddr_in6),
                         host, NI_MAXHOST,
                         NULL, 0, NI_NUMERICHOST) != 0)
         {
            /* Failed to get name */
            return;
         }
         curIp = host;
         if(curIp != "127.0.0.1")
         {
            if(ips != "")
            {
               ips += "|";
            }
            ips += host;
         }
      }
   }
   
   freeifaddrs(ifaddr);
#endif
}

/****************************************************************
 *                        getUserName                           *
 ****************************************************************/
const Kobold::String& UserInfo::getUserName()
{
   return userName;
}

/****************************************************************
 *                        getUserHome                           *
 ****************************************************************/
const Kobold::String& UserInfo::getUserHome()
{
   return userHome;
}

/****************************************************************
 *                     getSavesDirectory                        *
 ****************************************************************/
const Kobold::String UserInfo::getSaveDirectory()
{
   return (userHome + "saves/");
}


/****************************************************************
 *                     getCacheDirectory                        *
 ****************************************************************/
const Kobold::String& UserInfo::getCacheDirectory()
{
   return userTemp;
}

/****************************************************************
 *                      getTempDirectory                        *
 ****************************************************************/
const Kobold::String& UserInfo::getTempDirectory()
{
   return userTemp;
}

/****************************************************************
 *                        getLanguage                           *
 ****************************************************************/
const Kobold::String& UserInfo::getLanguage()
{
   return language;
}

/****************************************************************
 *                        getLanguage                           *
 ****************************************************************/
const Kobold::String& UserInfo::getIpAddress()
{
   if(ips == "")
   {
      /* No ips got since, must try to get them again. */
      getIPs();
   }
   return ips;
}

//
//
////////Static Vars///////
//
//

Kobold::String UserInfo::userName;
Kobold::String UserInfo::userHome;
Kobold::String UserInfo::userTemp;
Kobold::String UserInfo::language;
Kobold::String UserInfo::ips = "";

