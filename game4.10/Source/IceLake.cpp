#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "IceLake.h"

namespace game_framework {
	IceLake::IceLake()
	{
		is_alive = true;
		x = y = 0;
	}

	bool IceLake::HitPlayer(RedPlayer *player)
	{

		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool IceLake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x+5;				// 球的左上角x座標
		int y1 = y+5;				// 球的左上角y座標
		int x2 = x1 + LAKE.Width()-5;	// 球的右下角x座標
		int y2 = y1 + LAKE.Height()-5;	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool IceLake::IsAlive()
	{
		return is_alive;
	}

	void IceLake::LoadBitmap()
	{

		LAKE.LoadBitmap(ICE_LAKE, RGB(255, 255, 255));			// 載入球的圖形

	}
	void IceLake::OnMove()
	{
		if (!is_alive)
			return;
	}

	void IceLake::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void IceLake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void IceLake::OnShow()
	{
		if (is_alive) {
			LAKE.SetTopLeft(x, y);
			LAKE.ShowBitmap();
			//LAKE.SetTopLeft(530, 573);
			//LAKE.ShowBitmap();
			//LAKE.SetTopLeft(448, 326);
			//LAKE.ShowBitmap();
			//LAKE.SetTopLeft(465, 122);
			//LAKE.ShowBitmap();
		}
	}
}
