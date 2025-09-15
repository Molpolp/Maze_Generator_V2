//
// Created by molpo on 9/10/2025.
//

#ifndef MAZE_GENERATOR_V2_CELL_AND_WALL_DATA_H
#define MAZE_GENERATOR_V2_CELL_AND_WALL_DATA_H

namespace MAZE {
	class CellData {
	public:
		CellData(int row, int col);
		~CellData();

		/*For an MxN maze with M rows and N columns
		coords[0] = row
		coords[1] = column*/
		int coords[2]{};
		// Tracks if the cell has been added to the maze yet
		bool isExplored;
	};

	class WallData {
	public:
		WallData(int row, int col);
		~WallData();

		/*For an MxN maze with M rows and N columns
		It has M - 1 rows of walls and N - 1 columns of walls
		coords[0] = row
		coords[1] = column*/
		int coords[2]{};
		// Tracks if the wall has been broken yet
		bool isBroken;
	};
}

#endif //MAZE_GENERATOR_V2_CELL_AND_WALL_DATA_H