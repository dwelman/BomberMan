#pragma once

#include "Mesh.hpp"
#include "RenderObject.hpp"
#include "GameObjectRenderInfo.hpp"
#include "Clock.hpp"
#include "main.hpp"
#include "VBOIndexer.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

class GameManager;
class GameObjectRenderInfo;
class Mesh;

struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a;
	float size, angle, weight;
	float life;
	float cameradistance;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

struct renderData
{
//	float xPos;
//	float yPos;
//	float zPos;
	GLuint shaders;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint ModelView3x3MatrixID;
	GLuint LightID;
	GLuint DepthBiasID;
	GLuint ShadowMapID;
	//GLuint TextureID;
	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;
	GLuint *Textures;
	GLuint VertexBuffer;
	GLuint UVBuffer;
	GLuint NormalBuffer;
	GLuint TangentBuffer;
	GLuint BitangentBuffer;
	GLuint ElementBuffer;
    //ObjectType type;
	std::vector<unsigned short> Indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> indexed_tangents;
	std::vector<glm::vec3> indexed_bitangents;
	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUVS;
	std::vector<glm::vec3> objNormals;
	std::vector<glm::vec3> objTangents;
	std::vector<glm::vec3> objBitangents;
	int objRes;
	int res;
};

class RenderEngine
{
	public:
		RenderEngine();
		RenderEngine(const RenderEngine &renderEngine);
		RenderEngine &operator = (const RenderEngine &rhs);
		~RenderEngine();

        void handleResize(int w, int h);
		void setViewMatrix(glm::mat4 viewMatrix);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		void computeMatricesFromInputs(SDL_Window *window, SDL_Event &event);
		//static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
		GLuint loadBMP(const char * imagepath, GLuint texture);
		GLuint loadDDS(const char * imagepath, GLuint texture);
		bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);
		void computeTangentBasis(/*Inputs*/std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & uvs, std::vector<glm::vec3> & normals, /*Outputs*/std::vector<glm::vec3> & tangents, std::vector<glm::vec3> & bitangents);
		int FindUnusedParticle();
		void SortParticles();
		void drawParticles(std::vector<GameObjectRenderInfo> parts);
		void initGlew();
		int Draw(SDL_Window *window, bool gameStarted, std::vector<GameObjectRenderInfo>   gameObjects);

	private:
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
		glm::vec3 position;
        glm::vec3 playerPosition;
		std::vector<renderData> rdata;
        std::vector<Mesh> mesh;
		const int MaxParticles = 10000;
		Particle ParticlesContainer[10000];
		int LastUsedParticle = 0;

		float horizontalAngle,
				verticalAngle,
				FoV,
				speed,
				mouseSpeed;
};

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
