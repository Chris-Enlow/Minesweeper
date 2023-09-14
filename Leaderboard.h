#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#pragma once
using namespace std;

class Score {
public:
	bool isUser;
	string time;
	string name;
	Score() {
		time = "";
		name = "";
	}
	Score(string time , string name, bool user) {
		this->name = name;
		this->time = time;
		this->isUser = user;
	}
	Score(int time, string name, bool user) {
		this->name = name;
		this->time = convertToTimer(time);
		this->isUser = user;
	}

	int convertToSeconds() {
		int mins = stoi(time.substr(0,2));
		mins *= 60;
		int seconds = stoi(time.substr(3, 2));
		return mins + seconds;
	}

	string convertToTimer(int timex) {
		string fin = "";
		int timeSeconds = timex % 60;
		int timeMinutes = timex / 60;
		string str1 = to_string(timeSeconds);
		string str2 = to_string(timeMinutes);
		

		if (timeMinutes < 10) {
			str2 = "0" + str2;
		}
		if (timeSeconds < 10){
			str1 = "0" + str1;
		}
		fin = str2 + ":" + str1;
		return fin;
	}

	string getTimerValue() {
		return time;
	}
	string getFileScript() {
		if (isUser) {
			return time + "," + name + "*";
		}
		return time + "," + name;
	}

};

void createWindow(map<int, Score> board, int height, int width, sf::Font& font) {
	sf::RenderWindow window(sf::VideoMode(width * 16, (height * 16) + 50), "SFML window", sf::Style::Close);
	sf::Text leaderboardText = loadLeaderboardText();
	leaderboardText.setFont(font);
	sf::FloatRect lRect = leaderboardText.getLocalBounds();
	leaderboardText.setOrigin(lRect.left + lRect.width / 2.0f, lRect.top + lRect.height / 2.0f);
	leaderboardText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 120.0f);
	string temp = "";
	for (int i = 1; i <= 5; i++) {
		string str = to_string(i);
		temp = temp + str+".\t"+board.at(i).getTimerValue() + "\t" + board.at(i).name;
		if(board[i].isUser){
			temp = temp + "*";
		}
		temp = temp + "\n\n";
	}

	sf::Text rankings;
	rankings.setString(temp);
	rankings.setCharacterSize(18);
	rankings.setFillColor(sf::Color::White);
	rankings.setFont(font);
	sf::FloatRect pRect = rankings.getLocalBounds();
	rankings.setOrigin(pRect.left + pRect.width / 2.0f, pRect.top + pRect.height / 2.0f);
	rankings.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 20.0f);

	while (window.isOpen()) {
		sf::Event event;
			while (window.pollEvent(event)) {
				if(event.type == sf::Event::Closed) {
					window.close();
				}
		}

		window.clear(sf::Color::Blue);
		window.draw(leaderboardText);
		window.draw(rankings);
		window.display();

	}

}
