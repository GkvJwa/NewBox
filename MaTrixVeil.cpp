// MaTrixVeil.cpp: implementation of the MaTrixVeil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void MaTrixVeil::Gotoxy( const int y, const int x)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);	
}

void MaTrixVeil::SetColor(const int color)
{    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MaTrixVeil::PtfVeil( const int fy, const int fx, const int * x, const int * y)
{
	for( int i = 0; i < 4; i++)
	{
		Gotoxy( fy + y[i], fx + x[i]);
		printf("%c", SHAPE_SIGN1);
	}
}

void MaTrixVeil::ReleaseVeil( const int fy, const int fx, const int * x, const int * y)
{
	for( int i = 0; i < 4; i++)
	{
		Gotoxy( fy + y[i], fx + x[i]);
		printf("%c", SHAPE_SIGN2);
	}
}

void MaTrixVeil::MakeVeilMap( const int fy, const int fx, const int * x, const int * y)
{
	for( int i = 0; i < 4; i++)
	{
		Gotoxy( fy + y[i], fx + x[i]);
		printf("%c", SHAPE_MAP);
	}
}

void MaTrixVeil::IteratorVeil( const int y, const int x, const int type)
{
	Gotoxy(y,x);
	printf( "%c", !type ? SHAPE_SIGN2 : SHAPE_MAP);
}

void MaTrixVeil::ShowIteratorShapeBox(const int y, const int x)
{
	for( int i = 0; i < 36; i++)
	{
		Gotoxy(y + (i / 6),x + (i % 6));
		printf("%c", DOUNNDARY);
	}	
}

void MaTrixVeil::IteratorShape(const int y, const int x, const int *shape)
{
	for( int i = 0; i < 16; i++)
	{
		Gotoxy( y + (i/4), x + (i%4));
		printf( "%c", shape[i] ? SHAPE_SIGN1 : SHAPE_SIGN2);
	}
}

void MaTrixVeil::ShowGameOver( const int y, const int x)
{
	Gotoxy( y, x);
	printf("Oh, Game Over!~\n");
}

void MaTrixVeil::ShowMap(const int fy, const int fx, int **map)
{
	for( int i = 0; i < maxn; i++)
	{
		Gotoxy( fy - 1, fx + i);
		printf("%c", DOUNNDARY);
	}
	for( int y = 0; y < maxn * maxn; y++)
	{
		Gotoxy( fy + y / maxn, fx + y % maxn);
		printf( "%c", *((int *)map + y) ? DOUNNDARY : INSIDE);
	}
}


