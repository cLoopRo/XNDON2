#pragma once

#include "XDmain.h"
#include "XDScene.h"

class XDSprite;
class XDDirector
{
public:
	static void setScene(XDScene* pScene){	_pScene = pScene;	}
	static XDScene* _pScene;
	
	static int _dTime;
	static int _lastTime;
	static void Update( ){ 	}

	/*<----- ȭ�� ����� ���� ----->*/
	static HWND hWnd;
	static CachedBitmap *pCBit;
	static void UpdateScreen();
	static void OnPaint(HDC hdc);
	/*<----- ȭ�� ����� ���� ���� ----->*/
};

