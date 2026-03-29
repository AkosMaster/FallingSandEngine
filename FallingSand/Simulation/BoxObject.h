#pragma once
#include <SFML/Graphics.hpp>
#include "Sand.h"

#include "vec2.h"

class BoxObject {
	int width;
	int height;
	
	SandWorld* world;
	
	float mass;
	float drag;
public:
	vec2 pos;
	vec2 accel;

	BoxObject(SandWorld* world, vec2 pos, int width, int height, float mass, float drag=0.85) : world(world), width(width), height(height), pos(pos), mass(mass), drag(drag) {}

	void render(sf::Image& image);

	vec2 getCenter();
	vec2 getForces();
	void update();
};