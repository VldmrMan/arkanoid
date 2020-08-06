#include "pch.h"
#include <iostream>
#include "glut.h"
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

//экранные перемене
static int  wight = 800; //размер окна
static int  hight = 500;
static float  speedx = 3; //скорость мячика
static float  speedy = 3;
//генератор
static int columns = 9; //среднее количество столбцов до генератора
static int row = 5;
bool MouseInput = true; //тип движени (клавиатура (A/W/D) либо мышь)

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
};

vector <Rock*> map; //вектор из камней на поле

vector <Rock*>  generator(vector<Rock*> _vector )
{	
	//генерирует вектор используя случайные числа< изменяет
	int _columns = columns + rand() % 5 - 2; //чуть чуть случайной генерации
	int _row = row + rand() % 3 - 2; //чуть чуть случайной генерации
	_vector.clear(); //так как генератор запускает не  только при первом запуске, но еще и при рестарте
						//очищаем

	for (int i = 1; i < columns; i++)
		for (int j = 1; j< row; j++)
	{

		//формирование новый карты
		Rock* _rock = new Rock(wight / _columns  * i , hight / _row / 2 * j , 40 ,40);
		if ((wight / _columns * i + 40) < wight)
			_vector.push_back(_rock);

	}

	return _vector;
}

class Kicker
{
private:
public:
	float pointx; //якорь 
	float pointy; //якорь 
	float wight;  //ширина
	float hight;  //длина

	Kicker(float _pontex, float _pointy, float _wight, float _hight) {
		pointx = _pontex;
		pointy = _pointy;
		wight = _wight;
		hight = _hight;
	}
};

//так как шарик и бита в 1 экземпляре можно сделать их глобальными

Kicker kicker = Kicker(wight / 2, hight - 15, wight / 10, hight / 50);

class Ball
{

public:

	float x = hight +50 , y, //координаты
		dx, dy, // скорость
		r;		//радиус
	bool active;
	Ball( float r_)
	{

		r = r_;
	}
	
	void move()
	{	
		//проверка на столкновения
		_rocksСollision(map);
		_kickerСollision(kicker);
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
				dy *= -1;

		if (x - r <= 0)
			if (dx < 0)
				dx *= -1;
		if (x + r >= wight)
			if (dx > 0)
				dx *= -1;

		if (y - 4 * r > hight)
		{
			//ппроигрышь => генерая,остановка,активность шарика 
			map = generator(map);
			stopmove();
			active = false;
		}
	}

	void _kickerСollision(Kicker kicker)
	{
		//Проверка столкновения с битой
		if ((y < kicker.pointy && y + r + speedy  > kicker.pointy))
			if (x > kicker.pointx - r && x < kicker.pointx + kicker.wight + r) 
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
			if (_rock->x1 < x + r   && x - r < _rock->x1 + _rock->w)
				if (_rock->y1 < y + r  && y - r < _rock->y1 + _rock->h)
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

	void _rocksСollision(vector <Rock*> _rocks)

	{
		//колизия с камнем для коллекции камней
		for (int i = 0; i < _rocks.size(); i++)
			_rockСollision(_rocks.at(i));
	};
	
};

Ball ball(10); 

void showRock(Rock* _rock)
{
	//отображает камень< используется в Drow()
	if (_rock->live)
	glRectf(_rock->x1, _rock->y1, _rock->x1 + _rock->w, _rock->y1 + _rock->h);
}

void showRocks(vector <Rock*> _rocks) {

	//обход вектора с камнями  и отображение в drow()
	for (int i = 0; i < _rocks.size(); i++)
	{
		showRock(_rocks.at(i));
	}
};

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//камушки
	showRocks(map);
	   
	//бита
	glColor3f(0.2, 0.8, 0.1);
	glRectf(kicker.pointx, kicker.pointy, kicker.pointx + kicker.wight, kicker.pointy + kicker.hight);

	//шарик
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
	{
		glVertex2f(ball.x + ball.r*sin(i), ball.y + ball.r*cos(i));
	}
	   	 
	glEnd();
	glutSwapBuffers();
}

void Timer(int)
{
	if (ball.active)
		ball.move();
	Draw();
	glutTimerFunc(5, Timer, 500);
}

void Mouse(int ax, int ay)
{
	//курсор мыши
	int mouse_x = ax;
	kicker.pointx = ax - kicker.wight / 2; //координаты биты

	if (!ball.active)
	{
		ball.x = kicker.pointx + kicker.wight / 2; //привязка шарика к бите
		ball.y = kicker.pointy - ball.r;
	}


}

void MousePress(int button, int state, int x, int y)
{
	//нажатие левой клавиши мыши
	if (button == GLUT_LEFT_BUTTON && !ball.active)
	{

		ball.active = true;
		ball.dx = -speedx;
		ball.dy = -speedy;
	}

}

void processNormalKeys(unsigned char key, int x, int y) {
	//выход через esc
	if (key == 27)
		exit(0);

	if (key == 'd') //движение вправо
	{
		kicker.pointx += 50;
		if (!ball.active)
		{
			ball.x = kicker.pointx + kicker.wight / 2; //привязка шарика к бите
			ball.y = kicker.pointy - ball.r;
		}

	}


	if (key == 'a') // движение влево
	{
		kicker.pointx -= 50;
		if (!ball.active)
		{
			ball.x = kicker.pointx + kicker.wight / 2; //привязка шарика к бите
			ball.y = kicker.pointy - ball.r;
		}
	}


	if (key == 'w') // запуск шариа
	{
		ball.active = true;
		ball.dx = -speedx;
		ball.dy = -speedy;

	}

}

void Init()
{
	glClearColor(0.5, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, wight, hight, 0, 1, 0); //ориентация экрана
}

int main(int argc, char **argv) {

	map = generator(map); // первая генерация поля

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(wight, hight);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Acranoid");
	glutDisplayFunc(Draw);
	glutTimerFunc(0, Timer, 0);


	if (MouseInput) {  //опциональное включения игры с клавиатуры
		glutPassiveMotionFunc(Mouse);
		glutMouseFunc(MousePress);
	}
	else {
		glutKeyboardFunc(processNormalKeys);
		}

	Init();
	glutMainLoop();
	return 0;


}