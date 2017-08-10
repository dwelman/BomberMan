#include "systems/BombSystem.hpp"

void BombSystem::ChangeBombTimeByDelta(Bomb &b, double delta)
{
    b.SetBombTime(b.GetBombTime() + delta);
}
