#include "components/Render.hpp"

Render::Render() : BaseComponent(RENDER)
{

}

Render::Render(std::size_t meshID, std::size_t textureID, bool active) : Render()
{
    m_meshID = meshID;
    m_textureID = textureID;
    m_active = active;
}

Render::Render(std::size_t mesh, std::size_t text) : Render()
{
    m_meshID = mesh;
    m_textureID = text;
    m_active = true;
}

Render::Render(Render const &src) : Render()
{
    *this = src;
}

Render::~Render()
{

}

Render &Render::operator=(Render const &cp)
{
    return(*this);
}

std::size_t Render::getMeshID()const
{
    return m_meshID;
}

std::size_t Render::getTextureID()const
{
    return m_textureID;
}

bool Render::getActive()const
{
    return active;
}

void Render::setMeshID(std::size_t meshID)
{
    m_meshID = meshID;
}

void Render::setTextureID(std::size_t textureID)
{
    m_textureID = textureID;
}

void Render::setActive(bool active)
{
    m_active = active;
}