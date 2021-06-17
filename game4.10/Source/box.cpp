#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "box.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// box: Ball class
	/////////////////////////////////////////////////////////////////////////////

	box::box()
	{
		x = y = dx = dy = index = delay_counter = 0;
	}
	bool box::HitEraser(RedPlayer *redplayer)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(redplayer->GetX1(), redplayer->GetY1(),
			redplayer->GetX2(), redplayer->GetY2());
	}
	bool box::HitEraser(IcePlayer *iceplayer)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(iceplayer->GetX1(), iceplayer->GetY1(),
			iceplayer->GetX2(), iceplayer->GetY2());
	}

	bool box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
		/*
		if (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2)
		{
			re
		}*/
		return false;
	}
	bool box::OnBox(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	void box::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BOX, RGB(0, 0, 0));			// ���J�y���ϧ�
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// ���J�y��ߪ��ϧ�
	}

	void box::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
			//
			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	void box::SetDelay(int d)
	{
		delay = d;
	}

	void box::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void box::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void box::OnShow()
	{
		bmp.SetTopLeft(x + dx, y + dy);
		bmp.ShowBitmap();
	}
}