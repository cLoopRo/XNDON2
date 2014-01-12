#pragma once
#include "Engine\XDMain.h"
#include "Engine\XDSprite.h"

class BaseMissile : public XDSprite
{
	void Update(double _dTime){	}

	/*<----- BaseMissile �� ���� ���� ��ȯ ���� ���� ----->*/
public:
	static vector<XDSprite*> baseMissiles;
	static void Reserve(int _N){	for (int i=0; i<_N; i++) baseMissiles.push_back( new BaseMissile() );	}
	static XDSprite* Create(int _X, int _Y, int _Z ){
		if ( baseMissiles.empty() )
			baseMissiles.push_back( new BaseMissile() );
		XDSprite* pTmpBaseMissile = *( --baseMissiles.end() );
		baseMissiles.pop_back();
		pTmpBaseMissile->setPosition( _X, _Y, _Z );
		return pTmpBaseMissile;
	}

	void Return( ){
		baseMissiles.push_back( this );
	}

	static void Clear( ){
		for(int i=0; i<baseMissiles.size(); i++)
			delete baseMissiles[i];
		baseMissiles.clear();
	}
/*<----- BaseMissile�� ���� ���� ��ȯ ���� �Ϸ� ----->*/

/*<----- BaseMissile�� �ִϸ��̼� ���� ���� ----->*/
private:
	BaseMissile()
	{
		make_Animation(_T("./assets/img/missile/quake1.png"),
					   _T("./assets/img/missile/quake2.png") );
	}
public:	
	enum STATE{
		MOVE
	};
/*<----- BaseMissile�� �ִϸ��̼� ���� �Ϸ� ----->*/


};
