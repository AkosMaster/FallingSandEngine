#pragma once
#include <SFML/Graphics.hpp>
#include "QuadTree.h"
enum SandType {
	Empty = 0,
	Sand = 1,
	Water = 2,
	Wall = 3,
	Wood = 4
};

struct SandCell {
	SandCell() : type(Empty), density(0), collides(false) {}

	SandCell(SandType type, int density, bool collides) : type(type), density(density), collides(collides) {}

	SandType type;
	int density;
	int lastUpdateTick = -1;
	bool collides;
};

class SandWorld {
	int width;
	int height;
	int updateTick = 0;

	SandCell* buffer;
	QuadTree tree = QuadTree(200,2,9);
	
public:
	SandWorld(int width, int height);
	~SandWorld() {
		delete[] buffer;
	}

	inline void write(int x, int y, SandCell cell);
	inline SandCell read(int x, int y);
	inline void swap (int x, int y, int x2, int y2);

	void render(sf::Image& image);
	void update();
	void updateCell(int x, int y);
};