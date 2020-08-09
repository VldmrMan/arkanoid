#include "Kicker.h"
#include <iostream>

Kicker::Kicker(float pontex, float pointy, float wight, float hight) {
	this->pointx = pontex;
	this->pointy = pointy;
	this->wight = wight;
	this->hight = hight;
}
Kicker::~Kicker() {
	std::cout << "Distructor Kicker complited" << std::endl;
};