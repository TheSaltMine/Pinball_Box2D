#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -9.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


enum ColliderType
{
	NONE = -1,
	BALL,
	BACKGROUND,
	FLIPPER,
	STONE_BLOCK,
	BUMPER,
	FRUIT,
	WHEEL,
	BIGBUMPER,
	EXTRA_BALL,
	MUSHROOM,
	DEATH
};
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	ColliderType type;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType static_body = b2_dynamicBody, int filter_index = 0);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType body_type = b2_dynamicBody);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, b2BodyType body_type = b2_dynamicBody);
	PhysBody* CreateChain(int x, int y, int* points, int size, bool static_body = false);
	PhysBody* CreateFlipper(int x, int y, bool flipX = false);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;
	b2Body* ground;
private:

	bool debug;
	b2MouseJoint* mouse_joint;

};