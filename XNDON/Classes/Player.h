#include "Engine\XDSprite.h"

class Player : public XDSprite
{
public:
	enum Animation{
		STAND,
		WALKING,
		BASH,
	};

	Player()
	{
		make_Animation( _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_walk1.png"), _T("./assets/img/player/player.png"),
						_T("./assets/img/player/new_player_walk2.png"), _T("./assets/img/player/player.png") );
		make_Animation( _T("./assets/img/player/new_player_bash1.png"), _T("./assets/img/player/new_player_bash2.png") );
		
		_gridPos = XDVector3<int>(0.0, 0.0, 0.0);
		_realPos = XDVector3<double>(0.0, 0.0, 0.0);
		_velocity = XDVector3<double>(2.0/1000, 2.0/1000, 0.0);
		_collideBox1 = XDVector3<double>(0.0, 0.0, 0.0);
		_collideBox2 = XDVector3<double>(1.0, 1.0, 1.0);
		_is_Controlled = false;
		setScreenPos();
	}
	void Delete(){
	
	}
	void Update(double _dTime )
	{
		if ( XDDirector::_keys[VK_LEFT]  ) // left
		{
			moveLeft();			
		}
		if ( XDDirector::_keys[VK_UP]  ){
			moveUp();
		}
		else if ( XDDirector::_keys[VK_RIGHT] ) // right
		{
			moveRight();
		}
		else if ( XDDirector::_keys[VK_DOWN] ) // down
		{
			moveDown();
		}
		else if ( XDDirector::_keys['Z'] ){
			Attack();
		}
		else if ( XDDirector::_keys['x'] ){
			Jump();
		}

		Update_Move(_dTime);
	}
	void Jump()
	{

	}

	void Attack( )
	{
		set_Animation(Player::Animation::BASH);
		
	}

	~Player(){	}




};