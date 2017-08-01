#include "components/Render.hpp"

Render::Render() : BaseComponent(RENDER)
{

}

Render::Render(Render const &src) : Render()
{
    *this = src;
}

Render::Render(std::size_t mesh, std::size_t text, bool act) : Render()
{
    m_meshID = mesh;
    m_textureID = text;
    active = act;
}

Render::Render(std::size_t mesh, std::size_t text) : Render()
{
    m_meshID = mesh;
    m_textureID = text;
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

void Render::setMeshID(std::size_t mesh)
{
    m_meshID = mesh;
}

void Render::setTextureID(std::size_t text)
{
    m_textureID = text;
}

void Render::setActive(bool act)
{
    active = act;
}