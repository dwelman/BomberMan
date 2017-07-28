/*Project created for WeThinkCode_ syllabus
	Created by:
		*David Welman
		*Dean du Toit
		*Reyno van der Westhuizen
		*Michael Eckhardt
	Copyright (c) 2017
*/

#include "main.hpp"
#include "RenderEngine.hpp"

SDL_Window *initWindow(ConfigEditor &cfg)
{
	if (SDL_Init(0) == -1)
	{
		std::cerr << "Error : " << SDL_GetError() << std::endl;
		return (nullptr);
	}
	SDL_Window *window = SDL_CreateWindow(
		"Bomberman", 100, 100, cfg["xres"].to_int(), cfg["yres"].to_int(),
		SDL_WINDOW_OPENGL);
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
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Error : " << "Failed to initialize GLEW" << std::endl;
		return nullptr;
	}
	return (window);
}

void gameLoop(SDL_Window *window, renderData rdata)
{
    SDL_Event e;
    do
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_PollEvent(&e);

        draw(window, rdata);
        SDL_GL_SwapWindow(window);
    }
	while (e.type != SDL_QUIT);
}

int	main(int argc, char *argv[])
{
	renderData rdata;
    ConfigEditor cfg("../resources/settings.cfg");
	SDL_Window	*window = initWindow(cfg);

	rdata = initGlew();
	if (window == nullptr || rdata.res == -1)
		return (-1);

	gameLoop(window, rdata);

	//startGUI(window);
	SDL_Quit();
	return (0);
}