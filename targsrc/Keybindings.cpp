//
// Created by Dean duToit on 2017/08/16.
//

#include <main.hpp>
#include <GUI.hpp>

void            mapSDLKeyToText( std::map<SDL_Keycode, std::string>	&keyCodeToText, std::map<std::string, SDL_Keycode> &textToKeyCode)
{
    auto end = textToKeyCode.end();
    for (auto it = textToKeyCode.begin(); it != end; it++)
    {
        keyCodeToText[it->second] = it->first;
    }
}

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

void            mapKeyName(std::map<SDL_Keycode, std::string> &keyName)
{
    keyName[SDLK_1] = "1";
    keyName[SDLK_2] = "2";
    keyName[SDLK_3] = "3";
    keyName[SDLK_4] = "4";
    keyName[SDLK_5] = "5";
    keyName[SDLK_6] = "6";
    keyName[SDLK_7] = "7";
    keyName[SDLK_8] = "8";
    keyName[SDLK_9] = "9";
    keyName[SDLK_0] = "0";
    keyName[SDLK_q] = "q";
    keyName[SDLK_w] = "w";
    keyName[SDLK_e] = "e";
    keyName[SDLK_r] = "r";
    keyName[SDLK_t] = "t";
    keyName[SDLK_y] = "y";
    keyName[SDLK_u] = "u";
    keyName[SDLK_i] = "i";
    keyName[SDLK_o] = "o";
    keyName[SDLK_p] = "p";
    keyName[SDLK_a] = "a";
    keyName[SDLK_d] = "d";
    keyName[SDLK_f] = "f";
    keyName[SDLK_g] = "g";
    keyName[SDLK_h] = "h";
    keyName[SDLK_j] = "j";
    keyName[SDLK_k] = "k";
    keyName[SDLK_l] = "l";
    keyName[SDLK_z] = "z";
    keyName[SDLK_x] = "x";
    keyName[SDLK_c] = "c";
    keyName[SDLK_v] = "v";
    keyName[SDLK_b] = "b";
    keyName[SDLK_n] = "n";
    keyName[SDLK_m] = "m";
    keyName[SDLK_COMMA] = "COMMA";
    keyName[SDLK_PERIOD] = "PERIOD";
    keyName[SDLK_SLASH] = "SLASH";
    keyName[SDLK_BACKSLASH] = "BACKSLASH";
    keyName[SDLK_MINUS] = "MINUS";
    keyName[SDLK_EQUALS] = "EQUALS";
    keyName[SDLK_SEMICOLON] = "SEMICOLON";
    keyName[SDLK_LEFTBRACKET] = "LEFTBRACKET";
    keyName[SDLK_RIGHTBRACKET] = "RIGHTBRACKET";
    keyName[SDLK_QUOTE] = "QUOTE";
    keyName[SDLK_BACKQUOTE] = "BACKQUOTE";
    keyName[SDLK_RETURN] = "RETURN";
    keyName[SDLK_SPACE] = "SPACE";
    keyName[SDLK_BACKSPACE] = "BACKSPACE";
    keyName[SDLK_TAB] = "TAB";
    keyName[SDLK_ESCAPE] = "ESCAPE";
    keyName[SDLK_PAUSE] = "PAUSE";
    keyName[SDLK_SYSREQ] = "SYSREQ";
    keyName[SDLK_POWER] = "POWER";
    keyName[SDLK_NUMLOCKCLEAR] = "NUMLOCKCLEAR";
    keyName[SDLK_SCROLLLOCK] = "SCROLLLOCK";
    keyName[SDLK_F1] = "F1";
    keyName[SDLK_F2] = "F2";
    keyName[SDLK_F3] = "F3";
    keyName[SDLK_F4] = "F4";
    keyName[SDLK_F5] = "F5";
    keyName[SDLK_F6] = "F6";
    keyName[SDLK_F7] = "F7";
    keyName[SDLK_F8] = "F8";
    keyName[SDLK_F9] = "F9";
    keyName[SDLK_F10] = "F10";
    keyName[SDLK_F11] = "F11";
    keyName[SDLK_F12] = "F12";
    keyName[SDLK_F13] = "F13";
    keyName[SDLK_F14] = "F14";
    keyName[SDLK_F15] = "F15";
    keyName[SDLK_LCTRL] = "LCTRL";
    keyName[SDLK_LALT] = "LALT";
    keyName[SDLK_LSHIFT] = "LSHIFT";
    keyName[SDLK_LGUI] = "LGUI";
    keyName[SDLK_RCTRL] = "RCTRL";
    keyName[SDLK_RALT] = "RALT";
    keyName[SDLK_RSHIFT] = "RSHIFT";
    keyName[SDLK_RGUI] = "RGUI";
    keyName[SDLK_MENU] = "MENU";
    keyName[SDLK_KP_0] = "Keypad  0";
    keyName[SDLK_KP_1] = "Keypad  1";
    keyName[SDLK_KP_2] = "Keypad  2";
    keyName[SDLK_KP_3] = "Keypad  3";
    keyName[SDLK_KP_4] = "Keypad  4";
    keyName[SDLK_KP_5] = "Keypad  5";
    keyName[SDLK_KP_6] = "Keypad  6";
    keyName[SDLK_KP_7] = "Keypad  7";
    keyName[SDLK_KP_8] = "Keypad  8";
    keyName[SDLK_KP_9] = "Keypad  9";
    keyName[SDLK_KP_PERIOD] = "KP_PERIOD";
    keyName[SDLK_KP_PLUS] = "KP_PLUS";
    keyName[SDLK_KP_MINUS] = "KP_MINUS";
    keyName[SDLK_KP_MULTIPLY] = "KP_MULTIPLY";
    keyName[SDLK_KP_DIVIDE] = "KP_DIVIDE";
    keyName[SDLK_KP_ENTER] = "KP_ENTER";
    keyName[SDLK_UP] = "UP ARROW";
    keyName[SDLK_LEFT] = "LEFT ARROW";
    keyName[SDLK_RIGHT] = "RIGHT ARROW";
    keyName[SDLK_DOWN] = "DOWN ARROW";
    keyName[SDLK_HOME] = "HOME";
    keyName[SDLK_END] = "END";
    keyName[SDLK_PAGEUP] = "PAGEUP";
    keyName[SDLK_PAGEDOWN] = "PAGEDOWN";
    keyName[SDLK_INSERT] = "INSERT";
    keyName[SDLK_DELETE] = "DELETE";
}


void	mapActionToKey(	std::map<std::string, SDL_Keycode> &textToKeyCode,
						std::map<ePlayerAction, SDL_Keycode > &actionToKeyCode,
						std::map<SDL_Keycode, std::string> &keyCodeToText,
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
	{
		actionToKeyCode[action] = defaultKey;
		g_cfg[actionString] = keyCodeToText[defaultKey];
		g_cfg.saveConfig();
	}
}

void     GetKeyCodesFromConfig(	std::map<std::string,SDL_Keycode> &textToKeyCode, 
								std::map<ePlayerAction, SDL_Keycode > &actionToKeyCode,
								std::map<SDL_Keycode, std::string> &keyCodeToText,
								ConfigEditor &cfg)
{
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg,	P_MOVE_DOWN, "P_MOVE_DOWN", SDLK_DOWN);
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg, P_MOVE_UP, "P_MOVE_UP", SDLK_UP);
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg, P_MOVE_LEFT, "P_MOVE_LEFT", SDLK_LEFT);
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg, P_MOVE_RIGHT, "P_MOVE_RIGHT", SDLK_RIGHT);
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg, P_PLACE_BOMB, "P_PLACE_BOMB", SDLK_SPACE);
	mapActionToKey(textToKeyCode, actionToKeyCode, keyCodeToText, cfg, P_PAUSE_GAME, "P_PAUSE_GAME", SDLK_ESCAPE);
}

void       SetupKeybindings (KeyBindings &keyBindings)
{
    mapKeyTextToSDLKey(*keyBindings.textToKeyCode);
    mapSDLKeyToText(*keyBindings.keyCodeToText, *keyBindings.textToKeyCode);
    GetKeyCodesFromConfig(*keyBindings.textToKeyCode, *keyBindings.actionToKeyCode, *keyBindings.keyCodeToText, g_cfg);
    mapKeyName(*keyBindings.keyName);
}

ePlayerAction   GetPlayerAction(SDL_KeyboardEvent &e)
{
	return (P_NOACTION);
}