#pragma once

#include <vector>
#include <SDL_opengl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class RenderObject
{
    public:
        RenderObject();
        RenderObject(const RenderObject &rObj);
        RenderObject &operator=(const RenderObject &rhs);
        ~RenderObject();

        void setShaders(GLuint &shaders);
        void setMatrixID(GLuint &MatrixID);
        void setViewMatrixID(GLuint &ViewMatrixID);
        void setModelMatrixID(GLuint &ModelMatrixID);
        void setModelView3x3MatrixID(GLuint &ModelView3x3MatrixID);
        void setLightID(GLuint &LightID);
        void setTextureID(GLuint &TextureID);
        void setDiffuseTextureID(GLuint &DiffuseTextureID);
        void setNormalTextureID(GLuint &NormalTextureID);
        void setSpecularTextureID(GLuint &SpecularTextureID);
        void setVertexBuffer(GLuint &VertexBuffer);
        void setUVBuffer(GLuint &UVBuffer);
        void setNormalBuffer(GLuint &NormalBuffer);
        void setTangentBuffer(GLuint &TangentBuffer);
        void setBitangentBuffer(GLuint &BitangentBuffer);
        void setElementBuffer(GLuint &ElementBuffer);
        void setIndices(std::vector<unsigned short> &Indices);
        void setIndexedVertices(std::vector<glm::vec3> &indexed_vertices);
        void setIndexedUVS(std::vector<glm::vec2> &indexed_uvs);
        void setIndexedNormals(std::vector<glm::vec3> &indexed_normals);
        void setIndexedTangents(std::vector<glm::vec3> &indexed_tangents);
        void setIndexedBitangents(std::vector<glm::vec3> &indexed_bitangents);
        void setObjVertices(std::vector<glm::vec3> &objVertices);
        void setObjUVS(std::vector<glm::vec2> &objUVS);
        void setObjNormals(std::vector<glm::vec3> &objNormals);
        void setObjTangents(std::vector<glm::vec3> &objTangents);
        void setObjBitangents(std::vector<glm::vec3> &objBitangents);
        GLuint getShaders();
        GLuint getMatrixID();
        GLuint getViewMatrixID();
        GLuint getModelMatrixID();
        GLuint getModelView3x3MatrixID();
        GLuint getLightID();
        GLuint getTextureID();
        GLuint getDiffuseTextureID();
        GLuint getNormalTextureID();
        GLuint getSpecularTextureID();
        GLuint getVertexBuffer();
        GLuint getUVBuffer();
        GLuint getNormalBuffer();
        GLuint getTangentBuffer();
        GLuint getBitangentBuffer();
        GLuint getElementBuffer();
        std::vector<unsigned short> getIndices();
        std::vector<glm::vec3> getIndexedVertices();
        std::vector<glm::vec2> getIndexedUVS();
        std::vector<glm::vec3> getIndexedNormals();
        std::vector<glm::vec3> getIndexedTangents();
        std::vector<glm::vec3> getIndexedBitangents();
        std::vector<glm::vec3> getObjVertices();
        std::vector<glm::vec2> getObjUVS();
        std::vector<glm::vec3> getObjNormals();
        std::vector<glm::vec3> getObjTangents();
        std::vector<glm::vec3> getObjBitangents();

    private:
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
        GLuint VertexBuffer;
        GLuint UVBuffer;
        GLuint NormalBuffer;
        GLuint TangentBuffer;
        GLuint BitangentBuffer;
        GLuint ElementBuffer;
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
};