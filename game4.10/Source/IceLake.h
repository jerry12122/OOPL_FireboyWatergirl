#include "RedPlayer.h"
#pragma once
namespace game_framework {
	class IceLake
	{
	public:
		IceLake();
		bool HitPlayer(RedPlayer *player);							// �O�_�I�����l
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
	protected:
		CMovingBitmap LAKE;			// �y����	
		int x, y;					// ��ߪ��y��
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
