#pragma once
#include <fstream> 
extern bool current_rank;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		RedPlayer();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
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
		CAnimation animation, animation1;		// ���l���ʵe
		CMovingBitmap bit;
		CGameMap gamemap;
		static CGameMap getMap();
=======
		void Addgem();
		int getgem();
		string Getcharacteristic();
	protected:
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
		int x, y;					// ���l���W���y��
		int gem = 0;
		CAnimation animation;
		string character;
		bool upEnable;
		bool setFloorEnable;
		int floor;
		int ceil;
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��		
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
<<<<<<< HEAD
		bool isFrontBox;
		bool isOnBox;
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
=======
		int direction;
		int times;
		int step_size;
		int stop_down;

>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
	};
}