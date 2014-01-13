#include "Engine\XDMain.h"
#include "Engine\XDGridSprite.h"
#include "BaseMonster.h"

class BaseMissile : public XDGridSprite
{

	void Update(double _dTime){
		if ( !reversed && !isMoving ){
			if ( grid_map->getState( (grid_current_position.X+1)%16, grid_current_position.Y) == BASE_MONSTER ){
				((BaseMonster*)grid_map->getSprite( (grid_current_position.X+1)%16, grid_current_position.Y))->Attacked();
				duration = 0;
				return ; 
			}
			move_Right();
			set_Animation(MOVE);
			duration--;
		}
		else if ( reversed && !isMoving ){
			move_Left();
			set_Animation(MOVE);
			duration--;
		}
		
	}
	TYPE GetType( ){	return BASE_MISSILE;	}

	/*<----- BaseMissile 의 예약 생성 반환 관리 시작 ----->*/
public:
	static vector<XDGridSprite*> baseMissiles;
	static void Reserve(int _N){	for (int i=0; i<_N; i++) baseMissiles.push_back( new BaseMissile() );	}
	static XDGridSprite* Create(int _X, int _Y, int _Z ){
		if ( baseMissiles.empty() )
			baseMissiles.push_back( new BaseMissile() );
		XDGridSprite* pTmpBaseMissile = *( baseMissiles.end() - 1 );
		baseMissiles.pop_back();
		pTmpBaseMissile->setPosition( _X, _Y, _Z );
		return pTmpBaseMissile;
	}
	
	static XDGridSprite* Create(int _X, int _Y, int _Z, GridMap* _map ){
		if ( baseMissiles.empty() )
			baseMissiles.push_back( new BaseMissile() );
		XDGridSprite* pTmpBaseMissile = *( baseMissiles.end() - 1 );
		baseMissiles.pop_back();
		pTmpBaseMissile->setPosition( _X, _Y, _Z );
		pTmpBaseMissile->grid_map=_map;
		((BaseMissile*)pTmpBaseMissile)->duration = 5; 
		return pTmpBaseMissile;
	}

	void Return( ){
		baseMissiles.push_back( this );
	}

	static void Clear( ){
		for(unsigned int i=0; i<baseMissiles.size(); i++)
			delete baseMissiles[i];
		baseMissiles.clear();
	}
/*<----- BaseMissile의 예약 생성 반환 관리 완료 ----->*/

/*<----- BaseMissile의 애니메이션 관리 시작 ----->*/
private:
	BaseMissile()
	{
		make_Animation(_T("./assets/img/missile/quake1.png"),
					   _T("./assets/img/missile/quake2.png") );
		duration = 5;
	}
public:	
	int duration;
	enum STATE{
		MOVE
	};
/*<----- BaseMissile의 애니메이션 관리 완료 ----->*/


};
