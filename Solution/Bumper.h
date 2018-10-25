#pragma once
#include "Interactable.h"
class Bumper :
	public Interactable
{
public:
	Bumper();
	~Bumper();
	int time = 0;
	bool hit = false;

	SDL_Rect* GetSprite();
	void Hit(b2Contact* contact, PhysBody* bodyA);
};

