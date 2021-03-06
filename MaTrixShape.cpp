// MaTrixShape.cpp: implementation of the MaTrixShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int MaTrixShape::MTType[] =  {
		/*0*/
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
		/*J*/		
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,
		1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,
		/*L*/
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
		0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,
		1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,
		1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,		
		/*?*/		
		0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,
		1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
		1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,											
		/*--*/
		0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
		1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,											
		/*N*/		
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
		0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
		0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,												
		/*Z*/		
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
		1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
		1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0	
};

MaTrixShape::MaTrixShape()
{
	GetShape();
}

MaTrixShape::~MaTrixShape()
{

}

void MaTrixShape::GetShape()
{
	srand((unsigned)time(0));
	for( int i = 0; i < 2; i++)
	{
		mt.m_tshape[i] = rand() % TYPE;
		mt.m_ttype[i]  = rand() % CTRL;
	}
}

void MaTrixShape::IteratShape()
{
	mt.m_tshape[0] = mt.m_tshape[1];
	mt.m_ttype[0]  = mt.m_ttype[1];
	srand((unsigned)time(0));
	mt.m_tshape[1] = rand() % TYPE;
	mt.m_ttype[1]  = rand() % CTRL;	
}

int * MaTrixShape::GetMTShape()
{
	return MTType + mt.m_tshape[0] * 64 + mt.m_ttype[0] * 16;
}

int * MaTrixShape::GetIteratorShape()
{
	return MTType + mt.m_tshape[1] * 64 + mt.m_ttype[1] * 16;
}

int * MaTrixShape::GetNewShape()
{
	int type = (mt.m_ttype[0] + 1) % 4;
	return MTType + mt.m_tshape[0] * 64 + type * 16;
}

void MaTrixShape::ChangeType()
{
	mt.m_ttype[0] = (mt.m_ttype[0] + 1) % 4;
}