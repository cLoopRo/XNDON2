#pragma once
#include "Engine\XDGridSprite.h"
#include "Engine\XDMain.h"
#include "Engine\XDGridMap.h"

class BaseMonster : public XDGridSprite
{
public:
	TYPE GetType( ){	return BASE_MONSTER;	}

/* do by 이승민 que를 이용한 애니메이션 설정*/
private:
	typedef void (BaseMonster::*BMfptr)(void); //함수 포인터형 큐를 사용하기 위해 typedef를 사용
	BMfptr _doptr;	//애니메이션 함수를 가르킬 함수 포인터
	deque< BMfptr > _animation_que;	//함수 포인터를 저장할 큐
	char _dir;	//방향을 저장할 변수
public:

	void Update(double _dTime ) // 업데이트
	{
		if(isMoving == false){//_is_Controlled == false) {
			_time += _dTime; // 주기적으로 이동을 하기 위해 (이동 사이사이 텀을 주기 위해)
			if ( _time >= 0.3 ) {
                _time -= 0.3;
				if(!_animation_que.empty()) {				
					do_que_pattern();
				}
				pattern_make();				
			}
		}	
	}
	void pattern_make () { //랜덤으로 배회
		int _rand;
		int i = 0;
		srand( clock() );
		while( i < 3 ) {
			_rand = rand()%4;
			if(_rand == 0) {
				_doptr = &BaseMonster::WalkDown;
				add_que_pattern(_doptr);
			}
			if(_rand == 1) {
				_doptr = &BaseMonster::WalkRight;
				add_que_pattern(_doptr);
			}
			if(_rand == 2) {
				_doptr = &BaseMonster::WalkLeft;
				add_que_pattern(_doptr);
			}
			if(_rand == 3) {
				_doptr = &BaseMonster::WalkUp;
				add_que_pattern(_doptr);
			}
			i++;
		}
		_doptr = &BaseMonster::Attack;
		add_que_pattern(_doptr);
	}
	//행동함수들 ........./////////
	void WalkDown() {
//		gridMap->resetState(_gridPos.X,_gridPos.Y);
		move_Down();
//		gridMap->setState(_gridPos.X,_gridPos.Y,BASE_MONSTER);
		set_Animation(MOVE);
	}
	void WalkUp() {
//		gridMap->resetState(_gridPos.X,_gridPos.Y);
		move_Up();
//		gridMap->setState(_gridPos.X,_gridPos.Y,BASE_MONSTER);
		set_Animation(MOVE);
	}
	void WalkLeft() {
		reversed = false;
//		gridMap->resetState(_gridPos.X,_gridPos.Y);
		move_Left();
//		gridMap->setState(_gridPos.X,_gridPos.Y,BASE_MONSTER);
		set_Animation(MOVE);
	}
	void WalkRight() {
		reversed = true;
//		gridMap->resetState(_gridPos.X,_gridPos.Y);
		move_Right();
//		gridMap->setState(_gridPos.X,_gridPos.Y,BASE_MONSTER);
		set_Animation(MOVE);
	}
	void Attack () {
		set_Animation(ATTACK);
		_time -= 0.3;
	}
	void Attacked() {
		_animation_que.clear();
		set_Animation(ATTACKED);
		_time -= 0.3;
	}
	//행동함수들 ........./////////
	// 큐에 함수를 넣는 함수들 //
	//큐 관리 함수들
	void add_que_pattern (BMfptr _nextpattern, int time = 1) {
		for(int i = 0 ; i < time ; i ++) {
			_animation_que.push_back(_nextpattern);
		}
	}
	void do_que_pattern () {
		(this->*_animation_que.front()) ();
		_animation_que.pop_front();
	}
	/*<----- BaseMonster 의 예약 생성 반환 관리 시작 ----->*/
public:
	static vector<XDGridSprite*> baseMonsters;
	static void Reserve(int _N){	for (int i=0; i<_N; i++) baseMonsters.push_back(new BaseMonster());	}
	static XDGridSprite* Create(int _X, int _Y, int _Z ){
		if ( baseMonsters.empty() )
			baseMonsters.push_back( new BaseMonster() );
		XDGridSprite* pTmpBaseMonster = *( --baseMonsters.end() );
		baseMonsters.pop_back();
		pTmpBaseMonster->setPosition( _X, _Y, _Z );
		return pTmpBaseMonster;
	}
	static XDGridSprite* Create(int _X, int _Y, int _Z, GridMap* _map ){
		if ( baseMonsters.empty() )
			baseMonsters.push_back( new BaseMonster() );
		XDGridSprite* pTmpBaseMonster = *( --baseMonsters.end() );
		baseMonsters.pop_back();
		pTmpBaseMonster->setPosition( _X, _Y, _Z );
		pTmpBaseMonster->grid_map=_map;
		return pTmpBaseMonster;
	}

	void Return( ){
		baseMonsters.push_back( this );
	}

	static void Clear( ){
		for(unsigned int i=0; i<baseMonsters.size(); i++)
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
		_dir = 'L';
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
/*<----- BaseMonster의 asd 관리 완료 ----->*/



};