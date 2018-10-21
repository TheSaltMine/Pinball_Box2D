#pragma once
#include "Interactable.h"
class Fruit :
	public Interactable
{
public:
	Fruit();
	~Fruit();
	void Restart();
	void Hit();
	SDL_Rect* GetSprite();
	bool collected = false;
	float timer = 0.0f;
};