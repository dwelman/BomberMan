#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"
#include "main.hpp"
#include "RenderEngine.hpp"
#include <cstddef>

class Render : public BaseComponent
{
private:
    ObjectType  m_type;
    bool        m_active;

    Render();
public:
    Render(ObjectType type, bool active);
    Render(ObjectType type);
    Render(Render const &src);
    ~Render();

    Render &operator=(Render const &cp);

    ObjectType  GetObjectType() const;
    bool        GetActive() const;
    void        SetObjectType(ObjectType type);
    void        SetActive(bool active);
};