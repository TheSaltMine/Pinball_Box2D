#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = ball = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/background.png");
	ball = App->textures->Load("pinball/ball.png");
	spring = App->textures->Load("pinball/spring.png");
	flipper = App->textures->Load("pinball/flipper_test.png");
	stone_block = App->textures->Load("pinball/stone_block.png");
	background_image = App->textures->Load("pinball/background_image.png");
	bumper = App->textures->Load("pinball/bumper.png");
	bumper_light = App->textures->Load("pinball/bumper_light.png");

	#include "BackgroundVertex.h"
	background_phys[0] = App->physics->CreateChain(0, 0, background_vertex, 204, true);
	background_phys[1] = App->physics->CreateChain(0, 0, background_piece1, 62, true);
	background_phys[2] = App->physics->CreateChain(0, 0, background_piece2, 24, true);
	background_phys[3] = App->physics->CreateChain(0, 0, background_piece3, 28, true);
	background_phys[4] = App->physics->CreateChain(0, 0, background_piece4, 40, true);
	background_phys[5] = App->physics->CreateChain(0, 0, background_piece5, 52, true);
	background_phys[6] = App->physics->CreateChain(0, 0, background_piece6, 42, true);
	background_phys[7] = App->physics->CreateChain(0, 0, background_piece7, 14, true);
	background_phys[8] = App->physics->CreateChain(0, 0, background_piece8, 36, true);
	background_phys[9] = App->physics->CreateChain(0, 0, background_piece9, 18, true);
	background_phys[10] = App->physics->CreateChain(0, 0, background_piece10, 8, true);
	background_phys[11] = App->physics->CreateChain(0, 0, background_piece11, 8, true);
	background_phys[12] = App->physics->CreateChain(0, 0, background_piece12, 8, true);
	background_phys[13] = App->physics->CreateChain(0, 0, background_piece13, 10, true);
	background_phys[14] = App->physics->CreateChain(0, 0, background_piece14, 10, true);
	background_phys[15] = App->physics->CreateChain(0, 0, background_piece15, 8, true);
	background_phys[16] = App->physics->CreateChain(0, 0, background_piece16, 10, true);
	background_phys[17] = App->physics->CreateChain(0, 0, background_piece17, 12, true);

	ball_phys = App->physics->CreateCircle(449, 625, 8);
	ball_phys->body->SetBullet(true);
	ball_phys->listener = this;
	spring_phys = App->physics->CreateRectangle(449, 800, 21, 26);
	
	flippers[0] = App->physics->CreateFlipper(129, 894);
	flippers[1] = App->physics->CreateFlipper(220, 895, true);

	stone_blocks[0].phys = App->physics->CreateRectangle(40, 505, 80, 21, true);
	stone_blocks[0].phys->type = STONE_BLOCK;
	stone_blocks[1].phys = App->physics->CreateRectangle(100, 525, 80, 21, true);
	stone_blocks[1].phys->type = STONE_BLOCK;
	stone_blocks[2].phys = App->physics->CreateRectangle(40, 525, 80, 21, true);
	stone_blocks[2].phys->type = STONE_BLOCK;
	stone_blocks[3].phys = App->physics->CreateRectangle(362, 610, 80, 21, true);
	stone_blocks[3].phys->type = STONE_BLOCK;
	stone_blocks[4].phys = App->physics->CreateRectangle(297, 245, 80, 21, true);
	stone_blocks[4].phys->type = STONE_BLOCK;
	stone_blocks[5].phys = App->physics->CreateRectangle(218, 245, 80, 21, true);
	stone_blocks[5].phys->type = STONE_BLOCK;
	stone_blocks[6].phys = App->physics->CreateRectangle(138, 245, 80, 21, true);
	stone_blocks[6].phys->type = STONE_BLOCK;
	stone_blocks[7].phys = App->physics->CreateRectangle(915, 181, 80, 21, true);
	stone_blocks[7].phys->type = STONE_BLOCK;
	stone_blocks[8].phys = App->physics->CreateRectangle(861, 548, 80, 21, true);
	stone_blocks[8].phys->type = STONE_BLOCK;
	stone_blocks[9].phys = App->physics->CreateRectangle(901, 569, 80, 21, true);
	stone_blocks[9].phys->type = STONE_BLOCK;

	bumpers[0] = App->physics->CreateCircle(250, 530, 21, true, this);

	//joints
	b2MouseJointDef def;
	def.bodyA = App->physics->ground;
	def.bodyB = spring_phys->body;
	def.target = { PIXEL_TO_METERS(449), PIXEL_TO_METERS(800) };
	def.dampingRatio = 3.0f;
	def.maxForce = 1000.0f * spring_phys->body->GetMass();
	mouse_joint = (b2MouseJoint*)App->physics->world->CreateJoint(&def);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//deactivate or activate stone_blocks
	for (int i = 0; i < 10; i++)
	{
		if (!stone_blocks[i].active && stone_blocks[i].phys->body->IsActive()) stone_blocks[i].phys->body->SetActive(false);
		else if (stone_blocks[i].active && !stone_blocks[i].phys->body->IsActive()) stone_blocks[i].phys->body->SetActive(true);
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		mouse_joint->SetTarget({ PIXEL_TO_METERS(449), PIXEL_TO_METERS(900) });
		mouse_joint->SetFrequency(1.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		mouse_joint->SetTarget({ PIXEL_TO_METERS(449), PIXEL_TO_METERS(800) });
		mouse_joint->SetFrequency(20.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flippers[1]->body->ApplyTorque(10000.0f, true);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flippers[0]->body->ApplyTorque(-10000.0f, true);
	}

	App->renderer->Blit(background_image, 0, 0);
	int x, y;

	for (int i = 0; i < 10; i++)
	{
		stone_blocks[i].phys->GetPosition(x, y);
		App->renderer->Blit(stone_block, x, y, stone_blocks[i].current_sprite);
	}

	flippers[0]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[0]->GetRotation());
	flippers[1]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[1]->GetRotation(), true);

	bumpers[0]->GetPosition(x, y);
	App->renderer->Blit(bumper, x, y);

	//Draw background

	for (int i = 0; i < 18; i++)
	{
		background_phys[i]->GetPosition(x, y);
		App->renderer->Blit(background, x, y);
	}

	ball_phys->GetPosition(x, y);
	App->renderer->Blit(ball, x, y, NULL, 1.0F, ball_phys->GetRotation());
	spring_phys->GetPosition(x, y);
	App->renderer->Blit(spring, x, y);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB->type == STONE_BLOCK)
	{
		for (int i = 0; i < 10; i++)
		{
			if (stone_blocks[i].phys == bodyB) {
				stone_blocks[i].Hit();
				break;
			}
		}
	}
}


void StoneBlock::Hit()
{
	hits++;
	if (hits > 2)
	{
		hits = 3;
		active = false;
	}
	current_sprite = &sprites[hits];
}

void StoneBlock::Restart()
{
	active = true;
	hits = 0;
	current_sprite = &sprites[hits];
}

StoneBlock::StoneBlock()
{
	sprites[0] = { 0,0,80,21 };
	sprites[1] = { 0,20,80,21 };
	sprites[2] = { 0,40,80,21 };
	sprites[3] = { 0,61,80,21 };
	current_sprite = &sprites[hits];
}
