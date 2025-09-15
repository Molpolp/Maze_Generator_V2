//
// Created by molpo on 9/10/2025.
//

#include "MazeData.h"

namespace MAZE {
	MazeData::MazeData(int row, int col) {
		totalRows = row; totalCols = col;
		initCells(); initWalls();
	}
	MazeData::~MazeData() {
		for (int row = 0; row < totalRows; row++) {
			for (int col = 0; col < totalCols; col++) {
				delete cellData[row][col];
			}
			delete[] cellData[row];
		}
		delete[] cellData;

		for (int row = 0; row < totalRows; row++) {
			for (int col = 0; col < totalCols; col++) {
				if (row != (totalRows - 1)) {delete rowWallData[row][col];}
				if (col != (totalCols - 1)) {delete colWallData[row][col];}
			}
			delete[] rowWallData[row];
			delete[] colWallData[row];
		}
		delete[] rowWallData;
		delete[] colWallData;
	}

	void MazeData::initCells() {
		cellData = new CellData**[totalRows];

		for (int row = 0; row < totalRows; row++) {
			cellData[row] = new CellData*[totalCols];

			for (int col = 0; col < totalCols; col++) {
				cellData[row][col] = new CellData(row, col);
			}
		}
	}
	void MazeData::initWalls() {
		rowWallData = new WallData**[totalRows - 1];
		colWallData = new WallData**[totalRows];

		for (int row = 0; row < totalRows; row++) {
			if (row != (totalRows - 1)) {rowWallData[row] = new WallData*[totalCols];}
			colWallData[row] = new WallData*[totalCols - 1];

			for (int col = 0; col < totalCols; col++) {
				if (row != (totalRows - 1)) {rowWallData[row][col] = new WallData(row, col);}
				if (col != (totalCols - 1)) {colWallData[row][col] = new WallData(row, col);}
			}
		}
	}
}