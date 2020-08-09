#pragma once
#include <iostream>
using namespace std;
class Rock {
//класс клетки на поле
public:
	float x1;  //верхняя левая точка
	float y1;
	float h;   //ширина и длина
	float w;
	bool live; //жив ли(отображается ли на поле)
	Rock(float x1, float y1, float h, float w)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->h = h;
		this->w = w;

		live = 1;
	};

	~Rock() { 
		std::cout << "Distructor ROCK complited" << std::endl; 
	};
};
