#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "BigBumper.h"



BigBumper::~BigBumper()
{
}

SDL_Rect * BigBumper::GetSprite()
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

void BigBumper::Hit(b2Contact* contact, PhysBody* bodyA)
{
	hit = true;
	current_sprite = &sprites[1];


	/*b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	bodyA->body->SetLinearVelocity({0.0f, 0.0f});
	//bodyA->body->SetAngularVelocity(30);
	bodyA->body->ApplyForce(200 * worldManifold.normal, worldManifold.points[0], true);*/
	App->audio->PlayFx(App->scene_intro->fx[FX_BIGBUMPER]);
}

BigBumper::BigBumper()
{
	sprites = new SDL_Rect[2];
	sprites[0] = { 0,0,41,123 };
	sprites[1] = { 41,0,50,123 };
	current_sprite = &sprites[0];
}