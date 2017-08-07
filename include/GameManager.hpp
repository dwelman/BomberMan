#pragma once

#include <vector>

#include "Entity.hpp"
#include "components/BaseComponent.hpp"
#include "systems/CollisionSystem.hpp"

class GameManager
{
private:
	std::vector<Entity>			m_entities;
	std::vector<BaseComponent*>	m_components;
	std::size_t 				m_currentEntityID;
	std::size_t 				m_currentComponentID;

	void		CheckCollisions(Collision &c, Position &p, std::size_t ID);
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    void        Update();
};
