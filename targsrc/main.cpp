/*Project created for WeThinkCode_ syllabus
	Created by:
		*David Welman
		*Dean du Toit
		*Reyno van der Westhuizen
		*Michael Eckhardt
	Copyright (c) 2017
*/

#include "main.hpp"

SDL_Window *initWindow()
{
	if (SDL_Init(0) == -1)
	{
		std::cerr << "Error : " << SDL_GetError() << std::endl;
		return (nullptr);
	}
	SDL_Window *window = SDL_CreateWindow(
		"Bomberman", 100, 100, 640, 480,
		SDL_WINDOW_OPENGL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

int initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Error : " << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
}

void gameLoop(SDL_Window *window)
{
    SDL_Event e;
    do
    {
        SDL_PollEvent(&e);

        draw(window);
        SDL_GL_SwapWindow(window);
    }
	while (e.type != SDL_QUIT);
}

int	main(int argc, char *argv[])
{
	SDL_Window	*window = initWindow();
	if (window == nullptr || initGlew() == -1)
		return (-1);
	gameLoop(window);

	//startGUI(window);
	SDL_Quit();
	return (0);
}