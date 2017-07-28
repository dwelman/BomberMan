#include "StateObject.hpp"

StateObject::StateObject() : activate(nullptr)
{
}

StateObject::StateObject(void(*activateFunc)(void)) : activate(activateFunc)
{
}

StateObject::~StateObject()
{
}

StateObject::StateObject(StateObject const & s)
{
    *this = s;
}

void StateObject::Activate() const
{
    if (activate != nullptr)
    {
        activate();
    }
}

StateObject & StateObject::operator=(StateObject const & s)
{
    this->activate = s.activate;
    return (*this);
}