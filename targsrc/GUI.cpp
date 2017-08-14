
#include <main.hpp>
#include <GUI.hpp>

//#include <MenuFunction.hpp>

void               loadDefaultSettings(GUIFunctionCrate &crate)
{
    crate.settingContainer.resolution.push_back("800x600");
    crate.settingContainer.resolution.push_back("1280x720");
    crate.settingContainer.resolution.push_back("1920x1080");
    crate.settingContainer.resolution.setIterator( g_cfg["xres"].to_str() + "x" + g_cfg["yres"].to_str() );

    crate.settingContainer.fullScreen.push_back("Yes");
    crate.settingContainer.fullScreen.push_back("No");
    crate.settingContainer.fullScreen.setIterator( g_cfg["fullscreen"].to_str() == "true" ? "Yes" : "No" );
}

GUIFunctionCrate::GUIFunctionCrate()
{
    memset(this, 0, sizeof(GUIFunctionCrate));

    loadDefaultSettings(*this);
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

	//Load Layouts
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	crate.main = wmgr.loadLayoutFromFile("TestLayout.layout");

	crate.settings = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Settings.layout");
	crate.settings->setVisible(false);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(crate.main);

}

void		setupEvents(GUIFunctionCrate &crate)
{
	//Main menu
	CEGUI::NamedElement *start = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("StartGame");
	crate.MenuFunctions.push_back(new MenuFunction(start, CEGUI::PushButton::EventClicked, &startGameMainMenu, crate));

	CEGUI::NamedElement *settings = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("SettingsBtn");
	crate.MenuFunctions.push_back(new MenuFunction(settings, CEGUI::PushButton::EventClicked, &openSettingsMenu, crate));

	//Settings
	CEGUI::NamedElement *closeSettings = crate.settings->getChildElementRecursive("Close");
	crate.MenuFunctions.push_back(new MenuFunction(closeSettings, CEGUI::PushButton::EventClicked, &openMainMenu, crate));
	
	CEGUI::NamedElement *exit = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("Exit");
	crate.MenuFunctions.push_back(new MenuFunction(exit, CEGUI::PushButton::EventClicked, &setExit, crate));

    CEGUI::NamedElement *resolutionNext = crate.settings->getChildElementRecursive("ResolutionNext");
    crate.MenuFunctions.push_back(new MenuFunction(resolutionNext, CEGUI::PushButton::EventClicked, &resolutionNextClick, crate));

    CEGUI::NamedElement *resolutionPrev = crate.settings->getChildElementRecursive("ResolutionPrevious");
    crate.MenuFunctions.push_back(new MenuFunction(resolutionPrev, CEGUI::PushButton::EventClicked, &resolutionPreviousClick, crate));

    CEGUI::NamedElement *fullscreenNext = crate.settings->getChildElementRecursive("FullscreenNext");
    crate.MenuFunctions.push_back(new MenuFunction(fullscreenNext, CEGUI::PushButton::EventClicked, &fullscreenNextClick, crate));

    CEGUI::NamedElement *fullscreenPrev = crate.settings->getChildElementRecursive("FullscreenPrevious");
    crate.MenuFunctions.push_back(new MenuFunction(fullscreenPrev, CEGUI::PushButton::EventClicked, &fullscreenPreviousClick, crate));

}
//MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUIFunctionCrate	&var)

void        initValues(GUIFunctionCrate &crate)
{
    CEGUI::NamedElement *resolutionValue = crate.settings->getChildElementRecursive("ResolutionValue");
    resolutionValue->setProperty("Text", g_cfg["xres"].to_str() + "x" + g_cfg["yres"].to_str());
    CEGUI::NamedElement *fullscreenValue = crate.settings->getChildElementRecursive("FullscreenValue");
    fullscreenValue->setProperty("Text", g_cfg["fullscreen"].to_str() == "true" ? "Yes" : "No");
}

void		destroyGUI(GUIFunctionCrate &crate)
{
	/*
	TODO
	*/
	// Clean crate
	for (auto it = crate.MenuFunctions.begin(); it != crate.MenuFunctions.end(); it++)
		delete (*it);

	CEGUI::System::destroy();
	//CEGUI::OpenGL3Renderer::destroy(static_cast<CEGUI::OpenGL3Renderer&>(myRenderer));
}

double    initGui(SDL_Window *window, GUIFunctionCrate &crate)
{
	try
	{

		initializeKeyMap();
		CEGUI::OpenGL3Renderer::bootstrapSystem();
		CEGUI::OpenGL3Renderer& myRenderer = CEGUI::OpenGL3Renderer::create();

		SDL_ShowCursor(SDL_ENABLE);
		setupResourceGroups();
		loadResources(crate);
		setupEvents(crate);
        initValues(crate);
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