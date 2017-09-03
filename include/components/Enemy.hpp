#pragma once

#include "components/BaseComponent.hpp"

class Enemy : public BaseComponent
{
private:
	short	m_enemyType;

	Enemy();
	Enemy(Enemy const &e);

	Enemy    &operator=(Enemy const &e);
public:
	Enemy(short enemyType);

	~Enemy();

	short	GetEnemyType() const;
};