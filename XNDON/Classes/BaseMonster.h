#pragma once
#include "Engine\XDSprite.h"
#include "Engine\XDMain.h"

class BaseMonster : public XDSprite
{
/* do by �̽¹� que�� �̿��� �ִϸ��̼� ����*/
private:
	typedef void (BaseMonster::*BMfptr)(void); //�Լ� �������� ť�� ����ϱ� ���� typedef�� ���
	BMfptr _doptr;	//�ִϸ��̼� �Լ��� ����ų �Լ� ������
	queue< BMfptr > _animation_que;	//�Լ� �����͸� ������ ť
	char _dir;	//������ ������ ����
public:

	void Update(double _dTime ) // ������Ʈ
	{
		if(_is_Controlled == false) {
			_time += _dTime; // �ֱ������� �̵��� �ϱ� ���� (�̵� ���̻��� ���� �ֱ� ����)
			if ( _time >= 0.3 ) {
                _time -= 0.3;
				//ť�� ���� �ִ� �κ�
				if(_animation_que.empty()) {
					add_que_animation();
				}
				//�ൿ�� �ϴ� �κ�
				else {
					do_que_animation();
				}
			}
		}	
	}
	void add_que_animation () { //�ش� ��ǥ�� �����ϸ� ������ �ٲ�
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
		switch(_dir) { //�ٲ� ���� ������ ���� �Լ� �����Ϳ� �Լ� ����
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
		_animation_que.push(_doptr); //�����Ϳ� ����
	}

void do_que_animation() { //����� ť�� �����Ų��.
		if(_dir == 'R') {
			reversed = true;
		}
		else if(_dir == 'L') {
			reversed = false;
		}
		// �ø� ����
		(this->*_animation_que.front())(); //�տ� �ִ� �����Ϳ��� �Լ��� ������ ���� �Ѵ�.
		_animation_que.pop(); // ������ �Լ� �����͸� �����Ѵ�.
	}
	//�ൿ�Լ��� ........./////////
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
	//�ൿ�Լ��� ........./////////

/*<----- BaseMonster �� ���� ���� ��ȯ ���� ���� ----->*/
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
/*<----- BaseMonster�� �ִϸ��̼� ���� �Ϸ� ----->*/



};
