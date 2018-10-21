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
#include "Wheel.h"
#include "BigBumper.h"
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
	flipper = App->textures->Load("pinball/flipper.png");
	stone_block = App->textures->Load("pinball/stone_block.png");
	background_image = App->textures->Load("pinball/background_image.png");
	fruit = App->textures->Load("pinball/fruits.png");
	bumper = App->textures->Load("pinball/bumper.png");
	wheel = App->textures->Load("pinball/wheel.png");
    bigbumper = App->textures->Load("pinball/bigbumper.png");

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



	/*AddStoneBlocks();
	AddFruits();
	AddBumpers();*/
	AddBigbumpers();

	//create stoneblocks
	CreateStoneBlock(40, 505, 80, 21);
	CreateStoneBlock(100, 525, 80, 21);
	CreateStoneBlock(40, 525, 80, 21);
	CreateStoneBlock(362, 610, 80, 21);
	CreateStoneBlock(297, 245, 80, 21);
	CreateStoneBlock(218, 245, 80, 21);
	CreateStoneBlock(138, 245, 80, 21);
	CreateStoneBlock(915, 181, 80, 21);
	CreateStoneBlock(861, 548, 80, 21);
	CreateStoneBlock(901, 569, 80, 21);
	//create fruits
	CreateFruit(216, 700, 22, 18);//bottom left
	CreateFruit(256, 718, 22, 18);
	CreateFruit(178, 718, 22, 18);
	CreateFruit(134, 740, 22, 18);
	CreateFruit(300, 740, 22, 18);
	CreateFruit(72, 390, 22, 18);//top left
	CreateFruit(72, 354, 22, 18);
	CreateFruit(72, 313, 22, 18);
	CreateFruit(72, 276, 22, 18);
	CreateFruit(72, 239, 22, 18);
	CreateFruit(72, 203, 22, 18);
	CreateFruit(390, 230, 22, 18);//top left next to wheel
	CreateFruit(428, 230, 22, 18);
	CreateFruit(468, 230, 22, 18);
	CreateFruit(872, 478, 22, 18);//mid right
	CreateFruit(872, 432, 22, 18);
	CreateFruit(872, 386, 22, 18);
	CreateFruit(872, 340, 22, 18);
	CreateFruit(872, 294, 22, 18);
	CreateFruit(770, 30, 22, 18);//top right
	CreateFruit(832, 47, 22, 18);
	CreateFruit(868, 80, 22, 18);
	CreateFruit(888, 147, 22, 18);
	CreateFruit(686, 700, 22, 18);//bottom right
	CreateFruit(726, 718, 22, 18);
	CreateFruit(648, 718, 22, 18);
	CreateFruit(604, 740, 22, 18);
	CreateFruit(770, 740, 22, 18);
	//Create Bumpers
	CreateBumper(300, 520, 21);
	CreateBumper(235, 600, 21);
	CreateBumper(200, 520, 21);
	CreateBumper(210, 330, 21);
	CreateBumper(300, 520, 21);
	CreateBumper(300, 520, 21);
	CreateBumper(400, 150, 21);
	//Create wheels
	CreateWheel(125, 74);
	CreateWheel(520, 147);

	CreateBumper(770, 170, 21);
	CreateBumper(590, 470, 21);
	CreateBumper(750, 350, 21);

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
			case WHEEL:
				App->renderer->Blit(wheel, x, y, NULL, 1.0f, interactable->data->phys->GetRotation(), false, false, PIXEL_TO_METERS(76), PIXEL_TO_METERS(76));
			break;
			case BIGBUMPER:
				App->renderer->Blit(bigbumper, x, y, interactable->data->GetSprite());
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

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB, b2Contact* contact)
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
	if (bodyB->type == BUMPER)
	{
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		float normalLength = 0.1f;
		bodyA->body->ApplyForce(normalLength*1000 * worldManifold.normal, worldManifold.points[0], false);
	}
}

void ModuleSceneIntro::CreateStoneBlock(int x, int y, int w, int h)
{
	PhysBody* body;
	body = App->physics->CreateRectangle(x, y, w, h, b2_staticBody);
	body->type = STONE_BLOCK;
	StoneBlock* block = new StoneBlock();
	block->phys = body;
	interactables.add(block);
}

void ModuleSceneIntro::CreateFruit(int x, int y, int w, int h)
{
	PhysBody* body;
	body = App->physics->CreateRectangleSensor(x, y, w, h, b2_kinematicBody);
	body->type = FRUIT;
	Fruit* fruit = new Fruit();
	fruit->phys = body;
	interactables.add(fruit);
}

void ModuleSceneIntro::CreateBumper(int x, int y, int radius)
{
	PhysBody* body;
	body = App->physics->CreateCircle(x, y, radius, true);
	body->type = BUMPER;
	Bumper* bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

}

void ModuleSceneIntro::AddBigbumpers()
{
	PhysBody* body;
	body = App->physics->CreateRectangle(100, 770, 41, 123, b2_staticBody);
	body->type = BIGBUMPER;
	BigBumper* bigbumper = new BigBumper();
	bigbumper->phys = body;
	interactables.add(bigbumper);
}

void ModuleSceneIntro::CreateWheel(int x, int y)
{
	int wheel_vertex[132] = {
		121, 124,
		112, 130,
		102, 135,
		92, 139,
		80, 140,
		67, 139,
		53, 135,
		41, 129,
		32, 124,
		25, 118,
		20, 109,
		13, 96,
		11, 88,
		10, 77,
		11, 65,
		14, 54,
		19, 44,
		24, 35,
		31, 28,
		39, 21,
		51, 15,
		62, 12,
		75, 11,
		87, 12,
		99, 14,
		110, 20,
		119, 27,
		127, 35,
		133, 45,
		140, 58,
		141, 73,
		142, 94,
		151, 94,
		151, 73,
		150, 58,
		149, 51,
		141, 38,
		133, 27,
		125, 18,
		115, 11,
		101, 5,
		86, 1,
		63, 1,
		52, 4,
		42, 8,
		32, 15,
		23, 23,
		15, 31,
		9, 39,
		4, 53,
		2, 66,
		1, 77,
		3, 92,
		7, 107,
		15, 120,
		22, 129,
		34, 138,
		47, 145,
		59, 149,
		70, 151,
		82, 151,
		95, 148,
		107, 144,
		116, 140,
		124, 135,
		128, 128
	};

	b2MassData data;
	data.mass = 36.664001f;
	data.I = 22.52466f;
	data.center = { 0.0f, 0.0f };
	PhysBody* body = App->physics->CreateChain(x, y, wheel_vertex, 132);
	body->body->SetMassData(&data);
	Wheel* w = new Wheel();
	w->phys = body;
	w->phys->type = WHEEL;
	PhysBody* pivot = App->physics->CreateCircle(x + 76, y + 76, 5, true);

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body->body;
	jointDef.bodyB = pivot->body;
	jointDef.localAnchorA = { PIXEL_TO_METERS(76), PIXEL_TO_METERS(76) };
	jointDef.localAnchorB = { 0,0 };
	jointDef.lowerAngle = 0.0F;
	jointDef.upperAngle = 0.0F;
	jointDef.enableLimit = true;
	jointDef.collideConnected = false;
	jointDef.enableMotor = false;
	jointDef.maxMotorTorque = 100.0f;
	jointDef.motorSpeed = 5.0f;
	w->joint = (b2RevoluteJoint*) App->physics->world->CreateJoint(&jointDef);

	interactables.add(w);
}