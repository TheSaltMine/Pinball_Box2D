#pragma once
#include "Interactable.h"
class StoneBlock :
	public Interactable
{
public:
	StoneBlock();
	~StoneBlock();

	unsigned int hits = 0;
	SDL_Rect* GetSprite()
	{
		return current_sprite;
	}

	void Hit();
	void Restart();

};