
cmake_minimum_required(VERSION 3.3)

# Define project and its current version
set(PACKAGE kobold)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
if(${VERSION_PATCH})
   set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
else(${VERSION_PATCH})
   set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
endif(${VERSION_PATCH})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

# Define some options
option(KOBOLD_STATIC "Static build" FALSE)
option(KOBOLD_DEBUG "Enable debug symbols" FALSE)

# Some compiler options
if(UNIX)
   if(${KOBOLD_DEBUG})
      add_definitions(-Wall -g)
   else(${KOBOLD_DEBUG})
      add_definitions(-Wall)
   endif(${KOBOLD_DEBUG})
endif(UNIX)

if(APPLE)
   set(KOBOLD_STATIC True)
   set(OGRE_STATIC True)
endif(APPLE)

# Find mandatory packages
if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
   set(KOBOLD_STATIC True)
   set(OGRE_STATIC True)
   set(ANDROID True)
   FIND_PACKAGE(Tremor REQUIRED)
   include_directories(${VORBISFILE_INCLUDE_DIR})
else(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
   FIND_PACKAGE(SDL2 REQUIRED)
   include_directories(${SDL2_INCLUDE_DIR})
   FIND_PACKAGE(Vorbis REQUIRED)
   include_directories(${VORBIS_INCLUDE_DIR})
   FIND_PACKAGE(Vorbisfile REQUIRED)
   include_directories(${VORBISFILE_INCLUDE_DIR})
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")

FIND_PACKAGE(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})
FIND_PACKAGE(Ogg REQUIRED)
include_directories(${OGG_INCLUDE_DIR})

# Find optional packages
FIND_PACKAGE(OGRE)
if(${OGRE_FOUND})
   include_directories(${OGRE_INCLUDE_DIR})
   set(KOBOLD_HAS_OGRE 1)
   if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
      include_directories(${OGRE_INCLUDE_DIR}/RenderSystems/GLES2/)
      include_directories(${OGRE_INCLUDE_DIR}/RenderSystems/GLES2/Android/)
   endif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
else(${OGRE_FOUND})
   set(KOBOLD_HAS_OGRE 0)
endif(${OGRE_FOUND})

# Include directories: src and the binary src (as generating config.h there)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

# Generate dynamic info
set(KOBOLD_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/koboldconfig.h)
configure_file("./src/koboldconfig.h.in" "./src/koboldconfig.h")

# Include headers and files
include(sources.cmake)

# Build the library with defined mode (static or shared)
if(${KOBOLD_STATIC})
   add_library(kobold ${KOBOLD_SOURCES} ${KOBOLD_HEADERS})
else(${KOBOLD_STATIC})
   add_library(kobold SHARED ${KOBOLD_SOURCES} ${KOBOLD_HEADERS} )
endif(${KOBOLD_STATIC})

set_target_properties(kobold PROPERTIES VERSION ${VERSION}
                             SOVERSION ${VERSION_MAJOR} )

# install the include files and created library.
install(FILES ${KOBOLD_CONFIG_FILE} DESTINATION include/kobold)
install(FILES ${KOBOLD_HEADERS} DESTINATION include/kobold)
install(TARGETS kobold DESTINATION lib)

message("\n**********************************************")
message("Kobold build: ")
if(${KOBOLD_STATIC})
   message("   Static library")
else(${KOBOLD_STATIC})
   message("   Shared library")
endif(${KOBOLD_STATIC})
message("**********************************************\n")

