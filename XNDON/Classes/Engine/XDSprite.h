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
<---------- �̹��� && �ִϸ��̼� ���� ���� ----------->
�̹����� �⺻������ Gdiplus �� Image �� ���� �����Ѵ�.
�⺻������ �� ��ü�� �̹����� �����͸��� ������ ������

�̹����� �ߺ��� ��ο� �̸��� ���ؼ��� Ȯ���� �ϸ�
static map<wstring, Image* >  _images; => (RB TREE) �� ����Ͽ�
���� �̹������� �����Ѵ�.

�� ��ü������ �̹��������ʹ� �ִϸ��̼� ����ҿ� ����ȴ�.

P.S. ���� ��� �̹����� ũ��� �����̹Ƿ� ������� ������� �ʴ´�.
<-----------------------------------------------------> 
*/

private:
	Image* _pImage; // ���� ��������Ʈ�� �׸� �� ����ϴ� �̹���������
	static map<wstring, Image* >  _images; // ��ü �̹������� �����ϴ� map

	double _animation_time; // �ִϸ��̼��� ��ȭ�� ���� �ִ� ��, �����ڿ��� 0.0 ���� ���־���Ѵ�. 
	list< Image* > _animation_queue; // ������ ��µ� �׸��� �������� �����
	vector< list< Image* > > _animation_list; // �ִϸ��̼��� �����

protected:
	/* 
	add_Image �Լ��� ��ο� �̸��� �̿��Ͽ�, �̹����� �ߺ��� Ȯ���ϰ�
	�̹����� �߰��ϰ� �̹����� �����͸� ��ȯ�Ѵ�.
	*/		
	Image* add_Image(const wstring& _Path){

		map<wstring, Image*>::iterator itr;
		// �߰��� ��ΰ� map �� �ִ����� Ȯ���ϰ�, pImage �߰��� �̹����� ����Ű���� �Ѵ�.
		if ( _images.end() == ( itr = _images.find(_Path) )  ) 
		{	// �������� �ʴ´ٸ� ���� �Ҵ��Ͽ� �߰��Ѵ�.
			_pImage = new Image( _Path.c_str() );
			_images.insert ( std::pair<wstring, Image* >(_Path, _pImage) );
		}
		else
		{	// �����Ѵٸ� �� �̹��������͸� ��ȯ�Ѵ�.
			_pImage = itr->second;
		}
		return _pImage; 	
	
	}
	
	// �ִϸ��̼� ����Ʈ�� �ִ� N ��° �ִϸ��̼��� ���� �ִϸ��̼����� �Ѵ�.
	void set_Animation( int _N, bool *_Flag = NULL )
	{
		_animation_queue = _animation_list[_N];
		_animation_time = 0.25/(speed);
		flag = _Flag;
	}

	bool *flag;

public: 
	// �ִϸ��̼��� ��ȭ�� �����Ѵ�.
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
	// �ִϸ��̼��� �߰��Ѵ�. ���� �ִϸ��̼��� ��ȣ�� ��ȯ�Ѵ�.
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
	/*<---------------- �ִϸ��̼� ���� ���� ------->*/	
	
public:
	// ���� pImage �� ����Ű�� �̹����� �׸���.
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

