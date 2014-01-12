#include "Engine\XDScene.h"
#include "BasePlayer.h"
#include "BaseMonster.h"
#include "BaseMissile.h"

class BaseScene : public XDScene
{
public:

	XDSprite* player;
	vector<XDSprite*> monsters;
	BaseScene()
	{
	
		player = BasePlayer::Create(0, 0, 0);
		insertPaintSprite(player);
		
		BaseMonster::Reserve( 20 );
		monsters.push_back( BaseMonster::Create(14,1,0) );
		insertPaintSprite(monsters[0]);
		
	}

	void Update(double _dTime)
	{
		player->Update_Animation(_dTime);
		player->Update(_dTime);
		player->Update_Move(_dTime);
		monsters[0]->Update_Animation(_dTime);
		monsters[0]->Update(_dTime);
		monsters[0]->Update_Move(_dTime);
	}


};