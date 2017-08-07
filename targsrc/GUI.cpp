
#include <main.hpp>
#include <GUIRenderer.hpp>

void sayhi(void *param, UIElement *elem)
{
	std::cout << "THAT TICKLES" << std::endl;
}


void    initGui(GUIRenderer &guiRenderer)
{
	UIElement	*n = new UIElement(0, 0, 100, 100);

	n->setMouseDown(&sayhi, guiRenderer);

	guiRenderer.AddUIElement(new UIElement(0, 0, 100, 100));
	guiRenderer.AddUIElement(new UIElement(100, 100, 100, 100));
	guiRenderer.AddUIElement(new UIElement(200, 200, 100, 100));
	guiRenderer.AddUIElement(new UIElement(300, 300, 300, 300));
}
