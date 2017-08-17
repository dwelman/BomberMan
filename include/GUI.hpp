#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <AudioManager.hpp>
#include <GameManager.hpp>
#include <Settings.hpp>

struct MenuFunction;
struct Setting;

struct KeyBindings
{
	std::map<ePlayerAction, SDL_Keycode >   *actionToKeyCode;
	std::map<std::string, SDL_Keycode>		*textToKeyCode;
};

struct GUICrate
{
	//Variables GUI Needs to access
	GameManager								*manager;
	CEGUI::OpenGL3Renderer					*guiRenderer;
	AudioManager							*audio;
    SDL_Window                              *window;
	bool									*mustQuit;
	bool									displayChanged;
	KeyBindings								keybindings;
	//Event Functions
	std::vector<MenuFunction*>				MenuFunctions;
	//Layouts
	CEGUI::Window							*main;
	CEGUI::Window							*settings;
	//Setting States
	SettingsState							activeSettings;
	SettingsState							pendingSettings;

	GUICrate();
	~GUICrate();
};



typedef	bool(*ccev)(const CEGUI::EventArgs &e, CEGUI::NamedElement *_element , GUICrate &var);

struct MenuFunction
{
	GUICrate	&var;
	ccev				customEvent;
	CEGUI::NamedElement	*element;

	MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUICrate	&_var) :
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

double  initGui(SDL_Window *window, GUICrate &crate);

void	renderGUIInjectEvents(GameManager &manager, SDL_Window *window, double guiLastTimePulse, bool &must_quit, GUICrate &crate);

void	initializeKeyMap();

void	injectInput(bool & must_quit, CEGUI::GUIContext& context, SDL_Event &e);

void	injectTimePulse(double& last_time_pulse);

void	loadResources();

void	setupEvents(GUICrate &crate);

void	loadSettingsFromDefaultConfig(SettingsState &settings);

void	destroyGUI(GUICrate &crate);

void	reloadDisplayMode(SDL_Window *win, GUICrate &crate);

void	captureWindowEvents(SDL_Event &e, bool & must_quit);

//Events

bool setExit(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate	&var);

bool openSettingsMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate &var);

bool openMainMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate &var);

bool startGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool resolutionNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool resolutionPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool fullscreenNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool fullscreenPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool applyClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);