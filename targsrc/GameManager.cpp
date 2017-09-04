#include "GameManager.hpp"
#include "Clock.hpp"

#include <iostream>
#include <time.h>
#include <cmath>
#include <fstream>

GameManager::GameManager()
{
	m_currentEntityID = 0;
	m_currentComponentID = 0;
	m_gameStarted = false;
	m_playerMoveSpeed = 5;
	m_playerBombAmount = 1;
	m_explosionSize = 1;
	m_lives = 3;
	m_score = 0;
    m_paused = false;
    m_level = 1;
	startLevel(false);
}

GameManager::GameManager(GameManager const & gm)
{
	*this = gm;
}

GameManager::~GameManager()
{
}

GameManager & GameManager::operator=(GameManager const & gm)
{
	m_entities = gm.m_entities;
	return (*this);
}

void	GameManager::handleCollisions(Position &p, Tag &t, std::size_t ID)
{
    //if ()
    /*for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
    {
        std::size_t i = iter->first;
		if (i != ID)
		{
			COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
			if ((bitmask & COLLISION_SYSTEM_FLAGS) == COLLISION_SYSTEM_FLAGS)
			{
				try
				{
					std::size_t collisionID = m_entities[i].GetComponentOfType(COLLISION);
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					Collision *collision = dynamic_cast<Collision*>(m_components[collisionID]);
					Position *position = dynamic_cast<Position*>(m_components[positionID]);
					if (CollisionSystem::CheckCollision(p, c, *position, *collision) == true)
					{
						std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
						Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
						if (TagSystem::CheckMaskForTag(t.GetTagMask(), DAMAGE_PLAYER_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), PLAYER_TAG)
							&& !TagSystem::CheckMaskForTag(tag->GetTagMask(), INDESTRUCTIBLE_TAG))
						{
							//Player dies
							m_lives--;
							m_toBeDeleted.push_back(i);
							//createEntityAtPosition("player", Vec3(0, 0, 0));
						}
						if (TagSystem::CheckMaskForTag(t.GetTagMask(), DAMAGE_WALL_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), WALL_TAG)
							&& !TagSystem::CheckMaskForTag(tag->GetTagMask(), INDESTRUCTIBLE_TAG))
						{
							//Wall is destroyed
							m_toBeDeleted.push_back(i);
							//Explosion is destroyed as well
							std::size_t explosionID = m_entities[ID].GetComponentOfType(EXPLOSION);
							Explosion *explosion = dynamic_cast<Explosion*>(m_components[explosionID]);
							explosion->SetDuration(0);
							explosion->SetChildExplosions(0);

							//A powerup may spawn
							if (rand() % 100 <= 30)
							{
								if (rand() % 100 >= 66)
								{
									createEntityAtPosition("powerup_life", position->GetPosition());
								}
								else if (rand() >= 33)
								{
									createEntityAtPosition("powerup_bomb_amount", position->GetPosition());
								}
								else
								{
									createEntityAtPosition("powerup_bomb_strength", position->GetPosition());
								}
							}
						}
						if (TagSystem::CheckMaskForTag(t.GetTagMask(), DAMAGE_WALL_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), BOMB_TAG)
							&& !TagSystem::CheckMaskForTag(tag->GetTagMask(), INDESTRUCTIBLE_TAG))
						{
							//Bomb is set off
							std::size_t bombID = m_entities[i].GetComponentOfType(BOMB);
							Bomb *bomb = dynamic_cast<Bomb*>(m_components[bombID]);
							bomb->SetBombTime(0);
						}
						if (TagSystem::CheckMaskForTag(t.GetTagMask(), DAMAGE_ENEMY_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), ENEMY_TAG)
							&& !TagSystem::CheckMaskForTag(tag->GetTagMask(), INDESTRUCTIBLE_TAG))
						{
							//Enemy is destroyed
							m_toBeDeleted.push_back(i);
						}

						if (TagSystem::CheckMaskForTag(t.GetTagMask(), PLAYER_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), POWERUP_TAG))
						{
							//Player collects a powerup
							std::size_t powerupID = m_entities[i].GetComponentOfType(POWERUP);
							Powerup *powerup = dynamic_cast<Powerup *>(m_components[powerupID]);
							if (powerup->GetPowerupType() == LIFE)
							{
								m_lives++;
							}
							else if (powerup->GetPowerupType() == BOMB_AMOUNT_UP)
							{
								m_playerBombAmount++;
							}
							else if (powerup->GetPowerupType() == BOMB_STRENGTH_UP)
							{
								m_explosionSize++;
							}
							m_toBeDeleted.push_back(i);
						}

						if (TagSystem::CheckMaskForTag(t.GetTagMask(), MOVING_ENTITY_TAG) && TagSystem::CheckMaskForTag(tag->GetTagMask(), WALL_TAG))
						{
                            std::size_t movementID = m_entities[ID].GetComponentOfType(MOVEMENT);
                            Movement *movement = dynamic_cast<Movement*>(m_components[movementID]);
                            std::size_t posID = m_entities[ID].GetComponentOfType(POSITION);
                            Position *pos = dynamic_cast<Position*>(m_components[posID]);

                            std::cout << "x: " << pos->GetPosition().GetX() << " y: " << pos->GetPosition().GetY() << " z: " << pos->GetPosition().GetZ() << std::endl;
                            movement->SetDestination(movement->GetDestination() - (movement->GetDirection() * -2));
                            movement->SetDirection(movement->GetDirection() * -1);
						}
					}
				}
				catch (std::exception &e)
				{
                    std::cout << e.what() << std::endl;
				}
			}
		}
	}*/
}


void GameManager::handleMovement(Position &p, Movement &m)
{
	Vec3 newPos = p.GetPosition();
	float newX = newPos.GetX();
	float newY = newPos.GetY();
	float newZ = newPos.GetZ();

	newX += m.GetDirection().GetX() * m.GetSpeed() * m_deltaTime;
	newY += m.GetDirection().GetY() * m.GetSpeed() * m_deltaTime;
	newZ += m.GetDirection().GetZ() * m.GetSpeed() * m_deltaTime;
	p.SetPosition(Vec3(newX, newY, newZ));
	MovementSystem::CheckSnapMovement(m, p);
}

std::size_t GameManager::createEntityAtPosition(std::string entityType, Vec3 const &pos)
{
	Entity entity;
	if (entityType == "player")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.4f, 0.4f, 0.4f, true)));
		entity.RegisterComponent(m_currentComponentID, MOVEMENT);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Movement(Vec3(0, 0, 0), m_playerMoveSpeed, Vec3(0, 0, 0))));
		entity.RegisterComponent(m_currentComponentID, PLAYERCONTROLLER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new PlayerController()));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(PLAYER_TAG | MOVING_ENTITY_TAG)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(PLAYER_OT, true)));
	}
	else if (entityType == "indestructible_wall")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(WALL_TAG | INDESTRUCTIBLE_TAG)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(IND_BLOCK_OT, true)));
		entity.SetCanTick(false);
	}
	else if (entityType == "destructible_wall")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(WALL_TAG)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BLOCK_OT, true)));
		//entity.SetCanTick(false);
	}
    else if (entityType == "level_exit_closed")
    {
        entity.RegisterComponent(m_currentComponentID, POSITION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
        entity.RegisterComponent(m_currentComponentID, COLLISION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
        entity.RegisterComponent(m_currentComponentID, TAG);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(INDESTRUCTIBLE_TAG)));
        entity.RegisterComponent(m_currentComponentID, RENDER);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Render(DOOR_CLOSED_OT, true)));
        entity.SetCanTick(false);
    }
    else if (entityType == "level_exit_open")
    {
        entity.RegisterComponent(m_currentComponentID, POSITION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
        entity.RegisterComponent(m_currentComponentID, COLLISION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
        entity.RegisterComponent(m_currentComponentID, TAG);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(INDESTRUCTIBLE_TAG | LEVEL_EXIT_TAG)));
        entity.RegisterComponent(m_currentComponentID, RENDER);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Render(DOOR_OPEN_OT, true)));
        entity.SetCanTick(false);
    }
	else if (entityType == "enemy_1")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.4f, 0.4f, 0.4f, true)));
		entity.RegisterComponent(m_currentComponentID, MOVEMENT);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Movement(Vec3(0, 0, 0), 3, Vec3(0, 0, 0))));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(ENEMY_TAG | MOVING_ENTITY_TAG)));
		entity.RegisterComponent(m_currentComponentID, ENEMY);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Enemy(1)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BOMB_STRENGTH_POWERUP_OT, true)));
	}
	else if (entityType == "enemy_2")
	{

	}
	else if (entityType == "enemy_3")
	{

	}
	else if (entityType == "bomb")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(BOMB_TAG)));
		entity.RegisterComponent(m_currentComponentID, BOMB);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Bomb(3.0)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BOMB_OT, true)));
	}
	else if (entityType == "explosion")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(DAMAGE_ENEMY_TAG | DAMAGE_PLAYER_TAG | DAMAGE_WALL_TAG | EXPLOSION_TAG)));
		entity.RegisterComponent(m_currentComponentID, EXPLOSION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Explosion(m_explosionSize, Vec3(0, 0, 0), 0.4f)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(EXPLOSION_PE, true)));
	}
	else if (entityType == "powerup_life")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(POWERUP_TAG)));
		entity.RegisterComponent(m_currentComponentID, POWERUP);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Powerup(LIFE)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(LIFE_POWERUP_OT, true)));
		entity.SetCanTick(false);
	}
	else if (entityType == "powerup_bomb_amount")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, COLLISION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
		entity.RegisterComponent(m_currentComponentID, TAG);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(POWERUP_TAG)));
		entity.RegisterComponent(m_currentComponentID, POWERUP);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Powerup(BOMB_AMOUNT_UP)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BOMB_AMOUNT_POWERUP_OT, true)));
		entity.SetCanTick(false);
	}
	else if (entityType == "powerup_bomb_strength")
    {
        entity.RegisterComponent(m_currentComponentID, POSITION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
        entity.RegisterComponent(m_currentComponentID, COLLISION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
        entity.RegisterComponent(m_currentComponentID, TAG);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(POWERUP_TAG)));
        entity.RegisterComponent(m_currentComponentID, POWERUP);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Powerup(BOMB_STRENGTH_UP)));
        entity.RegisterComponent(m_currentComponentID, RENDER);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BOMB_STRENGTH_POWERUP_OT, true)));
        entity.SetCanTick(false);
    }
	else if (entityType == "explosion_particle")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		/*entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(EXPLOSION_PE, true)));*/
	}
	else if (entityType == "blood_particle")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(BLOOD_PE, true)));
	}
	else if (entityType == "rubble_particle")
	{
		entity.RegisterComponent(m_currentComponentID, POSITION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
		entity.RegisterComponent(m_currentComponentID, RENDER);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Render(RUBBLE_PE, true)));
	}
	m_entities.emplace(std::make_pair(m_currentEntityID++, Entity(entity)));
    return (m_currentEntityID - 1);
}

void GameManager::deleteEntity(std::size_t ID)
{
	try
	{
		std::vector<std::size_t> components;

		components = m_entities[ID].GetChildrenIDs();
		for (std::size_t i = 0; i < components.size(); i++)
		{
			auto iter = m_components.find(components[i]);
			if (iter != m_components.end())
			{
				delete m_components[iter->first];
				m_components.erase(iter);
			}
		}
		auto iter = m_entities.find(ID);
		if (iter != m_entities.end())
		{
			m_entities.erase(iter);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void GameManager::startLevel(bool save, unsigned int seed)
{
	m_entities.clear();
	m_components.clear();
	m_currentEntityID = 0;
	m_currentComponentID = 0;
	if (seed == 0)
	{
		m_seed = time(NULL);
	}
	else
	{
		m_seed = seed;
	}
	srand(m_seed);

	for (std::size_t y = 0; y < MAP_Y; y++)
	{
		for (std::size_t x = 0; x < MAP_X; x++)
		{
			m_gameMap[y][x] = -1;
			if (x == 0 || y == 0 || x == MAP_X - 1 || y == MAP_Y - 1)
			{
				m_gameMap[y][x] = -2;
				createEntityAtPosition("indestructible_wall", Vec3(x, y, 1));
			}
			else if (x % 2 == 0 && y % 2 == 0)
			{
				m_gameMap[y][x] = -2;
				createEntityAtPosition("indestructible_wall", Vec3(x, y, 1));
			}
		}
	}

	for (std::size_t y = 1; y < MAP_Y; y++)
	{
		for (std::size_t x = 1; x < MAP_X; x++)
		{
			if (m_gameMap[y][x] == -1 && !(y == 2 && x == 1) && !(y == 1 && x == 2) && !(y == 1 && x == 1))
			{
				if (rand() % 100 > 70)
				{
					if (rand() % 100 <= 70)
					{
						m_gameMap[y][x] = createEntityAtPosition("destructible_wall", Vec3(x, y, 1));
					}
					else
					{
						m_gameMap[y][x] = createEntityAtPosition("enemy_1", Vec3(x, y, 0));
					}
				}
			}
		}
	}

    createEntityAtPosition("player", Vec3(1, 1, 0));
    createEntityAtPosition("level_exit_closed", Vec3(2, 1, 0));
    if (save)
    {
        WriteSave("save/savegame");
    }
	m_playerBombAmount = 1;
	m_explosionSize = 1;
    m_enemiesToDestroy = 5;
}

void GameManager::killPlayer()
{
	m_lives--;
	if (m_lives <= 0)
	{
		exit(0);
	}
	WriteSave("save/savegame");
	m_playerBombAmount = 1;
	m_explosionSize = 1;
	startLevel();
}

bool 	GameManager::Update()
{
	m_deltaTime = Clock::Instance().GetDeltaTime();
    std::size_t playerID;
    bool playerAlive = false;

    if (m_action == P_PAUSE_GAME)
    {
        m_paused = !m_paused;
        m_action = P_NOACTION;
    }
    if (m_paused == true)
        return (false);

	for (std::size_t y = 0; y < MAP_Y; y++)
	{
		for (std::size_t x = 0; x < MAP_X; x++)
		{
			if (m_gameMap[y][x] >= 0)
			{
				m_gameMap[y][x] = -1;
			}
		}
	}
    for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
    {
        std::size_t i = iter->first;
        //Check each component for the relevant flags
        COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
        //Position system
        {
            if ((bitmask & (POSITION | TAG)) == (POSITION | TAG))
            {
                try
                {
                    std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
                    Position *position = dynamic_cast<Position *>(m_components[positionID]);
                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
					if ((tag->GetTagMask() & PLAYER_TAG) == PLAYER_TAG)
					{
						playerID = i;
						playerAlive = true;
					}
                    else if (!((tag->GetTagMask() & (INDESTRUCTIBLE_TAG | WALL_TAG)) == (INDESTRUCTIBLE_TAG | WALL_TAG)))
                    {
                        m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] = i;
                    }
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    if (playerAlive == false)
    {
        killPlayer();
    }
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		std::size_t i = iter->first;
		if (!m_entities[i].GetCanTick())
		{
			continue;
		}
		//Check each component for the relevant flags
		COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
		//Player control system
		{
			if ((bitmask & PLAYER_CONTROLLER_SYSTEM_FLAGS) == PLAYER_CONTROLLER_SYSTEM_FLAGS)
			{
				try
				{
					bool canDoAction = true;
					std::size_t playerControllerID = m_entities[i].GetComponentOfType(PLAYERCONTROLLER);
					PlayerController *playerController = dynamic_cast<PlayerController *>(m_components[playerControllerID]);
					if ((bitmask & MOVEMENT) == MOVEMENT)
					{
						std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
						Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
						std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
						Position *position = dynamic_cast<Position *>(m_components[positionID]);
						canDoAction = movement->GetCanChangeDirection();
						if (m_action == P_MOVE_LEFT)
						{
                            long ID = m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX() - 1];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[ID].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

									if (!((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG)) && !((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG)))
									{
										MovementSystem::SetMovement(*movement, *position, Vec3(-1, 0, 0));
									}

									if ((tag->GetTagMask() & (POWERUP_TAG)) == (POWERUP_TAG))
									{
										std::size_t powerupID = m_entities[ID].GetComponentOfType(POWERUP);
										Powerup *powerup = dynamic_cast<Powerup *>(m_components[powerupID]);
										if (powerup->GetPowerupType() == LIFE)
										{
											m_lives++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_AMOUNT_UP)
										{
											m_playerBombAmount++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_STRENGTH_UP)
										{
											m_explosionSize++;
											m_toBeDeleted.push_back(ID);
										}
									}
                                    if ((tag->GetTagMask() & (LEVEL_EXIT_TAG)) == (LEVEL_EXIT_TAG))
                                    {
                                        m_level++;
                                        startLevel();
                                    }
                                }
                            }
                            else if (ID == -1)
                            {
                                MovementSystem::SetMovement(*movement, *position, Vec3(-1, 0, 0));
                            }
						}
						else if (m_action == P_MOVE_RIGHT)
						{
                            long ID = m_gameMap[(long int)position->GetPosition().GetY()][(long int)position->GetPosition().GetX() + 1];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[ID].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

									if (!((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG)) && !((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG)))
									{
										MovementSystem::SetMovement(*movement, *position, Vec3(1, 0, 0));
									}

                                    if ((tag->GetTagMask() & (POWERUP_TAG)) == (POWERUP_TAG))
                                    {
										std::size_t powerupID = m_entities[ID].GetComponentOfType(POWERUP);
										Powerup *powerup = dynamic_cast<Powerup *>(m_components[powerupID]);
										if (powerup->GetPowerupType() == LIFE)
										{
											m_lives++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_AMOUNT_UP)
										{
											m_playerBombAmount++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_STRENGTH_UP)
										{
											m_explosionSize++;
											m_toBeDeleted.push_back(ID);
										}
                                    }
                                    if ((tag->GetTagMask() & (LEVEL_EXIT_TAG)) == (LEVEL_EXIT_TAG))
                                    {
                                        m_level++;
                                        startLevel();
                                        return (false);
                                    }
                                }
                            }
                            else if (ID == -1)
                            {
                                MovementSystem::SetMovement(*movement, *position, Vec3(1, 0, 0));
                            }
						}
						else if (m_action == P_MOVE_UP)
						{
                            long ID = m_gameMap[(int)position->GetPosition().GetY() + 1][(int)position->GetPosition().GetX()];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[ID].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

									if (!((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG)) && !((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG)))
									{
										MovementSystem::SetMovement(*movement, *position, Vec3(0, 1, 0));
									}

									if ((tag->GetTagMask() & (POWERUP_TAG)) == (POWERUP_TAG))
									{	
										std::size_t powerupID = m_entities[ID].GetComponentOfType(POWERUP);
										Powerup *powerup = dynamic_cast<Powerup *>(m_components[powerupID]);
										if (powerup->GetPowerupType() == LIFE)
										{
											m_lives++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_AMOUNT_UP)
										{
											m_playerBombAmount++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_STRENGTH_UP)
										{
											m_explosionSize++;
											m_toBeDeleted.push_back(ID);
										}
									}
                                    if ((tag->GetTagMask() & (LEVEL_EXIT_TAG)) == (LEVEL_EXIT_TAG))
                                    {
                                        m_level++;
                                        startLevel();
                                    }
                                }
                            }
                            else if (ID == -1)
                            {
                                MovementSystem::SetMovement(*movement, *position, Vec3(0, 1, 0));
                            }
						}
						else if (m_action == P_MOVE_DOWN)
						{
                            long ID = m_gameMap[(int)position->GetPosition().GetY() - 1][(int)position->GetPosition().GetX()];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[ID].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

									if (!((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG)) && !((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG)))
									{
										MovementSystem::SetMovement(*movement, *position, Vec3(0, -1, 0));
									}

									if ((tag->GetTagMask() & (POWERUP_TAG)) == (POWERUP_TAG))
									{
										std::size_t powerupID = m_entities[ID].GetComponentOfType(POWERUP);
										Powerup *powerup = dynamic_cast<Powerup *>(m_components[powerupID]);
										if (powerup->GetPowerupType() == LIFE)
										{
											m_lives++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_AMOUNT_UP)
										{
											m_playerBombAmount++;
											m_toBeDeleted.push_back(ID);
										}
										else if (powerup->GetPowerupType() == BOMB_STRENGTH_UP)
										{
											m_explosionSize++;
											m_toBeDeleted.push_back(ID);
										}
									}
                                    if ((tag->GetTagMask() & (LEVEL_EXIT_TAG)) == (LEVEL_EXIT_TAG))
                                    {
                                        m_level++;
                                        startLevel();
                                    }
                                }
                            }
                            else if (ID == -1)
                            {
                                MovementSystem::SetMovement(*movement, *position, Vec3(0, -1, 0));
                            }
						}
					}

					//if bomb placed
					if (m_action == P_PLACE_BOMB && canDoAction)
					{
						std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
						Position *position = dynamic_cast<Position *>(m_components[positionID]);
						if (m_playerBombAmount > 0)
						{
							m_playerBombAmount--;
                            m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] = createEntityAtPosition("bomb", position->GetPosition());
						}
					}
				}
				catch (std::exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
		}

		//Movement System
		{
			if ((bitmask & MOVEMENT_SYSTEM_FLAGS) == MOVEMENT_SYSTEM_FLAGS)
			{
				try
				{
					std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
					Position *position = dynamic_cast<Position *>(m_components[positionID]);
					handleMovement(*position, *movement);
					m_gameMap[(int)round(position->GetPosition().GetY())][(int)round(position->GetPosition().GetX())] = i;
					//std::cout << "Map pos x: " << (long int)round(position->GetPosition().GetX()) << " | y: " << (long int)round(position->GetPosition().GetY()) << std::endl;
					//std::cout << "Actual pos x: " << position->GetPosition().GetX() << " | y: " << position->GetPosition().GetY() << std::endl;
				}
				catch (std::exception &e)
				{
					return (false);
				}
			}
		}

		//Enemy system
		{
			if ((bitmask & ENEMY) == ENEMY)
			{
				try
				{
					std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					std::size_t enemyID = m_entities[i].GetComponentOfType(ENEMY);
					Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
					Position *position = dynamic_cast<Position *>(m_components[positionID]);
					Enemy *enemy = dynamic_cast<Enemy *>(m_components[enemyID]);
					if (enemy->GetEnemyType() == 1)
					{
						if (movement->GetCanChangeDirection() == true)
						{
                            if (enemy->GetTimeUntilNextMove() <= 0)
                            {
                                int x = (int) position->GetPosition().GetX();
                                int y = (int) position->GetPosition().GetY();

                                if (rand() % 100 >= 25 && m_gameMap[y + 1][x] == -1)
                                {
                                    movement->SetDirection(Vec3(0, 1, 0));
                                    movement->SetDestination(position->GetPosition() + movement->GetDirection());
                                }
                                else if (rand() % 100 >= 50 && m_gameMap[y - 1][x] == -1)
                                {
                                    movement->SetDirection(Vec3(0, -1, 0));
                                    movement->SetDestination(position->GetPosition() + movement->GetDirection());
                                }
                                else if (rand() % 100 >= 75 && m_gameMap[y][x + 1] == -1)
                                {
                                    movement->SetDirection(Vec3(1, 0, 0));
                                    movement->SetDestination(position->GetPosition() + movement->GetDirection());
                                }
                                else if (m_gameMap[y][x - 1] == -1)
                                {
                                    movement->SetDirection(Vec3(-1, 0, 0));
                                    movement->SetDestination(position->GetPosition() + movement->GetDirection());
                                }
                                enemy->SetTimeUntilNextMove(0.5f);
                            }
                            enemy->SetTimeUntilNextMove(enemy->GetTimeUntilNextMove() - Clock::Instance().GetDeltaTime());
						}
					}
					/*else if (enemy->GetEnemyType() == 2)
					{

					}
					else
					{

					}*/
					if (playerAlive)
					{
						std::size_t posID = m_entities[playerID].GetComponentOfType(POSITION);
						Position *pos = dynamic_cast<Position *>(m_components[posID]);
                        float   aPosX = pos->GetPosition().GetX() - 0.3f;
                        float   bPosX = position->GetPosition().GetX() - 0.3f;

                        //The corner of the y axis for a
                        float   aPosY = pos->GetPosition().GetY() - 0.3f;
                        //The corner of the y axis for b
                        float   bPosY = position->GetPosition().GetY() - 0.3f;

                        //The collider size is doubled to get from the one corner to the other
                        bool collisionX = aPosX + (0.6f) >= bPosX && bPosX + (0.6f) >= aPosX;
                        bool collisionY = aPosY + (0.6f) >= bPosY && bPosY + (0.6f) >= aPosY;
						if (collisionX && collisionY)
						{
							m_toBeDeleted.push_back(playerID);
							createEntityAtPosition("blood_particle", position->GetPosition());
							killPlayer();
							return (false);
						}
					}
				}
				catch (std::exception &e)
				{
					return (false);
				}
			}
		}

		//Bomb system
		{
			if ((bitmask & BOMB_SYSTEM_FLAGS) == BOMB_SYSTEM_FLAGS)
			{
				try
				{
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					std::size_t bombID = m_entities[i].GetComponentOfType(BOMB);
					Position *position = dynamic_cast<Position *>(m_components[positionID]);
					Bomb *bomb = dynamic_cast<Bomb *>(m_components[bombID]);
					BombSystem::ChangeBombTimeByDelta(*bomb, -(Clock::Instance().GetDeltaTime()));
					if (bomb->GetBombTime() <= 0)
					{
						Explosion *explosion;
						createEntityAtPosition("explosion", position->GetPosition());
						explosion = dynamic_cast<Explosion *>(m_components[m_entities[m_currentEntityID - 1].GetComponentOfType(EXPLOSION)]);
						explosion->SetDirection(Vec3(1, 0, 0));
						createEntityAtPosition("explosion", position->GetPosition());
						explosion = dynamic_cast<Explosion *>(m_components[m_entities[m_currentEntityID - 1].GetComponentOfType(EXPLOSION)]);
						explosion->SetDirection(Vec3(-1, 0, 0));
						createEntityAtPosition("explosion", position->GetPosition());
						explosion = dynamic_cast<Explosion *>(m_components[m_entities[m_currentEntityID - 1].GetComponentOfType(EXPLOSION)]);
						explosion->SetDirection(Vec3(0, 1, 0));
						createEntityAtPosition("explosion", position->GetPosition());
						explosion = dynamic_cast<Explosion *>(m_components[m_entities[m_currentEntityID - 1].GetComponentOfType(EXPLOSION)]);
						explosion->SetDirection(Vec3(0, -1, 0));
						m_playerBombAmount++;
						m_toBeDeleted.push_back(i);
					}
				}
				catch (std::exception &e)
				{
					return (false);
				}
			}
		}



		//Explosion system
		{
			if ((bitmask & EXPLOSION) == EXPLOSION)
			{
				try
				{
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					std::size_t explosionID = m_entities[i].GetComponentOfType(EXPLOSION);
					Position *position = dynamic_cast<Position *>(m_components[positionID]);
					Explosion *explosion = dynamic_cast<Explosion *>(m_components[explosionID]);
					//createEntityAtPosition("explosion_particle", position->GetPosition());
                    if (m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] >= 0)
                    {
                        std::size_t tagID = m_entities[m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]].GetComponentOfType(TAG);
                        Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
						if ((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG))
						{
							std::size_t bombID = m_entities[m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]].GetComponentOfType(BOMB);
							Bomb *bomb = dynamic_cast<Bomb *>(m_components[bombID]);
							bomb->SetBombTime(0);
							m_score += 5;
						}
                        else if ((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG))
                        {
                            explosion->SetChildExplosions(0);
                            explosion->SetDuration(0);
							m_toBeDeleted.push_back(m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]);
							createEntityAtPosition("rubble_particle", position->GetPosition());
							m_score++;
							//TODO: Tweak, needs balancing
							if (rand() % 100 < 40)
							{
								if (rand() % 100 <= 60)
								{
									m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] = createEntityAtPosition("powerup_bomb_amount", position->GetPosition());
								}
								else if (rand() % 100 <= 90)
								{
									m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] = createEntityAtPosition("powerup_bomb_strength", position->GetPosition());
								}
								else
								{
									m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] = createEntityAtPosition("powerup_life", position->GetPosition());
								}
							}
                        }
                        else if ((tag->GetTagMask() & (ENEMY_TAG)) == (ENEMY_TAG))
                        {
                            m_score += 10;
                            m_enemiesToDestroy--;
                            m_toBeDeleted.push_back(m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]);
                        }
						else if (!((tag->GetTagMask() & (INDESTRUCTIBLE_TAG)) == (INDESTRUCTIBLE_TAG)) && !((tag->GetTagMask() & (EXPLOSION_TAG)) == (EXPLOSION_TAG)))
						{
							m_toBeDeleted.push_back(m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]);
						}
                        if (playerAlive)
                        {
                            std::size_t posID = m_entities[playerID].GetComponentOfType(POSITION);
                            Position *pos = dynamic_cast<Position *>(m_components[posID]);
                            if (pos->GetPosition() == position->GetPosition())
                            {
                                m_toBeDeleted.push_back(playerID);
								createEntityAtPosition("blood_particle", position->GetPosition());
								killPlayer();
								return (false);
                            }
                        }
                    }
                    else if (m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] == -2)
                    {
                        explosion->SetChildExplosions(0);
                        explosion->SetDuration(0);
                    }
					if (explosion->GetChildExplosions() > 0)
					{
						Vec3 newPos = position->GetPosition() + explosion->GetDirection();
						Explosion *newExplosion = dynamic_cast<Explosion *>(m_components[m_entities[createEntityAtPosition("explosion", newPos)].GetComponentOfType(EXPLOSION)]);
						newExplosion->SetDirection(explosion->GetDirection());
						newExplosion->SetChildExplosions(explosion->GetChildExplosions() - 1);
						explosion->SetChildExplosions(0);
					}
					explosion->SetDuration(explosion->GetDuration() - Clock::Instance().GetDeltaTime());
					if (explosion->GetDuration() <= 0)
					{
						m_toBeDeleted.push_back(i);
                        std::cout << "Explosion done" << std::endl;
					}
				}
				catch (std::exception &e)
				{
					return (false);
				}
			}
		}

        //level exit System
        {
            if ((bitmask & TAG) == TAG)
            {
                try
                {
                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
                    std::size_t posID = m_entities[i].GetComponentOfType(POSITION);
                    Position *pos = dynamic_cast<Position *>(m_components[posID]);
                    if ((tag->GetTagMask() & LEVEL_EXIT_TAG) == LEVEL_EXIT_TAG)
                    {
                        if (m_enemiesToDestroy <= 0)
                        {
                            m_toBeDeleted.push_back(i);
                            createEntityAtPosition("level_exit_open", pos->GetPosition());
                        }
                    }
                }
                catch (std::exception &e)
                {
                    return (false);
                }
            }
        }
	}
	for (std::size_t i = 0; i < m_toBeDeleted.size(); i++)
	{
		deleteEntity(m_toBeDeleted[i]);
	}
	m_toBeDeleted.clear();
	m_action = P_NOACTION;

	return (false);
}

void        GameManager::GetRenderData(std::vector<GameObjectRenderInfo> &g)
{
	for (std::size_t i = m_entities.begin()->first; i < m_entities.size(); i++)
	{
		try
		{
			COMPONENT_MASK_TYPE mask = m_entities[i].GetComponentFlags();
			if ((mask & RENDER_SYSTEM_FLAGS) == RENDER_SYSTEM_FLAGS)
			{
				std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
				Position *position = dynamic_cast<Position *>(m_components[positionID]);
				std::size_t renderID = m_entities[i].GetComponentOfType(RENDER);
				Render *render = dynamic_cast<Render *>(m_components[renderID]);
				Direction dir = NORTH;

				if ((mask & MOVEMENT) == MOVEMENT)
				{
					std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
					Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
					if (movement->GetDirection().GetX() == 1)
					{
						dir = EAST;
					}
					else if (movement->GetDirection().GetX() == -1)
					{
						dir = WEST;
					}
					else if (movement->GetDirection().GetY() == 1)
					{
						dir = NORTH;
					}
					else if (movement->GetDirection().GetY() == -1)
					{
						dir = SOUTH;
					}
				}

				if (/*render->GetObjectType() == EXPLOSION_PE || */render->GetObjectType() == RUBBLE_PE || render->GetObjectType() == BLOOD_PE)
				{
					m_toBeDeleted.push_back(i);
				}

				GameObjectRenderInfo newObj(render->GetObjectType(), position->GetPosition(), dir);
				g.push_back(newObj);
			}
			for (std::size_t i = 0; i < m_toBeDeleted.size(); i++)
			{
				deleteEntity(m_toBeDeleted[i]);
			}
		}
		catch (std::exception &e)
		{

		}
	}
}

bool GameManager::GetGameStarted() const
{
	return (m_gameStarted);
}

void GameManager::SetGameStarted(bool gameStarted)
{
	m_gameStarted = gameStarted;
}

void GameManager::GivePlayerAction(ePlayerAction pa)
{
	m_action = pa;
}

bool GameManager::GetGamePaused() const
{
    return (m_paused);
}

void GameManager::LoadSave(std::string path)
{
	std::ifstream	file;
	file.open(path);

    if (file.is_open())
    {
        std::string save;
        getline(file, save);
        m_seed = std::stoi(save);
        getline(file, save);
        m_level = std::stoi(save);
        getline(file, save);
        m_score = std::stoi(save);
        getline(file, save);
        m_lives = std::stoi(save);
        file.close();
    }
    else
    {
        m_lives = 3;
        m_score = 0;
        m_seed = time(NULL);
        m_level = 1;
    }
    startLevel(false, m_seed);
}

void GameManager::WriteSave(std::string path)
{
	std::ofstream	file;
	file.open(path);

    file << m_seed << std::endl;
    file << m_level << std::endl;
    file << m_score << std::endl;
    file << m_lives << std::endl;
}

std::size_t GameManager::GetLives() const
{
    return (m_lives);
}

std::size_t GameManager::GetScore() const
{
    return (m_score);
}

std::size_t GameManager::GetBombs() const
{
    return (m_playerBombAmount);
}
