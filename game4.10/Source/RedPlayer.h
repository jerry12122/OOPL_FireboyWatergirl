#pragma once
#include <fstream> 
extern bool current_rank;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap {
	public:
		CGameMap();
		CGameMap(int _stage);
		~CGameMap();
		void LoadBitmap();
		void OnShow();
		void setMap(int x, int y, int v);
		void SetStage(int _stage);
		void ReadFile(int stages);
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


	class RedPlayer {

	public:
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetButton(bool flag);
		void SetButton2(bool flag);
		void SetButton3(bool flag);
		void SetMood(bool flag);
		void MoodY(int MY);
		RedPlayer();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize(int stages);				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnMove1();
		void OnShow();					// �N���l�ϧζK��e��
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetFloor(int y);
		void SetVelocity(int);
		bool isLeftRightEmpty(int x, int y, int value);
		int getCoordX(int x, int y);
		int getCoordY(int x, int y);
		void setfloor();

		bool frontBox(int x, int y);
		bool onBox(int x, int y);
		bool butin();
		bool isOnButton;
		void setFront(bool a);
		void setOnBox(bool a);
		int map[60][80];
		int x_edge[800];
		int y_edge[600];
		int floor;
	protected:
		CAnimation animation, animation1;		// ���l���ʵe
		CMovingBitmap bit;
		CGameMap gamemap;
		int x, y;					// ���l���W���y��
		int xxx, yyy;
		int gem = 0;
		string character;
		bool upEnable;
		bool setFloorEnable;
		
		int ceil;
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��		
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isFrontBox;
		bool isOnBox;
		bool isButton;
		bool isButton2;
		bool isButton3;
		bool isMood;
		bool isBox;
		int  MY, pot, dot;
		int stage;
	};
}