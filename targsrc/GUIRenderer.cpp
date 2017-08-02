#include <GUIRenderer.hpp>


GUIRenderer::GUIRenderer() {};

GUIRenderer::GUIRenderer(const char * vertex_file_path, const char * fragment_file_path) : vbCapacity(16)
, vertexBufferSize(0), vbIndex(0)
{
	shader = LoadShaders(vertex_file_path, fragment_file_path);
	vertexBuffer = new float[vbCapacity * 18];
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

};

GUIRenderer::~GUIRenderer() {};

void 		GUIRenderer::checkEvents(SDL_Event &e)
{
	for (auto it = UIElements.begin(); it != UIElements.end(); it++)
	{
		(*it)->checkEvent(e, true);
	}
}

void GUIRenderer::Ortho2D(float* mat, float left, float right, float bottom, float top)
{
	// http://en.wikipedia.org/wiki/Orthographic_projection_(geometry)
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
	//Create VBO & VAO
	glLoadIdentity();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBufferSize, vertexBuffer, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	//Apply Orthograpic projection;
	glGetFloatv(GL_VIEWPORT, my_viewport);
	Ortho2D(my_proj_matrix, 0.0f, my_viewport[2], my_viewport[3], 0.0f);
	my_projection_ref = glGetUniformLocation(shader, "uProjectionMatrix");
	glUniformMatrix4fv(my_projection_ref, 1, GL_FALSE, my_proj_matrix);

	glUseProgram(shader);
	glDrawArrays(GL_TRIANGLES, 0, 6 * UIElements.size());
	//Cleanup
	glDisableVertexAttribArray(0);
	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &VAO);
}

void	 GUIRenderer::growVB()
{
	size_t	newCapacity = vbCapacity * 2;
	float	*newVertexBuffer = new float[18 * newCapacity];
	memcpy(newVertexBuffer, vertexBuffer, sizeof(float) * 18 * newCapacity);
	delete [] vertexBuffer;
	vertexBuffer = newVertexBuffer;
	vbCapacity = newCapacity;
}

void	GUIRenderer::AddUIElement(UIElement *element)
{
	if (UIElements.size() + 1 > vbCapacity)
		growVB();
	UIElements.push_back(element);
	//append vertices
	memcpy(&vertexBuffer[vertexBufferSize], element->getVertices(), sizeof(float) * 18);
	vertexBufferSize += 18;
}