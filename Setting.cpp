#include "Setting.h"
#include <iostream>


GameSetting::GameSetting(

	int wight,
	int hight,

	int speedx,
	int speedy,
	int range,

	int columns,
	int rows,

	bool mouseinput)
{
	this->wight = wight;
	this->hight = hight;

	this->speedx = speedx;
	this->speedy = speedy;
	this->range = range;

	this->columns = columns;
	this->rows = rows;

	this->mouseinput = mouseinput;
}


GameSetting::~GameSetting()
{
	std::cout << "Distructor GameSetting complited" << std::endl;
}
