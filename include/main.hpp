#pragma once

#ifdef  WIN32
# include <Windows.h>
#include <gl/glu.h>
#endif 

//External
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
//#include <glu.h>
#include <glm/glm.hpp>
#include <iostream>

//Internal


void	startGUI(SDL_Window *win);

int     draw(SDL_Window *window);