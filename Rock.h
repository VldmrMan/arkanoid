#pragma once

using namespace std;
class Rock {
//����� ������ �� ����
public:
	float x1;  //������� ����� �����
	float y1;
	float h;   //������ � �����
	float w;
	bool live; //��� ��(������������ �� �� ����)
	Rock(float x1, float y1, float h, float w);
	~Rock();
};
