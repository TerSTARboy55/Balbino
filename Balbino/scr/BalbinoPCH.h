#pragma once

#ifndef _DEBUG
#include "gl3w/GL/gl3w.h"
#endif // !_DEBUG

// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib")  


#ifdef _DEBUG
#include "imgui-1.75/imgui.h"
#include "imgui-1.75/imgui_sdl.h"
#include "imgui-1.75/imgui_impl_sdl.h"
#include "imgui-1.75/imgui_impl_opengl3.h"
#include "imgui-1.75/imgui_extra.h"

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include "../gl3w/GL/gl3w.h"
#endif
#endif

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <string>
#include "Struct.h"

//#define WIN32_LEAN_AND_MEAN
#include <windows.h>