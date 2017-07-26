#pragma once

#ifdef  WIN32
# include <Windows.h>
#endif 

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <iostream>


void	startGUI(SDL_Window *win);