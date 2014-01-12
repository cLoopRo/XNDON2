#pragma once
#include "Engine\XDScene.h"
#include "BasePlayer.h"
#include "BaseMonster.h"
#include "BaseMissile.h"
#include "GridMap.h"

class BaseScene : public XDScene
{
public:

	XDSprite* player;
	vector<XDSprite*> monsters;
	GridMap map;
	BaseScene()
	{
	
		player = BasePlayer::Create(0, 0, 0,&map);
		map.setState(0, 0, BASE_PLAYER, player);
		insertPaintSprite(player);

		BaseMonster::Reserve( 20 );
		monsters.push_back( BaseMonster::Create(14,1,0,&map) );
		map.setState(14, 1, BASE_MONSTER, monsters[0] );
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


	/*<----- ¸Ê °ü¸® ----->*/
	




};

