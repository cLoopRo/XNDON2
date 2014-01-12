#pragma once
#include "Engine\XDGridSprite.h"
#include "Engine\XDGridMap.h"
class BasePlayer : public XDGridSprite
{
public:



	bool rFoot;



public:
	
	bool _attack_flag;
	void Update(double _dTime )
	{
		if ( XDDirector::_keys['Z'] ){
			Attack();
		}
		else if ( XDDirector::_keys['X'] ){
			Kick();
		}
		else if ( XDDirector::_keys['C'] ){
			Quake();
		}
		else if ( XDDirector::_keys['V'] ){
			Guard();
		}
		else if ( XDDirector::_keys[VK_SPACE] ){
			Jump();
		}
		else if ( XDDirector::_keys[VK_LEFT]  ){
			reversed=true;
			gridMap->resetState(_gridPos.X,_gridPos.Y);
			move_Left();
			gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER,this);
			Walk();
		}
		else if ( XDDirector::_keys[VK_UP]  ){
			gridMap->resetState(_gridPos.X,_gridPos.Y);
			move_Up();
			gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER,this);
			Walk();
		}
		else if ( XDDirector::_keys[VK_RIGHT] ){
			reversed=false;
		//	gridMap->resetState(_gridPos.X,_gridPos.Y);
			move_Right();
		//	gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER);
			Walk();
		}
		else if ( XDDirector::_keys[VK_DOWN] ){
		//	gridMap->resetState(_gridPos.X,_gridPos.Y);
			move_Down();
		//	gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER);
			Walk();
		}
		else
			stop();
	}

	void Attack( )
	{
		if(Controlled==false ){
			set_Animation(BASH);
			Controlled=true;


		}
	}
	void Kick()
	{
		if(Controlled==false ){
			set_Animation(KICK);
			Controlled=true;
		}
	}
	void Walk()
	{
		if(Controlled==false ){
			if(rFoot){
				set_Animation(WALK);
				Controlled=true;
			}
			else{
				set_Animation(WALK2);
				Controlled=true;
			}
			rFoot = !rFoot;
		}
	}
	void Jump()
	{
		if(Controlled==false ){
			set_Animation(JUMP);
			Controlled=true;
		}
	}
	void Quake()
	{
		if(Controlled==false ){
			set_Animation(QUAKE);
			Controlled=true;
		}
	}
	void Guard()
	{
		if(Controlled==false ){
			set_Animation(GUARD);
			Controlled=true;
		}
	}

	~BasePlayer(){	}





/*<----- 플레이어 생성 및 메모리 관리 ----->*/
	static XDGridSprite* pPlayer;
	static void Create_Player(){	pPlayer = new BasePlayer();	}
	static XDGridSprite* Create(int _X, int _Y, int _Z ){
		pPlayer->setPosition( _X, _Y, _Z );
		return pPlayer;
	}
	static XDGridSprite* Create(int _X, int _Y, int _Z, GridMap* _map ){
		pPlayer->setPosition( _X, _Y, _Z );
		pPlayer->gridMap=_map;
		return pPlayer;
	}
	void Return( ){		}
/*<----- 플레이어 생성 및 메모리 관리 완료 ----->*/


/*<----- 애니메이션 세팅 ----->*/
private :
	BasePlayer( )
	{
		make_Animation( _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_walk1.png"), _T("./assets/img/player/player.png") );
		make_Animation(	_T("./assets/img/player/new_player_walk2.png"), _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_bash1.png"), _T("./assets/img/player/new_player_bash2.png") );
		make_Animation( _T("./assets/img/player/new_player_jump.png"),  _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_kick1.png"), _T("./assets/img/player/new_player_kick2.png"), _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_quake1.png"), _T("./assets/img/player/new_player_quake2.png"), _T("./assets/img/player/new_player_quake3.png") );
		make_Animation( _T("./assets/img/player/new_player_guard.png") );
		make_Animation( _T("./assets/img/player/new_player_death.png") );
	}
	
	enum STATE {
		STAND,
		WALK,
		WALK2,
		BASH,
		JUMP,
		KICK,
		QUAKE,
		GUARD,
		DEATH,
	};
/*<----- 애니메이션 세팅 종료 ----->*/

};
