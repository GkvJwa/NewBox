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
	

	//��ӡ��һ������
	ShowIteratorShapeBox( M_pos.fty + 2 + offsety - 1, M_pos.ftx + maxn * 2 + offsetx - 1);
	IteratorShape( M_pos.fty + 2 + offsety, M_pos.ftx + maxn * 2 + offsetx, GetIteratorShape());  

	//��ӡ��ǰ����          
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

//�ܷ�ı���״
bool MaTrixCheck::IsGetNewShape()
{
	//��֪4*4��ʼλ�õ������
	int count = 0;
	MTPoint tmp;
	int * shape = GetNewShape();
	int tmpbox[maxn][maxn];
	for( int n = 0; n < maxn; n++)
	{
		for( int m = 0; m < maxn; m++)
		{
			tmpbox[n][m] = m_box[n][m];
			if( tmpbox[n][m] == -1) //ȥ����ǰ��״
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

//�ܷ������ƶ�
bool MaTrixCheck::IsMove( int CRTL)
{
	//0���ƶ�, 1����
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

//�����ƶ�
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

		//��շ���
		ReleaseShapeInMap();
		ReleaseVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//��ӡ����
		M_pos.fty += dir;
		PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//���������
		MakeShapeInMap();
	}
	else  //�µķ���
	{
		//�ı�map
		ChangeTheMap();
		MakeVeilMap( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);

		//�ܷ�����
		IsRemoveFloor(); 

		//�����µķ���
		MakeNewMeTrix(); 
		
		//�ж��Ƿ��ܼ���
		if( IsDeadMeTrix()) 
		{
			//����
			MakeShapeInMap(); 

			IteratorShape( M_pos.fty + 2 + offsety, M_pos.ftx + maxn * 2 + offsetx, GetIteratorShape());  //��ӡ��һ������              
			PtfVeil( M_pos.fty + offsety, M_pos.ftx + offsetx, M_pos.x, M_pos.y);
		}
		else
		{
			//����
			ShowGameOver( maxn + offsety, 0);
			return true;
		}
	}
	return false;
}

void MaTrixCheck::MakeNewMeTrix()
{
	IteratShape();        //�µķ���
	
	M_pos.InitMTPoint();  //���ñ�־λ��
	GetShapePositon();    //�õ���־λ��

	
}

//�Ƿ�����
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

//����
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


//�ܷ�����
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
		if( j == maxn - 1) //����
		{
//			mark++; //����
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
	//�ı�
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
