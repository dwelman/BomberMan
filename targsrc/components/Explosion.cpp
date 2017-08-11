//
// Created by David WELMAN on 2017/08/11.
//

#include "components/Explosion.hpp"

Explosion::Explosion() : BaseComponent(EXPLOSION)
{

}

Explosion::Explosion(std::size_t childExplosions, Vec3 dirction, double duration) : Explosion()
{
    m_childExplosions = childExplosions;
    m_direction = dirction;
    m_duration = duration;
}

Explosion::Explosion(Explosion const &e) : Explosion()
{
    *this = e;
}

Explosion::~Explosion()
{

}

Explosion &Explosion::operator=(Explosion const &e)
{
    m_childExplosions = e.m_childExplosions;
    m_direction = e.m_direction;
    m_duration = e.m_duration;
    return (*this);
}

std::size_t Explosion::GetChildExplosions() const
{
    return (m_childExplosions);
}

void Explosion::SetChildExplosions(std::size_t childExplosions)
{
    m_childExplosions = childExplosions;
}

Vec3 Explosion::GetDirection() const
{
    return (m_direction);
}

void Explosion::SetDirection(Vec3 const &direction)
{
    m_direction = direction;
}

double Explosion::GetDuration() const
{
    return (m_duration);
}

void Explosion::SetDuration(double duration)
{
    m_duration = duration;
}
