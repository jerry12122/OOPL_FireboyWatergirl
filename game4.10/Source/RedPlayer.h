#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	

	class RedPlayer {
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
		void Addgem();
		int getgem();
		string Getcharacteristic();
	protected:
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
		int direction;
		int times;
		int step_size;
		int stop_down;

	};
}