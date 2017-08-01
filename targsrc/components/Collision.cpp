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

bool        Collision::CheckCollision(Position const &thisPos, Position const &otherPos, Collision const &otherCollide) const
{
    bool    collisionX;
    bool    collisionY;
    bool    collisionZ;

    //The corner of the x axis for this object
    float   thisPosX = thisPos.GetPosition().GetX() - m_colliderSize.GetX();
    //The corner of the x axis for the other object
    float   otherPosX = otherPos.GetPosition().GetX() - otherCollide.GetColliderSize().GetX();

    //The corner of the y axis for this object
    float   thisPosY = thisPos.GetPosition().GetY() - m_colliderSize.GetY();
    //The corner of the y axis for the other object
    float   otherPosY = otherPos.GetPosition().GetY() - otherCollide.GetColliderSize().GetY();

    //The corner of the y axis for this object
    float   thisPosZ = thisPos.GetPosition().GetZ() - m_colliderSize.GetZ();
    //The corner of the y axis for the other object
    float   otherPosZ = otherPos.GetPosition().GetZ() - otherCollide.GetColliderSize().GetZ();

    //The collider size is doubled to get from the one corner to the other
    collisionX = thisPosX + (m_colliderSize.GetX() * 2) >= otherPosX && otherPosX + (otherCollide.GetColliderSize().GetX() * 2) >= thisPosX;
    collisionY = thisPosY + (m_colliderSize.GetY() * 2) >= otherPosY && otherPosY + (otherCollide.GetColliderSize().GetY() * 2) >= thisPosY;
    collisionZ = thisPosZ + (m_colliderSize.GetZ() * 2) >= otherPosZ && otherPosZ + (otherCollide.GetColliderSize().GetZ() * 2) >= thisPosZ;
    return (collisionX && collisionY && collisionZ);
}