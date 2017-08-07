#pragma once

#include "Vec3.hpp"
#include "components/Position.hpp"
#include "components/BaseComponent.hpp"

class Collision : public BaseComponent
{
private:
    Vec3    m_colliderSize;
	//If set to false, this component will not check collision for itself. Use on
	// non moving objects. False by default
	bool	m_checkCollision;

    Collision();
public:
	Collision(Vec3 const &colliderSize);
	Collision(Vec3 const &colliderSize, bool checkCollision);
	Collision(float x, float y, float z);
	Collision(float x, float y, float z, bool checkCollision);
    Collision(Collision const &c);
    ~Collision();

    Collision   &operator=(Collision const &c);

    Vec3        GetColliderSize() const;
    void        SetColliderSize(Vec3 const &v);
	bool		GetCheckCollision() const;
	void		SetCheckCollision(bool checkCollision);
};

