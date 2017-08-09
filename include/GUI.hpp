#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

double  initGui(SDL_Window *window);

void	renderGUIInjectEvents(SDL_Window *window, double guiLastTimePulse, bool &must_quit);

void	initializeKeyMap();

void	injectInput(bool & must_quit, CEGUI::GUIContext& context, SDL_Event &e);

void	injectTimePulse(double& last_time_pulse);

void	captureInputForGameLogic(SDL_Event const &e, bool & must_quit);