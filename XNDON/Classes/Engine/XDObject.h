#pragma once
#include "main.h"

class XDObject
{
public:
	void auto_release( ){
		_objects.push_back( this );
	}

	static void Clear_Objects( )
	{
		for( list<XDObject*>::iterator itr = _objects.begin(); itr != _objects.end(); itr++ )
			delete (*itr); // Important delete (*itr)
		_objects.clear( );
	}

private:
	static list<XDObject*> _objects;
	
protected:
	XDObject( ){	}
	virtual ~XDObject( ){	}
};
