#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"

class Position : public BaseComponent
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
    Position    &operator+=(Position const &p);
    Position    &operator-=(Position const &p);
    Position    &operator/=(Position const &p);
    Position    &operator*=(Position const &p);

    Vec3        GetPosition() const;
    void        SetPosition(Vec3 const &p);
};

Position        operator+(Position lhs, Position const &rhs);
Position        operator-(Position lhs, Position const &rhs);
Position        operator/(Position lhs, Position const &rhs);
Position        operator*(Position lhs, Position const &rhs);
