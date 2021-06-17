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
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(redplayer->GetX1(), redplayer->GetY1(),
			redplayer->GetX2(), redplayer->GetY2());
	}
	bool box::HitEraser(IcePlayer *iceplayer)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(iceplayer->GetX1(), iceplayer->GetY1(),
			iceplayer->GetX2(), iceplayer->GetY2());
	}

	bool box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
		/*
		if (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2)
		{
			re
		}*/
		return false;
	}
	bool box::OnBox(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	void box::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BOX, RGB(0, 0, 0));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}

	void box::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
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