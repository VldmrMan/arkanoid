#pragma once
//класс шарика
class Ball
{
public:
	float	x, y, //координаты
			dx = 0, dy = 0, // скорость
			r;		//радиус

	float wight;
	float hight;

	bool active = false; //движется ли шарик
	Ball(float r, float x, float y,
		float wight, float hight,

		float speedx, float speedy)
	{
		this->r = r;
		this->x = x;
		this->y = y;

		this->wight = wight;
		this->hight = hight;
	}

	void move()
	{		
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
	   
};
