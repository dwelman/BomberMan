#include "systems/MovementSystem.hpp"
#include <iostream>

void MovementSystem::SetMovement(Movement &m, Position &p, Vec3 dir)
{
    if (m.GetCanChangeDirection())
    {
        std::cout << dir.GetX() << " " << dir.GetY() << " " << dir.GetZ() << std::endl;
        m.SetDirection(dir);
        m.SetDestination(p.GetPosition() + dir);
        m.SetCanChangeDirection(false);
        std::cout << p.GetPosition().GetX() << " " << p.GetPosition().GetY() << " " << p.GetPosition().GetZ() << std::endl;
        std::cout << m.GetDestination().GetX() << " " << m.GetDestination().GetY() << " " << m.GetDestination().GetZ() << std::endl;
    }
}

void MovementSystem::CheckSnapMovement(Movement &m, Position &p)
{
    Vec3 dest = m.GetDestination();
    if (m.GetDirection().GetX() == 1)
    {
        if (p.GetPosition().GetX() >= dest.GetX())
        {
            p.SetPosition(dest);
            m.SetCanChangeDirection(true);
        }
    }
    else if (m.GetDirection().GetX() == -1)
    {
        if (p.GetPosition().GetX() <= dest.GetX())
        {
            p.SetPosition(dest);
            m.SetCanChangeDirection(true);
        }
    }
    else if (m.GetDirection().GetY() == 1)
    {
        if (p.GetPosition().GetY() >= dest.GetY())
        {
            p.SetPosition(dest);
            m.SetCanChangeDirection(true);
        }
    }
    else if (m.GetDirection().GetY() == -1)
    {
        if (p.GetPosition().GetY() <= dest.GetY())
        {
            p.SetPosition(dest);
            m.SetCanChangeDirection(true);
        }
    }
}
