#pragma once

#include "components/BaseComponent.hpp"

enum PowerupType
{
    LIFE,
    BOMB_AMOUNT_UP,
    BOMB_STRENGTH_UP
};

class Powerup : public BaseComponent
{
private:
    PowerupType m_type;

    Powerup();
public:
    Powerup(PowerupType type);
    Powerup(Powerup const &p);

    Powerup &operator=(Powerup const &p);

    ~Powerup();

    PowerupType GetPowerupType() const;
};
