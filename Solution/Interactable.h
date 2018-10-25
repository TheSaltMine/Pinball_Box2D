#ifndef __INTERACTABLE_H__
#define __INTERACTABLE_H__

class Interactable
{
public:
	Interactable() {};
	~Interactable() {};

	virtual void Hit(b2Contact* contact, PhysBody* bodyA) {};
	virtual void Restart() {};
	virtual SDL_Rect* GetSprite() { return nullptr; };

	bool flip;
	bool active = true;
	SDL_Rect* sprites;
	PhysBody* phys = nullptr;
	SDL_Rect* current_sprite = nullptr;
	int score = 0;
	unsigned int fx;
	int group = 0;
};

#endif