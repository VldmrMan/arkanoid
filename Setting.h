#pragma once
//����� ������� ��������
class GameSetting {

public:
	//�����
	int wight;
	int hight;
	//�����
	int speedx;
	int speedy;
	//���������
	int columns;
	int rows;
	int range;
	//��� �����
	bool mouseinput;

	

	GameSetting(

		int wight,
		int hight,

		int speedx,
		int speedy,
		int range,

	int columns,
	int rows,

	bool mouseinput

	)

	{
		this->wight = wight;
		this->hight = hight;

		this->speedx = speedx;
		this->speedy = speedy;
		this->range = range;

		this->columns = columns;
		this->rows = rows;

		this->mouseinput = mouseinput;

	};

	~GameSetting() {
		std::cout << "Distructor GameSetting complited" << std::endl;
	};

};