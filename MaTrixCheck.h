// MaTrixCheck.h: interface for the MeTrixCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXCHECK_H__76C6E9A4_9C43_4327_9130_AA2F3EDAE9E5__INCLUDED_)
#define AFX_MATRIXCHECK_H__76C6E9A4_9C43_4327_9130_AA2F3EDAE9E5__INCLUDED_

#define    maxn        ( 15 + 1)
#define    Inf         ( 1 << 30)
//#define    min( a, b)  ( a < b ? a : b)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ÕæÊµÐÎ×´
struct MTPoint
{
	int fty, ftx;
	int y[4];
	int x[4];

	MTPoint()
	{
		InitMTPoint();
	}

	void InitMTPoint()
	{
		ftx = maxn / 2 - 2;
		fty = 0;
		memset( y, 0, sizeof(y));
		memset( x, 0, sizeof(x));
	}

	void operator= ( const MTPoint& Mt)
	{
		for( int i = 0; i < 4; i++)
		{
			x[i] = Mt.x[i];
			y[i] = Mt.y[i];
		}
	};
};

class MaTrixCheck  : public MaTrixShape, public MaTrixVeil
{
private:
	static int offsetx;
	static int offsety;
	static int dirx[];
	static int diry[];

	MTPoint M_pos;

	int m_box[maxn][maxn];

public:
	MaTrixCheck();
	~MaTrixCheck();

public:
	bool DNMoveMeTrix();
	bool IsMove( int CRTL);
	bool IsDownMove();
	bool IsGetNewShape();
	bool IsDeadMeTrix();

	void RLMoveMeTrix( int CRTL);
	void IsRemoveFloor();

public:
	void ChangeFloor( int k);
	void MakeNewMeTrix();
	void ChangeTheMap();
	void ChangeShape();
	void ReleaseShapeInMap();
	void GetShapePositon();
	void InitMap();
	void MakeShapeInMap();
	


};

#endif // !defined(AFX_MATRIXCHECK_H__76C6E9A4_9C43_4327_9130_AA2F3EDAE9E5__INCLUDED_)
