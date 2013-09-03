Tranquility
======================
Tranquility is a personal project engine to be used as the core of both future games and tools.

Compilation
-----------------
Currently, the build system for this engine is incomplete, as I have limited time to work and would rather spend it adding and polishing features in the engine.  However if you are interested in building it, you will need the following dependencies:  

 * **SDL 2** - os abstraction layer
 * **GLM 0.9.4** - standard math library
 * **ImageMagick++ 6.8** - used to enable broad file support for texture loading
 * **Assimp 3** - used to enable broad file support for asset loading  
 * **GLEW 1.10** - typical OpenGL extension loading support  

I will attempt to get a working CMake configuration file set up in the next few days, but no promises.

File Structure
-------------------
The file structure of the engine is as follows  (subject to change)
 
 * **Config** - directory for configuration files (other can be elsewhere, but must be specified in the config.xml file)
 * **Engine** - main source directory
 * **Models** - default directory for the test models (configurable in config.xml)
 * **Shaders** - default directory for GLSL shaders (configurable in config.xml)
