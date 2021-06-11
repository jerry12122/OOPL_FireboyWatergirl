
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
		int x1 = x;				// 球的左上角x座標
		int y1 = y;				// 球的左上角y座標
		int x2 = x1 + rm.Width();	// 球的右下角x座標
		int y2 = y1 + rm.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Mood::HitHitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// 球的左上角x座標
		int y1 = y;				// 球的左上角y座標
		int x2 = x1 + lm.Width();	// 球的右下角x座標
		int y2 = y1 + lm.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
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