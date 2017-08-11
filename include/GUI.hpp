#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <GameManager.hpp>

struct MenuFunction;

struct GUIFunctionCrate
{
	std::vector<MenuFunction*>	MenuFunctions;
	bool						*mustQuit;

	~GUIFunctionCrate();
};

typedef	bool(*ccev)(const CEGUI::EventArgs &e, CEGUI::NamedElement *_element , GUIFunctionCrate &var);

struct MenuFunction
{
	GUIFunctionCrate	&var;
	ccev				customEvent;
	CEGUI::NamedElement	*element;

	MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUIFunctionCrate	&_var) :
		var(_var), element(_element)
	{
		customEvent = eventFunction;
		element->subscribeEvent(name, CEGUI::Event::Subscriber(&MenuFunction::invoke, this));
	}

	bool invoke(const CEGUI::EventArgs& e)
	{
		return (customEvent(e, element ,var));
	}

	virtual ~MenuFunction() {};
};



double  initGui(SDL_Window *window, GUIFunctionCrate &crate);

void	renderGUIInjectEvents(GameManager &manager, SDL_Window *window, double guiLastTimePulse, bool &must_quit);

void	initializeKeyMap();

void	injectInput(bool & must_quit, CEGUI::GUIContext& context, SDL_Event &e);

void	injectTimePulse(double& last_time_pulse);

void	loadResources();

void	destroyGUI(GUIFunctionCrate &crate);


//Events

bool setExit(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate	&var);