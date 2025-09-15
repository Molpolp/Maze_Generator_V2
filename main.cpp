#include <iostream>
#include <string>

#include "MazeGeneration.h"
#include "raylib.h"
#include "VerifyInput.h"

enum windowAndMazeParams {
	WIDTH_OFFSET = 50, HEIGHT_OFFSET = 50,
	WINDOW_WIDTH = 1400, WINDOW_HEIGHT = 1400
};

void drawMaze(MAZE::MazeGeneration &mazeToDraw, int mazeHeight, int cellHeight, int mazeWidth, int cellWidth);
void drawEntryOrExit(MAZE::EntryAndExit &wallToBreak, int cellHeight, int heightOffset, int cellWidth, int widthOffset);

int main() {
	int mazeHeight = VI::verifyIntInput
					("Please specify the height of the maze in the range [5, 50]: ",5, 50);
	int mazeWidth = VI::verifyIntInput
					("Please specify the width of the maze in the range [5, 50]: ",5, 50);

	int cellHeight = (WINDOW_HEIGHT - HEIGHT_OFFSET * 2) / mazeHeight;
	int cellWidth = (WINDOW_WIDTH - WIDTH_OFFSET * 2) / mazeWidth;

	MAZE::MazeGeneration testMaze(mazeHeight, mazeWidth);
	testMaze.initMaze();

	testMaze.entryCoords.setCoords(0, 0,  MAZE::WEST);
	testMaze.exitCoords.setCoords(mazeHeight / 2, mazeWidth - 1, MAZE::EAST);

	while (testMaze.iterateMaze()){};
	std::cout << "Maze Generation Finished." << std::endl;

	drawMaze(testMaze, mazeHeight, cellHeight, mazeWidth, cellWidth);

	return 0;
}

void drawMaze(MAZE::MazeGeneration &mazeToDraw, int mazeHeight, int cellHeight, int mazeWidth, int cellWidth) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawFPS(5, 5);

			DrawRectangle(WIDTH_OFFSET, HEIGHT_OFFSET,
				WINDOW_WIDTH - WIDTH_OFFSET * 2, WINDOW_HEIGHT - HEIGHT_OFFSET * 2, BLACK);
			DrawRectangleLines(WIDTH_OFFSET, HEIGHT_OFFSET,
				WINDOW_WIDTH - WIDTH_OFFSET * 2, WINDOW_HEIGHT - HEIGHT_OFFSET * 2, WHITE);

			int reveal = static_cast<int>(GetTime() * 120);
			reveal = std::min(reveal + 1, mazeHeight * mazeWidth);

			int startX{}, endX{}, currentX{}, startY{}, endY{}, currentY{};

			drawEntryOrExit(mazeToDraw.entryCoords, cellHeight, HEIGHT_OFFSET,
													cellWidth, WIDTH_OFFSET);

			drawEntryOrExit(mazeToDraw.exitCoords, cellHeight, HEIGHT_OFFSET,
													cellWidth, WIDTH_OFFSET);

			for (int row = 0; row < mazeHeight; row++) {
				for (int col = 0; col < mazeWidth; col++) {
					if (row * mazeWidth + col >= reveal) continue;

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
		EndDrawing();
	}
}

void drawEntryOrExit(MAZE::EntryAndExit &wallToBreak, int cellHeight, int heightOffset, int cellWidth, int widthOffset) {
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