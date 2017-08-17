#pragma once

#include "components/Movement.hpp"
#include "components/Position.hpp"

#define MOVEMENT_SYSTEM_FLAGS (MOVEMENT|POSITION)

namespace MovementSystem
{
    void    SetMovement(Movement &m, Position &p, Vec3 dir);
    void    CheckSnapMovement(Movement &m, Position &p);
};