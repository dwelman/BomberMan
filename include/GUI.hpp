#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <GameManager.hpp>
#include <Settings.hpp>

struct MenuFunction;
struct Setting;

struct GUIFunctionCrate
{
	GameManager                 *manager;
	CEGUI::OpenGL3Renderer		*guiRenderer;
	bool						*mustQuit;
	bool						displayChanged;
	//Layouts
	CEGUI::Window* main;
	CEGUI::Window* settings;

	SettingsState				activeSettings;
	SettingsState				pendingSettings;

	std::vector<MenuFunction*>	MenuFunctions;

	GUIFunctionCrate();
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

void	setupEvents(GUIFunctionCrate &crate);

void	loadSettingsFromDefaultConfig(SettingsState &settings);

void	destroyGUI(GUIFunctionCrate &crate);

void		reloadDisplayMode(SDL_Window *win, GUIFunctionCrate &crate);

//Events

bool setExit(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate	&var);

bool openSettingsMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate &var);

bool openMainMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate &var);

bool startGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var);

bool resolutionNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var);

bool resolutionPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var);

bool fullscreenNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var);

bool fullscreenPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var);

bool applyClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var);