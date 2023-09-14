#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Tile.h"
#pragma once
using namespace std;

void drawBoard(sf::RenderWindow& window, Tile** gameBoard, bool& paused, bool& showLeaderboard,
    bool& gameLost, bool& allowClicks, int& squaresSearched,
    int tileHeight, int tileWidth, map <string, sf::Texture>& sprites, bool& won, int& flagCounter) {
    if (won) {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                if (gameBoard[i][j].getCorrect() == "mine") {
                    gameBoard[i][j].setCurrent("flag");
                }
            }
        }
    }
    if (!showLeaderboard && !paused && !gameLost) {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                if (gameBoard[i][j].isSolved) {
                    squaresSearched++;
                }
                if (gameBoard[i][j].getCurrent() == "flag" || gameBoard[i][j].getCurrent() == "tile") {
                    sf::Sprite temp;
                    temp.setTexture(sprites.at("tile"));
                    temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                    window.draw(temp);
                }
                else {
                    sf::Sprite temp;
                    temp.setTexture(sprites.at("0"));
                    temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                    window.draw(temp);
                }
                sf::Sprite temp;
                temp.setTexture(sprites.at(gameBoard[i][j].getCurrent()));
                temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                window.draw(temp);
            }
        }
    }
    else if (!gameLost) {
        allowClicks = false;
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                sf::Sprite temp;
                temp.setTexture(sprites.at("0"));
                temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                window.draw(temp);
            }
        }
    }
    else {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                sf::Sprite bg;
                bg.setTexture(sprites.at("0"));
                bg.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                window.draw(bg);
                if (gameBoard[i][j].getCorrect() != "mine") {
                    sf::Sprite temp;
                    temp.setTexture(sprites.at(gameBoard[i][j].getCurrent()));
                    temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                    window.draw(temp);
                }
                else {
                    sf::Sprite temp;
                    temp.setTexture(sprites.at("mine"));
                    temp.setPosition(gameBoard[i][j].x, gameBoard[i][j].y);
                    window.draw(temp);
                }
                
            }
        }
    }
}
