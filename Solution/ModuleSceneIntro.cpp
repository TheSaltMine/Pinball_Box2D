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
#include "Mushroom.h"
#include "ModuleScore.h"
#include "ModuleSceneIntro.h"
#include <ctime>

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
	background = ball = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	srand(time(0));

	LOG("Loading Intro assets");
	bool ret = true;
	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/textures/background.png");
	ball = App->textures->Load("pinball/textures/ball.png");
	launcher = App->textures->Load("pinball/textures/launcher.png");
	flipper = App->textures->Load("pinball/textures/flipper.png");
	stone_block = App->textures->Load("pinball/textures/stone_block.png");
	background_image = App->textures->Load("pinball/textures/background_image.png");
	fruit = App->textures->Load("pinball/textures/fruits.png");
	bumper = App->textures->Load("pinball/textures/bumper.png");
	wheel = App->textures->Load("pinball/textures/wheel.png");
    bigbumper = App->textures->Load("pinball/textures/bigbumper.png");
	extra_ball = App->textures->Load("pinball/textures/extra_ball.png");
	game_over_text = App->textures->Load("pinball/textures/game_over.png");
	start_menu = App->textures->Load("pinball/textures/start_menu.png");
	mushroom = App->textures->Load("pinball/textures/mushroom.png");
	bonus = App->textures->Load("pinball/textures/bonus.png");

	//load audio
	fx[FX_BIGBUMPER] = App->audio->LoadFx("pinball/fx/fx_bigbumper.wav");
	fx[FX_BONUS] = App->audio->LoadFx("pinball/fx/fx_bonus.wav");
	fx[FX_BUMPER] = App->audio->LoadFx("pinball/fx/fx_bumper.wav");
	fx[FX_FLIPPER] = App->audio->LoadFx("pinball/fx/fx_flipper.wav");
	fx[FX_FRUIT] = App->audio->LoadFx("pinball/fx/fx_fruit.wav");
	fx[FX_GAME_OVER] = App->audio->LoadFx("pinball/fx/fx_game_over.wav");
	fx[FX_LAUNCHER] = App->audio->LoadFx("pinball/fx/fx_launcher.wav");
	fx[FX_MUSHROOM] = App->audio->LoadFx("pinball/fx/fx_shroom.wav");
	fx[FX_START] = App->audio->LoadFx("pinball/fx/fx_startround.wav");
	fx[FX_STONE_BLOCK] = App->audio->LoadFx("pinball/fx/fx_stoneblock.wav");

	App->audio->PlayMusic(music_path);


	#include "BackgroundVertex.h"
	background_phys[0] = App->physics->CreateChain(0, 0, background_vertex, 226, true);
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

	ball_phys = App->physics->CreateCircle(449, 850, 8, b2_dynamicBody, -2);
	ball_phys->body->SetBullet(true);
	ball_phys->listener = this;

	launcher_phys = App->physics->CreateRectangle(449, 935, 21, 26);
	launcher_phys->body->SetFixedRotation(true);
	
	flippers[0] = App->physics->CreateFlipper(129, 896);
	flippers[1] = App->physics->CreateFlipper(220, 896, true);
	flippers[2] = App->physics->CreateFlipper(600, 894);
	flippers[3] = App->physics->CreateFlipper(691, 894, true);
	flippers[4] = App->physics->CreateFlipper(500, 550);

	extra_balls[0] = App->physics->CreateCircle(193, 156, 6);
	extra_balls[0]->listener = this;
	extra_balls[0]->type = EXTRA_BALL;
	extra_balls[1] = App->physics->CreateCircle(193, 156, 6);
	extra_balls[1]->listener = this;
	extra_balls[1]->type = EXTRA_BALL;
	extra_balls[2] = App->physics->CreateCircle(193, 156, 6);
	extra_balls[2]->listener = this;
	extra_balls[2]->type = EXTRA_BALL;
	extra_balls[3] = App->physics->CreateCircle(580, 240, 6);
	extra_balls[3]->listener = this;
	extra_balls[3]->type = EXTRA_BALL;
	extra_balls[4] = App->physics->CreateCircle(580, 240, 6);
	extra_balls[4]->listener = this;
	extra_balls[4]->type = EXTRA_BALL;
	extra_balls[5] = App->physics->CreateCircle(580, 240, 6);
	extra_balls[5]->listener = this;
	extra_balls[5]->type = EXTRA_BALL;

	death_triggers[0] = App->physics->CreateRectangleSensor(210, 980, 229, 35, b2_staticBody);
	death_triggers[0]->type = DEATH;
	death_triggers[1] = App->physics->CreateRectangleSensor(690, 980, 229, 35, b2_staticBody);
	death_triggers[1]->type = DEATH;

	CreateBigbumpers(70, 720, 41, 123, true);
	CreateBigbumpers(320, 720, 41, 123, false);
	CreateBigbumpers(540, 720, 41, 123, true);
	CreateBigbumpers(800, 720, 41, 123, false);

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
	CreateBumper(770, 170, 21);
	CreateBumper(590, 470, 21);
	CreateBumper(750, 350, 21);
	//Create wheels
	CreateWheel(125, 74);
	CreateWheel(520, 147);

	CreateMushroom(360, 650, 8, 89, 1);
	CreateMushroom(377, 665, 8, 89, 1);
	CreateMushroom(394, 680, 8, 89, 1);

	CreateMushroom(267, 445, 8, 10, 2);
	CreateMushroom(227, 445, 8, 10, 2);
	CreateMushroom(187, 445, 8, 10, 2);

	CreateMushroom(37, 625, 8, 25, 3);
	CreateMushroom(20, 645, 8, 25, 3);

	CreateMushroom(825, 338, 8, 40, 4);
	CreateMushroom(826, 390, 8, 40, 4);
	CreateMushroom(827, 450, 8, 40, 4);
	CreateMushroom(828, 510, 8, 40, 4);

	//launcher joint
	b2MouseJointDef def;
	def.bodyA = App->physics->ground;
	def.bodyB = launcher_phys->body;
	def.target = { PIXEL_TO_METERS(449), PIXEL_TO_METERS(935) };
	def.dampingRatio = 1.0f;
	def.maxForce = 10000.0f * launcher_phys->body->GetMass();
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
		if (state == RESTART) interactable->data->Restart();
		if (interactable->data->group == 1)
		{
			G1 = chackBonus(interactable->data, G1);
		}
		else if (interactable->data->group == 2)
		{
			G2 = chackBonus(interactable->data, G2);
		}
		else if (interactable->data->group == 3)
		{
			G3 = chackBonus(interactable->data, G3);
		}
		else if (interactable->data->group == 4)
		{
			G4 = chackBonus(interactable->data, G4);
		}
		interactable = interactable->next;
	}

	G1 = DataBonus(G1);
	G2 = DataBonus(G2);
	G3 = DataBonus(G3);
	G4 = DataBonus(G4);

	if (state == RESTART)
	{
		App->audio->PlayFx(fx[FX_START]);
		//restart balls
		ball_phys->body->SetTransform(START_POSITION, ball_phys->body->GetAngle());
		extra_balls[0]->body->SetTransform({ PIXEL_TO_METERS(193), PIXEL_TO_METERS(156) }, extra_balls[0]->body->GetAngle());
		extra_balls[0]->body->SetLinearVelocity({ 0.0f,0.0f });
		extra_balls[1]->body->SetTransform({ PIXEL_TO_METERS(193), PIXEL_TO_METERS(156) }, extra_balls[1]->body->GetAngle());
		extra_balls[1]->body->SetLinearVelocity({ 0.0f,0.0f });
		extra_balls[2]->body->SetTransform({ PIXEL_TO_METERS(193), PIXEL_TO_METERS(156) }, extra_balls[2]->body->GetAngle());
		extra_balls[2]->body->SetLinearVelocity({ 0.0f,0.0f });
		extra_balls[3]->body->SetTransform({ PIXEL_TO_METERS(580), PIXEL_TO_METERS(240) }, extra_balls[3]->body->GetAngle());
		extra_balls[3]->body->SetLinearVelocity({ 0.0f,0.0f });
		extra_balls[4]->body->SetTransform({ PIXEL_TO_METERS(580), PIXEL_TO_METERS(240) }, extra_balls[4]->body->GetAngle());
		extra_balls[4]->body->SetLinearVelocity({ 0.0f,0.0f });
		extra_balls[5]->body->SetTransform({ PIXEL_TO_METERS(580), PIXEL_TO_METERS(240) }, extra_balls[5]->body->GetAngle());
		extra_balls[5]->body->SetLinearVelocity({ 0.0f,0.0f });

		tilts = 3;

		state = PLAYING;
	}

	ManageInputs();

	BlitScene();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB, b2Contact* contact)
{
	if (bodyB->type != BACKGROUND && bodyB->type != DEATH)
	{
		p2List_item<Interactable*>* interactable = interactables.start;
		while (interactable != NULL)
		{
			if (interactable->data->phys == bodyB) 
			{
				interactable->data->Hit(contact, bodyA);
				App->score->IncreaseScore(interactable->data->score);
				break;
			}
			interactable = interactable->next;
		}
	}
	else if (bodyB->type == DEATH)
	{
		if (bodyA->type == BALL) LoseLife();
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
	fruit->start_position = fruit->phys->body->GetPosition();
	interactables.add(fruit);
}

void ModuleSceneIntro::CreateBumper(int x, int y, int radius)
{
	PhysBody* body;
	body = App->physics->CreateCircle(x, y, radius, b2_kinematicBody);
	b2Fixture* f = body->body->GetFixtureList();
	f->SetRestitution(2.0f);
	body->type = BUMPER;
	Bumper* bumper = new Bumper();
	bumper->phys = body;
	interactables.add(bumper);

}

void ModuleSceneIntro::CreateMushroom(int x, int y, int radius, int rotation, int group)
{
	PhysBody* body;
	body = App->physics->CreateCircle(x, y, radius, b2_kinematicBody);
	b2Fixture* f = body->body->GetFixtureList();
	f->SetRestitution(2.0f);
	body->type = MUSHROOM;
	Mushroom* mushroom = new Mushroom();
	mushroom->phys = body;
	mushroom->start_position = mushroom->phys->body->GetPosition();
	mushroom->start_rotation = rotation;
	mushroom->phys->body->SetTransform(mushroom->start_position, mushroom->start_rotation);
	mushroom->group = group;
	interactables.add(mushroom);
}

void ModuleSceneIntro::CreateBigbumpers(int x, int y, int w, int h, bool flip_)
{
	PhysBody* body;
	if (flip_) {
		int bigbumpercoord[10] = {
			9, 1,
			41, 101,
			22, 121,
			1, 102,
			2, 0
		};
		body = App->physics->CreateChain(x, y, bigbumpercoord, 10, true);
	}
	else
	{
		int bigbumpercoord[10] = {
			39, 0,
			38, 102,
			20, 123,
			1, 103,
			21, 8
		};
		body = App->physics->CreateChain(x, y, bigbumpercoord, 10, true);
	}
	b2Fixture* f = body->body->GetFixtureList();
	f->SetRestitution(4.0f);
	body->type = BIGBUMPER;
	BigBumper* bigbumper = new BigBumper();
	bigbumper->phys = body;
	bigbumper->flip = flip_;
	interactables.add(bigbumper);
}

void ModuleSceneIntro::LoseLife()
{
	if(lives>=0) lives--;
	if (lives == 0)
	{
		GameOver();
	}
	else state = RESTART;
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
	PhysBody* pivot = App->physics->CreateCircle(x + 76, y + 76, 5, b2_kinematicBody, -2);

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
	w->start_rotation = body->GetRotation();
	w->start_position = { PIXEL_TO_METERS(x), PIXEL_TO_METERS(y) };

	interactables.add(w);
}

Groups ModuleSceneIntro::chackBonus(Interactable* object, Groups g)
{
		if (g == BONUS && timer > 20)
		{
			object->Restart();
		}
		if (object->active == true && g != BONUS)
		{
			return g = OFF;
		}
		else
		{
			return g;
		}
}

void ModuleSceneIntro::BlitScene()
{
	App->renderer->Blit(background_image, 0, 0);
	int x, y;

	p2List_item<Interactable*>* interactable = interactables.start;
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
			if(interactable->data->flip)
			App->renderer->Blit(bigbumper, x, y, interactable->data->GetSprite());
			else
			App->renderer->Blit(bigbumper, x, y, interactable->data->GetSprite(),0,0,true);
			break;
		case MUSHROOM:
			App->renderer->Blit(mushroom, x, y, interactable->data->GetSprite(),0, interactable->data->phys->GetRotation());
		break;
		}
		interactable = interactable->next;
	}

	for (int i = 0; i < 5; i++)
	{
		flippers[i]->GetPosition(x, y);
		App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[i]->GetRotation(), (i%2 == 0)? false:true);
	}

	launcher_phys->GetPosition(x, y);
	App->renderer->Blit(launcher, x, y);

	App->renderer->Blit(background, 0, 0);
	for (int i = 0; i < 6; i++)
	{
		extra_balls[i]->GetPosition(x, y);
		App->renderer->Blit(extra_ball, x, y);
	}

	ball_phys->GetPosition(x, y);
	App->renderer->Blit(ball, x, y, NULL, 1.0F, ball_phys->GetRotation());


	if(state == GAME_OVER) App->renderer->Blit(game_over_text, 0, 0);
	else if(state == START_MENU) App->renderer->Blit(start_menu, 0, 0);
	if(state == BONUSES)App->renderer->Blit(bonus, 0, 0);
}

void ModuleSceneIntro::ManageInputs()
{
	if (state == PLAYING)
	{
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		{
			mouse_joint->SetTarget({ PIXEL_TO_METERS(449), PIXEL_TO_METERS(950) });
			mouse_joint->SetFrequency(1.0f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			App->audio->PlayFx(fx[FX_LAUNCHER]);
			mouse_joint->SetTarget({ PIXEL_TO_METERS(449), PIXEL_TO_METERS(935) });
			mouse_joint->SetFrequency(150.0f);
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) App->audio->PlayFx(fx[FX_FLIPPER]);
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			flippers[1]->body->ApplyTorque(10000.0f, true);
			flippers[3]->body->ApplyTorque(10000.0f, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			flippers[0]->body->ApplyTorque(-10000.0f, true);
			flippers[2]->body->ApplyTorque(-10000.0f, true);
			flippers[4]->body->ApplyTorque(-10000.0f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		{
			if (tilts > 0)
			{
				ball_phys->body->ApplyForceToCenter({ 0.0f,80.0f }, true);
				tilts--;
			}
		}
	}

	if (state == START_MENU && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (lives == 0) {
			state = RESTART;
			lives = 3;
		}
		else
		{
			App->audio->PlayFx(fx[FX_START]);
			state = PLAYING;
		}
	}

	if (state == GAME_OVER)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			state = RESTART;
			lives = 3;
		}
		else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN) state = START_MENU;
	}
}

Groups ModuleSceneIntro::DataBonus(Groups g)
{
	if (g == ON)
	{
		state = BONUSES;
		return g = BONUS;
	}
	else
	{

		if (g == BONUS)
		{
			if (timer > 20)
			{
				App->score->IncreaseScore(5000);
				App->audio->PlayFx(fx[FX_BONUS]);
				timer = 0;
				state = PLAYING;
				return g = ON;
			}
			timer++;
		}
		else
		{
			return g = ON;
		}
	}
}

void ModuleSceneIntro::GameOver()
{
	App->audio->PlayFx(fx[FX_GAME_OVER]);
	state = GAME_OVER;
	App->score->Finished();
}
