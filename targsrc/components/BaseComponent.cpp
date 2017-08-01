#include "components/BaseComponent.hpp"

BaseComponent::BaseComponent(ComponentMask mask) : m_type(mask)
{

}

BaseComponent::BaseComponent(BaseComponent const &c)
{
    *this = c;
}

BaseComponent::~BaseComponent()
{

}

BaseComponent &BaseComponent::operator=(BaseComponent const &c)
{
    this->m_type = c.m_type;
    return (*this);
}

ComponentMask BaseComponent::GetComponentType() const
{
    return (m_type);
}

void BaseComponent::SetComponentType(ComponentMask mask)
{
    m_type = mask;
}
