#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "IcePlayer.h"
#include "Greenlake.h"

namespace game_framework {
	Greenlake::Greenlake()
	{
		x = y = 0;
		hack = false;
	}

	bool Greenlake::HitPlayer(RedPlayer *player)
	{

		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Greenlake::HitPlayer(IcePlayer *player)
	{

		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool Greenlake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x +5;				// �y�����W��x�y��
		int y1 = y -5;				// �y�����W��y�y��
		int x2 = x1 + LAKE.Width() -10;	// �y���k�U��x�y��
		int y2 = y1 + LAKE.Height() - 5;	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}


	void Greenlake::LoadBitmap()
	{

		LAKE.LoadBitmap(GREEN_LAKE, RGB(255, 255, 255));			// ���J�y���ϧ�

	}
	void Greenlake::OnMove()
	{
	}



	void Greenlake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Greenlake::OnShow()
	{
		LAKE.SetTopLeft(x, y);
		LAKE.ShowBitmap();
	}
}
