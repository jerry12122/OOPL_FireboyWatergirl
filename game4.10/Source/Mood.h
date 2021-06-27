#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class�O�Ա쪺Class
	/////////////////////////////////////////////////////////////////////////////
	class Mood
	{
		public:
			Mood();
			bool HitPlayer(RedPlayer *player);						// �O�_�I�쪱�a
			bool HitPlayer(IcePlayer *player);
			bool IsAlive();											// �O�_����
			void LoadBitmap();										// ���J�ϧ�
			void OnMove();											// ����
			void OnMove1();
			void OnShow();											// �N�ϧζK��e��
			void OnShow1();
			void SetXY(int nx, int ny);								// �]�w�y��
			int ReY();
			void SetIsAlive(bool alive);							// �]�w�O�_����
		protected:
			CMovingBitmap rm ,mm ,lm, mo , mo2;			
			int x, y;					// �y��
			bool is_alive;				// �O�_����
		private:
			bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��

	};
}