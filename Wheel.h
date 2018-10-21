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
	void Hit();
	void Restart();
};

