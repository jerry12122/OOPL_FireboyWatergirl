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
		diamond_color = 0;
		is_alive = true;
		x = y = 0;
	}

	bool RedDiamond::HitPlayer(Player *player)
	{

		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool RedDiamond::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// 球的左上角x座標
		int y1 = y ;				// 球的左上角y座標
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
		if (diamond_color == 0)
			bmp.LoadBitmap(FIRE_DIAMOND, RGB(255, 255, 255));			// 載入球的圖形
		else
			bmp.LoadBitmap(ICE_DIAMOND, RGB(255, 255, 255));			// 載入球的圖形
	}
	void RedDiamond::OnMove()
	{
		if (!is_alive)
			return;
	}
	int RedDiamond::GetColor()
	{
		return diamond_color;
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
			bmp.SetTopLeft(x , y );
			bmp.ShowBitmap();
		}
	}
}