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
		init();
	}
	void box::init()
	{
		const int INITIAL_VELOCITY = 6;
		x = y = index = delay_counter = 0;
		dx = dy = 35;
		floor = 0;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		inertia = false;
		isMovingLeft = false;
		int map_init[18][14] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,0,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,0,1,1,1,1,1,1,1,1},
			{0,0,1,1,1,1,1,1,1,0,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,0,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0}
		};
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				map[i][j] = map_init[i][j];
			}
		}
		int x_edge_init[15] = { 20,103,122,203,246,269,348,370,390,411,553,591,694,717,778 };
		for (int j = 0; j < 15; j++)
		{
			x_edge[j] = x_edge_init[j];
		}
		int y_edge_init[19] = { 21,84,102,127,148,187,229,247,267,311,328,349,413,432,458,474,496,515,578 };
		for (int j = 0; j < 19; j++)
		{
			y_edge[j] = y_edge_init[j];
		}

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
		int x1 = x;				// 球的左上角x座標
		int y1 = y;				// 球的左上角y座標
		int x2 = x1 + dx;	// 球的右下角x座標
		int y2 = y1 + dy;	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool box::OnBox(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	void box::setfloor()
	{
		if ((x + 20 >= 20 && x + 20 < 266 && y + 35 < 578 && y + 35 >= 515) || \
			(x + 20 >= 266 && x + 20 < 717 && y + 35 >= 474 && y + 35 < 578) || \
			(x + 20 >= 266 && x + 20 < 370 && y + 35 >= 433 && y + 35 < 474) || \
			(x + 20 >= 695 && x + 20 < 778 && y + 35 >= 350 && y + 35 < 517))
		{
			floor = 578 - 35;
		}
		else if (x + 20 >= 717 && x + 20 < 778 && y + 35 < 578 && y + 35 >= 350)
		{
			floor = 517 - 35;
		}
		else if ((x + 20 >= 20 && x + 20 < 266 && y + 35 >= 432 && y + 35 < 496))
		{
			floor = 496 - 35;
		}
		else if ((x + 20 >= 389 && x + 20 < 695 && y + 35 >= 350 && y + 35 < 458))
		{
			floor = 458 - 35;
		}
		else if ((x + 20 >= 20 && x + 20 < 392 && y + 35 >= 329 && y + 35 < 413) || \
			(x + 20 >= 20 && x + 20 < 103 && y + 35 >= 247 && y + 35 < 329))
		{
			floor = 413 - 35;
		}
		else if ((x + 20 >= 103 && x + 20 < 414 && y + 35 >= 247 && y + 35 < 311))
		{
			floor = 311 - 35;
		}
		else if ((x + 20 >= 414 && x + 20 < 591 && y + 35 >= 247 && y + 35 < 331) || \
			(x + 20 >= 591 && x + 20 < 778 && y + 40 >= 267 && y + 35 < 331) || \
			(x + 20 >= 694 && x + 20 < 778 && y + 40 >= 144 && y + 35 < 267))
		{
			floor = 331 - 35;
		}
		else if ((x + 20 >= 553 && x + 20 < 591 && y + 35 >= 144 && y + 35 < 247) || \
			(x + 20 >= 591 && x + 20 < 694 && y + 35 >= 144 && y + 35 < 267) || \
			(x + 20 >= 348 && x + 20 < 411 && y + 35 >= 144 && y + 35 < 229) || \
			(x + 20 >= 246 && x + 20 < 348 && y + 35 >= 186 && y + 35 < 229) || \
			(x + 20 >= 122 && x + 20 < 246 && y + 35 >= 102 && y + 35 < 229) || \
			(x + 20 >= 122 && x + 20 < 203 && y + 35 >= 21 && y + 35 < 102))
		{
			floor = 229 - 35;
		}
		else if ((x + 20 >= 411 && x + 20 < 553 && y + 40 >= 144 && y + 40 < 188))
		{
			floor = 188 - 35;
		}
		else if ((x + 20 >= 21 && x + 20 < 203 && y + 40 >= 21 && y + 40 < 229))
		{
			floor = 148 - 35;
		}
		else if ((x + 20 >= 203 && x + 20 < 269 && y + 40 >= 21 && y + 40 < 84))
		{
			floor = 84 - 35;
		}
		else if ((x + 20 >= 269 && x + 20 < 778 && y + 40 >= 21 && y + 40 < 102))
		{
			floor = 102 - 18;
		}
	}
	void box::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BOX, RGB(0, 0, 0));			// 載入球的圖形
	}
	bool box::isLeftRightEmpty(int x, int y, int value)
	{
		int x_coord = 0, ycoord = 0;
		if (x < 21 || x>778 || y < 21 || y>578)
		{
			return 0;
		}
		bool result = 1;
		if (value == 0) {
			for (int i = 0; i < 15; i++)
			{
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}
			for (int i = 0; i < 19; i++)
			{
				if (y + value >= y_edge[i]) {
					ycoord = i;
				}
			}
			result = map[ycoord][x_coord] && result;
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}

			for (int j = 5; j < 35; j += 3)
			{
				for (int i = 0; i < 19; i++)
				{
					if (y + j >= y_edge[i]) {
						ycoord = i;
					}
				}
				result = map[ycoord][x_coord] && result;
			}

		}

		return map[ycoord][x_coord];
	}
	void box::OnMove()
	{
		y = floor;
		if (isMovingLeft) {
			if (isLeftRightEmpty(x - 7, y, 1) && x > 20) {
				x -= 7;
				setfloor();
			}
			inertia = true;
			isMovingLeft = false;
		}
		if (inertia)
		{
			if (velocity > 0)
			{
				if (!isLeftRightEmpty(x - 1, y, 0))
				{
					velocity--;
				}
				else {
					x -= velocity;
					velocity--;
					setfloor();

					// 重設上升初始速度
				}
			}
			else {
				inertia = false;
				velocity = initial_velocity;
			}
		}	
	}
	void box::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void box::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
		setfloor();
		floor = ny;
	}
	void box::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void box::OnShow()
	{
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
}