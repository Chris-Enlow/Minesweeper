#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#pragma once
using namespace std;

bool isSpecialKey(int a) {
	if (a < 65 || a > 122) {
		return true;
	}
	if (a < 97 && a > 90) {
		return true;
	}
	return false;
}
sf::Text loadInputPrompt(int height, int width) {
	sf::Text inputPrompt;
	inputPrompt.setString("Enter your name:");
	inputPrompt.setCharacterSize(20);
	inputPrompt.setFillColor(sf::Color::White);
	inputPrompt.setStyle(sf::Text::Bold);
	return inputPrompt;
}
sf::Text loadWelcomeText(int height, int width) {
	sf::Text welcomeText;
	welcomeText.setString("WELCOME TO MINESWEEPER!");
	welcomeText.setCharacterSize(24);
	welcomeText.setFillColor(sf::Color::White);
	welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	return welcomeText;
}

sf::Text loadLeaderboardText() {
	sf::Text text;
	text.setString("LEADERBOARD");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	return text;
}

void keyPressed(string& text, int input) {
	if (!isSpecialKey(input)) {
		if (text.length() == 0 && (input >= 97 && input < 122)) {
			input -= 32;
		}
		if (text.length() > 0 && (input >= 65 && input <= 90)) {
			input += 32;
		}
		if (text.length() < 10) {

			text += static_cast<char>(input);
		}
	}
	else if (input == 8) {
		if (text.length() > 0) {
			string deletedText = "";
			for (int i = 0; i < text.length() - 1; i++) {
				deletedText += text[i];
			}
			text.clear();
			for (int i = 0; i < deletedText.length(); i++) {
				text += static_cast<char>(deletedText[i]);
			}
		}
	}
}