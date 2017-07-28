#pragma once

#include <vector>

class StateObject
{
public:
    StateObject(void(*activateFunc)(void));
    StateObject(StateObject const &s);
    ~StateObject();
    StateObject				&operator=(StateObject const &s);

    void					Activate() const;
private:
    StateObject();
    void(*activate)(void);
};
