#pragma once
#include "Engine\XDSprite.h"

class BaseFire : public XDSprite
{
public:

	void Update(double _dTime )
	{
		_time += _dTime;
		if ( _time >= 1.0 )
		{

		}
	
	}

	


/*<----- BaseFire 의 예약 생성 반환 관리 시작 ----->*/
public:
	static vector<XDSprite*> baseFires;
	static void Reserve(int _N){	for (int i=0; i<_N; i++) baseFires.push_back(new BaseFire() );	}
	static XDSprite* Create(int _X, int _Y, int _Z ){
		if ( baseFires.empty() )
			baseFires.push_back( new BaseFire() );
		XDSprite* pTmpBaseFire = *( --baseFires.end() );
		baseFires.pop_back();
		pTmpBaseFire->setPosition( _X, _Y, _Z );
		return pTmpBaseFire;
	}

	void Return( ){
		baseFires.push_back( this );
	}

	static void Clear( ){
		for(unsigned int i=0; i<baseFires.size(); i++)
			delete baseFires[i];
		baseFires.clear();
	}
/*<----- BaseFire의 예약 생성 반환 관리 완료 ----->*/

/*<----- BaseFire의 애니메이션 관리 시작 ----->*/
private:
	BaseFire()
	{
		make_Animation(_T("./assets/img/gob/new_goblin.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_walk.png"),
					   _T("./assets/img/gob/new_goblin.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_attack1.png"),
					   _T("./assets/img/gob/new_goblin_attack2.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_walk.png"),
					   _T("./assets/img/gob/new_goblin_walk.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_attacked.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_death.png") );	
	}
public:	
	enum STATE{
		STAND,
		MOVE,
		ATTACK,
		JUMP,
		ATTACKED,
		DEAD,
	};
/*<----- BaseFire의 애니메이션 관리 완료 ----->*/



};
