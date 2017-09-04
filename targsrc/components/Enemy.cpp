#include "components/Enemy.hpp"

Enemy::Enemy() : BaseComponent(ENEMY)
{
}

Enemy::Enemy(Enemy const & e) : Enemy()
{
	*this = e;
}

Enemy & Enemy::operator=(Enemy const & e)
{
	m_enemyType = e.m_enemyType;
	return (*this);
}

Enemy::Enemy(short enemyType) : Enemy()
{
	m_enemyType = enemyType;
}

Enemy::~Enemy()
{
}

short Enemy::GetEnemyType() const
{
	return (m_enemyType);
}
