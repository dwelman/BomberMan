#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

typedef	bool(*ccev)(const CEGUI::EventArgs &e, void *var);

template <typename T>
struct MenuFunction
{
	T					&var;
	ccev				customEvent;
	CEGUI::NamedElement	*element;

	MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, T &var) :
		var(var), element(_element)
	{
		customEvent = eventFunction;
		element->subscribeEvent(name, CEGUI::Event::Subscriber(&MenuFunction::invoke, this));
	}

	bool invoke(const CEGUI::EventArgs& e)
	{
		return (customEvent(e, var));
	}

	virtual ~MenuFunction() {};
};

struct GUIFunctionCrate
{
	MenuFunction<bool*>	*triggerExit;
	bool				*triggerExitParam;

	~GUIFunctionCrate();
};

double  initGui(SDL_Window *window, GUIFunctionCrate &crate);

void	renderGUIInjectEvents(SDL_Window *window, double guiLastTimePulse, bool &must_quit);

void	initializeKeyMap();

void	injectInput(bool & must_quit, CEGUI::GUIContext& context, SDL_Event &e);

void	injectTimePulse(double& last_time_pulse);

void	captureInputForGameLogic(SDL_Event const &e, bool & must_quit);

void	loadResources();