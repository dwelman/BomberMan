#pragma once

#include <cstddef>
#include "components/BaseComponent.hpp"

class PlayerData : public BaseComponent
{
private:
    std::size_t m_bombNumber;
    float       m_moveSpeed;

    PlayerData();
public:
    PlayerData(std::size_t bombNumber, float moveSpeed);
    PlayerData(PlayerData const &pd);
    ~PlayerData();

    PlayerData  &operator=(PlayerData const &pd);

    std::size_t GetBombNumber() const;
    void        SetBombNumber(std::size_t bombNumber);
    float       GetMoveSpeed() const;
    void        SetMoveSpeed(float moveSpeed);
};
