#include "components/Render.hpp"

Render::Render() : BaseComponent(RENDER)
{

}

Render::Render(ObjectType type, bool active) : Render()
{
    m_type = type;
    m_active = active;
}

Render::Render(ObjectType type) : Render()
{
    m_type = type;
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

ObjectType  Render::GetObjectType() const
{
    return (m_type);
}

bool Render::GetActive()const
{
    return (m_active);
}

void        Render::SetObjectType(ObjectType type)
{
    m_type = type;
}

void Render::SetActive(bool active)
{
    m_active = active;
}