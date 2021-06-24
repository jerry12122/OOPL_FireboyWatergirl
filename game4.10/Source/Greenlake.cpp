#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "IcePlayer.h"
#include "Greenlake.h"

namespace game_framework {
	Greenlake::Greenlake()
	{
		x = y = 0;
		hack = false;
	}

	bool Greenlake::HitPlayer(RedPlayer *player)
	{

		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Greenlake::HitPlayer(IcePlayer *player)
	{

		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool Greenlake::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x +5;				// 球的左上角x座標
		int y1 = y -5;				// 球的左上角y座標
		int x2 = x1 + LAKE.Width() -10;	// 球的右下角x座標
		int y2 = y1 + LAKE.Height() - 5;	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}


	void Greenlake::LoadBitmap()
	{

		LAKE.LoadBitmap(GREEN_LAKE, RGB(255, 255, 255));			// 載入球的圖形

	}
	void Greenlake::OnMove()
	{
	}



	void Greenlake::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Greenlake::OnShow()
	{
		LAKE.SetTopLeft(x, y);
		LAKE.ShowBitmap();
	}
}
