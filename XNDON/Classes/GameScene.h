#include "Engine\XDScene.h"
#include "Player.h"

class GameScene : public XDScene
{
public:

	Player* player;
	GameScene()
	{
		player = new Player();

		insertNewPaintSprite(player);
	}

	void Update(double _dTime)
	{
		player->Update_Animation(_dTime);
		player->Update(_dTime);
		player->Update_Move(_dTime);
	}


};