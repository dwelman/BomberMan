
#include <main.hpp>
#include <GUIRenderer.hpp>

void sayhi(void *param, UIElement *elem)
{
	static int count = 0;
	std::cout << count++ << std::endl;
}


void    initGui(GUIRenderer &guiRenderer)
{
	GLUIElement::shader = guiRenderer.GetShader();
	glUseProgram(guiRenderer.GetShader());

	GLUIElement	*n = new GLUIElement(0, 0, 720, 720);
	n->setMouseUp(&sayhi, guiRenderer);
	n->SetGLTexture(guiRenderer.GetShader(), guiRenderer.GetRenderer(), "textures/uv_checker large.png");
	guiRenderer.AddUIElement(n);
//	guiRenderer.AddUIElement(new GLUIElement(100, 100, 100, 100));
//	guiRenderer.AddUIElement(new GLUIElement(200, 200, 100, 100));
//	guiRenderer.AddUIElement(new GLUIElement(300, 300, 300, 300));
}