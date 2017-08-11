#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.hpp"
#include "components/BaseComponent.hpp"
#include "components/Tag.hpp"
#include "systems/PlayerControllerSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/BombSystem.hpp"

class GameManager
{
private:
	std::vector<Entity>			            m_entities;
	std::map<std::size_t, BaseComponent*>	m_components;
	std::size_t 				            m_currentComponentID;
    double                                  m_deltaTime;
    std::vector<std::size_t>                m_toBeDeleted;

	void		handleCollisions(Collision &c, Position &p, std::size_t ID);
    void        handleMovement(Position &p, Movement &m);
    void        createEntity(std::string entityType);
    void        deleteEntity(std::size_t ID);
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    bool        Update();
};
