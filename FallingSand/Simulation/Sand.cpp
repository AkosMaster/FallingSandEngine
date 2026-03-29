#include "Sand.h"
#include "../Math/Perlin.h"

SandWorld::SandWorld(int width, int height) : width(width), height(height) {
	buffer = new SandCell[width * height];
	
	Perlin noise = Perlin(20);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			double n = noise.noise(x * 0.1, y * 0.1);
			if (n > 0.5) {
				write(x, y, SandCell(Wall));
			}
			else {
				write(x, y, SandCell(Empty));
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
	return SandCell(Wall);
}

void SandWorld::render(sf::Image& image) {
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			SandCell cell = read(x, y);
			if (cell.type == Wall) {
				image.setPixel(x, y, sf::Color::White);
			}
			else {
				image.setPixel(x, y, sf::Color::Black);
			}
		}
	}
}