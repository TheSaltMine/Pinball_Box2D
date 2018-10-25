#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Mushroom.h"



Mushroom::~Mushroom()
{
}

SDL_Rect * Mushroom::GetSprite()
{
	return current_sprite;
}

void Mushroom::Hit(b2Contact* contact, PhysBody* bodyA)
{
	active = false;
	current_sprite = &sprites[1];
	/*b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	
	//bodyA->body->SetAngularVelocity(30);
	bodyA->body->ApplyForce(200 * worldManifold.normal, worldManifold.points[0],true);*/
	App->audio->PlayFx(App->scene_intro->fx[FX_MUSHROOM]);
}

void Mushroom::Restart()
{
	active = true;
	current_sprite = &sprites[0];
	phys->body->SetLinearVelocity({ 0.0f, 0.0f });
	phys->body->SetTransform(start_position, start_rotation);
}

Mushroom::Mushroom()
{
	sprites = new SDL_Rect[2];
	sprites[0] = {0,0,20,19};
	sprites[1] = { 20,0,20,19 };
	current_sprite = &sprites[0];
	score = 100;
}