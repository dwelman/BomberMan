
#include <main.hpp>
#include <GUI.hpp>
#include <SDL_video.h>

void 				tryAddResolution(int w, int h, SettingsState &s)
{
	SDL_DisplayMode	dspAttempt, dspClosest;
	std::string		str;

	dspAttempt.w = w;
	dspAttempt.h = h;
	SDL_GetClosestDisplayMode(0, &dspAttempt, &dspClosest);

	if (dspAttempt.w == dspClosest.w && dspAttempt.h == dspClosest.h)
	{
		str = std::to_string(dspAttempt.w ) + "x" + std::to_string(dspAttempt.h);
		s.video.resolution.push_back(str.c_str());
	}
	else
	{
		if (dspClosest.w / dspAttempt.h != 1.77777777778f)
		{
			return;
		}
		else
		{
			str = std::to_string(dspClosest.w ) + "x" + std::to_string(dspClosest.h);
		}
	}
}

void				populateSettingSpinners(SettingsState &s)
{
	SDL_DisplayMode	monitorDisplayMode;

	SDL_GetCurrentDisplayMode(0, &monitorDisplayMode);

	tryAddResolution(1024,576, s);
	tryAddResolution(1280,720, s);
	tryAddResolution(1366,768, s);
	tryAddResolution(1600,900, s);
	tryAddResolution(1920,1080, s);
	tryAddResolution(2560,1440, s);
	tryAddResolution(3840,2160, s);

	s.video.resolution.setIterator(s.video.resolution.activeValue);
	s.video.fullScreen.push_back("Yes");
	s.video.fullScreen.push_back("No");
	s.video.fullScreen.setIterator(s.video.fullScreen.activeValue);
}

GUICrate::GUICrate()
{
    memset(this, 0, sizeof(GUICrate));

	loadSettingsFromDefaultConfig(this->activeSettings);
	keybindings.actionToKeyCode = new std::map<ePlayerAction, SDL_Keycode>;
	keybindings.textToKeyCode = new  std::map<std::string, SDL_Keycode>;
	pendingSettings = activeSettings;
}

GUICrate::~GUICrate()
{
	delete keybindings.actionToKeyCode;
	delete keybindings.textToKeyCode;
}

inline void	  setupResourceGroups()
{
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("imagesets", "resources/GUI/imagesets/");
	rp->setResourceGroupDirectory("schemes", "resources/GUI/schemes/");
	rp->setResourceGroupDirectory("fonts", "resources/GUI/fonts/");
	rp->setResourceGroupDirectory("layouts", "resources/GUI/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "resources/GUI/looknfeel/");
	//	rp->setResourceGroupDirectory("lua_scripts", "resources/GUI/lua_scripts/");

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	//	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
}

void		loadResources(GUICrate &crate)
{
	//Load Schemes
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("SampleBrowser.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Bomberman.scheme");



	//Setup Defaults
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("Jura-18");
//	CEGUI::FontManager::getSingleton().createFromFile("Jura-18.font");
//	CEGUI::FontManager::getSingleton().createFromFile("Jura-13.font");
//	CEGUI::FontManager::getSingleton().createFromFile("Jura-10.font");

	//Load Layouts
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	crate.main = wmgr.loadLayoutFromFile("MainMenu.layout");

	crate.settings = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Settings.layout");
	crate.settings->setVisible(false);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(crate.main);

}


//MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUICrate	&var)

void        initValues(GUICrate &crate)
{
    CEGUI::NamedElement *resolutionValue = crate.settings->getChildElementRecursive("ResolutionValue");
    resolutionValue->setProperty("Text", g_cfg["xres"].to_str() + "x" + g_cfg["yres"].to_str());
    CEGUI::NamedElement *fullscreenValue = crate.settings->getChildElementRecursive("FullscreenValue");
    fullscreenValue->setProperty("Text", case_ins_cmp("yes", g_cfg["fullscreen"].to_str()) ? "Yes" : "No");
}

void		destroyGUI(GUICrate &crate)
{
	/*
	TODO
	*/
	// Clean crate
//	for (auto it = crate.MenuFunctions.begin(); it != crate.MenuFunctions.end(); it++)
//		delete (*it);

	CEGUI::System::destroy();
	CEGUI::OpenGL3Renderer::destroy(static_cast<CEGUI::OpenGL3Renderer&>(*crate.guiRenderer));
}

double    initGui(SDL_Window *window, GUICrate &crate)
{
	try
	{

		initializeKeyMap();
		CEGUI::OpenGL3Renderer::bootstrapSystem();
		crate.guiRenderer = &CEGUI::OpenGL3Renderer::create();

		SDL_ShowCursor(SDL_ENABLE);
		setupResourceGroups();
		loadResources(crate);
		setupEvents(crate);
        initValues(crate);
		populateSettingSpinners(crate.activeSettings);
	}
	catch (...)
	{
	}
	return (0.001 * static_cast<double>(SDL_GetTicks()));
}

void	captureInputForGameManager(GameManager &manager, SDL_Event &e, bool & must_quit, KeyBindings &keybindings)
{
	ePlayerAction	action = P_NOACTION;
	if (e.type == SDL_QUIT)
		must_quit = true;

	//TODO game logic stoofs
	if (e.type == SDL_KEYDOWN)
	{
		if ((*keybindings.actionToKeyCode)[P_MOVE_LEFT] == e.key.keysym.sym)
			action = P_MOVE_LEFT;
		else if ((*keybindings.actionToKeyCode)[P_MOVE_RIGHT] == e.key.keysym.sym)
			action = P_MOVE_RIGHT;
		else if ((*keybindings.actionToKeyCode)[P_MOVE_UP] == e.key.keysym.sym)
			action = P_MOVE_UP;
		else if ((*keybindings.actionToKeyCode)[P_MOVE_DOWN] == e.key.keysym.sym)
			action = P_MOVE_DOWN;
		else if ((*keybindings.actionToKeyCode)[P_PLACE_BOMB] == e.key.keysym.sym)
			action = P_PLACE_BOMB;
		else if ((*keybindings.actionToKeyCode)[P_PAUSE_GAME] == e.key.keysym.sym)
			action = P_PAUSE_GAME;

		if (action != P_NOACTION)
		{
			// Feed actions  into GM
			manager.GivePlayerAction(action);
			std::cout << "action = " << action << std::endl;
		}
	}
}

void	captureWindowEvents(SDL_Event &e, GUICrate &crate)
{
	SDL_Event	*event = &e;

	if (e.type == SDL_WINDOWEVENT)
	{
		if (event->type == SDL_WINDOWEVENT)
		{
			switch (event->window.event)
			{
				case SDL_WINDOWEVENT_SHOWN:
					SDL_Log("Window %d shown", event->window.windowID); //TODO Unpause
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					SDL_Log("Window %d hidden", event->window.windowID); //TODO Pause
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					SDL_Log("Window %d size changed to %dx%d",
							event->window.windowID, event->window.data1,
							event->window.data2);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					SDL_Log("Window %d minimized", event->window.windowID); //TODO Pause
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					SDL_Log("Window %d maximized", event->window.windowID); //TODO Unpause
					break;
				case SDL_WINDOWEVENT_CLOSE:
					SDL_Log("Window %d closed", event->window.windowID);
					break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
				case SDL_WINDOWEVENT_TAKE_FOCUS:
					SDL_Log("Window %d is offered a focus", event->window.windowID);
					break;
#endif
				default:
					break;
			}
		}
	}
}

void	renderGUIInjectEvents(GameManager &manager, SDL_Window *window, double guiLastTimePulse, bool &must_quit, GUICrate &crate)
{
	SDL_Event			e;
	GLint				activeID;

	while (SDL_PollEvent(&e))
	{
		injectInput(must_quit, CEGUI::System::getSingleton().getDefaultGUIContext(), e);
		captureInputForGameManager(manager, e, must_quit, crate.keybindings);
		captureWindowEvents(e, crate);
	}
//	if (manager.GetGameStarted()) // && !manager.GetGamePaused())
//		crate.main->setVisible(false);
	injectTimePulse(guiLastTimePulse);
	//Draw Stuff 
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
	glGetIntegerv(GL_ACTIVE_TEXTURE, &activeID);
	glActiveTexture(GL_TEXTURE0);
	if (!manager.GetGameStarted()) //NEED TO FIGURE LIGHTS THE FUCK PIdasdasdads
	 CEGUI::System::getSingleton().renderAllGUIContexts();

	glActiveTexture(activeID);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void		reloadDisplayMode(SDL_Window *win, GUICrate &crate)
{
	SDL_DisplayMode	dsp;
	SDL_GetDesktopDisplayMode(0, &dsp);

	g_cfg.reload();
	dsp.w = g_cfg["xres"].to_int();
	dsp.h = g_cfg["yres"].to_int();

	SDL_SetWindowSize(win, g_cfg["xres"].to_int(), g_cfg["yres"].to_int());
	SDL_SetWindowDisplayMode(win, &dsp);
	CEGUI::Size<float> NewWindowSize((float)g_cfg["xres"].to_int(), (float)g_cfg["yres"].to_int());
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(NewWindowSize);
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().notifyDisplaySizeChanged(NewWindowSize);
	crate.guiRenderer->setDisplaySize(NewWindowSize);
	std::cout << "setting to " << g_cfg["xres"].to_str() << 'x' << g_cfg["yres"].to_str() << std::endl;
	SDL_GetDisplayMode(0,0, &dsp);
	if (case_ins_cmp(g_cfg["Fullscreen"].to_str(), "yes"))
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	else
		SDL_SetWindowFullscreen(win, SDL_WINDOW_OPENGL);
	crate.displayChanged = false;
}