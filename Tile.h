#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#pragma once
using namespace std;
class Tile {
public:
	string correctText;
	string currentText;
	string backdrop;
	float x;
	float y;
	bool isSolved;
	Tile() {

		correctText = "";
		currentText = "";
		backdrop = "";
		x = 0;
		y = 0;
		isSolved = false;
	}
	Tile(string corr, string curr, float x, float y) {

		correctText = corr;
		currentText = curr;
		this->x = x;
		this->y = y;
		isSolved = false;

	}
	string getCorrect() {
		return correctText;
	}
	string getCurrent() {
		return currentText;
	}
	void setCurrent(string a) {
		if (a == correctText) {
			isSolved = true;
		}
		currentText = a;
	}
};