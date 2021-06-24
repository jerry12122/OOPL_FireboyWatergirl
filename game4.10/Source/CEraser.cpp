#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}
	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + 28;
	}

	int CEraser::GetY2()
	{
		return y + 40;
	}

	int CEraser::GetVelocity()
	{
		return velocity;
	}
	int CEraser::GetFloor()
	{
		return floor;
	}
	bool CEraser::OnFloor()
	{
		if (animation.GetCurrentBitmapNumber() < 5 || animation.GetCurrentBitmapNumber() > 0) return true;
		else return false;
	}

	bool CEraser::getRising()
	{
		return rising;
	}

	int CEraser::getStep()
	{
		return step_size;
	}
	void CEraser::Addgem()
	{
		gem++;
	}
	int CEraser::getgem()
	{
		return gem;
	}
	string CEraser::Getcharacteristic()
	{
		return character;
	}

	void CEraser::Initialize()
	{
		const int INITIAL_VELOCITY = 11;	// ��l�W�ɳt��
		const int X_POS = 20;
		const int Y_POS = 460;
		const int STEP_SIZE = 6;
		step_size = STEP_SIZE;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		x = X_POS;
		ceil = floor = y = Y_POS;
		times = 0;
		character = "water";
		direction = 0;
		setFloorEnable = true;
		gem = 0;
		rising = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = upEnable = false;
	}
	void CEraser::LoadBitmap()
	{
		/*animation.AddBitmap(IDB_WATER, RGB(255, 255, 255));
		animation.AddBitmap(IDB_WATER_L1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_WATER_L2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_WATER_R1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_WATER_R2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_WATER_UP, RGB(255, 255, 255));*/
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));
		animation.AddBitmap(GOOD, RGB(255, 255, 255));

	}
	void CEraser::OnMove()
	{
		if ((y + 40) < 580 && (y + 40) > 570)
			y = 579 - 40;
		if (isMovingLeft)
		{
			x -= step_size;
		}
		if (isMovingRight)
		{
			x += step_size;
		}
		if (isMovingUp) {			// �W�ɪ��A
			rising = true;
			velocity = initial_velocity;
		}
		if (rising) {			// �W�ɪ��A
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
		if (isMovingDown)
		{
			if (((floor - 1) - (this->GetY2()) < velocity)) {
				y = floor - 41;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				isMovingDown = false;
				//rising = true;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
			else if (velocity >= initial_velocity)
				velocity = 1;

			else if (this->GetY2() < floor - 1 && ((floor - 1) - (this->GetY2()) > velocity)) {  // ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
				animation.OnMove();
			}
		}
	}

	bool CEraser::GetUpEnable() {
		return upEnable;
	}

	void CEraser::SetStopDown(int y) {
		stop_down = y;
	}

	void CEraser::SetUpEnable(bool flag) {
		upEnable = flag;
	}

	void CEraser::SetFloorEnable(bool flag) {
		setFloorEnable = flag;
	}

	void CEraser::SetStepSize(int _step) {
		step_size = _step;
	}

	void CEraser::SetVelocity(int v) {
		velocity = v;
	}

	void CEraser::setfloor(int _floor)
	{
		if (_floor <= 580 && setFloorEnable)
			floor = _floor;
		else if (_floor >= 580)
			floor = 580;
	}

	void CEraser::setceil(int _ceil)
	{
		if (ceil <= 100 && ceil >= 20)
			ceil = 20;
		if (_ceil >= 20)
			ceil = _ceil;
	}
	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}


	bool CEraser::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool CEraser::GetMovingRight()
	{
		return isMovingRight;
	}

	bool CEraser::GetMovingUp() {
		return isMovingUp;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void CEraser::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}