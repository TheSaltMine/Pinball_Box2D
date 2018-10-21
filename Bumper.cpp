#include "ModuleRender.h"
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

void Bumper::Hit()
{
	hit = true;
	current_sprite = &sprites[1];
}

Bumper::Bumper()
{
	sprites = new SDL_Rect[2];
	sprites[0] = { 0,0,41,41 };
	sprites[1] = { 41,0,41,41 };
	current_sprite = &sprites[0];
}

