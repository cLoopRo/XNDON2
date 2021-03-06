#pragma once

#include "XDMain.h"
class XDSprite;

class XDScene
{
public:
	virtual void Update(double _dTime) = 0;
	
/*<----- 출력 스프라이트 관리 및 몬스터 생성 부분 구현 ----->*/
public:

	void insertPaintSprite(XDSprite* _pSprite){
		_paint_pSprites.insert(_pSprite);
	}

	void deletePaintSprite(XDSprite* pSprite);

	set<XDSprite*> get_Paint_pSprites(){	return _paint_pSprites;	}
private:
	set<XDSprite*> _paint_pSprites;

/*<----- 출력 및 몬스터 생성 부분 구현 완료 ----->*/
protected:
	XDScene :: XDScene( ){	}
	virtual XDScene::~XDScene( ){	}

};

