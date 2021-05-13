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
		is_alive = true;
		x = y = 0;
	}

	bool RedLake::HitPlayer(IcePlayer *player)
	{

		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedLake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + 5;				// �y�����W��x�y��
		int y1 = y + 5;				// �y�����W��y�y��
		int x2 = x1 + LAKE.Width() - 5;	// �y���k�U��x�y��
		int y2 = y1 + LAKE.Height() - 5;	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool RedLake::IsAlive()
	{
		return is_alive;
	}

	void RedLake::LoadBitmap()
	{

		LAKE.LoadBitmap(FIRE_LAKE, RGB(255, 255, 255));			// ���J�y���ϧ�

	}
	void RedLake::OnMove()
	{
		if (!is_alive)
			return;
	}

	void RedLake::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void RedLake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void RedLake::OnShow()
	{
		if (is_alive) {
			LAKE.SetTopLeft(x,y);
			LAKE.ShowBitmap();
		}
	}
}
