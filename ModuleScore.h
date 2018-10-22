#pragma once
#include "Module.h"

#define MAX_SCORE 999999
#define MAX_DIGITS 6
class ModuleScore : public Module
{
public:
	ModuleScore(Application* app, bool start_enabled = true);
	~ModuleScore();

	SDL_Texture* font;
	SDL_Texture* lives_font;
	SDL_Texture* extra_font;

	SDL_Rect number_rects[10];
	SDL_Rect extra_number_rects[10];
	SDL_Rect lives_rects[4];
	int score;
	int digit_score[MAX_DIGITS] = {-1,-1,-1,-1,-1,0};
	int previous_score;
	int prev_digit_score[MAX_DIGITS] = { -1,-1,-1,-1,-1,0 };
	int high_score;
	int high_digit_score[MAX_DIGITS] = { -1,-1,-1,-1,-1,0 };

	bool Start();
	update_status Update();
	bool CleanUp();

	void IncreaseScore(int points);
	void Finished();
};

