namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CEraser
	{
	public:
		CEraser();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		int GetVelocity();
		int GetFloor();
		bool OnFloor();
		bool getRising();
		int getStep();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void setfloor(int _floor);
		void setceil(int _ceil);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		bool GetMovingLeft();
		bool GetMovingRight();
		bool GetMovingUp();
		bool GetUpEnable();
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void Addgem();
		void SetStepSize(int _step);
		void SetStopDown(int y);
		int getgem();
		void SetUpEnable(bool flag);
		void SetFloorEnable(bool flag);
		void SetVelocity(int v);
		string Getcharacteristic();
	protected:
		bool upEnable;
		bool setFloorEnable;
		int floor;
		int ceil;
		int velocity;			// 目前的速度(點/次)
		int initial_velocity;	// 初始速度
		bool rising;				// true表上升、false表下降
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int direction;
		int times;
		int step_size;
		int gem = 0;
		int stop_down;
		string character;
		CAnimation animation;		// 利用動畫作圖形
	};
}