//
// Created by molpo on 9/10/2025.
//
/* Reusing data that's already been initialized for solution, this could easily be implemented
 * to initialize and track the walls encountered as it passes through the maze, just no need to here.*/

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

	class MazeOperations {
		// Storing an array of bools corresponding to if the corresponding enum values are valid directions
		// [0] = North, [1] = South, [2] = East, [3] = West
		bool validDirections[4]{};
		int numValidCardinals{};
		int numCellsExplored{};
		CellData *currentCell{};

		CellData*** solutionCellData{};

		[[nodiscard]] int getRandVal(int seed) const;

		// Resizes our current branch by either pushing inputCell or popping the top item
		void resizeBranch(branchOperations operation, CellData ***cellDataArr, CellData *inputCell = nullptr);

		// Pushes the coordinates of the input cell to the top of the current branch
		void pushToBranch(CellData *inputCell, CellData ***cellDataArr);
		// Pops the top cell coordinates from the top of the current branch
		void popBranch(CellData ***cellDataArr);

		/* Modifies the validDirections bool array stored as a private variable
		 * [0] = North, [1] = South, [2] = East, [3] = West*/
		void genCheckValidCardinals();
		void solutionCheckValidCardinals();

	public:
		MazeOperations(int row, int col);
		~MazeOperations();

		int lengthOfBranch{};
		int** currentBranch{nullptr};
		MazeData* currentMaze;
		EntryAndExit entryCoords{};
		EntryAndExit exitCoords{};

		void genInitMaze(int entryRow = 0, int entryCol = 0);
		void solutionInitMaze();

	   /* Will return true if the maze is not fully initialized.
		* The function iterates our position in the maze by one,
		* if we finish the maze then our currentBranch[] array will
		* be empty and as such we'll terminate the driver function*/
		bool genIterateMaze();
		bool solutionIterateMaze();
	};
}

#endif //MAZE_GENERATOR_V2_MAZE_GENERATION_H