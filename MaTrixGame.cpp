// MaTrixGame.cpp: implementation of the MeTrixGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MaTrixGame::MaTrixGame():GSetTime(400)
{

}

MaTrixGame::~MaTrixGame()
{

}

void MaTrixGame::GameStart()
{  
	do 
	{
	} while (GetGameCONTROL());
}


int MaTrixGame::GetGameCONTROL()
{
	if( kbhit())
	{
		char Control = getch();
		switch( Control)
		{
			case UP:
			{
				ChangeShape();
				break;
			}
			case DOWN:
			{
				if( DNMoveMeTrix())
				{
					return 0;
				}
				MakeShapeInMap();
				break;
			}
			case LEFT:
			{
				RLMoveMeTrix(MyLEFT);
				MakeShapeInMap();
				break;
			}
			case RIGHT:
			{
				RLMoveMeTrix(MyRIGHT);
				MakeShapeInMap();
				break;
			}
			case PUASE:
			{
				getch();
				break;
			}
		}
	}
	else
	{
		Sleep(GSetTime);
		if( DNMoveMeTrix())
		{
			return 0;
		}
		MakeShapeInMap();
	}
	return 1;
}
