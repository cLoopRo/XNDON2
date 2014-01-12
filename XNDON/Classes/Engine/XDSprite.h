#pragma once
#include "XDMain.h"
#include "XDDirector.h"

class XDSprite
{
public:
	virtual void Delete() = 0;
	virtual void Update(double _dTime) = 0;
	XDSprite()
	{
		_animation_time = 0.0;
		speed = 1.0;
		_time = 0.0;
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
	//	_collideBox1 = XDVector3<double>(0.0, 0.0, 0.0);
	//	_collideBox2 = XDVector3<double>(1.0, 1.0, 1.0);
		_is_Controlled = false;
	}
	XDSprite(int _X, int _Y, int _Z){
		_animation_time = 0.0;
		speed = 1.0;
		_time = 0.0;
		_velocity = XDVector3<double>(2.0, 2.0, 0.0);
		_is_Controlled = false;
	}

protected:
	double _time;

	bool isMoving; 	  
	bool isJumping;
	bool isSkilling;
	bool isBeingAttackted;

	double attackSpeed;
	double moveSpeed;
	double recoverySpeed;

protected:
	

	/*<----- ��ġ�� �浹 ���� ���� ----->*/
	// ȭ����� ���� ��ġ�� ���� ���� ���κ��� 0,0 ���� �Ѵ�.
	
//protected:
public:
	XDVector3<int> _gridPos;
	XDVector3<double> _realPos;
	XDVector3<double> _velocity;
	XDVector3<double> _collideBox1;
	XDVector3<double> _collideBox2;
	XDVector3<int> _screenPos;
	double speed;

	bool _is_Controlled;

	bool Controlled;
	bool reversed;
	
	void moveLeft() {if(!_is_Controlled && _gridPos.X>0) {_gridPos.X -= 1; _is_Controlled = true;}}
	void moveRight() {if(!_is_Controlled && _gridPos.X<15) {_gridPos.X += 1; _is_Controlled = true;}}
	void moveUp() {if(!_is_Controlled && _gridPos.Y>0) {_gridPos.Y -= 1; _is_Controlled = true;}}
	void moveDown() {if(!_is_Controlled && _gridPos.Y<5) {_gridPos.Y += 1; _is_Controlled = true;}}

public:
	void Update_Move(double _DTime ){
		// ��ġ�� �ٸ��� 
		double delta = 0.0;
		if (std::abs(_gridPos.Y - _realPos.Y) < 0.01) {     //y��ǥ�� ��ȭ�� ���� ��
			if( _realPos.X - _gridPos.X > 0) {    //�������� �� ��
				delta = -_DTime*_velocity.X;    //��ȭ�� ���
				if( _realPos.X + delta <= _gridPos.X) {delta = _gridPos.X - _realPos.X; _is_Controlled = false;}   //��ȭ���� Ŀ�� �ʹ� ���� ������ �� ������ ����
				_realPos.X += delta;    //�̵���ȭ ����
				_collideBox1.X += delta;    //�浹�ڽ� ��ǥ���� ���� �̵���ȭ�� ����
				_collideBox2.X += delta;
			}
			else {    //���������� �� ��
				delta = _DTime*_velocity.X;
				if( _realPos.X + delta >= _gridPos.X) {delta = _gridPos.X - _realPos.X; _is_Controlled = false;}
				_realPos.X += delta;
				_collideBox1.X += delta;
				_collideBox2.X += delta;
			}
		}
		else if (std::abs(_gridPos.X - _realPos.X) < 0.01) {    //x��ǥ�� ��ȭ�� ���� ��
			if( _realPos.Y - _gridPos.Y > 0) {    //���� �� ��
				delta = -_DTime*_velocity.Y;
				if( _realPos.Y + delta <= _gridPos.Y) {delta = _gridPos.Y - _realPos.Y; _is_Controlled = false;}
				_realPos.Y += delta;
				_collideBox1.Y += delta;
				_collideBox2.Y += delta;
			}
			else {    //�Ʒ��� �� ��
				delta = _DTime*_velocity.Y;
				if( _realPos.Y + delta >= _gridPos.Y) {delta = _gridPos.Y - _realPos.Y; _is_Controlled = false;}
				_realPos.Y += delta;
				_collideBox1.Y += delta;
				_collideBox2.Y += delta;
			}
		}
		setScreenPos();    //����� ���� ��ǥ�� ������ ȭ����� ��ǥ�� ���
		//collideBox�� ��ǥ ����ȭ�� �ʿ�
	}



/*
<---------- �̹��� && �ִϸ��̼� ���� ���� ----------->
�̹����� �⺻������ Gdiplus �� Image �� ���� �����Ѵ�.
�⺻������ �� ��ü�� �̹����� �����͸��� ������ ������

�̹����� �ߺ��� ��ο� �̸��� ���ؼ��� Ȯ���� �ϸ�
static map<wstring, Image* >  _images; => (RB TREE) �� ����Ͽ�
���� �̹������� �����Ѵ�.

�� ��ü������ �̹��������ʹ� �ִϸ��̼� ����ҿ� ����ȴ�.

P.S. ���� ��� �̹����� ũ��� �����̹Ƿ� ������� �������� �ʴ´�.
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
	void set_Animation( int _N , bool* _Fin = NULL )
	{
		_animation_queue = _animation_list[_N];
		_animation_time = 0.25/(speed);
		_fin = _Fin;
	}
	bool* _fin;

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
				if ( (_fin != NULL)  && (_animation_queue.size() == 1) )
					*_fin = true;
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
	


	/*
	enum DIR{
		LEFT,
		RIGHT,
	};
	*/
	~XDSprite(){	}
};