#pragma once
#include "Engine\XDGridSprite.h"
#include "Engine\XDMain.h"
#include "Engine\XDGridMap.h"

class BaseMonster : public XDGridSprite
{
public:
	TYPE GetType( ){	return BASE_MONSTER;	}

/* do by �̽¹� que�� �̿��� �ִϸ��̼� ����*/
private:
	typedef void (BaseMonster::*BMfptr)(void); //�Լ� �������� ť�� ����ϱ� ���� typedef�� ���
	BMfptr _doptr;	//�ִϸ��̼� �Լ��� ����ų �Լ� ������
	deque< BMfptr > _animation_que;	//�Լ� �����͸� ������ ť
	char _dir;	//������ ������ ����
public:

	void Update(double _dTime ) // ������Ʈ
	{
		if(isMoving == false){//_is_Controlled == false) {
			_time += _dTime; // �ֱ������� �̵��� �ϱ� ���� (�̵� ���̻��� ���� �ֱ� ����)
			if ( _time >= 0.3 ) {
                _time -= 0.3;
				if(!_animation_que.empty()) {				
					do_que_pattern();
				}
				pattern_make();				
			}
		}	
	}
	void pattern_make () { //�������� ��ȸ
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
	//�ൿ�Լ��� ........./////////
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
	//�ൿ�Լ��� ........./////////
	// ť�� �Լ��� �ִ� �Լ��� //
	//ť ���� �Լ���
	void add_que_pattern (BMfptr _nextpattern, int time = 1) {
		for(int i = 0 ; i < time ; i ++) {
			_animation_que.push_back(_nextpattern);
		}
	}
	void do_que_pattern () {
		(this->*_animation_que.front()) ();
		_animation_que.pop_front();
	}
	/*<----- BaseMonster �� ���� ���� ��ȯ ���� ���� ----->*/
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
/*<----- BaseMonster�� ���� ���� ��ȯ ���� �Ϸ� ----->*/

/*<----- BaseMonster�� �ִϸ��̼� ���� ���� ----->*/
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
/*<----- BaseMonster�� asd ���� �Ϸ� ----->*/



};