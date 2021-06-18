#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class Greenlake
	{
	public:
		Greenlake();
		bool HitPlayer(RedPlayer *player);							// �O�_�I�����l
		bool HitPlayer(IcePlayer *player);
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);
		bool hack;// �]�w��ߪ��y��
	protected:
		CMovingBitmap LAKE;			// �y����	
		int x, y;					// ��ߪ��y��
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
