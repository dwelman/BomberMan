#include "GameManager.hpp"
#include "Clock.hpp"

#include <iostream>
#include <time.h>
#include <cmath>

GameManager::GameManager()
{
	m_currentEntityID = 0;
	m_currentComponentID = 0;
	m_gameStarted = false;
	m_playerMoveSpeed = 4.5f;
	m_playerBombAmount = 1;
	m_explosionSize = 1;
	m_lives = 3;
	m_score = 0;
	createEntityAtPosition("player", Vec3(1, 1, 0));
	srand(time(NULL));

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

    for (std::size_t y = 0; y < MAP_Y; y++)
    {
        for (std::size_t x = 0; x < MAP_X; x++)
        {
            if (m_gameMap[y][x] == -1 && !(y == 2 && x == 1) && !(y == 1 && x == 2) && !(y == 1 && x == 1))
            {
                if (rand() % 100 > 40)
                {
                    createEntityAtPosition("destructible_wall", Vec3(x, y, 1));
                }
            }
        }
    }
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
		//TODO: Read this from config file later
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
	else if (entityType == "enemy_1")
	{

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
		m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(DAMAGE_ENEMY_TAG | DAMAGE_PLAYER_TAG | DAMAGE_WALL_TAG)));
		entity.RegisterComponent(m_currentComponentID, EXPLOSION);
		m_components.emplace(std::make_pair(m_currentComponentID++, new Explosion(m_explosionSize, Vec3(0, 0, 0), 0.4f)));
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

bool 	GameManager::Update()
{
	m_deltaTime = Clock::Instance().GetDeltaTime();
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
        if (!m_entities[i].GetCanTick())
        {
            continue;
        }
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
                    if (!((tag->GetTagMask() & (INDESTRUCTIBLE_TAG | WALL_TAG)) == (INDESTRUCTIBLE_TAG | WALL_TAG)))
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
                                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

                                    if ((tag->GetTagMask() & (POWERUP_TAG | ENEMY_TAG)) == (POWERUP_TAG | ENEMY_TAG))
                                    {
                                        MovementSystem::SetMovement(*movement, *position, Vec3(-1, 0, 0));
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
                                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

                                    if ((tag->GetTagMask() & (POWERUP_TAG | ENEMY_TAG)) == (POWERUP_TAG | ENEMY_TAG))
                                    {
                                        MovementSystem::SetMovement(*movement, *position, Vec3(1, 0, 0));
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
                            long ID = m_gameMap[(long int)position->GetPosition().GetY() + 1][(long int)position->GetPosition().GetX()];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

                                    if ((tag->GetTagMask() & (POWERUP_TAG | ENEMY_TAG)) == (POWERUP_TAG | ENEMY_TAG))
                                    {
                                        MovementSystem::SetMovement(*movement, *position, Vec3(0, 1, 0));
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
                            long ID = m_gameMap[(long int)position->GetPosition().GetY() - 1][(long int)position->GetPosition().GetX()];
                            if (ID >= 0)
                            {
                                COMPONENT_MASK_TYPE flags = m_entities[ID].GetComponentFlags();
                                if ((flags & TAG) == TAG)
                                {
                                    std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
                                    Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);

                                    if ((tag->GetTagMask() & (POWERUP_TAG | ENEMY_TAG)) == (POWERUP_TAG | ENEMY_TAG))
                                    {
                                        MovementSystem::SetMovement(*movement, *position, Vec3(0, -1, 0));
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
                    if (m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()] >= 0)
                    {
                        std::size_t tagID = m_entities[m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]].GetComponentOfType(TAG);
                        Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
                        if ((tag->GetTagMask() & (WALL_TAG)) == (WALL_TAG))
                        {
                            explosion->SetChildExplosions(0);
                            explosion->SetDuration(0);
                        }
                        if ((tag->GetTagMask() & (BOMB_TAG)) == (BOMB_TAG))
                        {
                            std::size_t bombID = m_entities[m_gameMap[(int)position->GetPosition().GetY()][(int)position->GetPosition().GetX()]].GetComponentOfType(BOMB);
                            Bomb *bomb = dynamic_cast<Bomb *>(m_components[bombID]);
                            bomb->SetBombTime(0);
                        }
                        else
                        {
                            m_toBeDeleted.push_back(m_gameMap[(int) position->GetPosition().GetY()][(int) position->GetPosition().GetX()]);
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
						createEntityAtPosition("explosion", newPos);
						Explosion *newExplosion = dynamic_cast<Explosion *>(m_components[m_entities[m_currentEntityID - 1].GetComponentOfType(EXPLOSION)]);
						newExplosion->SetDirection(explosion->GetDirection());
						newExplosion->SetChildExplosions(explosion->GetChildExplosions() - 1);
						explosion->SetChildExplosions(0);
					}
					explosion->SetDuration(explosion->GetDuration() - Clock::Instance().GetDeltaTime());
					if (explosion->GetDuration() <= 0)
					{
						m_toBeDeleted.push_back(i);
					}
				}
				catch (std::exception &e)
				{
					return (false);
				}
			}
		}

		//Collision System
		/*{
			if ((bitmask & COLLISION_SYSTEM_FLAGS) == COLLISION_SYSTEM_FLAGS)
			{
				try
				{
					std::size_t collisionID = m_entities[i].GetComponentOfType(COLLISION);
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					Collision *collision = dynamic_cast<Collision *>(m_components[collisionID]);
					Position *position = dynamic_cast<Position *>(m_components[positionID]);
					if (collision->GetCheckCollision() == true)
					{
						std::size_t tagID = m_entities[i].GetComponentOfType(TAG);
						Tag *tag = dynamic_cast<Tag *>(m_components[tagID]);
						handleCollisions(*collision, *position, *tag, i);
					}
				}
				catch (std::exception &e)
				{
				return (false);
				}
			}
		}*/

		m_action = P_NOACTION;
	}
	for (std::size_t i = 0; i < m_toBeDeleted.size(); i++)
	{
		deleteEntity(m_toBeDeleted[i]);
	}
	m_toBeDeleted.clear();
	return (false);
}

void        GameManager::GetRenderData(std::vector<GameObjectRenderInfo> &g)
{
	for (std::size_t i = 0; i < m_entities.size(); i++)
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

				GameObjectRenderInfo newObj(render->GetObjectType(), position->GetPosition(), dir);
				g.push_back(newObj);
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
