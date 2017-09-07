#pragma once
#include <main.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <AudioManager.hpp>
#include <GameManager.hpp>
#include <Settings.hpp>

struct MenuFunction;
struct Setting;
class PaneGroup;

struct KeyBindChange
{
	std::string		cfgKey;
	std::string		cfgVal;
	ePlayerAction	action;
	SDL_Keycode		key;
};

struct KeyBindings
{
	std::map<ePlayerAction, SDL_Keycode >   *actionToKeyCode;
	std::map<std::string, SDL_Keycode>		*textToKeyCode;
	std::map<SDL_Keycode, std::string>		*keyCodeToText;
	std::map<SDL_Keycode, std::string>		*keyName;
	std::map<SDL_Keycode, SDL_Scancode>		*keyCodeToScan;

	bool 									catchNext;
	ePlayerAction							actionToMap;
	std::string								actionToMapKey;
	std::string								boundElementName;
	std::vector<KeyBindChange*>				keyBindChanges;
};

enum eGUIState
{
	S_INGAME,
	S_PAUSED,
	S_SETTINGS,
	S_MENU
};

struct GUICrate
{
	//Variables GUI Needs to access
	eGUIState                               state;
	CEGUI::Window							*active;
	GameManager								*manager;
	CEGUI::OpenGL3Renderer					*guiRenderer;
	AudioManager							*audio;
	RenderEngine							*engine;
    SDL_Window                              *window;
	bool									*mustQuit;
	bool									displayChanged;
	KeyBindings								keybindings;

	//Event Functions
	std::vector<MenuFunction*>				MenuFunctions;

	//Layouts
	CEGUI::Window							*main;
	CEGUI::Window							*settings;
	CEGUI::Window							*gameOverlay;

	//Elements
	CEGUI::NamedElement						*paused;
	CEGUI::NamedElement						*levelText;
	CEGUI::NamedElement						*livesText;
	CEGUI::NamedElement						*bombsText;
	CEGUI::NamedElement						*enemiesText;
	CEGUI::NamedElement						*scoreText;
	CEGUI::NamedElement						*timerText;


	PaneGroup								*settingPanes;

	//Setting States
	SettingsState							activeSettings;
	SettingsState							pendingSettings;

	void									switchLayout(CEGUI::Window *to);
	GUICrate();
	~GUICrate();
};

class PaneGroup
{

private:
	std::string										active;
	std::map<std::string, CEGUI::NamedElement*>		panes;

public:
	PaneGroup();
	PaneGroup(PaneGroup &src);
	~PaneGroup();

	PaneGroup							&operator=(PaneGroup const &c);
	void								Add(CEGUI::NamedElement *elem, std::string const & name);
	std::string const					&GetActiveName();
	void								SetActive(std::string const & name);

};


typedef	bool(*ccev)(const CEGUI::EventArgs &e, CEGUI::NamedElement *_element , GUICrate &var);

struct MenuFunction
{
	GUICrate	&var;
	ccev				customEvent;
	CEGUI::NamedElement	*element;

	MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUICrate	&_var);
	bool invoke(const CEGUI::EventArgs& e);
	virtual ~MenuFunction() {};
};

double  initGui(SDL_Window *window, GUICrate &crate);

void    initMenuValues(GUICrate &crate);

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

void    SetupKeybindings (KeyBindings &keyBindings);

void	switchLayouts(CEGUI::Window *from, CEGUI::Window *to);

//Events

bool setExit(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate	&var);

bool openSettingsMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate &var);

bool openMainMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUICrate &var);

bool continueGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool startGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool resolutionNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool resolutionPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var);

bool fullscreenNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool fullscreenPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool applyClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool showVideoSettingsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool showAudioSettingsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool showControlsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActiveUp(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActiveDown(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActiveLeft(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActiveRight(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActivePlaceBomb(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);

bool keyBindActivePauseGame(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var);