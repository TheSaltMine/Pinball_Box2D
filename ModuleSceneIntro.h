#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2MouseJoint;

struct StoneBlock
{
	SDL_Rect sprites[4];
	SDL_Rect* current_sprite;
	PhysBody* phys = nullptr;
	unsigned int hits = 0;
	bool active = true;

	StoneBlock();
	SDL_Rect* GetSprite()
	{
		current_sprite;
	}

	void Hit();
	void Restart();
	
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	PhysBody* ball_phys;
	PhysBody* background_phys[18];
	PhysBody* spring_phys;
	PhysBody* flippers[5];
	StoneBlock stone_blocks[10];

	b2MouseJoint* mouse_joint;

	SDL_Texture* ball;
	SDL_Texture* background;
	SDL_Texture* spring;
	SDL_Texture* flipper;
	SDL_Texture* stone_block;
	SDL_Texture* background_image;
};
