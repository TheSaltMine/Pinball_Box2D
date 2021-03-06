#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Interactable.h"

class PhysBody;
class b2MouseJoint;

#define START_POSITION { PIXEL_TO_METERS(449), PIXEL_TO_METERS(850) }

enum GameState
{
	PLAYING,
	RESTART,
	GAME_OVER,
	START_MENU,
	BONUSES
};

enum FX 
{
	FX_BIGBUMPER,
	FX_BONUS,
	FX_BUMPER,
	FX_FLIPPER,
	FX_FRUIT,
	FX_GAME_OVER,
	FX_LAUNCHER,
	FX_MUSHROOM,
	FX_START,
	FX_STONE_BLOCK
};

enum Groups
{
	OFF,
	ON,
	BONUS
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB, b2Contact* contact);
	
	void CreateBigbumpers(int x, int y, int w, int h, bool flip, int x2, int y2, int w2, int h2);
	void CreateStoneBlock(int x, int y, int w, int h);
	void CreateFruit(int x, int y, int w, int h);
	void CreateBumper(int x, int y, int radius);
	void CreateMushroom(int x, int y, int radius,int rotation, int group);
	void CreateWheel(int x, int y);
	Groups chackBonus(Interactable* object, Groups g);
	void LoseLife();
	void BlitScene();
	void ManageInputs();
	Groups DataBonus(Groups g);
	void GameOver();

public:
	PhysBody* ball_phys;
	PhysBody* background_phys[18];
	PhysBody* launcher_phys;
	PhysBody* flippers[5];
	PhysBody* wheel_phys;
	PhysBody* extra_balls[6];
	PhysBody* death_triggers[2];

	p2List<Interactable*> interactables;

	b2MouseJoint* mouse_joint;

	SDL_Texture* ball;
	SDL_Texture* background;
	SDL_Texture* launcher;
	SDL_Texture* flipper;
	SDL_Texture* stone_block;
	SDL_Texture* background_image;
	SDL_Texture* fruit;
	SDL_Texture* bumper;
	SDL_Texture* wheel;
	SDL_Texture* bigbumper;
	SDL_Texture* extra_ball;
	SDL_Texture* game_over_text;
	SDL_Texture* start_menu;
	SDL_Texture* bonus;
	SDL_Texture* mushroom;

	int lives = 3;
	int tilts = 3;
	Groups G1 = ON;
	Groups G2 = ON;
	Groups G3 = ON;
	Groups G4 = ON;
	float timer = 0;
	unsigned int fx[10];
	char* music_path = "pinball/music/music.ogg";
	GameState state = START_MENU;
};
