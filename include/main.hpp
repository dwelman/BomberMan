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


//Standard
#include <iostream>

//Internal
#include "MenuStateMachine.hpp"
#include <RenderEngine.hpp>
#include <ConfigEditor.hpp>
#include <Util.hpp>
#include "GameObjectRenderInfo.hpp"

enum    ePlayerAction
{
    P_NOACTION = 0,
    P_MOVE_UP,
    P_MOVE_LEFT,
    P_MOVE_RIGHT,
    P_MOVE_DOWN,
    P_PLACE_BOMB
};

static ConfigEditor g_cfg("resources/settings.cfg");

void            mapKeyTextToSDLKey(std::map<std::string, SDL_Keycode> &textToKeyCode);

SDL_Keycode     GetKeyCodesFromConfig(std::map<std::string, SDL_Keycode> &textToKeyCode, std::map<ePlayerAction, SDL_Keycode > &actionToKeyCode ,ConfigEditor &cfg);

ePlayerAction   GetPlayerAction(SDL_KeyboardEvent &e);