#include "Ball.h"
#include <iostream>

using namespace std;

Ball::Ball(float r, float x, float y,
	float wight, float hight,

	float speedx, float speedy)
{
	this->r = r;
	this->x = x;
	this->y = y;

	this->wight = wight;
	this->hight = hight;
};

Ball::~Ball() {
	cout << "destroyed ball" << endl;
};

void Ball::move() {
	//���������� �������� (��������)

	x += dx;
	y += dy;

};

void Ball::stopmove()
{
	//������� �������� ���� (��� �������������)
	dx = 0;
	dy = 0;
}