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

		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedDoor::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool RedDoor::IsAlive()
	{
		return is_alive;
	}

	void RedDoor::LoadBitmap()
	{

		bmp.LoadBitmap(FIRE_DOOR_CLOSE, RGB(255, 255, 255));			// ���J�y���ϧ�
		bmp2.LoadBitmap(DOOR_OPEN, RGB(255, 255, 255));			// ���J�y���ϧ�


	}

	void RedDoor::OnMove()
	{
		if (!is_alive)
			return;
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
			bmp.SetTopLeft(x, y);
			bmp.ShowBitmap();
		}
	}
}