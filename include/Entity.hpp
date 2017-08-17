#pragma once

#include <cstdio>
#include <map>
#include <vector>

#include "components/BaseComponent.hpp"

class Entity
{
private:
    COMPONENT_MASK_TYPE 					m_componentFlags;
	std::map<std::size_t, ComponentMask>	m_childComponents;
	bool									m_canTick;

public:
    Entity();
    Entity(COMPONENT_MASK_TYPE flags, bool canTick);
    Entity(Entity const &e);
    ~Entity();

    Entity  &operator=(Entity const &e);

    COMPONENT_MASK_TYPE 		GetComponentFlags() const;
    void                		SetComponentFlags(COMPONENT_MASK_TYPE flags);
	void						RegisterComponent(std::size_t componentID, ComponentMask componentType);
	void						DeregisterComponent(std::size_t componentID);
	std::size_t 				GetComponentOfType(COMPONENT_MASK_TYPE flag);
	std::vector<std::size_t>	GetChildrenIDs() const;
	bool 						GetCanTick() const;
	void						SetCanTick(bool canTick);

	class ChildComponentNotFoundException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};
