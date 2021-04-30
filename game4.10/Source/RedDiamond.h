#include "Player.h"
#pragma once
namespace game_framework {
	class RedDiamond
	{
		public:
			RedDiamond();
			bool HitPlayer(Player *player);							// �O�_�I�����l
			bool IsAlive();											// �O�_����
			void LoadBitmap();										// ���J�ϧ�
			void OnMove();											// ����
			void OnShow();											// �N�ϧζK��e��
			void SetXY(int nx, int ny);								// �]�w��ߪ��y��
			void SetIsAlive(bool alive);							// �]�w�O�_����
			void SetColor(int a);
			int GetColor();
		protected:
			CMovingBitmap bmp;			// �y����	
			int x, y;					// ��ߪ��y��
			int diamond_color;			// �p���C�� 0:�� 1:��
			bool is_alive;				// �O�_����
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
