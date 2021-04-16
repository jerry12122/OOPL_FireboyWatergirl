#include "Player.h"
#pragma once
namespace game_framework {
	class RedDiamond
	{
		public:
			RedDiamond();
			//RedDiamond(int color);
			bool HitPlayer(Player *player);							// �O�_�I�����l
			bool IsAlive();											// �O�_����
			void LoadBitmap();										// ���J�ϧ�
			//void OnMove();											// ����
			void OnShow();											// �N�ϧζK��e��
			void SetXY(int nx, int ny);								// �]�w��ߪ��y��
			void SetIsAlive(bool alive);							// �]�w�O�_����
			void SetDelay(int d);									// �]�w���઺�t��
			void SetColor(int a);
		protected:
			CMovingBitmap bmp;			// �y����
			CMovingBitmap bmp_center;	// ��ߪ���			
			int x, y;					// ��ߪ��y��
			int dx, dy;					// �y�Z����ߪ��첾�q
			int index;					// �y���u���סv�A0-17���0-360��
			int delay_counter;			// �վ����t�ת��p�ƾ�
			int delay;					// ���઺�t��
			int diamond_color;					// �p���C�� 0:�� 1:��
			bool is_alive;				// �O�_����
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
