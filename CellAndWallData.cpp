//
// Created by molpo on 9/10/2025.
//

#include "CellAndWallData.h"

namespace MAZE {
	CellData::CellData(int row, int col) {coords[0] = row; coords[1] = col; isExplored = false;}
	// Placeholder
	CellData::~CellData() = default;

	WallData::WallData(int row, int col) {coords[0] = row; coords[1] = col; isBroken = false;}
	// Placeholder
	WallData::~WallData() = default;

}