#include <iostream>
#include <string>

#include "MazeOperations.h"
#include "raylib.h"
#include "VerifyInput.h"

enum windowAndMazeParams {
	WIDTH_OFFSET = 50, HEIGHT_OFFSET = 50,
	WINDOW_WIDTH = 1400, WINDOW_HEIGHT = 1400
};

void drawSolution(MAZE::MazeOperations &solutionToDraw,
	int cellHeight, int cellWidth);

void drawMaze(MAZE::MazeOperations &mazeToDraw, int mazeHeight, int cellHeight,
	int mazeWidth, int cellWidth, bool revealSolution);

void drawEntryOrExit(MAZE::EntryAndExit &wallToBreak, int cellHeight, int cellWidth);

int main() {
	int mazeHeight = VI::verifyIntInput
					("Please specify the height of the maze in the range [5, 100]: ",5, 100);
	int mazeWidth = VI::verifyIntInput
					("Please specify the width of the maze in the range [5, 100]: ",5, 100);

	int cellHeight = (WINDOW_HEIGHT - HEIGHT_OFFSET * 2) / mazeHeight;
	int cellWidth = (WINDOW_WIDTH - WIDTH_OFFSET * 2) / mazeWidth;

	MAZE::MazeOperations currentMaze(mazeHeight, mazeWidth);
	currentMaze.genInitMaze();

	currentMaze.entryCoords.setCoords(0, 0,  MAZE::WEST);
	currentMaze.exitCoords.setCoords(mazeHeight / 2, mazeWidth - 1, MAZE::EAST);

	while (currentMaze.genIterateMaze()){};
	std::cout << "Maze Generation Finished." << std::endl;

	currentMaze.solutionInitMaze();
	while (currentMaze.solutionIterateMaze()){};
	std::cout << "Maze Solution Constructed." << std::endl;

	bool revealSolution = VI::verifyIntInput
		("Would you like to view the solution? (1) Yes or (0) No: ", 0, 1);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "A maze of all time for sure");
	SetTargetFPS(30);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(5, 5);
		drawMaze(currentMaze, mazeHeight, cellHeight, mazeWidth, cellWidth, revealSolution);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void drawSolution(MAZE::MazeOperations &solutionToDraw, int cellHeight, int cellWidth) {
	int cornerX{}, cornerY{}, reveal{};

	reveal = static_cast<int>(GetTime() * 120);
	reveal = std::min(reveal + 1, solutionToDraw.lengthOfBranch);

	for (int index = 0; index < solutionToDraw.lengthOfBranch; index++) {

		if (index >= reveal) {continue;}

		cornerX = WIDTH_OFFSET + (solutionToDraw.currentBranch[index][1] * cellWidth);
		cornerY = HEIGHT_OFFSET + (solutionToDraw.currentBranch[index][0] * cellHeight);

		DrawRectangle(cornerX, cornerY, cellWidth, cellHeight, PURPLE);
	}
}

void drawMaze(MAZE::MazeOperations &mazeToDraw, int mazeHeight, int cellHeight,
	int mazeWidth, int cellWidth, bool revealSolution)
{
	if (revealSolution) {drawSolution(mazeToDraw, cellHeight, cellWidth);}

	DrawRectangleLines(WIDTH_OFFSET, HEIGHT_OFFSET,
		WINDOW_WIDTH - WIDTH_OFFSET * 2, WINDOW_HEIGHT - HEIGHT_OFFSET * 2, WHITE);

	int startX{}, endX{}, currentX{}, startY{}, endY{}, currentY{};

	drawEntryOrExit(mazeToDraw.entryCoords, cellHeight, cellWidth);

	drawEntryOrExit(mazeToDraw.exitCoords, cellHeight, cellWidth);

	for (int row = 0; row < mazeHeight; row++) {
		for (int col = 0; col < mazeWidth; col++) {

			if (col < mazeWidth - 1 && !mazeToDraw.currentMaze->colWallData[row][col]->isBroken) {
				startY = cellHeight * row + HEIGHT_OFFSET,
				endY = startY + cellHeight,
				currentX = cellWidth * (col + 1) + WIDTH_OFFSET;

				DrawLine(currentX, startY,
					currentX, endY, WHITE);
			}

			if (row < mazeHeight - 1 && !mazeToDraw.currentMaze->rowWallData[row][col]->isBroken) {
				startX = cellWidth * col + WIDTH_OFFSET,
				endX = startX + cellWidth,
				currentY = cellHeight * (row + 1) + HEIGHT_OFFSET;

				DrawLine(startX, currentY,
					endX, currentY, WHITE);
			}
		}
	}
}

void drawEntryOrExit(MAZE::EntryAndExit &wallToBreak, int cellHeight, int cellWidth) {
	int startX{}, endX{}, currentX{}, startY{}, endY{}, currentY{};

	switch (wallToBreak.dir) {
		case MAZE::NORTH: {
			// Will use currentY and variable X
			startX = wallToBreak.col * cellWidth + WIDTH_OFFSET;
			endX = startX + cellWidth;
			currentY = HEIGHT_OFFSET;

			DrawLine(startX, currentY, endX, currentY, BLACK);
			return;
		}

		case MAZE::SOUTH: {
			// Will use currentY and variable X
			startX = wallToBreak.col * cellWidth + WIDTH_OFFSET;
			endX = startX + cellWidth;
				// Need to offset + 1 down to get the south wall
			currentY = (wallToBreak.row + 1) * cellHeight + HEIGHT_OFFSET;

			DrawLine(startX, currentY, endX, currentY, BLACK);
			return;
		}

		case MAZE::EAST: {
			// Will use currentX and variable Y
			startY = wallToBreak.row * cellWidth + HEIGHT_OFFSET;
			endY = startY + cellHeight;
			currentX = (wallToBreak.col + 1) * cellWidth + WIDTH_OFFSET;

			DrawLine(currentX, startY, currentX, endY, BLACK);
			return;
		}

		case MAZE::WEST: {
			// Will use currentX and variable Y
			startY = wallToBreak.row * cellWidth + HEIGHT_OFFSET;
			endY = startY + cellHeight;
			currentX = WIDTH_OFFSET;

			DrawLine(currentX, startY, currentX, endY, BLACK);
			return;
		}

		default: {std::cout << "Bad index in drawEntryOrExit switch statement: " << wallToBreak.dir;}
	}
}