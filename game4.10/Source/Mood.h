#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class Mood
	{
		public:
			Mood();
			bool HitPlayer(RedPlayer *player);							// �O�_�I�����l
			bool HitPlayer(IcePlayer *player);
			bool HitHitPlayer(RedPlayer *player);
			bool HitHitPlayer(IcePlayer *player);
			bool IsAlive();											// �O�_����
			void LoadBitmap();										// ���J�ϧ�
			void OnMove();											// ����
			void OnShow();											// �N�ϧζK��e��
			void OnShow1();
			void SetXY(int nx, int ny);								// �]�w��ߪ��y��
			void SetIsAlive(bool alive);							// �]�w�O�_����
		protected:
			CMovingBitmap rm ,mm ,lm, mo;			// �y����	
			int x, y;					// ��ߪ��y��
			bool is_alive;				// �O�_����
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
			bool HitHitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}
