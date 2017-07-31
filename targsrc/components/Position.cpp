#include "components/Position.hpp"

Position::Position()
{

}

Position::Position(Vec3 const &v) : m_pos(v)
{

}

Position::Position(float x, float y, float z) : m_pos(x, y, z)
{

}

Position::Position(Position const &p)
{
    *this = p;
}

Position    &Position::operator=(Position const &p)
{
    this->m_pos = p.m_pos;
    return (*this);
}

bool        Position::operator==(Position const &p)
{
    return (this->m_pos == p.m_pos);
}

Position    &Position::operator+=(Position const &p)
{
    this->m_pos += p.m_pos;
    return (*this);
}

Position    &Position::operator-=(Position const &p)
{
    this->m_pos -= p.m_pos;
    return (*this);
}

Position    &Position::operator/=(Position const &p)
{
    this->m_pos /= p.m_pos;
    return (*this);
}

Position    &Position::operator*=(Position const &p)
{
    this->m_pos *= p.m_pos;
    return (*this);
}

Vec3        Position::GetPosition() const
{
    return (m_pos);
}

void        Position::SetPosition(Vec3 const &p)
{
    m_pos = p;
}

Position        operator+(Position lhs, Position const &rhs)
{
    lhs.SetPosition(lhs.GetPosition() + rhs.GetPosition());
    return (lhs);
}

Position        operator-(Position lhs, Position const &rhs)
{
    lhs.SetPosition(lhs.GetPosition() - rhs.GetPosition());
    return (lhs);
}

Position        operator/(Position lhs, Position const &rhs)
{
    lhs.SetPosition(lhs.GetPosition() / rhs.GetPosition());
    return (lhs);
}

Position        operator*(Position lhs, Position const &rhs)
{
    lhs.SetPosition(lhs.GetPosition() * rhs.GetPosition());
    return (lhs);
}