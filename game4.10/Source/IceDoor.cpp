#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "IcePlayer.h"
#include "IceDoor.h"

namespace game_framework {
	IceDoor::IceDoor()
	{
		is_alive = true;
		x = y = 0;
	}

	bool IceDoor::HitPlayer(IcePlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool IceDoor::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// �y�����W��x�y��
		int y1 = y ;				// �y�����W��y�y��
		int x2 = x1 + door.Width();	// �y���k�U��x�y��
		int y2 = y1 + door.Height();	// �y���k�U��y�y��
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool IceDoor::IsAlive()
	{
		return is_alive;
	}

	void IceDoor::LoadBitmap()
	{
		door.LoadBitmap(ICE_DOOR_CLOSE, RGB(255, 255, 255));			
		bmp2.LoadBitmap(DOOR_OPEN, RGB(255, 255, 255));			
	}

	void IceDoor::OnMove()
	{
	}

	void IceDoor::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void IceDoor::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void IceDoor::OnShow()
	{
		if (is_alive) {
			door.SetTopLeft(x, y);
			door.ShowBitmap();
		}
		else {
			bmp2.SetTopLeft(x, y);
			bmp2.ShowBitmap();
		}
	}
}