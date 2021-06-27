#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class是拉桿的Class
	/////////////////////////////////////////////////////////////////////////////
	class Mood
	{
		public:
			Mood();
			bool HitPlayer(RedPlayer *player);						// 是否碰到玩家
			bool HitPlayer(IcePlayer *player);
			bool IsAlive();											// 是否活著
			void LoadBitmap();										// 載入圖形
			void OnMove();											// 移動
			void OnMove1();
			void OnShow();											// 將圖形貼到畫面
			void OnShow1();
			void SetXY(int nx, int ny);								// 設定座標
			int ReY();
			void SetIsAlive(bool alive);							// 設定是否活著
		protected:
			CMovingBitmap rm ,mm ,lm, mo , mo2;			
			int x, y;					// 座標
			bool is_alive;				// 是否活著
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形

	};
}