#pragma once
const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 6;

class XDSprite;

enum TYPE{
	EMPTY = 0,
	BASE_PLAYER,
	BASE_MONSTER,
	BASE_MISSILE,
};

struct Grid{
	XDSprite* pSprite;
	TYPE type;
};


class GridMap
{
public:
	GridMap(){	
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				Cell[i][j].type = EMPTY;
				Cell[i][j].pSprite = NULL;
			}
		}
	}

	inline bool isEmpty(int _X, int _Y){	return ( Cell[_X][_Y].type == NULL ); }
	inline TYPE getState(int _X, int _Y){	return Cell[_X][_Y].type;	}
	inline XDSprite* getSprite(int _X, int _Y){	return Cell[_X][_Y].pSprite;	}
	void setState(int _X, int _Y, TYPE _Type, XDSprite* _pSprite){
		Cell[_X][_Y].type = _Type;
		Cell[_X][_Y].pSprite = _pSprite;
	}
	void resetState(int _X, int _Y){	
		Cell[_X][_Y].type = EMPTY;
		Cell[_X][_Y].pSprite = NULL;
	}
	void moveSprite(int _srcX, int _srcY, int _desX, int _desY){
		setState(_desX, _desY, getState(_srcX, _srcY), getSprite(_srcX, _srcY) ); 
		resetState(_srcX, _srcY);
	}
	

private:
	Grid Cell[GRID_WIDTH][GRID_HEIGHT];

};

