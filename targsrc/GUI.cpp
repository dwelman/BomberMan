
#include <main.hpp>
#include <GUI.hpp>

double    initGui(SDL_Window *window)
{
	initializeKeyMap();
	CEGUI::OpenGL3Renderer::bootstrapSystem();
	CEGUI::OpenGL3Renderer& myRenderer = CEGUI::OpenGL3Renderer::create();
	/*
	TODO 
	CEGUI::System::destroy();
	CEGUI::OpenGL3Renderer::destroy(static_cast<CEGUI::OpenGL3Renderer&>(*myRenderer));
	*/
	SDL_ShowCursor(SDL_DISABLE);

	using namespace CEGUI;
	SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

	WindowManager& wmgr = WindowManager::getSingleton();
	Window* myRoot = wmgr.createWindow("DefaultWindow", "root");
	System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);
	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow("TaharezLook/FrameWindow", "testWindow"));
	myRoot->addChild(fWnd);
	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition(UVector2(UDim(0.25f, 0.0f), UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(USize(UDim(0.5f, 0.0f), UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");

	return (0.001 * static_cast<double>(SDL_GetTicks()));
}

void	captureInputForGameLogic(SDL_Event &e, bool & must_quit)
{
	if (e.type == SDL_QUIT)
		must_quit = true;
	//TODO game logic stoofs
}

void	renderGUIInjectEvents(SDL_Window *window, double guiLastTimePulse, bool &must_quit)
{
	CEGUI::GUIContext&	context = CEGUI::System::getSingleton().getDefaultGUIContext();
	SDL_Event			e;

	while (SDL_PollEvent(&e))
	{
		injectInput(must_quit, context, e);
		captureInputForGameLogic(e, must_quit);
	}
	injectTimePulse(guiLastTimePulse);
	CEGUI::System::getSingleton().renderAllGUIContexts();
}