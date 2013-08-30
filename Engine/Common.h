#ifndef _TRILLEK_COMMON_H_
#define _TRILLEK_COMMON_H_

//#define _HAS_ITERATOR_DEBUGGING  0
//#define _SECURE_SCL 0

// GLEW Includes
#include <GL\glew.h>

// SDL Includes
#define NO_SDL_GLEXT
#include "SDL.h"
#include "SDL_opengl.h"

// GLM Includes
#include "glm.hpp"
#include "ext.hpp"

#define INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xFFFFFFFF

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cctype>
#include <condition_variable>
#include <exception>
#include <float.h>
#include <fstream>
#include <functional>
#include <future>
#include <iosfwd>
#include <iostream>
#include <locale>
#include <map>
#include <math.h>
#include <memory>
#include <mmsystem.h>
#include <mutex>
#include <pdh.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#endif