#pragma once

#include "XDmain.h"
#include "XDScene.h"

#define LEFT 37
#define UP 38
#define RIGHT 39
#define DOWN 40

class XDSprite;
class XDDirector
{
public:
	static void setScene(XDScene* pScene){	_pScene = pScene;	}
	static XDScene* _pScene;
	
	static int _dTime;
	static int _lastTime;
	static void Update( ); 	
	static bool _keys[256];
	

	/*<----- 화면 출력을 관리 ----->*/
	static HWND hWnd;
	static CachedBitmap *pCBit;
	static void UpdateScreen();
	static void OnPaint(HDC hdc);
	/*<----- 화면 출력을 관리 종료 ----->*/
};

