#pragma once
#include <main.hpp>
#include <UIElement.hpp>

class GUIRenderer
{
private:
	GLuint					shader;
	std::vector<UIElement*>	UIElements;
	float					*vertexBuffer;
	size_t					vbCapacity;
	size_t					vertexBufferSize;
	int						vbIndex;
	unsigned int			VBO, VAO;
	float					my_viewport[4];
	float					my_proj_matrix[16];
	GLint					my_projection_ref;

	GUIRenderer() ;
	void	growVB();
public:
	~GUIRenderer();

	GUIRenderer(const char * vertex_file_path, const char * fragment_file_path);
	void		RenderGUI();
	void		AddUIElement(UIElement *element);
	void 		checkEvents(SDL_Event &e);
	static void Ortho2D(float* mat, float left, float right, float bottom, float top);

};

