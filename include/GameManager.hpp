#pragma once

#include <vector>

#include "Entity.hpp"
#include "components/BaseComponent.hpp"

class GameManager
{
private:
	std::vector<Entity>			m_entities;
	std::vector<BaseComponent*>	m_components;
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    void        Update();
};
