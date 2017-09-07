/*Project created for WeThinkCode_ syllabus
	Created by:
		*David Welman
		*Dean du Toit
		*Reyno van der Westhuizen
		*Michael Eckhardt
		*Luke Hamlyn
	Copyright (c) 2017
*/

#include "main.hpp"
#include "Clock.hpp"
#include <GUI.hpp>
#include "GameManager.hpp"

SDL_Window *initWindow(ConfigEditor &cfg)
{
	if (SDL_Init(SDL_INIT_AUDIO ) == -1)
	{
		std::cerr << "Error : " << SDL_GetError() << std::endl;
		return (nullptr);
	}
	SDL_Window *window = SDL_CreateWindow(
		"Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cfg["xres"].to_int(), cfg["yres"].to_int(),
		SDL_WINDOW_OPENGL);
    if (case_ins_cmp(cfg["Fullscreen"].to_str(), "yes"))
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GLContext gContext = SDL_GL_CreateContext(window);
	if (gContext == NULL)
	{ 
		std::cerr << "OpenGL context could not be created! SDL Error: %s\n" << SDL_GetError();
		return (nullptr);
	}
	return (window);
}

void gameLoop(SDL_Window *window)
{
	GameManager         manager;
	bool				mustQuit = false;
    GUICrate			crate;
	double				guiLastTimePulse ;
	RenderEngine        rEngine;
	AudioManager		*Audio = new AudioManager(g_cfg);
	SDL_Thread			*audioThread;
	int					audioThreadStatus;
    std::vector<GameObjectRenderInfo>   gameObjects;

    manager.SetGameStarted(false);
	rEngine.initGlew();
	crate.manager = &manager;
	crate.audio = Audio;
    crate.mustQuit = &mustQuit;
	crate.window = window;
    crate.engine = &rEngine;
    SetupKeybindings(crate.keybindings);
	guiLastTimePulse = initGui(window, crate);
	manager.GiveAudioManager(Audio);
    do
    {
		Clock::Instance().Tick();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (manager.Update() == true)
		{
//			break;
        }
        manager.GetRenderData(gameObjects);
		rEngine.Draw(window, manager.GetGameStarted(), gameObjects);
        Audio->execQueue();
        renderGUIInjectEvents(manager, window, guiLastTimePulse, mustQuit, crate);
		SDL_GL_SwapWindow(window);
        gameObjects.clear();
		if (crate.displayChanged)
			reloadDisplayMode(crate.window, crate);
    }
	while (mustQuit == false);
	destroyGUI(crate);
}

int	main(int argc, char *argv[])
{
	RenderEngine rEngine;

	SDL_Window	*window = initWindow(g_cfg);
	if (window == nullptr)
		return (-1);
	gameLoop(window);
	SDL_Quit();
	return (0);
}