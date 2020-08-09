#include "Rock.h"
#include <iostream>

Rock::Rock(float x1, float y1, float h, float w) {
	this->x1 = x1;
	this->y1 = y1;
	this->h = h;
	this->w = w;

	live = 1;
}

Rock::~Rock() {
	std::cout << "Distructor ROCK complited" << std::endl;
}