#pragma once

#include "Vec3.hpp"

class Position
{
private:
    Vec3    m_pos;
public:
    Position();
    Position(Vec3 const &v);
    Position(float x, float y, float z);
    Position(Position const &p);

    Position    &operator=(Position const &p);
    bool        operator==(Position const &p);
};
