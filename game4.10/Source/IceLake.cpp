#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "IceLake.h"

namespace game_framework {
	IceLake::IceLake()
	{
		x = y = 0;
		hack = false;
	}

	bool IceLake::HitPlayer(RedPlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool IceLake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x+15;				// ���a�����W��x�y��
		int y1 = y-5;				// ���a�����W��y�y��
		int x2 = x1 + LAKE.Width()-30;	// ���a���k�U��x�y��
		int y2 = y1 + LAKE.Height();	// ���a���k�U��y�y��
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void IceLake::LoadBitmap()
	{
		LAKE.LoadBitmap(ICE_LAKE, RGB(255, 255, 255));
	}
	void IceLake::OnMove() {

	}




	void IceLake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void IceLake::OnShow()
	{
		LAKE.SetTopLeft(x, y);
		LAKE.ShowBitmap();
	}
}
