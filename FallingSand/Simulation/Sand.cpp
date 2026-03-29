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
			SandCell c;
			if (n > 0.75) {
				c = SandCell(Wood, INT_MAX, true);
			}
			else if (n > 0.5) {
				c = SandCell(Sand, 3, true);
			}
			else if (n > 0.25) {
				c = SandCell(Water, 2, false);
			}
			else {
				c = SandCell(Empty, 0, false);
			}

			write(x, y, c);
			
		}
	}
	//tree.refresh(0, 0, 0);
}

inline void SandWorld::write(int x, int y, SandCell cell) {
	if (x >= 0 && x < width && y >= 0 && y < height) {

		SandCell prev = buffer[y * width + x];
		if (!prev.collides && cell.collides) {
			tree.modify(x, y, 1);
		}
		else if (prev.collides && !cell.collides) {
			tree.modify(x, y, -1);
		}

		buffer[y * width + x] = cell;
		
	}
}

inline SandCell SandWorld::read(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return buffer[y * width + x];
	}
	return SandCell(Wall, INT_MAX, false);
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

			int quaddepth = tree.getdepth(x, y);
			if (quaddepth > 0) {
				image.setPixel(x, y, sf::Color(255*quaddepth/8, 0, 0));
				continue;
			}

			sf::Color color;
			switch (cell.type) {
			case Empty:
				color = sf::Color::Black;
				break;
			case Sand:
				color = sf::Color(194, 178, 128);
				break;
			case Water:
				color = sf::Color(0,0, 255);
				break;
			case Wall:
				color = sf::Color(255,0,0);
				break;
			case Wood:
				color = sf::Color(164, 116, 73);
				break;
			}
			//image.setPixel(x, y, color);
			image.setPixel(x, y, color);

			
		}
	}
}


void SandWorld::update() {
	//return;
	std::cout << "Updating world..." << rand() << std::endl;
	for (int y = height - 1; y >= 0; y--) {
		bool go_right = rand() % 2 == 0;

		for (int _x = 0; _x < width; _x++) {
			int x = go_right ? _x : width - 1 - _x;
			updateCell(x, y);
		}
	}
	updateTick++;
	tree.updateTick++;
	tree.refresh(0, 0, 0);
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





