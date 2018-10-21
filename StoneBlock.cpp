#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "StoneBlock.h"


StoneBlock::StoneBlock()
{
	sprites = new SDL_Rect[4];
	sprites[0] = { 0,0,80,21 };
	sprites[1] = { 0,20,80,21 };
	sprites[2] = { 0,40,80,21 };
	sprites[3] = { 0,61,80,21 };
	current_sprite = &sprites[hits];
}
StoneBlock::~StoneBlock()
{
}
void StoneBlock::Hit(b2Contact* contact, PhysBody* bodyA)
{
	hits++;
	if (hits > 2)
	{
		hits = 3;
		active = false;
	}
	current_sprite = &sprites[hits];
}

void StoneBlock::Restart()
{
	active = true;
	hits = 0;
	current_sprite = &sprites[hits];
}
