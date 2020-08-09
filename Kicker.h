#pragma once
#include <iostream>
using namespace std;
class Kicker
{
private:
public:
	float pointx; //якорь а.к.а. поинт
	float pointy; //якорь 
	float wight;
	float hight;

	Kicker(float pontex, float pointy, float wight, float hight) {
		this->pointx = pontex;
		this->pointy = pointy;
		this->wight = wight;
		this->hight = hight;
	}

	~Kicker() {
		std::cout << "Distructor Kicker complited" << std::endl;
	};

};