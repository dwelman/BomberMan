#ifndef BOMBERMAN_RENDERENGINE_HPP
#define BOMBERMAN_RENDERENGINE_HPP

#include "main.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct renderData
{
    GLuint shaders;
    GLuint MatrixID;
    GLuint Texture;
    GLuint VertexBuffer;
    GLuint UVBuffer;
    bool objRes;
    int res;
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint loadBMP(const char * imagepath);
bool loadOBJ(
        const char * path,
        std::vector<glm::vec3> & out_vertices,
        std::vector<glm::vec2> & out_uvs,
        std::vector<glm::vec3> & out_normals
);
renderData     initGlew();
int     draw(SDL_Window *window, renderData rdata);


#endif //BOMBERMAN_RENDERENGINE_HPP
