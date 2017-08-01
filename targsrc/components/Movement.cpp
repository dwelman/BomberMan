#include "components/Movement.hpp"

Movement::Movement() : BaseComponent(MOVEMENT)
{

}

Movement::Movement(Movement const &src) : Movement()
{
    *this = src;
}

Movement::Movement(Vec3 vel) : Movement()
{
    m_velocity = vel;
}

Movement::Movement(float x, float y, float z) : Movement()
{
    m_velocity = Vec3(x, y, z);
}

Movement::~Movement()
{

}

Movement &Movement::operator=(Movement const &cp)
{
    m_velocity = cp.getVelocity();
    return(*this);
}

Vec3 Movement::getVelocity()const
{
    return(m_velocity);
}

void Movement::setVelocity(Vec3 vel)
{
    m_velocity = vel;
}

void Movement::setVelocity(float x, float y, float z)
{
    m_velocity = Vec3(x,y,z);
}