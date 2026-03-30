#include "BoxObject.h"
#include <iostream>
#include <cmath>
#define CONST_FORCE_MULT 0.2

void BoxObject::render(sf::Image& image) {
	std::cout << pos.x << " " << pos.y << "\n";
	auto size = image.getSize();

	int px = std::round(pos.x);
	int py = std::round(pos.y);

	for (int _x = px; _x < px + width; _x++) {
		for (int _y = py; _y < py + height; _y++) {
			if (_x < 0 || _x >= size.x || _y < 0 || _y >= size.y)
				continue;
			image.setPixel(_x, _y, sf::Color(255, 0, 0));
		}
	}
}

vec2 BoxObject::getCenter() {
	return vec2(pos.x + (float)width / 2.0, pos.y + (float)height / 2.0);
}

bool BoxObject::checkCollision(vec2 newpos) {
	vec2 center = getCenter();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			int wx = (int)(newpos.x + i);
			int wy = (int)(newpos.y + j);

			if (world->read(wx, wy).density > 0)
				return true;
		}
	}
	return false;
}

void BoxObject::update() {
	vec2 newpos = pos + vec2(0, vel.y);
	if (!checkCollision(newpos)) {
		pos = newpos;
	}
	else {
		vel.y = 0;
	}

	newpos = pos + vec2(vel.x, 0);
	if (!checkCollision(newpos)) {
		pos = newpos;
	}
	else {
		vel.x = 0;
	}

	vel.y += 0.1;
}