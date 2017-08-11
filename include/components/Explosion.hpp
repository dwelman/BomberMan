#pragma once

#include <cstdio>
#include "components/BaseComponent.hpp"
#include "Vec3.hpp"

class Explosion : public BaseComponent
{
private:
    std::size_t m_childExplosions;
    Vec3        m_direction;
    double      m_duration;

    Explosion();
public:
    Explosion(std::size_t childExplosions, Vec3 dirction, double duration)
    Explosion(Explosion const &e);
    ~Explosion();

    Explosion   &operator=(Explosion const &e);

    std::size_t     GetChildExplosions() const;
    void            SetChildExplosions(std::size_t childExplosions);
    Vec3            GetDirection() const;
    void            SetDirection(Vec3 const &direction);
    double          GetDuration() const;
    void            SetDuration(double duration);
};
