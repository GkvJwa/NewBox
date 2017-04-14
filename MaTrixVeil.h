// MaTrixVeil.h: interface for the MaTrixVeil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXVEIL_H__2CDC8A73_67F9_4B63_B9DF_DF98F5B476B9__INCLUDED_)
#define AFX_MATRIXVEIL_H__2CDC8A73_67F9_4B63_B9DF_DF98F5B476B9__INCLUDED_

#define     DOUNNDARY      5
#define     INSIDE        ' '
#define     SHAPE_SIGN1    1
#define     SHAPE_SIGN2   ' '
#define     SHAPE_MAP      2

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MaTrixVeil  
{
public:
	static void IteratorShape( const int y, const int x, const int *shape);
	static void ReleaseVeil( const int fy, const int fx, const int * x, const int * y);
	static void PtfVeil( const int fy, const int fx, const int * x, const int * y);
	static void Gotoxy( const int y,  const int x);
	static void MakeVeilMap( const int fy, const int fx, const int * x, const int * y);
	static void IteratorVeil( const int y, const int x, const int type);
	static void ShowIteratorShapeBox( const int y, const int x);

public:
	static void SetColor( const int color);
	static void ShowMap( const fy, const fx, int ** map);
	static void ShowGameOver( const int y, const int x);

};

#endif // !defined(AFX_MATRIXVEIL_H__2CDC8A73_67F9_4B63_B9DF_DF98F5B476B9__INCLUDED_)
