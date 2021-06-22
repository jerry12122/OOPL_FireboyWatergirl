#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "box.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// RedPlayer: RedPlayer class
	/////////////////////////////////////////////////////////////////////////////

	void RedPlayer::Initialize()
	{
		const int X_POS = 20;
		const int Y_POS = 540;
		floor = 580;
		x = X_POS;
		y = Y_POS;
		gem = 0;
		character = "fire";
		setFloorEnable = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

	}

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
		return x + 28;
	}

	int RedPlayer::GetY2()
	{
		return y + 40;
	}


	string RedPlayer::Getcharacteristic()
	{
		return character;
	}

	void RedPlayer::Addgem()
	{
		gem++;
	}
	int RedPlayer::getgem()
	{
		return gem;
	}

	void RedPlayer::LoadBitmap()
	{
		/*animation.AddBitmap(IDB_FIRE, RGB(255, 255, 255));
		animation.AddBitmap(IDB_FIRE_L1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_FIRE_L2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_FIRE_R1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_FIRE_R2, RGB(255, 255, 255));*/
		/*
		animation.AddBitmap(IDB_BITMAP11, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BITMAP13, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BITMAP17, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BITMAP14, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BITMAP15, RGB(255, 255, 255));*/

		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
	}

	void RedPlayer::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
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
	void RedPlayer::OnMove()
	{

		if (isMovingLeft)
		{
			x -= step_size;
		}
		if (isMovingRight)
		{
			x += step_size;
		}
		if (isMovingUp) {			// �W�ɪ��A
			upEnable = true;
			velocity = initial_velocity;
		}

		if (upEnable) {
			isMovingUp = false;
			if ((velocity > 0) && (y > ceil + 1)) {
				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
				animation.OnMove();
			}
			else {
				velocity = 1;	// �U������t(velocity)��1
				upEnable = false;
				isMovingDown = true;
			}

		}
		else if (isMovingDown) {				// �U�����A
			if ((this->GetY2()) < floor - 1) {  // ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
				animation.OnMove();
			}
			else {
				y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				isMovingDown = false;
				//rising = true;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
		}
		if (!(isMovingDown || isMovingLeft || isMovingRight || isMovingUp))
			animation.Reset();
	}
	void RedPlayer::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}