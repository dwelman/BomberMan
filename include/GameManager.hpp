#pragma once

#include <vector>

#include "Entity.hpp"

class GameManager
{
private:
	std::vector<Entity>	m_entities;
	//std::vector<*AComponent> m_components
public:
	GameManager();
	GameManager(GameManager const &gm);
	~GameManager();

	GameManager	&operator=(GameManager const &gm);
    void        Update();
};
