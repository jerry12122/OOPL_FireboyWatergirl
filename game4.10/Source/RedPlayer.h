#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class RedPlayer
	{
	public:
		RedPlayer();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetFloor(int);
		void SetVelocity(int);
		bool isLeftRightEmpty(int x, int y, int value);
		int getCoordX(int x, int y);
		int getCoordY(int x, int y);
		void setfloor();
		bool frontBox(int x,int y);
		bool onBox(int x, int y);
		void setFront(bool a);
		void setOnBox(bool a);

	protected:
		CAnimation animation, animation1;		// 擦子的動畫
		CMovingBitmap bit;
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isFrontBox;
		bool isOnBox;
		int floor;				// 地板的Y座標
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		int map[18][14];
		int x_edge[15];
		int y_edge[19];
	};
}