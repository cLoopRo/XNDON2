#include "XDScene.h"
#include "XDSprite.h"

void XDScene :: deletePaintSprite(XDSprite* pSprite)
{
	set<XDSprite*>::iterator itr;
	if ( _paint_pSprites.end() == ( itr = _paint_pSprites.find(pSprite) ) )
	{
		// 찾지못했어 없는거 넣을래 빡치게??
	}
	else
	{
		(*itr)->Return( );	_paint_pSprites.erase( itr );
	}
}