#pragma once
#include "XDMain.h"
#include "XDDirector.h"

class XDSprite
{
public:
	virtual void Return() = 0;
	virtual void Update(double _dTime) = 0;
	
	
	bool isSkilling;
	XDSprite()
	{
		flag = NULL;
		_animation_time = 0.0;
		speed = 1.0;
		_time = 0.0;
		isSkilling = false;
	}

	double speed;
	XDVector3<double> position;
	XDVector3<double> velocity;
	inline void setSpeed(double _Speed){	speed = _Speed;		}
	inline void setPosition(int _X, int _Y, int _Z){	position.setPosition(_X, _Y, _Z);	}
	inline void setVelocity(int _X, int _Y, int _Z){	velocity.setPosition(_X, _Y, _Z);	}
	
protected:
	double _time;

public:
	XDVector3<int> _screenPos;


	bool Controlled;
	bool reversed;

public:
	void Update_Move( double _dTime ){
		position.X += _dTime * velocity.X;
		position.Y += _dTime * velocity.Y;
		position.Z += _dTime * velocity.Z;
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
	void set_Animation( int _N, bool *_Flag = NULL )
	{
		_animation_queue = _animation_list[_N];
		_animation_time = 0.25/(speed);
		flag = _Flag;
	}

	bool *flag;

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
				if ( flag != NULL && _animation_queue.size() == 1 ){
					*flag = true;
				}
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
		G.FillEllipse(brush, (int)(position.X*60), (int)(position.Y*60/sqrt(2.0)+130)+20, 60, (int)(50/sqrt(2.0)-10));
		
		
		G.DrawImage(_pImage, _screenPos.X, _screenPos.Y, 180, 180);//, Gdiplus::UnitPixel);	
		if(reversed==true){
			_pImage->RotateFlip(Gdiplus::Rotate180FlipY);
		}

	}

	void setScreenPos(){
		int gridSize = 60;
		int backgroundSize = 130;

		_screenPos.X = (int)(position.X * gridSize - 60);
		_screenPos.Y = (int)(((position.Y * gridSize + gridSize / 2 ) - (position.Z * gridSize + 120 * sqrt(2.0))) / sqrt(2.0) + backgroundSize );	

	}

	~XDSprite(){	}
};

