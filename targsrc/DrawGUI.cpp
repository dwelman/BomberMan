//
// Created by Dean DU TOIT on 2017/08/01.
//

#include <main.hpp>

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

void    initGui(SDL_Window *window, renderData rdata)
{
    unsigned int VBO, VAO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, 4096, NULL, GL_STATIC_DRAW);
    //   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);


    glUseProgram(rdata.shaders);

    float my_viewport[4];
    glGetFloatv(GL_VIEWPORT, my_viewport);


    float my_proj_matrix[16];
    MyOrtho2D(my_proj_matrix, 0.0f, my_viewport[2], my_viewport[3], 0.0f);
    GLint my_projection_ref = glGetUniformLocation(rdata.shaders, "uProjectionMatrix");
    glUniformMatrix4fv(my_projection_ref, 1, GL_FALSE, my_proj_matrix);

    //https://stackoverflow.com/questions/2571402/explain-the-usage-of-glortho
    glBindVertexArray(VAO);
}

void    drawGUI(SDL_Window *window, renderData rdata)
{
    static bool first = true;

    float vertices[] = {
            0, 0, 0,
            0, 100, 0,
            100, 100, 0,
            100, 100, 0,
            100, 0, 0,
            0, 0, 0
    };


    const float a_2d_triangle[] =
            {
                    200.0f, 10.0f,
                    10.0f, 200.0f,
                    400.0f, 200.0f
            };


    static unsigned int VBO, VAO;

    if (first) {


        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        // glBufferData(GL_ARRAY_BUFFER, 4096, NULL, GL_STATIC_DRAW);
        //   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);


        glUseProgram(rdata.shaders);

        float my_viewport[4];
        glGetFloatv(GL_VIEWPORT, my_viewport);


        float my_proj_matrix[16];
        MyOrtho2D(my_proj_matrix, 0.0f, my_viewport[2], my_viewport[3], 0.0f);
        GLint my_projection_ref = glGetUniformLocation(rdata.shaders, "uProjectionMatrix");
        glUniformMatrix4fv(my_projection_ref, 1, GL_FALSE, my_proj_matrix);

        //https://stackoverflow.com/questions/2571402/explain-the-usage-of-glortho
        glBindVertexArray(VAO);
        first = false;
    }

    glClearColor(0.3, 0.4, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
