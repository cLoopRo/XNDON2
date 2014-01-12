#pragma once
#include "XDMain.h"
#include "XDDirector.h"

class XDSprite
{
public:
	virtual void Return() = 0;
	virtual void Update(double _dTime) = 0;
	
	XDSprite()
	{
		_animation_time = 0.0;
		speed = 1.0;
		_time = 0.0;
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
		_is_Controlled = false;
	}

	inline void setSpeed(double _Speed){	speed = _Speed;		}
	inline void setPosition(int _X, int _Y, int _Z){	_realPos.setPosition(_X, _Y, _Z);	_gridPos.setPosition(_X, _Y, _Z);	}
	inline void setVelocity(int _X, int _Y, int _Z){	_velocity.setPosition(_X, _Y, _Z);	}


protected:
	double _time;

public:
	XDVector3<int> _gridPos;
	XDVector3<double> _realPos;
	XDVector3<double> _velocity;
	XDVector3<int> _screenPos;
	double speed;

	bool _is_Controlled;

	bool Controlled;
	bool reversed;
	
	void moveLeft(){	_velocity.X = -2.0; _velocity.Y = -0.0;  }//	if(!_is_Controlled && _gridPos.X>0){_gridPos.X -= 1;	_is_Controlled = true;	}	}
	void moveRight(){	_velocity.X = 2.0; _velocity.Y = -0.0; 	} //if(!_is_Controlled && _gridPos.X<15) {_gridPos.X += 1; _is_Controlled = true;}}
	void moveUp(){		_velocity.X = 0.0; _velocity.Y = -2.0; }//if(!_is_Controlled && _gridPos.Y>0) {_gridPos.Y -= 1; _is_Controlled = true;}}
	void moveDown(){ _velocity.X = 0.0; _velocity.Y = 2.0;  }//if(!_is_Controlled && _gridPos.Y<5) {_gridPos.Y += 1; _is_Controlled = true;}}
	void stop(){ _velocity.X = 0.0; _velocity.Y = 0.0; }

public:
	void Update_Move( double _dTime ){
		_realPos.X += _dTime * _velocity.X;
		_realPos.Y += _dTime * _velocity.Y;
		_realPos.Z += _dTime * _velocity.Z;				
		/*
		// 위치가 다르면 
		double delta = 0.0;
		if (std::abs(_gridPos.Y - _realPos.Y) < 0.01) {     //y좌표의 변화가 없을 때
			if( _realPos.X - _gridPos.X > 0) {    //왼쪽으로 갈 때
				delta = -_DTime*_velocity.X;    //변화량 계산
				if( _realPos.X + delta <= _gridPos.X){	delta = _gridPos.X - _realPos.X; _is_Controlled = false;	}   //변화량이 커서 너무 많이 움직일 것 같으면 조정
				_realPos.X += delta;    //이동변화 적용
			}
			else {    //오른쪽으로 갈 때
				delta = _DTime*_velocity.X;
				if( _realPos.X + delta >= _gridPos.X) {delta = _gridPos.X - _realPos.X; _is_Controlled = false;}
				_realPos.X += delta;
			}
		}
		else if (std::abs(_gridPos.X - _realPos.X) < 0.01) {    //x좌표의 변화가 없을 때
			if( _realPos.Y - _gridPos.Y > 0) {    //위로 갈 때
				delta = -_DTime*_velocity.Y;
				if( _realPos.Y + delta <= _gridPos.Y) {delta = _gridPos.Y - _realPos.Y; _is_Controlled = false;}
				_realPos.Y += delta;
			}
			else {    //아래로 갈 때
				delta = _DTime*_velocity.Y;
				if( _realPos.Y + delta >= _gridPos.Y) {delta = _gridPos.Y - _realPos.Y; _is_Controlled = false;}
				_realPos.Y += delta;
			}
		}
		setScreenPos();    //계산한 실제 좌표를 가지고 화면상의 좌표를 계산
		//collideBox의 좌표 동기화가 필요 
*/
	}



/*
<---------- 이미지 && 애니메이션 관리 구현 ----------->
이미지는 기본적으로 Gdiplus 의 Image 를 통해 관리한다.
기본적으로 각 객체는 이미지의 포인터만를 가지고 있으며

이미지의 중복은 경로와 이름을 통해서만 확인을 하며
static map<wstring, Image* >  _images; => (RB TREE) 를 사용하여
실제 이미지들을 관리한다.

각 객체에서의 이미지포인터는 애니메이션 저장소에 저장된다.

P.S. 현재 모든 이미지의 크기는 고정이므로 사이즈는 고려하지 않는다.
<-----------------------------------------------------> 
*/

private:
	Image* _pImage; // 현재 스프라이트를 그릴 때 사용하는 이미지포인터
	static map<wstring, Image* >  _images; // 전체 이미지들을 관리하는 map

	double _animation_time; // 애니메이션의 변화를 위해 있는 값, 생성자에서 0.0 으로 해주어야한다. 
	list< Image* > _animation_queue; // 다음에 출력될 그림의 포인터의 저장소
	vector< list< Image* > > _animation_list; // 애니메이션의 저장소

protected:
	/* 
	add_Image 함수는 경로와 이름을 이용하여, 이미지의 중복을 확인하고
	이미지를 추가하고 이미지의 포인터를 반환한다.
	*/		
	Image* add_Image(const wstring& _Path){

		map<wstring, Image*>::iterator itr;
		// 추가된 경로가 map 에 있는지를 확인하고, pImage 추가된 이미지를 가리키도록 한다.
		if ( _images.end() == ( itr = _images.find(_Path) )  ) 
		{	// 존재하지 않는다면 새로 할당하여 추가한다.
			_pImage = new Image( _Path.c_str() );
			_images.insert ( std::pair<wstring, Image* >(_Path, _pImage) );
		}
		else
		{	// 존재한다면 그 이미지포인터를 반환한다.
			_pImage = itr->second;
		}
		return _pImage; 	
	
	}
	
	// 애니메이션 리스트에 있는 N 번째 애니메이션을 현재 애니메이션으로 한다.
	void set_Animation( int _N , bool* _Fin = NULL )
	{
		_animation_queue = _animation_list[_N];
		_animation_time = 0.25/(speed);
		_fin = _Fin;
	}
	bool* _fin;

public: 
	// 애니메이션의 변화를 관리한다.
	void Update_Animation(double _dTime){	
		_animation_time += _dTime;
		if ( _animation_time >= (0.25/speed) )
		{
			_animation_time -= (0.25/speed);
			if ( _animation_queue.empty() ){
				set_Animation(0);
				Controlled=false;
			}
			else
			{
				if ( (_fin != NULL)  && (_animation_queue.size() == 1) )
					*_fin = true;
				_pImage = *_animation_queue.begin( );
				_animation_queue.pop_front( );	
			}
		}
	}

protected:
	// 애니메이션을 추가한다. 현재 애니메이션의 번호를 반환한다.
	int make_Animation(wstring _Img1, wstring _Img2= _T(""), wstring _Img3 = _T(""), wstring _Img4 = _T(""))
	{
		list<Image* > tmpList;
		tmpList.push_back( add_Image(_Img1) );
		if ( _Img2 != _T("") )
			tmpList.push_back( add_Image(_Img2) );
		if ( _Img3 != _T("") )
			tmpList.push_back( add_Image(_Img3) );
		if ( _Img4 != _T("") )
			tmpList.push_back( add_Image(_Img4) );
		_animation_list.push_back( tmpList );
		return ( _animation_list.size()-1 );
	}
	/*<---------------- 애니메이션 구현 종료 ------->*/	
	
public:
	// 현재 pImage 가 가리키는 이미지를 그린다.
	void draw_Sprite(Graphics& G)
	{
		setScreenPos();

		if(reversed==true){
			_pImage->RotateFlip(Gdiplus::Rotate180FlipY);
		}

		SolidBrush *brush = new SolidBrush(Color(50, 0, 0, 0));
		G.FillEllipse(brush, (int)(_realPos.X*60), (int)(_realPos.Y*60/sqrt(2.0)+130)+20, 60, (int)(50/sqrt(2.0)-10));

		G.DrawImage(_pImage, _screenPos.X, _screenPos.Y, 180, 180);//, Gdiplus::UnitPixel);	
		if(reversed==true){
			_pImage->RotateFlip(Gdiplus::Rotate180FlipY);
		}
	}

	void setScreenPos(){
		int gridSize = 60;
		int backgroundSize = 130;
		_screenPos.X = (int)(_realPos.X * gridSize - 60);
		_screenPos.Y = (int)(((_realPos.Y * gridSize + gridSize / 2 ) - (_realPos.Z * gridSize + 120 * sqrt(2.0))) / sqrt(2.0) + backgroundSize );	
	}

	~XDSprite(){	}
};

	/*
	enum DIR{
		LEFT,
		RIGHT,
	};
	*/

	/*
	bool isMoving; 	  
	bool isJumping;
	bool isSkilling;
	bool isBeingAttackted;

	double attackSpeed;
	double moveSpeed;
	double recoverySpeed;
	*/