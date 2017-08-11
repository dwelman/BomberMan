#pragma once

#include <cstdio>
#include "Vec3.hpp"
#include "components/BaseComponent.hpp"

class PlayerController : public BaseComponent
{
private:

public:
    PlayerController();
    PlayerController(PlayerController const &src);
    ~PlayerController();

    PlayerController    &operator=(PlayerController const &cp);
};