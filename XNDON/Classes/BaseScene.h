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
	vector<XDGridSprite*> missiles;
	GridMap map;
	BaseScene()
	{
	
		player = BasePlayer::Create(0, 0, 0, &map);
		map.setState(0, 0, BASE_PLAYER, player);
		insertPaintSprite(player);

		BaseMonster::Reserve( 20 );
		monsters.push_back( BaseMonster::Create( 14, 1, 0, &map) );
		map.setState(14, 1, BASE_MONSTER, monsters[0] );
		insertPaintSprite(monsters[0]);
	
		BaseMissile::Reserve( 20 );
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
		else if ( XDDirector::_keys['A'] ){
			if ( ((BasePlayer*)player )->speed_duration <= 0 ){
				((BasePlayer*)player )->speed = 2.0;
				((BasePlayer*)player )->speed_duration = 5.0;
			}
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
		


		for(vector<XDGridSprite*>::iterator itr1 = monsters.begin(); itr1 != monsters.end(); itr1++){
			for(vector<XDGridSprite*>::iterator itr2 = missiles.begin(); itr2 != missiles.end(); itr2++){
				if ( (*itr1)->grid_current_position.X == (*itr2)->grid_current_position.X && (*itr1)->grid_current_position.Y == (*itr2)->grid_current_position.Y ) {
					((BaseMonster*)(*itr1))->Attacked_by();
					((BaseMissile*)(*itr2))->duration = 0;
				}
			}
		}
		vector<vector<XDGridSprite*>::iterator> eraseList; 
		for(vector<XDGridSprite*>::iterator itr = missiles.begin(); itr != missiles.end(); itr++){
			if ( ((BaseMissile*)(*itr))->duration == 0 ){
				deletePaintSprite( (*itr) );
				missiles.erase( itr );
				break;
			}
			(*itr)->Update_Animation(_dTime);
			(*itr)->Update(_dTime);
			(*itr)->Update_Grid_Move(_dTime);	

		}
		
		if( ((BasePlayer*) player)->flag_earthquake == true )
		{
			if ( player->reversed == true )
			{
				missiles.push_back( BaseMissile::Create(player->grid_current_position.X - 1, player->grid_current_position.Y, 0, &map) );
				map.setState(player->grid_current_position.X - 1, player->grid_current_position.Y, BASE_MISSILE, *( missiles.end() - 1 ) );
				(*(missiles.end()-1))->reversed = true;
			}
			else{
				missiles.push_back( BaseMissile::Create(player->grid_current_position.X + 1, player->grid_current_position.Y, 0, &map) );
				map.setState(player->grid_current_position.X + 1, player->grid_current_position.Y, BASE_MISSILE, *( missiles.end() - 1 ) );
				(*(missiles.end()-1))->reversed = false;
			}
			insertPaintSprite( *( missiles.end() - 1 ) );
			((BasePlayer*) player)->flag_earthquake = false;
		}


	}


	/*<----- ¸Ê °ü¸® ----->*/
	




};

