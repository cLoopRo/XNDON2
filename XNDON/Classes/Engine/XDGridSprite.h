#pragma once
#include "XDMain.h"
#include "XDSprite.h"
#include "XDGridMap.h"

class XDGridSprite : public XDSprite
{
public:

	void Update(double _dTime) = 0;
	TYPE virtual GetType( ) = 0;

	enum DIRECTION{ // 현재 이동방향을 나타낸다.
		STOP,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
public:	
	GridMap* grid_map;
	
protected:
	XDGridSprite()
		: XDSprite()
	{	
		isMoving = false;
		direction = STOP;
	}
public:	
	bool isMoving;
	DIRECTION direction;
	static const double base_velocity;
	
	XDVector3<int> grid_current_position;
	XDVector3<int> grid_next_position;
public:
	void setPosition(int _X, int _Y, int _Z ){
		XDSprite::setPosition(_X, _Y, _Z);
		grid_current_position.setPosition(_X,_Y,_Z);
		grid_next_position.setPosition(_X,_Y,_Z);
	}

public:
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
		if ( grid_current_position.Y < 5 && !isMoving ){
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
			if ( position.X <= grid_next_position.X ){ // 넘어갔을때 이동종료지점				
				grid_map->moveSprite( grid_current_position.X, grid_current_position.Y, grid_next_position.X, grid_next_position.Y); 
				position.X = grid_next_position.X;
				grid_current_position.X = grid_next_position.X;
				velocity.X = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case RIGHT:
			if ( grid_next_position.X <= position.X ){
				grid_map->moveSprite( grid_current_position.X, grid_current_position.Y, grid_next_position.X, grid_next_position.Y); 
				position.X = grid_next_position.X;
				grid_current_position.X = grid_next_position.X;
				velocity.X = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case UP:
			if ( position.Y <= grid_next_position.Y ){
				grid_map->moveSprite( grid_current_position.X, grid_current_position.Y, grid_next_position.X, grid_next_position.Y); 
				position.Y = grid_next_position.Y;
				grid_current_position.Y = grid_next_position.Y;
				velocity.Y = 0.0;
				direction = STOP;
				isMoving = false;
			}
			break;
		case DOWN:
			if ( grid_next_position.Y <= position.Y ){
				grid_map->moveSprite( grid_current_position.X, grid_current_position.Y, grid_next_position.X, grid_next_position.Y); 
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

	void draw_Sprite(Graphics &G)
	{
		XDSprite::draw_Sprite(G);

		TCHAR szWidth[128];
		Font F(L"굴림",20,FontStyleRegular,UnitPixel);
		SolidBrush B(Color(0,0,0));
		_stprintf(szWidth, TEXT("%d %d "), grid_current_position.X, grid_current_position.Y );
		G.DrawString(szWidth,-1,&F,PointF(_screenPos.X + 65, _screenPos.Y + 25),&B);
	
	}

};