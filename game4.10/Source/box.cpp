#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "box.h"
#include <iostream>    
#include <fstream> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <sstream>
namespace game_framework {
	box::box()
	{
		init();
	}
	//�]�m��l�ȡAŪ���a���ɮ��ഫ���}�C
	void box::init()
	{
		gamemap.~CGameMap();
		gamemap.ReadFile(1);
		const int INITIAL_VELOCITY = 6;
		x = y =  0;
		dx = dy = 35;
		floor = 190;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		inertia = false;
		isMovingLeft = false;
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
	bool box::HitEraser(RedPlayer *redplayer)
	{
		
		return HitRectangle(redplayer->GetX1(), redplayer->GetY1(),
			redplayer->GetX2(), redplayer->GetY2());
	}
	bool box::HitEraser(IcePlayer *iceplayer)
	{
		
		return HitRectangle(iceplayer->GetX1(), iceplayer->GetY1(),
			iceplayer->GetX2(), iceplayer->GetY2());
	}

	bool box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				// �y�����W��x�y��
		int y1 = y;				// �y�����W��y�y��
		int x2 = x1 + 45;	// �y���k�U��x�y��
		int y2 = y1 + 30;	// �y���k�U��y�y��
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool box::OnBox(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;
		int y1 = y + dy;
		int x2 = x1 + bmp.Width();
		int y2 = y1 + bmp.Height();

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	//�̾ڦa�ϰ}�C�]�m���O�@�ɦa�O
	void box::setfloor()
	{
		if ((map[(y + 30) / 10][(x) / 10]) && (map[(y + 30) / 10][(x + 30) / 10]) == 1) {
			if ((map[(y + 40) / 10][(x) / 10]) && (map[(y + 40) / 10][(x + 30) / 10]) == 1) {
				if ((map[(y + 50) / 10][(x) / 10]) && (map[(y + 50) / 10][(x + 30) / 10]) == 1) {
					if ((map[(y + 60) / 10][(x) / 10]) && (map[(y + 60) / 10][(x + 30) / 10]) == 1) {
						if ((map[(y + 70) / 10][(x) / 10]) && (map[(y + 70) / 10][(x + 30) / 10]) == 1) {
							floor = (((y + 30) / 10) + 5) * 10;
						}
						else {
							floor = (((y + 30) / 10) + 4) * 10;
						}
					}
					else {
						floor = (((y + 30) / 10) + 3) * 10;
					}
				}
				else {
					floor = (((y + 30) / 10) + 2) * 10;
				}
			}
			else {
				floor = (((y + 30) / 10) + 1) * 10;
			}
		}
		else {
			floor = ((y + 30) / 10) * 10;
		}
		if (floor >= 580) {
			floor = 579;
		}
	}
	void box::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BOX, RGB(0, 0, 0));			
	}
	//�̾ڦa�ϰ}�C�˴�����B�Ѫ�O
	bool box::isLeftRightEmpty(int x, int y, int value)
	{
		int x_coord = 0, ycoord = 0;
		if (x < 21 || x>778 || y < 21 || y>578)
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
					if (y + j >= y_edge[i]) {
						ycoord = i;
					}
				}
				result = map[ycoord / 10][x_coord / 10] && result;
			}

		}

		return map[ycoord / 10][x_coord / 10];
	}
	//���ʥ]�t�D��
	void box::OnMove()
	{
		y = floor - 30;
		if (isMovingLeft) {
			if (isLeftRightEmpty(x - 7, y, 1) && x > 20) {
				x -= 7;
				setfloor();
			}
			inertia = true;
			isMovingLeft = false;
		}
		if (inertia)
		{
			if (velocity > 0)
			{
				if (!isLeftRightEmpty(x - 1, y, 0))
				{
					velocity--;
				}
				else {
					x -= velocity;
					velocity--;
					setfloor();
				}
			}
			else {
				inertia = false;
				velocity = initial_velocity;
			}
		}
	}
	void box::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void box::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	int box::GetX1()
	{
		return x;
	}
	int box::GetY1()
	{
		return y;
	}
	void box::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void box::OnShow()
	{
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
}