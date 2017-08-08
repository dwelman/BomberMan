#pragma once

//External
#include <GL/glew.h>
#ifdef  _WIN32
# include <Windows.h>
#include <gl/glu.h>
#endif 
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

//Standard
#include <iostream>

//Internal
#include "MenuStateMachine.hpp"
#include <RenderEngine.hpp>
#include <ConfigEditor.hpp>


void	startGUI(SDL_Window *win);

int     draw(SDL_Window *window, renderData rdata);


static ConfigEditor g_cfg("resources/settings.cfg");
