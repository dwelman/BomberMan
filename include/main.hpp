#pragma once


//External
#include <GL/glew.h>
#ifdef  _WIN32
# include <Windows.h>
# include <gl/glu.h>
# pragma comment(linker, "/STACK:100000000")
#endif 
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>


//Standard
#include <iostream>
#include <atomic>

//Internal
#include "MenuStateMachine.hpp"
#include <RenderEngine.hpp>
#include <ConfigEditor.hpp>
#include <Util.hpp>
#include <AudioManager.hpp>
#include "GameObjectRenderInfo.hpp"

enum    ePlayerAction
{
    P_NOACTION = 0,
    P_MOVE_UP,
    P_MOVE_LEFT,
    P_MOVE_RIGHT,
    P_MOVE_DOWN,
    P_PLACE_BOMB,
	P_PAUSE_GAME
};

static ConfigEditor g_cfg("resources/settings.cfg");


ePlayerAction   GetPlayerAction(SDL_KeyboardEvent &e);

int				AudioThread(void *ptr);