#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.hpp"
#include "components/BaseComponent.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/MovementSystem.hpp"

class GameManager
{
private:
	std::vector<Entity>			            m_entities;
	std::map<std::size_t, BaseComponent*>	m_components;
	std::size_t 				            m_currentComponentID;

	void		checkCollisions(Collision &c, Position &p, std::size_t ID);
    void        createEntity(std::string entityType);
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    void        Update();
};
