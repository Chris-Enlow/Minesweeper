#include "Textures.h"
#include "Text.h"
#include "Game.h"
#include "Tile.h"
#include "Window.h"
#include "Leaderboard.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
    //load board dimensions

    ifstream file("files/board_config.cfg", ios_base::in);
    int tileWidth;
    int tileHeight;
    int mineCount;
    file >> tileWidth >> tileHeight >> mineCount;

    //load leaderboard

    fstream leaderboardFile;
    leaderboardFile.open("files/leaderboard.txt", ios::in);
    string line;
    map<int, Score> leaderboard;
    int ranking = 1;
    while (getline(leaderboardFile, line)) {
        Score player(line.substr(0, 5), line.substr(6), false);
        leaderboard.emplace(ranking, player);
        ranking++;
    }
    leaderboardFile.close();




    string text;
    string name;
    sf::RenderWindow welcomeWindow(sf::VideoMode(tileWidth * 32, (tileHeight * 32) + 100), "SFML window", sf::Style::Close);
    sf::Text welcomeText = loadWelcomeText(tileHeight, tileWidth);
    sf::Text inputPrompt = loadInputPrompt(tileHeight, tileWidth);
    sf::Text playerName;
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    //load basic sprites

    map<string, sf::Texture> sprites;
    loadSprites(sprites);
    sf::Sprite playButton;
    playButton.setTexture(sprites.at("play"));
    sf::Sprite pauseButton;
    pauseButton.setTexture(sprites.at("pause"));;

    //Load mine numbers
    map<int, sf::Texture> numberTextures;
    loadNumberTextures(numberTextures);

    //load red numbers

    map<int, sf::Texture> digitTextures;
    loadDigitTextures(digitTextures);

    //load button sprites

    sf::Sprite happyFace;
    happyFace.setTexture(sprites.at("happyFace"));
    sf::Sprite winningFace;
    winningFace.setTexture(sprites.at("winFace"));
    sf::Sprite losingFace;
    losingFace.setTexture(sprites.at("loseFace"));
    sf::Sprite debugIcon;
    debugIcon.setTexture(sprites.at("debug"));
    sf::Sprite leaderboardButton;
    leaderboardButton.setTexture(sprites.at("leaderboard"));

    //load welcome scripts

    welcomeText.setFont(font);
    sf::FloatRect tRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(tRect.left + tRect.width / 2.0f, tRect.top + tRect.height / 2.0f);
    welcomeText.setPosition(welcomeWindow.getSize().x * .5f, (welcomeWindow.getSize().y * .5f) - 150.0f);

    inputPrompt.setFont(font);
    sf::FloatRect pRect = inputPrompt.getLocalBounds();
    inputPrompt.setOrigin(pRect.left + pRect.width / 2.0f, pRect.top + pRect.height / 2.0f);
    inputPrompt.setPosition(welcomeWindow.getSize().x * .5f, (welcomeWindow.getSize().y * .5f) - 75.0f);

    playerName.setFont(font);
    playerName.setCharacterSize(18);
    playerName.setFillColor(sf::Color::Yellow);
    playerName.setStyle(sf::Text::Bold);

    //create system for when to move on to next stage

    bool endWelcome = false;
    bool gameOver = false;

    while (welcomeWindow.isOpen()) {
        sf::Event event;
        welcomeWindow.clear(sf::Color(0, 0, 255, 255));
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(inputPrompt);
        while (welcomeWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                int input = event.text.unicode;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && text.length() > 0) {
                    endWelcome = true;
                    break;
                }
                keyPressed(text, input);
            }
        }
        if (!endWelcome) {
            playerName.setString(text + "|");
            sf::FloatRect nRect = playerName.getLocalBounds();
            playerName.setOrigin(nRect.left + nRect.width / 2.0f, nRect.top + nRect.height / 2.0f);
            playerName.setPosition(welcomeWindow.getSize().x * .5f, (welcomeWindow.getSize().y * .5f) - 45.0f);
            welcomeWindow.draw(playerName);
            welcomeWindow.display();
        }
        else {
            name = text;
            welcomeWindow.close();
        }
    }
    if (text.length() == 0) {
        return 0;
    }

    //Adjust Sprites

    happyFace.setPosition(((tileWidth / 2.0f) * 32.0f) - 32.0f, 32.0f * (tileHeight + 0.5f));
    winningFace.setPosition(((tileWidth / 2.0f) * 32.0f) - 32.0f, 32.0f * (tileHeight + 0.5f));
    losingFace.setPosition(((tileWidth / 2.0f) * 32.0f) - 32.0f, 32.0f * (tileHeight + 0.5f));
    debugIcon.setPosition((tileWidth * 32.0f) - 304.0f, 32.0f * (tileHeight + 0.5f));
    playButton.setPosition((tileWidth * 32.0f) - 240.0f, 32.0f * (tileHeight + 0.5f));
    pauseButton.setPosition((tileWidth * 32.0f) - 240.0f, 32.0f * (tileHeight + 0.5f));
    leaderboardButton.setPosition((tileWidth * 32.0f) - 176.0f, 32.0f * (tileHeight + 0.5f));

    //Mine Counter

    sf::Sprite mine1;
    sf::Sprite mine2;
    sf::Sprite mine3;
    sf::Sprite negativeMines;
    mine1.setPosition(33, 32 * ((tileHeight)+0.5f) + 16);
    mine2.setPosition(54, 32 * ((tileHeight)+0.5f) + 16);
    mine3.setPosition(75, 32 * ((tileHeight)+0.5f) + 16);
    negativeMines.setPosition(12, 32 * ((tileHeight)+0.5f) + 16);
    int flagCount = mineCount;
    mine1.setTexture(digitTextures.at(flagCount / 100));
    mine2.setTexture(digitTextures.at(flagCount / 10));
    mine3.setTexture(digitTextures.at(flagCount % 10));
    negativeMines.setTexture(digitTextures.at(-1));

    //Create Board

    int** boardKey = new int* [tileHeight];
    for (int i = 0; i < tileHeight; i++) {
        boardKey[i] = new int[tileWidth];
    }
    vector<sf::Sprite> debugMines;

    Tile** gameBoard = new Tile * [tileHeight];
    for (int i = 0; i < tileHeight; i++) {
        gameBoard[i] = new Tile[tileWidth];
    }


    //Functionality
    bool debugMode = false;
    int squaresSearched = 0;
    int solvedSquareCount = tileHeight * tileWidth - mineCount;

    //Clock things

    sf::Sprite time1;
    sf::Sprite time2;
    sf::Sprite time3;
    sf::Sprite time4;
    time1.setPosition(((tileWidth) * 32.0f) - 97.0f, 32.0f * (tileHeight + 0.5f) + 16.0f);
    time2.setPosition(((tileWidth) * 32.0f) - 76.0f, 32.0f * (tileHeight + 0.5f) + 16.0f);
    time3.setPosition(((tileWidth) * 32.0f) - 54.0f, 32.0f * (tileHeight + 0.5f) + 16.0f);
    time4.setPosition(((tileWidth) * 32.0f) - 33.0f, 32.0f * (tileHeight + 0.5f) + 16.0f);
    time1.setTexture(digitTextures.at(0));
    time2.setTexture(digitTextures.at(0));
    time3.setTexture(digitTextures.at(0));
    time4.setTexture(digitTextures.at(0));
    int lastTime = 0;
    int pausedTime = 0;
    bool paused = false;
    sf::Clock pausedClock;
    sf::Clock clock;
    int currTime = 0;

    int firstWin = 0;
    bool gameLost = false;
    bool allowClicks = true;
    bool showLeaderboard = false;
    bool makeNewBoard = true;
    bool won = false;
    sf::RenderWindow gameWindow(sf::VideoMode(tileWidth * 32, (tileHeight * 32) + 100), "SFML window", sf::Style::Close);
    while (gameWindow.isOpen()) {
        if (makeNewBoard) {
            flagCount = mineCount;
            firstWin = 0;
            squaresSearched = 0;
            won = false;
            allowClicks = true;
            gameOver = false;
            gameLost = false;
            vector<int> boardTemplate = createBoard(tileHeight, tileWidth, mineCount);

            for (int i = 0; i < tileHeight; i++) {
                for (int j = 0; j < tileWidth; j++) {
                    boardKey[i][j] = boardTemplate[i * tileWidth + j];
                }
            }
            for (int i = 0; i < tileHeight; i++) {
                for (int j = 0; j < tileWidth; j++) {
                    if (boardKey[i][j] == 1) {
                        sf::Sprite mine;
                        mine.setTexture(sprites.at("mine"));
                        mine.setPosition(j * 32.0f, i * 32.0f);
                        debugMines.push_back(mine);
                        gameBoard[i][j] = Tile("mine", "tile", (j) * 32.0f, (i) * 32.0f);
                    }
                    else {
                        int currMines = getNearbyMines(boardKey, i, j, tileWidth, tileHeight);
                        string temp = determineTexture(currMines);
                        gameBoard[i][j] = Tile(temp, "tile", (j) * 32.0f, (i) * 32.0f);
                    }
                }
            }
            makeNewBoard = false;
        }
        if (squaresSearched == solvedSquareCount) { gameOver = true; }
        sf::Event event;
        gameWindow.clear(sf::Color(255, 255, 255, 255));
        if (!gameOver) {
            if (!paused) {
                sf::Time elapsed1 = clock.getElapsedTime();
                currTime = (int)elapsed1.asSeconds();
                lastTime = currTime - pausedTime;
            }
            else if (paused) {
                allowClicks = false;
                sf::Time elapsed = pausedClock.getElapsedTime();
                pausedTime = (int)elapsed.asSeconds() - lastTime;
            }
            int time4num = lastTime % 10;
            int time3num = lastTime % 60 / 10;
            int time2num = lastTime / 60 % 10;
            int time1num = lastTime / 60 / 10;
            time1.setTexture(digitTextures.at(time1num));
            time2.setTexture(digitTextures.at(time2num));
            time3.setTexture(digitTextures.at(time3num));
            time4.setTexture(digitTextures.at(time4num));
        }
        gameWindow.draw(happyFace);
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    double mouseX = sf::Mouse::getPosition(gameWindow).x;
                    double mouseY = sf::Mouse::getPosition(gameWindow).y;
                    if (mouseY < tileHeight * 32.0f && allowClicks && !gameLost) {
                        int tileX = (int)mouseX / 32.0f;
                        int tileY = (int)mouseY / 32.0f;

                        //When not a mine
                        if (gameBoard[tileY][tileX].getCurrent() != "flag") {

                            if (boardKey[tileY][tileX] == 0) {
                                int currMines = getNearbyMines(boardKey, tileY, tileX, tileWidth, tileHeight);

                                //When no Adjacent Mines

                                if (currMines == 0) {
                                    //No Number Way
                                    int** tiles = new int* [tileHeight];
                                    for (int i = 0; i < tileHeight; i++) {
                                        tiles[i] = new int[tileWidth];
                                    }
                                    for (int i = 0; i < tileHeight; i++) {
                                        for (int j = 0; j < tileWidth; j++) {
                                            tiles[i][j] = boardKey[i][j];
                                        }
                                    }
                                    findEmpties(tiles, tileY, tileX, tileWidth, tileHeight);
                                    for (int i = 0; i < tileHeight; i++) {
                                        for (int j = 0; j < tileWidth; j++) {
                                            if (tiles[i][j] == 2) {
                                                if (gameBoard[i][j].getCurrent() != "flag") {
                                                    gameBoard[i][j].setCurrent(gameBoard[i][j].getCorrect());
                                                }
                                            }
                                        }
                                    }
                                    for (int i = 0; i < tileHeight; i++) {
                                        delete[] tiles[i];
                                    }
                                    delete[] tiles;
                                }

                                //When there are adjacent mines

                                else {
                                    gameBoard[tileY][tileX].setCurrent(gameBoard[tileY][tileX].getCorrect());
                                }
                            }

                            //When its a mine

                            else if (boardKey[tileY][tileX] == 1) {
                                gameBoard[tileY][tileX].setCurrent(gameBoard[tileY][tileX].getCorrect());
                                gameOver = true;
                                gameLost = true;
                            }
                        }
                    }

                    //Happy face button

                    else if (faceBounds(mouseX, mouseY, tileHeight, tileWidth) && allowClicks) {
                        makeNewBoard = true;
                        clock.restart();
                        pausedClock.restart();
                        lastTime = 0;
                        currTime = 1;
                    }

                    //When press Debug Button

                    else if (debugBounds(mouseX, mouseY, tileHeight, tileWidth) && !gameOver) {
                        debugMode = !debugMode;
                    }

                    //Pause Button

                    else if (pauseBounds(mouseX, mouseY, tileHeight, tileWidth) && !gameOver) {
                        if (paused) {
                            allowClicks = true;
                        }
                        else { allowClicks = false; }
                        paused = !paused;
                    }

                    //Leaderboard button

                    else if (leaderboardBounds(mouseX, mouseY, tileHeight, tileWidth)) {
                        //Show leaderboard
                        showLeaderboard = true;
                        allowClicks = false;
                    }
                }

                //When Right Click for a Flag

                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    double mouseX = sf::Mouse::getPosition(gameWindow).x;
                    double mouseY = sf::Mouse::getPosition(gameWindow).y;
                    if (mouseY < tileHeight * 32.0f) {
                        int tileX = (int)mouseX / 32.0f;
                        int tileY = (int)mouseY / 32.0f;
                        if (!gameBoard[tileY][tileX].isSolved) {
                            if (gameBoard[tileY][tileX].getCurrent() != "flag") {
                                gameBoard[tileY][tileX].setCurrent("flag");
                                flagCount--;
                            }
                            else {
                                gameBoard[tileY][tileX].setCurrent("tile");
                                flagCount++;
                            }
                        }
                    }
                }
            }
        }
        if (gameOver) {
            if (gameLost) {
                gameWindow.draw(losingFace);
            }
            else {
                gameWindow.draw(winningFace);
                won = true;
                flagCount = 0;
                firstWin++;
            }
        }
        int absolute = 0;
        if (flagCount < 0) {
            absolute = abs(flagCount);
        }
        else {
            absolute = flagCount;
        }
        mine1.setTexture(digitTextures.at(absolute / 100));
        mine2.setTexture(digitTextures.at(absolute / 10));
        mine3.setTexture(digitTextures.at(absolute % 10));
        //Draw board
        squaresSearched = 0;
        drawBoard(gameWindow, gameBoard, paused, showLeaderboard, gameLost, allowClicks,
            squaresSearched, tileHeight, tileWidth, sprites, won, flagCount);
        if (debugMode && !paused) {
            for (int i = 0; i < debugMines.size(); i++) {
                gameWindow.draw(debugMines[i]);
            }
        }
        gameWindow.draw(time1);
        gameWindow.draw(time2);
        gameWindow.draw(time3);
        gameWindow.draw(time4);
        if (flagCount < 0) {
            gameWindow.draw(negativeMines);
        }
        gameWindow.draw(mine1);
        gameWindow.draw(mine2);
        gameWindow.draw(mine3);
        if (!paused) {
            gameWindow.draw(pauseButton);
        }
        else {
            gameWindow.draw(playButton);
        }
        gameWindow.draw(debugIcon);
        gameWindow.draw(leaderboardButton);
        gameWindow.display();
        if (showLeaderboard || firstWin == 1) {
            createWindow(leaderboard, tileHeight, tileWidth, font);
            if (!won) {
                sf::Time elapsed = pausedClock.getElapsedTime();
                pausedTime = (int)elapsed.asSeconds() - lastTime;
                showLeaderboard = false;
                if (!paused) {
                    allowClicks = true;
                }
            }
        }
        //Leaderboard changes
        if (gameOver) {
            bool changed = false;
            if (won) {
                Score newScore(lastTime, name, true);
                for (int i = 1; i <= 5; i++) {
                    if (lastTime < leaderboard[i].convertToSeconds()) {
                        changed = true;
                        for (int j = i; j <= 5; j++) {
                            leaderboard[i + 1] = leaderboard[i];
                        }
                        leaderboard[i] = newScore;
                        break;
                    }
                }
            }
            if (changed) {
                leaderboardFile.open("files/leaderboard.txt", ios::out);
                for (int i = 1; i <= 5; i++) {
                    leaderboardFile << leaderboard[i].getFileScript() << endl;
                }
                leaderboardFile.close();
            }
        }
    }
    for (int i = 0; i < tileHeight; i++) {
        delete[] boardKey[i];
    }
    delete[] boardKey;
    for (int i = 0; i < tileHeight; i++) {
        delete[] gameBoard[i];
    }
    delete[] gameBoard;

    //Game end

    return 0;
}