#pragma once
#include "Interactable.h"
class Fruit :
	public Interactable
{
public:
	Fruit();
	~Fruit();
	void Restart();
	void Hit(b2Contact* contact, PhysBody* bodyA);
	SDL_Rect* GetSprite();
	bool collected = false;
	b2Vec2 start_position;
	float timer = 0.0f;
};