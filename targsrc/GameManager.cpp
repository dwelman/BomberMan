#include "GameManager.hpp"

GameManager::GameManager()
{
	m_currentComponentID = 0;
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

void	GameManager::checkCollisions(Collision &c, Position &p, std::size_t ID)
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
        m_components.emplace(std::make_pair(m_currentComponentID++, new Movement(0, 0, 0)));
        //m_components.emplace(std::make_pair(m_currentComponentID++, new ));
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

void 	GameManager::Update()
{
	for (std::size_t i = 0; i < m_entities.size(); i++)
	{
        //Check each component for the relevant flags
        COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
        //Player control system
        {
            /*if ((bitmask & MOVEMENT_SYSTEM_FLAGS) == MOVEMENT_SYSTEM_FLAGS)
            {
                try
                {
                    std::size_t movementID = m_entities[i].GetComponentOfType(MOVEMENT);
                    std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
                    Movement *movement = dynamic_cast<Movement *>(m_components[movementID]);
                    Position *position = dynamic_cast<Position *>(m_components[positionID]);
                    //Do something with movement
                }
                catch (std::exception &e)
                {

                }
            }*/
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
                    //Do something with movement
                }
                catch (std::exception &e)
                {

                }
            }
        }

        //Collision System
        {
            if ((bitmask & COLLISION_SYSTEM_FLAGS) == COLLISION_SYSTEM_FLAGS)
            {
                try {
                    std::size_t collisionID = m_entities[i].GetComponentOfType(COLLISION);
                    std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
                    Collision *collision = dynamic_cast<Collision *>(m_components[collisionID]);
                    Position *position = dynamic_cast<Position *>(m_components[positionID]);
                    if (collision->GetCheckCollision() == true)
                    {
                        checkCollisions(*collision, *position, i);
                    }
                }
                catch (std::exception &e)
                {

                }
            }
        }
	}
}
