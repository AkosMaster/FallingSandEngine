#pragma once
#include <SFML/Graphics.hpp>
#include "Sand.h"

#include "vec2.h"

class BoxObject {
	int width;
	int height;
	
	SandWorld* world;
	float mass;
public:
	vec2 pos;
	vec2 vel;

	BoxObject(SandWorld* world, vec2 pos, int width, int height, float mass) : world(world), width(width), height(height), pos(pos), mass(mass) {}

	void render(sf::Image& image);

	vec2 getCenter();
	bool checkCollision(vec2 newpos);
	void update();
};