#pragma once

#include "XDMain.h"
class XDSprite;

class XDScene
{

/*<----- ��� ��������Ʈ ���� �� ���� ���� �κ� ���� ----->*/
public:
//	virtual XDSprite* CreateSpriteWithType(int _Type) = 0;

	void insertNewPaintSprite(XDSprite* _pSprite)
	{
		_paint_pSprites.insert(_pSprite);
	}

	void DeleteSprite(XDSprite* pSprite);

	set<XDSprite*> get_Paint_pSprites(){	return _paint_pSprites;	}
private:
	set<XDSprite*> _paint_pSprites;

/*<----- ��� �� ���� ���� �κ� ���� �Ϸ� ----->*/
protected:
	XDScene :: XDScene( ){	}
	virtual XDScene::~XDScene( ){	}

};

