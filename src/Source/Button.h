#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class�O���s�M�W�ɱ쪺Class
/////////////////////////////////////////////////////////////////////////////
	class Button
	{
	public:
		Button();
		bool HitPlayer(RedPlayer *player);							// �O�_�I�쪱�a
		bool HitPlayer(IcePlayer *player);
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnMove1();
		void OnMove2();
		void OnMove3();
		void OnShow();											// �N�ϧζK��e��
		void OnShow1();
		void OnShow2();
		void OnShow3();
		void SetXY(int nx, int ny);								// �]�w�y��
		int GetY();
		int GetX();
		void SetIsAlive(bool alive);							// �]�w�O�_����
	protected:
		CMovingBitmap but, mo ,mo2 ,mo3;			
		int x, y;					// �y��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}