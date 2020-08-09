
#include "Rock.h"
#include "Kicker.h"
#include "Setting.h"

#include "glut.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <clocale>



using namespace std;

//игровые настройки
GameSetting* _gamesetting = new GameSetting(800, 600, 3, 3, 10, 10, 10, true);
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
//описания шарика, и событий передвижения
class Ball
{
public:
	float x, y, //координаты
		dx, dy, // скорость
		r;		//радиус

	float wight;
	float hight;

	float speedx;
	float speedy;

	vector <Rock*>* map;
	Kicker* kicker;

	bool active;
	Ball(float r, float x, float y,
		float wight, float hight,
		vector <Rock*>* map, Kicker* kicker,
		float speedx, float speedy)
	{
		this->r = r;
		this->x = x;
		this->y = y;
		
		this->wight = wight;
		this->hight = hight;

		this->map = map;
		this->kicker = kicker;


	}

	void move()
	{		//проверка на столкновения
		_rocksСollision(this->map);
		_kickerСollision(this->kicker);
		_borderСollision();
		//обновление координа (движение)
		x += dx;
		y += dy;
	}

	void stopmove()
	{
		//нулевая скорость шара (при переигрывании)
		dx = 0;
		dy = 0;
	}

	void _borderСollision()
	{
		//првоерка на столкновение с рамкой 

		if (y - r <= 0)
			if (dy < 0)
			{
				dy *= -1;
		
			}

		if (x - r <= 0)
			if (dx < 0)
			{
				dx *= -1;
		
			}
		if (x + r >= wight)
			if (dx > 0)
			{
				dx *= -1;
		
			}
		if (y - 4 * r > hight)
		{
			
			generator(map, _gamesetting->columns, _gamesetting->rows, _gamesetting->wight, _gamesetting->hight);
			stopmove();
			active = false;


			x = kicker->pointx + (_gamesetting->wight / 10)/2 ;
			y = kicker->pointy - _gamesetting->range ;

		
		}
	}

	void _kickerСollision(Kicker* kicker)
	{
		//Проверка столкновения с битой
		if ((y < kicker->pointy && y + r + speedy  > kicker->pointy))
			if (x > kicker->pointx - r && x < kicker->pointx + kicker->wight + r)
				if (dy > 0)
					dy *= -1;
	}

	void _rockСollision(Rock* _rock)
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
			if (_rock->x1 < x + r && x - r < _rock->x1 + _rock->w)
				if (_rock->y1 < y + r && y - r < _rock->y1 + _rock->h)
				{
					top = abs(y - _rock->y1);
					bot = abs(y - _rock->y1 + _rock->h);

					left = abs(x - _rock->x1);
					right = abs(x - _rock->x1 + _rock->w);

					//находится минимальное расстояние
					minimum = min(min(top, bot), min(right, left));
					//шарик отражается от стороны< с минимальным расстоянием до шарика
					if (minimum == top || minimum == bot)
						dy *= -1;

					else
						dx *= -1;

					//консольный вывод расчетво ближайшей стороны

					/*
					cout << "top = " << top << "  bot = " << bot << "  left = " << left << " right = " << right << endl;
					cout << "Minimum = " << minimum << endl;
					*/

					//камень умирает после соприкосновения
					_rock->live = false;
				}
	}

	void _rocksСollision(vector <Rock*>* _rocks)

	{
		//колизия с камнем для коллекции камней
		for (int i = 0; i < _rocks->size(); i++)
			_rockСollision(_rocks->at(i));
	};

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
Kicker* _kicker = new Kicker(_gamesetting->wight / 2 - (_gamesetting->wight / 10 )/2 ,_gamesetting->hight -15 ,_gamesetting->wight / 10, 15);
vector <Rock*>* map = new vector<Rock*>;
Ball* _ball = new Ball(

	_gamesetting->range,
	_gamesetting->wight / 2,
	 _gamesetting->hight - 15  - _gamesetting->range,
	_gamesetting->wight,
	_gamesetting->hight,
	map,_kicker,
	_gamesetting->speedx,
	_gamesetting->speedy

);


//отрисовка
void Draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	//камушки
	showRocks(map);

	//бита
	glColor3f(0.2, 0.8, 0.1);
	glRectf(_kicker->pointx, _kicker->pointy, _kicker->pointx + _kicker->wight, _kicker->pointy + _kicker->hight);

	//шарик
	glColor3f(1.0, 0.0, 0.0);
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
		_ball->move();
	Draw();
	glutTimerFunc(5, Timer, 500);

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

			_ball->dx -= _gamesetting->speedx;
			_ball->dy = _gamesetting->speedy;

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
