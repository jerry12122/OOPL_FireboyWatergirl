#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class Button
	{
	public:
		Button();
		bool HitPlayer(RedPlayer *player);							// �O�_�I�����l
		bool HitPlayer(IcePlayer *player);
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnMove1();
		void OnShow();											// �N�ϧζK��e��
		void OnShow1();
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		int ReY();
		void SetIsAlive(bool alive);							// �]�w�O�_����
	protected:
		CMovingBitmap but, mo;			// �y����	
		int x, y;					// ��ߪ��y��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}