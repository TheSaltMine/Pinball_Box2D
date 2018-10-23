#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "Bumper.h"



Bumper::~Bumper()
{
}

SDL_Rect * Bumper::GetSprite()
{
	if (!hit)
	{
		return current_sprite;
	}
	else if (time > 20 && hit)
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

void Bumper::Hit(b2Contact* contact, PhysBody* bodyA)
{
	hit = true;
	current_sprite = &sprites[1];

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	float normalLength = 0.1f;
	bodyA->body->ApplyForce(normalLength * 1000 * worldManifold.normal, worldManifold.points[0], false);
	App->audio->PlayFx(App->scene_intro->fx[FX_BUMPER]);
}

Bumper::Bumper()
{
	sprites = new SDL_Rect[2];
	sprites[0] = { 0,0,41,41 };
	sprites[1] = { 41,0,41,41 };
	current_sprite = &sprites[0];
	score = 100;
}

