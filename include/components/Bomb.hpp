#pragma once

#include "components/BaseComponent.hpp"

class Bomb : public BaseComponent
{
private:
    double m_bombTime;

    Bomb();
    Bomb(Bomb const &b);

    Bomb    &operator=(Bomb const &b);
public:
    Bomb(double bombTime);

    ~Bomb();

    double  GetBombTime() const;
    void    SetBombTime(double time);
};