#pragma once
//����� ������
class Ball
{
public:
	float	x, y, //����������
			dx = 0, dy = 0, // ��������
			r;		//������

	float wight;
	float hight;

	bool active = false; //�������� �� �����
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
		//���������� �������� (��������)

		x += dx;
		y += dy;

	}

	void stopmove()
	{
		//������� �������� ���� (��� �������������)
		dx = 0;
		dy = 0;
	}
	   
};
