#include "components/Collision.hpp"
#include <iostream>

Collision::Collision() : BaseComponent(COLLISION)
{

}

Collision::Collision(Vec3 const &colliderSize) : Collision()
{
    m_colliderSize = colliderSize;
    m_checkCollision = false;
}

Collision::Collision(Vec3 const & colliderSize, bool checkCollision) : Collision()
{
    m_colliderSize = colliderSize;
    m_checkCollision = checkCollision;
}

Collision::Collision(float x, float y, float z) : Collision()
{
    m_colliderSize = Vec3(x, y, z);
    m_checkCollision = false;
}

Collision::Collision(float x, float y, float z, bool checkCollision) : Collision()
{
    m_colliderSize = Vec3(x, y, z);
    m_checkCollision = checkCollision;
}

Collision::Collision(Collision const &c) : Collision()
{
    *this = c;
}

Collision::~Collision()
{

}

Collision   &Collision::operator=(Collision const &c)
{
    m_colliderSize = c.m_colliderSize;
	m_checkCollision = c.m_checkCollision;
    return (*this);
}

Vec3        Collision::GetColliderSize() const
{
    return (m_colliderSize);
}

void        Collision::SetColliderSize(Vec3 const &v)
{
    m_colliderSize = v;
}

bool Collision::GetCheckCollision() const
{
	return (m_checkCollision);
}

void Collision::SetCheckCollision(bool checkCollision)
{
	m_checkCollision = checkCollision;
}