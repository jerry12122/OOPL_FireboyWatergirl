#pragma once
#include <fstream> 
extern bool current_rank;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD

	class CGameMap {
	public:
		CGameMap();
		CGameMap(int _stage);
		~CGameMap();
		void LoadBitmap();
		void OnShow();
		void setMap(int x, int y, int v);
		void SetStage(int _stage);
		void ReadFile();
		int remap();
		int mapCoordinate(int x, int y);
		int GetX();
		int GetY();
		int GetMW();
		int GetMH();
		int GetSizeX();
		int GetSizeY();
		int GetStage();
	protected:
		CMovingBitmap blue, green;
		//int **map;
		//bool map[60][80];
		int map[60][80];
		int X, Y;
		int MW, MH;
		int sizeX, sizeY;
		int stage;
	};

	class RedPlayer
	{
=======
	

	class RedPlayer {
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
	public:
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		RedPlayer();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
<<<<<<< HEAD
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
		int map[60][80];
		int x_edge[800];
		int y_edge[600];

	protected:
		CAnimation animation, animation1;		// 擦子的動畫
		CMovingBitmap bit;
		CGameMap gamemap;
		static CGameMap getMap();
=======
		void Addgem();
		int getgem();
		string Getcharacteristic();
	protected:
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
		int x, y;					// 擦子左上角座標
		int gem = 0;
		CAnimation animation;
		string character;
		bool upEnable;
		bool setFloorEnable;
		int floor;
		int ceil;
		int velocity;			// 目前的速度(點/次)
		int initial_velocity;	// 初始速度
		bool rising;				// true表上升、false表下降		
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
<<<<<<< HEAD
		bool isFrontBox;
		bool isOnBox;
		int floor;				// 地板的Y座標
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
=======
		int direction;
		int times;
		int step_size;
		int stop_down;

>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
	};
}