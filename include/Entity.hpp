#pragma once

#include <cstdio>
#include "components/BaseComponent.hpp"

class Entity
{
private:
    //Change this variable type based on the amount of components there are
    COMPONENT_MASK_TYPE m_componentFlags;
	std::size_t         m_ID;

public:
    Entity();
    Entity(COMPONENT_MASK_TYPE flags);
    Entity(Entity const &e);
    ~Entity();

    Entity  &operator=(Entity const &e);
    COMPONENT_MASK_TYPE GetComponentFlags() const;
    void                SetComponentFlags(COMPONENT_MASK_TYPE flags);
    std::size_t         GetID() const;
};
