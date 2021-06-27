#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "IcePlayer.h"
#include "RedLake.h"

namespace game_framework {
	RedLake::RedLake()
	{
		this->hack = false;
		x = y = 0;
	}

	bool RedLake::HitPlayer(IcePlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedLake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x +15;				// ���a�����W��x�y��
		int y1 = y -5;				// ���a�����W��y�y��
		int x2 = x1 + LAKE.Width() -30;	// ���a���k�U��x�y��
		int y2 = y1 + LAKE.Height() -5;	// ���a���k�U��y�y��
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}


	void RedLake::LoadBitmap()
	{
		LAKE.LoadBitmap(FIRE_LAKE, RGB(255, 255, 255));		
	}

	void RedLake::OnMove()
	{
	}

	void RedLake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;

	}

	void RedLake::OnShow()
	{
		LAKE.SetTopLeft(x, y);
		LAKE.ShowBitmap();
	}
}
