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

		bool mouseinput);

	~GameSetting();

};

