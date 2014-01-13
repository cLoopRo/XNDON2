#pragma once
#include "Engine\XDScene.h"
#include "Engine\XDGridMap.h"
#include "BasePlayer.h"
#include "BaseMonster.h"
#include "BaseMissile.h"

class BaseScene : public XDScene
{
public:

	XDGridSprite* player;
	vector<XDGridSprite*> monsters;
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

	void Update_InputController(double _dTime){
	
		if ( XDDirector::_keys['Z'] ){
			((BasePlayer*)player )->Attack( );
		}
		else if ( XDDirector::_keys['X'] ){
			((BasePlayer*)player )->Kick( );
		}
		else if ( XDDirector::_keys['C'] ){
			((BasePlayer*)player )->Quake();
		}
		else if ( XDDirector::_keys['V'] ){
			((BasePlayer*)player )->Guard();
		}
		else if ( XDDirector::_keys[VK_SPACE] ){
			((BasePlayer*)player )->Jump();
		}
		else if ( XDDirector::_keys[VK_LEFT]  ){
			((BasePlayer*)player )->reversed = true;
//			gridMap->resetState(_gridPos.X,_gridPos.Y);
			((BasePlayer*)player )->move_Left();
//			gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER,this);
			((BasePlayer*)player )->Walk();
		}
		else if ( XDDirector::_keys[VK_UP]  ){
//			gridMap->resetState(_gridPos.X,_gridPos.Y);
			((BasePlayer*)player )->move_Up();
//			gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER,this);
			((BasePlayer*)player )->Walk();
		}
		else if ( XDDirector::_keys[VK_RIGHT] ){
			((BasePlayer*)player )->reversed=false;
		//	gridMap->resetState(_gridPos.X,_gridPos.Y);
			((BasePlayer*)player )->move_Right();
		//	gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER);
			((BasePlayer*)player )->Walk();
		}
		else if ( XDDirector::_keys[VK_DOWN] ){
		//	gridMap->resetState(_gridPos.X,_gridPos.Y);
			((BasePlayer*)player )->move_Down();
		//	gridMap->setState(_gridPos.X,_gridPos.Y,BASE_PLAYER);
			((BasePlayer*)player )->Walk();
		}
		else
			;
	
	
	}

	void Update(double _dTime)
	{
		Update_InputController(_dTime);			
		player->Update(_dTime);

		monsters[0]->Update_Animation(_dTime);
		monsters[0]->Update(_dTime);
		monsters[0]->Update_Grid_Move(_dTime);
		

	}


	/*<----- ¸Ê °ü¸® ----->*/
	




};

