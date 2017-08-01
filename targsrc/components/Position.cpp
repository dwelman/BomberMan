#include "components/Position.hpp"

Position::Position() : BaseComponent(POSITION)
{

}

Position::Position(Vec3 const &v) : Position()
{
    m_pos = v;
}

Position::Position(float x, float y, float z) : Position()
{
    m_pos = Vec3(x, y, z);
}

Position::Position(Position const &p) : Position()
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