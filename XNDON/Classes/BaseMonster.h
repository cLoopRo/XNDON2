#include "Engine\XDSprite.h"

class BaseMonster : public XDSprite
{
public:

	void Update(double _dTime )
	{
		_time += _dTime;
		if ( _time >= 1.0 )
		{
			_time -= 1.0;
			set_Animation(MOVE);
			moveLeft();
		}
	
	}

	


/*<----- BaseMonster 의 예약 생성 반환 관리 시작 ----->*/
public:
	static vector<XDSprite*> baseMonsters;
	static void Reserve(int _N){	for (int i=0; i<_N; i++) baseMonsters.push_back(new BaseMonster());	}
	static XDSprite* Create(int _X, int _Y, int _Z ){
		if ( baseMonsters.empty() )
			baseMonsters.push_back( new BaseMonster() );
		XDSprite* pTmpBaseMonster = *( --baseMonsters.end() );
		baseMonsters.pop_back();
		pTmpBaseMonster->setPosition( _X, _Y, _Z );
		return pTmpBaseMonster;
	}

	void Return( ){
		baseMonsters.push_back( this );
	}

	static void Clear( ){
		for(int i=0; i<baseMonsters.size(); i++)
			delete baseMonsters[i];
		baseMonsters.clear();
	}
/*<----- BaseMonster의 예약 생성 반환 관리 완료 ----->*/

/*<----- BaseMonster의 애니메이션 관리 시작 ----->*/
private:
	BaseMonster()
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
/*<----- BaseMonster의 애니메이션 관리 완료 ----->*/



};
