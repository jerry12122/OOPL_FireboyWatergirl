#include "RedPlayer.h"
#include "IcePlayer.h"
#pragma once
namespace game_framework {
	class Greenlake
	{
	public:
		Greenlake();
		bool HitPlayer(RedPlayer *player);							
		bool HitPlayer(IcePlayer *player);
		void LoadBitmap();										
		void OnMove();											
		void OnShow();											
		void SetXY(int nx, int ny);
		bool hack;											
	protected:
		CMovingBitmap LAKE;			
		int x, y;					
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	
	};
}
