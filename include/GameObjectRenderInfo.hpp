#pragma once

#include "main.hpp"
#include "RenderEngine.hpp"
#include "Vec3.hpp"

class GameObjectRenderInfo
{
private:
    ObjectType  m_objectType;
    Vec3        m_position;
    Vec3        m_direction;

    GameObjectRenderInfo();
public:
    GameObjectRenderInfo(ObjectType objectType, Vec3 position, Vec3 direction);
    GameObjectRenderInfo(GameObjectRenderInfo const &g);

    ~GameObjectRenderInfo();

    GameObjectRenderInfo    &operator=(GameObjectRenderInfo const &g);

    ObjectType  GetObjectType() const;
    Vec3        GetPosition() const;
    Vec3        GetDirection() const;
    void        SetObjectType(ObjectType type);
    void        SetPosition(Vec3 position);
    void        SetDirection(Vec3 direction);
};
