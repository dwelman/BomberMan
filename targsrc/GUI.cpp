
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

bool setExit(const CEGUI::EventArgs& /*e*/, void *var) 
{
	bool	*must_exit = reinterpret_cast<bool*>(var);

	*must_exit = true;
	return (true);
};

inline void		loadResources()
{
	//Load Schemes
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");

	//Setup Defaults
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("Jura-18");

	//Load Layouts
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* myRoot = wmgr.loadLayoutFromFile("Testlayout.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

}

void		setupEvents(GUIFunctionCrate &crate)
{
	//Main menu
	CEGUI::NamedElement *exit = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("Exit");
	crate.triggerExit =	new MenuFunction<bool*> (exit, CEGUI::PushButton::EventClicked, &setExit, crate.triggerExitParam);
}

void		destroyGUI()
{
	/*
	TODO
	*/
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

void	captureInputForGameLogic(SDL_Event &e, bool & must_quit)
{
	if (e.type == SDL_QUIT)
		must_quit = true;
	//TODO game logic stoofs
}

void	captureInputForState(SDL_Event &e, bool & must_quit)
{
	if (e.type == SDL_KEYDOWN)
	{
		
	}
}

void	renderGUIInjectEvents(SDL_Window *window, double guiLastTimePulse, bool &must_quit)
{
	CEGUI::GUIContext&	context = CEGUI::System::getSingleton().getDefaultGUIContext();
	SDL_Event			e;

	while (SDL_PollEvent(&e))
	{
		injectInput(must_quit, context, e);
		captureInputForGameLogic(e, must_quit);
		captureInputForState(e, must_quit);
	}
	injectTimePulse(guiLastTimePulse);
	glDisable(GL_DEPTH_TEST);
	CEGUI::System::getSingleton().renderAllGUIContexts();
	glEnable(GL_DEPTH_TEST);
}