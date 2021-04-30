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
		const int INITIAL_VELOCITY = 12;	// 初始上升速度
		const int FLOOR = 578 - 52;				// 地板座標
		const int X_POS = 19;
		const int Y_POS = 520;
		floor = FLOOR;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		rising = false;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		this->color = 0;
	}

	void Player::SetColor(int a)
	{
		this->color = a;
	}
	int	 Player::GetColor()
	{
		return this->color;
	}
	void Player::LoadBitmap()
	{
		if (color == 1)
		{
			animation.AddBitmap(ICE_RIGHT_RUN_1, RGB(255, 255, 255));
			animation.AddBitmap(ICE_RIGHT_RUN_2, RGB(255, 255, 255));
			animation.AddBitmap(ICE_RIGHT_RUN_3, RGB(255, 255, 255));
			animation1.AddBitmap(ICE_LEFT_RUN_1, RGB(255, 255, 255));
			animation1.AddBitmap(ICE_LEFT_RUN_2, RGB(255, 255, 255));
			animation1.AddBitmap(ICE_LEFT_RUN_3, RGB(255, 255, 255));
			bit.LoadBitmap(ICE_FRONT, RGB(255, 255, 255));
		}
		else
		{
			animation.AddBitmap(FIRE_RIGHT_RUN_1, RGB(255, 255, 255));
			animation.AddBitmap(FIRE_RIGHT_RUN_2, RGB(255, 255, 255));
			animation.AddBitmap(FIRE_RIGHT_RUN_3, RGB(255, 255, 255));
			animation1.AddBitmap(FIRE_LEFT_RUN_1, RGB(255, 255, 255));
			animation1.AddBitmap(FIRE_LEFT_RUN_2, RGB(255, 255, 255));
			animation1.AddBitmap(FIRE_LEFT_RUN_3, RGB(255, 255, 255));
			bit.LoadBitmap(FIRE_FRONT, RGB(255, 255, 255));
		}

	}

	void Player::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		animation1.OnMove();

		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			rising = true;
			
			if (rising) {			// 上升狀態
				if (velocity > 0) {
					
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
					velocity--;		// 受重力影響，下次的上升速度降低
				}
				else {
					rising = false; // 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;	// 下降的初速(velocity)為1
				}
			}
			else {				// 下降狀態
				if (y < floor - 1) {  // 當y座標還沒碰到地板
					y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
					velocity++;		// 受重力影響，下次的下降速度增加
				}
				else {
					y = floor - 1;  // 當y座標低於地板，更正為地板上
					
					rising = false;	// 探底反彈，下次改為上升
					velocity = initial_velocity;
					 // 重設上升初始速度
				}
				isMovingUp = false;
			};

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

	void Player::SetFloor(int floor)
	{
		this->floor = floor;
	}
	void Player::SetVelocity(int velocity) {
		this->velocity = velocity;
		this->initial_velocity = velocity;
	}
	void Player::OnShow()
	{
		if (isMovingLeft) {
			animation1.SetTopLeft(x, y);
			animation1.OnShow();
		}
		else if (isMovingRight)
		{
			animation.SetTopLeft(x, y);
			animation.OnShow();
		}

		else if (!isMovingRight && !isMovingLeft)
		{
			bit.SetTopLeft(x, y);
			bit.ShowBitmap();
		}

	}
}