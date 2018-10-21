#include "ModuleRender.h"
#include "Fruit.h"


Fruit::~Fruit()
{
}

Fruit::Fruit()
{
	sprites = new SDL_Rect[4];
	int sprite = rand() % 4;
	sprites[0] = { 0,0,22,18 };
	sprites[1] = { 23,0,21,21 };
	sprites[2] = { 0,21,18,22 };
	sprites[3] = { 23,22,15,22 };

	current_sprite = &sprites[sprite];
}

void Fruit::Restart()
{

}

void Fruit::Hit()
{
	active = false;
	doing_anim = true;
}

SDL_Rect* Fruit::GetSprite()
{
	if (doing_anim)
	{

	}
	return current_sprite;
}
