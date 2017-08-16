//
// Created by Dean duToit on 2017/08/16.
//

#include <main.hpp>

void            mapKeyTextToSDLKey(std::map<std::string, SDL_Keycode> &textToKeyCode)
{
    textToKeyCode["SDLK_1"] = SDLK_1;
    textToKeyCode["SDLK_2"] = SDLK_2;
    textToKeyCode["SDLK_3"] = SDLK_3;
    textToKeyCode["SDLK_4"] = SDLK_4;
    textToKeyCode["SDLK_5"] = SDLK_5;
    textToKeyCode["SDLK_6"] = SDLK_6;
    textToKeyCode["SDLK_7"] = SDLK_7;
    textToKeyCode["SDLK_8"] = SDLK_8;
    textToKeyCode["SDLK_9"] = SDLK_9;
    textToKeyCode["SDLK_0"] = SDLK_0;
    textToKeyCode["SDLK_q"] = SDLK_q;
    textToKeyCode["SDLK_w"] = SDLK_w;
    textToKeyCode["SDLK_e"] = SDLK_e;
    textToKeyCode["SDLK_r"] = SDLK_r;
    textToKeyCode["SDLK_t"] = SDLK_t;
    textToKeyCode["SDLK_y"] = SDLK_y;
    textToKeyCode["SDLK_u"] = SDLK_u;
    textToKeyCode["SDLK_i"] = SDLK_i;
    textToKeyCode["SDLK_o"] = SDLK_o;
    textToKeyCode["SDLK_p"] = SDLK_p;
    textToKeyCode["SDLK_a"] = SDLK_a;
    textToKeyCode["SDLK_d"] = SDLK_d;
    textToKeyCode["SDLK_f"] = SDLK_f;
    textToKeyCode["SDLK_g"] = SDLK_g;
    textToKeyCode["SDLK_h"] = SDLK_h;
    textToKeyCode["SDLK_j"] = SDLK_j;
    textToKeyCode["SDLK_k"] = SDLK_k;
    textToKeyCode["SDLK_l"] = SDLK_l;
    textToKeyCode["SDLK_z"] = SDLK_z;
    textToKeyCode["SDLK_x"] = SDLK_x;
    textToKeyCode["SDLK_c"] = SDLK_c;
    textToKeyCode["SDLK_v"] = SDLK_v;
    textToKeyCode["SDLK_b"] = SDLK_b;
    textToKeyCode["SDLK_n"] = SDLK_n;
    textToKeyCode["SDLK_m"] = SDLK_m;
    textToKeyCode["SDLK_COMMA"] = SDLK_COMMA;
    textToKeyCode["SDLK_PERIOD"] = SDLK_PERIOD;
    textToKeyCode["SDLK_SLASH"] = SDLK_SLASH;
    textToKeyCode["SDLK_BACKSLASH"] = SDLK_BACKSLASH;
    textToKeyCode["SDLK_MINUS"] = SDLK_MINUS;
    textToKeyCode["SDLK_EQUALS"] = SDLK_EQUALS;
    textToKeyCode["SDLK_SEMICOLON"] = SDLK_SEMICOLON;
    textToKeyCode["SDLK_LEFTBRACKET"] = SDLK_LEFTBRACKET;
    textToKeyCode["SDLK_RIGHTBRACKET"] = SDLK_RIGHTBRACKET;
    textToKeyCode["SDLK_QUOTE"] = SDLK_QUOTE;
    textToKeyCode["SDLK_BACKQUOTE"] = SDLK_BACKQUOTE;
    textToKeyCode["SDLK_RETURN"] = SDLK_RETURN;
    textToKeyCode["SDLK_SPACE"] = SDLK_SPACE;
    textToKeyCode["SDLK_BACKSPACE"] = SDLK_BACKSPACE;
    textToKeyCode["SDLK_TAB"] = SDLK_TAB;
    textToKeyCode["SDLK_ESCAPE"] = SDLK_ESCAPE;
    textToKeyCode["SDLK_PAUSE"] = SDLK_PAUSE;
    textToKeyCode["SDLK_SYSREQ"] = SDLK_SYSREQ;
    textToKeyCode["SDLK_POWER"] = SDLK_POWER;
    textToKeyCode["SDLK_NUMLOCKCLEAR"] = SDLK_NUMLOCKCLEAR;
    textToKeyCode["SDLK_SCROLLLOCK"] = SDLK_SCROLLLOCK;
    textToKeyCode["SDLK_F1"] = SDLK_F1;
    textToKeyCode["SDLK_F2"] = SDLK_F2;
    textToKeyCode["SDLK_F3"] = SDLK_F3;
    textToKeyCode["SDLK_F4"] = SDLK_F4;
    textToKeyCode["SDLK_F5"] = SDLK_F5;
    textToKeyCode["SDLK_F6"] = SDLK_F6;
    textToKeyCode["SDLK_F7"] = SDLK_F7;
    textToKeyCode["SDLK_F8"] = SDLK_F8;
    textToKeyCode["SDLK_F9"] = SDLK_F9;
    textToKeyCode["SDLK_F10"] = SDLK_F10;
    textToKeyCode["SDLK_F11"] = SDLK_F11;
    textToKeyCode["SDLK_F12"] = SDLK_F12;
    textToKeyCode["SDLK_F13"] = SDLK_F13;
    textToKeyCode["SDLK_F14"] = SDLK_F14;
    textToKeyCode["SDLK_F15"] = SDLK_F15;
    textToKeyCode["SDLK_LCTRL"] = SDLK_LCTRL;
    textToKeyCode["SDLK_LALT"] = SDLK_LALT;
    textToKeyCode["SDLK_LSHIFT"] = SDLK_LSHIFT;
    textToKeyCode["SDLK_LGUI"] = SDLK_LGUI;
    textToKeyCode["SDLK_RCTRL"] = SDLK_RCTRL;
    textToKeyCode["SDLK_RALT"] = SDLK_RALT;
    textToKeyCode["SDLK_RSHIFT"] = SDLK_RSHIFT;
    textToKeyCode["SDLK_RGUI"] = SDLK_RGUI;
    textToKeyCode["SDLK_MENU"] = SDLK_MENU;
    textToKeyCode["SDLK_KP_0"] = SDLK_KP_0;
    textToKeyCode["SDLK_KP_1"] = SDLK_KP_1;
    textToKeyCode["SDLK_KP_2"] = SDLK_KP_2;
    textToKeyCode["SDLK_KP_3"] = SDLK_KP_3;
    textToKeyCode["SDLK_KP_4"] = SDLK_KP_4;
    textToKeyCode["SDLK_KP_5"] = SDLK_KP_5;
    textToKeyCode["SDLK_KP_6"] = SDLK_KP_6;
    textToKeyCode["SDLK_KP_7"] = SDLK_KP_7;
    textToKeyCode["SDLK_KP_8"] = SDLK_KP_8;
    textToKeyCode["SDLK_KP_9"] = SDLK_KP_9;
    textToKeyCode["SDLK_KP_PERIOD"] = SDLK_KP_PERIOD;
    textToKeyCode["SDLK_KP_PLUS"] = SDLK_KP_PLUS;
    textToKeyCode["SDLK_KP_MINUS"] = SDLK_KP_MINUS;
    textToKeyCode["SDLK_KP_MULTIPLY"] = SDLK_KP_MULTIPLY;
    textToKeyCode["SDLK_KP_DIVIDE"] = SDLK_KP_DIVIDE;
    textToKeyCode["SDLK_KP_ENTER"] = SDLK_KP_ENTER;
    textToKeyCode["SDLK_UP"] = SDLK_UP;
    textToKeyCode["SDLK_LEFT"] = SDLK_LEFT;
    textToKeyCode["SDLK_RIGHT"] = SDLK_RIGHT;
    textToKeyCode["SDLK_DOWN"] = SDLK_DOWN;
    textToKeyCode["SDLK_HOME"] = SDLK_HOME;
    textToKeyCode["SDLK_END"] = SDLK_END;
    textToKeyCode["SDLK_PAGEUP"] = SDLK_PAGEUP;
    textToKeyCode["SDLK_PAGEDOWN"] = SDLK_PAGEDOWN;
    textToKeyCode["SDLK_INSERT"] = SDLK_INSERT;
    textToKeyCode["SDLK_DELETE"] = SDLK_DELETE;
}

void	mapActionToKey(	std::map<std::string, SDL_Keycode> &textToKeyCode,
						std::map<ePlayerAction, SDL_Keycode > &actionToKeyCode,
						ConfigEditor &cfg, 
						ePlayerAction action, 
						std::string actionString, 
						SDL_Keycode defaultKey)
{
	if (cfg[actionString].ref.size() > 0)
	{
		SDL_Keycode key = textToKeyCode[cfg[actionString].to_str()];
		actionToKeyCode[action] = key;
	}
	else
		actionToKeyCode[action] = defaultKey;
}

void     GetKeyCodesFromConfig(	std::map<std::string,SDL_Keycode> &textToKeyCode, 
								std::map<ePlayerAction, SDL_Keycode > &actionToKeyCode,
								ConfigEditor &cfg)
{
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg,	P_MOVE_DOWN, "P_MOVE_DOWN", SDLK_DOWN);
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg, P_MOVE_UP, "P_MOVE_UP", SDLK_UP);
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg, P_MOVE_LEFT, "P_MOVE_LEFT", SDLK_LEFT);
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg, P_MOVE_RIGHT, "P_MOVE_RIGHT", SDLK_RIGHT);
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg, P_PLACE_BOMB, "P_PLACE_BOMB", SDLK_SPACE);
	mapActionToKey(textToKeyCode, actionToKeyCode, cfg, P_PAUSE_GAME, "P_PAUSE_GAME", SDLK_ESCAPE);
}

ePlayerAction   GetPlayerAction(SDL_KeyboardEvent &e)
{
	return (P_NOACTION);
}