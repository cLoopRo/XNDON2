#include "Engine\XDSprite.h"

class BasePlayer : public XDSprite
{
public:
	bool rFoot;
	enum state {
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
	BasePlayer()
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

		_gridPos = XDVector3<int>(0, 0, 0);
		_realPos = XDVector3<double>(0.0, 0.0, 0.0);
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
		
	}

	void Delete(){
	
	}

	bool _attack_flag;
	void Update(double _dTime )
	{
		if ( XDDirector::_keys['Z'] )
		{
			Attack();
		}
		if ( XDDirector::_keys['X'] )
		{
			Kick();
		}
		if ( XDDirector::_keys['C'] )
		{
			Quake();
		}
		if ( XDDirector::_keys['V'] )
		{
			Guard();
		}
		if ( XDDirector::_keys[VK_SPACE] )
		{
			Jump();
		}
		if ( XDDirector::_keys[VK_LEFT]  ) // left
		{
			reversed=true;
			moveLeft();
		}
		if ( XDDirector::_keys[VK_UP]  ) // up
		{
			moveUp();
			Walk();
		}
		if ( XDDirector::_keys[VK_RIGHT] ) // right
		{
			reversed=false;
			moveRight();
			Walk();
		}
		if ( XDDirector::_keys[VK_DOWN] ) // down
		{
			moveDown();
			Walk();
		}
//		Update_Move(_dTime);
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
	
};
