#pragma once

class Vec3
{
private:
    float m_x;
    float m_y;
    float m_z;
public:
    Vec3();
    Vec3(float x, float y, float z);
    Vec3(Vec3 const &v);
    ~Vec3();

    Vec3    &operator=(Vec3 const &v);
    Vec3    &operator+=(Vec3 const &v);
    Vec3    &operator-=(Vec3 const &v);
    Vec3    &operator/=(Vec3 const &v);
    Vec3    &operator*=(Vec3 const &v);
    bool    operator==(Vec3 const &v);

    float   GetX() const;
    float   GetY() const;
    float   GetZ() const;
    void    SetX(float x);
    void    SetY(float y);
    void    SetZ(float z);
};

Vec3    operator+(Vec3 lhs, Vec3 const &rhs);
Vec3    operator-(Vec3 lhs, Vec3 const &rhs);
Vec3    operator*(Vec3 lhs, Vec3 const &rhs);
Vec3    operator/(Vec3 lhs, Vec3 const &rhs);

