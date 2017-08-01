#pragma once

#include <vector>

#include "StateObject.hpp"

class MenuStateMachine
{
private:
	std::size_t					m_currentState;
	std::vector<StateObject>	m_states;
public:
	MenuStateMachine();
	MenuStateMachine(MenuStateMachine const &m);
	MenuStateMachine			&operator=(MenuStateMachine const &m);
	~MenuStateMachine();
	void						ActivateStateAt(std::size_t i) const;
	void						ActivateCurrentState() const;
	void						ShiftStateUp();
	void						ShiftStateDown();
	void						AddState(void(*activateFunc)(void));
    std::size_t                 GetActiveState() const;
};
