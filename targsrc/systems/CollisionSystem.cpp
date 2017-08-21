#include "systems/CollisionSystem.hpp"

bool CollisionSystem::CheckCollision(Position const &aPos, Collision const &aCol, Position const &bPos, Collision const &bCol)
{
    bool    collisionX;
    bool    collisionY;

    //The corner of the x axis for a
    float   aPosX = aPos.GetPosition().GetX() - aCol.GetColliderSize().GetX();
    //The corner of the x axis for b
    float   bPosX = bPos.GetPosition().GetX() - bCol.GetColliderSize().GetX();

    //The corner of the y axis for a
    float   aPosY = aPos.GetPosition().GetY() - aCol.GetColliderSize().GetY();
    //The corner of the y axis for b
    float   bPosY = bPos.GetPosition().GetY() - bCol.GetColliderSize().GetY();

    //The collider size is doubled to get from the one corner to the other
    collisionX = aPosX + (aCol.GetColliderSize().GetX() * 2) >= bPosX && bPosX + (bCol.GetColliderSize().GetX() * 2) >= aPosX;
    collisionY = aPosY + (aCol.GetColliderSize().GetY() * 2) >= bPosY && bPosY + (bCol.GetColliderSize().GetY() * 2) >= aPosY;
    return (collisionX && collisionY);
}