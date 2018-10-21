#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Interactable.h"

class PhysBody;
class b2MouseJoint;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void CreateStoneBlock(int x, int y, int w, int h);
	void CreateFruit(int x, int y, int w, int h);
	void CreateBumper(int x, int y, int radius);

public:
	PhysBody* ball_phys;
	PhysBody* background_phys[18];
	PhysBody* spring_phys;
	PhysBody* flippers[5];

	p2List<Interactable*> interactables;

	b2MouseJoint* mouse_joint;

	SDL_Texture* ball;
	SDL_Texture* background;
	SDL_Texture* spring;
	SDL_Texture* flipper;
	SDL_Texture* stone_block;
	SDL_Texture* background_image;
	SDL_Texture* fruit;
	SDL_Texture* bumper;

};
