#pragma once
#include <main.hpp>
#include <GLUIElement.hpp>

class GUIRenderer
{
private:
	GLuint					shader;
	std::vector<GLUIElement*>	UIElements;
	float					*vertexBuffer;
	size_t					vbCapacity;
	size_t					vertexBufferSize;
	int						vbIndex;
	unsigned int			VBO, VAO;
	float					my_viewport[4];
	float					my_proj_matrix[16];
	GLint					my_projection_ref;
	SDL_Renderer			*sdlRenderer;
	GUIRenderer() ;
	void	growVB();
public:
	~GUIRenderer();

	GUIRenderer(SDL_Window *win, const char * vertex_file_path, const char * fragment_file_path);
	void			RenderGUI();
	void			AddUIElement(GLUIElement *element);
	void 			CheckEvents(SDL_Event &e);
	SDL_Renderer	*GetRenderer();
	GLuint			GetShader();

	static void Ortho2D(float* mat, float left, float right, float bottom, float top);

};

