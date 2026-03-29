#include "BoxObject.h"
#include <iostream>

#define CONST_FORCE_MULT 0.05

void BoxObject::render(sf::Image& image) {
	auto size = image.getSize();
	for (int _x = pos.x; _x < pos.x + width; _x++) {
		for (int _y = pos.y; _y < pos.y + height; _y++) {
			if (_x < 0 || _x >= size.x || _y < 0 || _y >= size.y)
				continue;
			image.setPixel(_x, _y, sf::Color(255, 0, 0));
		}
	}
}

vec2 BoxObject::getCenter() {
	return vec2(pos.x + (float)width / 2.0, pos.y + (float)height / 2.0);
}

vec2 BoxObject::getForces() {
	vec2 center = getCenter();
	vec2 sumForces = vec2(0, 1);
	for (int _x = pos.x; _x < pos.x + width; _x++) {
		for (int _y = pos.y; _y < pos.y + height; _y++) {
			if (world->read(_x, _y).density > 0) {
				vec2 dir = (center - vec2(_x, _y)).normalized();
				sumForces += dir;
			}
		}
	}
	return sumForces;
}

void BoxObject::update() {
	vec2 forces = getForces();
	accel += forces * CONST_FORCE_MULT;
	accel *= drag;
	pos += accel;
}