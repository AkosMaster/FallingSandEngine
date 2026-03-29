#pragma once
#include <SFML/Graphics.hpp>
enum SandType {
	Empty = 0,
	Sand = 1,
	Water = 2,
	Wall = 3
};

struct SandCell {

	SandCell(SandType type = Empty, int regionId = -1) : type(type), regionId(regionId) {}

	SandType type;
	int regionId;
};

class SandWorld {
	int width;
	int height;


	SandCell* buffer;
	
public:
	SandWorld(int width, int height);
	~SandWorld() {
		delete[] buffer;
	}

	inline void write(int x, int y, SandCell cell);
	inline SandCell read(int x, int y);

	void render(sf::Image& image);
};