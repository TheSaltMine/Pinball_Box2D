#include "Application.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleScore.h"


ModuleScore::ModuleScore(bool start_enabled): Module(start_enabled)
{
}

ModuleScore::~ModuleScore()
{
}

bool ModuleScore::Start()
{
	number_rects[0] = {0,0,8,21};
	number_rects[1] = {8,0,4,20};
	number_rects[2] = {12,0,10,21};
	number_rects[3] = {22,0,11,21};
	number_rects[4] = {33,0,10,23};
	number_rects[5] = {43,0,10,25};
	number_rects[6] = {53,0,7,29};
	number_rects[7] = {60,0,12,33};
	number_rects[8] = {72,0,7,26};
	number_rects[9] = {79,0,8,36};

	extra_number_rects[0] = { 0,0,8,10 };
	extra_number_rects[1] = { 10,0,8,10 };
	extra_number_rects[2] = { 19,0,9,10 };
	extra_number_rects[3] = { 29,0,8,10 };
	extra_number_rects[4] = { 39,0,8,10 };
	extra_number_rects[5] = { 49,0,8,10 };
	extra_number_rects[6] = { 59,0,8,10 };
	extra_number_rects[7] = { 69,0,8,10 };
	extra_number_rects[8] = { 79,0,8,10 };
	extra_number_rects[9] = { 89,0,8,10 };

	lives_rects[0] = {0,0,12,13};
	lives_rects[1] = {12,0,8,14};
	lives_rects[2] = {20,0,10,14};
	lives_rects[3] = {30,0,10,14};


	font = App->textures->Load("pinball/textures/score_font.png");
	lives_font = App->textures->Load("pinball/textures/lives_font.png");
	extra_font = App->textures->Load("pinball/textures/extra_score_font.png");
	return true;
}

update_status ModuleScore::Update()
{
	if (App->scene_intro->state != START_MENU)
	{
		// blit score
		int current_x = 995;
		int current_y = 63;
		int prev_x = 1002;
		int prev_y = 247;
		int high_x = 1002;
		int high_y = 189;
		for (int i = 5; i > 0; i--)
		{
			if (digit_score[i] != -1)
			{
				App->renderer->Blit(font, current_x, current_y, &number_rects[digit_score[i]]);
				current_x -= 12;
			}
			if (prev_digit_score[i] != -1)
			{
				App->renderer->Blit(extra_font, prev_x, prev_y, &extra_number_rects[digit_score[i]]);
				prev_x -= 14;
			}
			if (high_digit_score[i] != -1)
			{
				App->renderer->Blit(extra_font, high_x, high_y, &extra_number_rects[digit_score[i]]);
				high_x -= 14;
			}
		}

		App->renderer->Blit(lives_font, 997, 482, &lives_rects[App->scene_intro->lives]);
		App->renderer->Blit(lives_font, 997, 526, &lives_rects[App->scene_intro->tilts]);

	}	

	return UPDATE_CONTINUE;
}

bool ModuleScore::CleanUp()
{
	return true;
}

void ModuleScore::IncreaseScore(int points)
{
	score += points;
	if (score > MAX_SCORE) score = MAX_SCORE;
	if (score > high_score) high_score = score;

	int index = 5;
	int aux_score = score;
	while (aux_score > 0)
	{
		int digit = aux_score % 10;
		aux_score /= 10;
		digit_score[index] = digit;
		index--;
	}

	index = 5;
	aux_score = high_score;
	while (aux_score > 0)
	{
		int digit = aux_score % 10;
		aux_score /= 10;
		high_digit_score[index] = digit;
		index--;
	}
}

void ModuleScore::Finished()
{
	previous_score = score;

	int index = 5;
	int aux_score = previous_score;
	while (aux_score > 0)
	{
		int digit = aux_score % 10;
		aux_score /= 10;
		prev_digit_score[index] = digit;
		index--;
	}

	score = 0;
	digit_score[0] = -1;
	digit_score[1] = -1;
	digit_score[2] = -1;
	digit_score[3] = -1;
	digit_score[4] = -1;
	digit_score[5] = 0;
}