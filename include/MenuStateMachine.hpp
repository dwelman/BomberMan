#pragma once

#include <vector>

class MenuStateMachine
{
public:
	struct StateObject
	{
		void(*activate)(void);
		StateObject();
		StateObject(void(*activateFunc)(void));
		StateObject(StateObject const &s);
		void					Activate() const;
		StateObject				&operator=(StateObject const &s);
	};

	MenuStateMachine();
	MenuStateMachine(MenuStateMachine const &m);
	MenuStateMachine			&operator=(MenuStateMachine const &m);
	~MenuStateMachine();
	void						ActivateStateAt(std::size_t i) const;
	void						ActivateCurrentState() const;
	void						ShiftStateUp();
	void						ShiftStateDown();
	void						AddState(void(*activateFunc)(void));
private:
	std::size_t					currentState;
	std::vector<StateObject>	states;
};
