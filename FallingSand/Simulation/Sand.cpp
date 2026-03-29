#include "Sand.h"
#include "../Math/Perlin.h"
#include <stdio.h>
#include <iostream>

SandWorld::SandWorld(int width, int height) : width(width), height(height) {
	buffer = new SandCell[width * height];
	
	Perlin noise = Perlin(2);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			double n = noise.noise(x * 0.1, y * 0.1);
			if (n > 0.75) {
				write(x, y, SandCell(Wood, INT_MAX));
			}
			else if (n > 0.25) {
				write(x, y, SandCell(Sand, 3));
			}
			else if (n > 100) {
				write(x, y, SandCell(Water, 2));
			}
			else {
				write(x, y, SandCell(Empty, 0));
			}
		}
	}
}

inline void SandWorld::write(int x, int y, SandCell type) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		buffer[y * width + x] = type;
	}
}

inline SandCell SandWorld::read(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return buffer[y * width + x];
	}
	return SandCell(Wall, INT_MAX);
}

inline void SandWorld::swap(int x, int y, int x2, int y2) {
	SandCell temp = read(x, y);
	write(x, y, read(x2, y2));
	write(x2, y2, temp);
}

void SandWorld::render(sf::Image& image) {
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			// itt: dinamikus programozassal megmondani hanyan vannak fölöttem egy sorban
			// ha 0 akkor a leheto legvilagosabb szinem legyen, ha sokan akkor egyre sotetebb (egy max pontig)


			SandCell cell = read(x, y);
			switch (cell.type) {
			case Empty:
				image.setPixel(x, y, sf::Color::Black);
				break;
			case Sand:
				image.setPixel(x, y, sf::Color(194, 178, 128));
				break;
			case Water:
				image.setPixel(x, y, sf::Color(0, 0, 255));
				break;
			case Wall:
				image.setPixel(x, y, sf::Color(255,0,0));
				break;
			case Wood:
				image.setPixel(x, y, sf::Color(164, 116, 73));
			}
		}
	}
}


void SandWorld::update() {
	
	for (int y = height - 1; y >= 0; y--) {
		bool go_right = rand() % 2 == 0;

		for (int _x = 0; _x < width; _x++) {
			int x = go_right ? _x : width - 1 - _x;
			updateCell(x, y);
		}
	}
	updateTick++;
}

void SandWorld::updateCell(int x, int y) {
	
	SandCell cell = read(x, y);

	if (cell.lastUpdateTick >= updateTick) {
		return;
	}
	else {
		cell.lastUpdateTick = updateTick;
	}

	switch (cell.type) {
	case Sand:

		//essen le
		if (read(x, y + 1).density < cell.density) {
			swap(x, y, x, y + 1);
		}
		//ha nem tud leesni ,akkor essen valamerre oldalra
		else if (rand() % 2 == 0) {
			//bal oldal
			if (read(x - 1, y + 1).density < cell.density) {
				swap(x, y, x - 1, y + 1);
			}
		}
		else {
			//jobb oldal
			if (read(x + 1, y + 1).density < cell.density) {
				swap(x, y, x + 1, y + 1);
			}
		}
		break;

	case Water: 

		if (read(x, y + 1).density < cell.density) {
			swap(x, y, x, y + 1);
			x, y = x, y + 1;
		}
 //átló probléma
		int rng = rand() % 2;
		if (rng == 0) {
			if (read(x-1, y).density < cell.density) {
				swap(x, y, x-1, y);
			}
		}
		else {
			if (read(x+1, y).density < cell.density) {
				swap(x, y, x+1, y);
			}
		}
		break;
	}
}





