#include "XDDirector.h"
#include "XDSprite.h"

XDScene* XDDirector::_pScene = NULL;
HWND XDDirector::hWnd = NULL;
CachedBitmap* XDDirector::pCBit = NULL;
int XDDirector::_dTime = 0;
int XDDirector::_lastTime = 0;
	

void XDDirector::OnPaint(HDC hdc){
	Graphics G(hdc);
	
	if ( pCBit == NULL) {
		UpdateScreen();
	}
	
	G.DrawCachedBitmap(pCBit,0,0);
}

void XDDirector::UpdateScreen()
{
	Graphics G(hWnd);
	RECT crt;
	GetClientRect(hWnd,&crt);
	Bitmap *pBit=new Bitmap(crt.right,crt.bottom,&G);
	Graphics *memG=new Graphics(pBit);
	memG->FillRectangle(&SolidBrush(Color(255,255,255)),0,0,crt.right,crt.bottom);
		
	set<XDSprite*> sprites = _pScene->get_Paint_pSprites();
	// sort ( sprites );s 나중에 고쳐라 

	for(set<XDSprite*>::iterator itr = sprites.begin() ; itr != sprites.end(); itr++ )
		(*itr)->draw_Sprite(*memG);

		if (pCBit) {
		delete pCBit;
	}

	pCBit=new CachedBitmap(pBit,&G);
	delete pBit;
	delete memG;
	InvalidateRect(hWnd,NULL,FALSE);
}

