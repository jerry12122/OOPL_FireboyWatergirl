
#include "RedPlayer.h"
#include "IcePlayer.h"
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Button.h"


namespace game_framework {
	Button::Button()
	{
		is_alive = true;
		x = y = 0;
	}

	bool Button::HitPlayer(IcePlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}
	bool Button::HitPlayer(RedPlayer *player)
	{
		return HitRectangle(player->GetX1(), player->GetY1(),
			player->GetX2(), player->GetY2());
	}

	bool Button::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + but.Width();	// �y���k�U��x�y��
		int y2 = y1 + but.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Button::IsAlive()
	{
		return is_alive;
	}

	void Button::LoadBitmap()
	{

		but.LoadBitmap(BUTTON_1, RGB(255, 255, 255));
		mo.LoadBitmap(MOOD, RGB(255, 255, 255));

	}
	void Button::OnMove()
	{
		return;
	}
	void Button::OnMove1()
	{
		if (is_alive)
			if (y > 228) {
				y -= 1;
			}
			else {
				y = y;
			}
		else {
			if (y < 310) {
				y += 1;
			}
			else {
				y = y;
			}
		}
		return;
	}

	void Button::SetIsAlive(bool alive)
	{
		is_alive = alive;

	}

	void Button::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	int Button::ReY()
	{
		return y;
	}

	void Button::OnShow()
	{
		if (is_alive) {
			but.SetTopLeft(x, y);
			but.ShowBitmap();
		}
		else {
		}
	}
	void Button::OnShow1()
	{
		if (is_alive) {
			mo.SetTopLeft(x, y);
			mo.ShowBitmap();
		}
		else {
			mo.SetTopLeft(x, y);
			mo.ShowBitmap();
		}
	}
}