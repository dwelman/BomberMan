
#include <main.hpp>
#include <GUIRenderer.hpp>

void    initGui(GUIRenderer &guiRenderer)
{
	guiRenderer.AddUIElement(new UIElement(0, 0, 100, 100));
	guiRenderer.AddUIElement(new UIElement(100, 100, 100, 100));
	guiRenderer.AddUIElement(new UIElement(200, 200, 100, 100));

	guiRenderer.AddUIElement(new UIElement(300, 300, 300, 300));
}
