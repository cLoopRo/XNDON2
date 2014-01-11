#pragma once
#include "XDMain.h"
#include "XDDirector.h"

class XDSprite
{
public:
	virtual void Delete() = 0;
	XDSprite(){ dt_animation = 0.0; }
private:
	bool isMoving; 	  
	bool isJumping;
	bool isSkilling;
	bool isBeingAttackted;

	double attackSpeed;
	double moveSpeed;
	double recoverySpeed;



protected:
	

	/*<----- �ִϸ��̼� ���� ----->*/
	// �ִϸ��̼� ���� ����
private:
	double dt_animation;
	vector< list< int > > animation_list; // �ִϸ��̼ǵ��� �����ϴ� ��
	list< int > animation_queue; // ������ ��µ� �׸��� ��ȣ�� �����ϴ� ��
	
protected:
	void set_Animation(int _N){
		animation_queue = animation_list[_N];
		dt_animation = 0.25;
	}
public: 
	void Update_Animation(double _dTime){	
		
		dt_animation += _dTime;
		if ( dt_animation >= 0.25 )
		{
			if ( animation_queue.empty() )
				set_Animation(0);
			else
			{
				_pImage = _pImages[ *animation_queue.begin() ];
				animation_queue.pop_front( );
				dt_animation -= 0.25;
				
			}
		}

	}

protected:
	// �ִϸ��̼��� �߰��Ѵ�. ���� �ִϸ��̼��� ��ȣ�� ��ȯ�Ѵ�.
	int make_Animation(wstring _Img1, wstring _Img2= _T(""), wstring _Img3 = _T(""), wstring _Img4 = _T(""))
	{
		list<int> tmpList;
		tmpList.push_back( add_Image(_Img1) );
		if ( _Img2 != _T("") )
			tmpList.push_back( add_Image(_Img2) );
		if ( _Img3 != _T("") )
			tmpList.push_back( add_Image(_Img3) );
		if ( _Img4 != _T("") )
			tmpList.push_back( add_Image(_Img4) );
		animation_list.push_back( tmpList );
		return (animation_list.size()-1);
	}

	/*<---------------- �ִϸ��̼� ���� ���� ------->*/	
	


	/*<----- ��ġ�� �浹 ���� ���� ----->*/
	// ȭ����� ���� ��ġ�� ���� ���� ���κ��� 0,0 ���� �Ѵ�.
	

protected:
	XDVector3<int> _gridPos;
	XDVector3<double> _realPos;
	XDVector3<double> _velocity;

/*
	<----- �̹��� ���� ���� ----->
�̹����� �⺻������ Gdiplus �� Image �� ���� �����Ѵ�.
�⺻������ �� ��ü�� �̹����� �����͸��� ������ ������

�̹����� �ߺ��� ��ο� �̸��� ���ؼ��� Ȯ���� �ϸ�
static map<wstring, Image* >  _images; => (RB TREE) �� ����Ͽ�
���� �̹������� �����Ѵ�.

�� ��ü�� �̹��������͸� ������ ���͸� �̿��Ͽ� �������� �̹����� �����Ѵ�.

P.S. ���� ��� �̹����� ũ��� �����̹Ƿ� ������� ������� �ʴ´�.
	<---------------------------> 
*/
private:
	Image* _pImage; // ���� ��������Ʈ�� �׸� �� ����ϴ� �̹���������
	vector< Image* > _pImages; // ���� ��������Ʈ�� ���õ� �̹������� ����Ű�� �����͵��� ����
	static map<wstring, Image* >  _images; // ��ü �̹������� �����ϴ� map

protected:
	/* 
	add_Image �Լ��� ��ο� �̸��� �̿��Ͽ� �̹����� �߰��ϸ�
	�ش� ��ü�� �߰��� �̹����� �����͸� ���Ϳ� �����Ͽ� ������ �Ǵµ�,
	�� ���� ���� �߰��� �̹����� �����Ͱ� ����� �ε����� ��ȯ�Ѵ�. 
	*/	
	
	int add_Image(const wstring& _Path){
		
		map<wstring, Image*>::iterator itr;
		// �߰��� ��ΰ� map �� �ִ����� Ȯ���ϰ�, pImage �߰��� �̹����� ����Ű���� �Ѵ�.
		if ( _images.end() == ( itr = _images.find(_Path) )  ) 
		{	// �������� �ʴ´ٸ� ���� �Ҵ��Ͽ� �߰��Ѵ�.
			_pImage = new Image( _Path.c_str() );
			_images.insert ( std::pair<wstring, Image* >(_Path, _pImage) );
		}
		else
		{	// �����Ѵٸ� �װ��� �ּҸ� ��ȯ�Ѵ�.
			_pImage = itr->second;
		}
		// ���Ϳ� ���ο��̹����� ����Ű�� �����Ͱ� �ִ��� Ȯ���ϰ�, ������ �� �ε����� ��ȯ�Ѵ�.
		for(int i=0; i<_pImages.size(); i++){
			if ( _pImage == _pImages[i] )
				return i;
		}
		// �׷��� ������ ���Ϳ� �̹��������͸� �߰��ϰ�, �ε����� ��ȯ�Ѵ�.
		_pImages.push_back( _pImage );
		return (_pImages.size()-1); 
	}
	
	// set_Image �Լ��� pImage�� ���� ���Ϳ� ����� �̹��� �� �ش� ������ ���� ����Ű�����Ѵ�.
	void set_Image(int _N)
	{
		_pImage = _pImages[_N];	
	}
public:
	// ���� pImage �� ����Ű�� �̹����� �׸���.
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