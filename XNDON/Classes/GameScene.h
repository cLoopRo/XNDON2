#include "Engine\XDScene.h"
#include "Player.h"
#include "BaseMonster.h"

class GameScene : public XDScene
{
public:

	Player* player;
	vector<BaseMonster*> monsters;
	GameScene()
	{
		player = new Player();
		insertNewPaintSprite(player);
		monsters.push_back(new BaseMonster() );
		monsters[0]->_realPos = XDVector3<double>(14,1,0);

		insertNewPaintSprite(monsters[0]);
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