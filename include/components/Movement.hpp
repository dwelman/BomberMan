#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"


class Movement : public BaseComponent
{
private:
    Vec3    m_direction;
    float   m_speed;

public:
    Movement();
    Movement(Movement const &src);
    Movement(Vec3 direction, float speed);
    Movement(float x, float y, float z, float speed);
    ~Movement();

    Movement    &operator=(Movement const &cp);

    Vec3        GetDirection() const;
    float       GetSpeed() const;
    void        SetDirection(Vec3 vel);
    void        SetDirection(float x, float y, float z);
    void        SetSpeed(float speed);
};