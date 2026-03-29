#pragma once
#include <SFML/Graphics.hpp>
enum SandType {
	Empty = 0,
	Sand = 1,
	Water = 2,
	Wall = 3,
	Wood = 4
};

struct SandCell {

	SandCell(SandType type=Empty, int density=0) : type(type), density(density) {}

	SandType type;
	int density;
	int lastUpdateTick = -1;
};

class SandWorld {
	int width;
	int height;
	int updateTick = 0;

	SandCell* buffer;
	
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