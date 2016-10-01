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

Usually, you build Kobold with the following commands (starting at project's
folder):
---
**mkdir** build
**cd** build
cmake ..
make
---

### Options

There are some options that could be passed to CMake script:

 * KOBOLD\_DEBUG -> Build the library with debugging symbols;
 * KOBOLD\_STATIC -> Build a .a static library, instead of the shared one.



