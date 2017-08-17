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

Movement::Movement(Vec3 direction, float speed, Vec3 destination) : Movement()
{
    m_direction = direction;
    m_speed = speed;
    m_destination = destination;
    m_canChangeDirection = true;
}

Movement::~Movement()
{

}

Movement &Movement::operator=(Movement const &cp)
{
    m_direction = cp.m_direction;
    m_speed = cp.m_speed;
    m_destination = cp.m_destination;
    m_canChangeDirection = cp.m_canChangeDirection;
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

void Movement::SetSpeed(float speed)
{
    m_speed = speed;
}

void Movement::SetCanChangeDirection(bool b)
{
    m_canChangeDirection = b;
}

Vec3 Movement::GetDestination() const
{
    return (m_destination);
}

void Movement::SetDestination(Vec3 dest)
{
    m_destination = dest;
}

bool Movement::GetCanChangeDirection() const
{
    return (m_canChangeDirection);
}
