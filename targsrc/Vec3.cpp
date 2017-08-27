#include "Vec3.hpp"

Vec3::Vec3() : m_x(0.f), m_y(0.f), m_z(0.f)
{

}

Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{

}

Vec3::Vec3(Vec3 const &v)
{
    *this = v;
}

Vec3::~Vec3()
{

}

Vec3    &Vec3::operator=(Vec3 const &v)
{
    m_x = v.m_x;
    m_y = v.m_y;
    m_z = v.m_z;
    return (*this);
}

Vec3    &Vec3::operator+=(Vec3 const &v)
{
    *this = *this + v;
    return (*this);
}

Vec3    &Vec3::operator-=(Vec3 const &v)
{
    *this = *this - v;
    return (*this);
}

Vec3    &Vec3::operator/=(Vec3 const &v)
{
    *this = *this / v;
    return (*this);
}

Vec3    &Vec3::operator*=(Vec3 const &v)
{
    *this = *this * v;
    return (*this);
}

bool    Vec3::operator==(Vec3 const &v)
{
    return (m_x == v.GetX() && m_y == v.GetY() && m_z == v.GetZ());
}

float   Vec3::GetX() const
{
    return (m_x);
}

float   Vec3::GetY() const
{
    return (m_y);
}

float   Vec3::GetZ() const
{
    return (m_z);
}

void    Vec3::SetX(float x)
{
    m_x = x;
}

void    Vec3::SetY(float y)
{
    m_y = y;
}

void    Vec3::SetZ(float z)
{
    m_z = z;
}

Vec3    operator+(Vec3 lhs, Vec3 const &rhs)
{
    lhs.SetX(lhs.GetX() + rhs.GetX());
    lhs.SetY(lhs.GetY() + rhs.GetY());
    lhs.SetZ(lhs.GetZ() + rhs.GetZ());
    return (lhs);
}

Vec3    operator-(Vec3 lhs, Vec3 const &rhs)
{
    lhs.SetX(lhs.GetX() - rhs.GetX());
    lhs.SetY(lhs.GetY() - rhs.GetY());
    lhs.SetZ(lhs.GetZ() - rhs.GetZ());
    return (lhs);
}

Vec3    operator*(Vec3 lhs, Vec3 const &rhs)
{
    lhs.SetX(lhs.GetX() * rhs.GetX());
    lhs.SetY(lhs.GetY() * rhs.GetY());
    lhs.SetZ(lhs.GetZ() * rhs.GetZ());
    return (lhs);
}

Vec3    operator/(Vec3 lhs, Vec3 const &rhs)
{
    lhs.SetX(lhs.GetX() / rhs.GetX());
    lhs.SetY(lhs.GetY() / rhs.GetY());
    lhs.SetZ(lhs.GetZ() / rhs.GetZ());
    return (lhs);
}

Vec3 operator*(Vec3 lhs, float rhs)
{
    lhs.SetX(lhs.GetX() * rhs);
    lhs.SetY(lhs.GetY() * rhs);
    lhs.SetZ(lhs.GetZ() * rhs);
    return (lhs);
}
