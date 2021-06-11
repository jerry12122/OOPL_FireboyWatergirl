
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "IcePlayer.h"
#include "Mood.h"


namespace game_framework {
	Mood::Mood()
	{
		is_alive = true;
		x = y = 0;
	}

	bool Mood::HitPlayer(RedPlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Mood::HitPlayer(IcePlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Mood::HitHitPlayer(RedPlayer *player)
	{
		return HitHitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Mood::HitHitPlayer(IcePlayer *player)
	{
		return HitHitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool Mood::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + rm.Width();	// �y���k�U��x�y��
		int y2 = y1 + rm.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Mood::HitHitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + lm.Width();	// �y���k�U��x�y��
		int y2 = y1 + lm.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Mood::IsAlive()
	{
		return is_alive;
	}

	void Mood::LoadBitmap()
	{

		rm.LoadBitmap(RIGHT_MOOD, RGB(255, 255, 255));
		mm.LoadBitmap(MID_MOOD, RGB(255, 255, 255));
		lm.LoadBitmap(LEFT_MOOD, RGB(255, 255, 255));

	}
	void Mood::OnMove()
	{
		if (!is_alive)
			return;
	}

	void Mood::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Mood::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Mood::OnShow()
	{
		if (is_alive) {
			rm.SetTopLeft(x, y);
			rm.ShowBitmap();
		}
		else {
			lm.SetTopLeft(x, y);
			lm.ShowBitmap();
		}
	}
}