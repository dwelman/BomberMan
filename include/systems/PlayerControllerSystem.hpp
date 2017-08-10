#pragma once

#include "components/BaseComponent.hpp"
#include "components/PlayerController.hpp"
#include "components/Movement.hpp"

#define PLAYER_CONTROLLER_SYSTEM_FLAGS (PLAYERCONTROLLER)

namespace PlayerControllerSystem
{
    void    ChangePlayerMovement(PlayerController &pc, Movement &m);
}