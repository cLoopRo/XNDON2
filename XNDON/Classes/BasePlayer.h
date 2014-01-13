#pragma once
#include "Engine\XDGridSprite.h"
#include "Engine\XDGridMap.h"
class BasePlayer : public XDGridSprite
{
public:
	bool rFoot;

public:
	TYPE GetType(){	return BASE_PLAYER;	}

	bool flag_earthquake;
	void Update(double _dTime )
	{
		Update_Animation( _dTime );
		Update_Grid_Move( _dTime );
	}

	void Attack( )
	{
		if(Controlled==false ){
			set_Animation( BASH );
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
			set_Animation(QUAKE, &flag_earthquake);
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
/*	
	static XDGridSprite* Create(int _X, int _Y, int _Z ){
		pPlayer->setPosition( _X, _Y, _Z );
		return pPlayer;
	}
*/
	static XDGridSprite* Create(int _X, int _Y, int _Z, GridMap* _map ){
		if ( _map->isEmpty(_X, _Y) ){
			pPlayer->setPosition( _X, _Y, _Z );
			pPlayer->grid_map = _map;
			return pPlayer;
		}
		else
			return NULL;
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
		
		flag_earthquake = false;
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
