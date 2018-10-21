#include "ModuleRender.h"
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

void BigBumper::Hit()
{
	hit = true;
	current_sprite = &sprites[1];
}

BigBumper::BigBumper()
{
	sprites = new SDL_Rect[2];
	sprites[0] = { 0,0,41,123 };
	sprites[1] = { 41,0,50,123 };
	current_sprite = &sprites[0];
}