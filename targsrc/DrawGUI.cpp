//
// Created by Dean DU TOIT on 2017/08/01.
//

#include <main.hpp>
#include <GUI.hpp>
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

void MyOrtho2D(float* mat, float left, float right, float bottom, float top)
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

void    initGui(GUIData &guiData)
{
	guiData.shader = LoadShaders("shaders/gui2D_vertex.glsl", "shaders/gui2D_fragment.glsl");
	guiData.UIElements.push_back(new UIElement(0, 0, 100, 100));
	guiData.UIElements.push_back(new UIElement(100, 100, 100, 100));


	guiData.vertexBufferSize = guiData.UIElements.size();
	guiData.vertexBuffer = new float[guiData.vertexBufferSize * 18];
	int index = 0;
	for (auto it = guiData.UIElements.begin() ; 
		it != guiData.UIElements.end(); 
		it++, index += 18)
	{
		memcpy(&guiData.vertexBuffer[index], (*it)->getVertices(), sizeof(float) * 18);
	}
}

void    drawGUI(SDL_Window *window, renderData rdata, GUIData guiData)
{
    unsigned int VBO, VAO;
	float my_viewport[4];
	float my_proj_matrix[16];
	GLint my_projection_ref;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * guiData.UIElements.size() * 18, guiData.vertexBuffer, GL_DYNAMIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    glGetFloatv(GL_VIEWPORT, my_viewport);
    MyOrtho2D(my_proj_matrix, 0.0f, my_viewport[2], my_viewport[3], 0.0f);
    my_projection_ref = glGetUniformLocation(guiData.shader, "uProjectionMatrix");
    glUniformMatrix4fv(my_projection_ref, 1, GL_FALSE, my_proj_matrix);
    
    glUseProgram(guiData.shader);
    glDrawArrays(GL_TRIANGLES, 0, 6 * guiData.UIElements.size());
	glDisableVertexAttribArray(0);
}
