#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"

class PlayerController : public BaseComponent
{
    public:
        PlayerController();
        PlayerController(PlayerController const &src);
        ~PlayerController();

    PlayerController    &operator=(PlayerController const &cp);

};