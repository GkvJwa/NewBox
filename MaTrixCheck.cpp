// MaTrixCheck.cpp: implementation of the MeTrixCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int MaTrixCheck::dirx[] = { -1, 1};

int MaTrixCheck::diry[] = { 1};

int MaTrixCheck::offsetx = 10;
int MaTrixCheck::offsety = 3;


MaTrixCheck::MaTrixCheck()
{
	InitMap();
	ShowMap( 0 + offsety, 0 + offsetx, (int **)m_box);

	GetShapePositon();
	MakeShapeInMap();
	

	//打印下一个方块
	ShowIteratorShapeBox( M_pos.fty + 2 + offsety - 1, M_pos.ftx + maxn * 2 + offsetx - 1);
	IteratorShape( M_pos.fty + 2 + offsety, M_pos.ftx + maxn * 2 + offsetx, GetIteratorShape());  

	//打印当前方块          
	PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
}

MaTrixCheck::~MaTrixCheck()
{
	
}

void MaTrixCheck::GetShapePositon()
{
	int * shape = GetMTShape();
	int count = 0;
	for( int i = 0; i < 16; i++)
	{
		if( shape[i] == 1)
		{
			M_pos.x[count] = i % 4;
			M_pos.y[count] = i / 4;
			count++;
		}
	}
}

//能否改变形状
bool MaTrixCheck::IsGetNewShape()
{
	//已知4*4起始位置的情况下
	int count = 0;
	MTPoint tmp;
	int * shape = GetNewShape();
	int tmpbox[maxn][maxn];
	for( int n = 0; n < maxn; n++)
	{
		for( int m = 0; m < maxn; m++)
		{
			tmpbox[n][m] = m_box[n][m];
			if( tmpbox[n][m] == -1) //去掉当前形状
			{
				tmpbox[n][m] = 0;
			}
		}
	}

	for( int i = 0; i < 16; i++)
	{
		if( shape[i] == 1)
		{
			if( tmpbox[i/4 + M_pos.fty][i%4 + M_pos.ftx] == 0)
			{
				tmp.x[count] = i%4;
				tmp.y[count] = i/4;
				count++;
			}
			else
			{
				return false;
			}
		}
	}

	ReleaseShapeInMap();
	ReleaseVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

	M_pos = tmp;
	PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
	return true;
}

void MaTrixCheck::ChangeShape()
{
	if( IsGetNewShape())
	{
		ChangeType();
		MakeShapeInMap();
	}
}

//能否左右移动
bool MaTrixCheck::IsMove( int CRTL)
{
	//0左移动, 1右移
	for ( int i = 0; i < 4; i++)
	{
		if( m_box[M_pos.y[i] + M_pos.fty][M_pos.x[i] + dirx[CRTL] + M_pos.ftx] == 1)
		{
			return false;
		}
	}
	return true;
}

void MaTrixCheck::RLMoveMeTrix(int CRTL)
{
	if( IsMove( CRTL))
	{
		int dir = !CRTL ? -1 : 1;
		ReleaseShapeInMap();
		ReleaseVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
		M_pos.ftx += dir;
		PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
	}
}

//向下移动
bool MaTrixCheck::IsDownMove()
{
	for( int i = 0; i < 4; i++)
	{
		if( m_box[M_pos.y[i] + M_pos.fty + diry[0]][M_pos.x[i] + M_pos.ftx] == 1)
		{
			return false;
		}
	}
	return true;
}

void MaTrixCheck::ChangeTheMap()
{
	for( int i = 0; i < 4; i++)
	{
		m_box[M_pos.fty+M_pos.y[i]][M_pos.ftx+M_pos.x[i]] = 1;
	}
}

bool MaTrixCheck::DNMoveMeTrix()
{
	if( IsDownMove())
	{
		int dir = 1;

		//清空方块
		ReleaseShapeInMap();
		ReleaseVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//打印方块
		M_pos.fty += dir;
		PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//放入盒子中
		MakeShapeInMap();
	}
	else  //新的方块
	{
		//改变map
		ChangeTheMap();
		MakeVeilMap( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//能否消层
		IsRemoveFloor(); 

		//放入新的方块
		MakeNewMeTrix(); 
		
		//判断是否能继续
		if( IsDeadMeTrix()) 
		{
			//放入
			MakeShapeInMap(); 

			IteratorShape( M_pos.fty + 2 + offsety, M_pos.ftx + maxn * 2 + offsetx, GetIteratorShape());  //打印下一个方块              
			PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
		}
		else
		{
			//结束
			ShowGameOver( maxn + offsety, 0);
			return true;
		}
	}
	return false;
}

void MaTrixCheck::MakeNewMeTrix()
{
	IteratShape();        //新的方块
	
	M_pos.InitMTPoint();  //重置标志位置
	GetShapePositon();    //得到标志位置

	
}

//是否死亡
bool MaTrixCheck::IsDeadMeTrix()
{
	for( int i = 0; i < 4; i++)	
	{
		if( m_box[M_pos.fty+M_pos.y[i]][M_pos.ftx+M_pos.x[i]] == 1)
		{
			return false;
		}
	}
	return true;
}

//消层
void MaTrixCheck::ChangeFloor( int k)
{
		for( int y = k; y > 0; y--)
		{
			for( int j = 1; j < maxn - 1; j++)
			{
				IteratorVeil( y + offsety, j + offsetx, m_box[y-1][j]);
				m_box[y][j] = m_box[y-1][j];
			}
		}
//	}
}


//能否消层
void MaTrixCheck::IsRemoveFloor()
{
	int GetMinY = Inf;
	for( int i = 0; i < 4; i++)
	{
		GetMinY = min( GetMinY, M_pos.y[i]);
	}
	GetMinY += M_pos.fty;
	for( int k = GetMinY; k < maxn - 1; k++)
	{
		for( int j = 1; j < maxn - 1 && m_box[k][j] == 1; j++);
		if( j == maxn - 1) //消层
		{
//			mark++; //计数
			ChangeFloor(k);
			k--;
		}
	}
}

void MaTrixCheck::ReleaseShapeInMap()
{
	for( int i = 0; i < 4; i++)
	{
		int fx = M_pos.ftx, fy = M_pos.fty;
		int x = M_pos.x[i], y = M_pos.y[i];
		m_box[fy+y][fx+x] = 0;
	}
}


void MaTrixCheck::MakeShapeInMap()
{
	//改变
	for( int i = 0; i < 4; i++)
	{
		int fx = M_pos.ftx, fy = M_pos.fty;
		int x = M_pos.x[i], y = M_pos.y[i];
		m_box[fy+y][fx+x] = -1;
	}
}

void MaTrixCheck::InitMap()
{
	memset( m_box, 0, sizeof(m_box));
	for( int y = 0; y < maxn; y++)
	{
		for( int x = 0; x < maxn; x++)
		{
			if( y == maxn - 1 || !x || x == maxn - 1)
			{
				m_box[y][x] = 1;
			}
		}
	}	
}
