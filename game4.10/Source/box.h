#include "IcePlayer.h"
#include "RedPlayer.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class box
	{
	public:
		box();
		int x, y;					// 擦子左上角座標
		bool HitEraser(RedPlayer *redplayer);						// 是否碰到擦子
		bool HitEraser(IcePlayer *iceplayer);						// 是否碰到擦子
		//bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetDelay(int d);									// 設定旋轉的速度
	protected:
		CMovingBitmap bmp;			// 球的圖	

		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int dx, dy;					// 球距離圓心的位移量
		int index;					// 球的「角度」，0-17表示0-360度
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		bool OnBox(int tx1, int ty1, int tx2, int ty2);
	};
}