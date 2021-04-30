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
		const int FLOOR = 578 - 52;				// �a�O�y��
		const int X_POS = 19;
		const int Y_POS = 520;
		floor = FLOOR;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		rising = false;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;

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

	void IcePlayer::OnMove()
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

		if (rising) {			// �W�ɪ��A
			if (velocity > 0) {

				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
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