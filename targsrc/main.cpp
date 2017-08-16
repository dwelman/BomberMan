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
	if (SDL_Init(0) == -1)
	{
		std::cerr << "Error : " << SDL_GetError() << std::endl;
		return (nullptr);
	}
	SDL_Window *window = SDL_CreateWindow(
		"Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cfg["xres"].to_int(), cfg["yres"].to_int(),
		SDL_WINDOW_OPENGL);
    if (case_ins_cmp(cfg["Fullscreen"].to_str(), "yes"))
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

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
    GUIFunctionCrate    crate;
	double				guiLastTimePulse = initGui(window, crate);
	RenderEngine        rEngine;
    std::vector<GameObjectRenderInfo>   gameObjects;

    manager.SetGameStarted(false);
    rEngine.initGlew();
    crate.manager = &manager;
    crate.mustQuit = &mustQuit;
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
        if (!manager.GetGameStarted())
		    renderGUIInjectEvents(manager, window, guiLastTimePulse, mustQuit);
		SDL_GL_SwapWindow(window);
        gameObjects.clear();
		//SDL_Delay(10);
    }
	while (mustQuit == false);
	destroyGUI(crate);
}

int	main(int argc, char *argv[])
{
	//renderData rdata;
	RenderEngine rEngine;

	SDL_Window	*window = initWindow(g_cfg);
	//rdata.rObjs.push_back(*obj);
	if (window == nullptr)
		return (-1);

	gameLoop(window);
	SDL_Quit();
	return (0);
}