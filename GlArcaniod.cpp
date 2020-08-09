
#include "Rock.h"
#include "Kicker.h"
#include "Setting.h"
#include "Ball.h"

#include "Collision.cpp"

#include "glut.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <clocale>

using namespace std;

//игровые настройки
GameSetting* _gamesetting = new GameSetting(960, 700, 15, 15, 10, 15, 10, true);
Kicker* _kicker = new Kicker(_gamesetting->wight / 2 - (_gamesetting->wight / 10) / 2, _gamesetting->hight - 15, _gamesetting->wight / 10, 15);
vector <Rock*>* map = new vector<Rock*>;
Ball* _ball = new Ball(

	_gamesetting->range,
	_gamesetting->wight / 2,
	_gamesetting->hight - 15 - _gamesetting->range,
	_gamesetting->wight,
	_gamesetting->hight,
	_gamesetting->speedx,
	_gamesetting->speedy
);
//генератор камней на поле
void generator(vector <Rock*>* map, int columns, int row, float wight, float hight) {

	//отступы , меняются от значений рандома
	int _leftpaddin = 15 + rand() % 70 ; 
	int _rightpadding = 10 + rand() % 70;
	int _toppadding = 15 + rand() % 100; 
	int _botpadding = hight / 2;
	int _columns = columns + rand() % 5 - 2; //чуть чуть случайной генерации
	int _row = row + rand() % 3 - 2; //чуть чуть случайной генерации
	int _myWight = wight - _leftpaddin - _rightpadding;
	

	for (int i = 0; i < map->size(); i++)
		delete map->at(i);
	//сбор мусора
	map->clear();

	for (int i = 0; i < columns; i++)
		for (int j = 0; j < row; j++)
		{

			//формирование новый карты
			Rock* _rock = new Rock(
				_myWight / _columns * i + _leftpaddin,
				hight / _row / 2 * j + _toppadding,
				((hight-_toppadding) - _botpadding)/ _row  - 10,
				_myWight / _columns - 10);
			if (
				(wight / _columns * i+1  + _rightpadding) < wight
				//&&

				)
				map->push_back(_rock);

		}


};

//отображение одноо камня
void showRock(Rock* _rock) {

	if (_rock->live)

		glRectf(_rock->x1, _rock->y1, _rock->x1 + _rock->w, _rock->y1 + _rock->h);


};
//вектора из кмней
void showRocks(vector <Rock*>* _map) {

	//обход вектора с камнями  и отображение в drow()
	for (int i = 0; i < _map->size(); i++)
	{
		glColor3f(	(i+1)*0.008,
					(i+1)*0.007,
					(i+1)*0.05);
		showRock(_map->at(i));
	}

};
//объекты игры


//отрисовка
void Draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	//камушки
	showRocks(map);

	//бита
	glColor3f(0.2, 0.8, 0.1);
	glRectf(_kicker->pointx, _kicker->pointy, _kicker->pointx + _kicker->wight, _kicker->pointy + _kicker->hight);

	//шарик
	glColor3f(1.0, 0.3, 0.0);
	glBegin(GL_POLYGON);
	for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
	{
		glVertex2f(_ball->x + _ball->r*sin(i), _ball->y + _ball->r*cos(i));
	}

	glEnd();
	glutSwapBuffers();




};
//тикер
void Timer(int) {	
	if (_ball->active)
	{

		if(
		_borderСollision(_ball, _kicker, _gamesetting))
		//retry
		generator(map, _gamesetting->columns, _gamesetting->rows, _gamesetting->wight, _gamesetting->hight);


		_kickerСollision(_kicker, _ball);
		_rocksСollision(map,_ball);


		_ball->move();
	}

	Draw();
	glutTimerFunc(30, Timer, 500);
};
//двжиение мыши
void Mouse(int ax, int ay) {

	int mouse_x = ax;
	_kicker->pointx = ax - _kicker->wight / 2; //координаты биты

	if (!_ball->active)
	{
		_ball->x = _kicker->pointx + _kicker->wight / 2; //привязка шарика к бите
		_ball->y = _kicker->pointy - _ball->r;
	}


};
//нажатие клавишь мыши 
void MousePress(int button, int state, int x, int y) {

	// нажатие левой клавиши мыши
		if (button == GLUT_LEFT_BUTTON && !_ball->active)
		{

			_ball->active = true;
			_ball->dx =  _gamesetting->speedx;
			_ball->dy = -_gamesetting->speedy;
		}

};
//нажатие клавишь клавиатуры
void ProcessNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
	{

		delete map;
		delete _gamesetting;
		delete _ball;
		delete _kicker;

		exit(0);
	}

	if (key == 'd' || key == 'D') //движение вправо
	{
		_kicker->pointx += 50;
		if (!_ball->active)
		{
			_ball->x = _kicker->pointx + _kicker->wight / 2; //привязка шарика к бите
			_ball->y = _kicker->pointy - _ball->r;
		}

	}


	if (key == 'a' || key == 'A') // движение влево
	{
		_kicker->pointx -= 50;
		if (!_ball->active)
		{
			_ball->x = _kicker->pointx + _kicker->wight / 2; //привязка шарика к бите
			_ball->y = _kicker->pointy - _ball->r;
		}
	}


	if (key == 'w'|| key == 'W') // запуск шариа
	{

		if (!_ball->active)
		{
			_ball->active = true;
			_ball->dx = _gamesetting->speedx;
			_ball->dy = -_gamesetting->speedy;

		}
	}

};
//инициализация окна
void Init() {

	glClearColor(0.5, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, _gamesetting->wight, _gamesetting->hight, 0, 1, 0); //ориентация экрана

};

int main(int argc, char **argv)
{
	//запуска генератора впервые
	generator(map, _gamesetting->columns, _gamesetting->rows, _gamesetting->wight, _gamesetting->hight);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(_gamesetting-> wight, _gamesetting->hight);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Acranoid");
	glutDisplayFunc(Draw);
	glutTimerFunc(0, Timer, 0);


	if (_gamesetting->mouseinput) {  //опциональное включения игры с клавиатуры
		glutPassiveMotionFunc(Mouse);
		glutMouseFunc(MousePress);
	}
	else {
		glutKeyboardFunc(ProcessNormalKeys);
	}
	

	Init();
	glutMainLoop();
	
	return 0;

}
