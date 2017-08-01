#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"


class Movement : public BaseComponent
{
private:
    Vec3 m_velocity;

public:
    Movement();
    Movement(Movement const &src);
    Movement(Vec3 vel);
    Movement(float x, float y, float z);
    ~Movement();

    Movement    &operator=(Movement const &cp);

    Vec3        GetVelocity() const;
    void        SetVelocity(Vec3 vel);
    void        SetVelocity(float x, float y, float z);
};