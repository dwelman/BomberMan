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
#include "components/Enemy.hpp"
#include "systems/TagSystem.hpp"
#include "systems/PlayerControllerSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/BombSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "AudioManager.hpp"

class RenderEngine;

#define MAP_X 61
#define MAP_Y 21

class GameManager
{
private:
	std::map<std::size_t, Entity>			m_entities;
	std::map<std::size_t, BaseComponent*>	m_components;
	std::size_t 				            m_currentComponentID;
	std::size_t								m_currentEntityID;
    double                                  m_deltaTime;
    std::vector<std::size_t>                m_toBeDeleted;
    bool                                    m_gameStarted;
    bool                                    m_paused;
	float 									m_playerMoveSpeed;
	std::size_t 							m_playerBombAmount;
	std::size_t 							m_explosionSize;
	std::size_t 							m_lives;
	std::size_t 							m_score;
	ePlayerAction 							m_action;
	long int								m_gameMap[MAP_Y][MAP_X];
	unsigned int							m_seed;
    unsigned int                            m_level;
    int                                     m_enemiesToDestroy;
	bool									m_exitOpen;
	float									m_time;
    AudioManager                            *m_audioManager;

	void		handleCollisions(Position &p, Tag &t, std::size_t ID);
    void        handleMovement(Position &p, Movement &m);
    std::size_t createEntityAtPosition(std::string entityType, Vec3 const &pos);
    void        deleteEntity(std::size_t ID);
	void		startLevel(bool save = true, unsigned int seed = 0);
	void		killPlayer();
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
    bool        GetGamePaused() const;
	void		LoadSave(std::string path);
	void		WriteSave(std::string path);
	std::size_t GetLives() const;
	std::size_t	GetScore() const;
	std::size_t	GetBombs() const;
	std::size_t	GetLevel() const;
	int			GetEnemiesLeft() const;
	float		GetGameTime() const;
    void        GiveAudioManager(AudioManager *manager);
};
