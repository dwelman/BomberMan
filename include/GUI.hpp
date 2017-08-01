#pragma once
#include <main.hpp>
#include <UIElement.hpp>

struct GUIData
{
	GLuint					shader;
	std::vector<UIElement*>	UIElements;
	float					*vertexBuffer;
	int						vertexBufferSize;
};

void    initGui(GUIData &guiData);

void    drawGUI(SDL_Window *window, renderData rdata, GUIData guiData);
