#pragma once
#include "XDMain.h"
#include "XDSprite.h"
class GridMap;

class XDGridSprite : public XDSprite
{


	enum DIRECTION{ // 현재 이동방향을 나타낸다.
		STOP,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	
protected:
	XDGridSprite()
		: XDSprite()
	{	
		isMoving = false;
		direction = STOP;
	}

	bool isMoving;
	DIRECTION direction;
	static const double base_velocity;
	
	XDVector3<int> grid_current_position;
	XDVector3<int> grid_next_position;

	GridMap* gridMap;

	void move_Left(){
		if ( 0 < grid_current_position.X && !isMoving ){
			isMoving = true;
			grid_next_position.X--;
			velocity.X = -base_velocity*speed;
			direction = LEFT;
		}
	}
	void move_Right(){
		if ( grid_current_position.X < 15 && !isMoving){
			isMoving = true;
			grid_next_position.X++;
			velocity.X = base_velocity*speed;
			direction = RIGHT;
		}

	}
	void move_Up(){
		if ( 0 < grid_current_position.Y && !isMoving ){
			isMoving = true;
			grid_next_position.Y--;
			velocity.Y = -base_velocity*speed;
			direction = UP;
		}
	
	}
	void move_Down(){
		if ( grid_current_position.Y < 15 && !isMoving ){
			isMoving = true;
			grid_next_position.Y++;
			velocity.Y = base_velocity*speed;
			direction = DOWN;
		}
	}
public:
	void Update_Grid_Move(double _dTime)
	{
		XDSprite::Update_Move(_dTime);
		switch ( direction ){
		case LEFT:
			if ( position.X <= grid_next_position.X ){
				position.X = grid_next_position.X;
				grid_current_position.X = grid_next_position.X;
				velocity.X = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case RIGHT:
			if ( grid_next_position.X <= position.X ){
				position.X = grid_next_position.X;
				grid_current_position.X = grid_next_position.X;
				velocity.X = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case UP:
			if ( position.Y <= grid_next_position.Y ){
				position.Y = grid_next_position.Y;
				grid_current_position.Y = grid_next_position.Y;
				velocity.Y = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case DOWN:
			if ( grid_next_position.Y <= position.Y ){
				position.Y = grid_next_position.Y;
				grid_current_position.Y = grid_next_position.Y;
				velocity.Y = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case STOP:
		default:
			break;
		}
	}

};