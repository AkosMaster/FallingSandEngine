#include "QuadTree.h"
#include <iostream>
void QuadTree::modify(int x, int y, int amt) {
	for (int i = 0; i < depth; i++) {
		int _x = x / sizes[i];
		int _y = y / sizes[i];

		counts[i][_x + gridSizes[i] * _y] += amt;
	}
	//std::cout << "total:" << counts[0][0] << "\n";
}

void QuadTree::refresh(int gridx, int gridy, int level = 0) {

	bool hasBox = boxmaps[level][gridx + gridSizes[level] * gridy];
	int amount = counts[level][gridx + gridSizes[level] * gridy];

	bool full = amount >= 0.9*sizes[level] * sizes[level]; // TODO optimize

	if (level == depth-1) {
		boxmaps[level][gridx + gridSizes[level] * gridy] = amount > 0 ? updateTick : -1;
		return;
	}

	if (full) {
		boxmaps[level][gridx + gridSizes[level] * gridy] = updateTick;
		return;
	}

	if (amount == 0) {	
		return;
	}
	
	for (int _x = 0; _x < 2; _x++) {
		for (int _y = 0; _y < 2; _y++) {
			refresh(gridx * 2 + _x, gridy * 2 + _y, level + 1);
		}
	}
}