#include "GameObjectRenderInfo.hpp"

GameObjectRenderInfo::GameObjectRenderInfo()
{
    m_moving = false;
}

GameObjectRenderInfo::GameObjectRenderInfo(ObjectType objectType, Vec3 position, Direction direction) : m_objectType(objectType), m_position(position), m_direction(direction)
{
    m_moving = false;
}

GameObjectRenderInfo::GameObjectRenderInfo(GameObjectRenderInfo const &g)
{
    *this = g;
}

GameObjectRenderInfo::~GameObjectRenderInfo()
{

}

GameObjectRenderInfo &GameObjectRenderInfo::operator=(GameObjectRenderInfo const &g)
{
    m_objectType = g.m_objectType;
    m_position = g.m_position;
    m_direction = g.m_direction;
    m_moving = g.m_moving;
    return (*this);
}

ObjectType GameObjectRenderInfo::GetObjectType() const
{
    return (m_objectType);
}

Vec3 GameObjectRenderInfo::GetPosition() const
{
    return (m_position);
}

Direction GameObjectRenderInfo::GetDirection() const
{
    return (m_direction);
}

bool GameObjectRenderInfo::GetMoving() const
{
    return (m_moving);
}

void GameObjectRenderInfo::SetObjectType(ObjectType type)
{
    m_objectType = type;
}

void GameObjectRenderInfo::SetPosition(Vec3 position)
{
    m_position = position;
}

void GameObjectRenderInfo::SetDirection(Direction direction)
{
    m_direction = direction;
}

void GameObjectRenderInfo::SetMoving(bool moving)
{
    m_moving = moving;
}
