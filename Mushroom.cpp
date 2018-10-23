#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "Mushroom.h"



Mushroom::~Mushroom()
{
}

SDL_Rect * Mushroom::GetSprite()
{
	if (!hit)
	{
		return current_sprite;
	}
	else if (time > 5 && hit)
	{
		time = 0;
		hit = false;
		return current_sprite = &sprites[0];
	}
	else
	{
		time++;
		return current_sprite;
	}
}

void Mushroom::Hit(b2Contact* contact, PhysBody* bodyA)
{
	hit = true;
	//collected = true;
	phys->body->SetLinearVelocity({ 0.0f, PIXEL_TO_METERS(-50.0f) });


	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	float normalLength = 0.1f;
	bodyA->body->ApplyForce(normalLength * 1000 * worldManifold.normal, worldManifold.points[0], false);
}

void Mushroom::Restart()
{
	active = true;
	current_sprite = &sprites[rand() % 4];
	/*collected = false;
	timer = 0.0f;*/
	phys->body->SetLinearVelocity({ 0.0f, 0.0f });
	phys->body->SetTransform(start_position, start_rotation);
}

Mushroom::Mushroom()
{
	
}