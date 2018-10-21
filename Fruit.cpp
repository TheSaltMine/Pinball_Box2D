#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "Fruit.h"


Fruit::~Fruit()
{
}

Fruit::Fruit()
{
	sprites = new SDL_Rect[5];
	int sprite = rand() % 4;
	sprites[0] = { 0,0,22,18 };
	sprites[1] = { 23,0,21,21 };
	sprites[2] = { 0,21,20,22 };
	sprites[3] = { 22,22,18,22 };
	sprites[4] = { 0,44,18,22 };

	current_sprite = &sprites[sprite];
}

void Fruit::Restart()
{
	active = true;
	current_sprite = &sprites[rand() % 4];
	collected = false;
	timer = 0.0f;
}

void Fruit::Hit()
{
	collected = true;
	phys->body->SetLinearVelocity({ 0.0f, PIXEL_TO_METERS(-50.0f) });
}

SDL_Rect* Fruit::GetSprite()
{
	if (collected && timer < 50.0f)
	{
		timer++;

		if (timer >= 50.0f)
		{
			active = false;
			current_sprite = &sprites[4];
		}
	}
	return current_sprite;
}
