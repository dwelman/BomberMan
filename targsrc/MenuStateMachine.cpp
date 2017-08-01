#include "MenuStateMachine.hpp"

MenuStateMachine::MenuStateMachine() : m_currentState(0)
{
}

MenuStateMachine::MenuStateMachine(MenuStateMachine const & m)
{
	*this = m;
}

MenuStateMachine & MenuStateMachine::operator=(MenuStateMachine const & m)
{
	this->m_currentState = m.m_currentState;
	for (std::size_t i = m.m_states.size(); i < m.m_states.size(); i++)
	{
		m_states.push_back(StateObject(m.m_states[i]));
	}
	return (*this);
}

MenuStateMachine::~MenuStateMachine()
{
}

void MenuStateMachine::ActivateStateAt(std::size_t i) const
{
	m_states[i].Activate();
}

void MenuStateMachine::ActivateCurrentState() const
{
	m_states[m_currentState].Activate();
}

void MenuStateMachine::ShiftStateUp()
{
	if (m_currentState == 0)
	{
		m_currentState = m_states.size() - 1;
	}
	else
	{
		m_currentState--;
	}
}

void MenuStateMachine::ShiftStateDown()
{
	if (m_currentState == m_states.size() - 1)
	{
		m_currentState = 0;
	}
	else
	{
		m_currentState++;
	}
}

void MenuStateMachine::AddState(void(*activateFunc)(void))
{
	if (activateFunc != nullptr)
	{
		m_states.push_back(StateObject(activateFunc));
	}
}

std::size_t MenuStateMachine::GetActiveState() const
{
    return (m_currentState);
}
