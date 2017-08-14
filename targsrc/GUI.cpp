
#include <main.hpp>
#include <GUI.hpp>

void				populateSettingSpinners(SettingsState &s)
{
	s.video.resolution.push_back("1280x720");
	s.video.resolution.push_back("1920x1080");
	s.video.resolution.setIterator(s.video.resolution.activeValue);

	s.video.fullScreen.push_back("Yes");
	s.video.fullScreen.push_back("No");
	s.video.fullScreen.setIterator(s.video.fullScreen.activeValue);
}



GUIFunctionCrate::GUIFunctionCrate()
{
    memset(this, 0, sizeof(GUIFunctionCrate));

	loadSettingsFromDefaultConfig(this->activeSettings);
	pendingSettings = activeSettings;
}

GUIFunctionCrate::~GUIFunctionCrate()
{
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

void		loadResources(GUIFunctionCrate &crate)
{
	//Load Schemes
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");

	//Setup Defaults
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("Jura-18");
	CEGUI::FontManager::getSingleton().createFromFile("Jura-18.font");
	CEGUI::FontManager::getSingleton().createFromFile("Jura-13.font");
	CEGUI::FontManager::getSingleton().createFromFile("Jura-10.font");

	//Load Layouts
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	crate.main = wmgr.loadLayoutFromFile("TestLayout.layout");

	crate.settings = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Settings.layout");
	crate.settings->setVisible(false);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(crate.main);

}


//MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUIFunctionCrate	&var)

void        initValues(GUIFunctionCrate &crate)
{
    CEGUI::NamedElement *resolutionValue = crate.settings->getChildElementRecursive("ResolutionValue");
    resolutionValue->setProperty("Text", g_cfg["xres"].to_str() + "x" + g_cfg["yres"].to_str());
    CEGUI::NamedElement *fullscreenValue = crate.settings->getChildElementRecursive("FullscreenValue");
    fullscreenValue->setProperty("Text", case_ins_cmp("yes", g_cfg["fullscreen"].to_str()) ? "Yes" : "No");
}

void		destroyGUI(GUIFunctionCrate &crate)
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

double    initGui(SDL_Window *window, GUIFunctionCrate &crate)
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

void	captureInputForGameManager(GameManager &manager, SDL_Event &e, bool & must_quit)
{
	ePlayerAction	action = P_NOACTION;
	if (e.type == SDL_QUIT)
		must_quit = true;

	//TODO game logic stoofs
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT :
				action = P_MOVE_LEFT;
				break;
			case SDLK_RIGHT :
				action = P_MOVE_RIGHT;
				break;
			case SDLK_UP :
				action = P_MOVE_UP;
				break;
			case SDLK_DOWN :
				action = P_MOVE_DOWN;
				break;
			case SDLK_SPACE :
				action = P_PLACE_BOMB;
				break;
		}
		if (action != P_NOACTION)
		{
			// Feed actions  into GM
			std::cout << "action = " << action << std::endl;
		}
	}
}

void	captureInputForState(SDL_Event &e, bool & must_quit)
{
	if (e.type == SDL_KEYDOWN)
	{
		
	}
}

void	renderGUIInjectEvents(GameManager &manager, SDL_Window *window, double guiLastTimePulse, bool &must_quit)
{
	CEGUI::GUIContext&	context = CEGUI::System::getSingleton().getDefaultGUIContext();
	SDL_Event			e;

	while (SDL_PollEvent(&e))
	{
		injectInput(must_quit, context, e);
		captureInputForGameManager(manager, e, must_quit);
		captureInputForState(e, must_quit);
	}
	injectTimePulse(guiLastTimePulse);
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
    CEGUI::System::getSingleton().renderAllGUIContexts();
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

}

void		reloadDisplayMode(SDL_Window *win, GUIFunctionCrate &crate)
{
	SDL_DisplayMode	dsp;
	SDL_GetDesktopDisplayMode(0, &dsp);

	g_cfg.reload();
	dsp.w = g_cfg["xres"].to_int();
	dsp.h = g_cfg["yres"].to_int();

	destroyGUI(crate);
	//crate.guiRenderer->setDisplaySize(CEGUI::Sizef(dsp.w, dsp.h));

	SDL_SetWindowSize(win, g_cfg["xres"].to_int(), g_cfg["yres"].to_int());
	SDL_SetWindowDisplayMode(win, &dsp);
	//const SDL_DisplayMode* mode)
	initGui(win, crate);
	crate.displayChanged = false;
}