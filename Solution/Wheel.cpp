#include "ModulePhysics.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Wheel.h"


Wheel::Wheel()
{
}


Wheel::~Wheel()
{
}

void Wheel::Hit(b2Contact* contact, PhysBody* bodyA)
{
	if (bodyA->type != EXTRA_BALL)
	{
		joint->EnableMotor(true);
		joint->EnableLimit(false);
	}
}

void Wheel::Restart()
{
	joint->EnableMotor(false);
	joint->EnableLimit(true);
	phys->body->SetTransform(start_position, start_rotation);
}
