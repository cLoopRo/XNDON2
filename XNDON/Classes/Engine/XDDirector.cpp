#include "XDDirector.h"
#include "XDSprite.h"

XDScene* XDDirector::_pScene = NULL;
HWND XDDirector::hWnd = NULL;
CachedBitmap* XDDirector::pCBit = NULL;
int XDDirector::_dTime = 0;
int XDDirector::_lastTime = 0;
bool XDDirector::_keys[256] = { 0 };	

void XDDirector::Update( ){
	double dTime = _dTime/1000.0;
	_pScene->Update(dTime);
	XDDirector::UpdateScreen();
}
	
void XDDirector::OnPaint(HDC hdc){
	Graphics G(hdc);
	
	if ( pCBit == NULL) {
		XDDirector::UpdateScreen();
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

	//격자그리기
	Color *color = new Color();
	Pen *pen = new Pen(*color, 1.0);
	int x1, y1, x2, y2;

	x1 = 0; y1 = 130; x2 = 960; y2 = 130;
	for(int i = 0; i < 7; i++) {
		memG->DrawLine(pen, x1, y1, x2, y2);
		if(i&1) {y1 += 42; y2 += 42;}
		else {y1 += 43; y2 += 43;}
	}
	x1 = 0; y1 = 130; x2 = 0; y2 = 385;
	for(int i = 0; i < 17; i++) {
		memG->DrawLine(pen, x1, y1, x2, y2);
		x1 += 60; x2 += 60;
	}
		
	set<XDSprite*> sprites = _pScene->get_Paint_pSprites();
	// sort ( sprites );s 나중에 고쳐라 
	for(set<XDSprite*>::iterator itr = sprites.begin() ; itr != sprites.end(); itr++ )
		(*itr)->draw_Sprite(*memG);

	TCHAR szWidth1[128];
	TCHAR szWidth2[128];
	Font F(L"굴림",20,FontStyleRegular,UnitPixel);
		SolidBrush B(Color(0,0,0));
	
	_stprintf(szWidth1, TEXT("%.1lf"), 1000.0/_dTime );
	_stprintf(szWidth2, TEXT("%d"), sprites.size() );
	memG->DrawString(szWidth1,-1,&F,PointF(0,0),&B);
	memG->DrawString(szWidth2,-1,&F,PointF(0,20),&B);


	if ( pCBit)  {
		delete pCBit;
	}
		
	pCBit=new CachedBitmap(pBit,&G);
	delete pBit;
	delete memG;
	InvalidateRect(hWnd,NULL,FALSE);
}

