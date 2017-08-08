#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.hpp"
#include "components/BaseComponent.hpp"
#include "components/PlayerController.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/MovementSystem.hpp"

class GameManager
{
private:
	std::vector<Entity>			            m_entities;
	std::map<std::size_t, BaseComponent*>	m_components;
	std::size_t 				            m_currentComponentID;
    float                                   m_deltaTime;

	void		handleCollisions(Collision &c, Position &p, std::size_t ID);
    void        handleMovement(Position &p, Movement &m);
    void        createEntity(std::string entityType);
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    void        Update();
};
