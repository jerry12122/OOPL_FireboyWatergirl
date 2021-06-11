#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "IcePlayer.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// IcePlayer: IcePlayer class
	/////////////////////////////////////////////////////////////////////////////


	IcePlayer::IcePlayer()
	{
		Initialize();
	}
	int IcePlayer::GetX1()
	{
		return x;
	}

	int IcePlayer::GetY1()
	{
		return y;
	}

	int IcePlayer::GetX2()
	{
		return x + animation.Width();
	}

	int IcePlayer::GetY2()
	{
		return y + animation.Height();
	}

	void IcePlayer::Initialize()
	{
		const int INITIAL_VELOCITY = 12;	// 初始上升速度
		const int FLOOR = 496 - 52;				// 地板座標
		const int X_POS = 42;
		const int Y_POS = 446;
		floor = FLOOR;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		rising = false;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		int map_init[18][14] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,0,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,0,1,1,1,1,1,1,1,1},
			{0,0,1,1,1,1,1,1,1,0,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,0,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,0,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0}
		};
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				map[i][j] = map_init[i][j];
			}
		}
		int x_edge_init[15] = { 20,103,122,203,246,269,348,370,390,411,553,591,694,717,778 };
		for (int j = 0; j < 15; j++)
		{
			x_edge[j] = x_edge_init[j];
		}
		int y_edge_init[19] = { 21,84,102,127,148,187,229,247,267,311,328,349,413,432,458,474,496,515,578 };
		for (int j = 0; j < 19; j++)
		{
			y_edge[j] = y_edge_init[j];
		}
	}
	void IcePlayer::LoadBitmap()
	{

		animation.AddBitmap(ICE_RIGHT_RUN_1, RGB(255, 255, 255));
		animation.AddBitmap(ICE_RIGHT_RUN_2, RGB(255, 255, 255));
		animation.AddBitmap(ICE_RIGHT_RUN_3, RGB(255, 255, 255));
		animation1.AddBitmap(ICE_LEFT_RUN_1, RGB(255, 255, 255));
		animation1.AddBitmap(ICE_LEFT_RUN_2, RGB(255, 255, 255));
		animation1.AddBitmap(ICE_LEFT_RUN_3, RGB(255, 255, 255));
		bit.LoadBitmap(ICE_FRONT, RGB(255, 255, 255));


	}
	bool IcePlayer::isLeftRightEmpty(int x, int y, int value)
	{
		int x_coord = 0, ycoord = 0;
		if (x < 21 || x>778 || y < 21 || y>578)
		{
			return 0;
		}
		bool result = 1;
		if (value == 0) {
			for (int i = 0; i < 15; i++)
			{
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}
			for (int i = 0; i < 19; i++)
			{
				if (y + value >= y_edge[i]) {
					ycoord = i;
				}
			}
			result = map[ycoord][x_coord] && result;
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}

			for (int j = 5; j < 35; j += 3)
			{
				for (int i = 0; i < 19; i++)
				{
					if (y + j >= y_edge[i]) {
						ycoord = i;
					}
				}
				result = map[ycoord][x_coord] && result;
			}

		}

		return map[ycoord][x_coord];
	}
	void IcePlayer::setfloor()
	{
		if ((x + 20 >= 20 && x + 20 < 266 && y + 40 < 578 && y + 40 >= 515) || (x + 20 >= 266 && x + 20 < 717 && y + 40 >= 474 && y + 40 < 578) || (x + 20 >= 266 && x + 20 < 370 && y + 40 >= 433 && y + 40 < 474) || (x + 20 >= 695 && x + 20 < 778 && y + 40 >= 350 && y + 40 < 517))
		{
			floor = 578 - 40;
		}
		else if (x + 20 >= 717 && x + 20 < 778 && y + 40 < 578 && y + 40 >= 350)
		{
			floor = 517 - 40;
		}
		else if ((x + 20 >= 20 && x + 20 < 266 && y + 40 >= 432 && y + 40 < 496))
		{
			floor = 496 - 40;
		}
		else if ((x + 20 >= 389 && x + 20 < 695 && y + 40 >= 350 && y + 40 < 458))
		{
			floor = 458 - 40;
		}
		else if ((x + 20 >= 20 && x + 20 < 392 && y + 40 >= 329 && y + 40 < 413) || (x + 20 >= 20 && x + 20 < 103 && y + 40 >= 247 && y + 40 < 329))
		{
			floor = 413 - 40;
		}
		else if ((x + 20 >= 103 && x + 20 < 414 && y + 40 >= 247 && y + 40 < 311))
		{
			floor = 311 - 40;
		}
		else if ((x + 20 >= 414 && x + 20 < 591 && y + 40 >= 247 && y + 40 < 331) || (x + 20 >= 591 && x + 20 < 778 && y + 40 >= 267 && y + 40 < 331) || (x + 20 >= 694 && x + 20 < 778 && y + 40 >= 144 && y + 40 < 267))
		{
			floor = 331 - 40;
		}
		else if ((x + 20 >= 553 && x + 20 < 591 && y + 40 >= 144 && y + 40 < 247) || (x + 20 >= 591 && x + 20 < 694 && y + 40 >= 144 && y + 40 < 267) || (x + 20 >= 348 && x + 20 < 411 && y + 40 >= 144 && y + 40 < 229) || (x + 20 >= 246 && x + 20 < 348 && y + 40 >= 186 && y + 40 < 229) || (x + 20 >= 122 && x + 20 < 246 && y + 40 >= 102 && y + 40 < 229) || (x + 20 >= 122 && x + 20 < 203 && y + 40 >= 21 && y + 40 < 102))
		{
			floor = 229 - 40;
		}
		else if ((x + 20 >= 411 && x + 20 < 553 && y + 40 >= 144 && y + 40 < 188))
		{
			floor = 188 - 40;
		}
		else if ((x + 20 >= 21 && x + 20 < 203 && y + 40 >= 21 && y + 40 < 229))
		{
			floor = 148 - 40;
		}
		else if ((x + 20 >= 203 && x + 20 < 269 && y + 40 >= 21 && y + 40 < 84))
		{
			floor = 84 - 40;
		}
		else if ((x + 20 >= 269 && x + 20 < 778 && y + 40 >= 21 && y + 40 < 102))
		{
			floor = 102 - 18;
		}
	}
	void IcePlayer::OnMove()
	{
		const int STEP_SIZE = 7;
		animation.OnMove();
		animation1.OnMove();
		/*
		if (isLeftRightEmpty(x, y+55)&&y+55<578)
		{
			int  ycoord = 0;
			for (int i = 0; i < 19; i++)
			{
				if (y >= y_edge[i]) {
					ycoord = i;
				}
			}
			floor = y_edge[ycoord + 1]-50;
		}
		*/
		setfloor();

		if (isMovingLeft)
			if (isLeftRightEmpty(x - STEP_SIZE, y, 1) && x > 20) {
				x -= STEP_SIZE;
				setfloor();
			}
		if (isMovingRight)
			if (isLeftRightEmpty(x + 45 + STEP_SIZE, y, 1) && x < 778) {
				x += STEP_SIZE;
				setfloor();
			}
		if (isMovingUp){
			rising = true;
			isMovingUp = false;
		} 
		if (rising) {			// 上升狀態
			if (velocity > 0) {
				if (!isLeftRightEmpty(x, y - 1, 0))
				{
					velocity-=2;
					setfloor();
				}
				else
				{
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
					velocity--;		// 受重力影響，下次的上升速度降低
					setfloor();
				}

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
				setfloor();
			}
			else {
				setfloor();
				y = floor - 1;  // 當y座標低於地板，更正為地板上
				rising = false;	// 探底反彈，下次改為上升
				velocity = initial_velocity;
				// 重設上升初始速度
			}
			isMovingUp = false;
		};
		if (isMovingDown)
			y = floor;
	}
	void IcePlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void IcePlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void IcePlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void IcePlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void IcePlayer::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void IcePlayer::SetVelocity(int velocity) {
		this->velocity = velocity;
		this->initial_velocity = velocity;
	}
	void IcePlayer::OnShow()
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