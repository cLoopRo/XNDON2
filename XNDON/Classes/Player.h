#include "Engine\XDSprite.h"

class Player : public XDSprite
{
public:
	Player()
	{
		make_Animation( _T("./assets/img/player/player.png") );
		make_Animation(_T("./assets/img/player/new_player_bash1.png"), 	_T("./assets/img/player/new_player_bash2.png") );
	}
	void Delete(){
	
	}
	void Update(double _dTime )
	{
		if ( XDDirector::_keys[UP] ){
			_realPos.Y++;
			Attack();
		}
		if ( XDDirector::_keys[DOWN] ){
			set_Animation(0);
			_realPos.Y--;
		}
		

	}


	void Attack( )
	{
		set_Animation(1);
		
	}

	~Player(){	}




};