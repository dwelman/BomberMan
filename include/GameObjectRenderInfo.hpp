#pragma once

#include "main.hpp"
#include "RenderEngine.hpp"
#include "Vec3.hpp"

enum ObjectType
{
    BLOCK_OT = 0,
    IND_BLOCK_OT,
    PLAYER_OT,
    BOMB_OT,
    ENEMY_1_OT,
    ENEMY_2_OT,
    ENEMY_3_OT,
    LIFE_POWERUP_OT,
    BOMB_STRENGTH_POWERUP_OT,
    BOMB_AMOUNT_POWERUP_OT
};

enum Direction
{
    EAST = 0,
    NORTH,
    WEST,
    SOUTH
};

class GameObjectRenderInfo
{
private:
    ObjectType  m_objectType;
    Vec3        m_position;
    Direction        m_direction;

    GameObjectRenderInfo();
public:
    GameObjectRenderInfo(ObjectType objectType, Vec3 position, Direction direction);
    GameObjectRenderInfo(GameObjectRenderInfo const &g);

    ~GameObjectRenderInfo();

    GameObjectRenderInfo    &operator=(GameObjectRenderInfo const &g);

    ObjectType  GetObjectType() const;
    Vec3        GetPosition() const;
    Direction   GetDirection() const;
    void        SetObjectType(ObjectType type);
    void        SetPosition(Vec3 position);
    void        SetDirection(Direction direction);
};
