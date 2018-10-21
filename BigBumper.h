#pragma once
#include "Interactable.h"
class BigBumper :
	public Interactable
{
public:
	BigBumper();
	~BigBumper();
	int time = 0;
	bool hit = false;

	SDL_Rect* GetSprite();
	void Hit(b2Contact* contact, PhysBody* bodyA);
};
