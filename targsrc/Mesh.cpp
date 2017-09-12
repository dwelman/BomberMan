#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include "assimp/scene.h"
#include "assimp/postprocess.h"


/**
*	Constructor, loading the specified aiMesh
**/
Mesh::MeshEntry::MeshEntry(aiMesh *mesh) {
    vbo[VERTEX_BUFFER] = NULL;
    vbo[TEXCOORD_BUFFER] = NULL;
    vbo[NORMAL_BUFFER] = NULL;
    vbo[INDEX_BUFFER] = NULL;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    elementCount = mesh->mNumFaces * 3;

    if(mesh->HasPositions()) {
        float *vertices = new float[mesh->mNumVertices * 3];
        for(int i = 0; i < mesh->mNumVertices; ++i) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        glGenBuffers(1, &vbo[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray (0);

        delete vertices;
    }


    if(mesh->HasTextureCoords(0)) {
        float *texCoords = new float[mesh->mNumVertices * 2];
        for(int i = 0; i < mesh->mNumVertices; ++i) {
            texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
            texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y * -1;
        }

        glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(glm::vec2), texCoords, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray (1);

        delete texCoords;
    }


    if(mesh->HasNormals()) {
        float *normals = new float[mesh->mNumVertices * 3];
        for(int i = 0; i < mesh->mNumVertices; ++i) {
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 3 + 1] = mesh->mNormals[i].y;
            normals[i * 3 + 2] = mesh->mNormals[i].z;
        }

        glGenBuffers(1, &vbo[NORMAL_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(glm::vec3), normals, GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray (2);

        delete normals;
    }


    if(mesh->HasFaces()) {
        unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];
        for(int i = 0; i < mesh->mNumFaces; ++i) {
            indices[i * 3] = mesh->mFaces[i].mIndices[0];
            indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
        }

        glGenBuffers(1, &vbo[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mNumFaces * sizeof(glm::vec3), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray (3);

        delete indices;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
*	Deletes the allocated OpenGL buffers
**/
Mesh::MeshEntry::~MeshEntry() {
    if(vbo[VERTEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
    }

    if(vbo[TEXCOORD_BUFFER]) {
        glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
    }

    if(vbo[NORMAL_BUFFER]) {
        glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
    }

    if(vbo[INDEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
    }

    glDeleteVertexArrays(1, &vao);
}

/**
*	Renders this MeshEntry
**/
void Mesh::MeshEntry::render()
{
//    glm::mat4 ModelMatrix3 = glm::mat4(1.0);
//    ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3((gameObject.GetPosition().GetX() * 2) - 4, gameObject.GetPosition().GetZ() * 2, (gameObject.GetPosition().GetY() * 2) - 4));
//    ModelMatrix3 = glm::rotate(ModelMatrix3, gameObject.GetDirection() * 1.575f, glm::vec3(0, 1, 0));
//    glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
//
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
//    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

/**
*	Mesh constructor, loads the specified filename if supported by Assimp
**/
Mesh::Mesh(const char *filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, NULL);
    if(!scene) {
        printf("Unable to load mesh: %s\n", importer.GetErrorString());
    }

    for(int i = 0; i < scene->mNumMeshes; ++i) {
        meshEntries.push_back(new Mesh::MeshEntry(scene->mMeshes[i]));
    }
}

/**
*	Clears all loaded MeshEntries
**/
Mesh::~Mesh(void)
{
    for(int i = 0; i < meshEntries.size() - 1; ++i) {
        delete meshEntries.at(i);
    }
    meshEntries.clear();
}

/**
*	Renders all loaded MeshEntries
**/
void Mesh::render() {
    for(int i = 0; i < meshEntries.size(); ++i) {
        meshEntries.at(i)->render();
    }
}