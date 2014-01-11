#include "Engine\XDSprite.h"

class Player : public XDSprite
{
public:
	Player()
	{
		add_Image( _T("./assets/img/player/player.png") );
		make_Animation(_T("./assets/img/player/new_player_bash1.png"), 	_T("./assets/img/player/new_player_bash1.png") );
	}
	void Delete(){
	
	}

	~Player(){	}




};