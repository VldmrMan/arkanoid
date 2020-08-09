#pragma once
//������� ������������ 

#include "Ball.h"
#include "Kicker.h"
#include "Setting.h"
#include <vector>
#include <algorithm>

bool _border�ollision(Ball* _ball, Kicker* _kicker, GameSetting* _gamesetting)
{
	//������������ ��������:
	//���� ����\��� ���� < ������������� ����� �����

	//�������� �� ������������ � ������ 
	//����
	if (_ball->y - _ball->r <= 0)
		if (_ball->dy < 0)
		{
			_ball->dy *= -1;
			return 0;

		}
	//����
	if (_ball->x - _ball->r <= 0)
		if (_ball->dx < 0)
		{
			_ball->dx *= -1;
			return 0;
		}
	//�����
	if (_ball->x + _ball->r >= _ball->wight)
		if (_ball->dx > 0)
		{
			_ball->dx *= -1;
			
			return 0;
		}
	//���
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

void _kicker�ollision(Kicker* _kicker, Ball* _ball )
{
	//�������� ������������ � �����
	if ((_ball->y < _kicker->pointy && _ball->y + _ball->r + _ball->dy  > _kicker->pointy))
		if (_ball->x > _kicker->pointx - _ball->r && _ball->x < _kicker->pointx + _kicker->wight + _ball->r)
			if (_ball->dy > 0)
				_ball->dy *= -1;
}

void _rock�ollision(Rock* _rock, Ball* _ball)
{
	//�������� �� ������������ � ������

	int top;
	int bot;
	int right;
	int left;
	int minimum;

	//���� ������ �����,
	//���� ����� ������ �� ���������� ������� �� ������
	//���� ����������� ��������� �� ������� ����� �� ������ ������
	if (_rock->live)
		if (_rock->x1 < _ball->x + _ball->r && _ball->x - _ball->r < _rock->x1 + _rock->w)
			if (_rock->y1 < _ball->y + _ball->r && _ball->y - _ball->r < _rock->y1 + _rock->h)
			{
				top = abs(_ball->y - _rock->y1);
				bot = abs(_ball->y - _rock->y1 + _rock->h);

				left = abs(_ball->x - _rock->x1);
				right = abs(_ball->x - _rock->x1 + _rock->w);

				//��������� ����������� ����������
				minimum = min(min(top, bot), min(right, left));
				//����� ���������� �� �������< � ����������� ����������� �� ������
				if (minimum == top || minimum == bot)
					_ball->dy *= -1;

				else
					_ball->dx *= -1;

				//���������� ����� �������� ��������� �������

				/*
				cout << "top = " << top << "  bot = " << bot << "  left = " << left << " right = " << right << endl;
				cout << "Minimum = " << minimum << endl;
				*/

				//������ ������� ����� ���������������
				_rock->live = false;
			}
};

void _rocks�ollision(vector <Rock*>* _rocks, Ball* _ball)

{
	//������� � ������ ��� ��������� ������
	for (int i = 0; i < _rocks->size(); i++)
		_rock�ollision(_rocks->at(i), _ball);
};