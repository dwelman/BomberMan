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

void	mapScanCodes(std::map<SDL_Keycode, SDL_Scancode> &keyCodeToScan)
{
	keyCodeToScan[SDLK_1] = SDL_SCANCODE_1;
	keyCodeToScan[SDLK_2] = SDL_SCANCODE_2;
	keyCodeToScan[SDLK_3] = SDL_SCANCODE_3;
	keyCodeToScan[SDLK_4] = SDL_SCANCODE_4;
	keyCodeToScan[SDLK_5] = SDL_SCANCODE_5;
	keyCodeToScan[SDLK_6] = SDL_SCANCODE_6;
	keyCodeToScan[SDLK_7] = SDL_SCANCODE_7;
	keyCodeToScan[SDLK_8] = SDL_SCANCODE_8;
	keyCodeToScan[SDLK_9] = SDL_SCANCODE_9;
	keyCodeToScan[SDLK_0] = SDL_SCANCODE_0;
	keyCodeToScan[SDLK_q] = SDL_SCANCODE_Q;
	keyCodeToScan[SDLK_w] = SDL_SCANCODE_W;
	keyCodeToScan[SDLK_e] = SDL_SCANCODE_E;
	keyCodeToScan[SDLK_r] = SDL_SCANCODE_R;
	keyCodeToScan[SDLK_t] = SDL_SCANCODE_T;
	keyCodeToScan[SDLK_y] = SDL_SCANCODE_Y;
	keyCodeToScan[SDLK_u] = SDL_SCANCODE_U;
	keyCodeToScan[SDLK_i] = SDL_SCANCODE_I;
	keyCodeToScan[SDLK_o] = SDL_SCANCODE_O;
	keyCodeToScan[SDLK_p] = SDL_SCANCODE_P;
	keyCodeToScan[SDLK_a] = SDL_SCANCODE_A;
	keyCodeToScan[SDLK_d] = SDL_SCANCODE_D;
	keyCodeToScan[SDLK_f] = SDL_SCANCODE_F;
	keyCodeToScan[SDLK_g] = SDL_SCANCODE_G;
	keyCodeToScan[SDLK_h] = SDL_SCANCODE_H;
	keyCodeToScan[SDLK_j] = SDL_SCANCODE_J;
	keyCodeToScan[SDLK_k] = SDL_SCANCODE_K;
	keyCodeToScan[SDLK_l] = SDL_SCANCODE_L;
	keyCodeToScan[SDLK_z] = SDL_SCANCODE_Z;
	keyCodeToScan[SDLK_x] = SDL_SCANCODE_X;
	keyCodeToScan[SDLK_c] = SDL_SCANCODE_C;
	keyCodeToScan[SDLK_v] = SDL_SCANCODE_V;
	keyCodeToScan[SDLK_b] = SDL_SCANCODE_B;
	keyCodeToScan[SDLK_n] = SDL_SCANCODE_N;
	keyCodeToScan[SDLK_m] = SDL_SCANCODE_M;
	keyCodeToScan[SDLK_COMMA] = SDL_SCANCODE_COMMA;
	keyCodeToScan[SDLK_PERIOD] = SDL_SCANCODE_PERIOD;
	keyCodeToScan[SDLK_SLASH] = SDL_SCANCODE_SLASH;
	keyCodeToScan[SDLK_BACKSLASH] = SDL_SCANCODE_BACKSLASH;
	keyCodeToScan[SDLK_MINUS] = SDL_SCANCODE_MINUS;
	keyCodeToScan[SDLK_EQUALS] = SDL_SCANCODE_EQUALS;
	keyCodeToScan[SDLK_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
	keyCodeToScan[SDLK_LEFTBRACKET] = SDL_SCANCODE_LEFTBRACKET;
	keyCodeToScan[SDLK_RIGHTBRACKET] = SDL_SCANCODE_RIGHTBRACKET;
	keyCodeToScan[SDLK_QUOTE] = SDL_SCANCODE_APOSTROPHE;
	keyCodeToScan[SDLK_BACKQUOTE] = SDL_SCANCODE_GRAVE;
	keyCodeToScan[SDLK_RETURN] = SDL_SCANCODE_RETURN;
	keyCodeToScan[SDLK_SPACE] = SDL_SCANCODE_SPACE;
	keyCodeToScan[SDLK_BACKSPACE] = SDL_SCANCODE_BACKSPACE;
	keyCodeToScan[SDLK_TAB] = SDL_SCANCODE_TAB;
	keyCodeToScan[SDLK_ESCAPE] = SDL_SCANCODE_ESCAPE;
	keyCodeToScan[SDLK_PAUSE] = SDL_SCANCODE_PAUSE;
	keyCodeToScan[SDLK_SYSREQ] = SDL_SCANCODE_SYSREQ;
	keyCodeToScan[SDLK_POWER] = SDL_SCANCODE_POWER;
	keyCodeToScan[SDLK_NUMLOCKCLEAR] = SDL_SCANCODE_NUMLOCKCLEAR;
	keyCodeToScan[SDLK_SCROLLLOCK] = SDL_SCANCODE_SCROLLLOCK;
	keyCodeToScan[SDLK_F1] = SDL_SCANCODE_F1;
	keyCodeToScan[SDLK_F2] = SDL_SCANCODE_F2;
	keyCodeToScan[SDLK_F3] = SDL_SCANCODE_F3;
	keyCodeToScan[SDLK_F4] = SDL_SCANCODE_F4;
	keyCodeToScan[SDLK_F5] = SDL_SCANCODE_F5;
	keyCodeToScan[SDLK_F6] = SDL_SCANCODE_F6;
	keyCodeToScan[SDLK_F7] = SDL_SCANCODE_F7;
	keyCodeToScan[SDLK_F8] = SDL_SCANCODE_F8;
	keyCodeToScan[SDLK_F9] = SDL_SCANCODE_F9;
	keyCodeToScan[SDLK_F10] = SDL_SCANCODE_F10;
	keyCodeToScan[SDLK_F11] = SDL_SCANCODE_F11;
	keyCodeToScan[SDLK_F12] = SDL_SCANCODE_F12;
	keyCodeToScan[SDLK_F13] = SDL_SCANCODE_F13;
	keyCodeToScan[SDLK_F14] = SDL_SCANCODE_F14;
	keyCodeToScan[SDLK_F15] = SDL_SCANCODE_F15;
	keyCodeToScan[SDLK_LCTRL] = SDL_SCANCODE_LCTRL;
	keyCodeToScan[SDLK_LALT] = SDL_SCANCODE_LALT;
	keyCodeToScan[SDLK_LSHIFT] = SDL_SCANCODE_LSHIFT;
	keyCodeToScan[SDLK_LGUI] = SDL_SCANCODE_LGUI;
	keyCodeToScan[SDLK_RCTRL] = SDL_SCANCODE_RCTRL;
	keyCodeToScan[SDLK_RALT] = SDL_SCANCODE_RALT;
	keyCodeToScan[SDLK_RSHIFT] = SDL_SCANCODE_RSHIFT;
	keyCodeToScan[SDLK_RGUI] = SDL_SCANCODE_RGUI;
	keyCodeToScan[SDLK_MENU] = SDL_SCANCODE_MENU;
	keyCodeToScan[SDLK_KP_0] = SDL_SCANCODE_KP_0;
	keyCodeToScan[SDLK_KP_1] = SDL_SCANCODE_KP_1;
	keyCodeToScan[SDLK_KP_2] = SDL_SCANCODE_KP_2;
	keyCodeToScan[SDLK_KP_3] = SDL_SCANCODE_KP_3;
	keyCodeToScan[SDLK_KP_4] = SDL_SCANCODE_KP_4;
	keyCodeToScan[SDLK_KP_5] = SDL_SCANCODE_KP_5;
	keyCodeToScan[SDLK_KP_6] = SDL_SCANCODE_KP_6;
	keyCodeToScan[SDLK_KP_7] = SDL_SCANCODE_KP_7;
	keyCodeToScan[SDLK_KP_8] = SDL_SCANCODE_KP_8;
	keyCodeToScan[SDLK_KP_9] = SDL_SCANCODE_KP_9;
	keyCodeToScan[SDLK_KP_PERIOD] = SDL_SCANCODE_KP_PERIOD;
	keyCodeToScan[SDLK_KP_PLUS] = SDL_SCANCODE_KP_PLUS;
	keyCodeToScan[SDLK_KP_MINUS] = SDL_SCANCODE_KP_MINUS;
	keyCodeToScan[SDLK_KP_MULTIPLY] = SDL_SCANCODE_KP_MULTIPLY;
	keyCodeToScan[SDLK_KP_DIVIDE] = SDL_SCANCODE_KP_DIVIDE;
	keyCodeToScan[SDLK_KP_ENTER] = SDL_SCANCODE_KP_ENTER;
	keyCodeToScan[SDLK_UP] = SDL_SCANCODE_UP;
	keyCodeToScan[SDLK_LEFT] = SDL_SCANCODE_LEFT;
	keyCodeToScan[SDLK_RIGHT] = SDL_SCANCODE_RIGHT;
	keyCodeToScan[SDLK_DOWN] = SDL_SCANCODE_DOWN;
	keyCodeToScan[SDLK_HOME] = SDL_SCANCODE_HOME;
	keyCodeToScan[SDLK_END] = SDL_SCANCODE_END;
	keyCodeToScan[SDLK_PAGEUP] = SDL_SCANCODE_PAGEUP;
	keyCodeToScan[SDLK_PAGEDOWN] = SDL_SCANCODE_PAGEDOWN;
	keyCodeToScan[SDLK_INSERT] = SDL_SCANCODE_INSERT;
	keyCodeToScan[SDLK_DELETE] = SDL_SCANCODE_DELETE;
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
	mapScanCodes(*keyBindings.keyCodeToScan);
}

ePlayerAction   GetPlayerAction(SDL_KeyboardEvent &e)
{
	return (P_NOACTION);
}