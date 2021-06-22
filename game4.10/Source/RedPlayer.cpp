#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "box.h"
#include <iostream>     // std::cout
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
	/////////////////////////////////////////////////////////////////////////////
	// RedPlayer: RedPlayer class
	/////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
	CGameMap::CGameMap(int _stage) {

	}

	CGameMap::CGameMap() :X(10), Y(10), MW(10), MH(10) {
		//map = (int**)malloc(sizeof(int*) * X);
		sizeX = 600 / X;
		sizeY = 800 / Y;
		//int map_init[60][80];

		/*  allocate storage for an array of pointers */
		//map = (int**)malloc(sizeX * sizeof(int*));

		/* for each pointer, allocate storage for an array of ints */
		/*for (int i = 0; i < sizeX; i++) {
			map[i] = (int*)malloc(sizeY * sizeof(int));
		}*/
		stage = 1;
	}

	void CGameMap::ReadFile() {
		std::stringstream filename;
		filename << "map\\Run" << "1" << ".txt";
		ifstream is(filename.str(), std::ifstream::binary);
		std::string line;
		int i = 0;
		while (getline(is, line)) {
			for (int j = 0; j < sizeY; j++) {
				map[i][j] = line[j] - '0';
				/*if (line[j] - '0' == 0)
					map[i][j] = 0;
				else
					map[i][j] = 1;	*/
					//*(*(map + i) + j) = line[j] - '0';
					//cout << map_init[i][j];
			}
			i++;
		}
		is.close();
		/*
		for (i = 0; i < 60; i++) {
			for (int j = 0; j < 80; j++) {
				map[i][j] = map_init[i][j];
			}
		}*/
	}

	void CGameMap::LoadBitmap() {
		blue.LoadBitmap(DOT, 1);
	}

	void CGameMap::OnShow() {
		for (int i = 0; i < 80; i++) {
			for (int j = 0; j < 60; j++) {
				switch (map[j][i]) {
				case 1:
					break;
				case 0:
					blue.SetTopLeft((10 * i), (10 * j));
					blue.ShowBitmap();
					break;
				}
			}
		}
	}

	void CGameMap::setMap(int x, int y, int v) {
		map[y][x] = v;
	}

	void CGameMap::SetStage(int _stage) {
		stage = _stage;
	}

	int CGameMap::mapCoordinate(int x, int y) {
		return map[y][x];
	}

	int CGameMap::GetX() {
		return X;
	}

	int CGameMap::GetY() {
		return Y;
	}

	int CGameMap::GetMH() {
		return MH;
	}

	int CGameMap::GetMW() {
		return MW;
	}

	int CGameMap::GetSizeX() {
		return sizeX;
	}

	int CGameMap::GetSizeY() {
		return sizeY;
	}

	CGameMap::~CGameMap() {
	}

=======
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
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a

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

<<<<<<< HEAD
	void RedPlayer::Initialize()
	{
		gamemap.~CGameMap();
		gamemap.ReadFile();
		const int INITIAL_VELOCITY = 11;	// 初始上升速度
		const int FLOOR = 578 - 40;	
		// 地板座標
		const int X_POS = 42;
		const int Y_POS = 530;
		floor = FLOOR;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
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
				map[i][j] = gamemap.mapCoordinate(j,i);
			}
		}
		for (int j = 0; j < 800; j++)
		{
			x_edge[j] = j+1;
		}
		for (int j = 0; j < 600; j++)
		{
			y_edge[j] = j+1;
		}
	}
	void RedPlayer::LoadBitmap()
=======

	string RedPlayer::Getcharacteristic()
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
	{
		return character;
	}
<<<<<<< HEAD
	bool RedPlayer::frontBox(int bx,int by)
	{
		int x1 = bx;
		int y1 = by;
		int x2 = x1 + 35;
		int y2 = y1 + 35;
		return (x+40 >= x1 && x <= x2 && y+40 >= y1 && y <= y2);
	}
	bool RedPlayer::onBox(int bx, int by)
	{
		int x1 = bx;
		int y1 = by-20;
		int x2 = x1 + 35;
		int y2 = y1 + 40;
		return (x + 40 >= x1 && x <= x2 && y + 40 >= y1 && y <= y2);
	}
	void RedPlayer::setFront(bool a)
	{
		isFrontBox = a;
	}
	bool RedPlayer::isLeftRightEmpty(int x, int y, int value)
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
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}
			for (int i = 0; i < 600; i++)
			{
				if (y + value >= y_edge[i]) {
					ycoord = i;
				}
			}
			result = map[ycoord/10][x_coord/10] && result;
		}
		else 
		{
			for (int i = 0; i < 800; i++)
			{
				if (x >= x_edge[i]) {
					x_coord = i;
				}
			}
			
			for (int j = 5; j < 35; j+=3)
			{
				for (int i = 0; i < 600; i++)
				{
					if (y + j >= y_edge[i]) {
						ycoord = i;
					}
				}
				result = map[ycoord/10][x_coord/10] && result;
			}

		}

		return map[ycoord/10][x_coord/10];
	}
	int RedPlayer::getCoordX(int x, int y)
	{
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i < 800; i++)
		{
			if (x >= x_edge[i]) {
				x_coord = i;
			}
		}
		return x_coord;
=======

	void RedPlayer::Addgem()
	{
		gem++;
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
	}
	int RedPlayer::getgem()
	{
<<<<<<< HEAD
		int x_coord = 0, ycoord = 0;
		for (int i = 0; i < 600; i++)
		{
			if (y >= y_edge[i]) {
				ycoord = i;
			}
		}
		return ycoord;
	}
	void RedPlayer::setfloor()
	{
		if ((map[(y+40)/10][(x+40)/10] )|| (map[(y + 40) / 10][(x + 40) / 10])== 1) {
			if ((map[(y + 50) / 10][(x ) / 10] ) || (map[(y + 50) / 10][(x+40) / 10]) ==1) {
				if ((map[(y + 60) / 10][(x) / 10]) || (map[(y + 60) / 10][(x + 40) / 10]) == 1) {
					if ((map[(y + 70) / 10][(x) / 10]) || (map[(y + 70) / 10][(x + 40) / 10]) == 1) {
						if ((map[(y + 80) / 10][(x) / 10]) || (map[(y + 80) / 10][(x + 40) / 10]) == 1) {
							if ((map[(y + 90) / 10][(x) / 10]) || (map[(y + 90) / 10][(x + 40) / 10]) == 1) {
								if ((map[(y + 100) / 10][(x) / 10]) || (map[(y + 100) / 10][(x + 40) / 10]) == 1) {
									if ((map[(y + 110) / 10][(x) / 10]) || (map[(y + 110) / 10][(x + 40) / 10]) == 1) {
										if ((map[(y + 120) / 10][(x) / 10]) || (map[(y + 120) / 10][(x + 40) / 10]) == 1) {
											floor = ((y / 10) + 9) * 10;
										}
										else {
											floor = ((y / 10) + 8) * 10;
										}
									}
									else {
										floor = ((y / 10) + 7) * 10;
									}
								}
								else {
									floor = ((y / 10) + 6) * 10;
								}
							}
							else {
								floor = ((y / 10) + 5) * 10;
							}
						}
						else {
							floor = ((y / 10) + 4) * 10;
						}
					}
					else {
						floor = ((y / 10) + 3) * 10;
					}
				}
				else {
					floor = ((y / 10) + 2) * 10+5;
				}
			}
			else {
				floor = ((y / 10)+1) * 10+5;
			}
		}
		else {
			floor = (y / 10) * 10+5;
		}
		if (floor > 540) {
			floor = 540;
		}
		/*if ((x + 20 >= 20 && x + 20 < 266 && y + 40 < 578 && y + 40 >= 515) || \
			(x + 20 >= 266 && x + 20 < 717 && y + 40 >= 474 && y + 40 < 578) || \
			(x + 20 >= 266 && x + 20 < 370 && y + 40 >= 433 && y + 40 < 474) || \
			(x + 20 >= 695 && x + 20 < 717 && y + 40 >= 350 && y + 40 < 517))
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
		else if ((x + 20 >= 20 && x + 20 < 392 && y + 40 >= 329 && y + 40 < 413) || \
			(x + 20 >= 20 && x + 20 < 103 && y + 40 >= 247 && y + 40 < 329))
		{
			floor = 413 - 40;
		}
		else if ((x + 20 >= 103 && x + 20 < 414 && y + 40 >= 247 && y + 40 < 311))
		{
			floor = 311 - 40;
		}
		else if ((x + 20 >= 414 && x + 20 < 591 && y + 40 >= 247 && y + 40 < 331) || \
			(x + 20 >= 591 && x + 20 < 778 && y + 40 >= 267 && y + 40 < 331) || \
			(x + 20 >= 694 && x + 20 < 778 && y + 40 >= 144 && y + 40 < 267))
		{
			floor = 331 - 40;
		}
		else if ((x + 20 >= 553 && x + 20 < 591 && y + 40 >= 144 && y + 40 < 247) || \
			(x + 20 >= 591 && x + 20 < 694 && y + 40 >= 144 && y + 40 < 267) || \
			(x + 20 >= 348 && x + 20 < 411 && y + 40 >= 144 && y + 40 < 229) || \
			(x + 20 >= 246 && x + 20 < 348 && y + 40 >= 186 && y + 40 < 229) || \
			(x + 20 >= 122 && x + 20 < 246 && y + 40 >= 102 && y + 40 < 229) || \
			(x + 20 >= 122 && x + 20 < 203 && y + 40 >= 21 && y + 40 < 102))
		{
			if (isOnBox)
			{
				floor = 229 - 40 - 35;
			}
			else
			{
				floor = 229 - 40;
			}
			
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
		}*/
	}
	void RedPlayer::OnMove()
=======
		return gem;
	}

	void RedPlayer::LoadBitmap()
>>>>>>> 52a6d6f4db2373a0e866e1f487e33a3ebf64072a
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
		if (isMovingUp) {			// 上升狀態
			upEnable = true;
			velocity = initial_velocity;
		}

		if (upEnable) {
			isMovingUp = false;
			if ((velocity > 0) && (y > ceil + 1)) {
				y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
				animation.OnMove();
			}
			else {
				velocity = 1;	// 下降的初速(velocity)為1
				upEnable = false;
				isMovingDown = true;
			}

		}
		else if (isMovingDown) {				// 下降狀態
			if ((this->GetY2()) < floor - 1) {  // 當y座標還沒碰到地板
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
				animation.OnMove();
			}
			else {
				y = floor - 1;  // 當y座標低於地板，更正為地板上
				isMovingDown = false;
				//rising = true;	// 探底反彈，下次改為上升
				velocity = initial_velocity; // 重設上升初始速度
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