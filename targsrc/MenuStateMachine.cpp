#include "MenuStateMachine.hpp"

MenuStateMachine::MenuStateMachine() : currentState(0)
{
}

MenuStateMachine::MenuStateMachine(MenuStateMachine const & m)
{
	*this = m;
}

MenuStateMachine & MenuStateMachine::operator=(MenuStateMachine const & m)
{
	this->currentState = m.currentState;
	for (std::size_t i = m.states.size(); i < m.states.size(); i++)
	{
		states.push_back(StateObject(m.states[i]));
	}
	return (*this);
}

MenuStateMachine::~MenuStateMachine()
{
}

void MenuStateMachine::ActivateStateAt(std::size_t i) const
{
	states[i].Activate();
}

void MenuStateMachine::ActivateCurrentState() const
{
	states[currentState].Activate();
}

void MenuStateMachine::ShiftStateUp()
{
	if (currentState == 0)
	{
		currentState = states.size() - 1;
	}
	else
	{
		currentState--;
	}
}

void MenuStateMachine::ShiftStateDown()
{
	if (currentState == states.size() - 1)
	{
		currentState = 0;
	}
	else
	{
		currentState++;
	}
}

void MenuStateMachine::AddState(void(*activateFunc)(void))
{
	if (activateFunc != nullptr)
	{
		states.push_back(StateObject(activateFunc));
	}
}

MenuStateMachine::StateObject::StateObject() : activate(nullptr)
{
}

MenuStateMachine::StateObject::StateObject(void(*activateFunc)(void)) : activate(activateFunc)
{
}

MenuStateMachine::StateObject::StateObject(StateObject const & s)
{
	*this = s;
}

void MenuStateMachine::StateObject::Activate() const
{
	if (activate != nullptr)
	{
		activate();
	}
}

MenuStateMachine::StateObject & MenuStateMachine::StateObject::operator=(StateObject const & s)
{
	this->activate = s.activate;
	return (*this);
}
