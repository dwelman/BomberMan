#pragma once

#include "components/Bomb.hpp"
#include "components/Position.hpp"

#define BOMB_SYSTEM_FLAGS (BOMB|POSITION)

namespace BombSystem
{
    void    ChangeBombTimeByDelta(Bomb &b, double delta);
}

