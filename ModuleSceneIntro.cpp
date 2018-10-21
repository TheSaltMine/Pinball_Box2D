#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "StoneBlock.h"
#include "Fruit.h"
#include "Bumper.h"
#include "ModuleSceneIntro.h"

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
	fruit = App->textures->Load("pinball/fruits.png");
	bumper = App->textures->Load("pinball/bumper.png");

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


	AddStoneBlocks();
	AddFruits();
	AddBumpers();

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
	//deactivate or activate interactables
	p2List_item<Interactable*>* interactable = interactables.start;
	while (interactable != NULL)
	{
		if (!interactable->data->active && interactable->data->phys->body->IsActive()) interactable->data->phys->body->SetActive(false);
		else if (interactable->data->active && !interactable->data->phys->body->IsActive()) interactable->data->phys->body->SetActive(true);
		interactable = interactable->next;
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

	interactable = interactables.start;
	while (interactable != NULL)
	{
		interactable->data->phys->GetPosition(x, y);
		switch (interactable->data->phys->type)
		{
			case STONE_BLOCK:
			App->renderer->Blit(stone_block, x, y, interactable->data->GetSprite());
			break;
			case FRUIT:
				App->renderer->Blit(fruit, x, y, interactable->data->GetSprite());
			break;
			case BUMPER:
				App->renderer->Blit(bumper, x, y, interactable->data->GetSprite());
			break;
		}
		interactable = interactable->next;
	}

	flippers[0]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[0]->GetRotation());
	flippers[1]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[1]->GetRotation(), true);

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
	if (bodyB->type != BACKGROUND)
	{
		p2List_item<Interactable*>* interactable = interactables.start;
		while (interactable != NULL)
		{
			if (interactable->data->phys == bodyB) 
			{
				interactable->data->Hit();
				break;
			}
			interactable = interactable->next;
		}
	}
}

void ModuleSceneIntro::AddStoneBlocks()
{
	PhysBody* body;

	body = App->physics->CreateRectangle(40, 505, 80, 21, true);
	body->type = STONE_BLOCK;
	StoneBlock* block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(100, 525, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(40, 525, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(362, 610, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(297, 245, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(218, 245, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(138, 245, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(915, 181, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(861, 548, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

	body = App->physics->CreateRectangle(901, 569, 80, 21, true);
	body->type = STONE_BLOCK;
	block = new StoneBlock();
	block->phys = body;
	interactables.add(block);

}

void ModuleSceneIntro::AddFruits()
{
	PhysBody* body;
	body = App->physics->CreateRectangleSensor(200, 700, 22, 18, true);
	body->type = FRUIT;
	Fruit* fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

	body = App->physics->CreateRectangleSensor(100, 525, 22, 18, true);
	body->type = FRUIT;
	fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

	body = App->physics->CreateRectangleSensor(40, 525, 22, 18, true);
	body->type = FRUIT;
	fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

	body = App->physics->CreateRectangleSensor(362, 610, 22, 18, true);
	body->type = FRUIT;
	fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

	body = App->physics->CreateRectangleSensor(297, 245, 22, 18, true);
	body->type = FRUIT;
	fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

	body = App->physics->CreateRectangleSensor(218, 245, 22, 18, true);
	body->type = FRUIT;
	fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);

}

void ModuleSceneIntro::AddBumpers()
{
	PhysBody* body;
	body = App->physics->CreateCircle(300, 520, 21, true);
	body->type = BUMPER;
	Bumper* bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

	body = App->physics->CreateCircle(235, 600, 21, true);
	body->type = BUMPER;
	bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

	body = App->physics->CreateCircle(200, 520, 21, true);
	body->type = BUMPER;
	bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

	body = App->physics->CreateCircle(210, 330, 21, true);
	body->type = BUMPER;
	bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

	body = App->physics->CreateCircle(400, 150, 21, true);
	body->type = BUMPER;
	bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);
}
