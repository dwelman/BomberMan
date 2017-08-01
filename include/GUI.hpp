#pragma once
#include <main.hpp>
#include <GUIRenderer.hpp>

struct GUIData
{
	GLuint					shader;
	std::vector<UIElement*>	UIElements;
	float					*vertexBuffer;
	size_t					vertexBufferSize;
	size_t					vertexBufferElements;
};

void    initGui(GUIRenderer &guiRenderer);

void    drawGUI(SDL_Window *window, renderData rdata, GUIData guiData);

