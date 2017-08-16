#pragma once

#include <vector>
#include <string>
#include <map>
#include <cstdlib>

#include "GameObjectRenderInfo.hpp"
#include "Entity.hpp"
#include "components/BaseComponent.hpp"
#include "components/Explosion.hpp"
#include "components/Powerup.hpp"
#include "components/Render.hpp"
#include "systems/TagSystem.hpp"
#include "systems/PlayerControllerSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/BombSystem.hpp"
#include "systems/RenderSystem.hpp"

class RenderEngine;

class GameManager
{
private:
	std::vector<Entity>			            m_entities;
	std::map<std::size_t, BaseComponent*>	m_components;
	std::size_t 				            m_currentComponentID;
    double                                  m_deltaTime;
    std::vector<std::size_t>                m_toBeDeleted;
    bool                                    m_gameStarted;
	float 									m_playerMoveSpeed;
	std::size_t 							m_playerBombAmount;
	std::size_t 							m_explosionSize;
	std::size_t 							m_lives;
	std::size_t 							m_score;
	ePlayerAction 							m_action;

	void		handleCollisions(Collision &c, Position &p, Tag &t, std::size_t ID);
    void        handleMovement(Position &p, Movement &m);
    void        createEntityAtPosition(std::string entityType, Vec3 const &pos);
    void        deleteEntity(std::size_t ID);
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    bool        Update();
    void        GetRenderData(std::vector<GameObjectRenderInfo> &g);
    bool        GetGameStarted() const;
    void        SetGameStarted(bool gameStarted);
	void 		GivePlayerAction(ePlayerAction pa);
};
