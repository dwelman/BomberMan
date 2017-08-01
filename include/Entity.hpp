#pragma once

#include "components/Position.hpp"
#include "components/Collision.hpp"

//A bit mask is used to quickly identify what components an entity has without costly checking
enum ComponentMask
{
	POSITION = 1,
	COLLISION = 2,
	RENDER = 4,
	MOVEMENT = 8
};

class Entity
{
private:
	
public:

};
