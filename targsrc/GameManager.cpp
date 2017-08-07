#include "GameManager.hpp"

GameManager::GameManager()
{
	m_currentEntityID = 0;
	m_currentComponentID = 0;
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

void	GameManager::CheckCollisions(Collision &c, Position &p, std::size_t ID)
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

void 	GameManager::Update()
{
	//Collision System
	for (std::size_t i = 0; i < m_entities.size(); i++)
	{
		//Check each component for the relevant flags
		COMPONENT_MASK_TYPE bitmask = m_entities[i].GetComponentFlags();
		if ((bitmask & COLLISION_SYSTEM_FLAGS) == COLLISION_SYSTEM_FLAGS)
		{
			try
			{
				std::size_t collisionID = m_entities[i].GetComponentOfType(COLLISION);
				std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
				Collision *collision = static_cast<Collision*>(m_components[collisionID]);
				Position *position = static_cast<Position*>(m_components[positionID]);
				if (collision->GetCheckCollision() == true)
				{
					CheckCollisions(*collision, *position, i);
				}
			}
			catch (std::exception &e)
			{

			}
		}
	}
}
