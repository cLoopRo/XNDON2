#pragma once
const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 6;

class XDSprite;

enum GRID{
	EMPTY,
	BASE_PLAYER,
	BASE_MONSTER,
	BASE_MISSLE,
};

struct Grid{
	XDSprite* pSprite;
	GRID State;
};


class GridMap
{
public:
	GridMap(){	
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				Cell[i][j].State = EMPTY;
				Cell[i][j].pSprite = NULL;
			}
		}
	}

	inline GRID getState(int _X, int _Y){	return Cell[_X][_Y].State;	}
	inline XDSprite* getSprite(int _X, int _Y){	return Cell[_X][_Y].pSprite;	}
	void setState(int _X, int _Y, GRID _State, XDSprite* _pSprite){
		Cell[_X][_Y].State = _State;
		Cell[_X][_Y].pSprite = _pSprite;
	}
	inline void resetState(int _X, int _Y){	
		Cell[_X][_Y].State = EMPTY;
		Cell[_X][_Y].pSprite = NULL;
	}

private:
	Grid Cell[16][6];

};

