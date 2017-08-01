#include "Entity.hpp"

Entity::Entity()
{
    //This variable tracks the current next available ID, which will increase when a new entity is created
    static std::size_t m_currentID = 0;
    m_ID = m_currentID;
    m_currentID++;
    m_componentFlags = 0;
}

Entity::Entity(COMPONENT_MASK_TYPE flags) : Entity()
{
    m_componentFlags = flags;
}

Entity::Entity(Entity const &e)
{
    *this = e;
}

Entity::~Entity()
{

}

Entity &Entity::operator=(Entity const &e)
{
    //ID is set upon creation and never changed, therefore it is not copied
    this->m_componentFlags = e.m_componentFlags;
    return (*this);
}

COMPONENT_MASK_TYPE Entity::GetComponentFlags() const
{
    return (m_componentFlags);
}

void Entity::SetComponentFlags(COMPONENT_MASK_TYPE flags)
{
    m_componentFlags = flags;
}

std::size_t Entity::GetID() const
{
    return (m_ID);
}
