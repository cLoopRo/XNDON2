#include "Engine\XDScene.h"
#include "BasePlayer.h"
#include "BaseMonster.h"
#include "BaseMissile.h"

class BaseScene : public XDScene
{
public:

	BasePlayer* player;
	vector<BaseMonster*> monsters;
	BaseScene()
	{
		player = new BasePlayer();
		insertPaintSprite(player);
		monsters.push_back(new BaseMonster() );
		monsters[0]->_realPos = XDVector3<double>(14,1,0);
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