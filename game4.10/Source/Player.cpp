#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Player: Player class
	/////////////////////////////////////////////////////////////////////////////

	Player::Player()
	{
		Initialize();
	}

	int Player::GetX1()
	{
		return x;
	}

	int Player::GetY1()
	{
		return y;
	}

	int Player::GetX2()
	{
		return x + animation.Width();
	}

	int Player::GetY2()
	{
		return y + animation.Height();
	}

	void Player::Initialize()
	{
		int tmpx, tmpy;
		tmpx = 19;
		tmpy = 520;
		const int X_POS = tmpx;
		const int Y_POS = tmpy;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Player::LoadBitmap()
	{
		animation.AddBitmap(ICE_FRONT, RGB(255, 255, 255));
		animation.AddBitmap(ICE_RIGHT_RUN_1, RGB(255, 255, 255));
		animation.AddBitmap(ICE_RIGHT_RUN_2, RGB(255, 255, 255));
		animation.AddBitmap(ICE_RIGHT_RUN_3, RGB(255, 255, 255));
	}

	void Player::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void Player::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Player::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Player::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Player::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Player::OnShow()
	{

		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}