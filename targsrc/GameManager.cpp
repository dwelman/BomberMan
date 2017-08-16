#include "GameManager.hpp"
#include "Clock.hpp"

#include <iostream>
#include <time.h>

GameManager::GameManager()
{
	m_currentComponentID = 0;
    m_gameStarted = false;
    m_playerMoveSpeed = 2;
    m_playerBombAmount = 1;
    m_explosionSize = 1;
    m_lives = 3;
    m_score = 0;
    createEntityAtPosition("player", Vec3(0, 0, 0));
    srand(time(NULL));
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

void	GameManager::handleCollisions(Collision &c, Position &p, Tag &t, std::size_t ID)
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
                            //Entity hits a wall and must turn around
                        }
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

void GameManager::createEntityAtPosition(std::string entityType, Vec3 const &pos)
{
    Entity entity;
    if (entityType == "player")
    {
        //TODO: Read this from config file later
        entity.RegisterComponent(m_currentComponentID, POSITION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Position(pos)));
        entity.RegisterComponent(m_currentComponentID, COLLISION);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Collision(0.5f, 0.5f, 0.5f, true)));
        entity.RegisterComponent(m_currentComponentID, MOVEMENT);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Movement(0, 0, 0, m_playerMoveSpeed)));
        entity.RegisterComponent(m_currentComponentID, PLAYERCONTROLLER);
        m_components.emplace(std::make_pair(m_currentComponentID++, new PlayerController()));
        entity.RegisterComponent(m_currentComponentID, TAG);
        m_components.emplace(std::make_pair(m_currentComponentID++, new Tag(PLAYER_TAG)));
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
        m_components.emplace(std::make_pair(m_currentComponentID++, new Explosion(m_explosionSize, Vec3(0, 0, 0), 0.4)));
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
    std::cout << m_entities.size() << std::endl;
    std::cout << m_components.size() << std::endl;
    m_toBeDeleted.clear();
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
                        if (m_action == P_MOVE_LEFT)
                        {
                            movement->SetDirection(Vec3(-1, 0, 0));
                        }
                        else if (m_action == P_MOVE_RIGHT)
                        {
                            movement->SetDirection(Vec3(1, 0, 0));
                        }
                        else if (m_action == P_MOVE_UP)
                        {
                            movement->SetDirection(Vec3(0, 1, 0));
                        }
                        else if (m_action == P_MOVE_DOWN)
                        {
                            movement->SetDirection(Vec3(0, -1, 0));
                        }
                        //std::cout << m_action << std::endl;
                    }

                    //if bomb placed
                    if (m_action == P_PLACE_BOMB)
                    {
                        std::size_t positionID = m_entities[i].GetComponentOfType(POSITION);
                        Position *position = dynamic_cast<Position *>(m_components[positionID]);
                        if (m_playerBombAmount > 0)
                        {
                            m_playerBombAmount--;
                            createEntityAtPosition("bomb", position->GetPosition());
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
                    std::cout << bomb->GetBombTime() << std::endl;
                    if (bomb->GetBombTime() <= 0)
                    {
                        Explosion *explosion;
                        createEntityAtPosition("explosion", position->GetPosition());
                        explosion = dynamic_cast<Explosion *>(m_components[m_entities.back().GetComponentOfType(EXPLOSION)]);
                        explosion->SetDirection(Vec3(1, 0, 0));
                        createEntityAtPosition("explosion", position->GetPosition());
                        explosion = dynamic_cast<Explosion *>(m_components[m_entities.back().GetComponentOfType(EXPLOSION)]);
                        explosion->SetDirection(Vec3(-1, 0, 0));
                        createEntityAtPosition("explosion", position->GetPosition());
                        explosion = dynamic_cast<Explosion *>(m_components[m_entities.back().GetComponentOfType(EXPLOSION)]);
                        explosion->SetDirection(Vec3(0, 1, 0));
                        createEntityAtPosition("explosion", position->GetPosition());
                        explosion = dynamic_cast<Explosion *>(m_components[m_entities.back().GetComponentOfType(EXPLOSION)]);
                        explosion->SetDirection(Vec3(0, -1, 0));
                        m_playerBombAmount++;
                        m_toBeDeleted.push_back(i);
                        std::cout << "Bomb exploded" << std::endl;
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
                    if (explosion->GetChildExplosions() > 0)
                    {
                        Vec3 newPos = position->GetPosition() + explosion->GetDirection();
                        createEntityAtPosition("explosion", newPos);
                        Explosion *newExplosion = dynamic_cast<Explosion *>(m_components[m_entities.back().GetComponentOfType(EXPLOSION)]);
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

        for (std::size_t i = 0; i < m_toBeDeleted.size(); i++)
        {
            deleteEntity(i);
        }
        m_action = P_NOACTION;
		return (false);
	}
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
                Render *render= dynamic_cast<Render *>(m_components[renderID]);
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
