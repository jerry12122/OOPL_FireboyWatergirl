#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// RedPlayer: RedPlayer class
	/////////////////////////////////////////////////////////////////////////////


	RedPlayer::RedPlayer()
	{
		Initialize();
	}
	int RedPlayer::GetX1()
	{
		return x;
	}

	int RedPlayer::GetY1()
	{
		return y;
	}

	int RedPlayer::GetX2()
	{
		return x + animation.Width();
	}

	int RedPlayer::GetY2()
	{
		return y + animation.Height();
	}


	void RedPlayer::Initialize()
	{
		const int INITIAL_VELOCITY = 12;	// ��l�W�ɳt��
		const int FLOOR = 578 - 52;				// �a�O�y��
		const int X_POS = 42;
		const int Y_POS = 530;
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

	void RedPlayer::LoadBitmap()
	{
		animation.AddBitmap(FIRE_RIGHT_RUN_1, RGB(255, 255, 255));
		animation.AddBitmap(FIRE_RIGHT_RUN_2, RGB(255, 255, 255));
		animation.AddBitmap(FIRE_RIGHT_RUN_3, RGB(255, 255, 255));
		animation1.AddBitmap(FIRE_LEFT_RUN_1, RGB(255, 255, 255));
		animation1.AddBitmap(FIRE_LEFT_RUN_2, RGB(255, 255, 255));
		animation1.AddBitmap(FIRE_LEFT_RUN_3, RGB(255, 255, 255));
		bit.LoadBitmap(FIRE_FRONT, RGB(255, 255, 255));


	}
	bool RedPlayer::isLeftRightEmpty(int x, int y)
	{
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i <15; i++)
		{
			if (x >= x_edge[i]) {
				x_coord = i;
			}
		}
		for (int i = 0; i < 19; i++)
		{
			if (y >= y_edge[i]) {
				ycoord = i;
			}
		}
		return map[ycoord][x_coord];
	}


	void RedPlayer::OnMove()
	{

		const int STEP_SIZE = 6;
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
		if (isMovingLeft)
			if (isLeftRightEmpty(x- STEP_SIZE,y) && x > 20) {
				x -= STEP_SIZE;
			}
		if (isMovingRight)
			if (isLeftRightEmpty(x+45+STEP_SIZE, y) && x < 778) {
				x += STEP_SIZE;
			}
		if (isMovingUp)
			rising = true;
		if (rising) {			// �W�ɪ��A
			if (velocity > 0) {

				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
			if (!isLeftRightEmpty(x, y - 1))
			{
				rising = false;
				velocity = 0;
			}
		}
		else {				// �U�����A
			if (y < floor - 1) {  // ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
			}
			else {
				y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W

				rising = false;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity;
				// ���]�W�ɪ�l�t��
			}
			isMovingUp = false;
		};
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void RedPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void RedPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void RedPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void RedPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void RedPlayer::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void RedPlayer::SetFloor(int floor)
	{
		this->floor = floor;
	}
	void RedPlayer::SetVelocity(int velocity) {
		this->velocity = velocity;
		this->initial_velocity = velocity;
	}
	void RedPlayer::OnShow()
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