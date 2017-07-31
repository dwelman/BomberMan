#include "GameManager.hpp"

GameManager::GameManager()
{
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

void GameManager::Update()
{
}
