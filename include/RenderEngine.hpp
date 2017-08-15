#pragma once

#include "RenderObject.hpp"
#include "main.hpp"
#include "VBOIndexer.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameManager;

enum ObjectType
{
	BLOCK_OT = 1,
	IND_BLOCK_OT,
	PLAYER_OT,
	BOMB_OT,
	ENEMY_1_OT,
	ENEMY_2_OT,
	ENEMY_3_OT,
	LIFE_POWERUP_OT,
	BOMB_STRENGTH_POWERUP_OT,
	BOMB_AMOUNT_POWERUP_OT
};

struct renderData
{
	float xPos;
	float yPos;
	float zPos;
	GLuint shaders;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint ModelView3x3MatrixID;
	GLuint LightID;
	GLuint TextureID;
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
    ObjectType type;
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

		void setViewMatrix(glm::mat4 viewMatrix);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		void computeMatricesFromInputs(SDL_Window *window);
		//static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
		GLuint loadBMP(const char * imagepath, GLuint texture);
		GLuint loadDDS(const char * imagepath, GLuint texture);
		bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);
		void computeTangentBasis(/*Inputs*/std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & uvs, std::vector<glm::vec3> & normals, /*Outputs*/std::vector<glm::vec3> & tangents, std::vector<glm::vec3> & bitangents);
		std::vector<renderData> initGlew(std::vector<renderData> rdata);
		int Draw(SDL_Window *window, std::vector<renderData> rdata, bool gameStarted);

	private:
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
		glm::vec3 position;

		float horizontalAngle,
				verticalAngle,
				FoV,
				speed,
				mouseSpeed;
};

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
