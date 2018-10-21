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

struct Bumper
{
	SDL_Rect sprites[2];
	SDL_Rect* current_sprite = nullptr;
	PhysBody* phys = nullptr;
	bool active = false;
	int time = 0;

	Bumper();
	SDL_Rect* GetSprite()
	{
		if (!active)
		{
			return current_sprite;
		}else if(time > 20 && active)
		{
			time = 0;
			active = false;
			return current_sprite = &sprites[0];
		}
		else
		{
			time++;
			return current_sprite;
		}
	}
	void Hit();
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
	Bumper bumpers[5];

	b2MouseJoint* mouse_joint;

	SDL_Texture* ball;
	SDL_Texture* background;
	SDL_Texture* spring;
	SDL_Texture* flipper;
	SDL_Texture* stone_block;
	SDL_Texture* background_image;
	SDL_Texture* bumper;
};
