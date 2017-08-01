#pragma once

//External
#include <GL/glew.h>
#ifdef  WIN32
# include <Windows.h>
#include <gl/glu.h>
#endif 
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <iostream>

//Internal
#include "MenuStateMachine.hpp"
#include <RenderEngine.hpp>
#include <ConfigEditor.hpp>

void	startGUI(SDL_Window *win);

int     draw(SDL_Window *window);