#include "Engine\XDSprite.h"

class BaseMonster : public XDSprite
{
public:
	enum Animation{
		STAND,
		MOVE,
		ATTACK,
		JUMP,
		ATTACKED,
		DEAD,
	};

	BaseMonster()
		: XDSprite()
	{

		make_Animation(_T("./assets/img/gob/new_goblin.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_walk.png"),
					   _T("./assets/img/gob/new_goblin.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_attack1.png"),
					   _T("./assets/img/gob/new_goblin_attack2.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_walk.png"),
					   _T("./assets/img/gob/new_goblin_walk.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_attacked.png") );
		make_Animation(_T("./assets/img/gob/new_goblin_death.png") );
	
		_gridPos = XDVector3<int>(15, 0, 0);
//		_realPos = XDVector3<double>(0.0, 0.0, 0.0);
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
		_collideBox1 = XDVector3<double>(0.0, 0.0, 0.0);
		_collideBox2 = XDVector3<double>(1.0, 1.0, 1.0);
		_is_Controlled = false;
		setScreenPos();
		

	}

	void Update(double _dTime )
	{
		_time += _dTime;
		if ( _time >= 1.0 )
		{
			_time -= 1.0;
			set_Animation(MOVE);
			moveLeft();
		}
	
	}

	void Delete(){ }


};
