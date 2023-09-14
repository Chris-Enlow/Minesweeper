#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#pragma once
using namespace std;

string determineTexture(int mines) {
	string value = "";
	switch (mines) {
		case 0:
			value = "0";
			break;
		case 1:
			value = "1";
			break;
		case 2:
			value = "2";
			break;
		case 3:
			value = "3";
			break;
		case 4:
			value = "4";
			break;
		case 5:
			value = "5";
			break;
		case 6:
			value = "6";
			break;
		case 7:
			value = "7";
			break;
		case 8:
			value = "8";
			break;
	}
	return value;
}


vector<int> createBoard(int tileHeight, int tileWidth, int mineCount) {
	vector<int> tempBoard;
	for (int i = 0; i < tileHeight * tileWidth; i++) {
		tempBoard.push_back(0);
	}
	int max = tileHeight * tileWidth - 1;
	for (int i = 0; i < mineCount; i++) {
		int random = rand() % max;
		if (tempBoard[random] == 1) {
			i--;
		}
		else {
			tempBoard[random] = 1;
		}
	}
	return tempBoard;
}

int getNearbyMines(int** board, int row, int col, int boardWidth, int boardHeight) {
	boardWidth--;
	boardHeight--;
	int mines=0;
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	if (row == 0) { top = true; } 
	if (row == boardHeight) { bottom = true; }
	if (col == 0) { left = true; }
	if (col == boardWidth) { right = true; }
	if (!top) {
		if (board[row - 1][col] == 1) { mines++; }
	}
	if (!bottom) {
		if (board[row + 1][col] == 1) { mines++; }
	}
	if (!left) {
		if (board[row][col - 1] == 1) { mines++; }
	}
	if (!right) {
		if (board[row][col + 1] == 1) { mines++; }
	}
	if (!top && !left) {
		if (board[row - 1][col - 1] == 1) { mines++; }
	}
	if (!top && !right) {
		if (board[row - 1][col + 1] == 1) { mines++; }
	}
	if (!bottom && !left) {
		if (board[row + 1][col - 1] == 1) { mines++; }
	}
	if (!bottom && !right) {
		if (board[row + 1][col + 1] == 1) { mines++; }
	}
	return mines;
}

void findEmpties(int** board, int row, int col, int boardWidth, int boardHeight) {
	board[row][col] = 2;
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	if (row == 0) { top = true; }
	if (row == boardHeight-1) { bottom = true; }
	if (col == 0) { left = true; }
	if (col == boardWidth-1) { right = true; }
	if(!top){
		if (board[row-1][col] == 0) {
			if (getNearbyMines(board, row-1, col, boardWidth, boardHeight) == 0) {
				findEmpties(board, row - 1, col, boardWidth, boardHeight);
			}
			else { board[row - 1][col] = 2; }
		}
	}
	if (!bottom) {
		if (board[row + 1][col] == 0) {
			if (getNearbyMines(board, row + 1, col, boardWidth, boardHeight) == 0) {
				findEmpties(board, row + 1, col, boardWidth, boardHeight);
			}
			else { board[row + 1][col] = 2; }
		}
	}
	if (!left) {
		if (board[row][col-1] == 0) {
			if (getNearbyMines(board, row, col-1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row, col-1, boardWidth, boardHeight);
			}
			else { board[row][col-1] = 2; }
		}
	}
	if (!right) {
		if (board[row][col+1] == 0) {
			if (getNearbyMines(board, row, col+1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row, col+1, boardWidth, boardHeight);
			}
			else { board[row][col+1] = 2; }
		}
	}
	if (!top && !right) {
		if (board[row - 1][col+1] == 0) {
			if (getNearbyMines(board, row - 1, col+1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row - 1, col+1, boardWidth, boardHeight);
			}
			else { board[row - 1][col+1] = 2; }
		}
	}
	if (!bottom && !right) {
		if (board[row + 1][col+1] == 0) {
			if (getNearbyMines(board, row + 1, col+1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row + 1, col+1, boardWidth, boardHeight);
			}
			else { board[row + 1][col+1] = 2; }
		}
	}
	if (!top && !left) {
		if (board[row-1][col - 1] == 0) {
			if (getNearbyMines(board, row-1, col - 1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row-1, col - 1, boardWidth, boardHeight);
			}
			else { board[row-1][col - 1] = 2; }
		}
	}
	if (!bottom && !left) {
		if (board[row+1][col -1 ] == 0) {
			if (getNearbyMines(board, row+1, col - 1, boardWidth, boardHeight) == 0) {
				findEmpties(board, row+1, col - 1, boardWidth, boardHeight);
			}
			else { board[row+1][col - 1] = 2; }
		}
	}
}

int pauseGame(int time) {
	sf::Clock pausedClock;
	int pausedTime;
	sf::Time elapsed = pausedClock.getElapsedTime();
	pausedTime = (int)elapsed.asSeconds() - time;
	return pausedTime;
}

bool faceBounds(float mouseX, float mouseY, int tileHeight, int tileWidth) {
	if (mouseX > ((tileWidth / 2.0f) * 32.0f) - 32.0f && mouseX < ((tileWidth / 2.0f) * 32.0f) + 32.0f
		&& mouseY > 32.0f * (tileHeight + 0.5f) && mouseY < 32.0f * (tileHeight + 0.5f) + 64.0f) {
		return true;
	}
	return false;
}
bool debugBounds(float mouseX, float mouseY, int tileHeight, int tileWidth) {
	if (mouseX > (tileWidth * 32.0f) - 304.0f && mouseX < (tileWidth * 32.0f) - 240.0f
		&& mouseY > 32.0f * (tileHeight + 0.5f && mouseY < 32.0f * (tileHeight + 0.5f) + 0.5f) + 64.0f) {
		return true;
	}
	return false;
}
bool pauseBounds(float mouseX, float mouseY, int tileHeight, int tileWidth) {
	if (mouseX > (tileWidth) * 32.0f - 240.0f && mouseX < (tileWidth) * 32.0f - 176.0f
		&& mouseY > 32.0f * ((tileHeight)+0.5f) && mouseY < 32.0f * ((tileHeight)+0.5f) + 64.0f) {
		return true;
	}
	return false;
}
bool leaderboardBounds(float mouseX, float mouseY, int tileHeight, int tileWidth) {
	if (mouseX > (tileWidth * 32.0f) - 176.0f && mouseX < (tileWidth * 32.0f) - 112.0f
		&& mouseY > 32.0f * (tileHeight + 0.5f) && mouseY < 32.0f * (tileHeight + 0.5f) + 64.0f) {
		return true;
	}
	return false;
}


