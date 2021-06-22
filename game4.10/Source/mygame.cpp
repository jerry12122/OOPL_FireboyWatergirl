/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
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
template <class P1, class P2, class M>
void setMoving(P1 *player1, P2 *player2, M *map) {

	int x_start = 0;
	int x_end = 0;
	int y_start = 0;
	int y_end = 0;

	int x_start_fireman = 0;
	int x_end_fireman = 0;
	int y_start_fireman = 0;
	int y_end_fireman = 0;

	int x1_water = (*player1).GetX1();
	int x2_water = (*player1).GetX2();
	int y1_water = (*player1).GetY1();
	int y2_water = (*player1).GetY2();

	int x1_fire = (*player2).GetX1();
	int x2_fire = (*player2).GetX2();
	int y1_fire = (*player2).GetY1();
	int y2_fire = (*player2).GetY2();

	int X = (*map).GetX();
	int Y = (*map).GetY();
	int sizeX = (*map).GetSizeX();
	int sizeY = (*map).GetSizeY();

	int i = 0;

	if (x1_water % X == 0) {
		x_start = ((int)x1_water / X) + 1;
	}
	else {
		x_start = ((int)x1_water / X);
	}
	if (x_start_fireman % X == 0) {
		x_start_fireman = ((int)x1_fire / X) + 1;
	}
	else {
		x_start_fireman = ((int)x1_fire / X);
	}

	if (y1_water % Y == 0) {
		y_start = ((int)y1_water / Y);
	}
	else {
		y_start = ((int)y1_water / Y) + 1;
	}
	if (y1_fire % Y == 0) {
		y_start_fireman = ((int)y1_fire / Y);
	}
	else {
		y_start_fireman = ((int)y1_fire / Y) + 1;
	}

	if (x2_water % X == 0) {
		x_end = (x2_water / X);
	}
	else {
		x_end = ((int)x2_water / X) + 1;
	}
	if (x2_fire % X == 0) {
		x_end_fireman = (x2_fire / X);
	}
	else {
		x_end_fireman = ((int)x2_fire
			/ X) + 1;
	}

	//y_start = ((int)y1_water / gamemap.GetY());
	if (y2_water % Y == 0) {
		y_end = (y2_water / Y);
	}
	else {
		y_end = ((int)y2_water / Y) + 1;
	}
	//y_start_fireman = ((int)y1_fire / gamemap.GetY());
	if (y2_fire % Y == 0) {
		y_end_fireman = (y2_fire / Y);
	}
	else {
		y_end_fireman = ((int)y2_fire / Y) + 1;
	}

	for (i = y_start; i <= y_end; i++) {
		if ((*map).mapCoordinate(x_start, i - 1) == 1) {
			(*player1).SetMovingLeft(false);
		}
		if ((*map).mapCoordinate(x_end, i - 1) == 1) {
			(*player1).SetMovingRight(false);
		}
	}
	for (i = y_start_fireman; i < y_end_fireman; i++) {
		if ((*map).mapCoordinate(x_start_fireman, i) == 1) {
			(*player2).SetMovingLeft(false);
		}
		if ((*map).mapCoordinate(x_end_fireman, i) == 1) {
			(*player2).SetMovingRight(false);
		}
	}
	for (i = y_end; i < (*map).GetSizeX(); i++) {
		if ((*map).mapCoordinate(x_end, i) == 1) {
			(*player1).SetStopDown(i);
			break;
		}
	}
	/*for (int i = y_start; i >= 0; i--) {
		if (gamemap.mapCoordinate(x_start, i+1) == 1) {
			P1.setceil(i * Y);
			break;
		}
	}
	for (int i = y_end; i < gamemap.GetSizeX(); i++) {
		if (gamemap.mapCoordinate(x_start, i) == 1) {
			P1.setfloor(i * Y);
			break;
		}
	}*/
	int stop = 0;
	for (i = y_start - 1; i >= 0; i--) {
		for (int j = x_start; j <= x_end; j++)
			if ((*map).mapCoordinate(j, i) == 1) {
				(*player1).setceil(i * Y);
				stop = 1;
				break;
			}
		if (stop == 1)
			break;
	}
	stop = 0;
	for (i = y_end; i < 59; i++) {
		for (int j = x_start; j <= x_end; j++)
			if ((*map).mapCoordinate(j, i) == 1) {
				(*player1).setfloor(i * Y);
				stop = 1;
				break;
			}
		if (stop == 1)
			break;
	}
	stop = 0;
	for (i = y_start_fireman - 1; i >= 0; i--) {
		for (int j = x_start_fireman; j <= x_end_fireman; j++)
			if ((*map).mapCoordinate(j, i) == 1) {
				(*player2).setceil(i * Y);
				stop = 1;
				break;
			}
		if (stop == 1)
			break;
	}
	stop = 0;
	for (i = y_end_fireman + 1; i < 59; i++) {
		for (int j = x_start_fireman; j <= x_end_fireman; j++)
			if ((*map).mapCoordinate(j, i) == 1) {
				(*player2).setfloor(i * Y);
				stop = 1;
				break;
			}
		if (stop == 1)
			break;
	}

	if (!(*player1).GetUpEnable()) {
		if ((*map).mapCoordinate(x_end, y_end) == 1 || y_end >= sizeX)
			(*player1).SetMovingDown(false);
		else {
			(*player1).SetMovingDown(true);
		}
	}

	if (!(*player2).GetUpEnable()) {
		if ((*map).mapCoordinate(x_end_fireman, y_end_fireman) == 1 || (*player2).GetY2() >= 580)
			(*player2).SetMovingDown(false);
		else {
			(*player2).SetMovingDown(true);
		}
	}
}
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////
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
		blue.LoadBitmap(IDB_BITMAP3);
	}

	void CGameMap::OnShow() {
		for (int i = 0; i < 80; i++) {
			for (int j = 0; j < 60; j++) {
				switch (map[j][i]) {
				case 0:
					break;
				case 1:
					blue.SetTopLeft((10 * i), (10 * j));
					blue.ShowBitmap();
					break;
					\
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



CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_GAME_MENU);
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//

}
void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	//const char KEY_SPACE = ' ';
	if (nChar == KEY_ESC)
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
	/*
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		*/
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 303 && point.x < 485) && (point.y > 311 && point.y < 375))
	{
		GotoGameState(GAME_STATE_RUN);
	}
	
		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();
	*/
	// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 254 && point.x < 367) && (point.y > 337 && point.y < 376))
	{
		GotoGameState(GAME_STATE_INIT);
	}
	if ((point.x > 444 && point.x < 556) && (point.y > 337 && point.y < 376))
	{
		GotoGameState(GAME_STATE_RUN);
	}
}
void CGameStateOver::OnMove()
{

}
void CGameStateOver::OnBeginState()
{

}
void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	gameover.LoadBitmap(GAMEOVER, RGB(255, 255, 255));
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateOver::OnShow()
{
	gameover.SetTopLeft(118, 138);
	gameover.ShowBitmap();

}
CGameStateWin::CGameStateWin(CGame *g)
	: CGameState(g)
{
}
void CGameStateWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 320 && point.x < 510) && (point.y > 350 && point.y < 404))
	{
		GotoGameState(GAME_STATE_INIT);
	}
}
void CGameStateWin::OnMove()
{

}
void CGameStateWin::OnBeginState()
{

}
void CGameStateWin::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	gamewinspace.LoadBitmap(Win, RGB(255, 255, 255));
	alarm.LoadBitmap(Alarm, RGB(255, 255, 255));
	boygirl.LoadBitmap(BOYGIRL, RGB(255, 255, 255));
	dim.LoadBitmap(DIM, RGB(255, 255, 255));
	good.LoadBitmap(GOOD, RGB(255, 255, 255));
	bad.LoadBitmap(BAD, RGB(255, 255, 255));
	conti.LoadBitmap(CONTI, RGB(255, 255, 255));
	next.LoadBitmap(NEXT, RGB(255, 255, 255));
	gold.LoadBitmap(GOLD, RGB(255, 255, 255));
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateWin::OnShow()
{
	gamewinspace.SetTopLeft(130, 138);
	gamewinspace.ShowBitmap();
	alarm.SetTopLeft(270, 280);
	alarm.ShowBitmap();
	boygirl.SetTopLeft(270, 180);
	boygirl.ShowBitmap();
	dim.SetTopLeft(270, 240);
	dim.ShowBitmap();
	next.SetTopLeft(380, 231);
	next.ShowBitmap();
	gold.SetTopLeft(480, 231);
	gold.ShowBitmap();
	conti.SetTopLeft(320, 350);
	conti.ShowBitmap();
}
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMRED(3),NUMICE(4), LAKERED(1), LAKEICE(1), LAKEGREEN(1), NUMMOD(2), NUMBUT(3)
{
	diamond1 = new RedDiamond[NUMRED];
	diamond2 = new IceDiamond[NUMICE];
	Lake1 = new RedLake[LAKERED];
	Lake2 = new IceLake[LAKEICE];
	Lake3 = new Greenlake[LAKEGREEN];
	mood = new Mood[NUMMOD];
	button = new Button[NUMBUT];
	//reddoor = new RedDoor();
	//icedoor = new IceDoor();
}

CGameStateRun::~CGameStateRun()
{
	delete[] diamond1;
	delete[] diamond2;
	delete[] Lake1;
	delete[] Lake2;
	delete[] Lake3;
	delete[] mood;
	delete[] button;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 0;
	const int HITS_LAKE = 1;
	const int HITS_DOOR = 1;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	const int STAGE = 1;
	const int diamond1_position[3][2] = { {405,535},{140,260},{223,41} };
	for (int i = 0; i < NUMRED; i++) {				// �]�w�y���_�l�y��
		diamond1[i].SetXY(diamond1_position[i][0], diamond1_position[i][1]);
		diamond1[i].SetIsAlive(true);
	}
	const int diamond2_position[4][2] = { {570,535},{470,290},{475,87},{35,109} };
	for (int i = 0; i < NUMICE; i++) {				// �]�w�y���_�l�y��
		diamond2[i].SetXY(diamond2_position[i][0], diamond2_position[i][1]);
		diamond2[i].SetIsAlive(true);
	}
	const int Lake1_position[1][2] = { {360,579} };
	for (int i = 0; i < LAKERED; i++) {				// �]�w�y���_�l�y��
		Lake1[i].SetXY(Lake1_position[i][0], Lake1_position[i][1]);

	}
	const int Lake2_position[1][2] = { {530,579}};
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake2[i].SetXY(Lake2_position[i][0], Lake2_position[i][1]);
	}
	const int Lake3_position[1][2] = { {460,455} };
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake3[i].SetXY(Lake3_position[i][0], Lake3_position[i][1]);
	}
	const int mood_position[2][2] = { {260,388},{22,308} };
	for (int i = 0; i < NUMMOD; i++) {				// �]�w�y���_�l�y��
		mood[i].SetXY(mood_position[i][0], mood_position[i][1]);
		mood[i].SetIsAlive(true);
	}
	
	gamemap.SetStage(1);
	gamemap.ReadFile();
	player1.Initialize();
	player2.Initialize();
	player1.SetXY(200,340);
	reddoor.SetIsAlive(true);
	reddoor.SetXY(690, 550);
	icedoor.SetIsAlive(true);
	icedoor.SetXY(600, 550);
	//69
	box.init();
	box.SetXY(500, 154);
	const int button_position[3][2] = { {270,295},{697,228} ,{600,215} };
	for (int i = 0; i < NUMBUT; i++) {				// �]�w�y���_�l�y��
		button[i].SetXY(button_position[i][0], button_position[i][1]);
		button[i].SetIsAlive(true);
	}

	background.SetTopLeft(0,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);


	hits_lake.SetInteger(HITS_LAKE);
	hits_door.SetInteger(HITS_DOOR);
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{

	int i;
	for (i = 0; i < NUMRED; i++)
		diamond1[i].OnMove();
	for (i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnMove();
	}
	player1.OnMove();
	player2.OnMove();
	mood[0].OnMove();
	mood[1].OnMove1();
	button[0].OnMove();
	button[1].OnMove1();
	button[2].OnMove();
	reddoor.OnMove();
	icedoor.OnMove();
	box.OnMove();
	//
	// �P�_���l�O�_�I��y
	//

	for (i = 0; i < NUMRED; i++) {
		if (diamond1[i].IsAlive() && diamond1[i].HitPlayer(&player1)) {
			diamond1[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < NUMICE; i++)
	{
		if (diamond2[i].IsAlive() && diamond2[i].HitPlayer(&player2)) {
			diamond2[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < LAKERED; i++) {
		if ( Lake1[i].HitPlayer(&player2) && Lake1[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEICE; i++)
	{
		if ( Lake2[i].HitPlayer(&player1)&& Lake2[i].hack==false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEGREEN; i++)
	{
		if (Lake3[i].HitPlayer(&player1) && Lake3[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	if (box.HitEraser(&player1)||box.HitEraser(&player2)) {
		box.SetMovingLeft(true);
	}


	/*
	if (box.OnBox(player1.GetX1(), player1.GetX2(), player1.GetY1(), player1.GetY2())) {
		player1.SetFloor(box.GetY1() - 40);
	}
	if (box.OnBox(player2.GetX1(), player2.GetX2(), player2.GetY1(), player2.GetY2())) {
		player2.SetFloor(box.GetY1() - 40);
	}
	*/
	if (reddoor.IsAlive() && (reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(false);
	}
	if (!(reddoor.IsAlive()) && !(reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(true);
	}
	if (icedoor.IsAlive() && icedoor.HitPlayer(&player2)) {
		icedoor.SetIsAlive(false);
	}
	if (!(icedoor.IsAlive()) && !(icedoor.HitPlayer(&player2))) {
		icedoor.SetIsAlive(true);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player2))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player1))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
	}
	//if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player2))) {
		//mood[0].SetIsAlive(true);
		//mood[1].SetIsAlive(true);
	//}
	//if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player1))) {
		//mood[0].SetIsAlive(true);
		//mood[1].SetIsAlive(true);
	//}
	if (button[0].IsAlive() && ((button[0].HitPlayer(&player2)) || button[0].HitPlayer(&player1))) {
		button[0].SetIsAlive(false);
		button[1].SetIsAlive(false);
	}
	if (button[2].IsAlive() && ((button[2].HitPlayer(&player2)) || button[2].HitPlayer(&player1))) {
		button[2].SetIsAlive(false);
		button[1].SetIsAlive(false);
	}
	if (!((button[0].IsAlive()) && (button[2].IsAlive())) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2)) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[1].SetIsAlive(true);

	}
	if (!(button[0].IsAlive()) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2))) {
		button[0].SetIsAlive(true);
	}
	if (!(button[2].IsAlive()) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[2].SetIsAlive(true);
	}
	
	if (!(icedoor.IsAlive()) && !(reddoor.IsAlive())) {
		GotoGameState(GAME_STATE_WIN);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMRED; i++)	
		diamond1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < NUMICE; i++) {
		diamond2[i].LoadBitmap();
	}
	for (i = 0; i < LAKERED; i++)
		Lake1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < LAKEICE; i++) {
		Lake2[i].LoadBitmap();
	}
	for (i = 0; i < LAKEGREEN; i++) {
		Lake3[i].LoadBitmap();
	}

	player1.LoadBitmap();
	player2.LoadBitmap();
	reddoor.LoadBitmap();
	icedoor.LoadBitmap();
	for (i = 0; i < NUMMOD; i++) {
		mood[i].LoadBitmap();
	}
	for (i = 0; i < NUMBUT; i++) {
		button[i].LoadBitmap();
	}
	box.LoadBitmap();
	background.LoadBitmap(IDB_MAP1);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	hits_left.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_DING,  ".\\sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  ".\\sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  ".\\sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//




}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	const char KEY_P = 'P';

	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(true);

	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(true);
	}
	if (nChar == KEY_UP)
	{
		player1.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN)
	{
		player1.SetMovingDown(true);
	}
	if (nChar == KEY_A)
	{
		player2.SetMovingLeft(true);		
	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(true);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(true);
	}
	if (nChar == KEY_S)
	{

		player2.SetMovingDown(true);
	}
	if (nChar == KEY_P)
	{
		for (int i = 0; i < LAKERED; i++) {
			Lake1[i].hack = true;
		}
		for (int i = 0; i < LAKEICE; i++) {
			Lake2[i].hack= true;
		}
		for (int i = 0; i < LAKEGREEN; i++) {
			Lake3[i].hack = true;
		}
		hits_left.Add(10000);
	}
	//gamemap.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(false);
	}
	if (nChar == KEY_UP)
	{

		player1.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN)
	{

		player1.SetMovingDown(false);
	}
	if (nChar == KEY_A)
	{

		player2.SetMovingLeft(false);

	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(false);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(false);
	}
	if (nChar == KEY_S)
	{
		player2.SetMovingDown(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();

	for (int i=0; i < NUMRED; i++)
		diamond1[i].OnShow();				// �K�W��i���y
	for (int i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnShow();
	}
	
	reddoor.OnShow();
	icedoor.OnShow();
	mood[0].OnShow();
	mood[1].OnShow1();
	button[0].OnShow();
	button[1].OnShow1();
	button[2].OnShow();
	box.OnShow();
	for (int i = 0; i < LAKERED; i++)
	{
		Lake1[i].OnShow();				// �K�W��i���y
	}
	for (int i = 0; i < LAKEICE; i++)
	{
		Lake2[i].OnShow();
	}
	for (int i = 0; i < LAKEGREEN; i++)
	{
		Lake3[i].OnShow();
	}
	player1.OnShow();
	player2.OnShow();
	//reddoor.OnShow();
	//
	//  �K�W���W�Υk�U��������
	//
}
}