#pragma once
//класс игровых натсроек
class GameSetting {

public:

	//экран
	int wight;
	int hight;
	//шарик
	int speedx;
	int speedy;
	//генератор
	int columns;
	int rows;
	int range;
	//тип вводв
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

