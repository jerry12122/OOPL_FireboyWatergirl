#include "IcePlayer.h"
#include "RedPlayer.h"
#include <fstream> 
extern bool current_rank;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class box
	{
	public:
		box();
		void init();
		int x, y;					// 擦子左上角座標
		bool HitEraser(RedPlayer *redplayer);						// 是否碰到擦子
		bool HitEraser(IcePlayer *iceplayer);						// 是否碰到擦子
		//bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		bool isLeftRightEmpty(int x, int y, int value);
		void setfloor();// 設定旋轉的速度
		bool OnBox(int tx1, int ty1, int tx2, int ty2);
		int GetX1();
		int GetY1();
	protected:
		CMovingBitmap bmp;			// 球的圖	
		CGameMap gamemap;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int dx, dy;					// 球距離圓心的位移量
		int floor;
		int index;					// 球的「角度」，0-17表示0-360度
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		int map[60][80];
		int x_edge[800];
		int y_edge[600];
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形

		bool inertia;
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
	};
}