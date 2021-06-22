namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void setfloor(int _floor);
		void setceil(int _ceil);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		bool GetMovingLeft();
		bool GetMovingRight();
		bool GetMovingUp();
		bool GetUpEnable();
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
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
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��
		int x, y;					// ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		int direction;
		int times;
		int step_size;
		int gem = 0;
		int stop_down;
		string character;
		CAnimation animation;		// �Q�ΰʵe�@�ϧ�
	};
}