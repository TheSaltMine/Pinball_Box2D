#pragma once
#include "Interactable.h"
class Mushroom :
	public Interactable
{
public:
	Mushroom();
	~Mushroom();
	int time = 0;
	bool hit = false;
	float32 start_rotation;

	SDL_Rect* GetSprite();
	void Hit(b2Contact* contact, PhysBody* bodyA);
	b2Vec2 start_position;
	void Restart();
};