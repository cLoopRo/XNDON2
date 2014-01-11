#include "Engine\XDSprite.h"

class Player : public XDSprite
{
public:
	Player()
	{
		enum{
			STAND,
			WALK,
			BASH,
			JUMP,
			KICK,
			QUAK
		};
		make_Animation( _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_walk1.png"), _T("./assets/img/player/player.png"),
						_T("./assets/img/player/new_player_walk2.png"), _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_bash1.png"), _T("./assets/img/player/new_player_bash2.png") );
		

		_gridPos = XDVector3<int>(0, 0, 0);
		_realPos = XDVector3<double>(0.0, 0.0, 0.0);
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
		_collideBox1 = XDVector3<double>(0.0, 0.0, 0.0);
		_collideBox2 = XDVector3<double>(1.0, 1.0, 1.0);
		_is_Controlled = false;
		setScreenPos();
	}
	void Delete(){
	
	}

	bool _attack_flag;
	void Update(double _dTime )
	{
		if ( _attack_flag == true )
		;//	Attack();

		if ( XDDirector::_keys[VK_CONTROL] ){
			Attack();	
		}
		else if ( XDDirector::_keys[37]  ) // left
		{
			moveLeft();
		}
		else if ( XDDirector::_keys[38]  ) // up
		{
			moveUp();
		}
		else if ( XDDirector::_keys[39] ) // right
		{
			moveRight();
		}
		else if ( XDDirector::_keys[40] ) // down
		{
			moveDown();
		}
		else {
//			set_Animation( 2 );	
		}
		Update_Move(_dTime);
	}


	void Attack( )
	{
		_attack_flag = false;
		set_Animation( 2, &_attack_flag );

	}

	~Player(){	}




};