#include "IcePlayer.h"
#include "RedPlayer.h"
#include <fstream> 
extern bool current_rank;
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class box
	{
	public:
		box();
		void init();
		int x, y;					// ���l���W���y��
		bool HitEraser(RedPlayer *redplayer);						// �O�_�I�����l
		bool HitEraser(IcePlayer *iceplayer);						// �O�_�I�����l
		//bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		bool isLeftRightEmpty(int x, int y, int value);
		void setfloor();// �]�w���઺�t��
		bool OnBox(int tx1, int ty1, int tx2, int ty2);
		int GetX1();
		int GetY1();
	protected:
		CMovingBitmap bmp;			// �y����	
		CGameMap gamemap;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		int dx, dy;					// �y�Z����ߪ��첾�q
		int floor;
		int index;					// �y���u���סv�A0-17���0-360��
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		int map[60][80];
		int x_edge[800];
		int y_edge[600];
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��

		bool inertia;
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
	};
}