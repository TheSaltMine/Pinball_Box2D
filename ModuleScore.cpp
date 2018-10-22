#include "Application.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleScore.h"


ModuleScore::ModuleScore(Application* app, bool start_enabled): Module(app, start_enabled)
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

	lives_rects[0] = {0,0,12,13};
	lives_rects[1] = {12,0,8,14};
	lives_rects[2] = {20,0,10,14};
	lives_rects[3] = {30,0,10,14};


	font = App->textures->Load("pinball/score_font.png");
	lives_font = App->textures->Load("pinball/lives_font.png");
	return true;
}

update_status ModuleScore::Update()
{
	// blit score
	int x = 995;
	int y = 63;
	for (int i = 5; i > 0; i--)
	{
		if (digit_score[i] != -1)
		{
			App->renderer->Blit(font, x, y, &number_rects[digit_score[i]]);
			x -= 12;
		}
		else break;
	}

	App->renderer->Blit(lives_font, 997, 482, &lives_rects[App->scene_intro->lives]);
	App->renderer->Blit(lives_font, 997, 526, &lives_rects[App->scene_intro->tilts]);


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

	int index = 5;
	int aux_score = score;
	while (aux_score > 0)
	{
		int digit = aux_score % 10;
		aux_score /= 10;
		digit_score[index] = digit;
		index--;
	}
}
