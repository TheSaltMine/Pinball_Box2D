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

	#include "BackgroundVertex.h"
	background_phys = App->physics->CreateChain(0, 0, background_vertex, 204, true);
	ball_phys = App->physics->CreateCircle(449, 625, 8);
	ball_phys->body->SetBullet(true);
	spring_phys = App->physics->CreateRectangle(449, 800, 21, 26);


	
	flippers[0] = App->physics->CreateFlipper(130, 895);
	flippers[1] = App->physics->CreateFlipper(220, 895, true);


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
	/*if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}*/

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

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		flippers[1]->body->ApplyTorque(10000.0f, true);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		flippers[0]->body->ApplyTorque(-10000.0f, true);
	}


	//Draw background
	int x, y;
	background_phys->GetPosition(x, y);
	App->renderer->Blit(background, x, y);

	ball_phys->GetPosition(x, y);
	App->renderer->Blit(ball, x, y, NULL, 1.0F, ball_phys->GetRotation());
	spring_phys->GetPosition(x, y);
	App->renderer->Blit(spring, x, y);

	flippers[0]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[0]->GetRotation());
	flippers[1]->GetPosition(x, y);
	App->renderer->Blit(flipper, x, y, NULL, 1.0F, flippers[1]->GetRotation());

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
