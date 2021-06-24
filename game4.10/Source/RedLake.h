#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class RedLake
	{
	public:
		RedLake();
		bool HitPlayer(IcePlayer *player);							// 是否碰到擦子
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);		
		bool hack;// 設定圓心的座標
	protected:
		CMovingBitmap LAKE;			// 球的圖	
		int x, y;					// 圓心的座標
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}

