#pragma once

#include "Vec3.hpp"
#include "components/Position.hpp"

class Collision
{
private:
    Vec3    m_colliderSize;

    Collision();
public:
    Collision(Vec3 const &colliderSize);
    Collision(float x, float y, float z);
    Collision(Collision const &c);
    ~Collision();

    Collision   &operator=(Collision const &c);

    Vec3        GetColliderSize() const;
    void        SetColliderSize(Vec3 const &v);
    bool        CheckCollision(Position const &thisPos, Position const &otherPos, Collision const &otherCollide) const;
};

