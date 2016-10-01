# Kobold - A simple utilities library

## About
Kobold is a multiplatform simple collection of usefull codes for input, sound
and common algorithms used by DNTeam applications.

## License
Kobold is released under GNU Lesser General Public License v3.0 or later
[https://www.gnu.org/licenses/lgpl.html]

## Dependencies

 * SDL2 [https://libsdl.org/download-2.0.php]
 * OpenAL [http://kcat.strangesoft.net/openal.html]
 * Ogg [https://xiph.org/downloads/]
 * Vorbis [https://xiph.org/downloads/]
 * VorbisFile [https://xiph.org/downloads/]

### Optional
 * Ogre3D 1.10 [http://www.ogre3d.org/]

## Building

Usually, you build Kobold with the following commands (starting at projects
folder):

**mkdir** build  
**cd** build  
cmake ..  
make  
make install (or sudo make install)

### Building for Android

To build for android, the CMake command call must set the needed NDK variables:

cmake -DCMAKE\_TOOLCHAIN\_FILE=../CMakeModules/android.toolchain.cmake -DKOBOLD\_STATIC=True -DANDROID\_NDK=path\_to\_Android\_Ndk -DCMAKE\_BUILD\_TYPE=Release -DANDROID\_ABI="armeabi-v7a" -DANDROID\_NATIVE\_API\_LEVEL=12 ..

Change those parameters to your needs.

### Options

There are some options that could be passed to CMake script:

 * KOBOLD\_DEBUG -> Build the library with debugging symbols;
 * KOBOLD\_STATIC -> Build a .a static library, instead of the shared one.



