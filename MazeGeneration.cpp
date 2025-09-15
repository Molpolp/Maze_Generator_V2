//
// Created by molpo on 9/10/2025.
//

#include "MazeGeneration.h"

namespace MAZE {
	MazeGeneration::MazeGeneration(int row, int col) {currentMaze = new MazeData(row, col);}
	MazeGeneration::~MazeGeneration() {delete[] currentBranch; delete currentMaze;}

	int MazeGeneration::getRandVal(int seed) const {
		static int chaos = currentMaze->totalCols * currentMaze->totalRows * 907;
		chaos = chaos ^ (seed * currentMaze->totalRows);
		chaos = chaos >> 3;
		return chaos;
	}

	void MazeGeneration::resizeBranch(branchOperations operation, CellData *inputCell) {
		switch (operation) {
			case POP: {
				if (!lengthOfBranch) {return;}
				lengthOfBranch--;

				if (!lengthOfBranch) {
					// Uncomment when done debugging
					delete[] currentBranch;
					currentBranch = nullptr;
					currentCell = nullptr;
					return;
				}

				int **newBranch = new int*[lengthOfBranch];
				for (int index = 0; index < lengthOfBranch; index++) {newBranch[index] = currentBranch[index];}

				delete[] currentBranch;
				currentBranch = newBranch;

				currentCell = currentMaze->cellData
					[currentBranch[lengthOfBranch - 1][0]]
					[currentBranch[lengthOfBranch - 1][1]];

				return;
			}

			case PUSH: {
				int **newBranch = new int*[lengthOfBranch + 1];

				for (int index = 0; index < lengthOfBranch; index++) {newBranch[index] = currentBranch[index];}

				newBranch[lengthOfBranch] = inputCell->coords;
				delete[] currentBranch;
				currentBranch = newBranch;
				lengthOfBranch++;

				return;
			}

			default: {
				std::cout << "Error in MazeGeneration class, resizeBranch function received input out of scope: "
				<< operation << std::endl;
			}
		}
	}

	void MazeGeneration::pushToBranch(CellData *inputCell) {resizeBranch(PUSH, inputCell);}
	void MazeGeneration::popBranch() {resizeBranch(POP);}

	void MazeGeneration::checkValidCardinals() {
		const int row = currentCell->coords[0], col = currentCell->coords[1];
		numValidCardinals = 0;

		for (bool & direction : validDirections) {direction = false;}

		// Note: the additional if statements are to ensure we don't accidentally check out of bounds of our map
		// North check
		if (row > 0 && !currentMaze->cellData[row - 1][col]->isExplored)
			{validDirections[NORTH] = true; numValidCardinals++;}

		// South check
		if (row < currentMaze->totalRows - 1 && !currentMaze->cellData[row + 1][col]->isExplored)
			{validDirections[SOUTH] = true; numValidCardinals++;}

		// East check
		if (col < currentMaze->totalCols - 1 && !currentMaze->cellData[row][col + 1]->isExplored)
			{validDirections[EAST] = true; numValidCardinals++;}

		// West check
		if (col > 0 && !currentMaze->cellData[row][col - 1]->isExplored)
			{validDirections[WEST] = true; numValidCardinals++;}
	}

	void MazeGeneration::initMaze(int entryRow, int entryCol) {
		currentCell = currentMaze->cellData[entryRow][entryCol];
		pushToBranch(currentCell);
		currentCell->isExplored = true;
		numCellsExplored = 1;
		entryCoords.row = entryRow;
		entryCoords.col = entryCol;
	}

	bool MazeGeneration::iterateMaze() {
		int randVal{}, curRow{}, curCol{};

		if (lengthOfBranch) {
			randVal = getRandVal(lengthOfBranch),
			curRow = currentBranch[lengthOfBranch - 1][0],
			curCol = currentBranch[lengthOfBranch - 1][1];
			currentCell = currentMaze->cellData[curRow][curCol];
		}

		// This shouldn't happen but just in case
		else {
			std::cout << "Unexpected early lengthOfBranch == 0 return from iterateMaze method.\n"
			<< "lengthOfBranch: " << lengthOfBranch << std::endl;
			return lengthOfBranch > 0;
		}

		checkValidCardinals();

		// If there are no valid paths just pop the top of our branch and return
		if (!numValidCardinals) {popBranch(); return lengthOfBranch > 0;}

		int countdown{};
		randVal %= numValidCardinals;

		for (int direction = 0; direction < 4; direction++) {

			if (!validDirections[direction]) {continue;}
			if (countdown++ != randVal) {continue;}

			int newRow = curRow, newCol = curCol;

			// Chose the next cell to go to
			switch (direction) {
				case NORTH: {--newRow; break;}

				case SOUTH: {++newRow; break;}

				case EAST:  {++newCol; break;}

				case WEST:  {--newCol; break;}

				default: {std::cout << "Bad index in iterateMaze switch statement: " << direction; break;}
			}

			// Break wall between current cell and the next cell we just chose above
			{
				// North check
				if (newRow == curRow - 1) {currentMaze->rowWallData[newRow][curCol]->isBroken = true;}

				// South check
				else if (newRow == curRow + 1) {currentMaze->rowWallData[curRow][curCol]->isBroken = true;}

				// East check
				else if (newCol == curCol + 1) {currentMaze->colWallData[curRow][curCol]->isBroken = true;}

				// West check
				else if (newCol == curCol - 1) {currentMaze->colWallData[curRow][newCol]->isBroken = true;}

				// IDK how this happened but oops
				else {
					std::cout << "IDK what happened, error in wall breaking else if sequence\n"
					<< "curRow: " << curRow << std::endl << "newRow: " << newRow << std::endl
					<< "curCol: " << curCol << std::endl << "newCol: " << newCol << std::endl;
				}
			}

			currentCell = currentMaze->cellData[newRow][newCol];
			currentCell->isExplored = true;

			pushToBranch(currentCell);

			// Break from the for loop
			break;
		}
		// When lengthOfBranch == 0 we'll have explored the entire maze
		return lengthOfBranch > 0;
	}
}