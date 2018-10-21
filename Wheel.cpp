#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "Wheel.h"



Wheel::Wheel()
{
}


Wheel::~Wheel()
{
}

void Wheel::Hit()
{
	joint->EnableMotor(true);
	joint->EnableLimit(false);
}

void Wheel::Restart()
{
	joint->EnableMotor(false);
	joint->EnableLimit(true);
}
