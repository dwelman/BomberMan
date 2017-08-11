#include "components/PlayerData.hpp"

PlayerData::PlayerData() : BaseComponent(PLAYER_DATA)
{

}

PlayerData::PlayerData(std::size_t bombNumber, float moveSpeed) : PlayerData()
{
    m_bombNumber = bombNumber;
    m_moveSpeed = moveSpeed;
}

PlayerData::PlayerData(PlayerData const &pd) : PlayerData()
{
    *this = pd;
}

PlayerData::~PlayerData()
{

}

PlayerData  &PlayerData::operator=(PlayerData const &pd)
{
    m_bombNumber = pd.m_bombNumber;
    m_moveSpeed = pd.m_moveSpeed;
    return (*this);
}

std::size_t PlayerData::GetBombNumber() const
{
    return (m_bombNumber);
}

void        PlayerData::SetBombNumber(std::size_t bombNumber)
{
    m_bombNumber = bombNumber;
}

float       PlayerData::GetMoveSpeed() const
{
    return (m_moveSpeed);
}

void        PlayerData::SetMoveSpeed(float moveSpeed)
{
    m_moveSpeed = moveSpeed;
}