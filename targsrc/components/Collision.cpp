#include "components/Collision.hpp"

Collision::Collision(Vec3 const &colliderSize) : m_colliderSize(colliderSize)
{

}

Collision::Collision(float x, float y, float z) : m_colliderSize(x, y, z)
{

}

Collision::Collision(Collision const &c)
{
    *this = c;
}

Collision::~Collision()
{

}

Collision   &Collision::operator=(Collision const &c)
{
    this->m_colliderSize = c.m_colliderSize;
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
    collisionX = thisPosZ + (m_colliderSize.GetZ() * 2) >= otherPosX && otherPosZ + (otherCollide.GetColliderSize().GetZ() * 2) >= thisPosZ;
    return (collisionX && collisionY && collisionZ);
}