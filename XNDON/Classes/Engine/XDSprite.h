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
	

	/*<----- �ִϸ��̼� ���� ----->*/
	void setUpdate(double _DTIME)
	{
	
	}

	// �ִϸ��̼� ���� ����
private:
	double dt_animation;

	queue< int , vector<int> > animation_queue; // ������ ��µ� �׸��� ��ȣ�� �����ϴ� ��
	vector< vector<int> > animation_list; // �ִϸ��̼ǵ��� �����ϴ� ��

protected:
	// �ִϸ��̼��� �߰��Ѵ�. ���� �ִϸ��̼��� ��ȣ�� ��ȯ�Ѵ�.
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

	// ���� �ִϸ��̼��� ť�� �ִ´�.
	void set_animation(int _N)
	{
		for(int i=0; i<animation_list[_N].size(); i++)
		animation_queue.push(animation_list[_N][i] );
	}

	/*<---------------- �ִϸ��̼� ���� ���� ------->*/	
	


	/*<----- ��ġ�� �浹 ���� ���� ----->*/
	// ȭ����� ���� ��ġ�� ���� ���� ���κ��� 0,0 ���� �Ѵ�.
	

private:
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