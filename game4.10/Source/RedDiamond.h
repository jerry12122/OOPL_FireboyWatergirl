#include "Player.h"
#pragma once
namespace game_framework {
	class RedDiamond
	{
		public:
			RedDiamond();
			bool HitPlayer(Player *player);							// 是否碰到擦子
			bool IsAlive();											// 是否活著
			void LoadBitmap();										// 載入圖形
			void OnMove();											// 移動
			void OnShow();											// 將圖形貼到畫面
			void SetXY(int nx, int ny);								// 設定圓心的座標
			void SetIsAlive(bool alive);							// 設定是否活著
			void SetColor(int a);
			int GetColor();
		protected:
			CMovingBitmap bmp;			// 球的圖	
			int x, y;					// 圓心的座標
			int diamond_color;			// 鑽石顏色 0:紅 1:藍
			bool is_alive;				// 是否活著
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}
