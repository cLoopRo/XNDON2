#pragma once
#include "Engine\XDSprite.h"
#include "Engine\XDMain.h"

class BaseMonster : public XDSprite
{
/* do by 이승민 que를 이용한 애니메이션 설정*/
private:
	typedef void (BaseMonster::*BMfptr)(void); //함수 포인터형 큐를 사용하기 위해 typedef를 사용
	BMfptr _doptr;	//애니메이션 함수를 가르킬 함수 포인터
	queue< BMfptr > _animation_que;	//함수 포인터를 저장할 큐
	char _dir;	//방향을 저장할 변수
public:

	void Update(double _dTime ) // 업데이트
	{
		if(_is_Controlled == false) {
			_time += _dTime; // 주기적으로 이동을 하기 위해 (이동 사이사이 텀을 주기 위해)
			if ( _time >= 0.3 ) {
                _time -= 0.3;
				//큐에 집어 넣는 부분
				if(_animation_que.empty()) {
					add_que_animation();
				}
				//행동을 하는 부분
				else {
					do_que_animation();
				}
			}
		}	
	}
	void add_que_animation () { //해당 좌표에 도달하면 방향을 바꿈
		if(_gridPos.X == 4 && _gridPos.Y == 1) { 
			_dir = 'D';
		}
		if(_gridPos.X == 4 && _gridPos.Y == 4) {
			_dir = 'R';
		}
		if(_gridPos.X == 8 && _gridPos.Y == 4) {
			_dir = 'U';
		}
		if(_gridPos.X == 8 && _gridPos.Y == 1) {
			_dir = 'L';
		}
		switch(_dir) { //바꾼 방향 정보를 토대로 함수 포인터에 함수 저장
		case 'D':
			_doptr = &BaseMonster::WalkDown;
			break;
		case 'U':
			_doptr = &BaseMonster::WalkUp;
			break;
		case 'R':
			_doptr = &BaseMonster::WalkRight;
			break;
		case 'L':
			_doptr = &BaseMonster::WalkLeft;
			break;
		}
		_animation_que.push(_doptr); //포인터에 저장
	}

void do_que_animation() { //저장된 큐를 실행시킨다.
		if(_dir == 'R') {
			reversed = true;
		}
		else if(_dir == 'L') {
			reversed = false;
		}
		// 플립 실행
		(this->*_animation_que.front())(); //앞에 있는 포인터에서 함수를 가져와 실행 한다.
		_animation_que.pop(); // 실행한 함수 포인터를 제거한다.
	}
	//행동함수들 ........./////////
	void WalkDown() {
		moveDown();
		set_Animation(MOVE);
	}
	void WalkUp() {
		moveUp();
		set_Animation(MOVE);
	}
	void WalkLeft() {
		moveLeft();
		set_Animation(MOVE);
	}
	void WalkRight() {
		moveRight();
		set_Animation(MOVE);
	}
	//행동함수들 ........./////////

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
/*<----- BaseMonster의 애니메이션 관리 완료 ----->*/



};
