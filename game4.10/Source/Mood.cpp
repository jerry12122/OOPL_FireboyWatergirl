
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

	bool Mood::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + rm.Width();				// 球的左上角x座標
		int y1 = y;				// 球的左上角y座標
		int x2 = x + rm.Width();	// 球的右下角x座標
		int y2 = y1 + rm.Height();	// 球的右下角y座標
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
		mo.LoadBitmap(MOOD, RGB(255, 255, 255));

	}
	void Mood::OnMove()
	{
		return;
	}
	void Mood::OnMove1()
	{
		if (is_alive)
			if (y >= 310) {
				y -= 1;
			}
			else {
				y = y;
			}
		else {
			if (y <=370) {
				y += 1;
			}
			else {
				y = y;
			}
		}
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

	int Mood::ReY()
	{
		return y;
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
	void Mood::OnShow1()
	{
		if (is_alive) {
			mo.SetTopLeft(x, y);
			mo.ShowBitmap();
		}
		else {
			mo.SetTopLeft(x, y);
			mo.ShowBitmap();
		}
	}
}