#pragma once

#include "components/Collision.hpp"
#include "components/Position.hpp"

#define COLLISION_SYSTEM_FLAGS (COLLISION|POSITION)

namespace CollisionSystem
{
    bool CheckCollision(Position const &aPos, Collision const &aCol, Position const &bPos, Collision const &bCol);
};