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
		const int INITIAL_VELOCITY = 12;	// ��l�W�ɳt��
		const int FLOOR = 496 - 52;				// �a�O�y��
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
	bool IcePlayer::isLeftRightEmpty(int x, int y)
	{
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i < 15; i++)
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
	void IcePlayer::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		animation1.OnMove();

		if (isMovingLeft)
			if (isLeftRightEmpty(x - STEP_SIZE, y) && x > 20) {
				x -= STEP_SIZE;
			}
		if (isMovingRight)
			if (isLeftRightEmpty(x + 45 + STEP_SIZE, y)) {
				x += STEP_SIZE;
			}
		if (isMovingUp)
			rising = true;

		if (rising) {			// �W�ɪ��A
			if (velocity > 6) {

				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 5;	// �U������t(velocity)��1
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

	void IcePlayer::SetFloor(int floor)
	{
		this->floor = floor;
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