#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#pragma once

void loadNumberTextures(map<int, sf::Texture>& numberTextures) {
    sf::Texture tnum0;
    tnum0.loadFromFile("files/images/tile_revealed.png");
    numberTextures.emplace(0, tnum0);
    sf::Texture tnum1;
    tnum1.loadFromFile("files/images/number_1.png");
    numberTextures.emplace(1, tnum1);
    sf::Texture tnum2;
    tnum2.loadFromFile("files/images/number_2.png");
    numberTextures.emplace(2, tnum2);
    sf::Texture tnum3;
    tnum3.loadFromFile("files/images/number_3.png");
    numberTextures.emplace(3, tnum3);
    sf::Texture tnum4;
    tnum4.loadFromFile("files/images/number_4.png");
    numberTextures.emplace(4, tnum4);
    sf::Texture tnum5;
    tnum5.loadFromFile("files/images/number_5.png");
    numberTextures.emplace(5, tnum5);
    sf::Texture tnum6;
    tnum6.loadFromFile("files/images/number_6.png");
    numberTextures.emplace(6, tnum6);
    sf::Texture tnum7;
    tnum7.loadFromFile("files/images/number_7.png");
    numberTextures.emplace(7, tnum7);
    sf::Texture tnum8;
    tnum8.loadFromFile("files/images/number_8.png");
    numberTextures.emplace(8, tnum8);
}

void loadDigitTextures(map<int, sf::Texture>& digitTextures) {
    sf::Texture redneg;
    redneg.loadFromFile("files/images/digits.png", sf::IntRect(210, 0, 21, 32));
    digitTextures.emplace(-1, redneg);
    sf::Texture red0;
    red0.loadFromFile("files/images/digits.png", sf::IntRect(0, 0, 21, 32));
    digitTextures.emplace(0, red0);
    sf::Texture red1;
    red1.loadFromFile("files/images/digits.png", sf::IntRect(21, 0, 21, 32));
    digitTextures.emplace(1, red1);
    sf::Texture red2;
    red2.loadFromFile("files/images/digits.png", sf::IntRect(42, 0, 21, 32));
    digitTextures.emplace(2, red2);
    sf::Texture red3;
    red3.loadFromFile("files/images/digits.png", sf::IntRect(63, 0, 21, 32));
    digitTextures.emplace(3, red3);
    sf::Texture red4;
    red4.loadFromFile("files/images/digits.png", sf::IntRect(84, 0, 21, 32));
    digitTextures.emplace(4, red4);
    sf::Texture red5;
    red5.loadFromFile("files/images/digits.png", sf::IntRect(105, 0, 21, 32));
    digitTextures.emplace(5, red5);
    sf::Texture red6;
    red6.loadFromFile("files/images/digits.png", sf::IntRect(126, 0, 21, 32));
    digitTextures.emplace(6, red6);
    sf::Texture red7;
    red7.loadFromFile("files/images/digits.png", sf::IntRect(147, 0, 21, 32));
    digitTextures.emplace(7, red7);
    sf::Texture red8;
    red8.loadFromFile("files/images/digits.png", sf::IntRect(168, 0, 21, 32));
    digitTextures.emplace(8, red8);
    sf::Texture red9;
    red9.loadFromFile("files/images/digits.png", sf::IntRect(189, 0, 21, 32));
    digitTextures.emplace(9, red9);
}

void loadSprites(map<string, sf::Texture>& sprites) {
    sf::Texture mineTexture;
    mineTexture.loadFromFile("files/images/mine.png");
    sprites.emplace("mine", mineTexture);
    sf::Texture tileTexture;
    tileTexture.loadFromFile("files/images/tile_hidden.png");
    sprites.emplace("tile", tileTexture);
    sf::Texture revealedTileTexture;
    revealedTileTexture.loadFromFile("files/images/tile_revealed.png");
    sprites.emplace("revealedTile", revealedTileTexture);
    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");
    sprites.emplace("flag", flag);
    sf::Texture happyTexture;
    happyTexture.loadFromFile("files/images/face_happy.png");
    sprites.emplace("happyFace", happyTexture);
    sf::Texture winningTexture;
    winningTexture.loadFromFile("files/images/face_win.png");
    sprites.emplace("winFace", winningTexture);
    sf::Texture losingTexture;
    losingTexture.loadFromFile("files/images/face_lose.png");
    sprites.emplace("loseFace", losingTexture);
    sf::Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    sprites.emplace("debug", debugTexture);
    sf::Texture lb;
    lb.loadFromFile("files/images/leaderboard.png");
    sprites.emplace("leaderboard", lb);
    sf::Texture play;
    play.loadFromFile("files/images/play.png");
    sprites.emplace("play", play);
    sf::Texture pause;
    pause.loadFromFile("files/images/pause.png");
    sprites.emplace("pause", pause);
    sf::Texture tnum0;
    tnum0.loadFromFile("files/images/tile_revealed.png");
    sprites.emplace("0", tnum0);
    sf::Texture tnum1;
    tnum1.loadFromFile("files/images/number_1.png");
    sprites.emplace("1", tnum1);
    sf::Texture tnum2;
    tnum2.loadFromFile("files/images/number_2.png");
    sprites.emplace("2", tnum2);
    sf::Texture tnum3;
    tnum3.loadFromFile("files/images/number_3.png");
    sprites.emplace("3", tnum3);
    sf::Texture tnum4;
    tnum4.loadFromFile("files/images/number_4.png");
    sprites.emplace("4", tnum4);
    sf::Texture tnum5;
    tnum5.loadFromFile("files/images/number_5.png");
    sprites.emplace("5", tnum5);
    sf::Texture tnum6;
    tnum6.loadFromFile("files/images/number_6.png");
    sprites.emplace("6", tnum6);
    sf::Texture tnum7;
    tnum7.loadFromFile("files/images/number_7.png");
    sprites.emplace("7", tnum7);
    sf::Texture tnum8;
    tnum8.loadFromFile("files/images/number_8.png");
    sprites.emplace("8", tnum8);
}

