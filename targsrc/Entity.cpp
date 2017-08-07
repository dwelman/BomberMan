#include "Entity.hpp"

Entity::Entity()
{
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

void Entity::RegisterComponent(std::size_t componentID, ComponentMask componentType)
{
    auto iter = m_childComponents.find(componentID);
    if (iter == m_childComponents.end())
    {
        m_childComponents.emplace(std::make_pair(componentID, componentType));
    }
    else
    {
        m_childComponents[componentID] = componentType;
    }
}

void Entity::DeregisterComponent(std::size_t componentID)
{
    auto iter = m_childComponents.find(componentID);
    if (iter != m_childComponents.end())
    {
        m_childComponents.erase(iter);
    }
}

//This will return the first/only component found of the type given
std::size_t Entity::GetComponentOfType(COMPONENT_MASK_TYPE flag)
{
    auto iter = m_childComponents.begin();
    while (iter != m_childComponents.end())
    {
        if (iter->second == flag)
        {
            return (iter->first);
        }
    }
    throw ChildComponentNotFoundException();
}

const char *Entity::ChildComponentNotFoundException::what() const throw()
{
    return ("Child component not found in entity");
}
