#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Interactable.h"

class PhysBody;
class b2MouseJoint;

#define START_POSITION { PIXEL_TO_METERS(449), PIXEL_TO_METERS(625) }

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB, b2Contact* contact);
	
	void CreateBigbumpers(int x, int y, int w, int h);
	void CreateStoneBlock(int x, int y, int w, int h);
	void CreateFruit(int x, int y, int w, int h);
	void CreateBumper(int x, int y, int radius);
	void CreateWheel(int x, int y);
	void LoseLife();
	void BlitScene();
	void ManageInputs();
	void GameOver();

public:
	PhysBody* ball_phys;
	PhysBody* background_phys[18];
	PhysBody* spring_phys;
	PhysBody* flippers[5];
	PhysBody* wheel_phys;
	PhysBody* extra_balls[6];
	PhysBody* death_triggers[2];

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
	SDL_Texture* wheel;
	SDL_Texture* bigbumper;
	SDL_Texture* extra_ball;
	SDL_Texture* game_over_text;

	int lives = 3;
	int tilts = 3;
	bool restart = false;
	bool game_over = false;
};
