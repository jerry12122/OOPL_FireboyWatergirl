#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class Mood
	{
		public:
			Mood();
			bool HitPlayer(RedPlayer *player);							// 是否碰到擦子
			bool HitPlayer(IcePlayer *player);
			bool HitHitPlayer(RedPlayer *player);
			bool HitHitPlayer(IcePlayer *player);
			bool IsAlive();											// 是否活著
			void LoadBitmap();										// 載入圖形
			void OnMove();											// 移動
			void OnShow();											// 將圖形貼到畫面
			void OnShow1();
			void SetXY(int nx, int ny);								// 設定圓心的座標
			void SetIsAlive(bool alive);							// 設定是否活著
		protected:
			CMovingBitmap rm ,mm ,lm, mo;			// 球的圖	
			int x, y;					// 圓心的座標
			bool is_alive;				// 是否活著
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
			bool HitHitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}
