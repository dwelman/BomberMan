#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"


class Movement : public BaseComponent
{
    private:
        Movement();

        Vec3 m_velocity;

    public:
        Movement(Movement const &src);
        Movement(Vec3 vel);
        Movement(float x, float y, float z);
        ~Movement();

        Vec3 getVelocity()const;

        void setVelocity(float x, float y, float z);
        void setVelocity(Vec3 vel);

        Movement &operator=(Movement const &cp);
};