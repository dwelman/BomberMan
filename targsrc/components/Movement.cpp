#include "components/Movement.hpp"

Movement::Movement() : BaseComponent(MOVEMENT)
{
    m_direction = Vec3(0.f, 0.f, 0.f);
    m_speed = 0;
}

Movement::Movement(Movement const &src) : Movement()
{
    *this = src;
}

Movement::Movement(Vec3 direction, float speed) : Movement()
{
    m_direction = direction;
    m_speed = speed;
}

Movement::Movement(float x, float y, float z, float speed) : Movement()
{
    m_direction = Vec3(x, y, z);
    m_speed = speed;
}

Movement::~Movement()
{

}

Movement &Movement::operator=(Movement const &cp)
{
    m_direction = cp.m_direction;
    m_speed = cp.m_speed;
    return(*this);
}

Vec3 Movement::GetDirection()const
{
    return(m_direction);
}

float Movement::GetSpeed() const
{
    return (m_speed);
}

void Movement::SetDirection(Vec3 vel)
{
    m_direction = vel;
}

void Movement::SetDirection(float x, float y, float z)
{
    m_direction = Vec3(x, y, z);
}

void Movement::SetSpeed(float speed)
{
    m_speed = speed;
}
