//
// Created by molpo on 9/10/2025.
//

#ifndef MAZE_GENERATOR_V2_MAZE_DATA_H
#define MAZE_GENERATOR_V2_MAZE_DATA_H

#include "CellAndWallData.h"
#include <iostream>

namespace MAZE {
	class MazeData {
		void initCells();
		void initWalls();
	public:
		MazeData(int row, int col);
		~MazeData();

		int totalRows{}, totalCols{};

		CellData*** cellData{};
		/*These walls are --- the horizontal walls
		Meaning their array will be (M - 1)xN
		Where M - 1 is the number of rows in the array*/
		WallData*** rowWallData{};
		/*These walls are | the vertical walls
		Meaning their array will be Mx(N - 1)
		Where N - 1 is the number of columns in the array*/
		WallData*** colWallData{};
	};
}

#endif //MAZE_GENERATOR_V2_MAZE_DATA_H