#include "components/Powerup.hpp"

Powerup::Powerup() : BaseComponent(POWERUP)
{

}

Powerup::Powerup(PowerupType type) : Powerup()
{
    m_type = type;
}

Powerup::Powerup(Powerup const &p) : Powerup()
{
    *this = p;
}

Powerup &Powerup::operator=(Powerup const &p)
{
    m_type = p.m_type;
    return (*this);
}

Powerup::~Powerup()
{

}

PowerupType Powerup::GetPowerupType() const
{
    return (m_type);
}
