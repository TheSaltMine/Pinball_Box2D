#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "StoneBlock.h"


StoneBlock::StoneBlock()
{
	sprites = new SDL_Rect[4];
	sprites[0] = { 0,0,80,21 };
	sprites[1] = { 0,20,80,21 };
	sprites[2] = { 0,40,80,21 };
	sprites[3] = { 0,61,80,21 };
	current_sprite = &sprites[hits];
	score = 100;
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
		score = 500;
	}
	current_sprite = &sprites[hits];
	App->audio->PlayFx(App->scene_intro->fx[FX_STONE_BLOCK]);
}

void StoneBlock::Restart()
{
	active = true;
	hits = 0;
	score = 100;
	current_sprite = &sprites[hits];
}
