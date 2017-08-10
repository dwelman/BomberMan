#include "GameManager.hpp"
#include "Clock.hpp"

#include <iostream>

GameManager::GameManager()
{
	m_currentComponentID = 0;
	m_deltaTime = 0.35f;
    createEntity("player");
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

void	GameManager::handleCollisions(Collision &c, Position &p, std::size_t ID)
{
	for (std::size_t i = 0; i < m_entities.size(); i++)
	{
		if (i != ID)
		{
			COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
			if ((bitmask & COLLISION_SYSTEM_FLAGS) == COLLISION_SYSTEM_FLAGS)
			{
				try
				{
					std::size_t collisionID = m_entities[i].GetComponentOfType(COLLISION);
					std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
					Collision *collision = static_cast<Collision*>(m_components[collisionID]);
					Position *position = static_cast<Position*>(m_components[positionID]);
					if (CollisionSystem::CheckCollision(p, c, *position, *collision) == true)
					{
						//Do collision
					}
				}
				catch (std::exception &e)
				{

				}
			}
		}
	}
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
}

/*
 * This factory method exists within the game manager as it is closely tied to the entity and component
 * lists within this class, therefore it makes the most sense to keep it within this class
 */
void GameManager::createEntity(std::string entityType)
{
    Entity entity;
    if (entityType == "player")
    {
        //TODO: Read this from config file later
        entity.RegisterComponent(m_currentComponentID, POSITION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Position(0, 0, 0)));
        entity.RegisterComponent(m_currentComponentID, COLLISION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
        entity.RegisterComponent(m_currentComponentID, MOVEMENT);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Movement(0, 0, 0, 10)));
        entity.RegisterComponent(m_currentComponentID, PLAYERCONTROLLER);
        m_components.emplace(std::make_pair(m_currentComponentID++, new PlayerController()));
    }
    else if (entityType == "indestructible_wall")
    {

    }
    else if (entityType == "destructible_wall")
    {

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

    }
    else
    {
        return ;
    }
    m_entities.push_back(Entity(entity));
}


void GameManager::deleteEntity(std::size_t ID)
{
    std::vector<std::size_t>    components;

    components = m_entities[ID].GetChildrenIDs();
    for (std::size_t i = 0; i < components.size(); i++)
    {
        auto iter = m_components.find(components[i]);
        if (iter != m_components.end())
        {
            m_components.erase(iter);
        }
    }
    m_entities.erase(m_entities.begin() + ID);
}

bool 	GameManager::Update()
{
	m_deltaTime = Clock::Instance().GetDeltaTime();
	for (std::size_t i = 0; i < m_entities.size(); i++)
	{
        //Check each component for the relevant flags
        COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
        //Player control system
        {
            if ((bitmask & PLAYER_CONTROLLER_SYSTEM_FLAGS) == PLAYER_CONTROLLER_SYSTEM_FLAGS)
            {
                try
                {
                    std::size_t playerControllerID = m_entities[i].GetComponentOfType(PLAYERCONTROLLER);
                    PlayerController *playerController = dynamic_cast<PlayerController *>(m_components[playerControllerID]);
                    //Do something with movement
                    if ((bitmask & MOVEMENT) == MOVEMENT)
                    {
                        std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
                        Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
                    }
                }
                catch (std::exception &e)
                {

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
                }
                catch (std::exception &e)
                {
                    return (false);
                }
            }
        }

        //Collision System
        {
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
                        handleCollisions(*collision, *position, i);
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
                        //Explode
                        deleteEntity(i);
                    }
                }
                catch (std::exception &e)
                {
                    return (false);
                }
            }
        }
		return (false);
	}
}
