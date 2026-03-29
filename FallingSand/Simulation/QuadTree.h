#pragma once
#include <vector>

class QuadTree {
	// size of MxM grid
	int worldSize;
	// size of quadtree leaf
	int atomSize;
	// depth of tree
	int depth;

	// grid size at each level
	std::vector<int>  sizes;
	// counts at each grid node
	std::vector<int*> counts;

	// number of grid cells per level
	std::vector<int> gridSizes;

	std::vector<int*> boxmaps;
	
public:
	int updateTick = 0;
	QuadTree(int worldSize, int atomSize, int depth) : worldSize(worldSize), atomSize(atomSize), depth(depth) {
		for (int i = 0; i < depth; i++) {
			sizes.push_back(atomSize * (1 << (depth-i-1)));
			gridSizes.push_back(worldSize/atomSize * (1 << (depth - i - 1)));
		}
		for (int i = 0; i < depth; i++) {
			int len = gridSizes[i];
			counts.push_back(new int[len * len]{0});
			boxmaps.push_back(new int[len * len]{-1});
		}
	}

	void modify(int x, int y, int amt);
	void refresh(int gridx, int gridy, int depth);

	int getdepth(int x, int y) {
		/*int i = 4;*/
		for (int i = 0; i < depth; i++) {
			int _x = x / sizes[i];
			int _y = y / sizes[i];

			if (boxmaps[i][_x + gridSizes[i] * _y] >= updateTick) {
				return i;
			}
		}
		return 0;
		/*int _x = x / sizes[i];
		int _y = y / sizes[i];

		return counts[i][_x + gridSizes[i] * _y] / (sizes[i]*sizes[i])*100;*/
	}
};