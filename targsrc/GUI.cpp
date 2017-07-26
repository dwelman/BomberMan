
#include <main.hpp>

void	startGUI(SDL_Window *window)
{
	// Create VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Identify vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer, put resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// Describe 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Dark blue background
	float Red = 0.0f;
	float Green = 0.0f;
	float Blue = 0.0f;
	glClearColor(Red, Green, Blue, 0.0f);

	SDL_Event e;

	do {
		//draw
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,			// Attribute 0.  Must match the Layout in the shader.
			3,			// Size
			GL_FLOAT,	// Type
			GL_FALSE,	// Normalise
			0,			// Stride
			(void *)0	// Array buffer offset
		);

		// Draw from array
		glDrawArrays(GL_TRIANGLES, 0, 3);  // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		//TwDraw();
		// Swap buffers
		SDL_GL_SwapWindow(window);
		SDL_Delay(200);
		SDL_PollEvent(&e);

	} // Check if the ESC key was pressed or the window was closed
	while (e.type != SDL_QUIT);

}