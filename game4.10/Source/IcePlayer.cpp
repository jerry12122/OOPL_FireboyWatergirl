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
		Initialize(stage);
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
	void IcePlayer::Initialize(int stages)
	{
		stage = stages;
		gamemap.ReadFile(stages);
		int INITIAL_VELOCITY;	// ��l�W�ɳt��
		if (stages == 1)
		{
			INITIAL_VELOCITY = 11;
		}
		else
		{
			INITIAL_VELOCITY = 15;
		}
		const int FLOOR = 462;
		// �a�O�y��
		const int X_POS = 42;
		const int Y_POS = 542;
		MY = 230;
		floor = FLOOR;
		//x = X_POS;
		//y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isOnBox = isFrontBox = isOnButton= false;
		rising = false;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		/*
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
		}*/
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				map[i][j] = gamemap.mapCoordinate(j, i);
			}
		}
		for (int j = 0; j < 800; j++)
		{
			x_edge[j] = j + 1;
		}
		for (int j = 0; j < 600; j++)
		{
			y_edge[j] = j + 1;
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
	bool IcePlayer::frontBox(int bx, int by)
	{
		int x1 = bx;
		int y1 = by;
		int x2 = x1 + 35;
		int y2 = y1 + 35;
		return (x + 40 >= x1 && x <= x2 && y + 40 >= y1 && y <= y2);
	}
	bool IcePlayer::onBox(int bx, int by)
	{
		int x1 = bx;
		int y1 = by - 20;
		int x2 = x1 + 35;
		int y2 = y1 + 40;
		return (x + 40 >= x1 && x <= x2 && y + 40 >= y1 && y <= y2);
	}
	void IcePlayer::setOnBox(bool a) {
		isOnBox = a;
	}
	void IcePlayer::setFront(bool a)
	{
		isFrontBox = a;
	}
	bool IcePlayer::isLeftRightEmpty(int x, int y, int value)
	{
		int x_coord = 0, ycoord = 0;
		if (x < 21 || x>788 || y < 21 || y>578)
		{
			return 0;
		}
		bool result = 1;
		if (value == 0) {
			for (int i = 0; i < 800; i++)
			{
				if (x == x_edge[i]) {
					x_coord = i;
				}
			}
			for (int i = 0; i < 600; i++)
			{
				if (y + value == y_edge[i]) {
					ycoord = i;
				}
			}
			result = map[ycoord / 10][x_coord / 10] && result;
		}
		else
		{
			for (int i = 0; i < 800; i++)
			{
				if (x == x_edge[i]) {
					x_coord = i;
				}
			}

			for (int j = 5; j < 35; j += 3)
			{
				for (int i = 0; i < 600; i++)
				{
					if (y + j == y_edge[i]) {
						ycoord = i;
					}
				}
				result = map[ycoord / 10][x_coord / 10] && result;
			}

		}

		return map[ycoord / 10][x_coord / 10];
	}
	int IcePlayer::getCoordX(int x, int y)
	{
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i < 800; i++)
		{
			if (x >= x_edge[i]) {
				x_coord = i;
			}
		}
		return x_coord;
	}
	int IcePlayer::getCoordY(int x, int y)
	{
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i < 600; i++)
		{
			if (y >= y_edge[i]) {
				ycoord = i;
			}
		}
		return ycoord;
	}
	void IcePlayer::setfloor()
	{
		if (!isOnButton)
		{
			if ((map[(y + 38) / 10][(x) / 10]) && (map[(y + 38) / 10][(x + 30) / 10]) == 1) {
				if ((map[(y + 48) / 10][(x) / 10]) && (map[(y + 48) / 10][(x + 30) / 10]) == 1) {
					if ((map[(y + 58) / 10][(x) / 10]) && (map[(y + 58) / 10][(x + 30) / 10]) == 1) {
						if ((map[(y + 68) / 10][(x) / 10]) && (map[(y + 68) / 10][(x + 30) / 10]) == 1) {
							if ((map[(y + 78) / 10][(x) / 10]) && (map[(y + 78) / 10][(x + 30) / 10]) == 1) {
								if ((map[(y + 88) / 10][(x) / 10]) && (map[(y + 88) / 10][(x + 30) / 10]) == 1) {
									if ((map[(y + 98) / 10][(x) / 10]) && (map[(y + 98) / 10][(x + 30) / 10]) == 1) {
										if ((map[(y + 108) / 10][(x) / 10]) && (map[(y + 108) / 10][(x + 30) / 10]) == 1) {
											if ((map[(y + 118) / 10][(x) / 10]) && (map[(y + 118) / 10][(x + 30) / 10]) == 1) {

												floor = (((y + 38) / 10) + 9) * 10;
											}
											else {
												floor = (((y + 38) / 10) + 8) * 10;
											}
										}
										else {
											floor = (((y + 38) / 10) + 7) * 10;
										}
									}
									else {
										floor = (((y + 38) / 10) + 6) * 10;
									}
								}
								else {
									floor = (((y + 38) / 10) + 5) * 10;
								}
							}
							else {
								floor = (((y + 38) / 10) + 4) * 10;
							}
						}
						else {
							floor = (((y + 38) / 10) + 3) * 10;
						}
					}
					else {
						floor = (((y + 38) / 10) + 2) * 10;
					}
				}
				else {
					floor = (((y + 38) / 10) + 1) * 10;
				}
			}
			else {
				floor = ((y + 38) / 10) * 10;
			}
		}
		if (floor >= 580) {
			floor = 579;
		}
		if ((x + 20 >= 122 && x + 20 < 157 && y + 40 >= 21 && y + 40 < 229) && isOnBox)
		{
			floor = 194;
		}
	}
	void IcePlayer::OnMove1() {
		if (!rising && velocity == initial_velocity) {
			y = floor - 38;

		}
		/*
		int a = MY / 10;
		if (isButton) {
			if (x > 710 && x < 780 && y >= 192 && y < 282) {
				for (int j = 71; j <= 77; j++) {
					map[a][j] = 0;
					map[a - 1][j] = 1;
				}
				y = a * 10 - 38;
				setfloor();
			}
		}
		else {
			if (x > 710 && x < 780 && y >= 192 && y < 282) {
				for (int j = 71; j <= 77; j++) {
					map[a][j] = 0;
					if (a <= 31) {
						map[a + 1][j] = 1;
					}
					y = a * 10 - 38;
					setfloor();
				}
			}
		}*/
	}
	void IcePlayer::OnMove()
	{
		const int STEP_SIZE = 7;
		animation.OnMove();
		animation1.OnMove();
		if (isMood) {
			for (int i = 2; i <= 8; i++) {
				map[37][i] = 0;
			}
		}
		else {
			for (int i = 2; i <= 8; i++) {
				map[37][i] = 1;
			}
		}
		if (stage == 2) {
			if (isButton2) {
				for (int i = 11; i <= 12; i++) {
					for (int j = 35; j <= 44; j++) {
						map[i][j] = 0;
					}
				}
			}
			else {
				for (int i = 11; i <= 12; i++) {
					for (int j = 35; j <= 44; j++) {
						map[i][j] = 1;
					}
				}
			}
			if (isButton3) {
				for (int i = 33; i <= 40; i++) {
					for (int j = 40; j <= 41; j++) {
						map[i][j] = 1;
					}
				}
			}
			else {
				for (int i = 33; i <= 40; i++) {
					for (int j = 40; j <= 41; j++) {
						map[i][j] = 0;
					}
				}
			}
		}
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
		if (!rising && velocity == initial_velocity) {
			y = floor - 38;

		}

		if (isMovingLeft)
			if (isLeftRightEmpty(x - STEP_SIZE, y, 1) && x > 20 && isFrontBox == false) {
				x -= STEP_SIZE;
				setfloor();
			}
		if (isMovingRight)
			if (isLeftRightEmpty(x + 38 + STEP_SIZE, y, 1) && x < 778) {
				x += STEP_SIZE;
				setfloor();
			}
		if (isMovingUp) {
			rising = true;
			isMovingUp = false;
		}
		if (rising) {			// �W�ɪ��A
			if (velocity > 0) {
				if (!isLeftRightEmpty(x, y - 1, 0))
				{
					velocity -= 2;
					setfloor();
				}
				else
				{
					y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
					velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
					setfloor();
				}

			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}

		}
		else {				// �U�����A
			if (y < floor - 39) {  // ��y�y���٨S�I��a�O
				if (velocity < 9) {
					y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
					velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
					setfloor();

				}
				else {
					y += velocity;
					setfloor();
				}
			}
			else {
				setfloor();
				y = floor - 38;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				rising = false;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity;
				// ���]�W�ɪ�l�t��
			}
			isMovingUp = false;
		};
		if (isMovingDown)
			y = floor - 38;
	}
	void IcePlayer::SetButton(bool flag) {
		isButton = flag;
	}
	void IcePlayer::SetButton2(bool flag) {
		isButton2 = flag;
	}
	void IcePlayer::SetButton3(bool flag) {
		isButton3 = flag;
	}
	void IcePlayer::SetMood(bool flag) {
		isMood = flag;
	}
	void IcePlayer::MoodY(int MY) {
		MY = MY;
	}
	bool IcePlayer::butin() {
		int x1 = x;
		int y1 = y;
		int x2 = x1 + bit.Width();
		int y2 = y1 + bit.Height();
		if (x2 >= 709 && x1 < 790 && y2 >= 192 && y1 <= 292) {
			return 1;
		}
		else {
			return 0;
		}
	}
	void IcePlayer::SetFloor(int y) {
		floor = y;
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
	void IcePlayer::OnShow() {
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