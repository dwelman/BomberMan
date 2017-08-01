#ifndef BOMBERMAN_RENDERENGINE_HPP
#define BOMBERMAN_RENDERENGINE_HPP

#include "main.hpp"
#include "VBOIndexer.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct renderData
{
    GLuint shaders;
    GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	GLuint TextureID;
    GLuint *Textures;
	GLuint TextureID2;
    GLuint VertexBuffer;
    GLuint UVBuffer;
	GLuint NormalBuffer;
	GLuint ElementBuffer;
	std::vector<unsigned short> Indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUVS;
	std::vector<glm::vec3> objNormals;
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
