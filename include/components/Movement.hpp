#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"


class Movement : public BaseComponent
{
private:
    Vec3    m_direction;
    Vec3    m_destination;
    float   m_speed;
    bool    m_canChangeDirection;

public:
    Movement();
    Movement(Movement const &src);
    Movement(Vec3 direction, float speed, Vec3 destination);
    ~Movement();

    Movement    &operator=(Movement const &cp);

    Vec3        GetDirection() const;
    float       GetSpeed() const;
    Vec3        GetDestination() const;
    bool        GetCanChangeDirection() const;
    void        SetDirection(Vec3 vel);
    void        SetSpeed(float speed);
    void        SetDestination(Vec3 dest);
    void        SetCanChangeDirection(bool b);
};