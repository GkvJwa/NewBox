// MaTrixGame.h: interface for the MeTrixGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXGAME_H__BDFB8097_5420_4C31_8C9D_151EACAA34F6__INCLUDED_)
#define AFX_MATRIXGAME_H__BDFB8097_5420_4C31_8C9D_151EACAA34F6__INCLUDED_

#define     UP      0x48
#define     DOWN    0x50
#define     LEFT    0x4B
#define     RIGHT   0x4D
#define     PUASE   0x20

typedef enum{ MyLEFT, MyRIGHT}MyConTrol;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class MaTrixGame : public MaTrixCheck  
{
private:
	int GSetTime;

public:
	void GameConTrol();
	void GameStart();
	int  GetGameCONTROL();

public:	
	MaTrixGame();
	~MaTrixGame();

};

#endif // !defined(AFX_MATRIXGAME_H__BDFB8097_5420_4C31_8C9D_151EACAA34F6__INCLUDED_)
