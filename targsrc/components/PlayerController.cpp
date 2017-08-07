#include "components/PlayerController.hpp"

PlayerController::PlayerController() : BaseComponent(PLAYERCONTROLLER)
{

}

PlayerController::PlayerController(PlayerController const &src) : PlayerController()
{
    *this = src;
}

PlayerController::~PlayerController()
{

}

PlayerController &PlayerController::operator=(PlayerController const &cp)
{
    return(*this);
}