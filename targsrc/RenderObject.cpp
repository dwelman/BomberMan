#include "RenderObject.hpp"

RenderObject::RenderObject()
{

}

RenderObject::RenderObject(const RenderObject &rObj)
{
    *this = rObj;
}

RenderObject &RenderObject::operator=(const RenderObject &rhs)
{
    shaders = rhs.shaders;
    MatrixID = rhs.MatrixID;
    ViewMatrixID = rhs.ViewMatrixID;
    ModelMatrixID = rhs.ModelMatrixID;
    ModelView3x3MatrixID = rhs.ModelView3x3MatrixID;
    LightID = rhs.LightID;
    TextureID = rhs.TextureID;
    DiffuseTextureID = rhs.DiffuseTextureID;
    NormalTextureID = rhs.NormalTextureID;
    SpecularTextureID = rhs.SpecularTextureID;
    VertexBuffer = rhs.VertexBuffer;
    UVBuffer = rhs.UVBuffer;
    NormalBuffer = rhs.NormalBuffer;
    TangentBuffer = rhs.TangentBuffer;
    BitangentBuffer = rhs.BitangentBuffer;
    ElementBuffer = rhs.ElementBuffer;
    Indices = rhs.Indices;
    indexed_vertices = rhs.indexed_vertices;
    indexed_uvs = rhs.indexed_uvs;
    indexed_normals = rhs.indexed_normals;
    indexed_tangents = rhs.indexed_tangents;
    indexed_bitangents = rhs.indexed_bitangents;
    objVertices = rhs.objVertices;
    objUVS = rhs.objUVS;
    objNormals = rhs.objNormals;
    objTangents = rhs.objTangents;
    objBitangents = rhs.objBitangents;
    return *this;
}

RenderObject::~RenderObject()
{

}

void RenderObject::setShaders(GLuint &shaders)
{
    this->shaders = shaders;
}

void RenderObject::setMatrixID(GLuint &MatrixID)
{
    this->MatrixID = MatrixID;
}

void RenderObject::setViewMatrixID(GLuint &ViewMatrixID)
{
    this->ViewMatrixID = ViewMatrixID;
}

void RenderObject::setModelMatrixID(GLuint &ModelMatrixID)
{
    this->ModelMatrixID = ModelMatrixID;
}

void RenderObject::setModelView3x3MatrixID(GLuint &ModelView3x3MatrixID)
{
    this->ModelView3x3MatrixID = ModelView3x3MatrixID;
}

void RenderObject::setLightID(GLuint &LightID)
{
    this->LightID = LightID;
}

void RenderObject::setTextureID(GLuint &TextureID)
{
    this->TextureID = TextureID;
}

void RenderObject::setDiffuseTextureID(GLuint &DiffuseTextureID)
{
    this->DiffuseTextureID = DiffuseTextureID;
}

void RenderObject::setNormalTextureID(GLuint &NormalTextureID)
{
    this->NormalTextureID = NormalTextureID;
}

void RenderObject::setSpecularTextureID(GLuint &SpecularTextureID)
{
    this->SpecularTextureID = SpecularTextureID;
}

void RenderObject::setVertexBuffer(GLuint &VertexBuffer)
{
    this-> VertexBuffer = VertexBuffer;
}

void RenderObject::setUVBuffer(GLuint &UVBuffer)
{
    this->UVBuffer = UVBuffer;
}

void RenderObject::setNormalBuffer(GLuint &NormalBuffer)
{
    this->NormalBuffer = NormalBuffer;
}

void RenderObject::setTangentBuffer(GLuint &TangentBuffer)
{
    this->TangentBuffer = TangentBuffer;
}

void RenderObject::setBitangentBuffer(GLuint &BitangentBuffer)
{
    this->BitangentBuffer = BitangentBuffer;
}

void RenderObject::setElementBuffer(GLuint &ElementBuffer)
{
    this->ElementBuffer = ElementBuffer;
}

void RenderObject::setIndices(std::vector<unsigned short> &Indices)
{
    this->Indices = Indices;
}

void RenderObject::setIndexedVertices(std::vector<glm::vec3> &indexed_vertices)
{
    this->indexed_vertices = indexed_vertices;
}

void RenderObject::setIndexedUVS(std::vector<glm::vec2> &indexed_uvs)
{
    this->indexed_uvs = indexed_uvs;
}

void RenderObject::setIndexedNormals(std::vector<glm::vec3> &indexed_normals)
{
    this->indexed_normals = indexed_normals;
}

void RenderObject::setIndexedTangents(std::vector<glm::vec3> &indexed_tangents)
{
    this->indexed_tangents = indexed_tangents;
}

void RenderObject::setIndexedBitangents(std::vector<glm::vec3> &indexed_bitangents)
{
    this->indexed_bitangents = indexed_bitangents;
}

void RenderObject::setObjVertices(std::vector<glm::vec3> &objVertices)
{
    this->objVertices = objVertices;
}

void RenderObject::setObjUVS(std::vector<glm::vec2> &objUVS)
{
    this->objUVS = objUVS;
}

void RenderObject::setObjNormals(std::vector<glm::vec3> &objNormals)
{
    this->objNormals = objNormals;
}

void RenderObject::setObjTangents(std::vector<glm::vec3> &objTangents)
{
    this->objTangents = objTangents;
}

void RenderObject::setObjBitangents(std::vector<glm::vec3> &objBitangents)
{
    this->objBitangents = objBitangents;
}

GLuint RenderObject::getShaders()
{
    return this->shaders;
}

GLuint RenderObject::getMatrixID()
{
    return this->MatrixID;
}

GLuint RenderObject::getViewMatrixID()
{
    return this->ViewMatrixID;
}

GLuint RenderObject::getModelMatrixID()
{
    return this->ModelMatrixID;
}

GLuint RenderObject::getModelView3x3MatrixID()
{
    return this->ModelView3x3MatrixID;
}

GLuint RenderObject::getLightID()
{
    return this->LightID;
}

GLuint RenderObject::getTextureID()
{
    return this->TextureID;
}

GLuint RenderObject::getDiffuseTextureID()
{
    return this->DiffuseTextureID;
}

GLuint RenderObject::getNormalTextureID()
{
    return this->NormalTextureID;
}

GLuint RenderObject::getSpecularTextureID()
{
    return this->SpecularTextureID;
}

GLuint RenderObject::getVertexBuffer()
{
    return this->VertexBuffer;
}

GLuint RenderObject::getUVBuffer()
{
    return this->UVBuffer;
}

GLuint RenderObject::getNormalBuffer()
{
    return this->NormalBuffer;
}

GLuint RenderObject::getTangentBuffer()
{
    return this->TangentBuffer;
}

GLuint RenderObject::getBitangentBuffer()
{
    return this->BitangentBuffer;
}

GLuint RenderObject::getElementBuffer()
{
    return this->ElementBuffer;
}

std::vector<unsigned short> RenderObject::getIndices()
{
    return this->Indices;
}

std::vector<glm::vec3> RenderObject::getIndexedVertices()
{
    return this->indexed_vertices;
}

std::vector<glm::vec2> RenderObject::getIndexedUVS()
{
    return this->indexed_uvs;
}

std::vector<glm::vec3> RenderObject::getIndexedNormals()
{
    return this->indexed_normals;
}

std::vector<glm::vec3> RenderObject::getIndexedTangents()
{
    return this->indexed_tangents;
}
std::vector<glm::vec3> RenderObject::getIndexedBitangents()
{
    return this->indexed_bitangents;
}

std::vector<glm::vec3> RenderObject::getObjVertices()
{
    return this->objVertices;
}

std::vector<glm::vec2> RenderObject::getObjUVS()
{
    return this->objUVS;
}

std::vector<glm::vec3> RenderObject::getObjNormals()
{
    return this->objNormals;
}

std::vector<glm::vec3> RenderObject::getObjTangents()
{
    return this->objTangents;
}

std::vector<glm::vec3> RenderObject::getObjBitangents()
{
    return this->objBitangents;
}