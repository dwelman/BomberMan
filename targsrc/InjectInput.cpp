#include <main.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <vector>

std::map<int, CEGUI::Key::Scan> m_keymap;


void initializeKeyMap() 
{
	m_keymap[SDLK_1] = CEGUI::Key::One;
	m_keymap[SDLK_2] = CEGUI::Key::Two;
	m_keymap[SDLK_3] = CEGUI::Key::Three;
	m_keymap[SDLK_4] = CEGUI::Key::Four;
	m_keymap[SDLK_5] = CEGUI::Key::Five;
	m_keymap[SDLK_6] = CEGUI::Key::Six;
	m_keymap[SDLK_7] = CEGUI::Key::Seven;
	m_keymap[SDLK_8] = CEGUI::Key::Eight;
	m_keymap[SDLK_9] = CEGUI::Key::Nine;
	m_keymap[SDLK_0] = CEGUI::Key::Zero;

	m_keymap[SDLK_q] = CEGUI::Key::Q;
	m_keymap[SDLK_w] = CEGUI::Key::W;
	m_keymap[SDLK_e] = CEGUI::Key::E;
	m_keymap[SDLK_r] = CEGUI::Key::R;
	m_keymap[SDLK_t] = CEGUI::Key::T;
	m_keymap[SDLK_y] = CEGUI::Key::Y;
	m_keymap[SDLK_u] = CEGUI::Key::U;
	m_keymap[SDLK_i] = CEGUI::Key::I;
	m_keymap[SDLK_o] = CEGUI::Key::O;
	m_keymap[SDLK_p] = CEGUI::Key::P;
	m_keymap[SDLK_a] = CEGUI::Key::A;
	m_keymap[SDLK_s] = CEGUI::Key::S;
	m_keymap[SDLK_d] = CEGUI::Key::D;
	m_keymap[SDLK_f] = CEGUI::Key::F;
	m_keymap[SDLK_g] = CEGUI::Key::G;
	m_keymap[SDLK_h] = CEGUI::Key::H;
	m_keymap[SDLK_j] = CEGUI::Key::J;
	m_keymap[SDLK_k] = CEGUI::Key::K;
	m_keymap[SDLK_l] = CEGUI::Key::L;
	m_keymap[SDLK_z] = CEGUI::Key::Z;
	m_keymap[SDLK_x] = CEGUI::Key::X;
	m_keymap[SDLK_c] = CEGUI::Key::C;
	m_keymap[SDLK_v] = CEGUI::Key::V;
	m_keymap[SDLK_b] = CEGUI::Key::B;
	m_keymap[SDLK_n] = CEGUI::Key::N;
	m_keymap[SDLK_m] = CEGUI::Key::M;

	m_keymap[SDLK_COMMA] = CEGUI::Key::Comma;
	m_keymap[SDLK_PERIOD] = CEGUI::Key::Period;
	m_keymap[SDLK_SLASH] = CEGUI::Key::Slash;
	m_keymap[SDLK_BACKSLASH] = CEGUI::Key::Backslash;
	m_keymap[SDLK_MINUS] = CEGUI::Key::Minus;
	m_keymap[SDLK_EQUALS] = CEGUI::Key::Equals;
	m_keymap[SDLK_SEMICOLON] = CEGUI::Key::Semicolon;
	m_keymap[SDLK_LEFTBRACKET] = CEGUI::Key::LeftBracket;
	m_keymap[SDLK_RIGHTBRACKET] = CEGUI::Key::RightBracket;
	m_keymap[SDLK_QUOTE] = CEGUI::Key::Apostrophe;
	m_keymap[SDLK_BACKQUOTE] = CEGUI::Key::Grave;

	m_keymap[SDLK_RETURN] = CEGUI::Key::Return;
	m_keymap[SDLK_SPACE] = CEGUI::Key::Space;
	m_keymap[SDLK_BACKSPACE] = CEGUI::Key::Backspace;
	m_keymap[SDLK_TAB] = CEGUI::Key::Tab;

	m_keymap[SDLK_ESCAPE] = CEGUI::Key::Escape;
	m_keymap[SDLK_PAUSE] = CEGUI::Key::Pause;
	m_keymap[SDLK_SYSREQ] = CEGUI::Key::SysRq;
	m_keymap[SDLK_POWER] = CEGUI::Key::Power;

	m_keymap[SDLK_NUMLOCKCLEAR] = CEGUI::Key::NumLock;
	m_keymap[SDLK_SCROLLLOCK] = CEGUI::Key::ScrollLock;

	m_keymap[SDLK_F1] = CEGUI::Key::F1;
	m_keymap[SDLK_F2] = CEGUI::Key::F2;
	m_keymap[SDLK_F3] = CEGUI::Key::F3;
	m_keymap[SDLK_F4] = CEGUI::Key::F4;
	m_keymap[SDLK_F5] = CEGUI::Key::F5;
	m_keymap[SDLK_F6] = CEGUI::Key::F6;
	m_keymap[SDLK_F7] = CEGUI::Key::F7;
	m_keymap[SDLK_F8] = CEGUI::Key::F8;
	m_keymap[SDLK_F9] = CEGUI::Key::F9;
	m_keymap[SDLK_F10] = CEGUI::Key::F10;
	m_keymap[SDLK_F11] = CEGUI::Key::F11;
	m_keymap[SDLK_F12] = CEGUI::Key::F12;
	m_keymap[SDLK_F13] = CEGUI::Key::F13;
	m_keymap[SDLK_F14] = CEGUI::Key::F14;
	m_keymap[SDLK_F15] = CEGUI::Key::F15;

	m_keymap[SDLK_LCTRL] = CEGUI::Key::LeftControl;
	m_keymap[SDLK_LALT] = CEGUI::Key::LeftAlt;
	m_keymap[SDLK_LSHIFT] = CEGUI::Key::LeftShift;
	m_keymap[SDLK_LGUI] = CEGUI::Key::LeftWindows;
	m_keymap[SDLK_RCTRL] = CEGUI::Key::RightControl;
	m_keymap[SDLK_RALT] = CEGUI::Key::RightAlt;
	m_keymap[SDLK_RSHIFT] = CEGUI::Key::RightShift;
	m_keymap[SDLK_RGUI] = CEGUI::Key::RightWindows;
	m_keymap[SDLK_MENU] = CEGUI::Key::AppMenu;

	m_keymap[SDLK_KP_0] = CEGUI::Key::Numpad0;
	m_keymap[SDLK_KP_1] = CEGUI::Key::Numpad1;
	m_keymap[SDLK_KP_2] = CEGUI::Key::Numpad2;
	m_keymap[SDLK_KP_3] = CEGUI::Key::Numpad3;
	m_keymap[SDLK_KP_4] = CEGUI::Key::Numpad4;
	m_keymap[SDLK_KP_5] = CEGUI::Key::Numpad5;
	m_keymap[SDLK_KP_6] = CEGUI::Key::Numpad6;
	m_keymap[SDLK_KP_7] = CEGUI::Key::Numpad7;
	m_keymap[SDLK_KP_8] = CEGUI::Key::Numpad8;
	m_keymap[SDLK_KP_9] = CEGUI::Key::Numpad9;

	m_keymap[SDLK_KP_PERIOD] = CEGUI::Key::Decimal;
	m_keymap[SDLK_KP_PLUS] = CEGUI::Key::Add;
	m_keymap[SDLK_KP_MINUS] = CEGUI::Key::Subtract;
	m_keymap[SDLK_KP_MULTIPLY] = CEGUI::Key::Multiply;
	m_keymap[SDLK_KP_DIVIDE] = CEGUI::Key::Divide;
	m_keymap[SDLK_KP_ENTER] = CEGUI::Key::NumpadEnter;

	m_keymap[SDLK_UP] = CEGUI::Key::ArrowUp;
	m_keymap[SDLK_LEFT] = CEGUI::Key::ArrowLeft;
	m_keymap[SDLK_RIGHT] = CEGUI::Key::ArrowRight;
	m_keymap[SDLK_DOWN] = CEGUI::Key::ArrowDown;

	m_keymap[SDLK_HOME] = CEGUI::Key::Home;
	m_keymap[SDLK_END] = CEGUI::Key::End;
	m_keymap[SDLK_PAGEUP] = CEGUI::Key::PageUp;
	m_keymap[SDLK_PAGEDOWN] = CEGUI::Key::PageDown;
	m_keymap[SDLK_INSERT] = CEGUI::Key::Insert;
	m_keymap[SDLK_DELETE] = CEGUI::Key::Delete;
}

void handle_mouse_down(Uint8 button, CEGUI::GUIContext& context)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		context.injectMouseButtonDown(CEGUI::LeftButton);
		break;
	case SDL_BUTTON_MIDDLE:
		context.injectMouseButtonDown(CEGUI::MiddleButton);
		break;
	case SDL_BUTTON_RIGHT:
		context.injectMouseButtonDown(CEGUI::RightButton);
		break;
	case SDL_BUTTON_X1:
		context.injectMouseWheelChange(-1);
	break;
	case SDL_BUTTON_X2:
		context.injectMouseWheelChange(+1);
	break;
	}
}


void handle_mouse_up(Uint8 button, CEGUI::GUIContext& context)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		context.injectMouseButtonUp(CEGUI::LeftButton);
		break;
	case SDL_BUTTON_MIDDLE:
		context.injectMouseButtonUp(CEGUI::MiddleButton);
		break;
	case SDL_BUTTON_RIGHT:
		context.injectMouseButtonUp(CEGUI::RightButton);
		break;
	}
}


void injectInput(bool & must_quit, CEGUI::GUIContext& context, SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		/* we inject the mouse position directly. */
		//				CEGUI::System::getSingleton().injectMousePosition(static_cast<float>(e.motion.x),static_cast<float>(e.motion.y));
			context.injectMousePosition(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y));
		break;
	case SDL_MOUSEBUTTONDOWN:
		handle_mouse_down(e.button.button, context);
		break;

		/* mouse up handler */
	case SDL_MOUSEBUTTONUP:
		handle_mouse_up(e.button.button, context);
		break;

		/* key down */
	case SDL_KEYDOWN:
		context.injectKeyDown(m_keymap[e.key.keysym.sym]);
		if ((e.key.keysym.sym & 0xFF80) == 0)
		{
			context.injectChar(e.key.keysym.sym & 0x7F);
		}
		break;
	case SDL_KEYUP:
		context.injectKeyUp(m_keymap[e.key.keysym.sym]);
		break;
	case SDL_QUIT:
		must_quit = true;
		break;
	case SDL_WINDOWEVENT_RESIZED:
		CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(e.window.data1, e.window.data2));
		break;
	}
}


void injectTimePulse(double& last_time_pulse)
{
	/* get current "run-time" in seconds */
	double t = 0.001 * SDL_GetTicks();
	/* inject the time that passed since the last call */
	CEGUI::System::getSingleton().injectTimePulse(float(t - last_time_pulse));
	/* store the new time as the last time */
	last_time_pulse = t;
}

void renderGui(SDL_Window *window)
{
	/* clear the colour buffer */
	glClear(GL_COLOR_BUFFER_BIT);
	/* render the GUI :) */
	CEGUI::System::getSingleton().renderAllGUIContexts();
	/* Update the screen */
	SDL_GL_SwapWindow(window);
}

/*
void main_loop(SDL_Window *window)
{
	bool must_quit = false;
	double last_time_pulse = 0.001 * static_cast<double>(SDL_GetTicks());
	while (!must_quit)
	{
		injectInput(must_quit);
		injectTimePulse(last_time_pulse);
		renderGui(window);
	}
}



int mainleop(int argc, char **argv)
{
	
}
*/