#include "Engine\XDScene.h"
#include "Player.h"

class GameScene : public XDScene
{
public:
	GameScene()
	{
		insertNewPaintSprite(new Player());
	}



};