#include "components/Bomb.hpp"

Bomb::Bomb() : BaseComponent(BOMB)
{

}

Bomb::Bomb(double bombTime) : Bomb()
{
    m_bombTime = bombTime;
}

Bomb::~Bomb()
{

}

double  Bomb::GetBombTime() const
{
    return (m_bombTime);
}

void    Bomb::SetBombTime(double time)
{
    m_bombTime = time;
}
