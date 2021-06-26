#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "RedDoor.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// RedDoor: Ball class
	/////////////////////////////////////////////////////////////////////////////
	RedDoor::RedDoor()
	{
		is_alive = true;
		x = y = 0;
	}
	bool RedDoor::HitPlayer(RedPlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedDoor::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// 球的左上角x座標
		int y1 = y ;				// 球的左上角y座標
		int x2 = x1 + doors.Width();	// 球的右下角x座標
		int y2 = y1 + doors.Height();	// 球的右下角y座標
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool RedDoor::IsAlive()
	{
		return is_alive;
	}

	void RedDoor::LoadBitmap()
	{
		doors.LoadBitmap(FIRE_DOOR_CLOSE, RGB(255, 255, 255));	
		bmp2.LoadBitmap(DOOR_OPEN, RGB(255, 255, 255));			
	}

	void RedDoor::OnMove()
	{
	}

	void RedDoor::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void RedDoor::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void RedDoor::OnShow()
	{
		if (is_alive) {
			doors.SetTopLeft(x, y);
			doors.ShowBitmap();
		}
		else {
			bmp2.SetTopLeft(x, y);
			bmp2.ShowBitmap();
		}
	}
}