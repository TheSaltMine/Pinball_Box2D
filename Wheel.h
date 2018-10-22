#pragma once
#include "Interactable.h"

class b2RevoluteJoint;

class Wheel :
	public Interactable
{
public:
	Wheel();
	~Wheel();

	b2RevoluteJoint* joint;
	void Hit(b2Contact* contact, PhysBody* bodyA);
	void Restart();
	float32 start_rotation;
	b2Vec2 start_position;
};

