//
// Created by molpo on 9/10/2025.
//

#ifndef MAZE_GENERATOR_V2_MAZE_GENERATION_H
#define MAZE_GENERATOR_V2_MAZE_GENERATION_H

#include "MazeData.h"

namespace MAZE {
	enum branchOperations {PUSH, POP};
	enum cardinals {NORTH, SOUTH, EAST, WEST};
	struct EntryAndExit {
		int row, col; cardinals dir;

		void setCoords(int inputRow, int inputCol, cardinals inputDir)
			{row = inputRow; col = inputCol; dir = inputDir;}
	};

	class MazeGeneration {
		[[nodiscard]] int getRandVal(int seed) const;
		// Storing an array of bools corresponding to if the corresponding enum values are valid directions
		// [0] = North, [1] = South, [2] = East, [3] = West
		bool validDirections[4]{};
		int numValidCardinals{};
		int numCellsExplored{};
		CellData *currentCell{};

	public:
		MazeGeneration(int row, int col);
		~MazeGeneration();

		int lengthOfBranch{};
		int** currentBranch{nullptr};
		MazeData* currentMaze;
		EntryAndExit entryCoords{};
		EntryAndExit exitCoords{};

		// Resizes our current branch by either pushing inputCell or popping the top item
		void resizeBranch(branchOperations operation, CellData *inputCell = nullptr);

		// Pushes the coordinates of the input cell to the top of the current branch
		void pushToBranch(CellData *inputCell);
		// Pops the top cell coordinates from the top of the current branch
		void popBranch();

		/* Modifies the validDirections bool array stored as a private variable
		 * [0] = North, [1] = South, [2] = East, [3] = West*/
		void checkValidCardinals();

		void initMaze(int entryRow = 0, int entryCol = 0);

	   /* Will return true if the maze is not fully initialized.
		* The function iterates our position in the maze by one,
		* if we finish the maze then our currentBranch[] array will
		* be empty and as such we'll terminate the driver function*/
		bool iterateMaze();
	};
}

#endif //MAZE_GENERATOR_V2_MAZE_GENERATION_H