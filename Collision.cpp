#pragma once
//функции столкнавений 

#include "Ball.h"
#include "Kicker.h"
#include "Setting.h"
#include <vector>
#include <algorithm>

bool _borderСollision(Ball* _ball, Kicker* _kicker, GameSetting* _gamesetting)
{
	//вовзращаемое значение:
	//если каши\рик упал < сгенерировать новую карту

	//првоерка на столкновение с рамкой 
	//верх
	if (_ball->y - _ball->r <= 0)
		if (_ball->dy < 0)
		{
			_ball->dy *= -1;
			return 0;

		}
	//лево
	if (_ball->x - _ball->r <= 0)
		if (_ball->dx < 0)
		{
			_ball->dx *= -1;
			return 0;
		}
	//право
	if (_ball->x + _ball->r >= _ball->wight)
		if (_ball->dx > 0)
		{
			_ball->dx *= -1;
			
			return 0;
		}
	//низ
	if (_ball->y - 4 * _ball->r > _ball->hight)
	{

	
		_ball->stopmove();
		_ball->active = false;


		_ball->x = _kicker->pointx + (_gamesetting->wight / 10) / 2;
		_ball->y = _kicker->pointy - _gamesetting->range;
		return 1;

	}

	return 0;
}

void _kickerСollision(Kicker* _kicker, Ball* _ball )
{
	//Проверка столкновения с битой
	if ((_ball->y < _kicker->pointy && _ball->y + _ball->r + _ball->dy  > _kicker->pointy))
		if (_ball->x > _kicker->pointx - _ball->r && _ball->x < _kicker->pointx + _kicker->wight + _ball->r)
			if (_ball->dy > 0)
				_ball->dy *= -1;
}

void _rockСollision(Rock* _rock, Ball* _ball)
{
	//проверка на столкновение с камнем

	int top;
	int bot;
	int right;
	int left;
	int minimum;

	//если камень живой,
	//если центр шарика на расстоянии радиуса от границ
	//тога вычисляются растояния до центров ребер до центра шарика
	if (_rock->live)
		if (_rock->x1 < _ball->x + _ball->r && _ball->x - _ball->r < _rock->x1 + _rock->w)
			if (_rock->y1 < _ball->y + _ball->r && _ball->y - _ball->r < _rock->y1 + _rock->h)
			{
				top = abs(_ball->y - _rock->y1);
				bot = abs(_ball->y - _rock->y1 + _rock->h);

				left = abs(_ball->x - _rock->x1);
				right = abs(_ball->x - _rock->x1 + _rock->w);

				//находится минимальное расстояние
				minimum = min(min(top, bot), min(right, left));
				//шарик отражается от стороны< с минимальным расстоянием до шарика
				if (minimum == top || minimum == bot)
					_ball->dy *= -1;

				else
					_ball->dx *= -1;

				//консольный вывод расчетво ближайшей стороны

				/*
				cout << "top = " << top << "  bot = " << bot << "  left = " << left << " right = " << right << endl;
				cout << "Minimum = " << minimum << endl;
				*/

				//камень умирает после соприкосновения
				_rock->live = false;
			}
};

void _rocksСollision(vector <Rock*>* _rocks, Ball* _ball)

{
	//колизия с камнем для коллекции камней
	for (int i = 0; i < _rocks->size(); i++)
		_rockСollision(_rocks->at(i), _ball);
};