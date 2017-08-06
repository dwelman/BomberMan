#include <GUIRenderer.hpp>


GUIRenderer::GUIRenderer() {};

GUIRenderer::GUIRenderer(SDL_Window *win, const char * vertex_file_path, const char * fragment_file_path) : vbCapacity(16)
, vertexBufferSize(0), vbIndex(0)
{
	shader = LoadShaders(vertex_file_path, fragment_file_path);
	sdlRenderer = SDL_CreateRenderer(win, -1, 0);
	if (!sdlRenderer)
	{
		std::cerr << "SDL Renderer could not be created, terminating..." << std::endl;
		exit(-1);
	}
};

GUIRenderer::~GUIRenderer() 
{
	SDL_DestroyRenderer(sdlRenderer);
};

void 		GUIRenderer::CheckEvents(SDL_Event &e)
{
	for (auto it = UIElements.begin(); it != UIElements.end(); it++)
	{
		(*it)->checkEvent(e, true);
	}
}

SDL_Renderer * GUIRenderer::GetRenderer()
{
	return (sdlRenderer);
}

GLuint GUIRenderer::GetShader()
{
	return (shader);
}

void GUIRenderer::Ortho2D(float* mat, float left, float right, float bottom, float top)
{
	const float zNear = -1.0f;
	const float zFar = 1.0f;
	const float inv_z = 1.0f / (zFar - zNear);
	const float inv_y = 1.0f / (top - bottom);
	const float inv_x = 1.0f / (right - left);

	//first column
	*mat++ = (2.0f*inv_x);
	*mat++ = (0.0f);
	*mat++ = (0.0f);
	*mat++ = (0.0f);

	//second
	*mat++ = (0.0f);
	*mat++ = (2.0*inv_y);
	*mat++ = (0.0f);
	*mat++ = (0.0f);

	//third
	*mat++ = (0.0f);
	*mat++ = (0.0f);
	*mat++ = (-2.0f*inv_z);
	*mat++ = (0.0f);

	//fourth
	*mat++ = (-(right + left)*inv_x);
	*mat++ = (-(top + bottom)*inv_y);
	*mat++ = (-(zFar + zNear)*inv_z);
	*mat++ = (1.0f);
}

void	GUIRenderer::RenderGUI()
{
	glUseProgram(shader);
	//Apply Orthograpic projection;
	glGetFloatv(GL_VIEWPORT, my_viewport);
	Ortho2D(my_proj_matrix, 0.0f, my_viewport[2], my_viewport[3], 0.0f);
	my_projection_ref = glGetUniformLocation(shader, "uProjectionMatrix");
	glUniformMatrix4fv(my_projection_ref, 1, GL_FALSE, my_proj_matrix);

	int elemIndex = 0;
	for (auto it = UIElements.begin(); it != UIElements.end(); it++)
	{
		(*it)->draw(shader);
	}
}

// Probably Never gonna use anymore
void	 GUIRenderer::growVB()
{
	size_t	newCapacity = vbCapacity * 2;
	float	*newVertexBuffer = new float[18 * newCapacity];
	memcpy(newVertexBuffer, vertexBuffer, sizeof(float) * 18 * newCapacity);
	delete [] vertexBuffer;
	vertexBuffer = newVertexBuffer;
	vbCapacity = newCapacity;
}

void	GUIRenderer::AddUIElement(GLUIElement *element)
{
	UIElements.push_back(element);
}