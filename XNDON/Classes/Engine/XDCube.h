#pragma once
#include "XDMain.h"

struct Coord3
{
	Coord3(){}
	~Coord3(){	}
	Coord3(int _X, int _Y, int _Z): X(_X), Y(_Y), Z(_Z)
	{	}
	int X, Y, Z;

};


class XDCube {
public:
	XDCube();
	XDCube(Coord3 _Init, Coord3 _End);
	XDCube(double _Init_x, double _Init_y, double _Init_z, double _End_x, double _End_y, double _End_z);

	friend bool CollisionCheck(const XDCube& _LC, const XDCube& _RC);

	~XDCube();

private:
	Coord3 CubeInit, CubeEnd;
	//Init�� xyz ���� x, y, z�� �ּ��� ��������, End�� �� �ݴ븦 ����ŵ�ϴ�.
};