#include "main.h"
#include "XDCube.h"

XDCube::XDCube() {
	
}

XDCube::~XDCube() {

}

XDCube::XDCube(Coord3 _Init, Coord3 _End) 
	: CubeInit(_Init), CubeEnd(_End) {
}

XDCube::XDCube(double _Init_x, double _Init_y, double _Init_z,
	double _End_x, double _End_y, double _End_z)
	: CubeInit(_Init_x, _Init_y, _Init_z), CubeEnd(_End_x, _End_y, _Init_z) {
}

bool CollisionCheck(const XDCube& _LC,const XDCube& _RC) {
	bool XCollision = (_RC.CubeInit.X >= _LC.CubeEnd.X || _LC.CubeInit.X >= _RC.CubeEnd.X);
	bool YCollision = (_RC.CubeInit.Y >= _LC.CubeEnd.Y || _LC.CubeInit.Y >= _RC.CubeEnd.Y);
	bool ZCollision = (_RC.CubeInit.Z >= _LC.CubeEnd.Z || _LC.CubeInit.Z >= _RC.CubeEnd.Z);
	return !(XCollision || YCollision || ZCollision);
}