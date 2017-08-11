
#include <main.hpp>
#include <GUI.hpp>

//#include <MenuFunction.hpp>

GUIFunctionCrate::~GUIFunctionCrate()
{
	memset(this, 0, sizeof(GUIFunctionCrate));
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

void		loadResources()
{
	//Load Schemes
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");

	//Setup Defaults
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("Jura-18");

	//Load Layouts
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* myRoot = wmgr.loadLayoutFromFile("TestLayout.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

}

void		setupEvents(GUIFunctionCrate &crate)
{
	//Main menu
	CEGUI::NamedElement *exit = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("Exit");
	crate.MenuFunctions.push_back(new MenuFunction(exit, CEGUI::PushButton::EventClicked, &setExit, crate));

    CEGUI::NamedElement *start = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("StartGame");
    crate.MenuFunctions.push_back(new MenuFunction(start, CEGUI::PushButton::EventClicked, &startGameMainMenu, crate));
}
//MenuFunction(CEGUI::NamedElement *_element, const CEGUI::String &name, ccev eventFunction, GUIFunctionCrate	&var)

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

		SDL_ShowCursor(SDL_DISABLE);
		setupResourceGroups();
		loadResources();
		setupEvents(crate);
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