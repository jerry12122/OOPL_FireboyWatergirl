#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"
#include "RedDiamond.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// RedDiamond: Ball class
	/////////////////////////////////////////////////////////////////////////////
	RedDiamond::RedDiamond()
	{
		diamond_color = 1;
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}
	/*RedDiamond::RedDiamond(int color)
	{
		diamond_color = color;
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}*/

	bool RedDiamond::HitPlayer(Player *player)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedDiamond::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool RedDiamond::IsAlive()
	{
		return is_alive;
	}

	void RedDiamond::LoadBitmap()
	{
		bmp.LoadBitmap(ICE_DIAMOND, RGB(0, 0, 0));			// 載入球的圖形
	}
	
	

	void RedDiamond::SetDelay(int d)
	{
		delay = d;
	}
	void RedDiamond::SetColor(int a)
	{
		diamond_color = a;
	}
	void RedDiamond::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void RedDiamond::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void RedDiamond::OnShow()
	{
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			bmp_center.SetTopLeft(x, y);
			bmp_center.ShowBitmap();
		}
	}
}