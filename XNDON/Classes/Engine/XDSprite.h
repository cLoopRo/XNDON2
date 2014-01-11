#pragma once
#include "XDMain.h"
#include "XDDirector.h"

class XDSprite
{
public:
	virtual void Delete() = 0;
	XDSprite(){	}
private:
	bool isMoving; 	  
	bool isJumping;
	bool isSkilling;
	bool isBeingAttackted;

	double attackSpeed;
	double moveSpeed;
	double recoverySpeed;



protected:
	

	/*<----- 애니메이션 구현 ----->*/
	void setUpdate(double _DTIME)
	{
	
	}

	// 애니메이션 관련 변수
private:
	double dt_animation;

	queue< int , vector<int> > animation_queue; // 다음에 출력될 그림의 번호를 저장하는 곳
	vector< vector<int> > animation_list; // 애니메이션들을 저장하는 곳

protected:
	// 애니메이션을 추가한다. 현재 애니메이션의 번호를 반환한다.
	int make_Animation(wstring _Img1, wstring _Img2, wstring _Img3 = _T(""), wstring _Img4 = _T(""))
	{
		vector<int> tmpList;
		tmpList.push_back( add_Image(_Img1) );
		tmpList.push_back( add_Image(_Img2) );
		if ( _Img3 != _T("") )
			tmpList.push_back( add_Image(_Img3) );
		if ( _Img4 != _T("") )
			tmpList.push_back( add_Image(_Img4) );
		animation_list.push_back( tmpList );
		return (animation_list.size()-1);
	}

	// 현재 애니메이션을 큐에 넣는다.
	void set_animation(int _N)
	{
		for(int i=0; i<animation_list[_N].size(); i++)
		animation_queue.push(animation_list[_N][i] );
	}

	/*<---------------- 애니메이션 구현 종료 ------->*/	
	


	/*<----- 위치와 충돌 관련 구현 ----->*/
	// 화면상의 격자 위치는 왼쪽 가장 윗부분을 0,0 으로 한다.
	

private:
	XDVector3<int> _gridPos;
	XDVector3<double> _realPos;
	XDVector3<double> _velocity;

/*
	<----- 이미지 관리 구현 ----->
이미지는 기본적으로 Gdiplus 의 Image 를 통해 관리한다.
기본적으로 각 객체는 이미지의 포인터만를 가지고 있으며

이미지의 중복은 경로와 이름을 통해서만 확인을 하며
static map<wstring, Image* >  _images; => (RB TREE) 를 사용하여
실제 이미지들을 관리한다.

각 객체는 이미지포인터를 가지는 벡터를 이용하여 여러가지 이미지를 관리한다.

P.S. 현재 모든 이미지의 크기는 고정이므로 사이즈는 고려하지 않는다.
	<---------------------------> 
*/
private:
	Image* _pImage; // 현재 스프라이트를 그릴 때 사용하는 이미지포인터
	vector< Image* > _pImages; // 현재 스프라이트와 관련된 이미지들을 가리키는 포인터들의 모음
	static map<wstring, Image* >  _images; // 전체 이미지들을 관리하는 map

protected:
	/* 
	add_Image 함수는 경로와 이름을 이용하여 이미지를 추가하며
	해당 객체는 추가된 이미지의 포인터를 벡터에 저장하여 가지게 되는데,
	이 때의 현재 추가된 이미지의 포인터가 저장된 인덱스를 반환한다. 
	*/	
	
	int add_Image(const wstring& _Path){
		
		map<wstring, Image*>::iterator itr;
		// 추가된 경로가 map 에 있는지를 확인하고, pImage 추가된 이미지를 가리키도록 한다.
		if ( _images.end() == ( itr = _images.find(_Path) )  ) 
		{	// 존재하지 않는다면 새로 할당하여 추가한다.
			_pImage = new Image( _Path.c_str() );
			_images.insert ( std::pair<wstring, Image* >(_Path, _pImage) );
		}
		else
		{	// 존재한다면 그곳의 주소를 반환한다.
			_pImage = itr->second;
		}
		// 벡터에 새로운이미지를 가리키는 포인터가 있는지 확인하고, 있으면 그 인덱스를 반환한다.
		for(int i=0; i<_pImages.size(); i++){
			if ( _pImage == _pImages[i] )
				return i;
		}
		// 그렇지 않으면 벡터에 이미지포인터를 추가하고, 인덱스를 반환한다.
		_pImages.push_back( _pImage );
		return (_pImages.size()-1); 
	}
	
	// set_Image 함수는 pImage가 현재 벡터에 저장된 이미지 중 해당 인자의 것을 가리키도록한다.
	void set_Image(int _N)
	{
		_pImage = _pImages[_N];	
	}
public:
	// 현재 pImage 가 가리키는 이미지를 그린다.
	void draw_Sprite(Graphics& G)
	{

		G.DrawImage(_pImage, _realPos.X, (_realPos.Y - _realPos.Z)/1.4 + 130, 180, 180);//, Gdiplus::UnitPixel);	
	}

	/*
	enum DIR{
		LEFT,
		RIGHT,
	};
	*/
	~XDSprite(){	}
};