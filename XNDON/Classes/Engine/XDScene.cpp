#include "XDScene.h"
#include "XDSprite.h"

void XDScene :: DeleteSprite(XDSprite* pSprite)
{
	set<XDSprite*>::iterator itr;
	if ( _paint_pSprites.end() == ( itr = _paint_pSprites.find(pSprite) ) )
	{
		// ã�����߾� ���°� ������ ��ġ��??
	}
	else
	{
			(*itr)->Delete( );		_paint_pSprites.erase( itr );
	}
}