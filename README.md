# GameEngineProgramming

# DEPENDENCIES
   1) Ogre 1.9
     <https://bitbucket.org/sinbad/ogre/src/108ab0bcc69603dba32c0ffd4bbbc39051f421c9/?at=v1-9>
   2) BASS 2.4
     <https://www.un4seen.com/>
   3) Crazy Eddie Graphic User Interface (CEGUI)
     <http://cegui.org.uk/>
   4) Lua 5.3
     <https://www.lua.org/>
   5) Lua Bridge
     <https://github.com/vinniefalco/LuaBridge>
   6) OIS
     <https://github.com/wgois/OIS>
   7) CMake for Ogre, CEGUI, and OIS.
     <https://cmake.org/>
   8) GCC 4.8 or newer (C++11)
     <https://gcc.gnu.org/>


#  How to Compile

 1)  Install and compile dependencies in a fashion which will allow them to link
     with GCC compilers.

 2)  Modify makefiles to point to header file locations for the dependencies and
     to library locations on your local system. 
     ** Makefiles are in the obj directories. **

 3)  Run make to compile source files into object files.

 4)  Run make install to create executable.


